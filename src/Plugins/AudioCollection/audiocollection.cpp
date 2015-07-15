#include "audiocollection.h"
#include "Interfaces/IMediaCollectionStorageFactory.h"
#include "Interfaces/IMediaCollectionStorage.h"
#include "pluginmanager.h"
#include "Interfaces/ICore.h"
#include "Interfaces/IInfoResolver.h"
#include "CoreSupply/InfoController.h"
#include "CoreSupply/InfoRequest.h"
#include <QDebug>
#include <QDir>
#include <QCryptographicHash>

AudioCollection::AudioCollection(QString name, QUrl url):m_name(name),
    currentAlbumID(0),
    currentArtistID(0),
    currentGenreID(0),
    currentSongID(0)
{
    m_songList = new QList<Song*>;
    m_artistList = new QList<Artist*> ;
    m_albumList = new QList<Album*> ;
    m_genreList = new QList<Genre*>;
    m_albumArtistList = new QList<AlbumArtist*>;
    m_IDtoSongMap = new QMap<int, Song*> ;
    m_PathToSongMap = new QMap<QString, Song*>;
    m_IDtoArtistMap = new QMap<int, Artist*>;
    m_IDtoAlbumArtistMap = new QMap<int, AlbumArtist*>;
    m_IDtoAlbumMap = new QMap<int, Album*>;
    m_IDtoGenreMap = new QMap<int, Genre*>;
    m_nameToSongMap = new QMap<QString, Song*>;
    m_nameToArtistMap = new QMap<QString, Artist*>;
    m_nameToAlbumMap = new QMap<QString, Album*>;
    m_nameToGenreMap = new QMap<QString, Genre*>;
    m_nameToAlbumArtistMap = new QMap<QString, AlbumArtist*>;
    m_rootPath = url;
}

AudioCollection::~AudioCollection()
{
    qDebug() << "AudioCollection destroyed";
}


void AudioCollection::lockForRead()
{
    m_lock.lockForRead();
}


void AudioCollection::lockForWrite()
{
    m_lock.lockForWrite();
}


void AudioCollection::unlock()
{
    m_lock.unlock();
}


QList<Core::DataItem *> AudioCollection::getByName(Core::DataItem::DATA_ITEM_TYPE type, QString name)
{
    m_lock.lockForRead();
    QList<DataItem*> list;

    switch (type)
    {
        case DataItem::ALBUM:
        {

            QList<Album*> tmp = m_nameToAlbumMap->values(name);


            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;

        }
        case DataItem::ARTIST:
        {
            QList<Artist*> tmp = m_nameToArtistMap->values(name);

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
        case DataItem::ALBUMARTIST:
        {
            QList<AlbumArtist*> tmp = m_nameToAlbumArtistMap->values(name);

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
        case DataItem::GENRE:
        {
            QList<Genre*> tmp = m_nameToGenreMap->values(name);

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
        case DataItem::SONG:
        {
            QList<Song*> tmp = m_nameToSongMap->values(name);

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
        default:

            break;
    }
    m_lock.unlock();
    return list;
}

Core::DataItem* AudioCollection::getByID(Core::DataItem::DATA_ITEM_TYPE type, int id)
{
    m_lock.lockForRead();
    Core::DataItem* item = 0;
    switch (type)
    {
    case DataItem::ALBUM:
        item = m_IDtoAlbumMap->value(id);
        break;
       case DataItem::ARTIST:
        item = m_IDtoArtistMap->value(id);
        break;
    case DataItem::GENRE:
        item = m_IDtoGenreMap->value(id);
        break;
    case DataItem::SONG:
        item = m_IDtoSongMap->value(id);
        break;
    case DataItem::ALBUMARTIST:
        item = m_IDtoAlbumArtistMap->value(id);
        break;
    default:
        break;
    }
    m_lock.unlock();
    return item;
}

QList<Core::DataItem *> AudioCollection::getDataItems(Core::DataItem::DATA_ITEM_TYPE type)
{
    QList<DataItem*> list;
    m_lock.lockForRead();
    switch (type)
    {
        case DataItem::ALBUM:

            for (int i = 0; i < m_albumList->size(); i++)
            {
                list.append(m_albumList->at(i));
            }

           break;

        case DataItem::ARTIST:

            for (int i = 0; i < m_artistList->size(); i++)
            {
                list.append(m_artistList->at(i));
            }
            break;

        case DataItem::ALBUMARTIST:

            for (int i = 0; i < m_albumArtistList->size(); i++)
            {
                list.append(m_albumArtistList->at(i));
            }
            break;

        case DataItem::GENRE:

            for (int i = 0; i < m_genreList->size(); i++)
            {
                list.append(m_genreList->at(i));
            }
            break;

        case DataItem::SONG:

            for (int i = 0; i < m_songList->size(); i++)
            {
                list.append(m_songList->at(i));
            }
            break;

        default:

            break;
    }
    m_lock.unlock();
    return list;
}

QList<Core::Media *> AudioCollection::getMedia()
{

    QList<Media*> list;
    m_lock.lockForRead();
    for(int i = 0; i < m_songList->size(); i++ )
    {
        list.append(m_songList->at(i));
    }
    m_lock.unlock();
    return list;
}

Media *AudioCollection::getMediaByURL(const QUrl &url)
{
    //qDebug() << "AudioCollection::getMediaByURL " << url.toLocalFile();
    return m_PathToSongMap->value( url.toLocalFile() );
}

QString AudioCollection::getName()
{
    return this->m_name;
}

QUrl AudioCollection::getAssetFolderPath(QString subfolder)
{
    QUrl url(this->getRootPath().toString()+"/Assets/"+subfolder);
    QDir assetFolder(url.toString());
    if(!assetFolder.exists())
        assetFolder.mkpath(url.toString());
    return url;
}


bool AudioCollection::isAvailable()
{
    //TODO
    return 1;
}

QUrl AudioCollection::getRootPath()
{
    return m_rootPath;
}

QString AudioCollection::getHash()
{
    QByteArray hash;
    hash = QCryptographicHash::hash(m_databaseLocation.toEncoded(), QCryptographicHash::Md5);
    hash = hash.toHex();

    return QString(hash);
}

QUrl AudioCollection::getDatabaseLocation()
{
    return m_databaseLocation;
}

void AudioCollection::setDatabaseLocation(QUrl url)
{
    m_databaseLocation = url;
}

InfoContainer *AudioCollection::getInfoContainerByName(QString name)
{
    //TODO
    Q_UNUSED(name)
    return 0;
}

QString AudioCollection::getContentType()
{
    return "org.safri.collection.audio";
}

QList<Core::Song *> AudioCollection::getSongs()
{
    QList<Song*> list;
    m_lock.lockForRead();
        list = *m_songList;
    m_lock.unlock();
    return list;
}

QList<Core::Artist *> AudioCollection::getArtists()
{
    QList<Artist*> list;
    m_lock.lockForRead();
        list = *m_artistList;
    m_lock.unlock();
    return list;
}

QList<Core::Album *> AudioCollection::getAlbums()
{
    QList<Album*> list;
    m_lock.lockForRead();
        list = *m_albumList;
    m_lock.unlock();
    return list;
}

QList<Core::Genre *> AudioCollection::getGenres()
{
    QList<Genre*> list;
    m_lock.lockForRead();
        list = *m_genreList;
    m_lock.unlock();
    return list;
}


QList<Core::Song *> AudioCollection::getSongsByName(QString name)
{
    QList<Song*> list;
    m_lock.lockForRead();
        list = m_nameToSongMap->values(name);
    m_lock.unlock();
    return list;
}

QList<Core::Artist *> AudioCollection::getArtistsByName(QString name)
{
    QList<Artist*> list;
    m_lock.lockForRead();
        list = m_nameToArtistMap->values(name);
    m_lock.unlock();
    return list;
}

QList<Core::Album *> AudioCollection::getAlbumsByName(QString name)
{
    QList<Album*> list;
    m_lock.lockForRead();
        list = m_nameToAlbumMap->values(name);
    m_lock.unlock();
    return list;
}

QList<Core::Genre *> AudioCollection::getGenresByName(QString name)
{
    QList<Genre*> list;
    m_lock.lockForRead();
        list = m_nameToGenreMap->values(name);
    m_lock.unlock();
    return list;
}


Core::Song* AudioCollection::getSongByID(int id)
{
    Song* song;
    m_lock.lockForRead();
        song = m_IDtoSongMap->value(id);
    m_lock.unlock();
    return song;
}

Core::Artist* AudioCollection::getArtistByID(int id)
{
    Artist* artist;
    m_lock.lockForRead();
        artist = m_IDtoArtistMap->value(id);
    m_lock.unlock();
    return artist;
}


Core::Album* AudioCollection::getAlbumByID(int id)
{
    Album* album;
    m_lock.lockForRead();
        album = m_IDtoAlbumMap->value(id);
    m_lock.unlock();
    return album;
}


Core::Genre* AudioCollection::getGenreByID(int id)
{
    Genre* genre;
    m_lock.lockForRead();
        genre = m_IDtoGenreMap->value(id);
    m_lock.unlock();
    return genre;
}


Core::Song* AudioCollection::getSongByPath(QString path)
{
    Song* song;
    m_lock.lockForRead();
        song = m_PathToSongMap->value(path);
    m_lock.unlock();
    return song;
}


Artist *AudioCollection::newArtist(QString name)
{
    Artist* artist = new Artist(newArtistID(), name, this);
    insertArtist(artist);
    return artist;
}


Album *AudioCollection::newAlbum(QString name)
{
    Album* album = new Core::Album(newAlbumID(), name, this);
    insertAlbum(album);
    return album;
}


Genre *AudioCollection::newGenre(QString name)
{
    Genre* genre = new Genre(newGenreID(), name, this);
    insertGenre(genre);
    return genre;
}


Song *AudioCollection::newSong(QString mime, QString name, int year, QString url)
{
    Song* song = new Song(mime, newSongID(), name, year, url, this);
    insertSong(song);
    return song;
}


void AudioCollection::removeSong(Song *song)
{
    m_lock.lockForWrite();
        m_songList->removeAll(song);
        m_PathToSongMap->remove(song->getFileName());
        m_nameToSongMap->remove(song->getName());
        m_IDtoSongMap->remove(song->getID());
    m_lock.unlock();
    Q_EMIT itemRemoved(song);
}

void AudioCollection::removeAlbumArtist(AlbumArtist* albumArtist)
{
    m_lock.lockForWrite();
        m_albumArtistList->removeAll(albumArtist);
        m_nameToAlbumArtistMap->remove(albumArtist->getName());
        m_IDtoAlbumArtistMap->remove(albumArtist->getID());
    m_lock.unlock();
    Q_EMIT itemRemoved(albumArtist);
}

void AudioCollection::removeArtist(Artist *artist)
{
    m_lock.lockForWrite();
        m_artistList->removeAll(artist);
        m_nameToArtistMap->remove(artist->getName());
        m_IDtoArtistMap->remove(artist->getID());
    m_lock.unlock();
    Q_EMIT itemRemoved(artist);
}


void AudioCollection::removeAlbum(Album *album)
{
    m_lock.lockForWrite();
        m_albumList->removeAll(album);
        m_nameToAlbumMap->remove(album->getName());
        m_IDtoAlbumMap->remove(album->getID());
    m_lock.unlock();
    Q_EMIT itemRemoved(album);
}


void AudioCollection::removeGenre(Genre *genre)
{
    m_lock.lockForWrite();
        m_genreList->removeAll(genre);
        m_IDtoGenreMap->remove(genre->getID());
        m_nameToGenreMap->remove(genre->getName());
    m_lock.unlock();
    Q_EMIT itemRemoved(genre);
}

QList<AlbumArtist *> AudioCollection::getAlbumArtists()
{
    QList<AlbumArtist*> list;
    m_lock.lockForRead();
        list = *m_albumArtistList;
    m_lock.unlock();
    return list;
}


void AudioCollection::insertGenre(Genre* genre)
{

    m_lock.lockForWrite();
        int ID = genre->getID();
        genre->setMediaCollection(this);
        m_genreList->append(genre);
        m_IDtoGenreMap->insert(ID, genre);
        m_nameToGenreMap->insert(genre->getName(), genre);
        if(ID > currentGenreID)
            currentGenreID = ID;
    m_lock.unlock();
    Q_EMIT itemAdded(genre);
}


void AudioCollection::insertArtist(Artist* artist)
{

    m_lock.lockForWrite();
        int ID = artist->getID();
        artist->setMediaCollection(this);
        m_artistList->append(artist);
        m_IDtoArtistMap->insert(ID , artist);
        m_nameToArtistMap->insert(artist->getName(), artist);
        if (ID > currentArtistID)
            currentArtistID = ID;
    m_lock.unlock();
    Q_EMIT itemAdded(artist);
}


void AudioCollection::insertAlbum(Album* album)
{
    m_lock.lockForWrite();
        int ID = album->getID();
        album->setMediaCollection(this);
        m_albumList->append(album);
        m_IDtoAlbumMap->insert(ID, album);
        m_nameToAlbumMap->insert(album->getName(), album);
        if (ID > currentAlbumID)
            currentAlbumID = ID;
    m_lock.unlock();
    Q_EMIT itemAdded(album);
}


void AudioCollection::insertSong(Song* song)
{
    m_lock.lockForWrite();
        int ID = song->getID();
        m_songList->append(song);
        song->setMediaCollection(this);
        m_IDtoSongMap->insert(ID, song);
        m_nameToSongMap->insert(song->getName(), song);
        m_PathToSongMap->insert( song->getFileName(), song );
        if (ID > currentSongID)
            currentSongID = ID;
    m_lock.unlock();
    //Q_EMIT itemAdded(song);
}

void AudioCollection::insertAlbumArtist(AlbumArtist *albumArtist)
{
    m_lock.lockForWrite();
        int ID = albumArtist->getID();
        albumArtist->setMediaCollection(this);
        m_albumArtistList->append(albumArtist);
        m_IDtoAlbumArtistMap->insert(ID , albumArtist);
        m_nameToAlbumArtistMap->insert(albumArtist->getName(), albumArtist);
        if (ID > currentAlbumArtistID)
            currentAlbumArtistID = ID;
    m_lock.unlock();
    Q_EMIT itemAdded(albumArtist);
}

Media* AudioCollection::addMedia(MediaInfoContainer &mediaInfo)
{
    bool newArtist = false;
    bool newAlbum  = false;
    bool newGenre  = false;
    bool newAlbumArtist = false;

    AudioCollection* audioCollection = this;
    bool isTemporary = false; //  functionality can be added here, if needed

    Q_UNUSED(isTemporary)

    if(audioCollection)
    {
        Song* song = 0;
        Artist* artist = 0;
        Album* album = 0;
        Genre* genre = 0;
        AlbumArtist* albumArtist = 0;

        QString artistName = mediaInfo.getMediaInfo(InfoArtist).toString();
        QString albumArtistName = mediaInfo.getMediaInfo(InfoAlbumArtist).toString();
        QString albumName = mediaInfo.getMediaInfo(InfoAlbum).toString();
        QString genreName = mediaInfo.getMediaInfo(InfoGenre).toString();
        QString mime = mediaInfo.getMediaInfo(InfoMime).toString();

        QString file = mediaInfo.getURL().toLocalFile();
        if (file.isEmpty())
        {
            file = mediaInfo.getMediaInfo(InfoURL).toString();
        }

        song = audioCollection->getSongByPath( file );
        if(!song) //Song doesn't already exists
        {
            song = audioCollection->newSong(mime, mediaInfo.getMediaInfo(InfoTitle).toString(), mediaInfo.getMediaInfo(InfoYear).toInt(), file);
            if(audioCollection->getAlbumArtistsByName(albumArtistName).size() > 0) //Artist already exists!
            {
               albumArtist = audioCollection->getAlbumArtistsByName(albumArtistName).at(0);
               QList<Album*> albumList = albumArtist->getAlbumByName(albumName);
               if(albumList.size() > 0 ) //Album already exists!
               {
                   album = albumList.at(0);
               }
               else //Album doesn't already exists!
               {
                   album = audioCollection->newAlbum(albumName);
                   album->setAlbumArtist(albumArtist);
                   albumArtist->addAlbum(album);
                   newAlbum = true;
               }
            }
            else    //Album Artist doesn't already exists -> the album can't exist too.
            {
                albumArtist = audioCollection->newAlbumArtist(albumArtistName);
                album = audioCollection->newAlbum(albumName);
                albumArtist->addAlbum(album);
                album->setAlbumArtist(albumArtist);
                newAlbum = true;
                newAlbumArtist = true;
            }

            if(getArtistsByName(artistName).size() > 0)
            {
                artist = getArtistsByName(artistName).at(0);
            }
            else
            {
                artist = audioCollection->newArtist(artistName);
            }

            album->addArtist(artist);
            artist->addAlbum(album);

            QList<Genre*> genreList = audioCollection->getGenresByName(genreName);
            if(genreList.size() > 0) //Genre already exists!
            {
                genre = genreList.at(0);
            }
            else
            {
                genre = audioCollection->newGenre(genreName);
                newGenre = true;
            }


         genre->addSong(song);
         song->setGenre(genre);
         album->addSong(song);
         song->setAlbum(album);

         song->setTrack(mediaInfo.getMediaInfo(InfoTrack).toInt());
         song->setLength(mediaInfo.getMediaInfo(InfoLength).toInt());

         song->setArtist(artist);

         //qDebug() << "Created Song " << song->getName();

         Q_EMIT itemAdded(song);
         Q_EMIT newSongInserted(song);

         if(newArtist)
             Q_EMIT newArtistInserted(artist);

         if(newAlbum)
             Q_EMIT newAlbumInserted(album);

         if(newGenre)
             Q_EMIT newGenreInserted(genre);


        }
        return song;
    }
    return 0;
}

/*
bool AudioCollection::save()
{
    qDebug() << "AudioCollection::save()";

    if (!storage)
    {
        qDebug() << "No storage defined! Searching for some now...";
        QList<Core::IMediaCollectionStorageFactory*> objects = PluginSystem::PluginManager::getObjects<Core::IMediaCollectionStorageFactory>();
        Core::IMediaCollectionStorageFactory* factory = 0;
        int size = objects.size();

        for (int i = 0; i < size; i++)
        {
            if ( objects.at(i)->getStorageType() == "org.safri.sqlite.audio" )
            {
                factory = objects.at(i);
            }
        }

        if (factory)
        {
            qDebug() << "Storage factory found";

            storage = factory->createMediaCollectionStorage(Core::ICore::storageDirectory() + "/sqlitedatabasev2.db");

            return storage->saveMediaCollection(this);
        }

        return false;
    }

    return false;
}
*/

int AudioCollection::newAlbumID()
{
    return ++currentAlbumID;
}

int AudioCollection::newAlbumArtistID()
{
    return ++currentAlbumArtistID;
}

int AudioCollection::newArtistID()
{
    return ++currentArtistID;
}

int AudioCollection::newGenreID()
{
    return ++currentGenreID;
}

int AudioCollection::newSongID()
{
    return ++currentSongID;
}


QList<AlbumArtist *> AudioCollection::getAlbumArtistsByName(QString name)
{
    QList<AlbumArtist*> albumArtists;
    m_lock.lockForRead();
    albumArtists = m_nameToAlbumArtistMap->values(name);
    m_lock.unlock();
    return albumArtists;
}

AlbumArtist *AudioCollection::getAlbumArtistByID(int id)
{
    AlbumArtist* albumArtist;
    m_lock.lockForRead();
    albumArtist = m_IDtoAlbumArtistMap->value(id);
    m_lock.unlock();
    return albumArtist;
}

AlbumArtist *AudioCollection::newAlbumArtist(QString name)
{
    AlbumArtist* albumArtist = new AlbumArtist(newAlbumArtistID(), name, this);
    insertAlbumArtist(albumArtist);
    return albumArtist;
}
