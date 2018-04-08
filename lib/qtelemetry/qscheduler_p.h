#ifndef QSCHEDULERPRIVATE_H
#define QSCHEDULERPRIVATE_H

#include "qscheduler.h"

#include <QMap>
#include <QSharedPointer>
#include <QtConcurrent/QtConcurrent>

class QSettings;

namespace QTelemetry {

class QTask;
class QScheduler;

class QTaskPrivate
{
public:
    QTaskPrivate(QTask *parent) : q(parent) {}

    FunctionType function;
    bool async;

    QFuture<void> future;
    QFutureWatcher<void> watcher;

    QTask *q;
};

/// Timer info data struct
struct TimerInfo {
    QString name;       /// Timer name
    int duration = 0;
    DurationMeasure measure = DurationMeasure::Minutes;
    bool isPeriodic = true;
    QSharedPointer<QTask> task;
    QDateTime nextShot;

    void calcNextShot(QDateTime startDate);
};

typedef QSharedPointer<TimerInfo> TimerInfoPointer;

class QSchedulerPrivate : public QObject
{
    Q_OBJECT
public:
    QSchedulerPrivate(QScheduler *parent);
    ~QSchedulerPrivate();

    bool isTaskExists(const QString &name);
    bool taskCouldBeAdded(const QString &name);

    void scheduleNextShot();
    void execTask();
    void save(); // Saves timers state

    QScheduler *q;
    QTimer *timer;   // Scheduler timer
    QSettings *settings;

    QMap<QString, TimerInfoPointer> tasks;      // Tasks list
    QMap<QDateTime, TimerInfoPointer> queue;    // Tasks queue ordered by time
};

}   // namespace QTelemetry


#endif // QSCHEDULERPRIVATE_H
