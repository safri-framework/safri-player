#include "songtreetabwidget.h"

#include <QDebug>
#include <QMenu>
#include <QTabBar>
#include <QSignalMapper>

#include "settingsmanager.h"
#include "settingsmodule.h"

SongtreeTabWidget::SongtreeTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
}


void SongtreeTabWidget::customContextMenuRequested(QPoint pos)
{
    int tab = this->tabBar()->tabAt(pos);

    if (tab < 3)
    {
        QSignalMapper* signalMapper = new QSignalMapper(this);

        this->setCurrentIndex(tab);
        QAction* action;

        QMenu* menu = new QMenu();

        QMenu* subMenu;

        subMenu = menu->addMenu("Gruppieren nach...");

        action = subMenu->addAction("Genre/Interpret/Album", signalMapper, SLOT(map()));
        signalMapper->setMapping(action, "GENRE;ARTIST;ALBUM;SONG");

        action = subMenu->addAction("Genre/Interpret", signalMapper, SLOT(map()));
        signalMapper->setMapping(action, "GENRE;ARTIST;SONG");

        action = subMenu->addAction("Genre/Dekade/Interpret", signalMapper, SLOT(map()));
        signalMapper->setMapping(action, "GENRE;DECADE;ARTIST;SONG");

        action = subMenu->addAction("Interpret/Album", signalMapper, SLOT(map()));
        signalMapper->setMapping(action, "ARTIST;ALBUM;SONG");

        action = subMenu->addAction("Album", signalMapper, SLOT(map()));
        signalMapper->setMapping(action, "ALBUM;SONG");

        menu->addSeparator();
        menu->addAction("Benutzerdefinierte Gruppierung");

        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(changeCurrentTreeviewHierarchy(QString)));

        menu->exec(QCursor::pos());
    }
}

void SongtreeTabWidget::changeCurrentTreeviewHierarchy(QString hierarchy)
{
    //qDebug() << this->currentIndex() << " -> " << hierarchy;

    int index = this->currentIndex() + 1;

    SettingsManager* sm = SettingsManager::getInstance();

    sm->getModule("core.view")->setSetting("treeview" + QString::number(index) + "Hierarchy", hierarchy);
    sm->saveSettings();

}
