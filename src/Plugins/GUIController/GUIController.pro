#-------------------------------------------------
#
# Project created by QtCreator 2012-12-13T17:11:00
#
#-------------------------------------------------

TARGET = GUIController
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += GUICONTROLLER_LIBRARY

SOURCES += guicontrollerplugin.cpp \
    guicontroller.cpp

HEADERS += guicontrollerplugin.h\
        GUIController_global.h \
    guicontroller.h

OTHER_FILES += \
    GUIController.xml \
    guicontroller.json
