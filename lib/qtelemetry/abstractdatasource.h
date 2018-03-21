#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H

#include "qtelemetry_global.h"
#include "qtelemetrymanager.h"

#include <QObject>

namespace QTelemetry {

class QTelemetryManager;
class QAbstractDataSourcePrivate;

class QTELEMETRYSHARED_EXPORT QAbstractDataSource : public QObject
{
    Q_OBJECT

public:
    /// Data collected by a source
    virtual QVariant data() = 0;

    /// Returns the id of this data source.
    QString id() const;
    /// short name which can be shown to user
    virtual QString name() const = 0;
    /// Data source description
    virtual QString description() const = 0;

    /// Necessary for QTelemetryManager on initialization
    void setManager(QTelemetryManager *manager);
    QTelemetryManager *manager() const;

    TelemetryLevel telemetryLevel() const;

public slots:
    virtual void reset() = 0;

protected:
    explicit QAbstractDataSource(const QString &id, TelemetryLevel level = TelemetryLevel::NoTelemetry);
    virtual void load() = 0;
    bool checkManagerInitialized();

private:
    QAbstractDataSourcePrivate *d;
};

}   // namespace QTelemetry

#endif // ABSTRACTDATASOURCE_H
