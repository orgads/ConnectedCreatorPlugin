﻿#ifndef QSCHEDULER_H
#define QSCHEDULER_H

#include "qtelemetry_global.h"

#include <functional>
#include <QObject>

namespace QTelemetry {

class QTaskPrivate;
class QSchedulerPrivate;

enum class DurationMeasure
{
    Minutes,
    Hours,
    Days,
    Weeks,
    Month
};

class QTask : public QObject {
    Q_OBJECT
public:
    explicit QTask(int duration, DurationMeasure type, std::function<void()> operation);

signals:

public slots:

private:
    QTaskPrivate *d;
};

class QScheduler : public QObject
{
    Q_OBJECT
public:
    explicit QScheduler(QObject *parent = nullptr);
    ~QScheduler();
    QTask& addTask(int duration, DurationMeasure measure,
                   std::function<void()> operation);

signals:

public slots:

private:
    QSchedulerPrivate *d;
};

}   // namespace QTelemetry

#endif // QSCHEDULER_H
