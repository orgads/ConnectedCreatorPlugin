#include "qtelemetry_logging.h"
#include "qtelemetrymanager.h"
#include "abstractdatasource.h"
#include "abstractdatasource_p.h"

namespace QTelemetry {

QAbstractDataSource::QAbstractDataSource(const QString &id , TelemetryLevel level)
    : QObject(nullptr)
    , d(new QAbstractDataSourcePrivate(this))
{
    d->id = id;
    d->level = level;
}

QAbstractDataSource::~QAbstractDataSource()
{
    delete d;
}

QString QAbstractDataSource::id() const
{
    return d->id;
}

TelemetryLevel QAbstractDataSource::telemetryLevel() const
{
    return d->level;
}

void QAbstractDataSource::setManager(QTelemetryManager *manager)
{
    d->manager = manager;
    setParent(manager);

    // Connect signals
    connect(d->manager, &QTelemetryManager::dataSubmitted, this, &QAbstractDataSource::reset);
    connect(d->manager, &QTelemetryManager::productIdentifierChanged,
            this, &QAbstractDataSource::load);

    emit managerChanged();
}

QTelemetryManager *QAbstractDataSource::manager() const
{
    return d->manager;
}

bool QAbstractDataSource::isManagerInitialized()
{
    if(d->manager && d->manager->settings()) {
        return true;
    } else if (d->manager) {
        qCWarning(Log) << "Telemetry manager was not set (initialized)!"
                       << "Could not load/save/reset '" << d->id << "' data source!";
        return false;
    } else {
        qCWarning(Log) << "Telemetry manager settings were not initialized!"
                       << "Could not load/save/reset '" << d->id << "' data source!";
        return false;
    }
}

}   // namespace QTelemetry
