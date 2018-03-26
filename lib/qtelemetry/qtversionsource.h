#ifndef QTVERSIONSOURCE_H
#define QTVERSIONSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source reporting the Qt version used at runtime.
///
/// The default telemetry level for this source is TelemetryLevel::BasicSystemInformation.
///
class QTELEMETRYSHARED_EXPORT QtVersionSource : public QAbstractDataSource
{
public:
    QtVersionSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // QTVERSIONSOURCE_H
