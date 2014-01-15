#include "TabbedPlaylistWidget.h"
#include "ui_TabbedPlaylistWidget.h"

#include "playlistitemdelegate.h"
#include "Interfaces/ICore.h"
#include "Interfaces/IPlaybackController.h"
#include "Interfaces/IPlaylistStorage.h"
#include "Settings/SettingsManager.h"
#include "pluginmanager.h"
#include "PlaylistView.h"
#include "PlaylistModel.h"
#include "CoreData/Media.h"
#include "PlaylistTabWidget.h"
#include <QIcon>
#include <QMenu>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QFileDialog>
#include <QUrl>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>

TabbedPlaylistWidget::TabbedPlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::TabbedPlaylistWidget), currentPlaylistTabWidget(0), currentPlayingListView(0), newTabCount(1), currentState(Core::NODATA)
{
    ui->setupUi(this);
    PlaylistTabWidget* newTabWidget;

    connect(Core::ICore::playbackController(), SIGNAL(stateChanged(Core::playState)), this, SLOT(playbackControllerStateChanged(Core::playState)));
    connect(Core::ICore::instance(), SIGNAL( aboutToClose() ), this, SLOT( onClose() ) );


    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.tabbedplaylist");
    bool loadTabs = settings->getSetting("loadTabsOnStart").toBool();

    if ( loadTabs )
    {
        if ( !loadTabConfiguration() )
        {
            addNewPlaylist("Safri", Core::ICore::createPlaylist());
        }
    }
    else
    {
        addNewPlaylist("Safri", Core::ICore::createPlaylist());
    }



    //newTabWidget = addNewPlaylist("Safri", Core::ICore::createPlaylist());
    //addNewPlaylist("Wusel", newTabWidget);
    //addNewPlaylist("Dusel", newTabWidget);
    //addNewPlaylist("+", newTabWidget);
    //newTabWidget = addNewPlaylist("Neuer Tab " + QString::number(newTabCount) );
    //newTabCount++;
    //addNewPlaylist("+", newTabWidget);
    //addNewPlaylist("Dusel");
    //addNewPlaylist("+", newTabWidget);
    //newTabWidget = addNewPlaylist("Foo");
    //addNewPlaylist("Bar", newTabWidget);

}

TabbedPlaylistWidget::~TabbedPlaylistWidget()
{
    //qDebug() << "DESTRUKTOR TabbedPlaylistWidget";
    delete ui;
}

void TabbedPlaylistWidget::showPlaylist(QSharedPointer<Core::IPlaylist> playlist)
{

}

void TabbedPlaylistWidget::showCurrentPlaylist()
{

}

QSharedPointer<Core::IPlaylist> TabbedPlaylistWidget::newPlaylist()
{

}

void TabbedPlaylistWidget::isAnimated(bool animated)
{

}

void TabbedPlaylistWidget::itemsSelected(QList<Core::Item*> selection)
{

}

PlaylistTabWidget *TabbedPlaylistWidget::addNewPlaylist(QString name, PlaylistTabWidget *tabWidget)
{
    return this->addNewPlaylist(name, Core::ICore::createPlaylist(), tabWidget);
}

PlaylistTabWidget *TabbedPlaylistWidget::addNewPlaylist(QString name, QSharedPointer<Core::IPlaylist> playlist, PlaylistTabWidget *tabWidget)
{
    PlaylistView *view = new PlaylistView(name, tabWidget);

    PlaylistItemDelegate* itemDelegate = new PlaylistItemDelegate(this, view);
    view->setItemDelegate(itemDelegate);

    PlaylistModel *model;

    if (tabWidget == 0)
    {
        tabWidget = addNewTabWidget();
    }

    model = new PlaylistModel(playlist, view);
    view->setModel(model);
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlistViewDoubleClicked(QModelIndex)));

    QWidget* wrapperWidget = new QWidget();

    wrapperWidget->setProperty("ident", "PlaylistFrame");

    wrapperWidget->setLayout( new QHBoxLayout() );
    wrapperWidget->layout()->addWidget(view);

    int index = tabWidget->addTab(wrapperWidget, name);

    tabWidget->setCurrentIndex(index);

    return tabWidget;
}

bool TabbedPlaylistWidget::isCurrentPlayingView(QObject *listView)
{
    return currentPlayingListView == listView;
}

void TabbedPlaylistWidget::playlistViewDoubleClicked(const QModelIndex &index)
{
    PlaylistView *senderView = qobject_cast<PlaylistView*>(sender());

    if (senderView != 0)
    {
        PlaylistModel* playlistModel = qobject_cast<PlaylistModel*>(senderView->model());
        if (playlistModel != 0)
        {
            QSharedPointer<Core::IPlaylist> playlist = playlistModel->getPlaylist();
            playlist->setCurrentMedia(index.row());

            Core::Media* media = playlist->getCurrentMedia();

            PlaylistTabWidget *tabWidget = qobject_cast<PlaylistTabWidget*>(senderView->parent()->parent());
            if (tabWidget != 0)
            {
                removeCurrentTabIcon();
                currentPlaylistTabWidget = tabWidget;
                currentPlaylistIndex = currentPlaylistTabWidget->indexOf(senderView);
                currentPlayingListView = senderView;
            }

            Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();
            playbackConntroller->stopAction()->trigger();
            playbackConntroller->setPlaylist(playlist);
            playbackConntroller->playAction()->trigger();
        }
    }
}

void TabbedPlaylistWidget::lastTabRemoved(PlaylistTabWidget *tabWidget)
{
    if (currentPlaylistTabWidget == tabWidget)
    {
        currentPlaylistTabWidget = 0;
        currentPlayingListView = 0;
    }

    delete tabWidget;

    if (ui->splitter->count() < 1)
    {
        addNewTab(0);
    }
}

void TabbedPlaylistWidget::addNewTab(PlaylistTabWidget *tabWidget)
{
    addNewPlaylist("Neuer Tab " + QString::number(newTabCount), tabWidget);
    newTabCount++;
}

void TabbedPlaylistWidget::playbackControllerStateChanged(Core::playState state)
{
    if (state == currentState)
    {
        return;
    }

    currentState = state;

    setCurrentTabIcon();
}


void TabbedPlaylistWidget::onTabWidgetCostumContextMenuRequested(const QPoint &pos)
{
    PlaylistTabWidget *senderView = qobject_cast<PlaylistTabWidget*>(sender()->parent());

    QAction* requestedAction;

    QMenu contextMenu("Kontext menü", this);
    QAction splitAction("Teilen", &contextMenu);
    QAction newTabAction("Neuer Tab", &contextMenu);
    QAction closeTab("Tab schließen", &contextMenu);
    QAction renameTab("Umbenennen", &contextMenu);
    QAction savePlaylistAction("Playliste speichern", &contextMenu);
    QAction loadPlaylistAction("Playliste laden", &contextMenu);
    QAction savePlaylistStateAction("Tabs speichern", &contextMenu);

    if ( senderView->count() < 2)
    {
        splitAction.setEnabled(false);
    }

    QList<Core::IPlaylistStorage*> playlistStorage = PluginSystem::PluginManager::getObjects<Core::IPlaylistStorage>();

    if ( playlistStorage.size() < 1 )
    {
        savePlaylistAction.setEnabled(false);
        loadPlaylistAction.setEnabled(false);
        savePlaylistStateAction.setEnabled(false);
    }

    contextMenu.addAction(&newTabAction);
    contextMenu.addAction(&loadPlaylistAction);
    contextMenu.addSeparator();
    contextMenu.addAction(&savePlaylistStateAction);
    contextMenu.addSeparator();
    contextMenu.addAction(&savePlaylistAction);
    contextMenu.addAction(&renameTab);
    contextMenu.addAction(&splitAction);
    contextMenu.addAction(&closeTab);
    requestedAction = contextMenu.exec(senderView->tabBar()->mapToGlobal(pos));

    int tabIndex = senderView->tabBar()->tabAt(pos);

    if (requestedAction == &splitAction)
    {     
        splitTabWidgetView( senderView,  tabIndex);
    }
    else if (requestedAction == &newTabAction)
    {
        addNewTab(senderView);
    }
    else if (requestedAction == &closeTab)
    {
        senderView->removePlaylistTab(tabIndex);
    }
    else if (requestedAction == &renameTab)
    {
        senderView->editTabName(tabIndex);
    }
    else if (requestedAction == &savePlaylistAction)
    {
        savePlaylist( senderView->getPlaylist(tabIndex) );
    }
    else if (requestedAction == &loadPlaylistAction)
    {
        loadPlaylist(senderView);
    }
    else if (requestedAction == &savePlaylistStateAction)
    {
        saveTabConfiguration();
    }
}

void TabbedPlaylistWidget::splitTabWidgetView(PlaylistTabWidget *tabWidget, int index)
{
    PlaylistView* playlistView = qobject_cast<PlaylistView*>( tabWidget->widget(index)->findChildren<PlaylistView*>().at(0) );
    PlaylistTabWidget* newTab = addNewTabWidget();

    QWidget* wrapper = tabWidget->widget(index);
    tabWidget->removeTab( index );

    // add playlistView with original wrapperWidget
    newTab->addTab( wrapper, playlistView->getName() );

    if (currentPlayingListView == playlistView)
    {
        removeCurrentTabIcon();
        currentPlaylistTabWidget = newTab;
        currentPlaylistIndex = 0;
        setCurrentTabIcon();
    }

}

void TabbedPlaylistWidget::savePlaylist(QSharedPointer<Core::IPlaylist> playlist)
{
    QList<Core::IPlaylistStorage*> playlistStorage = PluginSystem::PluginManager::getObjects<Core::IPlaylistStorage>();
    QMap<QString, Core::IPlaylistStorage*> filterMap;
    QString fileFilter, selectedFilter, filter;
    QString saveFilename;
    Core::IPlaylistStorage* storage;

    if (playlistStorage.size() < 1)
    {
        return;
    }

    for (int i = 0; i < playlistStorage.size(); i++)
    {
        storage = playlistStorage.at(i);

        filter = storage->getDescription() + " (*." + storage->getFileExtension() + ")";
        filterMap.insert(filter, storage);

        if (i > 0)
        {
            fileFilter += ";;";
        }

        fileFilter += filter;
    }

    //qDebug() << "Filter: " << fileFilter;
    saveFilename = QFileDialog::getSaveFileName(this, "Playliste speichern", "", fileFilter, &selectedFilter);

    if ( saveFilename.isEmpty() )
    {
        return;
    }

    if ( selectedFilter.isEmpty() )
    {
        return;
    }

    storage = filterMap.value(selectedFilter);

    qDebug() << "save to Filename: " << saveFilename;
    qDebug() << "selected Filter: " << selectedFilter;

    if ( !saveFilename.endsWith("." + storage->getFileExtension(), Qt::CaseInsensitive ) )
    {
        saveFilename += "." + storage->getFileExtension();
    }

    storage->savePlaylist(saveFilename, playlist );
}

void TabbedPlaylistWidget::loadPlaylist(PlaylistTabWidget *tabWidget)
{
    QList<Core::IPlaylistStorage*> playlistStorage = PluginSystem::PluginManager::getObjects<Core::IPlaylistStorage>();
    QMap<QString, Core::IPlaylistStorage*> filterMap;
    QMap<QString, Core::IPlaylistStorage*> extensionMap;
    QString fileFilter, selectedFilter, filter;
    QString openFilename;
    Core::IPlaylistStorage* storage;
    QSharedPointer<Core::IPlaylist> loadedPlaylist;

    if ( playlistStorage.size() < 1 )
    {
        return;
    }

    for (int i = 0; i < playlistStorage.size(); i++)
    {
        storage = playlistStorage.at(i);

        filter = storage->getDescription() + " (*." + storage->getFileExtension() + ")";
        filterMap.insert(filter, storage);
        extensionMap.insert( storage->getFileExtension(), storage );

        if (i > 0)
        {
            fileFilter += ";;";
        }

        fileFilter += filter;
    }

    openFilename = QFileDialog::getOpenFileName(this, "Playliste öffnen", "", fileFilter, &selectedFilter);

    if ( openFilename.isEmpty() )
    {
        return;
    }

    if ( selectedFilter.isEmpty() )
    {
        QStringList filenameParts = openFilename.split(".");
        QString fileExtension = filenameParts.at( filenameParts.size() - 1 );

        storage = extensionMap.value(fileExtension);

        if (storage == 0)
        {
            return;
        }
    }

    storage = filterMap.value(selectedFilter);

    loadedPlaylist = storage->loadPlaylist(openFilename);

    //qDebug() << "TabbedPlaylistWidget::loaded Playlist with size: " << loadedPlaylist->getSize();

    addNewPlaylist( QFileInfo(openFilename).baseName() , loadedPlaylist, tabWidget);
}

QSharedPointer<Core::IPlaylist> TabbedPlaylistWidget::loadPlaylist(QString filename)
{
    QList<Core::IPlaylistStorage*> playlistStorage = PluginSystem::PluginManager::getObjects<Core::IPlaylistStorage>();
    Core::IPlaylistStorage* storage;

    QStringList filenameParts = filename.split(".");
    QString fileExtension = filenameParts.at( filenameParts.size() - 1 );

    for (int i = 0; i < playlistStorage.size(); i++)
    {
        storage = playlistStorage.at(i);

        //qDebug() << "Checking storage: " << storage->getDescription() + " extension: " << storage->getFileExtension();

        if ( storage->getFileExtension() == fileExtension )
        {
            //qDebug() << "Load Playlist with extension: " << fileExtension << " storage: " << playlistStorage.at(i)->getFileExtension();
            return playlistStorage.at(i)->loadPlaylist(filename);
        }
    }


    return Core::ICore::createPlaylist();
}

void TabbedPlaylistWidget::onClose()
{
    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.tabbedplaylist");
    bool saveTabs = settings->getSetting("saveTabsOnClose").toBool();

    if ( saveTabs )
    {
        saveTabConfiguration();
    }
}

void TabbedPlaylistWidget::saveTabConfiguration()
{
    QString storageDir = Core::ICore::storageDirectory() + "/playlists";
    QDir directory(storageDir);
    QWidget* widget;
    PlaylistTabWidget *tabWidget;
    QList<Core::IPlaylistStorage*> playlistStorage = PluginSystem::PluginManager::getObjects<Core::IPlaylistStorage>();
    Core::IPlaylistStorage* storage = 0;
    QString tabName, filename;
    QSharedPointer<Core::IPlaylist> playlist;
    QDomDocument domDoc;

    qDebug() << "saveTabConfiguration";

    for (int i = 0; i < playlistStorage.size(); i++)
    {
        if ( playlistStorage.at(i)->getFileExtension() == "m3u" )
        {
            storage = playlistStorage.at(i);
        }
    }

    if (storage == 0)
    {
        return;
    }

    if ( !directory.exists() )
    {
        directory.mkdir(storageDir);
    }
    else
    {
        foreach(QString dirFile, directory.entryList())
        {
            directory.remove(dirFile);
        }
    }

    QDomElement root = domDoc.createElement("safri-tabs");
    domDoc.appendChild(root);

    QDomElement domTabWidget, domTab;
    QDomText domFilename;

    for (int i = 0; i < ui->splitter->count(); i++)
    {
        widget = ui->splitter->widget(i);
        tabWidget = qobject_cast<PlaylistTabWidget*>(widget);

        domTabWidget = domDoc.createElement("tabwidget");

        for (int j = 0; j < tabWidget->count(); j++)
        {
            tabName = tabWidget->tabText(j);
            playlist = tabWidget->getPlaylist(j);

            filename = storageDir + "/" + tabName + "." + storage->getFileExtension();
            storage->savePlaylist(filename, playlist);

            domTab = domDoc.createElement("tab");
            domTab.setAttribute("name", tabName);

            domFilename = domDoc.createTextNode(filename);
            domTab.appendChild(domFilename);

            domTabWidget.appendChild(domTab);
        }

        root.appendChild(domTabWidget);
    }

    QFile file(storageDir + "/tab-config.xml");

    if( !file.open( QIODevice::ReadWrite ) )
    {
        qDebug() << "FILE NOT OPEN " << file.errorString();
        return;
    }

    QTextStream ts( &file );
    ts << domDoc.toString(4);

    file.close();
}

bool TabbedPlaylistWidget::loadTabConfiguration()
{
    QString storageDir = Core::ICore::storageDirectory() + "/playlists";
    QDir directory(storageDir);
    PlaylistTabWidget* newTabWidget;
    QSharedPointer<Core::IPlaylist> loadedPlaylist;

    if ( !directory.exists() )
    {
        return false;
    }

    QDomDocument domDoc("settingsdom");
    QDomElement domTabWidget, domTab;

    QFile file(storageDir + "/tab-config.xml");
    if (!file.open(QIODevice::ReadOnly))
         return false;

     if (!domDoc.setContent(&file))
     {
         file.close();

         return false;
     }
     file.close();

     QDomElement docElem = domDoc.documentElement();

     QDomNodeList tabWidgets = docElem.elementsByTagName("tabwidget");
     QDomNodeList tabs;
     QString tabName, filename;
     int tabWidgetCount = tabWidgets.size();
     int tabCount;

     for (int i = 0; i < tabWidgetCount; i++)
     {
        domTabWidget = tabWidgets.at(i).toElement();
        tabs = domTabWidget.elementsByTagName("tab");
        tabCount = tabs.size();

        qDebug() << "New TabWidget: ";

        newTabWidget = 0;

        for (int j = 0; j < tabCount; j++)
        {
            domTab = tabs.at(j).toElement();

            tabName = domTab.attribute("name");
            filename = domTab.text();

            qDebug() << "Tab " << tabName << " - " << domTab.text();

            loadedPlaylist = loadPlaylist(filename);

            newTabWidget = addNewPlaylist(tabName, loadedPlaylist, newTabWidget);
        }
     }

     return true;
}

PlaylistTabWidget *TabbedPlaylistWidget::addNewTabWidget()
{
    PlaylistTabWidget* tabWidget = new PlaylistTabWidget(ui->splitter);

    tabWidget->tabBar()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabWidget,              SIGNAL( lastTabRemoved(PlaylistTabWidget*) ),    this, SLOT( lastTabRemoved(PlaylistTabWidget*) ) );
    connect(tabWidget->tabBar(),    SIGNAL( customContextMenuRequested(QPoint) ),    this, SLOT( onTabWidgetCostumContextMenuRequested(QPoint) ) );
    connect(tabWidget,              SIGNAL( addNewTab(PlaylistTabWidget*) ),         this, SLOT( addNewTab(PlaylistTabWidget*) ) );
    ui->splitter->addWidget(tabWidget);


    int sameSize = ui->splitter->width() / ui->splitter->count();
    QList<int> sizes;
    for (int i = 0; i < ui->splitter->count(); i++)
    {
        sizes.append(sameSize);
    }
    ui->splitter->setSizes(sizes);


    return tabWidget;
}

void TabbedPlaylistWidget::removeCurrentTabIcon()
{
    if (currentPlaylistTabWidget != 0)
    {
        currentPlaylistTabWidget->setTabIcon( currentPlaylistIndex, QIcon() );
    }
}

void TabbedPlaylistWidget::setCurrentTabIcon()
{

    if (currentPlaylistTabWidget == 0)
    {
        return;
    }

    Core::ISafriSkin *skin = Core::ICore::skin();


    switch (currentState)
    {
        case Core::PLAY:

            if (skin)
            {
                currentPlaylistTabWidget->setTabIcon( currentPlaylistIndex, *skin->getIcon("TabPlayingIndicator") );
            }
            break;

        case Core::PAUSE:
        case Core::STOP:

            if (skin)
            {
                currentPlaylistTabWidget->setTabIcon( currentPlaylistIndex, *skin->getIcon("TabPauseIndicator") );
            }
            break;

        default:

            removeCurrentTabIcon();
            break;
    }
}
