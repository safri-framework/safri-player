#ifndef PROGRESSNOTIFICATION_H
#define PROGRESSNOTIFICATION_H

#include "Notification.h"

namespace Core
{

    class COREPLUGINSHARED_EXPORT ProgressNotification : public Notification
    {
        Q_OBJECT
        public:

            explicit ProgressNotification(QString text, int min, int max, QObject *parent = 0);

            int getProgress();

        signals:

            void finished(bool success);
            void cancelRequested();
            void progressChanged(int progress, int max);

        public slots:

            void cancel();
            void finish(bool success);
            void setProgress(int progress);
            void incrementProgress(int increment = 1);

        private:

            int minimum;
            int maximum;
            int currentProgress;

    };

}

#endif // PROGRESSNOTIFICATION_H
