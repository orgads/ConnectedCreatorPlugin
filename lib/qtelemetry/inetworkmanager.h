#ifndef INETWORKMANAGER_H
#define INETWORKMANAGER_H

#include "qtelemetry_global.h"

#include <QObject>

namespace QTelemetry {

class INetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit INetworkManager(QObject *parent = Q_NULLPTR) : QObject(parent) {}

    virtual void setBackend(const QString & url, const QString & path = "") = 0;
    virtual void sendData(const QByteArray &data) = 0;

signals:
    void finished(bool success);
};

}   // namespace QTelemetry

#endif // INETWORKMANAGER_H
