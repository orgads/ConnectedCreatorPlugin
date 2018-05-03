include(qtc.pri)

#TARGET = $$qtLibraryTarget($$TARGET)

TEMPLATE = lib
CONFIG += shared dll
DESTDIR = $$IDE_LIB_PATH

win32 {
    #applies only to Windows targets. Specifies where to copy the target dll.
    DLLDESTDIR = $$IDE_BIN_PATH
}

osx {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/Frameworks/
    QMAKE_LFLAGS += -compatibility_version $$QTCREATOR_COMPAT_VERSION
}
