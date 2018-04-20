#include "styleinfosource.h"

#include <QVariant>
#include <QApplication>
#include <QPalette>
#include <QStyle>
#include <QDebug>
#include <QWidget>

namespace QTelemetry {

StyleInfoSource::StyleInfoSource()
    : QAbstractDataSource("style", TelemetryLevel::DetailedSystemInformation)
{
}

QString StyleInfoSource::name() const
{
    return tr("Application widget style and color scheme");
}

QString StyleInfoSource::description() const
{
    return tr("The widget style used by the application, and information about the used color scheme.");
}

QVariant StyleInfoSource::data()
{
    QVariantMap m;  // JSON key-value pairs
    if (qApp && qApp->style()) {
        // QStyleFactory sets the object name to the style name
        QString style = (!qApp->style()->objectName().isEmpty()) ?
            qApp->style()->objectName() : qApp->style()->metaObject()->className();
        m.insert("style", style);

        //qDebug() << qApp->activeWindow()->styleSheet();
    }
    m.insert("dark", qApp->palette().color(QPalette::Background).lightness() < 128);
    return m;
}

}   // namespace QTelemetry
