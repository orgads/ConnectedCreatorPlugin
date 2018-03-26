#ifndef STYLEINFOSOURCE_H
#define STYLEINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source of widget style and color scheme used by the application.
///
/// The default telemetry level for this source is TelemetryLevel::DetailedSystemInformation.
///
class StyleInfoSource : public QAbstractDataSource
{
public:
    StyleInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // STYLEINFOSOURCE_H
