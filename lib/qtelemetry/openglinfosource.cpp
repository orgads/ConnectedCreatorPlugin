#include "openglinfosource.h"

#include <QVariant>
#include <QWindow>
#include <QSurface>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>

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
    QOpenGLContext context;
    if(context.create()) {
        // Initialize OpenGL Functions to get the info
        QWindow window;
        window.setSurfaceType(QSurface::OpenGLSurface);
        window.create();
        context.makeCurrent(&window);
        QOpenGLFunctions funcs(&context);

        QString type = (context.openGLModuleType() == QOpenGLContext::LibGL) ?
                        "GL" : "GLES";
        QString vendorVersion = (const char*)funcs.glGetString(GL_VERSION);
        QString version = vendorVersion.split(" ")[0];
        m.insert("version", version);
        m.insert("type", type);
        m.insert("vendor", (const char*)funcs.glGetString(GL_VENDOR));
        m.insert("vendorVersion", vendorVersion.mid(version.length() + 1));
        m.insert("renderer", (const char*)funcs.glGetString(GL_RENDERER));
        m.insert("glslVersion", (const char*)funcs.glGetString(GL_SHADING_LANGUAGE_VERSION));
        //m.insert("extensions", (const char*)funcs.glGetString(GL_EXTENSIONS));
    } else {
        m.insert("type", "none");
    }
    return m;
}

}   // namespace QTelemetry
