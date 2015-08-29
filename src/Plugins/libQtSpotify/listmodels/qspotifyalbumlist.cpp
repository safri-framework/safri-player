#include "qspotifyalbumlist.h"
#include <qdebug.h>
#include "../qspotifyalbumbrowse.h"
#include "../SpotifyPlugin/SpotifySafriHelper.h"


QSpotifyAlbumList::QSpotifyAlbumList(QObject *parent) :
    ListModelBase<QSpotifyAlbum>(parent)
{
    m_roles[IsAvailableRole] = "isAvailable";
    m_roles[ArtistRole] = "artist";
    m_roles[NameRole] = "name";
    m_roles[YearRole] = "year";
    m_roles[TypeRole] = "type";
    m_roles[SectionTypeRole] = "sectionType";
    m_roles[CoverIdRole] = "coverId";
      m_roles[ContainerRole] = "container";
}

QVariant QSpotifyAlbumList::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_dataList.size())
        return QVariant();
    auto album = m_dataList.at(index.row());
    switch(role) {
    case Qt::DisplayRole:
        return album->name()+" - "+album->artist();
    case IsAvailableRole:
        return album->isAvailable();
    case ArtistRole:
        return album->artist();
    case NameRole:
        return album->name();
    case YearRole:
        return album->year();
    case TypeRole:
        return album->type();
    case SectionTypeRole:
        return album->sectionType();
    case CoverIdRole:
        return album->coverId();        
    case ContainerRole:
        return album->getMediaInfoContainer();

    default:
        return QVariant();
    }
}

QSpotifyAlbumBrowse *QSpotifyAlbumList::albumBrowse(const int idx)
{
    qDebug()<<"ALBUM BROWSE" << idx;
    auto browse = new QSpotifyAlbumBrowse();
    if( idx >= 0 && m_dataList.size() > idx)
    browse->setAlbum(m_dataList.at(idx));
    return browse;
}

bool QSpotifyAlbumList::appendToCurrentPlaylist(const int idx)
{
    SpotifySafriHelper::instance()->appendToCurrentPlaylist(data(index(idx), ContainerRole).toString());
    return true;
}
