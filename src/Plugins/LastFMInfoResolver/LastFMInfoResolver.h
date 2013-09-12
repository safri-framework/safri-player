#ifndef LASTFMINFORESOLVER_H
#define LASTFMINFORESOLVER_H
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include "CoreSupply/AbstractInfoResolver.h"
#include "CoreData/Album.h"



class LastFMInfoResolver : public Core::AbstractInfoResolver
{
    Q_OBJECT

public:
    LastFMInfoResolver(QObject* parent = 0);
    QStringList             getSupportedInfoTypes();

private:
    virtual void            getInfo(QString type, Core::DataItem* item);
    void                    getAlbumInfo(Core::Album* album, QString type = "");
    void                    getAlbumInfo(QString album, QString artist, QString type);
    QString lastFMUsr;
    QString lastFMKey;
    QNetworkAccessManager* manager;

signals:
    void                    coverFound(QString url);
    void                    error(QString error);
    void                    newRequest(QString url, QString type);

private slots:
    void                    coverRequestCallBack();
    void                    fetchCover(QString url);
    void                    startRequest(QString url, QString type);
    void                    fetchCoverCallback();
};

#endif // LASTFMINFORESOLVER_H
