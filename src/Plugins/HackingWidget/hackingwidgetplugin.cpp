#include "hackingwidgetplugin.h"

#include <QDebug>
#include "hackingwidget.h"

using namespace Plugins;

HackingWidgetPlugin::HackingWidgetPlugin()
{
}

bool HackingWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    qDebug() << "Hello Hacking Widget...";
    HackingWidget *widget = new HackingWidget(0);

    widget->show();

    return true;
}


