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

android {

    INCLUDEPATH += $$_PRO_FILE_PWD_/taglib_android/include
    LIBS += -L$$_PRO_FILE_PWD_/taglib_android/lib
    LIBS += -ltag

    taglib.files =  $$_PRO_FILE_PWD_/taglib_android/lib/libtag.so
    taglib.path=/libs/armeabi-v7a

    INSTALLS += taglib

} else {

    win32 {
        INCLUDEPATH += C:\\taglib-1.8\\include
        LIBS += -L"C:\\taglib-1.8\\lib"
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
}

DEFINES += TAGLIBMEDIATAGGER_LIBRARY

SOURCES += taglibmediataggerplugin.cpp \
    taglibmediatagger.cpp

HEADERS += taglibmediataggerplugin.h\
        TagLibMediaTagger_global.h \
    taglibmediatagger.h

OTHER_FILES += \
    TagLibMediaTagger.xml \
    taglibmediatagger.json

