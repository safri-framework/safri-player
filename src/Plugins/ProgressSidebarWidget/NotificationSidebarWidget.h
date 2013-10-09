#ifndef NOTIFICATIONSIDEBARWIDGET_H
#define NOTIFICATIONSIDEBARWIDGET_H

#include "Interfaces/ISideBarPlugin.h"


class NotificationSidebarWidget : public Core::ISideBarPlugin
{
public:
    NotificationSidebarWidget();
    virtual QWidget* getSideBarWidget();
    virtual QString getName();
    virtual QWidget* getMenuBarWidget();

    // defines if widget will be visible at start
    virtual bool isVisible();

};

#endif // NOTIFICATIONSIDEBARWIDGET_H
