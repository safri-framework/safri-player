#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:34:44
#
#-------------------------------------------------

TARGET = SafriApp
TEMPLATE = lib

QT += quick widgets

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore


DEFINES += SAFRIMOBILEGUIQML_LIBRARY

SOURCES += \
    SafriAppPlugin.cpp \
    SafriAppInstance.cpp \
    playlistmodel.cpp \
    SafriRESTClient/RESTSong.cpp \
    SafriRESTClient/RESTPlaybackController.cpp \
    SafriRESTClient/RESTMediaCollection.cpp \
    SafriRESTClient/RESTClient.cpp \
    SafriRESTClient/RESTSongtreeModel.cpp \
    IAppController.cpp \
    LocalAppController.cpp \
    SafriRESTClient/RESTAppController.cpp \
    SafriRESTClient/RESTSongtreeItem.cpp \
    SafriRESTClient/RESTSongtree.cpp \
    SafriRESTClient/RESTPlaylistModel.cpp \
    SafriRESTClient/RESTPlaylist.cpp

HEADERS +=\
    SafriAppInstance.h \
    SafriAppPlugin.h \
    SafriApp_global.h \
    playlistmodel.h \
    SafriRESTClient/RESTSong.h \
    SafriRESTClient/RESTPlaybackController.h \
    SafriRESTClient/RESTMediaCollection.h \
    SafriRESTClient/RESTActions.h \
    SafriRESTClient/RESTClient.h \
    SafriRESTClient/RESTSongtreeModel.h \
    IAppController.h \
    LocalAppController.h \
    SafriRESTClient/RESTAppController.h \
    SafriRESTClient/RESTSongtreeItem.h \
    SafriRESTClient/RESTSongtree.h \
    SafriRESTClient/RESTPlaylistModel.h \
    SafriRESTClient/RESTPlaylist.h

RESOURCES += \
    QMLResources.qrc

OTHER_FILES += \
    qml/PlayerButton.qml \
    qml/Player.qml \
    qml/MusicSelection.qml \
    qml/main.qml \
    qml/Home.qml \
    qml/functions.js \
    qml/Footer.qml \
    qml/TreeView.qml \
    safriapp.json \
    SafriApp.xml \
    qml/View1.qml \
    qml/TreeView.qml \
    qml/View2.qml \
    qml/Dialer.qml \
    qml/RotaryDialer.js \
    qml/MusicProgress.qml \
    MarqueeText.qml \
    qml/MarqueeText.qml \
    qml/Playlist.qml \
    qml/View3.qml \
    qml/Settings.qml

