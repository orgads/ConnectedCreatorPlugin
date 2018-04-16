﻿# ConnectedCreatorPlugin
<img src="src/images/monitoring-300px.png" alt="Telemetry-Icon" height="125" align="left"> This is a work-in-progress project to create a data analytics plugin for Connected Creator. The plugin collects usage data from Qt Creator users. This data is used to improve Qt user experience.

The Qt Company has an increasing need to better understand, how Qt products and product features are used. Currently, we collect statistics about Qt downloads and Qt web site and online documentation usage. However, we have limited understanding, what user actually install and how they use different features after the installation.

This project us about collecting and analyzing usage data to better understand, how developers use Qt. The idea is to collect anonymous data only, i.e. there is no way to map the collected data to any user identity. The feature is opt-in and collected data will be totally transparent to the user. We also plan to publish the collected data in a suitable format.

As the first step, we want to start building the expertise in data mining and analytics. Before we become experts in data mining, we will need some usage data, which is the main objective of this project. 

# Build

## Directory structure
Assume have following directory structure:
* `./ConnectedCreatorPlugin/src` - ConnectedCreatorPlugin sources
* `./ConnectedCreatorPlugin/3rdparty/kuserfeedback` - KUserFeedback sources
* `./qt-creator-src` - Qt Creator sources dir
* `./qt-creator-debug` - Qt Creator build dir

Need to build Qt Creator first into `./qt-creator-debug`.

## Plugin build instructions
Build instruction until moved to Qt Creator source tree:
- `cd ./ConnectedCreatorPlugin-build` - or other build dir
- `qmake ../ConnectedCreatorPlugin/ConnectedCreator.pro CONFIG+=debug` -r
- `make -j4`

Or Build & Run in Qt Creator preserving above directory structure.

## REST-server build instructions
To build sample REST-server (dummy for now) based on [QttpServer](https://github.com/supamii/QttpServer) execute:
- `cd ./ConnectedCreatorPlugin`
- `git submodule update --init --recursive`
- `cd ./server/qttpserver`
- `qmake qttpserver.pro -r`
- `make -j4`
- `cd ..`
- `qmake server.pro`
- `make -j4`

To build in Qt Creator disable "Shadow build" for qttpserver. After build you may find executable in 
- `./ConnectedCreatorPlugin/server/qttpserver/build/qtrelease` or 
- `./ConnectedCreatorPlugin/server/qttpserver/build/qtdebug` 

directories. By default `qttpserver`, `libuv`, `node_native`, `http_parser` libraries are linked statically into the server.
