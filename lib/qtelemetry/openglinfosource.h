#ifndef OPENGLINFOSOURCE_H
#define OPENGLINFOSOURCE_H

#include "qtelemetry_global.h"
#include "abstractdatasource.h"

namespace QTelemetry {

/// Data source reports type, version and vendor of the OpenGL stack.
///
/// The default telemetry level for this source is TelemetryLevel::DetailedSystemInformation.
///
class OpenGLInfoSource : public QAbstractDataSource
{
public:
    OpenGLInfoSource();
    QString name() const override;
    QString description() const override;
    QVariant data() override;
};

}   // namespace QTelemetry

#endif // OPENGLINFOSOURCE_H
