#ifndef COMPILERINFOSOURCE_H
#define COMPILERINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source reporting which compiler was used to build this code. Matches to
/// application compiller if built with same compiler.
///
/// The default telemetry mode for this source is TelemetryLevel::BasicSystemInformation.
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
