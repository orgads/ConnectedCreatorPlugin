#ifndef QTELEMETRYMANAGERPRIVATE_H
#define QTELEMETRYMANAGERPRIVATE_H

#include "qtelemetrymanager.h"

#include <QPointer>
#include <QList>
#include <QMap>
#include <QSettings>
#include <QCoreApplication>

namespace QTelemetry {

class QTelemetryManager;
class QAbstractDataSource;

class QTelemetryManagerPrivate
{
public:
    QTelemetryManagerPrivate(QTelemetryManager *manager) : q(manager) {}
    ~QTelemetryManagerPrivate();
    void createSettings();
    bool isValidSource(QAbstractDataSource *source) const;

    QList<QAbstractDataSource *> sources;
    QMap<QString, int> index;
    QPointer<QSettings> settings;
    QString productId = QCoreApplication::applicationName();

    TelemetryLevel level = TelemetryLevel::NoTelemetry;

    QTelemetryManager *q;
    QString organization();
};

}   // namespace QTelemetry

#endif // QTELEMETRYMANAGERPRIVATE_H
