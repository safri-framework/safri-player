#include "sqlstorageplugin.h"
#include "sqlstoragefactory.h"
#include <QtWidgets/QWidget>
using namespace Plugins;

SQLStoragePlugin::SQLStoragePlugin()
{
}

bool SQLStoragePlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new SQLStorageFactory(this));


    return true;
}

