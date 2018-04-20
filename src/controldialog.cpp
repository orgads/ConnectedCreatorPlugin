#include "controldialog.h"
#include "ui_controldialog.h"
#include "connectedcreatorpluginconstants.h"
#include "pluginsettings.h"

#include <qtelemetrymanager.h>
#include <abstractdatasource.h>

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

void ControlDialog::setTelemetryManager(QTelemetry::QTelemetryManager* manager)
{
    m_manager = manager;
    ui->groupBox->setChecked(m_manager->isEnabled());

    // Generate generic and Qt Creator specific data sources list
    generateDataSourcesList();
}

/// \brief Generates and updates generic and Qt Creator specific data sources list
void ControlDialog::generateDataSourcesList()
{
    if(!m_manager) return;

    QString genericText = "<ul>",
            qtcText = "<ul>";

    foreach (auto src, m_manager->dataSources()) {
        QString name = src->name(); // src->description();
        if (name.isEmpty()) continue;

        QString element = QString("<li>") + name + "</li>";
        if(src->telemetryLevel() < QTelemetry::TelemetryLevel::DetailedUsageStatistics)
            genericText += element;
        else
            qtcText += element;
    }
    genericText += "</ul>";
    qtcText += "</ul>";

    ui->genericTextBrowser->setHtml(genericText);
    ui->qtcTextBrowser->setHtml(qtcText);
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
    if(m_manager) m_manager->setEnabled(ui->groupBox->isChecked());
    PluginSettings::setTelemetryEnabled(ui->groupBox->isChecked());

    QDialog::accept();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
