#include "controldialog.h"
#include "ui_controldialog.h"
#include "connectedcreatorpluginconstants.h"

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
    if(!(firstRun() || checkEvalLicense())) {
        goSecondPage();
    }
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

bool ControlDialog::firstRun()
{
    auto settings = Core::ICore::settingsDatabase();
    bool first = settings->value(Constants::FIRST_RUN_KEY, true).value<bool>();
    if(first) settings->setValue(Constants::FIRST_RUN_KEY, false);
    return first;
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

} // namespace Internal
} // namespace ConnectedCreatorPlugin
