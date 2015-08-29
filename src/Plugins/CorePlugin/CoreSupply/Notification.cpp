#include "Notification.h"

using namespace Core;

Notification::Notification(NotificationType type, QString text, QObject *parent) :
    QObject(parent), description(text), type(type)
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
