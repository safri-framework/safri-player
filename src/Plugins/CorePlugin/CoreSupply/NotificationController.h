#ifndef NOTIFICATIONCONTROLLER_H
#define NOTIFICATIONCONTROLLER_H

#include <QObject>
#include <QList>
#include "CorePlugin_global.h"
#include "ProgressNotification.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT NotificationController : public QObject
    {
        Q_OBJECT

        public:

            explicit NotificationController(QObject *parent = 0);

            ProgressNotification*   createProgressNotification(QString text, int min, int max);

        signals:

            void newNotification(Notification* notification);

        private:

            QList<ProgressNotification*> progressNotifications;
    };
}

#endif // NOTIFICATIONCONTROLLER_H
