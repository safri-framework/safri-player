#include "SongTreeController.h"
#include "httpsession.h"
#include "static.h"
#include "SongtreeHelper.h"
#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "JSONSerializer.h"
#include <QFile>
SongTreeController::SongTreeController(){}

void SongTreeController::service(HttpRequest &request, HttpResponse &response)
{
    SongtreeHelper* helper;
    response.setHeader("Content-Type", "application/json"); //charset=ISO-8859-1");
    HttpSession session=Static::sessionStore->getSession(request,response);

    if (!session.contains("treeHelper")) {
        qDebug()<<"NEW SESSION";
        helper = new SongtreeHelper(session.getId());
        connect(Static::sessionStore, SIGNAL(sessionExpired(QByteArray)), helper, SLOT(sessionExpired(QByteArray)));
        QVariant var;
        var.setValue<SongtreeHelper*>(helper);
        session.set("treeHelper", var);
    }
    else
    {
        helper = session.get("treeHelper").value<SongtreeHelper*>();
        qDebug()<<"EXISTING SESSION";
    }

    QJsonDocument doc;

    if(request.getParameter("action") == "insertNodeInPl")
    {
        QJsonDocument doc;
        bool ok1;
        bool ok2;
        QVariant variantNodeId = request.getParameter("id");
        QVariant varianPlPos = request.getParameter("pos");
        if(variantNodeId.isValid() && varianPlPos.isValid())
        {
            int nodeId  = variantNodeId.toInt(&ok1);
            int plPos   = varianPlPos.toInt(&ok2);

            if(ok1 && ok2)
            {
                helper->addToPlaylist(nodeId, plPos);
                doc.setObject(JSONSerializer::generateErrorObject("", "Insert Node in Playlist", true));
                response.write(doc.toJson(), true);
            }
            else
            {
                doc.setObject(JSONSerializer::generateErrorObject("Wrong parameters", "Insert Node in Playlist", false));
                response.write(doc.toJson(), true);
            }
        }
        else
        {
            doc.setObject(JSONSerializer::generateErrorObject("Missing parameters", "Insert Node in Playlist", false));
            response.write(doc.toJson(), true);
        }
    }
    else if (request.getParameter("action") == "requestFile")
    {
        QString collection = request.getParameter("collection");
        QString type = request.getParameter("type");
        int ID = request.getParameter("mediaID").toInt();
        QFile file(helper->getMediaFilePath(collection, ID, type));
        if (file.exists())
        {

            if (file.open(QIODevice::ReadOnly))
            {
                response.setHeader("Content-Type","audio/mpeg");
        //        response.setHeader("Cache-Control","max-age="+QByteArray::number(maxAge/1000));

                // Return the file content
                while (!file.atEnd() && !file.error())
                {
                    response.write(file.read(65536));
                }
                file.close();
            }
            else
            {
                qWarning("StaticFileController: Cannot open existing file %s for reading",qPrintable(file.fileName()));
                response.setStatus(403,"forbidden");
                response.write("403 forbidden",true);
            }
        }
        else
        {
            response.setStatus(404,"not found");
            response.write("404 not found",true);
        }

    }
    else
    {
        bool ok;
        QVariant variantId = request.getParameter("id");
        if (variantId.isValid())
        {
            int id = variantId.toInt(&ok);
            if(ok)
            {
                doc.setArray(helper->getChilds(id));
                response.write(doc.toJson(), true);
            }
            else
            {
                //wron parameter
                doc.setObject(JSONSerializer::generateErrorObject("Wrong parameter", "Return Childs", false));
                response.write(doc.toJson(), true);
            }
        }
        else
        {
            //Missing parameter
            doc.setObject(JSONSerializer::generateErrorObject("Missing parameter", "Return Childs", false));
            response.write(doc.toJson(), true);
        }
    }
}
