TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += CorePlugin
SUBDIRS += Playlist
SUBDIRS += PlaybackController
SUBDIRS += PhononBackend
#SUBDIRS += HackingWidget
SUBDIRS += PlayerWidget
SUBDIRS += MainWindow
SUBDIRS += GUIController
SUBDIRS += SidebarPluginTest
SUBDIRS += PlaylistWidget
SUBDIRS += SongtreeWidget
SUBDIRS += PlayerWidgetII
SUBDIRS += SafriMobileGuiQML
#SUBDIRS += TouchEventFilterPlugin
SUBDIRS += LastFMInfoResolver
SUBDIRS += AlbumCovers

!android {
SUBDIRS += TagLibMediaTagger
SUBDIRS += ShoutCastPlugin
SUBDIRS += AudioCollection
SUBDIRS += CollectionController
SUBDIRS += AudioSQLStorage
SUBDIRS += RESTWebAPI
}
