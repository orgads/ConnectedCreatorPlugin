#ifndef QNETWORKMANAGER_H
#define QNETWORKMANAGER_H

#include "inetworkmanager.h"

namespace QTelemetry {

class QNetworkManagerPrivate;

class QNetworkManager : public INetworkManager
{
    Q_OBJECT

public:
    QNetworkManager(QObject *parent = Q_NULLPTR);
    ~QNetworkManager();

    virtual void setBackend(const QString & url, const QString & path = "");
    virtual void sendData(const QByteArray &data);

private:
    QNetworkManagerPrivate *d;
};

}   // namespace QTelemetry

#endif // QNETWORKMANAGER_H
