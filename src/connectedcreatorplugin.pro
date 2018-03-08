include(../3rdparty/kuserfeedback/widgets/qt_KUserFeedbackWidgets.pri)
include(../3rdparty/kuserfeedback/core/qt_KUserFeedbackCore.pri)

DEFINES += CONNECTEDCREATORPLUGIN_LIBRARY

QT += KUserFeedbackCore KUserFeedbackWidgets

# ConnectedCreatorPlugin files
INCLUDEPATH += \
    ../3rdparty \
    ../3rdparty/kuserfeedback/common \
    ../3rdparty/kuserfeedback/core \
    ../3rdparty/kuserfeedback/widgets

SOURCES += \
    connectedcreatorpluginplugin.cpp \
    controldialog.cpp \
    statisticsdialog.cpp \
    pluginsettings.cpp

HEADERS += \
    connectedcreatorpluginplugin.h \
    connectedcreatorplugin_global.h \
    connectedcreatorpluginconstants.h \
    controldialog.h \
    statisticsdialog.h \
    kuserfeedback_headers.h \
    pluginsettings.h

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
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
#USE_USER_DESTDIR = yes

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
isEmpty(DESTDIR): DESTDIR = $${IDE_BUILD_TREE}/lib/qtcreator/plugins

message(DESTDIR: ($$DESTDIR))

unix|win32: LIBS += -L$${IDE_BUILD_TREE}/lib/qtcreator/plugins/ -lKUserFeedbackCore -lKUserFeedbackWidgets

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
