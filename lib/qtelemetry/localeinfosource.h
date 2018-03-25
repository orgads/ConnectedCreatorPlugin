#ifndef LOCALEINFOSOURCE_H
#define LOCALEINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source reporting the region and language settings.
///
/// The default telemetry mode for this source is TelemetryLevel::DetailedSystemInformation.
///
class LocaleInfoSource : public QAbstractDataSource
{
public:
    LocaleInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // LOCALEINFOSOURCE_H
