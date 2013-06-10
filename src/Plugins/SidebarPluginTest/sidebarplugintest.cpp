#include "sidebarplugintest.h"
#include <QtWidgets/QPushButton>
#include <QVariant>
SidebarPluginTest::SidebarPluginTest(QString name, QWidget *parent)
{
    this->setParent(parent);
    this->name = name;
    QPushButton* button = new QPushButton(parent);
    button->setCheckable(true);
    button->setText(name);
    button->setProperty("style", QVariant("tabStyle"));
    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    menuBarWidget = button;
    sideBarWidget = new QWidget(parent);
//  sideBarWidget->show();
    sideBarWidget->setStyleSheet("background-color: red;");
}

SidebarPluginTest::~SidebarPluginTest()
{
}

QWidget *SidebarPluginTest::getSideBarWidget()
{
    return sideBarWidget;
}

QString SidebarPluginTest::getName()
{
    return name;
}

QWidget *SidebarPluginTest::getMenuBarWidget()
{
    return menuBarWidget;
}

bool SidebarPluginTest::isVisible()
{
  QPushButton* btn =  qobject_cast<QPushButton*>(menuBarWidget);
  return btn->isChecked();
}
