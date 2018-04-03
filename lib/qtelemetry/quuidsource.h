#ifndef QUUIDSOURCE_H
#define QUUIDSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class QUuidSourcePrivate;

/// Data source reports randommly generated unique machine ID not connected to
/// concrete user or Qt Account.
///
/// The default telemetry level for this source is TelemetryLevel::DetailedSystemInformation.
///
class QTELEMETRYSHARED_EXPORT QUuidSource : public QAbstractDataSource
{
    Q_OBJECT

public:
    /// Creates new unique machine ID data source instance
    QUuidSource();
    /// Saves source state on exit
    ~QUuidSource();

    QString name() const override;
    QString description() const override;
    QVariant data() override;

protected slots:
    void load() override;
    void save() override;

private:
    QUuidSourcePrivate *d;
};

}   // namespace QTelemetry

#endif // QUUIDSOURCE_H
