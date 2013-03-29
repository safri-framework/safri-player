#-------------------------------------------------
#
# Project created by QtCreator 2013-03-29T11:36:43
#
#-------------------------------------------------

QT       += webkit widgets webkitwidgets network

TARGET = ShoutCastPlugin
TEMPLATE = lib

DEFINES += SHOUTCASTPLUGIN_LIBRARY

SOURCES += shoutcastplugin.cpp \
    shoutcastsidebar.cpp \
    plsopener.cpp \
    shoutcaststream.cpp

HEADERS += shoutcastplugin.h\
        ShoutCastPlugin_global.h \
    shoutcastsidebar.h \
    plsopener.h \
    shoutcaststream.h


PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    shoutcastplugin.json

RESOURCES += \
    Resources.qrc
