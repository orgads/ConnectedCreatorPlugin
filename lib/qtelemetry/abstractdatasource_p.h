#ifndef ABSTRACTDATASOURCEPRIVATE_H
#define ABSTRACTDATASOURCEPRIVATE_H

namespace QTelemetry {

class QAbstractDataSource;
class QTelemetryManager;

class QAbstractDataSourcePrivate
{
public:
    QAbstractDataSourcePrivate(QAbstractDataSource *parent) : q(parent) {}
    QTelemetryManager *manager = nullptr;

    QString id;
    TelemetryLevel level;

    QAbstractDataSource *q;
};

}   // namespace QTelemetry

#endif // ABSTRACTDATASOURCEPRIVATE_H
