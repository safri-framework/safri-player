
#include "SongtreeWidget.h"
#include "ui_SongtreeWidget.h"
#include "../CorePlugin/Songtree/CoreItemTypes/AlbumItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/ArtistItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/SongItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/GenreItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/DecadeItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/MediaCollectionItemType.h"
#include "../CorePlugin/Songtree/CoreItemTypes/ArtistSongItemType.h"
#include "../CorePlugin/Interfaces/IMediaCollection.h"
#include "Interfaces/IPlaylist.h"
#include "Interfaces/IPlaybackController.h"
#include "Interfaces/IGUIController.h"
#include "Interfaces/IPlaylistWidget.h"
#include "../PluginSystem/pluginmanager.h"
#include <QDebug>
#include <QTreeView>
#include "Interfaces/ICore.h"
#include <QtWidgets/QPushButton>
#include <songtreeitemdelegate.h>


SongtreeWidget::SongtreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongtreeWidget),
    collController(0),
    model(0),
    tree(0)
{
    ui->setupUi(this);
    collController = ICore::collectionController();
    Q_ASSERT(collController);
    //TODO: No such slot
    connect(collController, SIGNAL(mediaCollectionAdded(IMediaCollection*)), this, SLOT(addNewCollection(IMediaCollection*)));

    searchProxy = new SongtreeProxyModel();

    connect(collController, SIGNAL(mediaCollectionRemoved(QUrl)), this, SLOT(removeCollection(QUrl)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),  this, SLOT(loadSongtreeModel(int)));
    buildHierarchy();
    loadSongtreeModel(0);
    //proxy->setSourceModel(model);
    searchProxy->setDynamicSortFilter(true);
    searchProxy->sort(0);
    connect(this->ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(textEdited(QString)));
    //connect(searchProxy, SIGNAL(expandIndex(QModelIndex)), this->ui->treeView, SLOT(expand(QModelIndex)));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    this->ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->treeView->setModel(searchProxy);
    this->ui->treeView->setItemDelegate(new SongTreeItemDelegate(this));
}

SongtreeWidget::~SongtreeWidget()
{
    delete ui;
}


void SongtreeWidget::textEdited(QString string)
{
    this->ui->treeView->expandAll();
    searchProxy->setFilterRegExp(string);
    if(string == "")
    {
        returnPressed();
    }
}

void SongtreeWidget::loadSongtreeModel(int hierarchy)
{
    QList<IAudioCollection*> audioCollList;
    QList<IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
    for (int i = 0; i < mediaColl.size(); i++)
    {
        IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(mediaColl.at(i));
        if(tempAudioColl)
        {
            audioCollList.append(tempAudioColl);
        }
    }

    qDebug()<<hierarchy;
    if(songList.size() > 0)
    {
        songList.clear();
    }
    // = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        songList.append(audioCollList.at(i)->getSongs());
    }

    if(tree)
    {
        delete tree;
        tree = 0;
    }
    tree = new SongTree(songList, hierarchyList.value(hierarchy));

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        //qDebug() << "CONNECT itemAdded";
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), tree, SLOT(addItem(Core::DataItem*)));
    }

    if(model)
    {
        delete model;
        model = 0;
    }
    model = new SongTreeModel(tree, this);
    searchProxy->setSourceModel(model);
}

void SongtreeWidget::buildHierarchy()
{
     QList<ITreeItemType*>* treeHierarchy = new QList<ITreeItemType*>();
     treeHierarchy->append(new MediaCollectionItemType());
     treeHierarchy->append(new GenreItemType());
     treeHierarchy->append(new ArtistItemType());
     treeHierarchy->append(new AlbumItemType());
     treeHierarchy->append(new SongItemType());


    hierarchyList.insert(0, treeHierarchy);




    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new GenreItemType());
    treeHierarchy->append(new ArtistItemType());
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());


    hierarchyList.insert(1, treeHierarchy);

    treeHierarchy = new QList<ITreeItemType*>();

    treeHierarchy->append(new ArtistItemType());
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());

    hierarchyList.insert(2, treeHierarchy);


    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new DecadeItemType());
    treeHierarchy->append(new GenreItemType());
    treeHierarchy->append(new ArtistItemType());
    treeHierarchy->append(new SongItemType());


    hierarchyList.insert(3, treeHierarchy);

    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());


    hierarchyList.insert(4, treeHierarchy);


    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new ArtistSongItemType());


    hierarchyList.insert(5, treeHierarchy);

    ui->comboBox->addItem("Collection > Genre > Artist > Album > Song");
    ui->comboBox->addItem("Genre > Artist > Album > Song");
    ui->comboBox->addItem("Artist > Album > Song");
    ui->comboBox->addItem("Dekade > Genre > Artist > Song");
    ui->comboBox->addItem("Album > Song");
    ui->comboBox->addItem("Artist - Song");
}


void SongtreeWidget::newAudioCollectionAvailable(QUrl collURL)
{
    IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(collController->getMediaCollection(collURL));
    if (tempAudioColl)
    {
        audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
    }
}

void SongtreeWidget::addNewCollection(IMediaCollection *collection)
{
    IAudioCollection* audioCollection = qobject_cast<IAudioCollection*>(collection);
    if(collection)
    {
        QList<Core::Song*> songs = audioCollection->getSongs();
        connect(audioCollection, SIGNAL(itemAdded(Core::DataItem*)), tree, SLOT(addItem(Core::DataItem*)));
        for(int i = 0; i <  songs.size(); i++)
        {
            tree->addSong(songs.at(i));
        }
    }
}

void SongtreeWidget::removeCollection(QUrl collURL)
{
    Q_UNUSED(collURL)
}

void SongtreeWidget::returnPressed()
{
    if(this->ui->lineEdit->text().size() > 0)
    {
        this->ui->treeView->expandAll();
    }
    else
    {
        this->ui->treeView->collapseAll();
    }
}


void SongtreeWidget::on_treeView_doubleClicked(const QModelIndex &index)
{

    SongTreeItem* item = static_cast<SongTreeItem*>(searchProxy->mapToSource(index).internalPointer());
    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
    QList<Core::Item*> items;
    items.append(static_cast<Core::Item*>(item));

    playList->insertMediaAt(0,items);
    IPlaybackController* playbackController = Core::ICore::playbackController();
    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playList);
    playbackController->playAction()->trigger();
    Core::ICore::guiController()->getPlaylistWidget()->showPlaylist(playList);
}
