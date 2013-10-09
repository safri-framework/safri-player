#include "NotificationSidebarWidget.h"
#include "NotificationWidget.h"

NotificationSidebarWidget::NotificationSidebarWidget()
{

}

QWidget *NotificationSidebarWidget::getSideBarWidget()
{
    return 0;
}

QString NotificationSidebarWidget::getName()
{
    return "Notification";
}

QWidget *NotificationSidebarWidget::getMenuBarWidget()
{
    return new NotificationWidget();
}

bool NotificationSidebarWidget::isVisible()
{
    return true;
}
