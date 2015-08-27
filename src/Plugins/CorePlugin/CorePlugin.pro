#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T20:21:28
#
#-------------------------------------------------

QT       += gui widgets xml

TARGET = Core
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

DEFINES += COREPLUGIN_LIBRARY

SOURCES += CorePlugin.cpp \
    CoreData/Genre.cpp \
    CoreData/Artist.cpp \
    CoreData/Album.cpp \
    CoreData/Song.cpp \
    Interfaces/ICore.cpp \
    CoreData/DataItem.cpp \
    Interfaces/IPlayerWidgetFactory.cpp \
    Interfaces/ISideBarPlugin.cpp \
    Interfaces/IGUIController.cpp \
    Interfaces/IPlaylistWidget.cpp \
    Interfaces/IPlaylistWidgetFactory.cpp \
    Interfaces/ITreeItemType.cpp \
    Songtree/CoreItemTypes/TrackSongItemType.cpp \
    Songtree/CoreItemTypes/SongItemType.cpp \
    Songtree/CoreItemTypes/GenreItemType.cpp \
    Songtree/CoreItemTypes/DecadeItemType.cpp \
    Songtree/CoreItemTypes/ArtistItemType.cpp \
    Songtree/CoreItemTypes/AlbumItemType.cpp \
    Songtree/SongTree.cpp \
    Songtree/SongTreeItem.cpp \
    Songtree/ChangedFlags.cpp \
    Songtree/SongTreeModel.cpp \ 
    Songtree/CoreItemTypes/MediaCollectionItemType.cpp \
    Interfaces/IPlayerWidget.cpp \
    Interfaces/IMediaBackend.cpp \
    Interfaces/IMediaTagger.cpp \
    Interfaces/IMediaTaggerFactory.cpp \
    CoreData/MediaInfoContainer.cpp \
    Interfaces/IMediaCollection.cpp \
    Interfaces/IAudioCollection.cpp \
    Interfaces/IMediaInserter.cpp \
    CoreSupply/FileSystemInserter.cpp \
    Interfaces/IPlaylist.cpp \
    Songtree/SongTreeProxyModel.cpp \
    Interfaces/IMediaCollectionStorage.cpp \
    Interfaces/IMediaCollectionStorageFactory.cpp \
    Interfaces/IMediaCollectionFactory.cpp \
                                CoreSupply/InfoController.cpp \
				Interfaces/IInfoResolver.cpp \
				CoreSupply/InfoRequest.cpp \
				CoreSupply/AbstractInfoResolver.cpp \
    Settings/SettingsModule.cpp \
    Interfaces/ISettingsModule.cpp \
    Settings/SettingsManager.cpp \
    Settings/SettingsManagerDialog.cpp \
    Interfaces/ISettingsModuleWidget.cpp \
    Interfaces/IAssetService.cpp \
    CoreSupply/AssetController.cpp \
    CoreData/AlbumArtist.cpp \
    Interfaces/ITreeItem.cpp \
    CoreSupply/BasicTreeItem.cpp \
    Interfaces/IPlaybackController.cpp \
    Interfaces/ISafriSkin.cpp \
    Songtree/CoreItemTypes/ArtistSongItemType.cpp \ 
    Interfaces/IPlaylistStorage.cpp \
    CoreSupply/NotificationController.cpp \
    CoreSupply/Notification.cpp \
    CoreSupply/ProgressNotification.cpp \
    CoreData/MediaInfoContainerList.cpp

HEADERS += CorePlugin.h\
        CorePlugin_global.h \
    Interfaces/IPlaybackController.h \
    CoreData/Genre.h \
    CoreData/Artist.h \
    CoreData/Album.h \
    CoreData/Song.h\
    Interfaces/IPlaylist.h \
    Interfaces/ICore.h \
    CoreData/DataItem.h \
    CoreData/Item.h \
    CoreData/Media.h \
    Interfaces/IPlaylistFactory.h \
    Interfaces/IMediaCollection.h \
    Interfaces/IAudioCollection.h \
    Interfaces/IPlayerWidgetFactory.h \
    Interfaces/ISideBarPlugin.h \
    Interfaces/IGUIController.h \
    Interfaces/IPlaylistWidget.h \
    Interfaces/IPlaylistWidgetFactory.h \
    Interfaces/ITreeItemType.h \
    Songtree/CoreItemTypes/TrackSongItemType.h \
    Songtree/CoreItemTypes/SongItemType.h \
    Songtree/CoreItemTypes/GenreItemType.h \
    Songtree/CoreItemTypes/DecadeItemType.h \
    Songtree/CoreItemTypes/ArtistItemType.h \
    Songtree/CoreItemTypes/AlbumItemType.h \
    Songtree/SongTree.h \
    Songtree/SongTreeItem.h \
    Songtree/ChangedFlags.h \
    Songtree/SongTreeModel.h \
    Interfaces/ICollectionController.h \
    Songtree/CoreItemTypes/MediaCollectionItemType.h \
    Interfaces/IPlayerWidget.h \
    Interfaces/IMediaBackend.h \
    CoreData/MediaInfoContainer.h \
    Interfaces/IMediaTagger.h \
    Interfaces/IMediaTaggerFactory.h \
    Interfaces/IMediaInserter.h \
    CoreSupply/FileSystemInserter.h \
    Songtree/SongTreeProxyModel.h \
    Interfaces/IMediaCollectionStorage.h \
    Interfaces/IMediaCollectionStorageFactory.h \
    Interfaces/IMediaCollectionFactory.h \
    CoreData/Audio.h \
				CoreSupply/InfoController.h \
				Interfaces/IInfoResolver.h \
				CoreSupply/InfoRequest.h \
				CoreSupply/AbstractInfoResolver.h \
    Settings/SettingsModule.h \
    Interfaces/ISettingsModule.h \
    Settings/SettingsManager.h \
    Settings/SettingsManagerDialog.h \
    Interfaces/ISettingsModuleWidget.h \
    Interfaces/IAssetService.h \
    CoreSupply/AssetController.h \
    CoreData/AlbumArtist.h \
    Interfaces/ITreeItem.h \
    CoreSupply/BasicTreeItem.h \
    Interfaces/ISafriSkin.h \
    Songtree/CoreItemTypes/ArtistSongItemType.h \ 
    Interfaces/IPlaylistStorage.h \
    CoreSupply/NotificationController.h \
    CoreSupply/Notification.h \
    CoreSupply/ProgressNotification.h \
    CoreData/MediaInfoContainerList.h

OTHER_FILES += \
    Core.xml \
    coreplugin.json

FORMS += \
    Settings/SettingsManagerDialog.ui
