#ifndef PROGRESSSIDEBARWIDGET_GLOBAL_H
#define PROGRESSSIDEBARWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PROGRESSSIDEBARWIDGET_LIBRARY)
#  define PROGRESSSIDEBARWIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PROGRESSSIDEBARWIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PROGRESSSIDEBARWIDGET_GLOBAL_H