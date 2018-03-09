#include "controldialog.h"
#include "ui_controldialog.h"
#include "connectedcreatorpluginconstants.h"
#include "pluginsettings.h"

#include <kuserfeedback/core/provider.h>
#include <kuserfeedback/core/abstractdatasource.h>

#include <coreplugin/icore.h>
#include <coreplugin/settingsdatabase.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

namespace ConnectedCreator {
namespace Internal {

ControlDialog::ControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlDialog)
{
    ui->setupUi(this);

    init();

    // Show 2nd dialog page and short description message if not first run or eval license
    bool first = PluginSettings::firstStart();
    if(!(first || checkEvalLicense())) {
        goSecondPage();
    }
    if(first)
        PluginSettings::setFirstStart();
}

void ControlDialog::init()
{
    ui->okButton->setIcon(style()->standardIcon(QStyle::SP_DialogOkButton));
    ui->cancelButton->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
    ui->helpButton->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));

    ui->stackedWidget->setCurrentIndex(0);  // Go to 1st page
    ui->okButton->hide();
}

ControlDialog::~ControlDialog()
{
    delete ui;
}

void ControlDialog::setFeedbackProvider(KUserFeedback::Provider* provider)
{
    m_feedbackProvider = provider;
    ui->groupBox->setChecked(m_feedbackProvider->isEnabled());

    qDebug() << "Sources: ";
    foreach (auto source, m_feedbackProvider->dataSources()) {
        qDebug() << ((KUserFeedback::AbstractDataSource*)source)->name()
                 << ((KUserFeedback::AbstractDataSource*)source)->description();
    }
}

bool ControlDialog::checkEvalLicense()
{
    auto plugins = ExtensionSystem::PluginManager::plugins();
    bool eval = false;
    foreach (ExtensionSystem::PluginSpec *spec, plugins) {
        if(spec->name().contains("LicenseChecker")) {
            eval = true;
            break;
        }
    }
    return eval;
}

void ControlDialog::goSecondPage()
{
    ui->telemetryButton->hide();
    ui->okButton->show();
    ui->stackedWidget->setCurrentIndex(1);  // Go to 2nd page
}

void ControlDialog::on_telemetryButton_clicked()
{
    goSecondPage();
    ui->groupBox->setChecked(true);
}

void ControlDialog::accept()
{
    m_feedbackProvider->setEnabled(ui->groupBox->isChecked());
    PluginSettings::setTelemetryEnabled(ui->groupBox->isChecked());

    QDialog::accept();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
