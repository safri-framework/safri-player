#include "NotificationController.h"

using namespace Core;

NotificationController::NotificationController(QObject *parent) :
    QObject(parent)
{
}

ProgressNotification *NotificationController::createProgressNotification(QString text, int min, int max)
{
    ProgressNotification* newProgress = new ProgressNotification(text, min, max, this);

    progressNotifications.append(newProgress);

    Q_EMIT newNotification(newProgress);

    return newProgress;
}
