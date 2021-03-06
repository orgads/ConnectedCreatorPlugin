﻿/****************************************************************************
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
#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

namespace Core { class SettingsDatabase; }

namespace ConnectedCreator {
namespace Internal {

class PluginSettings
{
public:
    static Core::SettingsDatabase *instance() { return settings(); }

    static bool firstStart();
    static void setFirstStart();

    static bool telemetryEnabled();
    static void setTelemetryEnabled(bool enabled);
    /// \return Log expiration period in days
    static int expirePeriod();
    /// \brief setExpirePeriod Log expiration period settings
    /// \param period -1 - never expires; 0 - expires right after tramsmission;
    /// 1...365 expires after period in days
    static void setExpirePeriod(int period);

private:
    static Core::SettingsDatabase *settings();
    static Core::SettingsDatabase *m_settings;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // PLUGINSETTINGS_H
