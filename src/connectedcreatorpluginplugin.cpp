﻿#include "connectedcreatorpluginplugin.h"
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

#include "kuserfeedback_headers.h"

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

    Core::Command *cmd3 = addMenuAction(tr("&Provider config"),
                                        &ConnectedCreatorPlugin::configureFeedback,
                                        Constants::PROVIDER_ACTION_ID,
                                        QKeySequence(tr("Ctrl+Alt+Meta+P")));

    // Add actions to ConnectedCreatorPlugin menu
    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("&Analytics"));
    menu->addAction(cmd1);
    menu->addAction(cmd2);
    menu->addAction(cmd3);

    // Add ConnectedCreatorPlugin menu to Qt Creator "Tools" menu
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

/// \brief Configure KUserFeedback
void ConnectedCreatorPlugin::configureFeedbackProvider()
{
    provider()->setProductIdentifier(QStringLiteral("io.qt.qtc.analytics"));
    //provider()->setFeedbackServer(QUrl(QStringLiteral("https://qt-creator-userfeedback.com/")));
    provider()->setSubmissionInterval(7);
    provider()->setApplicationStartsUntilEncouragement(5);
    provider()->setEncouragementDelay(30);
    provider()->setEnabled(PluginSettings::telemetryEnabled());

    // Add generic data sources
    provider()->addDataSource(new KUserFeedback::ApplicationVersionSource);
    provider()->addDataSource(new KUserFeedback::CompilerInfoSource);
    provider()->addDataSource(new KUserFeedback::CpuInfoSource);
    auto localeSource = new KUserFeedback::LocaleInfoSource();
    localeSource->setTelemetryMode(KUserFeedback::Provider::DetailedSystemInformation);
    provider()->addDataSource(localeSource);
    provider()->addDataSource(new KUserFeedback::OpenGLInfoSource);
    provider()->addDataSource(new KUserFeedback::PlatformInfoSource);
    provider()->addDataSource(new KUserFeedback::QPAInfoSource);
    provider()->addDataSource(new KUserFeedback::QtVersionSource);
    provider()->addDataSource(new KUserFeedback::ScreenInfoSource);
    provider()->addDataSource(new KUserFeedback::StartCountSource);
    auto styleSource = new KUserFeedback::StyleInfoSource();
    styleSource->setTelemetryMode(KUserFeedback::Provider::DetailedSystemInformation);
    provider()->addDataSource(styleSource);
    provider()->addDataSource(new KUserFeedback::UsageTimeSource);
    provider()->setTelemetryMode(KUserFeedback::Provider::DetailedUsageStatistics);

    // Add Qt Creator specific data sources
    QList<QWidget *> widgets =  Core::DesignMode::instance()->findChildren<QWidget *>();
            // Core::ICore::mainWindow()->findChildren<QWidget *>();
    QList<QWidget *>::iterator it = std::find_if(widgets.begin(), widgets.end(),
        [](QWidget *widget) -> bool {
            return QString::fromLatin1(widget->metaObject()->className()) == "DesignModeWidget";
    });
    QWidget *designer = (it != widgets.end()) ? *it : nullptr;
    qDebug() << ((designer) ? designer->metaObject()->className() : "nullptr");

    // Connect Provider to UI
    controlDialog()->setFeedbackProvider(provider());
    statisticsDialog()->setFeedbackProvider(provider());
    auto popup = new KUserFeedback::NotificationPopup(Core::ICore::mainWindow());
    popup->setFeedbackProvider(provider());
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
    // Configure KUserFeedback after all plugins initialized
    // to have all the objects available before configuration
    configureFeedbackProvider();

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

KUserFeedback::Provider* ConnectedCreatorPlugin::provider()
{
    if(!m_feedbackProvider) {
        m_feedbackProvider = new KUserFeedback::Provider(this);
    }
    return m_feedbackProvider.data();
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

void ConnectedCreatorPlugin::configureFeedback()
{
    KUserFeedback::FeedbackConfigDialog dlg;
    dlg.setFeedbackProvider(provider());
    dlg.exec();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
