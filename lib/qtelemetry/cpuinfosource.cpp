#include "cpuinfosource.h"

#include <QVariant>
#include <QThread>

namespace QTelemetry {

CpuInfoSource::CpuInfoSource()
    : QAbstractDataSource("cpu", TelemetryLevel::DetailedSystemInformation)
{
}

QString CpuInfoSource::name() const
{
    return tr("CPU information source");
}

QString CpuInfoSource::description() const
{
    return tr("CPU type and count used in this system.");
}

QVariant CpuInfoSource::data()
{
    QVariantMap m;
    m.insert("architecture", QSysInfo::currentCpuArchitecture());
    m.insert("count", QThread::idealThreadCount());
    return m;
}

}   // namespace QTelemetry
