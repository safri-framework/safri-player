#include "DarkBlueSkinPlugin.h"

#include <QDebug>

#include "DarkBlueSkin.h"

using namespace Plugins;

DarkBlueSkinPlugin::DarkBlueSkinPlugin()
{
}


bool DarkBlueSkinPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    qDebug() << "DarkBlueSkin Plugin";

 //   MainWindowSkin* skin = new MainWindowSkin("DarkBlueSkin", ":stylesheet/stylesheet.css", this);

 //   addObject(skin);
    addObject(new DarkBlueSkin());

    return true;
}
