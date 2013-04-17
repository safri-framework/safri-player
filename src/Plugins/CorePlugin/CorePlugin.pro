#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T20:21:28
#
#-------------------------------------------------

QT       += gui widgets

TARGET = Core
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

DEFINES += COREPLUGIN_LIBRARY

SOURCES += coreplugin.cpp \
    CoreData/genre.cpp \
    CoreData/artist.cpp \
    CoreData/album.cpp \
    CoreData/song.cpp \
    icore.cpp \
    CoreData/dataitem.cpp \
    CoreData/dataitemtablemodel.cpp \
    Interfaces/IStorageAdapter.cpp \
    Interfaces/IMediaCollectionBuilder.cpp \
    Interfaces/ITableModel.cpp \
    Interfaces/iplayerwidgetfactory.cpp \
    Interfaces/isidebarplugin.cpp \
    Interfaces/iguicontroller.cpp \
    Interfaces/iplaylistwidget.cpp \
    Interfaces/iplaylistwidgetfactory.cpp \
    Interfaces/itreeitemtype.cpp \
    Songtree/CoreItemTypes/tracksongitemtype.cpp \
    Songtree/CoreItemTypes/songitemtype.cpp \
    Songtree/CoreItemTypes/genreitemtype.cpp \
    Songtree/CoreItemTypes/decadeitemtype.cpp \
    Songtree/CoreItemTypes/artistitemtype.cpp \
    Songtree/CoreItemTypes/albumitemtype.cpp \
    Songtree/songtree.cpp \
    Songtree/songtreeitem.cpp \
    Songtree/changedflags.cpp \
    Songtree/songtreemodel.cpp \ 
    Interfaces/istorageadapterfactory.cpp \
    Songtree/CoreItemTypes/mediacollectionitemtype.cpp \
    Interfaces/IPlayerWidget.cpp \
    Interfaces/IMediaBackend.cpp \
    Interfaces/IMediaTagger.cpp \
    Interfaces/IMediaTaggerFactory.cpp \
    CoreData/mediainfocontainer.cpp \
    Interfaces/IMediaCollection.cpp \
    Interfaces/IAudioCollection.cpp \
    Interfaces/imediainserter.cpp \
    CoreSupply/filesysteminserter.cpp \
    iplaylist.cpp \
    Songtree/songtreeproxymodel.cpp \
    Interfaces/imediacollectionstorage.cpp \
    Interfaces/imediacollectionstoragefactory.cpp \
    Interfaces/imediacollectionfactory.cpp

HEADERS += coreplugin.h\
        CorePlugin_global.h \
    iplaybackcontroller.h \
    CoreData/genre.h \
    CoreData/artist.h \
    CoreData/album.h \
    CoreData/song.h\
    iplaylist.h \
    icore.h \
    CoreData/dataitem.h \
    CoreData/item.h \
    CoreData/media.h \
    Interfaces/IPlaylistFactory.h \
    Interfaces/IMediaCollection.h \
    Interfaces/IMediaCollectionBuilder.h \
    Interfaces/IStorageAdapter.h \
    Interfaces/IAudioCollection.h \
    CoreData/dataitemtablemodel.h \
    Interfaces/ITableModel.h \
    Interfaces/iplayerwidgetfactory.h \
    Interfaces/isidebarplugin.h \
    Interfaces/iguicontroller.h \
    Interfaces/iplaylistwidget.h \
    Interfaces/iplaylistwidgetfactory.h \
    Interfaces/itreeitemtype.h \
    Songtree/CoreItemTypes/tracksongitemtype.h \
    Songtree/CoreItemTypes/songitemtype.h \
    Songtree/CoreItemTypes/genreitemtype.h \
    Songtree/CoreItemTypes/decadeitemtype.h \
    Songtree/CoreItemTypes/artistitemtype.h \
    Songtree/CoreItemTypes/albumitemtype.h \
    Songtree/songtree.h \
    Songtree/songtreeitem.h \
    Songtree/changedflags.h \
    Songtree/songtreemodel.h \
    Interfaces/ICollectionController.h \
    Interfaces/istorageadapterfactory.h \
    Songtree/CoreItemTypes/mediacollectionitemtype.h \
    Interfaces/IPlayerWidget.h \
    Interfaces/IMediaBackend.h \
    CoreData/mediainfocontainer.h \
    Interfaces/IMediaTagger.h \
    Interfaces/IMediaTaggerFactory.h \
    Interfaces/imediainserter.h \
    CoreSupply/filesysteminserter.h \
    Songtree/songtreeproxymodel.h \
    Interfaces/imediacollectionstorage.h \
    Interfaces/imediacollectionstoragefactory.h \
    Interfaces/imediacollectionfactory.h \
    CoreData/audio.h

OTHER_FILES += \
    Core.xml \
    coreplugin.json

FORMS +=
