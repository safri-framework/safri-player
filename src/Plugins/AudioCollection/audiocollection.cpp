#include "audiocollection.h"

AudioCollection::AudioCollection(QString name):m_name(name)
{
    m_songList = new QList<Song*>;
    m_artistList = new QList<Artist*> ;
    m_albumList = new QList<Album*> ;
    m_genreList = new QList<Genre*>;
    m_IDtoSongMap = new QMap<int, Song*> ;
    m_PathToSongMap = new QMap<QString, Song*>;
    m_IDtoArtistMap = new QMap<int, Artist*>;
    m_IDtoAlbumMap = new QMap<int, Album*>;
    m_IDtoGenreMap = new QMap<int, Genre*>;
    m_nameToSongMap = new QMap<QString, Song*>;
    m_nameToArtistMap = new QMap<QString, Artist*>;
    m_nameToAlbumMap = new QMap<QString, Album*>;
    m_nameToGenreMap = new QMap<QString, Genre*>;
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
            QList<DataItem*> list;

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;

        }
        case DataItem::GENRE:
        {
            QList<Genre*> tmp = m_nameToGenreMap->values(name);
            QList<DataItem*> list;

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
        case DataItem::SONG:
        {
            QList<Song*> tmp = m_nameToSongMap->values(name);
            QList<DataItem*> list;

            for(int i = 0; i < tmp.size(); i++ )
            {
                list.append(tmp.at(i));
            }
            break;
        }
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

    case DataItem::GENRE:

        for (int i = 0; i < m_genreList->size(); i++)
        {
            list.append(m_genreList->at(i));
        }
        break;

        break;
    case DataItem::SONG:
        for (int i = 0; i < m_songList->size(); i++)
        {
            list.append(m_songList->at(i));
        }
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

QString AudioCollection::getName()
{
    return this->m_name;
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
    //TODO
    return QString::number(1);
}

QUrl AudioCollection::getDatabaseLocation()
{
  return m_databaseLocation;
}

InfoContainer *AudioCollection::getInfoContainerByName(QString name)
{
    //TODO
    return 0;
}


QList<Core::Song *> AudioCollection::getSongs()
{
    QList<Song*> list;
    m_lock.lockForRead();
        list = *m_songList;
    m_lock.unlock();
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









