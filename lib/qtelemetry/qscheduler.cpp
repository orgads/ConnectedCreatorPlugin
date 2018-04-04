#include "qscheduler.h"
#include "qscheduler_p.h"

namespace QTelemetry {

QTask::QTask(FunctionType function, bool async)
    : QObject(nullptr)
    , d(new QTaskPrivate(this))
{
    d->async = async;
    d->function = function;
}

void QTask::setFunction(FunctionType function)
{
    d->function = function;
}

void QTask::setThreaded(bool async)
{
    d->async = async;
}

bool QTask::isThreaded() const
{
    return d->async;
}

void QTask::exec()
{
    if(d->function == nullptr)  return;

    if(!d->async) {
        emit started();
        d->function();
        emit finished();
    } else {
        execAsync();
    }
}

void QTask::execAsync()
{
    if(d->function == nullptr)  return;

    connect(&d->watcher, SIGNAL(started()), this, SIGNAL(started()));
    connect(&d->watcher, SIGNAL(finished()), this, SIGNAL(finished()));
    d->future = QtConcurrent::run(d->function);
    d->watcher.setFuture(d->future);
}

QScheduler::QScheduler(QObject *parent)
    : QObject(parent)
    , d(new QSchedulerPrivate(this))
{
}

QScheduler::~QScheduler()
{
    delete d;
}

QSchedulerPrivate::~QSchedulerPrivate()
{
    qDeleteAll(tasks);
}

QTask& QScheduler::addTask(int duration, DurationMeasure measure,
                           FunctionType operation)
{
    QTask *task = new QTask(operation, false);
    task->setParent(this);
    d->tasks.append(task);
    return *task;
}

}   // namespace QTelemetry
