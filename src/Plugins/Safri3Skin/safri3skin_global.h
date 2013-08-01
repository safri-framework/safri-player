#ifndef SAFRI3SKIN_GLOBAL_H
#define SAFRI3SKIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SAFRI3SKIN_LIBRARY)
#  define SAFRI3SKINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SAFRI3SKINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SAFRI3SKIN_GLOBAL_H
