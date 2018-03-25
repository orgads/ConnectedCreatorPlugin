#include "localeinfosource.h"

#include <QVariant>
#include <QLocale>

namespace QTelemetry {

LocaleInfoSource::LocaleInfoSource()
    : QAbstractDataSource("locale", TelemetryLevel::DetailedSystemInformation)
{
}

QString LocaleInfoSource::name() const
{
    return tr("Region and language settings");
}

QString LocaleInfoSource::description() const
{
    return tr("Current region and language settings set in application.");
}

QVariant LocaleInfoSource::data()
{
    QLocale l;
    QVariantMap m;
    m.insert(QStringLiteral("region"), QLocale::countryToString(l.country()));
    m.insert(QStringLiteral("language"), QLocale::languageToString(l.language()));
    return m;
}

}   // namespace QTelemetry
