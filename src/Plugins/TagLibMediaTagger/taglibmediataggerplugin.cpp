#include "taglibmediataggerplugin.h"
#include <QDebug>
//#include "taglib.h"

using namespace Plugins;

TagLibMediaTaggerPlugin::TagLibMediaTaggerPlugin()
{
}

bool TagLibMediaTaggerPlugin::initialize(QStringList &arguments)
{


    return true;
}

Q_EXPORT_PLUGIN2(TagLibMediaTaggerPlugin, TagLibMediaTaggerPlugin)
