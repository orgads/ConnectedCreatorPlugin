#include "platforminfosource.h"

#include <QVariant>
#include <QSysInfo>

namespace QTelemetry {

PlatformInfoSource::PlatformInfoSource()
    : QAbstractDataSource("platform", TelemetryLevel::BasicSystemInformation)
{
}

QString PlatformInfoSource::name() const
{
    return tr("OS name and version");
}

QString PlatformInfoSource::description() const
{
    return tr("The operating system name and version.");
}

QVariant PlatformInfoSource::data()
{
    QVariantMap m;  // JSON key-value pairs

    m.insert("os", QSysInfo::kernelType());
    m.insert("kernel", QSysInfo::kernelVersion());
    m.insert("type", QSysInfo::productType());
    m.insert("release", QSysInfo::productVersion());
    m.insert("name", QSysInfo::prettyProductName());

    return m;
}

}   // namespace QTelemetry
