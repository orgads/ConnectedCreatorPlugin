#include <qtelemetrymanager.h>
#include <abstractdatasource.h>

#include "statisticsdialog.h"
#include "ctreeview.h"
#include "qjsonmodel.h"
#include "jsonsyntaxhighlighter.h"
#include "ui_statisticsdialog.h"

#include <QFontDatabase>
#include <QScrollBar>
#include <QHeaderView>
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
}

void StatisticsDialog::showEvent(QShowEvent *event)
{
    if(m_manager) {
        QByteArray statisticsData = m_manager->data(
                    QTelemetry::TelemetryLevel::DetailedUsageStatistics);

        // Show JSON statistics
        ui->textBrowser->setPlainText(QString::fromUtf8(statisticsData.constData()));
        m_model->loadJson(statisticsData);
        ui->treeView->expandAll();

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
