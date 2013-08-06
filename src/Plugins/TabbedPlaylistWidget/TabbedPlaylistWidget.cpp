#include "TabbedPlaylistWidget.h"
#include "ui_TabbedPlaylistWidget.h"

#include "icore.h"
#include "iplaybackcontroller.h"
#include "PlaylistView.h"
#include "PlaylistModel.h"
#include "CoreData/media.h"
#include "PlaylistTabWidget.h"
#include <QIcon>
#include <QMenu>

TabbedPlaylistWidget::TabbedPlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::TabbedPlaylistWidget), currentPlaylistTabWidget(0)
{
    ui->setupUi(this);
    PlaylistTabWidget* newTabWidget;

    connect(Core::ICore::playbackController(), SIGNAL(stateChanged(Core::playState)), this, SLOT(playbackControllerStateChanged(Core::playState)));

    newTabWidget = addNewPlaylist("Neu", Core::ICore::createPlaylist());
    //addNewPlaylist("Wusel", newTabWidget);
    addNewPlaylist("Dusel", newTabWidget);
    //addNewPlaylist("+", newTabWidget);
    newTabWidget = addNewPlaylist("Wusel");
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
    PlaylistView *view = new PlaylistView(tabWidget);
    PlaylistModel *model;

    if (tabWidget == 0)
    {
        tabWidget = new PlaylistTabWidget(ui->splitter);
        connect(tabWidget, SIGNAL(lastTabRemoved(PlaylistTabWidget*)), this, SLOT(lastTabRemoved(PlaylistTabWidget*)));
        tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(tabWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTabWidgetCostumContextMenuRequested(QPoint)));
        ui->splitter->addWidget(tabWidget);
    }

    qDebug() << "foo";
    model = new PlaylistModel(playlist, view);
    view->setModel(model);
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlistViewDoubleClicked(QModelIndex)));
    tabWidget->addTab(view, name);

    return tabWidget;
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

            qDebug() << media->getURL();

            Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();
            playbackConntroller->stopAction()->trigger();
            playbackConntroller->setPlaylist(playlist);
            playbackConntroller->playAction()->trigger();

            PlaylistTabWidget *tabWidget = qobject_cast<PlaylistTabWidget*>(senderView->parent()->parent());
            if (tabWidget != 0)
            {
                if (currentPlaylistTabWidget != 0)
                {
                    currentPlaylistTabWidget->setTabIcon(currentPlaylistIndex, QIcon());
                }
                currentPlaylistTabWidget = tabWidget;
                currentPlaylistIndex = currentPlaylistTabWidget->indexOf(senderView);
                tabWidget->setTabIcon(currentPlaylistIndex, QIcon(":/icons/ressources/play_icon_little.png"));
            }
        }
    }
}

void TabbedPlaylistWidget::lastTabRemoved(PlaylistTabWidget *tabWidget)
{
    if (currentPlaylistTabWidget == tabWidget)
    {
        currentPlaylistTabWidget = 0;
    }

    delete tabWidget;

    if (ui->splitter->count() < 1)
    {
        addNewPlaylist("Neu");
    }
}

void TabbedPlaylistWidget::playbackControllerStateChanged(Core::playState state)
{
    if (currentPlaylistTabWidget != 0)
    {
        switch (state)
        {
            case Core::PLAY:
                currentPlaylistTabWidget->setTabIcon(currentPlaylistIndex, QIcon(":/icons/ressources/play_icon_little.png"));
                break;
            case Core::PAUSE:
                currentPlaylistTabWidget->setTabIcon(currentPlaylistIndex, QIcon(":/icons/ressources/pause_icon_little.png"));
                break;
            default:
                break;
        }
    }
}


void TabbedPlaylistWidget::onTabWidgetCostumContextMenuRequested(const QPoint &pos)
{
    PlaylistTabWidget *senderView = qobject_cast<PlaylistTabWidget*>(sender());

    QMenu contextMenu("Kontext menü", this);
    QAction splitAction("Teilen", this);
    //connect(&splitAction, SIGNAL(triggered()), this, SLOT(onTabSplit()));

    contextMenu.addAction(new QAction("Neuer Tab", this));
    contextMenu.addSeparator();
    contextMenu.addAction(new QAction("Umbenennen", this));
    contextMenu.addAction(&splitAction);
    contextMenu.addAction(new QAction("Tab schließen", this));
    contextMenu.exec(senderView->mapToGlobal(pos));
}
