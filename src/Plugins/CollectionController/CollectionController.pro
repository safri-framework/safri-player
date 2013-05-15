#-------------------------------------------------
#
# Project created by QtCreator 2012-12-30T13:42:15
#
#-------------------------------------------------

QT       += widgets

TARGET = CollectionController
TEMPLATE = lib


PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore


DEFINES += COLLECTIONCONTROLLER_LIBRARY

SOURCES += CollectionController.cpp \
    CollectionControllerPlugin.cpp \
    CollectionControllerSettingsDialog.cpp

HEADERS += CollectionController.h\
        CollectionController_global.h \
    CollectionControllerPlugin.h \
    CollectionControllerSettingsDialog.h

OTHER_FILES += \
    collectioncontroller.json

FORMS += \
    CollectionControllerSettingsDialog.ui

RESOURCES += \
    ressources.qrc

