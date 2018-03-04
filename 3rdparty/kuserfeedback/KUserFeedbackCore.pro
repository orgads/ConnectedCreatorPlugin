#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T01:57:55
#
#-------------------------------------------------
include(core/qt_KUserFeedbackCore.pri)

QT += core network

TARGET = KUserFeedbackCore
TEMPLATE = lib
VERSION = $$QT.KUserFeedbackCore.VERSION

DEFINES += KUSERFEEDBACKCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += common core

SOURCES += \
    core/abstractdatasource.cpp \
    core/applicationversionsource.cpp \
    core/auditloguicontroller.cpp \
    core/compilerinfosource.cpp \
    core/cpuinfosource.cpp \
    core/ECMQmLoader-userfeedbackprovider5_qt.cpp \
    core/feedbackconfiguicontroller.cpp \
    core/localeinfosource.cpp \
    core/openglinfosource.cpp \
    core/platforminfosource.cpp \
    core/propertyratiosource.cpp \
    core/provider.cpp \
    core/qpainfosource.cpp \
    core/qtversionsource.cpp \
    core/screeninfosource.cpp \
    core/selectionratiosource.cpp \
    core/startcountsource.cpp \
    core/surveyinfo.cpp \
    core/usagetimesource.cpp

HEADERS += \
    core/AbstractDataSource \
    core/abstractdatasource_p.h \
    core/abstractdatasource.h \
    core/ApplicationVersionSource \
    core/applicationversionsource.h \
    core/auditloguicontroller.h \
    core/CompilerInfoSource \
    core/compilerinfosource.h \
    core/CpuInfoSource \
    core/cpuinfosource.h \
    core/feedbackconfiguicontroller.h \
    core/kuserfeedbackcore_export.h \
    core/LocaleInfoSource \
    core/localeinfosource.h \
    core/logging_p.h \
    core/OpenGLInfoSource \
    core/openglinfosource_p.h \
    core/openglinfosource.h \
    core/PlatformInfoSource \
    core/platforminfosource.h \
    core/PropertyRatioSource \
    core/propertyratiosource.h \
    core/Provider \
    core/provider_p.h \
    core/provider.h \
    core/QPAInfoSource \
    core/qpainfosource.h \
    core/QtVersionSource \
    core/qtversionsource.h \
    core/ScreenInfoSource \
    core/screeninfosource.h \
    core/selectionratiosource.h \
    core/StartCountSource \
    core/startcountsource.h \
    core/SurveyInfo \
    core/surveyinfo.h \
    core/UsageTimeSource \
    core/usagetimesource.h \
    common/surveytargetexpression.h \
    common/surveytargetexpressionevaluator.h \
    common/surveytargetexpressionlexer.l \
    common/surveytargetexpressionparser_p.h \
    common/surveytargetexpressionparser.h \
    common/surveytargetexpressionparser.y \
    common/surveytargetexpressionscanner.h

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = ../../../qt-creator-src

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = ../../../qt-creator-debug

message(Source tree: ($$IDE_SOURCE_TREE))
message(Build tree: ($$IDE_BUILD_TREE))

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
isEmpty(DESTDIR): DESTDIR = $${IDE_BUILD_TREE}/lib/qtcreator/plugins

message(DESTDIR: ($$DESTDIR))
message(PWD: ($$PWD))

DISTFILES +=
