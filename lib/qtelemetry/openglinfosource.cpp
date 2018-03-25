#include "openglinfosource.h"

#include <QVariant>

namespace QTelemetry {

OpenGLInfoSource::OpenGLInfoSource()
    : QAbstractDataSource("opengl", TelemetryLevel::DetailedSystemInformation)
{
}

QString OpenGLInfoSource::name() const
{
    return tr("OpenGL type and version");
}

QString OpenGLInfoSource::description() const
{
    return tr("OpenGL stack type, version and vendor.");
}

QVariant OpenGLInfoSource::data()
{
    QVariantMap m;
    return m;
}

}   // namespace QTelemetry
