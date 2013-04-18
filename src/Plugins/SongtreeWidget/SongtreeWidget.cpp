
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
#include <QtWidgets/QPushButton>

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
    //connect(collController, SIGNAL(mediaCollectionAdded(IMediaCollection*)), this, SLOT(newCollectionAvailable(QUrl)));

    /*QPushButton* button = new QPushButton();
    button->setParent(ui->lineEdit);
    button->setMinimumSize(20, 20);
    button->setMaximumSize(20,20);
    button->setText("");
    button->show();
    button->move(50, 5);
    */

    proxy = new SongtreeProxyModel();
    connect(collController, SIGNAL(mediaCollectionRemoved(QUrl)), this, SLOT(removeCollection(QUrl)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),  this, SLOT(loadSongtreeModel(int)));
    buildHierarchy();


    loadAudioCollections();
    loadSongtreeModel(0);
    //proxy->setSourceModel(model);
    proxy->setDynamicSortFilter(true);
    connect(this->ui->lineEdit, SIGNAL(textEdited(QString)), proxy, SLOT(setFilterRegExp(QString)));
    connect(proxy, SIGNAL(expandIndex(QModelIndex)), this->ui->treeView, SLOT(expand(QModelIndex)));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    this->ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->treeView->setModel(proxy);


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

void SongtreeWidget::loadSongtreeModel(int hierarchy)
{

    qDebug()<<hierarchy;
    if(songList.size() > 0)
    {
        songList.clear();
    }
    QList<IAudioCollection*> audioCollList = audioCollMap.values();
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
        qDebug() << "CONNECT itemAdded";
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), tree, SLOT(addItem(Core::DataItem*)));
    }

    if(model)
    {
        delete model;
        model = 0;
    }
    model = new SongTreeModel(tree, this);
    proxy->setSourceModel(model);
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
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());


    hierarchyList.insert(3, treeHierarchy);



    ui->comboBox->addItem("Collection > Genre > Artist > Album > Song");
    ui->comboBox->addItem("Genre > Artist > Album > Song");
    ui->comboBox->addItem("Artist > Album > Song");
    ui->comboBox->addItem("Album > Song");
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

    SongTreeItem* item = static_cast<SongTreeItem*>(proxy->mapToSource(index).internalPointer());
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
