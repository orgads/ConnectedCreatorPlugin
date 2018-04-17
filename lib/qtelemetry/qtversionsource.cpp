#include "qtversionsource.h"

#include <QVariant>

namespace QTelemetry {

QtVersionSource::QtVersionSource()
    : QAbstractDataSource("qt", TelemetryLevel::BasicSystemInformation)
{
}

QString QtVersionSource::name() const
{
    return tr("Qt version");
}

QString QtVersionSource::description() const
{
    return tr("The Qt version used by this application.");
}

QVariant QtVersionSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("version", QString::fromLatin1(qVersion()));
    m.insert("license", "unknown");
    return m;
}

}   // namespace QTelemetry
