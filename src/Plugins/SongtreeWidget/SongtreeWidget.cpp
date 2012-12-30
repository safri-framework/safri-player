/*
#include "SongtreeWidget.h"
#include "ui_SongtreeWidget.h"
#include "../CorePlugin/Interfaces/IStorageAdapter.h"
#include "../CorePlugin/Interfaces/IMediaCollectionBuilder.h"
#include "../CorePlugin/Interfaces/IMediaCollection.h"
#include "../PluginSystem/pluginmanager.h"
#include <QDebug>
#include "core"

SongtreeWidget::SongtreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongtreeWidget)
{
    ui->setupUi(this);
    loadAudioCollection();
    if(audioCollection)
    {


    }

}

SongtreeWidget::~SongtreeWidget()
{
    delete ui;
}


void SongtreeWidget::loadAudioCollection()
{
    Core::IStorageAdapter* storageAdapter;
    QList<Core::IStorageAdapter*> objects = PluginSystem::PluginManager::instance()->getObjects<Core::IStorageAdapter>();


    if (objects.size() > 0)
    {
        storageAdapter = objects.at(0);
        qDebug() << storageAdapter->getStorageType();
    }

    QList<Core::IMediaCollectionBuilder*> collectionBuilders = PluginSystem::PluginManager::instance()->getObjects<Core::IMediaCollectionBuilder>();
    Core::IMediaCollection *mediaCollection;

    if (collectionBuilders.size() > 0)
    {
        Core::IMediaCollectionBuilder* builder = collectionBuilders.at(0);
        this->mediaCollection = builder->buildMediaCollection(storageAdapter);
    }
    else
    {
        qDebug() << "No Collection Builders found!";
    }

    audioCollection = qobject_cast<Core::IAudioCollection*>(mediaCollection);
}

void SongtreeWidget::loadSongtreeModel()
{

    model = new SongTreeModel();
}
*/
