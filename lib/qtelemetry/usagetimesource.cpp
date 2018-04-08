#include "usagetimesource.h"
#include "usagetimesource_p.h"

#include <QVariant>
#include <QSettings>

namespace QTelemetry {

UsageTimeSource::UsageTimeSource()
    : QAbstractDataSource("usageTime", TelemetryLevel::BasicUsageStatistics)
    , d(new UsageTimeSourcePrivate(this))
{
}

UsageTimeSource::~UsageTimeSource()
{
    save();
    delete d;
}

QString UsageTimeSource::name() const
{
    return tr("Application usage time");
}

QString UsageTimeSource::description() const
{
    return tr("Total application usage time in seconds.");
}

QVariant UsageTimeSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("value", d->currentUsageTime());
    return m;
}

void UsageTimeSource::reset()
{
    d->usageTime = 0;
    d->startTime.restart();
    save();
}

void UsageTimeSource::load()
{
    if(isManagerInitialized()) {
        d->startTime.start();
        d->usageTime = manager()->settings()->value("Sources/usageTime", 0).toInt();
    }
}

void UsageTimeSource::save()
{
    // Write usageTime settings
    manager()->settings()->setValue("Sources/usageTime", d->currentUsageTime());
    manager()->settings()->sync();
}

}   // namespace QTelemetry
