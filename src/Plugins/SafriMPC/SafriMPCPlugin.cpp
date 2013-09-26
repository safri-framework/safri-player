#include "SafriMPCPlugin.h"
#include <QDebug>
#include "MPCInserter.h"
using namespace Plugins;

SafriMPC::SafriMPC()
{
}

bool SafriMPC::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    qDebug()<<"HALLO MPC";
    MPCInserter* test = new MPCInserter(this);

    return true;
}
