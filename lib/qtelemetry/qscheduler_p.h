#ifndef QSCHEDULERPRIVATE_H
#define QSCHEDULERPRIVATE_H

#include "qscheduler.h"

#include <QList>
#include <QtConcurrent/QtConcurrent>

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

class QSchedulerPrivate
{
public:
    QSchedulerPrivate(QScheduler *parent) : q(parent) {}
    ~QSchedulerPrivate();

    QList<QTask *> tasks;

    QScheduler *q;
};

}   // namespace QTelemetry


#endif // QSCHEDULERPRIVATE_H
