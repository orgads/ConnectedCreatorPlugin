#ifndef QMLDESIGNERUSAGETIMESOURCE_H
#define QMLDESIGNERUSAGETIMESOURCE_H

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/modemanager.h>

#include "qabstractusagetimesource.h"

/// Data source reports QmlDesigner usage time in seconds.
///
/// The default telemetry level for this source is TelemetryLevel::DetailedUsageStatistics.
///
class QmlDesignerUsageTimeSource : public QTelemetry::QAbstractUsageTimeSource
{
public:
    QmlDesignerUsageTimeSource();

    QString name() const override;
    QString description() const override;

protected slots:
    void timerControl(Core::Id mode);
};

#endif // QMLDESIGNERUSAGETIMESOURCE_H
