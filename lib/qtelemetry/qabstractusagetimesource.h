#ifndef QABSTRACTUSAGETIMESOURCE_H
#define QABSTRACTUSAGETIMESOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class QAbstractUsageTimeSourcePrivate;

/// Abstract Data source reports custom object or widget usage time in seconds.
/// @see QmlDesignerUsageTimeSource from ConnectedCreatorPlugin example
///
/// The default telemetry level for this source is TelemetryLevel::DetailedUsageStatistics.
///
class QAbstractUsageTimeSource : public QAbstractDataSource
{
    Q_OBJECT

public:
    /// Saves source state on exit
    ~QAbstractUsageTimeSource();

    virtual QString name() const override = 0;
    virtual QString description() const override = 0;
    QVariant data() final override;

signals:
    /// Emit this signal in derived class to start time counter
    void started();
    /// Emit this signal in derived class to stop time counter
    void stopped();

protected slots:
    /// Starts usage time count slot to connect signals directly
    void start();
    /// Stops usage time count slot to connect signals directly
    void stop();

    void reset() override;
    void load() override;
    void save() override;

protected:
    /// Creates new custom object or widget usage time data source instance
    explicit QAbstractUsageTimeSource(const QString &id);
    /// Returns whether tracked object/widget is currently using or not
    bool isUsing() const;

private:
    QAbstractUsageTimeSourcePrivate *d;
};

}   // namespace QTelemetry

#endif // QABSTRACTUSAGETIMESOURCE_H
