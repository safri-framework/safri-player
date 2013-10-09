#include "ProgressNotification.h"

using namespace Core;

ProgressNotification::ProgressNotification(QString text, int min, int max, QObject *parent) :
    Notification(NotificationProgress, text, parent), minimum(min), maximum(max), currentProgress(min)
{
}

int ProgressNotification::getProgress()
{
    return currentProgress;
}

void ProgressNotification::cancel()
{
    Q_EMIT cancelRequested();
}

void ProgressNotification::finish(bool success)
{
    Q_EMIT finished(success);
}

void ProgressNotification::setProgress(int progress)
{
    currentProgress = progress;
    Q_EMIT progressChanged(currentProgress, maximum);
}

void ProgressNotification::incrementProgress(int increment)
{
    setProgress(currentProgress + increment);
}
