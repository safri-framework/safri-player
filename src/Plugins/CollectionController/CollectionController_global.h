#ifndef COLLECTIONCONTROLLER_GLOBAL_H
#define COLLECTIONCONTROLLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COLLECTIONCONTROLLER_LIBRARY)
#  define COLLECTIONCONTROLLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COLLECTIONCONTROLLERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COLLECTIONCONTROLLER_GLOBAL_H
