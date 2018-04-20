#include "qpainfosource.h"

#include <QVariant>
#include <QGuiApplication>

namespace QTelemetry {

QPAInfoSource::QPAInfoSource()
    : QAbstractDataSource("qpa", TelemetryLevel::BasicSystemInformation)
{
}

QString QPAInfoSource::name() const
{
    return tr("Qt platform plugin name");
}

QString QPAInfoSource::description() const
{
    return tr("The Qt underlying platform abstraction plugin name.");
}

QVariant QPAInfoSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("name", QGuiApplication::platformName());
    return m;
}

}   // namespace QTelemetry
