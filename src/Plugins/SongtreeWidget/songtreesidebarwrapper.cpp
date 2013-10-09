#include "songtreesidebarwrapper.h"
#include <QPushButton>
#include "SongtreeWidget.h"
#include <QDebug>
#include <QIcon>
#include <QBitmap>
#include <Interfaces/ISafriSkin.h>
#include "CoreSupply/NotificationController.h"
#include "Interfaces/ICore.h"

SongTreeSidebarWrapper::SongTreeSidebarWrapper()
{
    this->name = "Songtree";
    QPushButton* button = new QPushButton();
    button->setCheckable(true);
    button->setProperty("style", QVariant("tabStyle"));
    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));

    //button->setMask( QPixmap(":icons/ressources/music_icon.png").mask() );

    ISafriSkin* skin = Core::ICore::instance()->skin();
    if(skin)
    {
        QIcon* icon = skin->getIcon("Note");
        if(icon)
        button->setIcon(*icon);
    }
    else
    {
        button->setIcon(QIcon(":icons/ressources/music_icon2.png"));
    }
    menuBarWidget = button;
    sideBarWidget = new SongtreeWidget();
    sideBarWidget->setMinimumHeight(300);
    //sideBarWidget->show();


    connect(Core::ICore::notificationController(), SIGNAL( newNotification(Notification*) ), this, SLOT( notificationReceived(Notification*) ) );
}

QWidget *SongTreeSidebarWrapper::getSideBarWidget()
{
    return sideBarWidget;
}

QString SongTreeSidebarWrapper::getName()
{
    return name;
}

QWidget *SongTreeSidebarWrapper::getMenuBarWidget()
{
    return menuBarWidget;
}

bool SongTreeSidebarWrapper::isVisible()
{
      QPushButton* btn =  qobject_cast<QPushButton*>(menuBarWidget);
      return btn->isChecked();
}

void SongTreeSidebarWrapper::notificationReceived(Notification *notification)
{
    qDebug() << "SongTreeSidebarWrapper::notificationReceived(...)";
    if (notification->getType() == NotificationMediaInserterFinished)
    {
        menuBarWidget->click();
    }
}
