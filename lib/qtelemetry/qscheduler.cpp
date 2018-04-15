#include "qscheduler.h"
#include "qscheduler_p.h"
#include "qtelemetry_logging.h"

#include <QSettings>
#include <limits>

namespace QTelemetry {

QTask::QTask(FunctionType function, bool async)
    : QObject(nullptr)
    , d(new QTaskPrivate(this))
{
    d->async = async;
    d->function = function;

    connect(&d->watcher, SIGNAL(started()), this, SIGNAL(started()));
    connect(&d->watcher, SIGNAL(finished()), this, SIGNAL(finished()));
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

    d->future = QtConcurrent::run(d->function);
    d->watcher.setFuture(d->future);
}

QScheduler::QScheduler(QSettings *settings, QObject *parent)
    : QObject(parent)
    , d(new QSchedulerPrivate(this))
{
    d->settings = settings;
}

QScheduler::~QScheduler()
{
    delete d;
}

QSchedulerPrivate::QSchedulerPrivate(QScheduler *parent)
    : q(parent)
    , timer(new QTimer(parent))
{
    connect(timer, &QTimer::timeout, this, &QSchedulerPrivate::execTask);
}

QSchedulerPrivate::~QSchedulerPrivate()
{
    timer->stop();
    save();
}

void QSchedulerPrivate::save()
{
    foreach (auto info, tasks) {
        settings->setValue("Timers/" + info->name, info->nextShot);
    }
    settings->sync();
}

QTask* QScheduler::addTask(const QString &name, FunctionType operation,
                           int duration, DurationMeasure measure)
{
    if(d->taskCouldBeAdded(name)) {
        QTask *task = new QTask(operation, false);
        addTask(name, task, duration, measure);
        return task;
    } else {
        return nullptr;
    }
}

void QScheduler::addTask(const QString &name, QTask *task,
                         int duration, DurationMeasure measure)
{
    if(!d->taskCouldBeAdded(name)) return;

    task->setParent(this);
    // Create TimerInfo and fill its parameters
    TimerInfoPointer timerInfo = TimerInfoPointer(new TimerInfo());
    timerInfo->name = name;
    timerInfo->duration = duration;
    timerInfo->measure = measure;
    timerInfo->task = QSharedPointer<QTask>(task);

    // Read timer settings
    timerInfo->nextShot = d->settings->value("Timers/" + name, QDateTime()).toDateTime();
    if(!timerInfo->nextShot.isValid())  // First start
        timerInfo->calcNextShot(QDateTime::currentDateTime());

    // Execute task if schedule time passed
    if(timerInfo->nextShot < QDateTime::currentDateTime()) {
        task->exec();
        timerInfo->calcNextShot(timerInfo->nextShot);
    }

    // Add task to queue
    d->tasks.insert(name, timerInfo);
    d->queue.insert(timerInfo->nextShot, timerInfo);

    d->scheduleNextShot();
}

void QSchedulerPrivate::scheduleNextShot()
{
    timer->stop();

    QDateTime nextShot = queue[queue.uniqueKeys()[0]]->nextShot;
    QDateTime now = QDateTime::currentDateTime();
    qint64 period = std::min((qint64)std::numeric_limits<int>::max(), now.msecsTo(nextShot));
    period = (period < 0) ? 1 : period; // Protect from negative values

    timer->start(period);
}

void QSchedulerPrivate::execTask()
{
    // Take first task from the queue
    QDateTime firstDateTime = queue.uniqueKeys()[0];

    // Check for big timers > 24 days (REMOVE: for qint64)
    if(firstDateTime <= QDateTime::currentDateTime()) {
        TimerInfoPointer info = queue.take(firstDateTime);
        // Execute task
        info->task->exec();

        // For periodic task ...
        if(info->isPeriodic) {
            // Calculate next task timer shot
            info->calcNextShot(info->nextShot);
            // Reinsert timer into the queue
            queue.insert(info->nextShot, info);
        }
    }
    scheduleNextShot();
}

QTask* QScheduler::task(const QString &name) const
{
    if(!d->isTaskExists(name)) {
        qCWarning(Log) << "Task '" << name << "' does not exist!";
        return nullptr;
    }

    return d->tasks[name]->task.data();
}

bool QSchedulerPrivate::isTaskExists(const QString &name)
{
    return tasks.contains(name);
}

bool QSchedulerPrivate::taskCouldBeAdded(const QString &name)
{
    if(isTaskExists(name)) {
        qCWarning(Log) << "Task was not added! Task '" << name << "' already exists!";
        return false;
    } else {
        return true;
    }
}

void TimerInfo::calcNextShot(QDateTime startDate)
{
    switch (measure) {
    default:
    case DurationMeasure::Minutes:
        nextShot = startDate.addSecs(duration * 60);
        break;
    case DurationMeasure::Hours:
        nextShot = startDate.addSecs(duration * 3600);
        break;
    case DurationMeasure::Days:
        nextShot = startDate.addDays(duration);
        break;
    case DurationMeasure::Month:
        nextShot = startDate.addMonths(duration);
        break;
    case DurationMeasure::Weeks:
        nextShot = startDate.addDays(duration * 7);
        break;
    }
}

}   // namespace QTelemetry
