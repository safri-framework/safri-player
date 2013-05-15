#include "playerwidgetII_plugin.h"
#include "plwidgetfactory.h"
#include "PlayerSettingsDialog.h"
#include <QFontDatabase>
#include <QDebug>
using namespace Plugins;

bool PlayerWidgetII_Plugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new PLWidgetFactory());
    addObject(new PlayerSettingsDialog(0));
    qDebug()<< QFontDatabase::addApplicationFont(":/font/SAFRI_UI/advent.ttf");
    return true;
}

PlayerWidgetII_Plugin::PlayerWidgetII_Plugin()
{
}

