#include "startcountsource.h"
#include "startcountsource_p.h"

#include <QVariant>
#include <QSettings>

namespace QTelemetry {

StartCountSource::StartCountSource()
    : QAbstractDataSource("startCount", TelemetryLevel::BasicUsageStatistics)
    , d(new StartCountSourcePrivate(this))
{
    // Load settings on manager initialization
    connect(this, &StartCountSource::managerChanged, this, &StartCountSource::load);
}

StartCountSource::~StartCountSource()
{
    save();
    delete d;
}

QString StartCountSource::name() const
{
    return tr("Application start count");
}

QString StartCountSource::description() const
{
    return tr("How often the application has been started.");
}

QVariant StartCountSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("value", d->startCount);
    return m;
}

void StartCountSource::reset()
{
    d->startCount = 0;
    save();
}

void StartCountSource::load()
{
    if(isManagerInitialized()) {
        d->startCount = manager()->settings()->value("Telemetry/startCount", 0).toInt();
        d->startCount++;
    }
}

void StartCountSource::save()
{
    // Write startCount settings
    manager()->settings()->setValue("Telemetry/startCount", d->startCount);
    manager()->settings()->sync();
}

}   // namespace QTelemetry
