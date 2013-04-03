
#include "SongtreeWidget.h"
#include "ui_SongtreeWidget.h"
#include "../CorePlugin/Songtree/CoreItemTypes/albumitemtype.h"
#include "../CorePlugin/Songtree/CoreItemTypes/artistitemtype.h"
#include "../CorePlugin/Songtree/CoreItemTypes/songitemtype.h"
#include "../CorePlugin/Songtree/CoreItemTypes/genreitemtype.h"
#include "../CorePlugin/Songtree/CoreItemTypes/mediacollectionitemtype.h"
#include "../CorePlugin/Interfaces/IMediaCollection.h"
#include "../CorePlugin/iplaylist.h"
#include "../CorePlugin/iplaybackcontroller.h"
#include "Interfaces/iguicontroller.h"
#include "Interfaces/iplaylistwidget.h"
#include "../PluginSystem/pluginmanager.h"
#include <QDebug>
#include <QTreeView>
#include "../CorePlugin/icore.h"


SongtreeWidget::SongtreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongtreeWidget),
    collController(0)
{
    ui->setupUi(this);
    collController = ICore::collectionController();
    Q_ASSERT(collController);
    //TODO: No such slot
    //connect(collController, SIGNAL(mediaCollectionAdded(IMediaCollection*)), this, SLOT(newCollectionAvailable(QUrl)));
    connect(collController, SIGNAL(mediaCollectionRemoved(QUrl)), this, SLOT(removeCollection(QUrl)));
    buildHierarchy();
    loadAudioCollections();
    loadSongtreeModel();
    this->ui->treeView->setModel(model);
}

SongtreeWidget::~SongtreeWidget()
{
    delete ui;
}


void SongtreeWidget::loadAudioCollections()
{
   QList<IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
   for (int i = 0; i < mediaColl.size(); i++)
   {
       IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(mediaColl.at(i));
       if(tempAudioColl)
       {
           audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
       }
   }
}

void SongtreeWidget::loadSongtreeModel()
{
    QList<IAudioCollection*> audioCollList = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        songList.append(audioCollList.at(i)->getSongs());
    }

    tree = new SongTree(songList, treeHierarchy);

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        qDebug() << "CONNECT itemAdded";
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), tree, SLOT(addItem(Core::DataItem*)));
    }
    model = new SongTreeModel(tree, this);
}

void SongtreeWidget::buildHierarchy()
{
     treeHierarchy = new QList<ITreeItemType*>();
     treeHierarchy->append(new MediaCollectionItemType());
     treeHierarchy->append(new GenreItemType());
     treeHierarchy->append(new ArtistItemType());
     treeHierarchy->append(new AlbumItemType());
     treeHierarchy->append(new SongItemType());
}


void SongtreeWidget::newAudioCollectionAvailable(QUrl collURL)
{
    IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(collController->getMediaCollection(collURL));
    if (tempAudioColl)
    {
        audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
    }
}

void SongtreeWidget::removeCollection(QUrl collURL)
{
    Q_UNUSED(collURL)
}


void SongtreeWidget::on_treeView_doubleClicked(const QModelIndex &index)
{

    SongTreeItem* item = static_cast<SongTreeItem*>(index.internalPointer());
    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
    QList<Core::Item*> items;
    items.append(static_cast<Core::Item*>(item));

    playList->insertMediaAt(0,items);
    IPlaybackController* playbackController = Core::ICore::playbackController();
    Core::ICore::guiController()->getPlaylistWidget()->showPlaylist(playList);
    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playList);
    playbackController->playAction()->trigger();
}
