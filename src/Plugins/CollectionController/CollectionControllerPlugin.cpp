#include "CollectionControllerPlugin.h"
#include "CollectionController.h"
#include "../CorePlugin/icore.h"
#include "CollectionControllerSettingsDialog.h"
#include "Settings/SettingsManager.h"
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
    addObject(new CollectionControllerSettingsDialog(Core::ICore::settingsManager()->getModule("org.safri.collection")));

    return collController->loadMediaCollection(databasePath);


return false;
}
