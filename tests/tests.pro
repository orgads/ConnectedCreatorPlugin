QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qtelemetrytest.cpp

INCLUDEPATH += \
    ./ \
    ../lib/qtelemetry

isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = ../../qt-creator-debug

## uncomment to build plugin into user config directory
#USE_USER_DESTDIR = yes

unix|win32: LIBS += -L$${IDE_BUILD_TREE}/lib/qtcreator/plugins/ -lQTelemetry
