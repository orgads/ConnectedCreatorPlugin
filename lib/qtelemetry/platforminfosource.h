#ifndef PLATFORMINFOSOURCE_H
#define PLATFORMINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Reports information about the platform the application is running on.
/// This includes two string data fields:
///   - platform.os: the operating system name
///   - platform.kernel: the operating system, kernel or distribution version.
///   - platform.type: operating system type
///   - platform.release: operating system release/product version
///   - platform.name: pretty operating system name
///
/// The default telemetry level for this source is TelemetryLevel::BasicSystemInformation.
///
class QTELEMETRYSHARED_EXPORT PlatformInfoSource : public QAbstractDataSource
{
public:
    PlatformInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // PLATFORMINFOSOURCE_H
