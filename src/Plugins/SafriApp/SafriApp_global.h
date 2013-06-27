#ifndef SAFRIAPP_GLOBAL_H
#define SAFRIAPP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SAFRIAPP_LIBRARY)
#  define SAFRIAPPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SAFRIAPPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SAFRIAPP_GLOBAL_H
