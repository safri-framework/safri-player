#include "hackingwidget.h"
#include "ui_hackingwidget.h"
#include "icore.h"
#include "Interfaces/IMediaBackend.h"
#include "iplaybackcontroller.h"
#include <QToolBar>
#include "CoreData/song.h"
#include <QList>
#include "iplaylist.h"
#include "pluginmanager.h"
#include "Interfaces/iguicontroller.h"
#include "Interfaces/iplayerwidgetfactory.h"
#include "Interfaces/iplaylistwidget.h"
#include <QDebug>
#include "Songtree/songtreemodel.h"
#include "Interfaces/IAudioCollection.h"
#include "Songtree/songtree.h"
#include "Songtree/CoreItemTypes/artistitemtype.h"
#include "Songtree/CoreItemTypes/albumitemtype.h"
#include "Songtree/CoreItemTypes/songitemtype.h"
#include "CoreSupply/infocontroller.h"
#include "CoreSupply/InfoRequest.h"
#include <QTreeView>
#include <QVariant>
#include "Interfaces/ICollectionController.h"
#include "Interfaces/IMediaTagger.h"
#include "CoreSupply/filesysteminserter.h"
#include <QPixmap>

HackingWidget::HackingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HackingWidget)
{
    ui->setupUi(this);
}

HackingWidget::~HackingWidget()
{
    delete ui;
}

void HackingWidget::on_pushButton_clicked()
{
    Core::ICore::audioBackend()->setVolume( ui->lineEdit->text().toInt() );
}

void HackingWidget::on_pushButton_4_clicked()
{
    playbackController = Core::ICore::playbackController();

    QToolBar *bar = new QToolBar(this);

    bar->addAction(playbackController->previousAction());
    bar->addAction(playbackController->playPauseAction());
    bar->addAction(playbackController->stopAction());
    bar->addAction(playbackController->nextAction());
    bar->addAction(playbackController->playAction());
    bar->addAction(playbackController->pauseAction());

    ui->widget->layout()->addWidget(bar);


    Core::Song *testMp31 = new Core::Song(1, "Test", 2012, "x:/audacity-test-file.mp3", this);
    Core::Song *testMp32 = new Core::Song(2, "Test", 2012, "C:\\YellowLedbetter.mp3", this);

    QList<Core::Item*> songs;
    songs.append(testMp31);
    songs.append(testMp32);

    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();

    playList->insertMediaAt(0, songs);

    playbackController->setPlaylist(playList);
    connect(playbackController, SIGNAL(update(int)), this, SLOT(update(int)));


}

void HackingWidget::on_verticalSlider_sliderMoved(int position)
{
    Core::ICore::playbackController()->setVolume(position);
}

void HackingWidget::update(int currentTime)
{

    currentTime /= 1000;

    ui->label->setText( QString::number(currentTime) );
}

void HackingWidget::on_pushButton_5_clicked()
{
    int sec = ui->lineEdit_3->text().toInt();
    Core::ICore::playbackController()->seek(sec * 1000);
}

void HackingWidget::on_pushButton_6_clicked()
{


}

void HackingWidget::on_pushButton_7_clicked()
{
    PluginSystem::PluginManager::instance()->showPluginViewer();
}

void HackingWidget::on_pushButton_8_clicked()
{
    QList<Core::IPlayerWidgetFactory*> playerFactories = PluginSystem::PluginManager::instance()->getObjects<Core::IPlayerWidgetFactory>();
    if (playerFactories.size() > 0)
    {
        qDebug() << playerFactories.at(0)->getName();
        QWidget* player = playerFactories.at(0)->createWidget();
        player->show();
    }
}

void HackingWidget::on_pushButton_9_clicked()
{
    Core::Artist *artist = audioCollection->getArtistByID(1);

    qDebug() << "PlaylistModel Test for: " << artist->getName();
    QList<Core::Album*> albums = artist->getAlbums();
    QList<Core::Song*> songs;

    QSharedPointer<Core::IPlaylist> playlist = Core::ICore::createPlaylist();


    if (albums.size() > 0)
    {
        Core::Album* album = albums.at(0);
        songs = album->getSongs();

        for (int i = 0; i < songs.size(); i++)
        {
            playlist->appendMedia(songs.at(i));
        }
    }

    qDebug() << "Playlist size: " << playlist->getSize();
    Core::ICore::guiController()->getPlaylistWidget()->showPlaylist(playlist);
}

void HackingWidget::on_pushButton_10_clicked()
{
    on_pushButton_6_clicked();
    QTreeView* view = new QTreeView();
    qDebug()<<"1";
    qDebug()<<audioCollection->getSongs().size();
    QList<Song*> songlist =  audioCollection->getSongs();
    qDebug()<<"2";
    QList<ITreeItemType*>* itemList = new QList<ITreeItemType*>();
    qDebug()<<"3";
   itemList->append(new ArtistItemType());
    qDebug()<<"4";
   itemList->append(new AlbumItemType());
    qDebug()<<"5";
    itemList->append(new SongItemType());
qDebug()<<"6"<<songlist.size();

    SongTree* tree = new SongTree(songlist, itemList);
    qDebug()<<"7";
    SongTreeModel* model = new SongTreeModel(tree);
    qDebug()<<"8";
    view->setModel(model);
    qDebug()<<"9";
    view->show();



}

void HackingWidget::on_pushButton_11_clicked()
{
    ICollectionController *cc = Core::ICore::collectionController();
    QList<Core::IMediaTagger*> taggers = PluginSystem::PluginManager::instance()->getObjects<Core::IMediaTagger>();

    QList<IMediaCollection*> collections = cc->getCollections("org.safri.collection.audio");

    IMediaCollection *collection = collections.at(0);
    qDebug() << collection->getName();

    Core::FileSystemInserter* inserter = new Core::FileSystemInserter(collection);

    inserter->insertMedia(QUrl("/data/GunsNRoses/"), taggers.at(0));

  //  qDebug() << "Return from inserter.insertMedia";
}

void HackingWidget::on_pushButton_12_clicked()
{
    Controller::InfoController* controller = Core::ICore::infoController();
    Album* album = new Album(4711, "By the way");
    Artist* artist = new Artist(12, "Red Hot Chili Peppers");
    album->addArtist(artist);

    Core::InfoRequest* request = controller->getInfoForItem("org.safri.audio.album.cover", album);
    connect(request, SIGNAL(infoDataAvailable()), this, SLOT(infoSlot()));

}

void HackingWidget::infoSlot()
{
    Core::InfoRequest* req = qobject_cast<InfoRequest*>(sender());
    if(req)
    {
        QPixmap pixmap = req->getInfo().value<QPixmap>();
        this->ui->coveLabel->setPixmap(pixmap);
    }
}
