TEMPLATE = subdirs

SUBDIRS += \     # sub-project names
        KUserFeedbackCore \
        KUserFeedbackWidgets \
        ConnectedCreatorPlugin

# where to find the sub projects - give the folders
KUserFeedbackCore.file = 3rdparty/kuserfeedback/KUserFeedbackCore.pro
KUserFeedbackWidgets.file = 3rdparty/kuserfeedback/KUserFeedbackWidgets.pro
ConnectedCreatorPlugin.file = src/connectedcreatorplugin.pro

# what subproject depends on others
ConnectedCreatorPlugin.depends = KUserFeedbackCore KUserFeedbackWidgets

CONFIG += ordered
