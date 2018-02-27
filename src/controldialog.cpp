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

    // Check first start here
    bool firstStart = firstRun();

    // Compose different description message if not first run or eval license
    if(!(firstStart || checkEvalLicense())) {
        ui->descrLabel->setText("If enabled, the analytics can be disabled at any time.");
        QFont font = ui->descrLabel->font();
        font.setItalic(true);
        ui->descrLabel->setFont(font);
        ui->horizLineWidget->hide();
    }
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

} // namespace Internal
} // namespace ConnectedCreatorPlugin
