#ifndef CPUINFOSOURCE_H
#define CPUINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class CpuInfoSource : public QAbstractDataSource
{
public:
    CpuInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // CPUINFOSOURCE_H
