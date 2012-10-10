#ifndef PLAYLIST_GLOBAL_H
#define PLAYLIST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLAYLIST_LIBRARY)
#  define PLAYLISTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLAYLISTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLAYLIST_GLOBAL_H
