#ifndef QSCHEDULER_H
#define QSCHEDULER_H

#include "qtelemetry_global.h"

#include <functional>
#include <QObject>

class QSettings;

namespace QTelemetry {

class QTaskPrivate;
class QSchedulerPrivate;

typedef std::function<void()> FunctionType;

enum class DurationMeasure
{
    Minutes,
    Hours,
    Days,
    Weeks,
    Month
};

///
/// \brief The QTask class helper class representing execution context for QScheduler
///
class QTask : public QObject {
    Q_OBJECT

public:
    /// \brief QTask Creates new task
    /// \param function
    /// \param async
    explicit QTask(FunctionType function = nullptr, bool async = false);

    /// Set execution function explicitly
    void setFunction(FunctionType function);

    /// Sets whether task should be executed in another thread (async)
    void setThreaded(bool async);
    /// Returns whether task is executed in another thread (async)
    bool isThreaded() const;

signals:
    /// Emits when task is started
    void started();
    /// Emits when task is finished
    void finished();

public slots:
    /// Run task according to its type: sync or async
    void exec();
    /// Force to run task in async mode (returns immediatelly)
    void execAsync();

private:
    QTaskPrivate *d;
};

///
/// \brief The QScheduler class
///
class QScheduler : public QObject
{
    Q_OBJECT
public:
    explicit QScheduler(QSettings *settings, QObject *parent = nullptr);
    ~QScheduler();

    /// \brief addTask Creates new task for periodic execution
    /// QScheduler takes ownership on the task and frees it on oject destroying
    /// \param name unique task name. If name is not uniquie task won't be added
    /// \param operation task function (or lambda expression)
    /// \param duration timer interval duration value
    /// \param measure timer interval duration measure @default DurationMeasure::Days
    /// \return
    QTask *addTask(const QString &name, FunctionType operation,
                   int duration, DurationMeasure measure = DurationMeasure::Minutes);
    /// Adds preliminary prepared task for periodic execution
    /// QScheduler takes ownership on the task and frees it on oject destroying
    void addTask(const QString &name, QTask *task,
                 int duration, DurationMeasure measure = DurationMeasure::Minutes);

    /// \brief addSingleShotTask Adds single time shot task
    /// QScheduler takes ownership on the task and frees it on oject destroying
    QTask* addSingleShotTask(const QString &name, FunctionType operation, QDateTime shotTime);
    /// \brief addSingleShotTask Adds single time shot task
    /// QScheduler takes ownership on the task and frees it on oject destroying
    QTask* addSingleShotTask(const QString &name, FunctionType operation,
                             int duration, DurationMeasure measure = DurationMeasure::Minutes);

    /// \brief task Retrieves taks for given @name
    /// \param name Task name
    /// \return task with given @name if found, nullptr otherwise
    QTask* task(const QString &name) const;

signals:

public slots:

private:
    QSchedulerPrivate *d;
};

}   // namespace QTelemetry

#endif // QSCHEDULER_H
