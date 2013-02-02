#include "taglibmediataggerplugin.h"
#include <QDebug>
#include "taglib.h"
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>

using namespace Plugins;

TagLibMediaTaggerPlugin::TagLibMediaTaggerPlugin()
{
}

bool TagLibMediaTaggerPlugin::initialize(QStringList &arguments)
{
    qDebug() << "TagLibMediaTaggerPlugin::initialize()";

    TagLib::FileRef ref = TagLib::FileRef("/home/sascha/sweet.mp3");

    qDebug() << ref.tag()->artist().toCString();

    return true;
}

Q_EXPORT_PLUGIN2(TagLibMediaTaggerPlugin, TagLibMediaTaggerPlugin)
