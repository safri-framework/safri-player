#ifndef SIDEBARPLUGINTEST_H
#define SIDEBARPLUGINTEST_H

#include "Interfaces/isidebarplugin.h"
#include <QWidget>

using namespace Core;
class SidebarPluginTest : public ISideBarPlugin
{
    Q_OBJECT

public:
    SidebarPluginTest(QString name, QWidget *parent = 0);
    ~SidebarPluginTest();

     QWidget* getSideBarWidget();
     QString getName();
     QWidget* getMenuBarWidget();
     bool isVisible();
private:

     QWidget* sideBarWidget;
     QWidget* menuBarWidget;
     QString name;

};

#endif // SIDEBARPLUGINTEST_H
