#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T03:13:20
#
#-------------------------------------------------
include(widgets/qt_KUserFeedbackWidgets.pri)
include(core/qt_KUserFeedbackCore.pri)

QT +=  KUserFeedbackCore widgets

TARGET = KUserFeedbackWidgets
TEMPLATE = lib
VERSION = $$QT.KUserFeedbackWidgets.VERSION

DEFINES += KUSERFEEDBACKWIDGETS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += common core widgets

SOURCES += \
    widgets/auditlogbrowserdialog.cpp \
    widgets/feedbackconfigdialog.cpp \
    widgets/feedbackconfigwidget.cpp \
    widgets/notificationpopup.cpp \
    widgets/styleinfosource.cpp

HEADERS += \
    widgets/auditlogbrowserdialog.h \
    widgets/FeedbackConfigDialog \
    widgets/feedbackconfigdialog.h \
    widgets/FeedbackConfigWidget \
    widgets/feedbackconfigwidget.h \
    widgets/kuserfeedbackwidgets_export.h \
    widgets/NotificationPopup \
    widgets/notificationpopup.h \
    widgets/StyleInfoSource \
    widgets/styleinfosource.h

FORMS += \
    widgets/auditlogbrowserdialog.ui \
    widgets/feedbackconfigdialog.ui \
    widgets/feedbackconfigwidget.ui \
    widgets/notificationpopup.ui

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = ../../../qt-creator-src

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = ../../../qt-creator-debug

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
isEmpty(DESTDIR): DESTDIR = $${IDE_BUILD_TREE}/lib/qtcreator/plugins

unix|win32: LIBS += -L$${IDE_BUILD_TREE}/lib/qtcreator/plugins/ -lKUserFeedbackCore
