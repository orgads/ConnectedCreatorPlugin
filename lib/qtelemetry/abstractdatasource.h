#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H

#include "qtelemetrymanager.h"

#include <QObject>

namespace QTelemetry {

class AbstractDataSource : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDataSource(QObject *parent = nullptr);
    /// Returns the id of this data source.
    QString id() const;
    /// short name which can be shown to user
    QString name() const;
    /// Data source description
    virtual QString description() const = 0;

    virtual QVariant data() = 0;

    TelemetryLevel telemetryLevel() const;

signals:

public slots:
};

}   // namespace QTelemetry

#endif // ABSTRACTDATASOURCE_H
