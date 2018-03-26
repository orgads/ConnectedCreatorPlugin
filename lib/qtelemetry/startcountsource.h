#ifndef STARTCOUNTSOURCE_H
#define STARTCOUNTSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class StartCountSourcePrivate;

/// Data source reports the total applications starts count.
///
/// The default telemetry level for this source is TelemetryLevel::BasicUsageStatistics.
///
class QTELEMETRYSHARED_EXPORT StartCountSource : public QAbstractDataSource
{
    Q_OBJECT

public:
    /// Creates new applications starts count data source instance
    StartCountSource();
    /// Saves source state on exit
    ~StartCountSource();

    QString name() const override;
    QString description() const override;
    QVariant data() override;

protected slots:
    void reset() override;
    void load() override;
    void save() override;

private:
    StartCountSourcePrivate *d;
};

}   // namespace QTelemetry

#endif // STARTCOUNTSOURCE_H
