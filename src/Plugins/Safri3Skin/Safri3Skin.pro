#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T01:57:31
#
#-------------------------------------------------

QT       += gui widgets

TARGET = Safri3Skin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

# Link against the MainWindow plugin for the skin interface
#INCLUDEPATH += ../MainWindow
#LIBS += -L"../../../bin/plugins/safri" -lMainWindow

DEFINES += SAFRI3SKIN_LIBRARY

SOURCES += Safri3SkinPlugin.cpp \
    Safri3Skin.cpp

HEADERS += Safri3SkinPlugin.h\
        safri3skin_global.h \
    Safri3Skin.h

OTHER_FILES += \
    Safri3Skin.xml \
    safri3skin.json \
    stylesheet.css

RESOURCES += \
    ressources.qrc
