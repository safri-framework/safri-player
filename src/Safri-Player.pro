#-------------------------------------------------
#
# Project created by QtCreator 2011-01-24T23:18:10
#
#-------------------------------------------------

QT       += core gui sql phonon webkit mysql

TARGET = SafriPlayer0-2
TEMPLATE = app

INCLUDEPATH += C:\taglib\include
LIBS += -L"C:\taglib\lib"
LIBS += -llibtag

HEADERS += \
    taginserter.h \
    songtreemodel.h \
    songinserter.h \
    playlistview.h \
    playlistmodel.h \
    playlist.h \
    playerwidget.h \
    mainwindow.h \
    m3utranslator.h \
    databasedao.h \
    basedto.h \
    audiofile.h \
    aboutdialog.h \
    playercontext.h \
    coversettingswidget.h \
    settingsdialog.h \
    databasesettingswidget.h \
    dtomapentry.h \
    databasecleaner.h \
    dtochanger.h

SOURCES += \
    taginserter.cpp \
    songtreemodel.cpp \
    songinserter.cpp \
    playlistview.cpp \
    playlistmodel.cpp \
    playlist.cpp \
    playerwidget.cpp \
    mainwindow.cpp \
    main.cpp \
    m3utranslator.cpp \
    databasedao.cpp \
    basedto.cpp \
    audiofile.cpp \
    aboutdialog.cpp \
    playercontext.cpp \
    coversettingswidget.cpp \
    settingsdialog.cpp \
    databasesettingswidget.cpp \
    dtomapentry.cpp \
    databasecleaner.cpp \
    dtochanger.cpp

FORMS += \
    playerwidget.ui \
    mainwindow.ui \
    aboutdialog.ui \
    coversettingswidget.ui \
    settingsdialog.ui \
    databasesettingswidget.ui
