#include "qscheduler.h"
#include "qscheduler_p.h"

namespace QTelemetry {

QScheduler::QScheduler(QObject *parent)
    : QObject(parent)
    , d(new QSchedulerPrivate(this))
{
}

QTask::QTask(int duration, DurationMeasure type, std::function<void()> operation)
    : QObject(nullptr)
    , d(new QTaskPrivate(this))
{
    Q_UNUSED(duration)
    Q_UNUSED(type)
    Q_UNUSED(operation)
}

QTask& QScheduler::addTask(int duration, DurationMeasure measure,
                           std::function<void()> operation)
{
    QTask *task = new QTask(duration, measure, operation);
    task->setParent(this);
    d->tasks.append(task);
    return *task;
}

}   // namespace QTelemetry
