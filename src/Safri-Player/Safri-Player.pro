#-------------------------------------------------
#
# Project created by QtCreator 2012-09-18T16:26:59
#
#-------------------------------------------------

SAFRI_VERSION = 0.3.1

QT       += core gui

TARGET = Safri-Player
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = ../../bin

INCLUDEPATH += ../PluginSystem
LIBS += -lPluginSystem -L../../lib

VERSTR = '\\"$${SAFRI_VERSION}\\"'
DEFINES += SAFRI_VERSION=\"$${VERSTR}\"

SOURCES += main.cpp


macx {

    QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/$${TARGET}.xml\" \"$$DESTDIR/$${TARGET}.xml\"

} else {

    win32 {

        PRO_PWD = $$_PRO_FILE_PWD_
        PRO_PWD_WIN = $$replace(PRO_PWD, /, \\)
        QMAKE_POST_LINK += $${QMAKE_COPY} \"$${PRO_PWD_WIN}\\audacity-test-file.mp3\" \"..\\..\\bin\\audacity-test-file.mp3\"

    } else {

        unix {
            QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/media/audacity-test-file.mp3\" \"$$DESTDIR/audacity-test-file.mp3\"
        }
    }
}
