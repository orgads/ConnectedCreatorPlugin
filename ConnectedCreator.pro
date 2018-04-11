TEMPLATE = subdirs

# sub-project names
SUBDIRS += \
    QTelemetry \
    ConnectedCreatorPlugin \
    tests

# where to find the sub projects - give the folders
QTelemetry.file = lib/qtelemetry/qtelemetry.pro
ConnectedCreatorPlugin.file = src/connectedcreatorplugin.pro

# what subproject depends on others
ConnectedCreatorPlugin.depends = QTelemetry

CONFIG += ordered
