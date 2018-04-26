#ifndef INETWORKMANAGER_H
#define INETWORKMANAGER_H

#include "qtelemetry_global.h"
#include "qtelemetrymanager.h"

#include <QObject>

namespace QTelemetry {

class INetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit INetworkManager(QTelemetryManager *parent) : QObject(parent) {}

    virtual void setBackend(const QString & url, const QString & path = "") = 0;
    virtual void sendData() = 0;

signals:
    void finished(bool success);
};

}   // namespace QTelemetry

#endif // INETWORKMANAGER_H
