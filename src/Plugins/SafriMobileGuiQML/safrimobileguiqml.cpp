#include "safrimobileguiqml.h"
#include <QDebug>
#include <QtWidgets/QWidget>
#include "safrimobileguiinstance.h"
using namespace Plugins;

SafriMobileGuiQML::SafriMobileGuiQML()
{

}

bool SafriMobileGuiQML::initialize(QStringList &arguments)
{
    SafriMobileGuiInstance* instance = new SafriMobileGuiInstance();

    Q_UNUSED(arguments)
    Q_UNUSED(instance)

    return true;
}

