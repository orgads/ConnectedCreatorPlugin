#ifndef SCREENINFOSOURCE_H
#define SCREENINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source for information about connected displays.
/// This provides as array of maps containing the following properties:
/// - height: Height of the corresponding screen in pixel.
/// - width: Width of the corresponding screen in pixel.
/// - dpi: Dots per inch of the corresponding screen.
///
/// The default telemetry level for this source is TelemetryLevel::DetailedSystemInformation.
///
class QTELEMETRYSHARED_EXPORT ScreenInfoSource : public QAbstractDataSource
{
public:
    ScreenInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // SCREENINFOSOURCE_H
