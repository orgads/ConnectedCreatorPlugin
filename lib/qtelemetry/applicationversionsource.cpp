#include "applicationversionsource.h"

#include <QCoreApplication>
#include <QVariant>

namespace QTelemetry {

ApplicationVersionSource::ApplicationVersionSource() :
    QAbstractDataSource("application", TelemetryLevel::BasicSystemInformation)
{
}

QString ApplicationVersionSource::name() const
{
    return tr("Application version source");
}

QString ApplicationVersionSource::description() const
{
    return tr("The version of the application.");
}

QVariant ApplicationVersionSource::data()
{
    if (QCoreApplication::applicationVersion().isEmpty())
        return QVariant();

    // Get application name
    QString appName = (!QCoreApplication::applicationName().isEmpty()) ?
        QCoreApplication::applicationName() : manager()->productIdentifier();

    QVariantMap m;  // JSON key-value pair
    m.insert("name", appName);
    m.insert("version", QCoreApplication::applicationVersion());
    return m;
}

}   // namespace QTelemetry
