#include "qtclicensesource.h"

#include <QVariant>
#include <coreplugin/icore.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <extensionsystem/iplugin.h>

QtcLicenseSource::QtcLicenseSource()
    : QAbstractDataSource("qtcLicense", QTelemetry::TelemetryLevel::CustomSystemInformation)
{
}

QString QtcLicenseSource::name() const
{
    return tr("Qt Creator licence type");
}

QString QtcLicenseSource::description() const
{
    return tr("Qt Creator licence type string: open source, evaluation, commercial");
}

QVariant QtcLicenseSource::data()
{
    QVariantMap m;  // JSON key-value pair
    m.insert("value", getLicense());
    return m;
}

QString QtcLicenseSource::getLicense()
{
    auto plugins = ExtensionSystem::PluginManager::plugins();
    bool eval = false, hasLicenseChecker = false;
    foreach (ExtensionSystem::PluginSpec *spec, plugins)
    {
        if(spec->name().contains("LicenseChecker"))
        {
            metaObject()->invokeMethod(spec->plugin(), "evaluationLicense",
                                       Q_RETURN_ARG(bool, eval));
            hasLicenseChecker = true;
            break;
        }
    }

    if(!hasLicenseChecker)
        return "opensource";
    else if(eval)
        return "evaluation";
    else
        return "commercial";
}
