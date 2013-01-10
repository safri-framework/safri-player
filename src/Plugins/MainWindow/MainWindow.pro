#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T15:51:06
#
#-------------------------------------------------

TARGET = MainWindow
TEMPLATE = lib

DEFINES += MAINWINDOW_LIBRARY

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

SOURCES += \
    mainwindowplugin.cpp \
    mainwindow.cpp

HEADERS +=\
        MainWindow_global.h \
    mainwindowplugin.h \
    mainwindow.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEB1257ED
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MainWindow.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    stylesheet.css \
    MainWindow.xml

RESOURCES += \
    ressources.qrc
