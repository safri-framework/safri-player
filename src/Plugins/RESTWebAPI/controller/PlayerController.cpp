#include "PlayerController.h"
#include "iplaybackcontroller.h"
#include "icore.h"
#include <QtWidgets/QAction>
#include "StaticPlayerHelper.h"
#include <QJsonDocument>

PlayerController::PlayerController():pbController(Core::ICore::playbackController())
{


}



void PlayerController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    QAction* action = 0;
    if (request.getParameter("action")=="next")
    {
       action = pbController->nextAction();

    }
    else if (request.getParameter("action")=="previous")
    {
        action = pbController->previousAction();

    }

    else if (request.getParameter("action")=="pause")
    {
        action = pbController->pauseAction();

    }

    else if (request.getParameter("action")=="play")
    {
        action = pbController->playAction();
    }

    if(!action)
    {
        response.write("{success:false;}", true);
        return;
    }

    if(action->isEnabled())
    {
        action->trigger();
        response.write(QJsonDocument(StaticPlayerHelper::getStatus()).toJson(), true);
    }

}

