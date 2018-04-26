#include "qtelemetry_logging.h"
#include "qnetworkmanager.h"
#include "qnetworkmanager_p.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegExp>

namespace QTelemetry {

QNetworkManager::QNetworkManager(QTelemetryManager *parent)
    : INetworkManager(parent)
    , d(new QNetworkManagerPrivate(this))
{
    d->telemetryManager = parent;
    d->networkManager = new QNetworkAccessManager(this);
}

QNetworkManager::~QNetworkManager()
{
    delete d;
}

void QNetworkManager::setBackend(const QString & url, const QString & path)
{
    d->m_url = QUrl(url.trimmed().remove(QRegExp("[/]+$")));
    if(!path.trimmed().isEmpty())
        d->m_url.setPath("/" + path.trimmed().remove(QRegExp("^[/]+")));
    if(d->m_url.isEmpty() || !d->m_url.isValid())
        qCWarning(Log) << "Error: backend URL is empty or invalid!";
}

void QNetworkManager::sendData()
{
    QNetworkRequest request;
    request.setUrl(d->m_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    // Get data from Telemetry Manager and send it
    QByteArray data = d->telemetryManager->submit();
    // TODO: send submission time and telemetryManager->productIdentifier() as request parameters
    QNetworkReply *reply = d->networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, [this, data, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qCInfo(Log) << "Success data submission: " << reply->readAll();
            emit finished(true);
        } else {
            qCWarning(Log) << "Error sending data to backend: "
                           << reply->errorString() << reply->readAll();
            emit finished(false);
            // TODO: retry 3 times on error
            // ...
        }
        reply->close();
        reply->deleteLater();
    });
}

}   // namespace QTelemetry
