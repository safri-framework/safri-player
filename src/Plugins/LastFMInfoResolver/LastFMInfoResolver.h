#ifndef LASTFMINFORESOLVER_H
#define LASTFMINFORESOLVER_H
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include "CoreSupply/AbstractInfoResolver.h"
#include "CoreData/album.h"



class LastFMInfoResolver : public Core::AbstractInfoResolver
{
    Q_OBJECT

public:
    LastFMInfoResolver(QObject* parent = 0);
    QStringList             getSupportedInfoTypes();

private:
    virtual void            getInfo(QString type, Core::DataItem* item);
    void                    getAlbumCover(Core::Album* album);
    void                    getAlbumCover(QString album, QString artist);
    QString lastFMUsr;
    QString lastFMKey;
    QNetworkAccessManager* manager;

signals:
    void                    coverFound(QString url);
    void                    error(QString error);
    void                    newRequest(QString url);

private slots:
    void                    coverRequestCallBack();
    void                    fetchCover(QString url);
    void                    startRequest(QString url);
    void                    fetchCoverCallback();
};

#endif // LASTFMINFORESOLVER_H
