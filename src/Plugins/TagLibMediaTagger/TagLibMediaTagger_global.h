#ifndef TAGLIBMEDIATAGGER_GLOBAL_H
#define TAGLIBMEDIATAGGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TAGLIBMEDIATAGGER_LIBRARY)
#  define TAGLIBMEDIATAGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TAGLIBMEDIATAGGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TAGLIBMEDIATAGGER_GLOBAL_H