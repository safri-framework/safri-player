#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkCookieJar;

namespace SafriRESTClient
{
    class RESTClient : public QObject
    {
        Q_OBJECT
        public:

            explicit RESTClient(QString location, QObject *parent = 0);

        public:

            QNetworkReply *sendRequest(QString request, QObject* receiver = 0, const char * slot = 0);

        private:

            QNetworkAccessManager* networkManager;
            QNetworkCookieJar* cookieJar;
            QString RESTLocation;
    };
}

#endif // RESTCLIENT_H
