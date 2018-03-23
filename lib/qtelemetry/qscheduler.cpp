#include "qscheduler.h"
#include "qscheduler_p.h"

namespace QTelemetry {

QScheduler::QScheduler(QObject *parent) : QObject(parent)
{

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
