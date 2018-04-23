#ifndef STATISTICSMODELPRIVATE_H
#define STATISTICSMODELPRIVATE_H

#include "qtelemetrymanager.h"

#include <QObject>
#include <QFileSystemWatcher>
#include <QList>

namespace QTelemetry {

class StatisticsModel;
class QTelemetryManager;

class StatisticsModelPrivate : public QObject
{
public:
    StatisticsModelPrivate(StatisticsModel *parent);
    QFileSystemWatcher logWatcher;

    QList<QString> items;
    /// Log file content for given model row (datetime)
    QJsonDocument logFileContent(int row);
    /// Returns whether log was sent to backend
    bool isTransferred(const QJsonDocument &doc) const;
    /// Filter JSON according to current model telemetry level
    QJsonDocument filterContent(const QJsonDocument &content);

    QTelemetryManager *manager;
    TelemetryLevel telemetryLevel;
    StatisticsModel *q;
};

}   // namespace QTelemetry

#endif // STATISTICSMODELPRIVATE_H
