#ifndef SHOUTCASTPLUGIN_GLOBAL_H
#define SHOUTCASTPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHOUTCASTPLUGIN_LIBRARY)
#  define SHOUTCASTPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHOUTCASTPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHOUTCASTPLUGIN_GLOBAL_H
