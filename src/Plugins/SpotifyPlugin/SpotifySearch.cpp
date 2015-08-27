#include "SpotifySearch.h"
#include "ui_SpotifySearch.h"
#include <QDebug>
#include "Interfaces/ICore.h"
#include "Interfaces/ICore.h"
#include "Interfaces/IMediaCollection.h"
#include "iplugin.h"
#include "pluginmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QVariantMap>
#include <QTextStream>

#define HANDLE_SIZE = sizeof(sp_track)

SpotifySearch::SpotifySearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpotifySearch),
    _session(0),
    _search(new QSpotifySearch(this))
{
    ui->setupUi(this);
    login();
    _session = QSpotifySession::instance();
    connect(_session, SIGNAL(isLoggedInChanged()), this, SLOT(loggedIn()));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(search()));
    connect(_search, SIGNAL(resultsChanged()), this, SLOT(resultsChanged()));
    _collection = Core::ICore::createMediaCollection("org.safri.collection.audio", "Spotify", ICore::storageDirectory()+"/Spotify");
    PluginSystem::PluginManager::instance()->addObject(_collection);
}

SpotifySearch::~SpotifySearch()
{
    delete ui;
}

bool SpotifySearch::login()
{
    QString loginFile = ICore::storageDirectory() + "/spotifylogin.json";
    if(QFile::exists(loginFile))
    {
        QFile file(loginFile);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QVariantMap map = QJsonDocument::fromJson(file.readAll()).toVariant().toMap();
            QString login = map["user"].toString();
            QString pass  = map["password"].toString();
            QSpotifySession::instance()->login(login, pass);
            return true;
        }
        else
        {
            qDebug()<<" COULD NOT OPEN FILE";
            return false;
        }
    }
    else
    {
        writeLoginData("","");
    }
    return false;
}

bool SpotifySearch::writeLoginData(QString login, QString pass)
{
    QString loginFile = ICore::storageDirectory() + "/spotifylogin.json";
    QFile file(loginFile);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        QVariantMap map;
        map.insert("user", login);
        map.insert("password",pass);
        stream << QJsonDocument::fromVariant(map).toJson();
        file.close();
        return true;
    }
    return false;
}

void SpotifySearch::search()
{
    if (_session->isLoggedIn())
    {
        _search->setQuery(this->ui->lineEdit->text().trimmed());
        _search->search();
    }
}

void SpotifySearch::loggedIn()
{
    qDebug()<<"Online!";
}

void SpotifySearch::resultsChanged()
{
    qDebug() << _search->trackResults()->count()<< " COUNT!!";
    if(_search->trackResults()->count() > 0)
    {

        for(int i = 0; i < _search->trackResults()->count(); i++)
        {
            addTrack(_search->trackResults()->at(i));
        }

        for(int i= 0; i < _search->albums()->count(); i++)
        {
           std::shared_ptr<QSpotifyAlbum> album = _search->albums()->at(i);
           QSpotifyAlbumBrowse* browse =  album->browse();
           connect(browse, SIGNAL(busyChanged()), this, SLOT(browseFinished()));
        }
    }
}

void SpotifySearch::browseFinished()
{
    QSpotifyAlbumBrowse* browse = qobject_cast<QSpotifyAlbumBrowse*>(sender());
    if(browse && !browse->busy())
    {
        qDebug()<<browse->tracks()->count();
        for(int i = 0; i < browse->tracks()->count(); i++)
        {
            addTrack( browse->tracks()->at(i));
        }
    }
}

bool SpotifySearch::addTrack(std::shared_ptr<QSpotifyTrack> ptr)
{
    MediaInfoContainer container;
    container.setMediaInfo(InfoArtist, ptr->artists());
    container.setMediaInfo(InfoAlbum, ptr->album());
    container.setMediaInfo(InfoMimeType, "spotify");
    container.setMediaInfo(InfoTitle, ptr->name());
    container.setMediaInfo(InfoTrack, ptr->discIndex());
    container.setMediaInfo(InfoLength, ptr->duration()/1000);
    container.setMediaInfo(InfoYear, ptr->creationDate());
    container.setMediaInfo(InfoURL, ptr->uriLink());
    container.setMediaInfo(InfoAlbumArtist, ptr->artists());

    _collection->addMedia(container);
    return true;
}
