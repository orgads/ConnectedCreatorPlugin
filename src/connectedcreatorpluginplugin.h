﻿#pragma once

#include "connectedcreatorplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace KUserFeedback { class Provider; }
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
    ShutdownFlag aboutToShutdown();

    ControlDialog* controlDialog();
    StatisticsDialog* statisticsDialog();
    KUserFeedback::Provider* provider();

private slots:
    void controlAction();
    void statisticsAction();
    void configureFeedback();

private:
    Core::Command* addMenuAction(const QString &text,
                                 const char *method,
                                 const char actionId[],
                                 const QKeySequence &sequence);

    QPointer<ControlDialog> m_controlDialog;
    QPointer<StatisticsDialog> m_statDialog;

    QPointer<KUserFeedback::Provider> m_feedbackProvider;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin
