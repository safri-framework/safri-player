#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QString>
#include "CorePlugin_global.h"

namespace Core
{

    enum NotificationType
    {
        NotificationInfo,
        NotificationWarn,
        NotificationError,
        NotificationProgress,
        NotificationMediaInserterFinished
    };

    class COREPLUGINSHARED_EXPORT Notification : public QObject
    {
        Q_OBJECT
        public:

            explicit Notification(NotificationType type, QString text, QObject *parent = 0);

            NotificationType    getType();
            QString             getDescription();

        private:

            QString             description;
            NotificationType    type;

    };
}

#endif // NOTIFICATION_H
