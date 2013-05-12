#include "RESTWebAPIPlugin.h"

#include "static.h"
#include "httplistener.h"
#include "requestmapper.h"
#include "staticfilecontroller.h"
#include "icore.h"
#include "controller/PlaylistHelper.h"

using namespace Plugins;

RESTWebAPIPlugin::RESTWebAPIPlugin()
{
}

bool RESTWebAPIPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    QString configFileName = Core::ICore::storageDirectory() + "/restwebapi.ini";
    PlaylistHelper::getInstance();

    // Configure template loader and cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat, this);
    templateSettings->beginGroup("templates");
    Static::templateLoader=new TemplateCache(templateSettings, this);

    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat, this);
    sessionSettings->beginGroup("sessions");
    Static::sessionStore=new HttpSessionStore(sessionSettings, this);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat, this);
    fileSettings->beginGroup("docroot");
    Static::staticFileController=new StaticFileController(fileSettings, this);

    // Configure and start the TCP listener
    qDebug("ServiceHelper: Starting service");
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
    listener=new HttpListener(listenerSettings,new RequestMapper(this), this);

    qDebug("ServiceHelper: Service has started");

    return true;
}
