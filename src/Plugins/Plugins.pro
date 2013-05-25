TEMPLATE = subdirs

CONFIG += ordered


SUBDIRS += \
        CorePlugin \
    	Playlist\
    	PlaybackController \
    	PhononBackend \
    	HackingWidget \
    	AudioCollection \
    	PlayerWidget \
    	MainWindow \
    	GUIController \
    	SidebarPluginTest \
    	PlaylistWidget \
    	SongtreeWidget \
    	CollectionController \
    	PlayerWidgetII \
        TagLibMediaTagger \
        SafriMobileGuiQML \
    ShoutCastPlugin \
    AudioSQLStorage \
#    TouchEventFilterPlugin \
    RESTWebAPI \
    LastFMInfoResolver \
    AlbumCovers
