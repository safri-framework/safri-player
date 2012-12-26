#include "sqlstorageplugin.h"
#include "sqlstorageadapter.h"

using namespace Plugins;

SQLStoragePlugin::SQLStoragePlugin()
{
}

bool SQLStoragePlugin::initialize(QStringList &arguments)
{
    SQLStorageAdapter *sqlAdapter = new SQLStorageAdapter(QUrl());

    addObject(sqlAdapter);
}

Q_EXPORT_PLUGIN2(SQLStoragePlugin, SQLStoragePlugin)
