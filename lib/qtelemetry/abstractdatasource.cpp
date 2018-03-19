#include "abstractdatasource.h"

namespace QTelemetry {

AbstractDataSource::AbstractDataSource(QObject *parent) : QObject(parent)
{

}

TelemetryLevel AbstractDataSource::telemetryLevel() const
{

}

}   // namespace QTelemetry
