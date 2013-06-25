include(Defines.pri)

INCLUDEPATH += ../../PluginSystem
LIBS += -L../../../lib -lPluginSystem

isEmpty(PROVIDER) {
    PROVIDER = safri
}

DESTDIR = ../../../bin/plugins/$$PROVIDER

#DEFINES += QT_NO_DEBUG_OUTPUT

CONFIG += thread

# copy plugin spec to appropriate folder
android {

deployment.files=$$_PRO_FILE_PWD_/$${TARGET}.xml
deployment.path=/assets/plugins

INSTALLS += deployment

} else {

    macx {

        QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/$${TARGET}.xml\" \"$$DESTDIR/$${TARGET}.xml\"

    } else {

        win32 {

            PRO_PWD = $$_PRO_FILE_PWD_
            PRO_PWD_WIN = $$replace(PRO_PWD, /, \\)
            QMAKE_POST_LINK += $${QMAKE_COPY} \"$${PRO_PWD_WIN}\\$${TARGET}.xml\" \"..\\..\\..\\bin\\plugins\\$$PROVIDER\\$${TARGET}.xml\"

        } else {

            unix {

                QMAKE_POST_LINK += $${QMAKE_COPY} \"$$_PRO_FILE_PWD_/$${TARGET}.xml\" \"$$DESTDIR/$${TARGET}.xml\"

            } # unix

        } # win32

    } # macx

} # android

HEADERS +=

SOURCES +=


