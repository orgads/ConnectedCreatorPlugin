#include "qtelemetry_logging.h"
#include "qnetworkmanager.h"
#include "qnetworkmanager_p.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace QTelemetry {

QNetworkManager::QNetworkManager(QObject *parent)
    : INetworkManager(parent)
    , d(new QNetworkManagerPrivate(this))
{
    d->m_manager = new QNetworkAccessManager(this);
}

QNetworkManager::~QNetworkManager()
{
    delete d;
}

void QNetworkManager::setBackend(const QString & url, const QString & path)
{
    d->m_url = QUrl(url);
    d->m_url.setPath(path);
}

void QNetworkManager::sendData(const QByteArray &data)
{
    QNetworkRequest request;
    request.setUrl(d->m_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkReply *reply = d->m_manager->post(request, data);

    connect(reply, &QNetworkReply::readyRead, [this, data, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qCInfo(Log) << "Success data submission: " << reply->readAll();
            emit finished(true);
        } else {
            qCWarning(Log) << "Error sending data to backend: " << reply->errorString();
            emit finished(false);
            // TODO: retry 3 times on error
            // ...
        }
        reply->close();
        reply->deleteLater();
    });
}

}   // namespace QTelemetry
