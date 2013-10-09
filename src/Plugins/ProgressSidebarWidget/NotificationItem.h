#ifndef NOTIFICATIONITEM_H
#define NOTIFICATIONITEM_H

#include <QWidget>

namespace Ui {
class NotificationItem;
}

class NotificationItem : public QWidget
{
    Q_OBJECT
    
public:
    explicit NotificationItem(QString progressName, QWidget *parent = 0);
    ~NotificationItem();
    void setProgressValue(int current, int max, int min = 0);

private:
    Ui::NotificationItem *ui;

signals:
    void cancelClicked();
};

#endif // NOTIFICATIONITEM_H
