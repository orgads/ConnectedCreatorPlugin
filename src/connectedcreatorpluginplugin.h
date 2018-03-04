#pragma once

#include "connectedcreatorplugin_global.h"

#include <extensionsystem/iplugin.h>

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
    ShutdownFlag aboutToShutdown();

private:
    void controlAction();
    void statisticsAction();

    QPointer<ControlDialog> m_controlDialog;
    QPointer<StatisticsDialog> m_statDialog;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin
