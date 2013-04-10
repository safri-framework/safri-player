#include "sqlstorageplugin.h"
#include "audiosqlstoragefactory.h"
#include <QtWidgets/QWidget>

using namespace Plugins;

SQLStoragePlugin::SQLStoragePlugin()
{
}

bool SQLStoragePlugin::initialize(QStringList &arguments)
{

    Q_UNUSED(arguments)

    addObject(new AudioSQLStorageFactory(this));

    return true;
}

