#include "sqlstorageplugin.h"
#include "sqlstoragefactory.h"

using namespace Plugins;

SQLStoragePlugin::SQLStoragePlugin()
{
}

bool SQLStoragePlugin::initialize(QStringList &arguments)
{
    addObject(new SQLStorageFactory(this));
}

Q_EXPORT_PLUGIN2(SQLStoragePlugin, SQLStoragePlugin)
