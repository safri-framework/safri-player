#include "TabbedPlaylistWidget.h"
#include "ui_TabbedPlaylistWidget.h"

#include "playlistitemdelegate.h"
#include "icore.h"
#include "iplaybackcontroller.h"
#include "PlaylistView.h"
#include "PlaylistModel.h"
#include "CoreData/media.h"
#include "PlaylistTabWidget.h"
#include <QIcon>
#include <QMenu>
#include <QDebug>

TabbedPlaylistWidget::TabbedPlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::TabbedPlaylistWidget), currentPlaylistTabWidget(0), currentPlayingListView(0), newTabCount(1), currentState(Core::NODATA)
{
    ui->setupUi(this);
    PlaylistTabWidget* newTabWidget;

    connect(Core::ICore::playbackController(), SIGNAL(stateChanged(Core::playState)), this, SLOT(playbackControllerStateChanged(Core::playState)));

    newTabWidget = addNewPlaylist("Safri", Core::ICore::createPlaylist());
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
    tabWidget->addTab(view, name);

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

    if ( senderView->count() < 2)
    {
        splitAction.setEnabled(false);
    }

    contextMenu.addAction(&newTabAction);
    contextMenu.addSeparator();
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
}

void TabbedPlaylistWidget::splitTabWidgetView(PlaylistTabWidget *tabWidget, int index)
{
    PlaylistView* playlistView = qobject_cast<PlaylistView*>( tabWidget->widget(index) );
    PlaylistTabWidget* newTab = addNewTabWidget();

    tabWidget->removeTab( index );
    newTab->addTab( playlistView, playlistView->getName() );

    if (currentPlayingListView == playlistView)
    {
        removeCurrentTabIcon();
        currentPlaylistTabWidget = newTab;
        currentPlaylistIndex = 0;
        setCurrentTabIcon();
    }

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
