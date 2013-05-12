/**
  @file
  @author Stefan Frings
*/

#include "requestmapper.h"
#include "static.h"
#include "staticfilecontroller.h"

#include "controller/PlayerController.h"
#include "controller/PlaylistController.h"
#include "controller/SongTreeController.h"

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent) {}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());


    if (path.startsWith("/player")) {
        PlayerController().service(request, response);
    }
    else if (path.startsWith("/playlist")) {
        PlaylistController().service(request, response);
    }
    else if (path.startsWith("/songtree")) {
        SongTreeController().service(request, response);
    }
    // All other pathes are mapped to the static file controller.
    else {
        Static::staticFileController->service(request, response);
    }
    qDebug("RequestMapper: finished request");
}
