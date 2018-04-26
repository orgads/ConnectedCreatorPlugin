#ifndef QNETWORKMANAGERPRIVATE_H
#define QNETWORKMANAGERPRIVATE_H

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;

namespace QTelemetry {

class QTelemetryManager;
class QNetworkManager;

class QNetworkManagerPrivate : public QObject
{
    Q_OBJECT

public:
    QNetworkManagerPrivate(QNetworkManager *parent) : q(parent) {}

    QNetworkAccessManager *networkManager;
    QUrl m_url;

    QTelemetryManager *telemetryManager;
    QNetworkManager *q;
};

}   // namespace QTelemetry

#endif // QNETWORKMANAGERPRIVATE_H
