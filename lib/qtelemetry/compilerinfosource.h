#ifndef COMPILERINFOSOURCE_H
#define COMPILERINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

class QTELEMETRYSHARED_EXPORT CompilerInfoSource : public QAbstractDataSource
{
public:
    CompilerInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // COMPILERINFOSOURCE_H
