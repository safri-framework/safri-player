#include "NotificationWidget.h"
#include "ui_NotificationWidget.h"
#include "NotificationItem.h"
#include "Interfaces/ICore.h"
#include "CoreSupply/ProgressNotification.h"

NotificationWidget::NotificationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationWidget)
{
    ui->setupUi(this);
    notificationController = Core::ICore::notificationController();
    connect(notificationController, SIGNAL(newNotification(Notification*)), this, SLOT(showNotification(Notification*)));
}

NotificationWidget::~NotificationWidget()
{
    delete ui;
}

void NotificationWidget::showNotification(Notification *notification)
{

    ProgressNotification* progressNotification = qobject_cast<ProgressNotification*>(notification);
    if(progressNotification)
    {
        NotificationItem* item = new NotificationItem(progressNotification->getDescription());
        connect(item, SIGNAL(cancelClicked()), this, SLOT(cancelClicked()));
        notificatioMap.insert(progressNotification, item);
        connect(item, SIGNAL(destroyed()), this, SLOT(notificationDestroyed()));
        connect(item, SIGNAL(progressChanged(int, int)), this, SLOT(progressChanged(int,int)));
        this->layout()->addWidget(item);
    }
}

void NotificationWidget::notificationDestroyed()
{
    Notification* notification = qobject_cast<Notification*>(sender());
    if(notification)
    {
        NotificationItem* item = notificatioMap.value(notification, 0);
        if(item)
        {
            delete item;
        }
        notificatioMap.remove(notification);
    }
}

void NotificationWidget::progressChanged(int current, int max)
{
    ProgressNotification* notification = qobject_cast<ProgressNotification*>(sender());
    if(notification)
    {
        NotificationItem* item = notificatioMap.value(notification);
        item->setProgressValue(current, max);
    }
}

void NotificationWidget::cancelClicked()
{
    NotificationItem* item = qobject_cast<NotificationItem*>(sender());
    Notification* notification = notificatioMap.key(item,0);

}
