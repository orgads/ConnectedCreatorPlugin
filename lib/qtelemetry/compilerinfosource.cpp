#include "compilerinfosource.h"

#include <QVariant>

namespace QTelemetry {


CompilerInfoSource::CompilerInfoSource()
    : QAbstractDataSource("compiler", TelemetryLevel::BasicSystemInformation)
{
}

QString CompilerInfoSource::name() const
{
    return tr("Compiler version source");
}

QString CompilerInfoSource::description() const
{
    return tr("The compiler used to build this application.");
}

#define STRINGIFY(x) #x
#define VER_STRING(major, minor, patch) \
    QString::fromLatin1(STRINGIFY(major) "." STRINGIFY(minor) "." STRINGIFY(patch))

QVariant CompilerInfoSource::data()
{
    QVariantMap m;

#ifdef Q_CC_GNU
    m.insert("type", "GCC");
    m.insert("version", VER_STRING(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__));
#endif

#ifdef Q_CC_CLANG
    m.insert("type", "Clang");
    m.insert("version", VER_STRING(__clang_major__, __clang_minor__, __clang_patchlevel__));
#endif

#ifdef Q_CC_MSVC
    m.insert("type", "MSVC");
    m.insert("version", QString::number(_MSC_VER));
#endif

    if (m.isEmpty())
        m.insert("type", "unknown");

    return m;
}


}   // namespace QTelemetry
