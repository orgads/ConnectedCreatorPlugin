#!/bin/sh
#
# Update the subset of KUserFeedback relevant for us from upstream
#
# Usage: kuserfeedback-update.sh path-to-kuserfeedback

upstream=$1
if ! [ -d "$upstream" ]; then
    echo "Usage $0 <kuserfeedback checkout>"
    exit 1
fi

# Create dirs if not exists
mkdir -p common
mkdir -p core
mkdir -p widgets
mkdir -p qml

# Run cmake in upstream to generate some sources
pushd $upstream
git pull
cmake .
popd

# Copy all files from kuserfeedback checkout ignoring file patterns below
ignore="-I "CMake*" -I "*.cmake" -I Makefile"

for i in `ls $ignore $upstream | grep "\.h$"`; do		# Copy root header files
    if [ -f $upstream/$i ]; then
        cp $upstream/$i ./$i
    fi
done

for i in `ls $ignore $upstream/src/common`; do
    if [ -f $upstream/src/common/$i ]; then
        cp $upstream/src/common/$i common/$i
    fi
done

for i in `ls $ignore $upstream/src/provider/core`; do
    cp $upstream/src/provider/core/$i core/$i
done

for i in `ls $ignore $upstream/src/provider/widgets`; do
    cp $upstream/src/provider/widgets/$i widgets/$i
done

for i in `ls $ignore $upstream/src/provider/qml`; do
    cp $upstream/src/provider/qml/$i qml/$i
done

pushd common
flex --header-file=surveytargetexpressionscanner.h -o surveytargetexpressionlexer.cpp surveytargetexpressionlexer.l
bison --defines=surveytargetexpressionparser_p.h -d -o surveytargetexpressionparser_p.cpp surveytargetexpressionparser.y
popd
