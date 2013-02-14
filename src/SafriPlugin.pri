INCLUDEPATH += ../../PluginSystem
LIBS += -L../../../lib -lPluginSystem

isEmpty(PROVIDER) {
    PROVIDER = safri
}

DESTDIR = ../../../bin/plugins/$$PROVIDER

CONFIG += thread

# copy plugin spec to appropriate folder
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
        }
    }
}

HEADERS +=

SOURCES +=


