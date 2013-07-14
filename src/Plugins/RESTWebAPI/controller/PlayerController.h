#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

namespace Core { class IPlaybackController; class Media; }

class PlayerController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(PlayerController);
    public:

        explicit PlayerController();
        void service(HttpRequest& request, HttpResponse& response);

    signals:

    private:

        Core::IPlaybackController* pbController;
    
};

#endif // PLAYERCONTROLLER_H
