#include "SafriAppPlugin.h"

#include "SafriAppInstance.h"

using namespace Plugins;

SafriAppPlugin::SafriAppPlugin()
{

}

bool SafriAppPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    // here we only create the actual app instance
    new SafriAppInstance();

    return true;
}

