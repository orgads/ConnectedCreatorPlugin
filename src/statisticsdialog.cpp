#include <qtelemetrymanager.h>
#include <abstractdatasource.h>
#include <statisticsmodel.h>

#include "statisticsdialog.h"
#include "ctreeview.h"
#include "qjsonmodel.h"
#include "jsonsyntaxhighlighter.h"
#include "ui_statisticsdialog.h"

#include <QFontDatabase>
#include <QScrollBar>
#include <QHeaderView>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

namespace ConnectedCreator {
namespace Internal {

StatisticsDialog::StatisticsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);

    // Initialize controls
    init();
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::init()
{
    // Create and apply json tree model
    m_model = new QJsonModel(this);
    ui->treeView->setModel(m_model);

    // Add JSON syntax highlighting
    new JsonSyntaxHighlighter(ui->textBrowser->document());

    // Initialize UI look and feel
    ui->textBrowser->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    ui->treeView->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QPalette treeViewPalette = ui->treeView->palette();
    treeViewPalette.setColor(QPalette::AlternateBase, QColor("#e2eef9"));
    ui->treeView->setPalette(treeViewPalette);
}

void StatisticsDialog::on_textToolButton_toggled(bool checked)
{
    if(checked)
        ui->textBrowser->show();
    else
        ui->textBrowser->hide();
}

void StatisticsDialog::on_treeToolButton_toggled(bool checked)
{
    if(checked)
        ui->treeView->show();
    else
        ui->treeView->hide();
}

void StatisticsDialog::setTelemetryManager(QTelemetry::QTelemetryManager* manager)
{
    m_manager = manager;
    telemetryEnum = QMetaEnum::fromType<QTelemetry::TelemetryLevel>();

    // Setup UI
    ui->comboBox->setModel(m_manager->statisticsModel());
    ui->comboBox->setCurrentIndex(0);
    ui->slider->setMaximum(0);
    ui->slider->setMaximum(telemetryEnum.keyCount() - 1);
    ui->slider->setValue(telemetryEnum.keyCount() - 1);

    // Connect combobox with statistics model
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(loadStatistics()));
    connect(m_manager->statisticsModel(), &QAbstractItemModel::modelReset, [=]() {
        if(ui->comboBox->currentIndex() < 0)    // If log file(s) was removed
            ui->comboBox->setCurrentIndex(0);
    });
    // Connect model data chnaged signal to reload statistics
    connect(m_manager->statisticsModel(),
            SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
            this, SLOT(loadStatistics()));
    // Connect slider to telemetry level
    connect(ui->slider, &QSlider::valueChanged, [=]() {
        // Get TelemetryLevel enum value
        int level = telemetryEnum.value(ui->slider->value());
        ((QTelemetry::StatisticsModel*)m_manager->statisticsModel())->setTelemetryLevel(
            static_cast<QTelemetry::TelemetryLevel>(level));
    });
}

QByteArray StatisticsDialog::getStatisticsData()
{
    QModelIndex index = m_manager->statisticsModel()->index(
                ui->comboBox->currentIndex(), 0);
    QByteArray data = m_manager->statisticsModel()->data(index,
        (int)QTelemetry::StatisticsModel::JsonRole).toJsonDocument().toJson();

    return data;
}

void StatisticsDialog::loadStatistics()
{
    // Get data
    QByteArray statisticsData = getStatisticsData();

    // Show JSON statistics
    ui->textBrowser->setPlainText(QString::fromUtf8(statisticsData.constData()));
    m_model->loadJson(statisticsData);
    ui->treeView->expandAll();
}

void StatisticsDialog::showEvent(QShowEvent *event)
{
    if(m_manager) {
        loadStatistics();

        // Adjust scroll bar step for synchronous scrolling
        syncScrollbars();
    }

    QDialog::showEvent(event);
}

/// \brief StatisticsDialog::syncScrollbars adjusts scroll bar steps for
/// tree view and text browser synchronous scrolling
void StatisticsDialog::syncScrollbars()
{
    // Get tree view row height in pixels for scroll step in text browser
    int step = ui->treeView->rowHeight(m_model->index(0, 0));
    ui->textBrowser->verticalScrollBar()->setSingleStep(step);

    // Disconnect all signals
    disconnect(ui->textBrowser->verticalScrollBar());
    disconnect(ui->treeView->verticalScrollBar());

    // Connect new signals with appropriate step scaling
    connect(ui->textBrowser->verticalScrollBar(), &QScrollBar::valueChanged,
            [this, step](int value) {
                ui->treeView->verticalScrollBar()->setValue(value / step);
            });
    connect(ui->treeView->verticalScrollBar(), &QScrollBar::valueChanged,
            [this, step](int value) {
                ui->textBrowser->verticalScrollBar()->setValue(value * step);
            });
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin

void ConnectedCreator::Internal::StatisticsDialog::on_saveToolButton_clicked()
{
    // Get data
    QByteArray statisticsData = getStatisticsData();

    QString defaultFileName = ((ui->comboBox->currentIndex() == 0) ?
        QDateTime::currentDateTimeUtc().toString("yyyyMMdd-hhmmss") :
        QDateTime::fromString(ui->comboBox->currentText(), "yyyy-MM-dd hh:mm:ss")
        .toString("yyyyMMdd-hhmmss")) + ".log";

    // Open file save dialog
    QString filter = tr("Logs (*.log)");
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Statistics Log File"),
                                                    defaultFileName,
                                                    filter, &filter);
    if(!fileName.isEmpty()) {
        // Save to file
        fileName = (fileName.endsWith(".log")) ? fileName : fileName + ".log";
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly)) {
            qWarning() << "Unable to open file to write statistics:"
                       << file.fileName() << file.errorString();
            return;
        }
        file.write(statisticsData);
    }
}
