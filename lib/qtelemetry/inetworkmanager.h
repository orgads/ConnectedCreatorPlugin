#ifndef INETWORKMANAGER_H
#define INETWORKMANAGER_H

#include "qtelemetry_global.h"

namespace QTelemetry {

class INetworkManager
{
public:
    void setBackend(const QString & url, const QString & path = "") = 0;
    void sendData(const QByteArray &data) = 0;
};

}   // namespace QTelemetry

#endif // INETWORKMANAGER_H
