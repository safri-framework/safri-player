#include "SafriAppPlugin.h"
#include <QDebug>
#include <QtWidgets/QWidget>
#include "SafriAppInstance.h"

using namespace Plugins;

SafriAppPlugin::SafriAppPlugin()
{

}

bool SafriAppPlugin::initialize(QStringList &arguments)
{
    SafriAppInstance* instance = new SafriAppInstance();

    Q_UNUSED(arguments)
    Q_UNUSED(instance)

    return true;
}

