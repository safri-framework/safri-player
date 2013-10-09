#include "NotificationController.h"

using namespace Core;

NotificationController::NotificationController(QObject *parent) :
    QObject(parent)
{
}

ProgressNotification *NotificationController::createProgressNotification(QString text, int min, int max, bool cancelable)
{
    ProgressNotification* newProgress = new ProgressNotification(text, min, max, cancelable);

    progressNotifications.append(newProgress);

    Q_EMIT newNotification(newProgress);

    return newProgress;
}

Notification *NotificationController::createNotification(NotificationType type, QString text)
{
    Notification *notification = new Notification(type, text);

    Q_EMIT newNotification(notification);

    return notification;
}
