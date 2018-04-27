#ifndef QNETWORKMANAGER_H
#define QNETWORKMANAGER_H

#include "qtelemetry_global.h"
#include "inetworkmanager.h"

namespace QTelemetry {

class QTelemetryManager;
class QNetworkManagerPrivate;

class QTELEMETRYSHARED_EXPORT QNetworkManager : public INetworkManager
{
    Q_OBJECT

public:
    QNetworkManager(QTelemetryManager *parent);
    ~QNetworkManager();

    virtual void setBackend(const QString & url, const QString & path = "") override;
    virtual void sendData() override;

private:
    QNetworkManagerPrivate *d;
};

}   // namespace QTelemetry

#endif // QNETWORKMANAGER_H
