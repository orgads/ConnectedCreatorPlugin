#include "qtelemetry_logging.h"
#include "qtelemetrymanager.h"
#include "qtelemetrymanager_p.h"
#include "abstractdatasource.h"

namespace QTelemetry {

Q_LOGGING_CATEGORY(Log, "io.qt.QTelemetry", QtInfoMsg)

QTelemetryManager::QTelemetryManager(QObject *parent)
    : QObject(parent)
    , d(new QTelemetryManagerPrivate(this))
{
}

QTelemetryManager::~QTelemetryManager()
{
    delete d;
}

QTelemetryManagerPrivate::~QTelemetryManagerPrivate()
{
    qDeleteAll(sources);
}

QString QTelemetryManagerPrivate::organization()
{
    QString org =
    #ifdef Q_OS_MAC
        QCoreApplication::organizationDomain().isEmpty()
            ? QCoreApplication::organizationName() : QCoreApplication::organizationDomain();
    #else
        QCoreApplication::organizationName().isEmpty()
            ? QCoreApplication::organizationDomain() : QCoreApplication::organizationName();
    #endif
    if (org.isEmpty())
        org = QLatin1String("Unknown Organization");
    return org;
}

void QTelemetryManagerPrivate::createSettings()
{
    settings = new QSettings(organization(), QStringLiteral("QTelemetry.") + productId);
}

QSettings *QTelemetryManager::settings() const
{
    return d->settings;
}

void QTelemetryManager::setProductIdentifier(const QString &productId)
{
    d->productId = productId;
    d->createSettings(); // Reload settings

    emit productIdentifierChanged(productId);
}

QString QTelemetryManager::productIdentifier() const
{
    return d->productId;
}

bool QTelemetryManager::isEnabled() const
{
    d->createSettings(); // Update settings

    // Read enable settings
    d->settings->beginGroup("Telemetry");
    return d->settings->value("Enabled", false).toBool();
}

void QTelemetryManager::setEnabled(bool enabled)
{
    if(enabled == isEnabled()) return;

    // Write enable settings
    d->settings->beginGroup("Telemetry");
    d->settings->setValue("Enabled", enabled);
    d->settings->endGroup();
}

void QTelemetryManager::addDataSource(QAbstractDataSource *source)
{
    if(!d->index.contains(source->id())) {
        d->sources.append(source);
        d->index[source->id()] = d->sources.count() - 1;
    } else {
        int idx = d->index[source->id()];
        delete d->sources[idx];
        d->sources[idx] = source;
    }
}

QList<QAbstractDataSource *> QTelemetryManager::dataSources() const
{
    return d->sources;
}

QAbstractDataSource *QTelemetryManager::dataSource(QString id) const
{
    if(d->index.contains(id))
        return d->sources[d->index[id]];
    else {
        qCWarning(Log) << "Data source '" << id << "' does not exist!";
        return nullptr;
    }
}

QByteArray QTelemetryManager::jsonData(TelemetryLevel level)
{
    // TODO: add JSON generation
    Q_UNUSED(level)
    return QByteArray();
}

QByteArray QTelemetryManager::submit()
{
    QByteArray data = jsonData(telemetryLevel());
    emit dataSubmitted(data);   // Reset in all data sources called automatically here
    return data;
}

TelemetryLevel QTelemetryManager::telemetryLevel() const
{
    return d->level;
}

void QTelemetryManager::setTelemetryLevel(const TelemetryLevel level)
{
    d->level = level;
}

}   // namespace QTelemetry
