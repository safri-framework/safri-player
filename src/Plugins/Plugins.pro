TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += CorePlugin
SUBDIRS += DarkBluePlayerWidget
SUBDIRS += M3UPlaylistStorage
SUBDIRS += Playlist
SUBDIRS += PlaybackController
SUBDIRS += PhononBackend
SUBDIRS += PlayerWidget
SUBDIRS += MainWindow
SUBDIRS += GUIController
SUBDIRS += SidebarPluginTest
SUBDIRS += PlaylistWidget
SUBDIRS += SongtreeWidget
SUBDIRS += PlayerWidgetII
#SUBDIRS += SafriMobileGuiQML
SUBDIRS += LastFMInfoResolver
SUBDIRS += AlbumCovers
SUBDIRS += AudioCollection
SUBDIRS += CollectionController
SUBDIRS += AudioSQLStorage
SUBDIRS += SafriApp
SUBDIRS += TagLibMediaTagger
SUBDIRS += Safri3Skin
SUBDIRS += DarkBlueSkin
SUBDIRS += TabbedPlaylistWidget

#SUBDIRS += HackingWidget
#SUBDIRS += TouchEventFilterPlugin

!android {
SUBDIRS += ShoutCastPlugin
SUBDIRS += RESTWebAPI
}
