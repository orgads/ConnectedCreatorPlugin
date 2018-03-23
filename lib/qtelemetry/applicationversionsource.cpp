#include "applicationversionsource.h"

#include <QCoreApplication>
#include <QVariant>

namespace QTelemetry {

ApplicationVersionSource::ApplicationVersionSource() :
    QAbstractDataSource("applicationVersion", TelemetryLevel::BasicSystemInformation)
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

    QVariantMap m;  // JSON key-value pair
    m.insert("value", QCoreApplication::applicationVersion());
    return m;
}

}   // namespace QTelemetry
