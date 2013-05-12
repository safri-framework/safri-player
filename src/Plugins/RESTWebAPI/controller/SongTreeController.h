#ifndef COLLECTIONCONTROLLER_H
#define COLLECTIONCONTROLLER_H

#include <QObject>
#include "httprequesthandler.h"

class SongTreeController : public HttpRequestHandler {

    Q_OBJECT
    Q_DISABLE_COPY(SongTreeController);

public:
    explicit SongTreeController();
    void service(HttpRequest& request, HttpResponse& response);

signals:

    
};

#endif // COLLECTIONCONTROLLER_H
