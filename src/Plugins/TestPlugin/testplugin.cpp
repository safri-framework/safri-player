#include "testplugin.h"

#include <QDebug>

#include "CoreData/genre.h"

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
    qDebug() << "TestPlugin::initialize(...)";

    Core::Genre *genre = new Core::Genre(1, "Rock");

    qDebug() << genre->getName();
    qDebug() << Core::BaseDTO::typeToString(genre->getType());

    return true;
}

Q_EXPORT_PLUGIN2(TestPlugin, TestPlugin)
