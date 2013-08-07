#ifndef TABBEDPLAYLISTWIDGET_GLOBAL_H
#define TABBEDPLAYLISTWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TABBEDPLAYLISTWIDGET_LIBRARY)
#  define TABBEDPLAYLISTWIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TABBEDPLAYLISTWIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TABBEDPLAYLISTWIDGET_GLOBAL_H