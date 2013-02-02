#include "taglibmediataggerplugin.h"
#include <QDebug>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>

using namespace Plugins;

TagLibMediaTaggerPlugin::TagLibMediaTaggerPlugin()
{
}

bool TagLibMediaTaggerPlugin::initialize(QStringList &arguments)
{


    return true;
}

Q_EXPORT_PLUGIN2(TagLibMediaTaggerPlugin, TagLibMediaTaggerPlugin)
