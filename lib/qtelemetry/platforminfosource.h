#ifndef PLATFORMINFOSOURCE_H
#define PLATFORMINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Reports information about the platform the application is running on.
/// This includes two string data fields:
///   - platform.os: the operating system name
///   - platform.version: the operating system or distribution version.
///
/// The default telemetry level for this source is TelemetryLevel::BasicSystemInformation.
///
class PlatformInfoSource : public QAbstractDataSource
{
public:
    PlatformInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // PLATFORMINFOSOURCE_H
