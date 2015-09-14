#include "ProgressSidebarWidgetPlugin.h"
#include <QDebug>
#include <NotificationSidebarWidget.h>

ProgressSidebarWidgetPlugin::ProgressSidebarWidgetPlugin()
{
}

bool ProgressSidebarWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED( arguments )
    addObject(new NotificationSidebarWidget());
    return true;
}
