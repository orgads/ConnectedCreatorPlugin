#include "qmldesignerusagetimesource.h"

#include <QFileInfo>
#include <QDebug>

QmlDesignerUsageTimeSource::QmlDesignerUsageTimeSource()
    : QTelemetry::QAbstractUsageTimeSource("qmlDesigner")
{
    connect(Core::ModeManager::instance(), &Core::ModeManager::currentModeChanged,
            this, &QmlDesignerUsageTimeSource::timerControl);
}

QString QmlDesignerUsageTimeSource::name() const
{
    return tr("QmlDesigner usage time");
}

QString QmlDesignerUsageTimeSource::description() const
{
    return tr("QmlDesigner total usage time in seconds");
}

void QmlDesignerUsageTimeSource::timerControl(Core::Id mode)
{
    bool isDesignMode = mode.name().toLower() == "design";
    if(isDesignMode == isUsing())   // mode was not changed
        return;                     // do nothing

    if(isDesignMode) {
        QString mime = Core::EditorManager::currentDocument()->mimeType().toLower();
        QString extension = Core::EditorManager::currentDocument()->filePath()
                .toFileInfo().completeSuffix().toLower();

        if(extension == "qml" || extension == "qml.ui" || mime.contains("qml")) {
            emit started();
        }
    } else { // !design
        emit stopped();
    }
}
