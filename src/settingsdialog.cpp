#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "connectedcreatorpluginconstants.h"
#include "pluginsettings.h"

#include <qtelemetrymanager.h>
#include <abstractdatasource.h>


namespace ConnectedCreator {
namespace Internal {

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setTelemetryManager(QTelemetry::QTelemetryManager* manager)
{
    m_manager = manager;
    ui->checkBox->setChecked(m_manager->isEnabled());
    int period = PluginSettings::expirePeriod();
    if(period < 0)
        ui->keepRadioButton->setChecked(true);
    else if(period == 0)
        ui->sentRadioButton->setChecked(true);
    else {
        ui->timeRadioButton->setChecked(true);
        ui->cacheSpinBox->setValue(std::min(ui->cacheSpinBox->maximum(), period));
    }
}

void SettingsDialog::on_timeRadioButton_toggled(bool checked)
{
    ui->cacheSpinBox->setEnabled(checked);
}

void SettingsDialog::accept()
{
    // Save settings
    if(m_manager) m_manager->setEnabled(ui->checkBox->isChecked());
    PluginSettings::setTelemetryEnabled(ui->checkBox->isChecked());

    if(ui->keepRadioButton->isChecked())
        PluginSettings::setExpirePeriod(-1);
    else if(ui->sentRadioButton->isChecked())
        PluginSettings::setExpirePeriod(0);
    else
        PluginSettings::setExpirePeriod(ui->cacheSpinBox->value());

    // Accept and close if not embedded
    if(ui->buttonBox->isVisible())
        QDialog::accept();
}

void SettingsDialog::embed(bool embedded)
{
    if(embedded)
        ui->buttonBox->hide();
    else
        ui->buttonBox->show();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
