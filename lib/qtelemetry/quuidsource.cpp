#include "quuidsource.h"
#include "quuidsource_p.h"

#include <QVariant>
#include <QSettings>

namespace QTelemetry {

QUuidSource::QUuidSource()
    : QAbstractDataSource("uuid", TelemetryLevel::DetailedSystemInformation)
    , d(new QUuidSourcePrivate(this))
{
}

QUuidSource::~QUuidSource()
{
    save();
    delete d;
}

QString QUuidSource::name() const
{
    return tr("Unique machine ID");
}

QString QUuidSource::description() const
{
    return tr("Randommly generated unique machine ID.");
}

QVariant QUuidSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    m.insert("value", d->uuid.toString().mid(1).chopped(1));
    return m;
}

void QUuidSource::load()
{
    if(isManagerInitialized()) {
        d->uuid = manager()->settings()->value("Telemetry/uuid", QUuid()).toUuid();
        if(d->uuid.isNull()) {  // On first start
            d->uuid = QUuid::createUuid();
        }
    }
}

void QUuidSource::save()
{
    // Write startCount settings
    manager()->settings()->setValue("Telemetry/uuid", d->uuid);
    manager()->settings()->sync();
}

}   // namespace QTelemetry
