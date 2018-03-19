#include "qtelemetrymanager.h"
#include "qtelemetrymanager_p.h"

namespace QTelemetry {

QTelemetryManager::QTelemetryManager(QObject *parent) : QObject(parent)
{
}

void QTelemetryManager::setProductIdentifier(const QString &productId)
{

}

bool QTelemetryManager::isEnabled() const
{

}

void QTelemetryManager::setEnabled(bool enabled)
{

}

QList<AbstractDataSource *> QTelemetryManager::dataSources()
{

}

QByteArray QTelemetryManager::jsonData(TelemetryLevel level)
{

}

}   // namespace QTelemetry
