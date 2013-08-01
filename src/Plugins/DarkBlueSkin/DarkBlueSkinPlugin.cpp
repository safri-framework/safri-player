#include "DarkBlueSkinPlugin.h"

#include <QDebug>
#include "MainWindowSkin.h"

using namespace Plugins;

DarkBlueSkinPlugin::DarkBlueSkinPlugin()
{
}


bool DarkBlueSkinPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    qDebug() << "DarkBlueSkin Plugin";

    MainWindowSkin* skin = new MainWindowSkin("DarkBlueSkin", ":stylesheet/stylesheet.css", this);

    addObject(skin);

    return true;
}
