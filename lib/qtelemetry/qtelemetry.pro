include(qtelemetry.pri)

QT += network opengl

TARGET = QTelemetry
TEMPLATE = lib
VERSION = $${QT.QTelemetry.VERSION}
win32:TARGET_EXT = .dll #Setting the output filename without the major version number on Windows

DEFINES += QTELEMETRY_LIBRARY QT_DEPRECATED_WARNINGS

SOURCES += \
    qtelemetrymanager.cpp \
    abstractdatasource.cpp \
    qscheduler.cpp \
    applicationversionsource.cpp \
    compilerinfosource.cpp \
    cpuinfosource.cpp \
    localeinfosource.cpp \
    openglinfosource.cpp \
    platforminfosource.cpp \
    qpainfosource.cpp \
    qtversionsource.cpp \
    screeninfosource.cpp \
    styleinfosource.cpp \
    startcountsource.cpp \
    usagetimesource.cpp \
    qabstractusagetimesource.cpp \
    quuidsource.cpp \
    qnetworkmanager.cpp \
    statisticsmodel.cpp

HEADERS += \
    qtelemetry_global.h \
    qtelemetrymanager.h \
    qtelemetrymanager_p.h \
    abstractdatasource.h \
    abstractdatasource_p.h \
    qtelemetry_logging.h \
    qscheduler.h \
    qscheduler_p.h \
    AllSources \
    applicationversionsource.h \
    compilerinfosource.h \
    cpuinfosource.h \
    localeinfosource.h \
    openglinfosource.h \
    platforminfosource.h \
    qpainfosource.h \
    qtversionsource.h \
    screeninfosource.h \
    styleinfosource.h \
    startcountsource.h \
    startcountsource_p.h \
    usagetimesource.h \
    usagetimesource_p.h \
    qabstractusagetimesource.h \
    qabstractusagetimesource_p.h \
    quuidsource.h \
    quuidsource_p.h \
    inetworkmanager.h \
    qnetworkmanager.h \
    qnetworkmanager_p.h \
    statisticsmodel.h \
    statisticsmodel_p.h

include(../../qtc.pri)
include(../../qtc_pluginlibrary.pri)
