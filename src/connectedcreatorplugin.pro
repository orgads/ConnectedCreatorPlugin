DEFINES += CONNECTEDCREATORPLUGIN_LIBRARY

# ConnectedCreatorPlugin files
INCLUDEPATH += \
    $$PWD \
    ../lib/qtelemetry \
    $$OUT_PWD

SOURCES += \
    connectedcreatorpluginplugin.cpp \
    statisticsdialog.cpp \
    pluginsettings.cpp \
    qjsonmodel.cpp \
    jsonsyntaxhighlighter.cpp \
    qmldesignerusagetimesource.cpp \
    telemetrydialog.cpp \
    datasourcesdialog.cpp \
    settingsdialog.cpp \
    qtclicensesource.cpp

HEADERS += \
    connectedcreatorpluginplugin.h \
    connectedcreatorplugin_global.h \
    connectedcreatorpluginconstants.h \
    statisticsdialog.h \
    pluginsettings.h \
    qjsonmodel.h \
    ctreeview.h \
    jsonsyntaxhighlighter.h \
    qmldesignerusagetimesource.h \
    telemetrydialog.h \
    settingsdialog.h \
    datasourcesdialog.h \
    qtclicensesource.h

FORMS += \
    statisticsdialog.ui \
    telemetrydialog.ui \
    datasourcesdialog.ui \
    settingsdialog.ui

RESOURCES += \
    plugin.qrc

# Qt Creator linking
include(../qtc.pri)

## uncomment to build plugin into user config directory
#USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = ConnectedCreatorPlugin
QTC_LIB_DEPENDS += \
    qtelemetry

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)

DISTFILES +=
