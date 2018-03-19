#ifndef QTELEMETRYMANAGERPRIVATE_H
#define QTELEMETRYMANAGERPRIVATE_H

#include <QList>
#include <QMap>

namespace QTelemetry {

class QTelemetryManager;
class AbstractDataSource;

class QTelemetryManagerPrivate
{
public:
    QTelemetryManagerPrivate(QTelemetryManager *manager) : q(manager) {}

private slots:
    void reset();

private:
    QList<AbstractDataSource *> m_sources;
    QMap<QString, AbstractDataSource *> m_map;

    QTelemetryManager *q;
};

}   // namespace QTelemetry

#endif // QTELEMETRYMANAGERPRIVATE_H
