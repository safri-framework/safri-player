#include "toucheventfilterplugin.h"
#include <QApplication>
#include "toucheventfilter.h"
bool Plugins::TouchEventFilterPlugin::initialize(QStringList &arguments)
{
    QApplication::instance()->installEventFilter(new TouchEventFilter());
    return true;
}


Plugins::TouchEventFilterPlugin::TouchEventFilterPlugin()
{
}
