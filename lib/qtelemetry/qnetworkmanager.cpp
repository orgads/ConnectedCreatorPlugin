#include "qtelemetry_logging.h"
#include "qnetworkmanager.h"
#include "qnetworkmanager_p.h"
#include "qtelemetryconstants.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegExp>
#include <QUrlQuery>

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
    d->url = QUrl(url.trimmed().remove(QRegExp("[/]+$")));
    if(!path.trimmed().isEmpty())
        d->url.setPath("/" + path.trimmed().remove(QRegExp("^[/]+")));
    if(d->url.isEmpty() || !d->url.isValid())
        qCWarning(Log) << "Error: backend URL is empty or invalid!";
}

void QNetworkManager::sendData()
{
    // Add product identifier and submission time as request parameters to URL
    QUrlQuery query;
    QDateTime submissionTime = d->telemetryManager->submit();
    query.addQueryItem("productIdentifier", d->telemetryManager->productIdentifier());
    query.addQueryItem("submissionTime", submissionTime.toString(Constants::FileNameDtFormat));
    d->url.setQuery(query);

    // Compose request
    QNetworkRequest request;
    request.setUrl(d->url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    // Get data from Telemetry Manager and send it
    QByteArray data = d->telemetryManager->logData(submissionTime);
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
