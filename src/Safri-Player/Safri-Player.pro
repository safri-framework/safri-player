#-------------------------------------------------
#
# Project created by QtCreator 2012-09-18T16:26:59
#
#-------------------------------------------------



QT       += core gui widgets xml

TARGET = Safri-Player
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += thread

TEMPLATE = app

include(../Defines.pri)

!android {
    DESTDIR = ../../bin
}

android {

deployment.files=selectedplugins.lst
deployment.path=/assets

INSTALLS += deployment
}

INCLUDEPATH += ../PluginSystem
INCLUDEPATH += -L/usr/include/i386-linux-gnu/c++/4.7/
LIBS += -lPluginSystem -L../../lib

SOURCES += main.cpp


macx {

    QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/$${TARGET}.xml\" \"$$DESTDIR/$${TARGET}.xml\"

} else {

    win32 {

        PRO_PWD = $$_PRO_FILE_PWD_
        PRO_PWD_WIN = $$replace(PRO_PWD, /, \\)
        #QMAKE_POST_LINK += $${QMAKE_COPY} \"$${PRO_PWD_WIN}\\audacity-test-file.mp3\" \"..\\..\\bin\\audacity-test-file.mp3\"

    } else {

        unix {
            #QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/audacity-test-file.mp3\" \"$$DESTDIR/audacity-test-file.mp3\"
        }
    }
}

RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    selectedplugins.lst \
    safri-config.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/src/Safri-Player/android
