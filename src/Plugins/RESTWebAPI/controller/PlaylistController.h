#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QObject>
#include "httprequesthandler.h"

class PlaylistController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(PlaylistController);

public:
    explicit PlaylistController();
    void service(HttpRequest& request, HttpResponse& response);

signals:
    
public slots:
    
};

#endif // PLAYLISTCONTROLLER_H
