#include "safrimobileguiqml.h"
#include <QDebug>
#include <QWidget>
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

Q_EXPORT_PLUGIN2(SafriMobileGuiQML, SafriMobileGuiQML)
