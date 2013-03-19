#include "CollectionControllerPlugin.h"
#include "CollectionController.h"
#include "../CorePlugin/icore.h"
#include <QDebug>

CollectionControllerPlugin::CollectionControllerPlugin()
{
}

bool CollectionControllerPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    QString databasePath = Core::ICore::storageDirectory() + "/sqlitedatabasev2.db";
    qDebug() << databasePath;

    Controller::CollectionController* collController = new Controller::CollectionController();

    addObject(collController);
    return collController->loadMediaCollection(databasePath);


return false;
}
