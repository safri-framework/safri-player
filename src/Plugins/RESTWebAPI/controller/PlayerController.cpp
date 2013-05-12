#include "PlayerController.h"
#include "iplaybackcontroller.h"
#include "icore.h"
#include <QtWidgets/QAction>
#include "JSONSerializer.h"
#include <QJsonDocument>

PlayerController::PlayerController():pbController(Core::ICore::playbackController())
{


}



void PlayerController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");

    QAction* action = 0;
    QVariant actionVariant = request.getParameter("action");

    if(actionVariant.isValid())
    {

        if (actionVariant =="next")
        {
           action = pbController->nextAction();

        }
        else if (actionVariant == "previous")
        {
            action = pbController->previousAction();

        }

        else if (actionVariant == "pause")
        {
            action = pbController->pauseAction();

        }

        else if (actionVariant == "play")
        {
            action = pbController->playAction();
        }
        else if(actionVariant == "getStatus")
        {
            response.write(QJsonDocument(JSONSerializer::getStatus()).toJson(), true);
            return;
        }

        if(!action)
        {
            response.write(QJsonDocument(JSONSerializer::generateErrorObject("No Action","Player action", false)).toJson(), true);
            return;
        }
        if(action->isEnabled())
        {
            action->trigger();
            response.write(QJsonDocument(JSONSerializer::getStatus()).toJson(), true);
        }
    }



}

