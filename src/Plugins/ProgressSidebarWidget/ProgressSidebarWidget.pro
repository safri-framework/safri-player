#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T15:12:25
#
#-------------------------------------------------

QT       += widgets

TARGET = ProgressSidebarWidget
TEMPLATE = lib

DEFINES += PROGRESSSIDEBARWIDGET_LIBRARY

SOURCES += \
    ProgressSidebarWidgetPlugin.cpp \
    NotificationSidebarWidget.cpp \
    NotificationWidget.cpp \
    NotificationItem.cpp

HEADERS +=\
        progresssidebarwidget_global.h \
    ProgressSidebarWidgetPlugin.h \
    NotificationSidebarWidget.h \
    NotificationWidget.h \
    NotificationItem.h

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore


OTHER_FILES += \
    ProgressSidebarWidget.json \
    ProgressSidebarWidget.xml

FORMS += \
    NotificationWidget.ui \
    NotificationItem.ui
