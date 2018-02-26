#include "controldialog.h"
#include "ui_controldialog.h"

#include <coreplugin/icore.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

ControlDialog::ControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlDialog)
{
    ui->setupUi(this);

    if(!checkEvalLicense()) {
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
