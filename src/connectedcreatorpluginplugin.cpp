#include "connectedcreatorpluginplugin.h"
#include "connectedcreatorpluginconstants.h"
#include "controldialog.h"
#include "statisticsdialog.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/settingsdatabase.h>

#include <kuserfeedback/core/provider.h>
#include <kuserfeedback/widgets/notificationpopup.h>
#include <kuserfeedback/widgets/feedbackconfigdialog.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

namespace ConnectedCreator {
namespace Internal {

ConnectedCreatorPlugin::ConnectedCreatorPlugin()
{
    // Create your members
}

ConnectedCreatorPlugin::~ConnectedCreatorPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool ConnectedCreatorPlugin::initialize(const QStringList &arguments, QString *errorString)
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
    connect(actControl, &QAction::triggered, this, &ConnectedCreatorPlugin::controlAction);
    Core::Command *cmd1 = Core::ActionManager::registerAction(
                actControl, Constants::CONTROL_ACTION_ID,
                Core::Context(Core::Constants::C_GLOBAL));
    cmd1->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+C")));

    auto actStatistics = new QAction(tr("View &Statistics"), this);
    connect(actStatistics, &QAction::triggered, this, &ConnectedCreatorPlugin::statisticsAction);
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

void ConnectedCreatorPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

/**
 * @brief ConnectedCreatorPlugin::delayedInitialize
 * Called after all plugins' IPlugin::extensionsInitialized() function has been
 * called, and after the IPlugin::delayedInitialize() function of plugins that
 * depend on this plugin have been called.
 * @return
 */
bool ConnectedCreatorPlugin::delayedInitialize()
{
    // Show telemetry control dialog to user on first run
    auto settings = Core::ICore::settingsDatabase();
    if(settings->value(Constants::FIRST_RUN_KEY, true).value<bool>())
        controlAction();

    // Plugin should return true from the function if itactually implements delayedInitialize()
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag ConnectedCreatorPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

// Create a non-modal dialog with refresh function or raise if it exists
template <class NonModalDialog>
inline void showNonModalDialog(QPointer<NonModalDialog> &dialog)
{
    if (dialog) {
        dialog->exec();
        dialog->raise();
    } else {
        dialog = new NonModalDialog(Core::ICore::mainWindow());
        dialog->exec();
    }
}

void ConnectedCreatorPlugin::controlAction()
{
    showNonModalDialog(m_controlDialog);
}

void ConnectedCreatorPlugin::statisticsAction()
{
    showNonModalDialog(m_statDialog);
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
