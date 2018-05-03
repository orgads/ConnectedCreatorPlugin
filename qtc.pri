## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$clean_path($${PWD}/../qt-creator-src)

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$clean_path($${PWD}/../qt-creator-debug)

!osx {
    IDE_LIB_PATH = $${IDE_BUILD_TREE}/lib/qtcreator/plugins
} else {
    IDE_LIB_PATH = $${IDE_BUILD_TREE}/Frameworks
}

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
IDE_BIN_PATH = $${IDE_BUILD_TREE}/bin

message(Source tree: ($$IDE_SOURCE_TREE))
message(Build tree: ($$IDE_BUILD_TREE))
message(Lib path: ($$IDE_LIB_PATH))
message(Bin path: ($$IDE_BIN_PATH))
