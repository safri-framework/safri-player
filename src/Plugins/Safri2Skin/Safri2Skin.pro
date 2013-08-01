#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T01:57:31
#
#-------------------------------------------------

QT       -= gui

TARGET = Safri2Skin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

# Link against the MainWindow plugin for the skin interface
INCLUDEPATH += ../MainWindow
LIBS += -L"../../../bin/plugins/safri" -lMainWindow

DEFINES += SAFRI2SKIN_LIBRARY

SOURCES += Safri2SkinPlugin.cpp

HEADERS += Safri2SkinPlugin.h\
        safri2skin_global.h

OTHER_FILES += \
    Safri2Skin.xml \
    safri2skin.json \
    stylesheet.css

RESOURCES += \
    ressources.qrc
