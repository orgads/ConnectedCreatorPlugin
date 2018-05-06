﻿#pragma once

#include "connectedcreatorplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace QTelemetry
{
    class QTelemetryManager;
    class QScheduler;
    class QNetworkManager;
}

namespace Core { class Command; }

namespace ConnectedCreator {
namespace Internal {

class ControlDialog;
class StatisticsDialog;

class ConnectedCreatorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ConnectedCreatorPlugin.json")

public:
    ConnectedCreatorPlugin();
    ~ConnectedCreatorPlugin();

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    bool delayedInitialize() override;
    ShutdownFlag aboutToShutdown() override;

    ControlDialog* controlDialog();
    StatisticsDialog* statisticsDialog();
    QTelemetry::QTelemetryManager* manager();
    QTelemetry::QScheduler* scheduler();
    QTelemetry::QNetworkManager* network();

private:
    void controlAction();
    void statisticsAction();
    void configureTelemetryManager();
    void configureScheduler();

    template <typename ConnectedCreatorFunction>
    Core::Command* addMenuAction(const QString &text,
                                 ConnectedCreatorFunction method,
                                 const char actionId[],
                                 const QKeySequence &sequence);

    QPointer<ControlDialog> m_controlDialog;
    QPointer<StatisticsDialog> m_statDialog;

    QTelemetry::QTelemetryManager *m_manager = nullptr;
    QTelemetry::QScheduler *m_scheduler = nullptr;
    QTelemetry::QNetworkManager *m_network = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin
