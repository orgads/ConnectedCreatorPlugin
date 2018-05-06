#ifndef QTELEMETRYMANAGERPRIVATE_H
#define QTELEMETRYMANAGERPRIVATE_H

#include "qtelemetrymanager.h"

#include <QPointer>
#include <QList>
#include <QMap>
#include <QSettings>
#include <QCoreApplication>
#include <QDateTime>

class QAbstractItemModel;

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
    QDateTime writeStatistics(const QJsonDocument &data);

    QList<QAbstractDataSource *> sources;
    QMap<QString, int> index;
    QPointer<QSettings> settings;
    QString productId = QCoreApplication::applicationName();

    TelemetryLevel level = TelemetryLevel::NoTelemetry;

    QAbstractItemModel *model;
    QTelemetryManager *q;
    QString organization();
};

}   // namespace QTelemetry

#endif // QTELEMETRYMANAGERPRIVATE_H
