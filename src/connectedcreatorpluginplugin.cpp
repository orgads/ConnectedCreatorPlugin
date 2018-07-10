#include "connectedcreatorpluginplugin.h"
#include "connectedcreatorpluginconstants.h"
#include "telemetrydialog.h"
#include "settingsdialog.h"
#include "datasourcesdialog.h"
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

#include "qtelemetrymanager.h"
#include "qscheduler.h"
#include "qnetworkmanager.h"
#include <AllSources>
#include "qmldesignerusagetimesource.h"
#include "qtclicensesource.h"
#include "qtelemetry_logging.h"
#include <statisticsmodel.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QTimer>
#include <QDateTime>
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
    delete m_scheduler; // Delete scheduler first as manager contains settings
    delete m_manager;
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
    Core::Command *cmd = addMenuAction(tr("&Options"),
                                        &ConnectedCreatorPlugin::telemetryAction,
                                        Constants::TELEMETRY_ACTION_ID,
                                        QKeySequence(tr("Ctrl+Alt+Meta+T")));

//    Core::Command *cmd1 = addMenuAction(tr("&Options"),
//                                        &ConnectedCreatorPlugin::settingsAction,
//                                        Constants::SETTINGS_ACTION_ID,
//                                        QKeySequence(tr("Ctrl+Alt+Meta+O")));

//    Core::Command *cmd2 = addMenuAction(tr("&Data Sources"),
//                                        &ConnectedCreatorPlugin::dataSourcesAction,
//                                        Constants::DATASOURCES_ACTION_ID,
//                                        QKeySequence(tr("Ctrl+Alt+Meta+D")));

//    Core::Command *cmd3 = addMenuAction(tr("View &Statistics"),
//                                        &ConnectedCreatorPlugin::statisticsAction,
//                                        Constants::STATISTICS_ACTION_ID,
//                                        QKeySequence(tr("Ctrl+Alt+Meta+S")));

    // Add actions to ConnectedCreatorPlugin menu
    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("&Telemetry"));
    menu->addAction(cmd);
//    menu->addAction(cmd1);
//    menu->addAction(cmd2);
//    menu->addAction(cmd3);

    // Add ConnectedCreatorPlugin menu to Qt Creator "Tools" menu
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

/// \brief Configure QTelemetry
void ConnectedCreatorPlugin::configureTelemetryManager()
{
    // Create and init telemetry manager
    manager()->setProductIdentifier("io.qt.qtc.telemetry");
    // Set Telemetry Level
    manager()->setTelemetryLevel(QTelemetry::TelemetryLevel::CustomUsageStatistics);

//    manager()->setSettingsDelay(30);
    manager()->setEnabled(PluginSettings::telemetryEnabled());

    // Add generic data sources
    manager()->addDataSource(new QTelemetry::ApplicationVersionSource);
    manager()->addDataSource(new QTelemetry::CompilerInfoSource);
    manager()->addDataSource(new QTelemetry::CpuInfoSource);
    manager()->addDataSource(new QTelemetry::LocaleInfoSource);
    manager()->addDataSource(new QTelemetry::OpenGLInfoSource);
    manager()->addDataSource(new QTelemetry::PlatformInfoSource);
    manager()->addDataSource(new QTelemetry::QPAInfoSource);
    manager()->addDataSource(new QTelemetry::QtVersionSource);
    manager()->addDataSource(new QTelemetry::ScreenInfoSource);
    manager()->addDataSource(new QTelemetry::StartCountSource);
    //manager()->addDataSource(new QTelemetry::StyleInfoSource);
    manager()->addDataSource(new QTelemetry::UsageTimeSource);
    manager()->addDataSource(new QTelemetry::QUuidSource);

    // Add Qt Creator specific data sources
    manager()->addDataSource(new QmlDesignerUsageTimeSource);
    manager()->addDataSource(new QtcLicenseSource);

    // Connect Telemetry Manager to UI
    telemetryDialog()->setTelemetryManager(manager());
//    settingsDialog()->setTelemetryManager(manager());
//    dataSourcesDialog()->setTelemetryManager(manager());
//    statisticsDialog()->setTelemetryManager(manager());
}

void ConnectedCreatorPlugin::configureScheduler()
{
    // Create scheduler and add submission task to it
    scheduler()->addTask("SubmitData", [=]() {
        network()->sendData();
        qCInfo(QTelemetry::Log) << QDateTime::currentDateTime().toString(Qt::ISODate)
                                << ": SubmitData Task executed...";
    }, 7, QTelemetry::DurationMeasure::Minutes);

    // Add task to delete expired logs
    scheduler()->addTask("DeleteExpiredLogs", [=]() {
        int expire = PluginSettings::expirePeriod();
        QTelemetry::StatisticsModel *model =
                (QTelemetry::StatisticsModel *)m_manager->statisticsModel();
        // expire == -1 - do nothing - never expires
        if(expire == 0) {
            // Delete all transferred files before current date time
            model->clearCache();
        } else if(expire > 0) {
            // Delete all transferred files after 'expire' days period
            QDateTime date = QDateTime::currentDateTimeUtc().addDays(-expire);
            model->clearCache(date);
        }
        qCInfo(QTelemetry::Log) << QDateTime::currentDateTime().toString(Qt::ISODate)
                                << ": DeleteExpiredLogs Task executed...";
    }, 1, QTelemetry::DurationMeasure::Days);

    // Add task to send left behind logs

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
void ConnectedCreatorPlugin::configureNetwork()
{
    // Get backend URL
    QString url = !QString(TELEMETRY_BACKEND_URL).isEmpty()
            ? QString(TELEMETRY_BACKEND_URL) : QString("http://localhost:3000/telemetry");
    // Create and init network manager
    network()->setBackend(url);
}

bool ConnectedCreatorPlugin::delayedInitialize()
{
    // Configure QTelemetry after all plugins initialized
    // to have all the objects available before configuration
    configureTelemetryManager();

    configureNetwork();

    // NOTE. Init scheduler after telemetry manager and all the data sources
    // to prevent sending empty statistics
    configureScheduler();

    // Show telemetry control dialog to user on first run
//    if(PluginSettings::firstStart()) {
//        // The 1st time Control Dialog is opened 30 minutes after the start
//        QTimer::singleShot(30*60*1000, this, &ConnectedCreatorPlugin:: dataSourcesAction);
//    }

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
    return m_manager;
}

QTelemetry::QScheduler* ConnectedCreatorPlugin::scheduler()
{
    if(!m_scheduler) {
        m_scheduler = new QTelemetry::QScheduler(manager(), this);
    }
    return m_scheduler;
}

QTelemetry::QNetworkManager* ConnectedCreatorPlugin::network()
{
    if(!m_network) {
        m_network = new QTelemetry::QNetworkManager(manager());
    }
    return m_network;
}

SettingsDialog* ConnectedCreatorPlugin::settingsDialog()
{
    if(!m_settingsDialog) {
        m_settingsDialog = new SettingsDialog(Core::ICore::mainWindow());
    }
    return m_settingsDialog.data();
}

TelemetryDialog* ConnectedCreatorPlugin::telemetryDialog()
{
    if (!m_telemetryDialog) {
        m_telemetryDialog = new TelemetryDialog(Core::ICore::mainWindow());
    }
    return m_telemetryDialog.data();
}

DataSourcesDialog* ConnectedCreatorPlugin::dataSourcesDialog()
{
    if (!m_sourcesDialog) {
        m_sourcesDialog = new DataSourcesDialog(Core::ICore::mainWindow());
    }
    return m_sourcesDialog.data();
}

StatisticsDialog* ConnectedCreatorPlugin::statisticsDialog()
{
    if (!m_statDialog) {
        m_statDialog = new StatisticsDialog(Core::ICore::mainWindow());
    }
    return m_statDialog.data();
}

void ConnectedCreatorPlugin::telemetryAction()
{
    telemetryDialog()->exec();
}

void ConnectedCreatorPlugin::settingsAction()
{
    settingsDialog()->exec();
}

void ConnectedCreatorPlugin::dataSourcesAction()
{
    dataSourcesDialog()->exec();
}

void ConnectedCreatorPlugin::statisticsAction()
{
    statisticsDialog()->exec();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
