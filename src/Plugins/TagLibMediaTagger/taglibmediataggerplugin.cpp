#include "taglibmediataggerplugin.h"
#include "taglibmediatagger.h"

using namespace Plugins;

TagLibMediaTaggerPlugin::TagLibMediaTaggerPlugin()
{
}

bool TagLibMediaTaggerPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new TaglibMediaTagger());
    return true;
}

Q_EXPORT_PLUGIN2(TagLibMediaTaggerPlugin, TagLibMediaTaggerPlugin)
