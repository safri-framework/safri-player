#include "hackingwidgetplugin.h"

#include <QDebug>
#include "hackingwidget.h"

HackingWidgetPlugin::HackingWidgetPlugin()
{
}

bool HackingWidgetPlugin::initialize(QStringList &arguments)
{
    qDebug() << "Hello Hacking Widget...";
    HackingWidget *widget = new HackingWidget(0);

    widget->show();

    return true;
}

Q_EXPORT_PLUGIN2(HackingWidgetPlugin, HackingWidgetPlugin)