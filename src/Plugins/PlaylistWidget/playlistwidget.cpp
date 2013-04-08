#include "playlistwidget.h"
#include "ui_playlistwidget.h"
#include "playlistmodel.h"
#include <QDebug>
#include "../CorePlugin/iplaybackcontroller.h"
#include "../CorePlugin/icore.h"
#include "playlistitemdelegate.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::showPlaylist(QSharedPointer<Core::IPlaylist> playlist)
{
    QAbstractItemModel* model = ui->playlistView->model();
    delete model;
    playlistModel = new PlaylistModel(playlist, this);
    connect(playlistModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this->ui->playlistView, SLOT(dataChanged(QModelIndex,QModelIndex)));
    ui->playlistView->setModel(playlistModel);
    PlaylistItemDelegate* itemDelegate = new PlaylistItemDelegate(this, this);
    ui->playlistView->setItemDelegate(itemDelegate);

}


void PlaylistWidget::itemsSelected(QList<Core::Item *> selection)
{
    Q_UNUSED(selection)
}


void PlaylistWidget::isAnimated(bool animated)
{
    if(animated)
    {

//this->ui->playlistView->header()->setResizeMode(QHeaderView::Fixed);
    }
    else
    {
        this->ui->playlistView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded );
        this->ui->playlistView->setVerticalScrollBarPolicy ( Qt::ScrollBarAsNeeded );
    }
}


QSharedPointer<Core::IPlaylist> PlaylistWidget::newPlaylist()
{
    return QSharedPointer<Core::IPlaylist>();
}

bool PlaylistWidget::isCurrentPlayingPlaylist()
{
    return isCurrentPl;
}


void PlaylistWidget::showCurrentPlaylist()
{
    Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();
    QSharedPointer<Core::IPlaylist> pl = playbackConntroller->getPlaylist();
    if(pl && !pl.isNull())
    {
        setPlaylist(pl);
    }
}

void PlaylistWidget::on_playlistView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"PLAY";
    QSharedPointer<Core::IPlaylist> playlist = playlistModel->getPlaylist();
    playlist->setCurrentMedia(index.row());
    Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();
    playbackConntroller->stopAction()->trigger();
    playbackConntroller->setPlaylist(playlist);
    playbackConntroller->playAction()->trigger();
}

void PlaylistWidget::on_pushButton_clicked()
{
    QSharedPointer<Core::IPlaylist> pl = Core::ICore::createPlaylist();
    setPlaylist(pl);
}

void PlaylistWidget::on_pushButton_2_clicked()
{
    showCurrentPlaylist();
}

void PlaylistWidget::setPlaylist(QSharedPointer<Core::IPlaylist> pl)
{
    QAbstractItemModel* model = ui->playlistView->model();
     //TODO: Check if old Playlist will be deleted.
    if (!pl.isNull())
    {
        if(model)
        delete model;
        playlistModel = new PlaylistModel(pl, this);
        connect(playlistModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this->ui->playlistView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        ui->playlistView->setModel(playlistModel);

        if(pl.data() == Core::ICore::playbackController()->getPlaylist().data())
            isCurrentPl = true;
        else
            isCurrentPl = false;

        currentPL = pl;
    }
    else
    {
        qDebug()<<"model is empty ):";
    }
}
