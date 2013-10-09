#ifndef SONGTREESIDEBARWRAPPER_H
#define SONGTREESIDEBARWRAPPER_H

#include "Interfaces/ISideBarPlugin.h"

using namespace Core;

namespace Core
{
    class Notification;
}
class QPushButton;

class SongTreeSidebarWrapper : public ISideBarPlugin
{
    Q_OBJECT
    public:
        SongTreeSidebarWrapper();
        QWidget* getSideBarWidget();
        QString getName();
        QWidget* getMenuBarWidget();
        bool isVisible();

    private slots:

        void notificationReceived(Notification* notification);


    private:

        QWidget* sideBarWidget;
        QPushButton* menuBarWidget;
        QString name;
};

#endif // SONGTREESIDEBARWRAPPER_H
