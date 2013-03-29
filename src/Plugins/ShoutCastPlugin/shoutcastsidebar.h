#ifndef SHOUTCASTSIDEBAR_H
#define SHOUTCASTSIDEBAR_H

#include "Interfaces/isidebarplugin.h"
#include <QtWidgets/QWidget>
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include "plsopener.h"
using namespace Core;
class ShoutCastSideBar : public ISideBarPlugin
{
    Q_OBJECT

public:
    ShoutCastSideBar(QWidget *parent = 0);
    ~ShoutCastSideBar();

     QWidget* getSideBarWidget();
     QString getName();
     QWidget* getMenuBarWidget();
     bool isVisible();
private:

     QWebView* sideBarWidget;
     QWidget* menuBarWidget;
     QString name;
     PlsOpener* opener;
private slots:
     void linkClicked(QUrl url);

};

#endif // SHOUTCASTSIDEBAR_H
