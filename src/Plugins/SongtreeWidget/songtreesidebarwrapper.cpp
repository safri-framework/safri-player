#include "songtreesidebarwrapper.h"
#include <QPushButton>
#include "SongtreeWidget.h"
#include <QDebug>
#include <QIcon>
SongTreeSidebarWrapper::SongTreeSidebarWrapper()
{
    this->name = "Songtree";
    QPushButton* button = new QPushButton();
    button->setCheckable(true);
    button->setProperty("style", QVariant("tabStyle"));
    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    button->setIcon(QIcon(":icons/ressources/music_icon.png"));
    menuBarWidget = button;
    sideBarWidget = new SongtreeWidget();
    sideBarWidget->setMinimumHeight(300);
    //sideBarWidget->show();
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
