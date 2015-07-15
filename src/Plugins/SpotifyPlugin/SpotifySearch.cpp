#include "SpotifySearch.h"
#include "ui_SpotifySearch.h"
#include <QDebug>

#include "Interfaces/ICore.h"
#include "Interfaces/IMediaCollection.h"
#include "iplugin.h"
#include "pluginmanager.h"

#define HANDLE_SIZE = sizeof(sp_track)

SpotifySearch::SpotifySearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpotifySearch),
    _session(0),
    _search(new QSpotifySearch(this))
{
    ui->setupUi(this);
    _session = QSpotifySession::instance();
    _session->login("LOGIN", "PASS");

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
        qDebug()<<"Online!!!!";
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
    qDebug()<<"BUSY?";
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
    container.setMediaInfo(InfoMime, "spotify");
    container.setMediaInfo(InfoTitle, ptr->name());
    container.setMediaInfo(InfoTrack, ptr->discIndex());
    container.setMediaInfo(InfoLength, ptr->duration()/1000);

    container.setMediaInfo(InfoYear, ptr->creationDate());
    container.setMediaInfo(InfoURL, ptr->uriLink());

    container.setMediaInfo(InfoAlbumArtist, ptr->artists());
    _collection->addMedia(container);
}
