﻿#include "datasourcesdialog.h"
#include "ui_datasourcesdialog.h"
#include "connectedcreatorpluginconstants.h"
#include "pluginsettings.h"

#include <qtelemetrymanager.h>
#include <abstractdatasource.h>

#include <coreplugin/icore.h>
#include <coreplugin/settingsdatabase.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <extensionsystem/iplugin.h>

namespace ConnectedCreator {
namespace Internal {

DataSourcesDialog::DataSourcesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataSourcesDialog)
{
    ui->setupUi(this);
}

DataSourcesDialog::~DataSourcesDialog()
{
    delete ui;
}

void DataSourcesDialog::setTelemetryManager(QTelemetry::QTelemetryManager* manager)
{
    m_manager = manager;

    // Generate generic and Qt Creator specific data sources list
    generateDataSourcesList();
}

/// \brief Generates and updates generic and Qt Creator specific data sources list
void DataSourcesDialog::generateDataSourcesList()
{
    if(!m_manager) return;

    QString genericText = "<ul>",
            qtcText = "<ul>";

    foreach (auto src, m_manager->dataSources()) {
        QString name = src->name(); // src->description();
        if (name.isEmpty()) continue;

        QString element = QString("<li>") + "<b>" + src->id() + "</b> – " + name + "</li>";
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

bool DataSourcesDialog::checkEvalLicense()
{
    auto plugins = ExtensionSystem::PluginManager::plugins();
    bool eval = false;
    foreach (ExtensionSystem::PluginSpec *spec, plugins) {
        if(spec->name().contains("LicenseChecker")) {
            metaObject()->invokeMethod(
                spec->plugin(), "evaluationLicense", Q_RETURN_ARG(bool, eval));
            break;
        }
    }
    return eval;
}

void DataSourcesDialog::embed(bool embedded)
{
    if(embedded)
        ui->buttonBox->hide();
    else
        ui->buttonBox->show();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
