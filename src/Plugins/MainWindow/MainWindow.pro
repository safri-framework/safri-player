#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T15:51:06
#
#-------------------------------------------------

TARGET = MainWindow
TEMPLATE = lib

DEFINES += MAINWINDOW_LIBRARY
QT += widgets
PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

SOURCES += \
    mainwindowplugin.cpp \
    mainwindow.cpp \
    MainWindowSkin.cpp \
    Interfaces/IMainWindowSkin.cpp

HEADERS +=\
        MainWindow_global.h \
    mainwindowplugin.h \
    mainwindow.h \
    MainWindowSkin.h \
    Interfaces/IMainWindowSkin.h

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    MainWindow.xml \
    mainwindow.json

RESOURCES += \
    ressources.qrc

