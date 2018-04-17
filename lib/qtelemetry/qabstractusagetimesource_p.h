#ifndef QABSTRACTUSAGETIMESOURCE_P_H
#define QABSTRACTUSAGETIMESOURCE_P_H

#include <QTime>

namespace QTelemetry {

class QAbstractUsageTimeSource;

class QAbstractUsageTimeSourcePrivate
{
public:
    QAbstractUsageTimeSourcePrivate(QAbstractUsageTimeSource *parent)
        : q(parent) {}

    int currentUsageTime() {
        return usageTime + using_ * (startTime.elapsed() / 1000);
    }

    int usageTime = 0,
        startCount = 0;
    int using_ = 0;    // Possible values 0/1

    QTime startTime;

    QAbstractUsageTimeSource *q;
};

}   // namespace QTelemetry

#endif // QABSTRACTUSAGETIMESOURCE_P_H
