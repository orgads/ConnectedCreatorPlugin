#ifndef USAGETIMESOURCEPRIVATE_H
#define USAGETIMESOURCEPRIVATE_H

#include <QTime>

namespace QTelemetry {

class UsageTimeSource;

class UsageTimeSourcePrivate
{
public:
    UsageTimeSourcePrivate(UsageTimeSource *parent) : q(parent) {}
    int currentUsageTime() { return usageTime + (startTime.elapsed() / 1000); }
    int usageTime = 0;
    QTime startTime;

    UsageTimeSource *q;
};

}   // namespace QTelemetry

#endif // USAGETIMESOURCEPRIVATE_H
