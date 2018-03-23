#ifndef APPLICATIONVERSIONSOURCE_H
#define APPLICATIONVERSIONSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source for the application version. The application version is retrieved
/// via QCoreApplication::applicationVersion.
///
/// The default telemetry mode for this source is TelemetryLevel::BasicSystemInformation.
class QTELEMETRYSHARED_EXPORT ApplicationVersionSource : public QAbstractDataSource
{
public:
    /// Creates a new application version source.
    ApplicationVersionSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // APPLICATIONVERSIONSOURCE_H
