#ifndef QSCHEDULER_H
#define QSCHEDULER_H

#include "qtelemetry_global.h"

#include <functional>
#include <QObject>

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

/// Helper class representing execution context for QScheduler
class QTask : public QObject {
    Q_OBJECT

public:
    /// Creates new task
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

class QScheduler : public QObject
{
    Q_OBJECT
public:
    explicit QScheduler(QObject *parent = nullptr);
    ~QScheduler();
    QTask& addTask(int duration, DurationMeasure measure, FunctionType operation);
    QTask& addTask(QDateTime shotTime, FunctionType operation);

signals:

public slots:

private:
    QSchedulerPrivate *d;
};

}   // namespace QTelemetry

#endif // QSCHEDULER_H
