#include "ProgressSidebarWidgetPlugin.h"
#include <QDebug>
#include <NotificationSidebarWidget.h>

ProgressSidebarWidgetPlugin::ProgressSidebarWidgetPlugin()
{
}

bool ProgressSidebarWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED( arguments )
    qDebug()<<"hier bin ich!!";
    addObject(new NotificationSidebarWidget());
    return true;
}
