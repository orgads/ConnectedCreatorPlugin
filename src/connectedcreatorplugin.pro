include(../lib/qtelemetry/qtelemetry.pri)

DEFINES += CONNECTEDCREATORPLUGIN_LIBRARY

QT += QTelemetry

# ConnectedCreatorPlugin files
INCLUDEPATH += \
    ./ \
    ../lib/qtelemetry

SOURCES += \
    connectedcreatorpluginplugin.cpp \
    controldialog.cpp \
    statisticsdialog.cpp \
    pluginsettings.cpp \
    qjsonmodel.cpp \
    jsonsyntaxhighlighter.cpp \
    qmldesignerusagetimesource.cpp

HEADERS += \
    connectedcreatorpluginplugin.h \
    connectedcreatorplugin_global.h \
    connectedcreatorpluginconstants.h \
    controldialog.h \
    statisticsdialog.h \
    pluginsettings.h \
    qjsonmodel.h \
    ctreeview.h \
    jsonsyntaxhighlighter.h \
    qmldesignerusagetimesource.h

FORMS += \
    controldialog.ui \
    statisticsdialog.ui

RESOURCES += \
    plugin.qrc

# Qt Creator linking
include(../qtc.pri)

## uncomment to build plugin into user config directory
#USE_USER_DESTDIR = yes

LIBS += -L$${IDE_LIB_PATH} -lQTelemetry

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = ConnectedCreatorPlugin
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)

DISTFILES +=
