include(qtc.pri)

#TARGET = $$qtLibraryTarget($$TARGET)

#CONFIG += debug_and_release

#CONFIG(debug, debug|release) {
#    mac: TARGET = $$join(TARGET,,,_debug)
#    win32: TARGET = $$join(TARGET,,d)
#}

TEMPLATE = lib
CONFIG += shared dll
DESTDIR = $$IDE_LIB_PATH

win32 {
    #applies only to Windows targets. Specifies where to copy the target dll.
    DLLDESTDIR = $$IDE_BIN_PATH
}

mac {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/Frameworks/
    QMAKE_LFLAGS += -compatibility_version $$VERSION
}
