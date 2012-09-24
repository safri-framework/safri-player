#include "testplugin.h"

#include <QDebug>

TestPlugin::TestPlugin()
{
    qDebug() << "TestPlugin()";
}

TestPlugin::~TestPlugin()
{
    qDebug() << "~TestPlugin";
}

bool TestPlugin::initialize(QStringList __attribute__ ((unused)) &arguments)
{
    qDebug() << "TestPlugin::initialize(...): 42";
    return true;
}

Q_EXPORT_PLUGIN2(TestPlugin, TestPlugin)
