#include "songtreesidebarwrapper.h"
#include <QPushButton>
#include "SongtreeWidget.h"
#include <QDebug>
SongTreeSidebarWrapper::SongTreeSidebarWrapper()
{
    this->name = "Songtree";
    QPushButton* button = new QPushButton();
    button->setCheckable(true);
    button->setText("SongTree");
    button->setProperty("style", QVariant("tabStyle"));
    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    menuBarWidget = button;
    sideBarWidget = new SongtreeWidget();
    //sideBarWidget->show();

    qDebug()<<"HIER BIN ICH";

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
