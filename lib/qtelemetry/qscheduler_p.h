#ifndef QSCHEDULERPRIVATE_H
#define QSCHEDULERPRIVATE_H

#include <QList>

namespace QTelemetry {

class QTask;
class QScheduler;

class QTaskPrivate
{
public:
    QTaskPrivate(QTask *parent) : q(parent) {}

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
