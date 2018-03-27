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

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = ../../qt-creator-src

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = ../../qt-creator-debug

message(Source tree: ($$IDE_SOURCE_TREE))
message(Build tree: ($$IDE_BUILD_TREE))

## uncomment to build plugin into user config directory
#USE_USER_DESTDIR = yes

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
isEmpty(DESTDIR): DESTDIR = $${IDE_BUILD_TREE}/lib/qtcreator/plugins
message(DESTDIR: ($$DESTDIR))

unix|win32: LIBS += -L$${IDE_BUILD_TREE}/lib/qtcreator/plugins/ -lQTelemetry

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
