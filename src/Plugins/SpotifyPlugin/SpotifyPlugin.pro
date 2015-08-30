#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T14:05:59
#
#-------------------------------------------------

TARGET = SpotifyPlugin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)
include(../libQtSpotify/libQtSpotify.pri)
QT += widgets quick quickwidgets
INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += SPOTIFYPLUGIN_LIBRARY

SOURCES += SpotifyPlugin.cpp \
    SpotifyLookupSidebarWidget.cpp \
    SpotifySearch.cpp \
    SpotifyMediaBackend.cpp \
    SpotifySafriHelper.cpp

HEADERS += SpotifyPlugin.h\
        spotifyplugin_global.h \
    SpotifyLookupSidebarWidget.h \
    SpotifySearch.h \
    SpotifyMediaBackend.h \
    SpotifySafriHelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    spotifyplugin.json \
    main.qml
//
FORMS += \
    SpotifySearch.ui

RESOURCES += \
    resources.qrc