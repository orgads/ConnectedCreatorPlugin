#include "connectedcreatorpluginplugin.h"
#include "connectedcreatorpluginconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

namespace ConnectedCreatorPlugin {
namespace Internal {

ConnectedCreatorPluginPlugin::ConnectedCreatorPluginPlugin()
{
    // Create your members
}

ConnectedCreatorPluginPlugin::~ConnectedCreatorPluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool ConnectedCreatorPluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    // Create plugin menu actions
    auto actControl = new QAction(tr("&Control"), this);
    connect(actControl, &QAction::triggered, this, &ConnectedCreatorPluginPlugin::controlAction);
    Core::Command *cmd1 = Core::ActionManager::registerAction(
                actControl, Constants::CONTROL_ACTION_ID,
                Core::Context(Core::Constants::C_GLOBAL));
    cmd1->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+C")));

    auto actStatistics = new QAction(tr("View &Statistics"), this);
    connect(actStatistics, &QAction::triggered, this, &ConnectedCreatorPluginPlugin::statisticsAction);
    Core::Command *cmd2 = Core::ActionManager::registerAction(
                actStatistics, Constants::STATISTICS_ACTION_ID,
                Core::Context(Core::Constants::C_GLOBAL));
    cmd2->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+S")));

    // Add actions to ConnectedCreatorPlugin menu
    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("&Analytics"));
    menu->addAction(cmd1);
    menu->addAction(cmd2);

    // Add ConnectedCreatorPlugin menu to Qt Creator "Tools" menu
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

void ConnectedCreatorPluginPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag ConnectedCreatorPluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void ConnectedCreatorPluginPlugin::controlAction()
{
    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action Triggered"),
                             tr("This is an action from ConnectedCreatorPlugin."));
}

void ConnectedCreatorPluginPlugin::statisticsAction()
{
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
