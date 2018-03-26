﻿#include "screeninfosource.h"

#include <QVariant>
#include <QGuiApplication>
#include <QScreen>

namespace QTelemetry {

ScreenInfoSource::ScreenInfoSource()
    : QAbstractDataSource("screens", TelemetryLevel::DetailedSystemInformation)
{
}

QString ScreenInfoSource::name() const
{
    return tr("Screens size and resolution");
}

QString ScreenInfoSource::description() const
{
    return tr("Size and resolution of all connected screens.");
}

QVariant ScreenInfoSource::data()
{
    QVariantList l;
    foreach (auto screen, QGuiApplication::screens()) {
        QVariantMap m;
        m.insert(QStringLiteral("width"), screen->size().width());
        m.insert(QStringLiteral("height"), screen->size().height());
        m.insert(QStringLiteral("dpi"), qRound(screen->physicalDotsPerInch()));
        l.push_back(m);
    }
    return l;
}

}   // namespace QTelemetry