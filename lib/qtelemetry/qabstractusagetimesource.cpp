#include "qabstractusagetimesource.h"
#include "qabstractusagetimesource_p.h"

#include <QVariant>
#include <QSettings>

namespace QTelemetry {

QAbstractUsageTimeSource::QAbstractUsageTimeSource(const QString &id)
    : QAbstractDataSource(id, TelemetryLevel::DetailedUsageStatistics)
    , d(new QAbstractUsageTimeSourcePrivate(this))
{
    // Connect signals/slot for automatic time count
    connect(this, &QAbstractUsageTimeSource::started,
            this, &QAbstractUsageTimeSource::start);
    connect(this, &QAbstractUsageTimeSource::stopped,
            this, &QAbstractUsageTimeSource::stop);
}

QAbstractUsageTimeSource::~QAbstractUsageTimeSource()
{
    save();
    delete d;
}

QVariant QAbstractUsageTimeSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("usageTime", d->currentUsageTime());
    m.insert("startCount", d->startCount);
    return m;
}

void QAbstractUsageTimeSource::reset()
{
    d->usageTime = 0;
    d->startCount = 0;
    d->startTime.restart();
    save();
}

void QAbstractUsageTimeSource::load()
{
    // Load custom usage time & start count settings
    if(isManagerInitialized()) {
        d->startTime.start();
        d->usageTime = manager()->settings()->value("Sources/" + id() + ".usageTime", 0).toInt();
        d->startCount = manager()->settings()->value("Sources/" + id() + ".startCount", 0).toInt();
        d->using_ = manager()->settings()->value("Sources/" + id() + "_using", 0).toInt();
    }
}

void QAbstractUsageTimeSource::save()
{
    // Write custom usage time & start count settings
    if(isManagerInitialized()) {
        manager()->settings()->setValue("Sources/" + id() + ".usageTime", d->currentUsageTime());
        manager()->settings()->setValue("Sources/" + id() + ".startCount", d->startCount);
        manager()->settings()->setValue("Sources/" + id() + "_using", d->using_);
        manager()->settings()->sync();
    }
}

void QAbstractUsageTimeSource::start()
{
    load();
    d->using_ = 1;
    d->startCount++;
}

void QAbstractUsageTimeSource::stop()
{
    d->usageTime = d->currentUsageTime();
    d->using_ = 0;
    save();
}

bool QAbstractUsageTimeSource::isUsing() const
{
    return d->using_;
}

}   // namespace QTelemetry
