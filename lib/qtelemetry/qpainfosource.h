#ifndef QPAINFOSOURCE_H
#define QPAINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Reports information about the Qt platform abstraction plugin the application
/// is running on.
///
/// The default telemetry mode for this source is TelemetryLevel::BasicSystemInformation.
///
class QTELEMETRYSHARED_EXPORT QPAInfoSource : public QAbstractDataSource
{
public:
    QPAInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // QPAINFOSOURCE_H
