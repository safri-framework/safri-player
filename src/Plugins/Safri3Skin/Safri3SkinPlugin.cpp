#include "Safri3SkinPlugin.h"

#include <QDebug>
#include "MainWindowSkin.h"

using namespace Plugins;

Safri3SkinPlugin::Safri3SkinPlugin()
{
}


bool Safri3SkinPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    qDebug() << "Safri3Skin Plugin";

    MainWindowSkin* skin = new MainWindowSkin("Safri3Skin", ":stylesheet/stylesheet.css", this);

    addObject(skin);

    return true;
}
