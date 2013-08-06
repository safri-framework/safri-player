#include "Safri3SkinPlugin.h"

#include <QDebug>
#include "Safri3Skin.h"

using namespace Plugins;

Safri3SkinPlugin::Safri3SkinPlugin()
{
}


bool Safri3SkinPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    qDebug() << "Safri3Skin Plugin";

    //MainWindowSkin* skin = new MainWindowSkin("Safri3Skin", ":stylesheet/stylesheet.css", this);
    //addObject(skin);

    addObject(new Safri3Skin() );

    return true;
}
