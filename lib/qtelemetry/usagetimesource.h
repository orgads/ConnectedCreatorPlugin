#ifndef USAGETIMESOURCE_H
#define USAGETIMESOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class UsageTimeSourcePrivate;

/// Data source reports total application usage time in seconds.
///
/// The default telemetry level for this source is TelemetryLevel::BasicUsageStatistics.
///
class QTELEMETRYSHARED_EXPORT UsageTimeSource : public QAbstractDataSource
{
    Q_OBJECT

public:
    /// Creates new application usage time data source instance
    UsageTimeSource();

    /// Saves source state on exit
    ~UsageTimeSource();

    QString name() const override;
    QString description() const override;
    QVariant data() override;

protected slots:
    void reset() override;
    void load() override;
    void save() override;

private:
    UsageTimeSourcePrivate *d;
};

}   // namespace QTelemetry

#endif // USAGETIMESOURCE_H
