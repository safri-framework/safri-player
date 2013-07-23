#include "PlaylistController.h"
#include "PlaylistHelper.h"
#include "QJsonDocument"
#include <QDebug>
#include <QJsonObject>
#include "JSONSerializer.h"

PlaylistController::PlaylistController(){}

void PlaylistController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");

    if(request.getParameter("action") == "newPlaylist")
    {
        QJsonDocument doc;
        PlaylistHelper::getInstance()->newPlaylist();
        doc.setObject(JSONSerializer::generateErrorObject("", "newPlaylist", true));
    }

    else if(request.getParameter("action") == "insertItem")
    {
       QString collection = request.getParameter("collection");
       QString type = request.getParameter("type");
       int ID = request.getParameter("mediaID").toInt();
       int pos = request.getParameter("pos").toInt();
       PlaylistHelper::getInstance()->insertItem(pos, collection, ID);
    }

    else if(request.getParameter("action") == "appendItem")
    {


    }

    else if(request.getParameter("action") == "move")
    {
        bool ok1;
        bool ok2;
        int from;
        int to;
        QJsonDocument doc;
        QVariant variantFrom = request.getParameter("from");
        QVariant variantTo = request.getParameter("to");
        if(variantFrom.isValid() && variantTo.isValid())
        {
            from = variantFrom.toInt(&ok1);
            to = variantTo.toInt(&ok2);
            if(ok1 && ok2)
            {
                PlaylistHelper::getInstance()->moveSong(from, to);
                qDebug()<<"MOVE!!!";
                doc.setObject(JSONSerializer::generateErrorObject("", "move", true));
            }
            else
            {
                //wrong parameter
                doc.setObject(JSONSerializer::generateErrorObject("wrong parameters", "move", false));
            }
        }
        else
        {
            //missing parameter
            doc.setObject(JSONSerializer::generateErrorObject("missing parameters", "move", false));
        }
        response.write(doc.toJson());
    }

    else if(request.getParameter("action") == "setPlaylist")
    {
        PlaylistHelper::getInstance()->setAsCurrent();
    }

    else if(request.getParameter("action") == "getPlaylist")
    {
       QJsonDocument doc;
       doc.setArray(PlaylistHelper::getInstance()->getCurrentPlaylist());
       response.write(doc.toJson(), true);
    }
    else if(request.getParameter("action") == "getVersionID")
    {
       QJsonDocument doc;
       QJsonObject obj;
       obj.insert("currentVersionID", PlaylistHelper::getInstance()->getCurrentVersionID());
       doc.setObject(obj);
       response.write(doc.toJson(), true);
    }
    else if(request.getParameter("action") == "getPlayingPlaylist")
    {
       QJsonDocument doc;
       QJsonObject obj;
       obj.insert("playingPlaylist", PlaylistHelper::getInstance()->getPlayingPlaylist());
       doc.setObject(obj);
       response.write(doc.toJson(), true);
    }
}
