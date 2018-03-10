#include <kuserfeedback/core/provider.h>
#include <kuserfeedback/core/abstractdatasource.h>

#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"

#include <QFontDatabase>

namespace ConnectedCreator {
namespace Internal {

StatisticsDialog::StatisticsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);
    ui->textBrowser->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::on_textToolButton_clicked(bool checked)
{
    if(checked)
        ui->textBrowser->hide();
    else
        ui->textBrowser->show();
}

void StatisticsDialog::on_treeToolButton_clicked(bool checked)
{
    if(checked)
        ui->treeWidget->hide();
    else
        ui->treeWidget->show();
}

void StatisticsDialog::setFeedbackProvider(KUserFeedback::Provider* provider)
{
    m_feedbackProvider = provider;
}

void StatisticsDialog::showEvent(QShowEvent *event)
{
    if(m_feedbackProvider) {
        QByteArray jsonData;
        QMetaObject::invokeMethod(
            m_feedbackProvider, "jsonData",
            Q_RETURN_ARG(QByteArray, jsonData),
            Q_ARG(KUserFeedback::Provider::TelemetryMode,
                  KUserFeedback::Provider::DetailedUsageStatistics));

        // Show JSON statistics
        ui->textBrowser->setPlainText(QString::fromUtf8(jsonData.constData()));
    }

    QDialog::showEvent(event);
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
