#pragma once

#include "connectedcreatorplugin_global.h"

#include <extensionsystem/iplugin.h>

class ControlDialog;
class StatisticsDialog;

namespace ConnectedCreatorPlugin {
namespace Internal {

class ConnectedCreatorPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ConnectedCreatorPlugin.json")

public:
    ConnectedCreatorPluginPlugin();
    ~ConnectedCreatorPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    void controlAction();
    void statisticsAction();

    QPointer<ControlDialog> m_controlDialog;
    QPointer<StatisticsDialog> m_statDialog;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin
