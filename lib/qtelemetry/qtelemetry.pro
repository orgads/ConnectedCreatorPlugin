include(qtelemetry.pri)

QT       += network
QT       -= gui

TARGET = QTelemetry
TEMPLATE = lib
VERSION = $${QT.QTelemetry.VERSION}

DEFINES += QTELEMETRY_LIBRARY QT_DEPRECATED_WARNINGS

SOURCES += \
        qtelemetrymanager.cpp \
        abstractdatasource.cpp

HEADERS += \
        qtelemetry_global.h \
        qtelemetrymanager.h \
        qtelemetrymanager_p.h \
        abstractdatasource.h \
        abstractdatasource_p.h \
        qtelemetry_logging.h

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