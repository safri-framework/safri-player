#include "PlayerController.h"
#include "Interfaces/IPlaybackController.h"
#include "Interfaces/ICore.h"
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
        else if (actionVariant == "stop")
        {
            action = pbController->stopAction();
        }
        else if (actionVariant == "getStatus")
        {
            response.write(QJsonDocument(JSONSerializer::getStatus()).toJson(), true);
            return;
        }
        else if (actionVariant == "seek")
        {
            int playTime = request.getParameter("playTime").toInt();
            if (playTime > 0)
            {
                pbController->seek(playTime);
            }
            return;
        }
        else if (actionVariant == "setVolume")
        {
            int volume = request.getParameter("volume").toInt();
            if (volume >= 0 && volume <= 100)
            {
                pbController->setVolume(volume);
            }
            return;
        }
        else if(actionVariant == "setShuffle")
        {
            QJsonDocument doc;
            QVariant enabled = request.getParameter("enabled");
            qDebug()<<"SHUFFLE "<<enabled.toBool();
            if(enabled.isValid())
            {
                doc.setObject(JSONSerializer::generateErrorObject("", "setShuffle", true));
                pbController->shuffleAction()->setChecked(enabled.toBool());
            }
            else
            {
                doc.setObject(JSONSerializer::generateErrorObject("missing parameters", "setShuffle", false));
            }
            response.write(doc.toJson(), true);
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

