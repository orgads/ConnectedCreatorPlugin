#include "qtversionsource.h"

#include <QVariant>

namespace QTelemetry {

QtVersionSource::QtVersionSource()
    : QAbstractDataSource("qtVersion", TelemetryLevel::BasicSystemInformation)
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
    m.insert("value", QString::fromLatin1(qVersion()));
    return m;
}

}   // namespace QTelemetry
