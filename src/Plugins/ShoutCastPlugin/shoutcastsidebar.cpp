#include "shoutcastsidebar.h"
#include <QtWidgets/QPushButton>
#include <QtWebKit>
#include <QtWebKitWidgets/QWebView>
#include <QDebug>
#include "icore.h"
#include "iplaybackcontroller.h"
#include <QIcon>

ShoutCastSideBar::ShoutCastSideBar(QWidget *parent)
{
    this->setParent(parent);

    this->name = name;
    QPushButton* button = new QPushButton(parent);
    button->setCheckable(true);
    button->setText(name);
    button->setProperty("style", QVariant("tabStyle"));
    button->setIcon(QIcon(":/Shoutcast.png"));
    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    menuBarWidget = button;
    sideBarWidget = new QWebView();

    sideBarWidget->load(QUrl("http://www.liveradio.de/"));
    sideBarWidget->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(sideBarWidget, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClicked(QUrl)));
    opener = new PlsOpener(this);
}

ShoutCastSideBar::~ShoutCastSideBar()
{
    delete sideBarWidget;
}

QWidget *ShoutCastSideBar::getSideBarWidget()
{
    return sideBarWidget;
}


QString ShoutCastSideBar::getName()
{
    return name;
}

QWidget *ShoutCastSideBar::getMenuBarWidget()
{
    return menuBarWidget;
}

bool ShoutCastSideBar::isVisible()
{
    QPushButton* btn =  qobject_cast<QPushButton*>(menuBarWidget);
    return btn->isChecked();
}

void ShoutCastSideBar::linkClicked(QUrl url)
{
    qDebug()<<"LINK CLICKED"<< url;
    //opener->playPlsFromWebUrl(QUrl("http://www.soundcloud.com"));
    if(url.toString().contains(".pls"))
    {
        opener->playPlsFromWebUrl(url);
    }
    else
       sideBarWidget->load(url);
}
