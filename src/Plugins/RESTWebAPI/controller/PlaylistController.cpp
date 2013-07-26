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

    else if(request.getParameter("action") == "deleteItem")
    {
        QJsonDocument doc;
        bool ok;
        int index = request.getParameter("index").toInt(&ok);
        if(ok && index < PlaylistHelper::getInstance()->getCurrentPlaylistSize())
        {
            PlaylistHelper::getInstance()->deleteItem(index);
            doc.setObject(JSONSerializer::generateErrorObject("", "deleteItem", true));
        }
        else
        {
            //wrong parameter
            doc.setObject(JSONSerializer::generateErrorObject("wrong parameters", "deleteItem", false));
        }
        response.write(doc.toJson(), true);
        qDebug()<<"DELETE";

    }

    else if(request.getParameter("action") == "playIndex")
    {
        qDebug()<<"PLAY";
        QJsonDocument doc;
        PlaylistHelper::getInstance()->playItem(request.getParameter("index").toInt());
        doc.setObject(JSONSerializer::generateErrorObject("", "move", true));
        response.write(doc.toJson(), true);
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
        response.write(doc.toJson(), true);
    }

    else if(request.getParameter("action") == "setPlaylist")
    {
        QJsonDocument doc;
        PlaylistHelper::getInstance()->setAsCurrent();
        doc.setObject(JSONSerializer::generateErrorObject("", "setPlaylist", true));
        response.write(doc.toJson(),true);
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
       obj.insert("currentPlayingSongIndex", PlaylistHelper::getInstance()->getCurrentPlayingSongIndex());
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
