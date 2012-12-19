#include "playlistwidget.h"
#include "ui_playlistwidget.h"
#include "playlistmodel.h"
#include <QDebug>

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

void PlaylistWidget::showPlaylist(Core::IPlaylist *playlist)
{
    QAbstractItemModel* model = ui->playlistView->model();
    delete model;

    qDebug() << "PlaylistWidget::showPlaylist()";

    model = new PlaylistModel(playlist, this);
    ui->playlistView->setModel(model);
}


void PlaylistWidget::itemsSelected(QList<Core::Item *> selection)
{
}


Core::IPlaylist *PlaylistWidget::newPlaylist()
{
    return 0;
}


void PlaylistWidget::showCurrentPlaylist()
{
}
