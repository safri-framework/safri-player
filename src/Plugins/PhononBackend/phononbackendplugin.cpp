#include "phononbackendplugin.h"

#include <QDebug>
#include "phononbackend.h"

using namespace Plugins;

PhononBackendPlugin::PhononBackendPlugin()
{
}

PhononBackendPlugin::~PhononBackendPlugin()
{
}

bool PhononBackendPlugin::initialize(QStringList __attribute__ ((unused)) &arguments)
{
    qDebug() << "PhononBackendPlugin::initialize(...)";
    PhononBackend *phonon_backend = new PhononBackend();

    addObject(phonon_backend);

    return true;
}

Q_EXPORT_PLUGIN2(PhononBackendPlugin, PhononBackendPlugin)
