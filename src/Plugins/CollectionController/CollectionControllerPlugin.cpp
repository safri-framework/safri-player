#include "CollectionControllerPlugin.h"
#include "CollectionController.h"
#include "../CorePlugin/icore.h"

CollectionControllerPlugin::CollectionControllerPlugin()
{
}

bool CollectionControllerPlugin::initialize(QStringList &arguments)
{

 /*  TODO
    Controller::CollectionController* collController = new Controller::CollectionController();
    QString databasePath = Core::ICore::storageDirectory() + "/sqlitedatabasev2.db";
    return collController->loadMediaCollection(databasePath);
*/

return false;
}
