#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>
#include <CoreSupply/NotificationController.h>
#include <CoreSupply/Notification.h>
#include <QMap>

namespace Ui {
class NotificationWidget;
}

using namespace Core;

class NotificationItem;
class NotificationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit NotificationWidget(QWidget *parent = 0);
    ~NotificationWidget();

private slots:
    void showNotification(Notification* notification);
    void progressChanged(int current, int max);
    void cancelClicked();

private:
    Ui::NotificationWidget *ui;
    NotificationController* notificationController;
    QMap<Notification*, NotificationItem*> notificatioMap;
    void notificationDestroyed();

};

#endif // NOTIFICATIONWIDGET_H
