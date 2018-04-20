#ifndef STATISTICSMODELPRIVATE_H
#define STATISTICSMODELPRIVATE_H

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
    QJsonDocument logFileContent(int row);
    bool isTransferred(const QJsonDocument &doc) const;

    QTelemetryManager *manager;
    StatisticsModel *q;
};

}   // namespace QTelemetry

#endif // STATISTICSMODELPRIVATE_H
