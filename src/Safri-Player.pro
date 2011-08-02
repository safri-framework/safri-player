#-------------------------------------------------
#
# Project created by QtCreator 2011-01-24T23:18:10
#
#-------------------------------------------------

QT       += core gui sql phonon webkit mysql

TARGET = SafriPlayer
TEMPLATE = app
CONFIG  += qxt
QXT     += core gui


win32 {
    INCLUDEPATH += C:\taglib\include




    LIBS += -L"C:\taglib\lib"
    LIBS += -llibtag


}

unix {
	CONFIG += link_pkgconfig
	PKGCONFIG += taglib

	target.path += ../bin/
	INSTALLS += target
}

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
    databasesettingswidget.h \
    dtomapentry.h \
    databasecleaner.h \
    dtochanger.h \
    datatablemodel.h \
    showfolderinfilesystemhandler.h \
    settingsmodule.h \
    settingsmanager.h \
    selectedfilesystemindexactionhandler.h \
    settingsmodulewidget.h \
    settingsmanagerdialog.h \
    coversmw.h \
    viewsmw.h

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
    databasesettingswidget.cpp \
    dtomapentry.cpp \
    databasecleaner.cpp \
    dtochanger.cpp \
    datatablemodel.cpp \
    showfolderinfilesystemhandler.cpp \
    settingsmodule.cpp \
    settingsmanager.cpp \
    selectedfilesystemindexactionhandler.cpp \
    settingsmodulewidget.cpp \
    settingsmanagerdialog.cpp \
    coversmw.cpp \
    viewsmw.cpp

FORMS += \
    playerwidget.ui \
    mainwindow.ui \
    aboutdialog.ui \
    coversettingswidget.ui \
    databasesettingswidget.ui \
    settingsmanagerdialog.ui \
    coversmw.ui \
    viewsmw.ui
