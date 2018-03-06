# ConnectedCreatorPlugin
<img src="src/images/monitoring-300px.png" alt="Telemetry-Icon" height="125" align="left"> This is a work-in-progress project to create a data analytics plugin for Connected Creator. The plugin collects usage data from Qt Creator users. This data is used to improve Qt user experience.

The Qt Company has an increasing need to better understand, how Qt products and product features are used. Currently, we collect statistics about Qt downloads and Qt web site and online documentation usage. However, we have limited understanding, what user actually install and how they use different features after the installation.

This project us about collecting and analyzing usage data to better understand, how developers use Qt. The idea is to collect anonymous data only, i.e. there is no way to map the collected data to any user identity. The feature is opt-in and collected data will be totally transparent to the user. We also plan to publish the collected data in a suitable format.

As the first step, we want to start building the expertise in data mining and analytics. Before we become experts in data mining, we will need some usage data, which is the main objective of this project. 

# Build
Assume have following directory structure:
* `./ConnectedCreatorPlugin/src` - ConnectedCreatorPlugin sources
* `./ConnectedCreatorPlugin/3rdparty/kuserfeedback` - KUserFeedback sources
* `./qt-creator-src` - Qt Creator sources dir
* `./qt-creator-debug` - Qt Creator build dir

Build instruction until moved to Qt Creator source tree:
- `cd ./ConnectedCreatorPlugin-build` - or other build dir
- `qmake ../ConnectedCreatorPlugin/ConnectedCreator.pro CONFIG+=debug` -r
- `make -j4`

Or Build & Run in Qt Creator preserving above directory structure.
