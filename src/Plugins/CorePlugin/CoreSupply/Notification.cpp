#include "Notification.h"

using namespace Core;

Notification::Notification(NotificationType type, QString text, QObject *parent) :
    QObject(parent), type(type), description(text)
{
}

NotificationType Notification::getType()
{
    return type;
}

QString Notification::getDescription()
{
    return description;
}
