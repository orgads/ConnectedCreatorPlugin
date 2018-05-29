/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/
#include "connectedcreatorpluginconstants.h"
#include "pluginsettings.h"

#include <coreplugin/icore.h>
#include <coreplugin/settingsdatabase.h>

namespace ConnectedCreator {
namespace Internal {

// Static member initialization
Core::SettingsDatabase* PluginSettings::m_settings = nullptr;

Core::SettingsDatabase* PluginSettings::settings()
{
    if(!m_settings)
        m_settings = Core::ICore::settingsDatabase();
    return m_settings;
}

bool PluginSettings::firstStart()
{
    return settings()->value(Constants::FIRST_RUN_KEY, true).value<bool>();
}

void PluginSettings::setFirstStart()
{
    settings()->setValue(Constants::FIRST_RUN_KEY, false);
    settings()->sync();
}

bool PluginSettings::telemetryEnabled()
{
    // Enable by default cause already selected as option in installer
    return settings()->value(Constants::ENABLED_KEY, true).value<bool>();
}

void PluginSettings::setTelemetryEnabled(bool enabled)
{
    settings()->setValue(Constants::ENABLED_KEY, enabled);
    settings()->sync();
}

int PluginSettings::expirePeriod()
{
    return settings()->value(Constants::LOGEXPIRE_KEY, -1).value<int>();
}

void PluginSettings::setExpirePeriod(int period)
{
    if(period > 365)
        period = -1;
    settings()->setValue(Constants::LOGEXPIRE_KEY, period);
    settings()->sync();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
