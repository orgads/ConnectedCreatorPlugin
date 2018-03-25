#include "connectedcreatorpluginplugin.h"
#include "connectedcreatorpluginconstants.h"
#include "controldialog.h"
#include "statisticsdialog.h"
#include "pluginsettings.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/settingsdatabase.h>
#include <coreplugin/designmode.h>

#include "qscheduler.h"
#include "qtelemetrymanager.h"
#include <AllSources>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QTimer>
#include <algorithm>

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
    Core::Command *cmd1 = addMenuAction(tr("&Control"),
                                        &ConnectedCreatorPlugin::controlAction,
                                        Constants::CONTROL_ACTION_ID,
                                        QKeySequence(tr("Ctrl+Alt+Meta+C")));

    Core::Command *cmd2 = addMenuAction(tr("View &Statistics"),
                                        &ConnectedCreatorPlugin::statisticsAction,
                                        Constants::STATISTICS_ACTION_ID,
                                        QKeySequence(tr("Ctrl+Alt+Meta+S")));

    // Add actions to ConnectedCreatorPlugin menu
    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("&Analytics"));
    menu->addAction(cmd1);
    menu->addAction(cmd2);

    // Add ConnectedCreatorPlugin menu to Qt Creator "Tools" menu
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

/// \brief Configure QTelemetry
void ConnectedCreatorPlugin::configureTelemetryManager()
{
    manager()->setProductIdentifier(QStringLiteral("io.qt.qtc.analytics"));
    // TODO: Create network object
    // ..

    // Create scheduler
    QTelemetry::QScheduler *scheduler = new QTelemetry::QScheduler(this);
    // Add submission task
    scheduler->addTask(7, QTelemetry::DurationMeasure::Days, [=]() {
        manager()->submit();
        // TODO: send data to backend
        // ...
    });

//    manager()->setSettingsDelay(30);
    manager()->setEnabled(PluginSettings::telemetryEnabled());

    // Add generic data sources
    manager()->addDataSource(new QTelemetry::ApplicationVersionSource);
    manager()->addDataSource(new QTelemetry::CompilerInfoSource);
    manager()->addDataSource(new QTelemetry::CpuInfoSource);
    manager()->addDataSource(new QTelemetry::LocaleInfoSource);
//    manager()->addDataSource(new QTelemetry::OpenGLInfoSource);
//    manager()->addDataSource(new QTelemetry::PlatformInfoSource);
//    manager()->addDataSource(new QTelemetry::QPAInfoSource);
//    manager()->addDataSource(new QTelemetry::QtVersionSource);
//    manager()->addDataSource(new QTelemetry::ScreenInfoSource);
//    manager()->addDataSource(new QTelemetry::StartCountSource);
//    manager()->addDataSource(new QTelemetry::StyleInfoSource);
//    manager()->addDataSource(new QTelemetry::UsageTimeSource);
    manager()->setTelemetryLevel(QTelemetry::TelemetryLevel::DetailedUsageStatistics);

    // Add Qt Creator specific data sources
    QList<QWidget *> widgets =  Core::DesignMode::instance()->findChildren<QWidget *>();
            // Core::ICore::mainWindow()->findChildren<QWidget *>();
    QList<QWidget *>::iterator it = std::find_if(widgets.begin(), widgets.end(),
        [](QWidget *widget) -> bool {
            return QString::fromLatin1(widget->metaObject()->className()) == "DesignModeWidget";
    });
    QWidget *designer = (it != widgets.end()) ? *it : nullptr;
    qDebug() << ((designer) ? designer->metaObject()->className() : "nullptr");

    // Connect Telemetry Manager to UI
    controlDialog()->setTelemetryManager(manager());
    statisticsDialog()->setTelemetryManager(manager());
}

/// \brief Helper function to create menu action
template <typename ConnectedCreatorFunction>
Core::Command* ConnectedCreatorPlugin::addMenuAction(const QString &text,
                                                     ConnectedCreatorFunction method,
                                                     const char actionId[],
                                                     const QKeySequence &sequence)
{
    auto action = new QAction(text, this);
    connect(action, &QAction::triggered, this, method);
    Core::Command *command = Core::ActionManager::registerAction(
                action, actionId, Core::Context(Core::Constants::C_GLOBAL));
    command->setDefaultKeySequence(sequence);

    return command;
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
    // Configure QTelemetry after all plugins initialized
    // to have all the objects available before configuration
    configureTelemetryManager();

    // Show telemetry control dialog to user on first run
    if(PluginSettings::firstStart()) {
        // The 1st time Control Dialog is opened 30 minutes after the start
        QTimer::singleShot(30*60*1000, this, &ConnectedCreatorPlugin:: controlAction);
    }

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

QTelemetry::QTelemetryManager* ConnectedCreatorPlugin::manager()
{
    if(!m_manager) {
        m_manager = new QTelemetry::QTelemetryManager(this);
    }
    return m_manager.data();
}

ControlDialog* ConnectedCreatorPlugin::controlDialog()
{
    if (!m_controlDialog) {
        m_controlDialog = new ControlDialog(Core::ICore::mainWindow());
    }
    return m_controlDialog.data();
}

StatisticsDialog* ConnectedCreatorPlugin::statisticsDialog()
{
    if (!m_statDialog) {
        m_statDialog = new StatisticsDialog(Core::ICore::mainWindow());
    }
    return m_statDialog.data();
}

void ConnectedCreatorPlugin::controlAction()
{
    controlDialog()->exec();
}

void ConnectedCreatorPlugin::statisticsAction()
{
    statisticsDialog()->exec();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
