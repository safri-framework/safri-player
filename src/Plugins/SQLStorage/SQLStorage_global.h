#ifndef SQLSTORAGE_GLOBAL_H
#define SQLSTORAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLSTORAGE_LIBRARY)
#  define SQLSTORAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLSTORAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#define STORAGE_TYPE "org.safri.sqlite"

#endif // SQLSTORAGE_GLOBAL_H
