#ifndef STARTCOUNTSOURCEPRIVATE_H
#define STARTCOUNTSOURCEPRIVATE_H

namespace QTelemetry {

class StartCountSource;

class StartCountSourcePrivate
{
public:
    StartCountSourcePrivate(StartCountSource *parent) : q(parent) {}
    int startCount = 0;

    StartCountSource *q;
};

}   // namespace QTelemetry

#endif // STARTCOUNTSOURCEPRIVATE_H
