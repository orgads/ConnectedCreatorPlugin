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
        return usageTime + running * (startTime.elapsed() / 1000);
    }

    int usageTime = 0;
    QTime startTime;
    int running = 0;    // Possible values 0/1

    QAbstractUsageTimeSource *q;
};

}   // namespace QTelemetry

#endif // QABSTRACTUSAGETIMESOURCE_P_H
