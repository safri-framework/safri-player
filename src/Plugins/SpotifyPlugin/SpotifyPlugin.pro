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
    SpotifySafriHelper.cpp \

HEADERS += SpotifyPlugin.h\
        spotifyplugin_global.h \
    SpotifyLookupSidebarWidget.h \
    SpotifySafriHelper.h \
    SpotifySearch.h \
    SpotifyMediaBackend.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    spotifyplugin.json

RESOURCES += \
    resources.qrc

FORMS += \
    SpotifySearch.ui
CONFIG += c++11


macx
{
    QMAKE_LFLAGS += -F/Users/friedemann/Downloads/libspotify-12.1-2.51-Darwin-universal
    INCLUDEPATH += /Users/friedemann/Downloads/libspotify-12.1-2.51-Darwin-universal/libspotify.framework
    LIBS += -framework libspotify
}

unix
{


}
