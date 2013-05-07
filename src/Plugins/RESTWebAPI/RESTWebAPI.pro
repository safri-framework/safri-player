#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T01:07:57
#
#-------------------------------------------------

QT       += network gui widgets

#QT       -= gui

TARGET = RESTWebAPI
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += RESTWEBAPI_LIBRARY

SOURCES += RESTWebAPIPlugin.cpp \
    controller/templatecontroller.cpp \
    controller/sessioncontroller.cpp \
    controller/formcontroller.cpp \
    controller/fileuploadcontroller.cpp \
    controller/dumpcontroller.cpp \
    static.cpp \
    requestmapper.cpp \
    controller/PlayerController.cpp \
    controller/StaticPlayerHelper.cpp \
    controller/PlaylistController.cpp \
    controller/CollectionController.cpp

HEADERS += RESTWebAPIPlugin.h\
        RESTWebAPI_global.h \
    controller/templatecontroller.h \
    controller/sessioncontroller.h \
    controller/formcontroller.h \
    controller/fileuploadcontroller.h \
    controller/dumpcontroller.h \
    static.h \
    requestmapper.h \
    documentcache.h \
    controller/PlayerController.h \
    controller/StaticPlayerHelper.h \
    controller/PlaylistController.h \
    controller/CollectionController.h

OTHER_FILES += \
    RESTWebAPI.xml \
    RESTWebAPI.json

include(lib/qtservice/src/qtservice.pri)
include(lib/bfHttpServer/src/bfHttpServer.pri)
include(lib/bfTemplateEngine/src/bfTemplateEngine.pri)
