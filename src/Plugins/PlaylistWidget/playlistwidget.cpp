#include "playlistwidget.h"
#include "ui_playlistwidget.h"
#include "playlistmodel.h"
#include <QDebug>
#include "../CorePlugin/iplaybackcontroller.h"
#include "../CorePlugin/icore.h"
#include "playlistitemdelegate.h"
#include <QHeaderView>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);
    PlaylistItemDelegate* itemDelegate = new PlaylistItemDelegate(this, this);
    ui->playlistView->setItemDelegate(itemDelegate);
    ui->playlistView->setUniformRowHeights(false);
    connect(Core::ICore::playbackController(), SIGNAL(newPlaylistInstalled(QSharedPointer<Core::IPlaylist>)), this, SLOT(newPlaylist(QSharedPointer<Core::IPlaylist>)));
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::showPlaylist(QSharedPointer<Core::IPlaylist> playlist)
{
    setPlaylist(playlist);
    ui->playlistView->header()->setStretchLastSection(false);
    ui->playlistView->header()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->playlistView->header()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->playlistView->header()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->playlistView->header()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->playlistView->header()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->playlistView->header()->resizeSection(7,50);
    ui->playlistView->header()->resizeSection(6,43);
    ui->playlistView->header()->setSectionResizeMode(7, QHeaderView::Fixed);
    ui->playlistView->header()->setSectionResizeMode(6, QHeaderView::Fixed);
    ui->playlistView->header()->resizeSection(0,25);
    ui->playlistView->header()->resizeSection(1,25);


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
    isCurrentPl = true;
    ui->pushButton_2->setChecked(true);
    ui->pushButton_2->setDisabled(true);
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

void PlaylistWidget::newPlaylist(QSharedPointer<Core::IPlaylist> pl)
{
    qDebug()<<"SIGNAL";
    if(pl.data() ==  currentPL.data())
    {
        isCurrentPl = true;
        ui->pushButton_2->setChecked(true);
        ui->pushButton_2->setDisabled(true);
    }
    else
    {
        ui->pushButton_2->setChecked(false);
        ui->pushButton_2->setEnabled(true);
        isCurrentPl = false;
    }
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
        {
            isCurrentPl = true;
            ui->pushButton_2->setChecked(true);
            ui->pushButton_2->setDisabled(true);
        }
        else
        {
            ui->pushButton_2->setChecked(false);
            ui->pushButton_2->setEnabled(true);
            isCurrentPl = false;
        }
        currentPL = pl;
    }
    else
    {
        qDebug()<<"model is empty ):";
    }
}
