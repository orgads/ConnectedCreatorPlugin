#include "qmldesignerusagetimesource.h"

#include <QFileInfo>
#include <QDebug>

QmlDesignerUsageTimeSource::QmlDesignerUsageTimeSource()
    : QTelemetry::QAbstractUsageTimeSource("qmlDesignerUsageTime")
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
    bool design = mode.name().toLower() == "design";
    if(design == isUsing()) // mode was not changed
        return;             // do nothing
    else if(design) {
        QString extension = Core::EditorManager::currentDocument()->filePath()
                .toFileInfo().completeSuffix().toLower();
        if(extension == "qml" || extension == "qml.ui") {
            emit started();
        }
    } else { // !design
        emit stopped();
    }
}
