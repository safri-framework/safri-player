#include "taglibmediataggerplugin.h"
#include "taglibmediatagger.h"

// TODO
// ********************* temporary includes *******************
// only for testing the taglib plugin
#include <QList>
#include <QDebug>
#include "Interfaces/iguicontroller.h"
#include "Interfaces/iplaylistwidget.h"
#include "icore.h"

#include "../CorePlugin/CoreData/song.h"
#include "../CorePlugin/iplaylist.h"

#include "Interfaces/ICollectionController.h"
#include "Interfaces/IMediaTagger.h"
#include "CoreSupply/filesysteminserter.h"

#include "../../PluginSystem/pluginmanager.h"
// *************************************************************

using namespace Plugins;

TagLibMediaTaggerPlugin::TagLibMediaTaggerPlugin()
{
}

bool TagLibMediaTaggerPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new TaglibMediaTagger());

    // testing the plugin
    // *******************************************************
    Core::ICollectionController *cc = Core::ICore::collectionController();
    QList<Core::IMediaTagger*> taggers = PluginSystem::PluginManager::instance()->getObjects<Core::IMediaTagger>();

    QList<Core::IMediaCollection*> collections = cc->getCollections("org.safri.collection.audio");

    Core::IMediaCollection *collection = collections.at(0);
    qDebug() << collection->getName();

    Core::FileSystemInserter* inserter = new Core::FileSystemInserter(collection);

    if(taggers.size() > 0)
        inserter->insertMedia(QUrl("/mnt/sdcard/"), taggers.at(0));
    else
        qDebug()<<"No Media-Taggers found!";
    // *******************************************************


    return true;
}

