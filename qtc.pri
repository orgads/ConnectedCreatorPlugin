isEmpty(IDE_DISPLAY_NAME): IDE_DISPLAY_NAME = Qt Creator

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$clean_path($${PWD}/../qt-creator-src)

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$clean_path($${PWD}/../qt-creator-debug)

# ${VAR} notation allows to append the contents of the variable to another value
# without separating the two with a space
IDE_BIN_PATH = $${IDE_BUILD_TREE}/bin

!mac {
    IDE_LIB_PATH = $${IDE_BUILD_TREE}/lib/qtcreator/plugins
} else {
    IDE_APP_TARGET = "$$IDE_DISPLAY_NAME"
	IDE_APP_BUNDLE = $$IDE_BIN_PATH/$${IDE_APP_TARGET}.app
    # set output path if not set manually
    isEmpty(IDE_OUTPUT_PATH): IDE_OUTPUT_PATH = $$IDE_APP_BUNDLE/Contents
    IDE_LIB_PATH = $${IDE_OUTPUT_PATH}/Frameworks
}

message(Source tree: ($$IDE_SOURCE_TREE))
message(Build tree: ($$IDE_BUILD_TREE))
message(Lib path: ($$IDE_LIB_PATH))
message(Bin path: ($$IDE_BIN_PATH))
