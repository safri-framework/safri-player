#include "sqlstorageplugin.h"
#include "sqlstoragefactory.h"

using namespace Plugins;

SQLStoragePlugin::SQLStoragePlugin()
{
}

bool SQLStoragePlugin::initialize(QStringList &arguments)
{
    addObject(new SQLStorageFactory(this));

    return true;
}

Q_EXPORT_PLUGIN2(SQLStoragePlugin, SQLStoragePlugin)
