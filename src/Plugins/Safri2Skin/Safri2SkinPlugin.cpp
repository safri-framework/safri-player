#include "Safri2SkinPlugin.h"

#include <QDebug>
#include "MainWindowSkin.h"

using namespace Plugins;

Safri2SkinPlugin::Safri2SkinPlugin()
{
}


bool Safri2SkinPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    qDebug() << "Safri2Skin Plugin";

    MainWindowSkin* skin = new MainWindowSkin("Safri2Skin", ":stylesheet/stylesheet.css", this);

    addObject(skin);

    return true;
}
