#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T15:26:04
#
#-------------------------------------------------

QT       -= gui

TARGET = TagLibMediaTagger
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

win32 {
    INCLUDEPATH += C:\\taglib\\include
    LIBS += -L"C:\\taglib\\lib"
    LIBS += -llibtag
}

macx {
    INCLUDEPATH += /opt/local/include
    LIBS += -L"/opt/local/lib"
    LIBS += -ltag
}

!macx{
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib
}
}

DEFINES += TAGLIBMEDIATAGGER_LIBRARY

SOURCES += taglibmediataggerplugin.cpp \
    taglibmediatagger.cpp

HEADERS += taglibmediataggerplugin.h\
        TagLibMediaTagger_global.h \
    taglibmediatagger.h

OTHER_FILES += \
    TagLibMediaTagger.xml

