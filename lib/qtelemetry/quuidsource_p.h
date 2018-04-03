#ifndef QUUIDSOURCEPRIVATE_H
#define QUUIDSOURCEPRIVATE_H

#include <QUuid>

namespace QTelemetry {

class QUuidSource;

class QUuidSourcePrivate
{
public:
    QUuidSourcePrivate(QUuidSource *parent) : q(parent) {}
    QUuid uuid;

    QUuidSource *q;
};

}   // namespace QTelemetry

#endif // QUUIDSOURCEPRIVATE_H
