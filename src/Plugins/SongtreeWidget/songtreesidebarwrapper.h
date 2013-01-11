#ifndef SONGTREESIDEBARWRAPPER_H
#define SONGTREESIDEBARWRAPPER_H

#include "Interfaces/isidebarplugin.h"

using namespace Core;

class SongTreeSidebarWrapper : public ISideBarPlugin
{
public:
    SongTreeSidebarWrapper();
    QWidget* getSideBarWidget();
    QString getName();
    QWidget* getMenuBarWidget();
    bool isVisible();
private:

    QWidget* sideBarWidget;
    QWidget* menuBarWidget;
    QString name;
};

#endif // SONGTREESIDEBARWRAPPER_H
