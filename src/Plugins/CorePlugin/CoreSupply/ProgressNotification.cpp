#include "ProgressNotification.h"

using namespace Core;

ProgressNotification::ProgressNotification(QString text, int min, int max, bool cancelable, QObject *parent) :
    Notification(NotificationProgress, text, parent), minimum(min), maximum(max), currentProgress(min), cancelabel(cancelable)
{
}

int ProgressNotification::getProgress()
{
    return currentProgress;
}

bool ProgressNotification::isCancelable()
{
    return cancelabel;
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
