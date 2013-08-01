#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T01:57:31
#
#-------------------------------------------------

QT       -= gui

TARGET = Safri3Skin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

# Link against the MainWindow plugin for the skin interface
INCLUDEPATH += ../MainWindow
LIBS += -L"../../../bin/plugins/safri" -lMainWindow

DEFINES += SAFRI3SKIN_LIBRARY

SOURCES += Safri3SkinPlugin.cpp

HEADERS += Safri3SkinPlugin.h\
        safri3skin_global.h

OTHER_FILES += \
    Safri3Skin.xml \
    safri3skin.json \
    stylesheet.css

RESOURCES += \
    ressources.qrc
