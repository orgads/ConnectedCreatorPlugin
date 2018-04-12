#ifndef QNETWORKMANAGERPRIVATE_H
#define QNETWORKMANAGERPRIVATE_H

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;

namespace QTelemetry {

class QNetworkManager;

class QNetworkManagerPrivate : public QObject
{
    Q_OBJECT

public:
    QNetworkManagerPrivate(QNetworkManager *parent) : q(parent) {}

    QNetworkAccessManager *m_manager;
    QUrl m_url;

    QNetworkManager *q;
};

}   // namespace QTelemetry

#endif // QNETWORKMANAGERPRIVATE_H
