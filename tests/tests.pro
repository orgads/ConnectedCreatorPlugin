QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qtelemetrytest.cpp

INCLUDEPATH += \
    ./ \
    ../lib/qtelemetry

# Qt Creator linking
include(../qtc.pri)

## uncomment to build plugin into user config directory
#USE_USER_DESTDIR = yes

LIBS += -L$${IDE_LIB_PATH} -lQTelemetry
