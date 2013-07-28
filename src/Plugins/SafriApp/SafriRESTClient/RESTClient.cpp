#include "RESTClient.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>

using namespace SafriRESTClient;

RESTClient::RESTClient(QString location, QObject *parent) :
    QObject(parent), networkManager(0), RESTLocation(location)
{
    networkManager = new QNetworkAccessManager(this);
    cookieJar = new QNetworkCookieJar(this);

    networkManager->setCookieJar(cookieJar);
}

QNetworkReply* RESTClient::sendRequest(QString request, QObject *receiver, const char *slot)
{
    QNetworkReply* reply = networkManager->get(QNetworkRequest( QUrl(RESTLocation + request) ));
    if (slot != 0 && receiver != 0)
    {
        connect(reply, SIGNAL(finished()), receiver, slot);
    }

    return reply;
}

void RESTClient::sendRequest(QString request, bool deleteLater)
{
    QNetworkReply* reply = sendRequest(request);

    if (deleteLater)
    {
        connect( reply, SIGNAL( finished() ), reply, SLOT( deleteLater() ) );
    }
}
