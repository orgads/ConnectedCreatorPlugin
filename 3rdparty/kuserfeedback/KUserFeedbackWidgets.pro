#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T03:13:20
#
#-------------------------------------------------

QT += KUserFeedbackCore widgets

TARGET = KUserFeedbackWidgets
TEMPLATE = lib

DEFINES += KUSERFEEDBACKWIDGETS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += common core

SOURCES += \
    widgets/auditlogbrowserdialog.cpp \
    widgets/feedbackconfigdialog.cpp \
    widgets/feedbackconfigwidget.cpp \
    widgets/notificationpopup.cpp \
    widgets/styleinfosource.cpp

HEADERS += \
    widgets/auditlogbrowserdialog.h \
    widgets/FeedbackConfigDialog \
    widgets/feedbackconfigdialog.h \
    widgets/FeedbackConfigWidget \
    widgets/feedbackconfigwidget.h \
    widgets/kuserfeedbackwidgets_export.h \
    widgets/NotificationPopup \
    widgets/notificationpopup.h \
    widgets/StyleInfoSource \
    widgets/styleinfosource.h

FORMS += \
    widgets/auditlogbrowserdialog.ui \
    widgets/feedbackconfigdialog.ui \
    widgets/feedbackconfigwidget.ui \
    widgets/notificationpopup.ui
