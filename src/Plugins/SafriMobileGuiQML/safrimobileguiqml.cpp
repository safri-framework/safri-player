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
    qDebug()<<"HalloPlugin LALA";
    SafriMobileGuiInstance* instance = new SafriMobileGuiInstance();

}

