#ifndef DARKBLUEPLAYERWIDGET_GLOBAL_H
#define DARKBLUEPLAYERWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DARKBLUEPLAYERWIDGET_LIBRARY)
#  define DARKBLUEPLAYERWIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DARKBLUEPLAYERWIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DARKBLUEPLAYERWIDGET_GLOBAL_H