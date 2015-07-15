/****************************************************************************
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Yoann Lopes (yoann.lopes@nokia.com)
**
** This file is part of the MeeSpot project.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** Redistributions of source code must retain the above copyright notice,
** this list of conditions and the following disclaimer.
**
** Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in the
** documentation and/or other materials provided with the distribution.
**
** Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the names of its
** contributors may be used to endorse or promote products derived from
** this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/


#include "qspotifyuser.h"

#include <QtQml/QQmlEngine>

#include <libspotify/api.h>

#include "qspotifyalbumbrowse.h"
#include "qspotifyalbum.h"
#include "qspotifyplaylistcontainer.h"
#include "qspotifyplaylist.h"
#include "qspotifysession.h"

QSpotifyUser::QSpotifyUser(sp_user *user)
    : QSpotifyObject(true)
    , m_playlistContainer(nullptr)
    , m_starredList(nullptr)
    , m_inbox(nullptr)
{
    Q_ASSERT(user);
    sp_user_add_ref(user);
    m_sp_user = user;
    m_canonicalName = QString::fromUtf8(sp_user_canonical_name(m_sp_user));

    connect(this, SIGNAL(dataChanged()), this, SIGNAL(userDataChanged()));
}

QSpotifyUser::~QSpotifyUser()
{
    if (m_playlistContainer) {
        // This is deleted directly as we have to make sure that its
        // gone as soon as this destructor is done.
        delete m_playlistContainer;
    }
    if (m_starredList)
        m_starredList->deleteLater();
    if (m_inbox)
        m_inbox->deleteLater();
    if (m_sp_user)
        sp_user_release(m_sp_user);
}

bool QSpotifyUser::isLoaded()
{
    return sp_user_is_loaded(m_sp_user);
}

bool QSpotifyUser::updateData()
{
    QString canonicalName = QString::fromUtf8(sp_user_canonical_name(m_sp_user));
    QString displayName = QString::fromUtf8(sp_user_display_name(m_sp_user));

    bool updated = false;
    if (m_canonicalName != canonicalName) {
        m_canonicalName = canonicalName;
        updated = true;
    }
    if (m_displayName != displayName) {
        m_displayName = displayName;
        updated = true;
    }

    return updated;
}

QSpotifyPlaylistContainer *QSpotifyUser::playlistContainer() const
{
    if (!m_playlistContainer) {
        sp_playlistcontainer *pc;
        if (QSpotifySession::instance()->user() == this) {
            pc = sp_session_playlistcontainer(QSpotifySession::instance()->m_sp_session);
            sp_playlistcontainer_add_ref(pc);
        } else {
            pc = sp_session_publishedcontainer_for_user_create(QSpotifySession::instance()->m_sp_session, m_canonicalName.toUtf8().constData());
        }
        m_playlistContainer = new QSpotifyPlaylistContainer(pc);
        m_playlistContainer->init();
        connect(m_playlistContainer, SIGNAL(playlistContainerDataChanged()), this, SIGNAL(playlistsChanged()));
        connect(m_playlistContainer, SIGNAL(playlistsNameChanged()), this, SIGNAL(playlistsNameChanged()));
    }
    return m_playlistContainer;
}

QSpotifyPlaylist *QSpotifyUser::starredList() const
{
    if (!m_starredList) {
        sp_playlist *sl;
        if (QSpotifySession::instance()->user() == this) {
            sl = sp_session_starred_create(QSpotifySession::instance()->m_sp_session);
        } else {
            sl = sp_session_starred_for_user_create(QSpotifySession::instance()->m_sp_session, m_canonicalName.toUtf8().constData());
        }
        m_starredList = new QSpotifyPlaylist(QSpotifyPlaylist::Starred, sl, false);
        m_starredList->init();
        QQmlEngine::setObjectOwnership(m_starredList, QQmlEngine::CppOwnership);
    }
    return m_starredList;
}

QSpotifyPlaylist *QSpotifyUser::inbox() const
{
    if (QSpotifySession::instance()->user() != this)
        return nullptr;

    if (!m_inbox) {
        sp_playlist *in;
        in = sp_session_inbox_create(QSpotifySession::instance()->m_sp_session);
        m_inbox = new QSpotifyPlaylist(QSpotifyPlaylist::Inbox, in, false);
        m_inbox->init();
        QQmlEngine::setObjectOwnership(m_inbox, QQmlEngine::CppOwnership);
    }
    return m_inbox;
}

QList<QObject*> QSpotifyUser::playlistsAsQObject() const
{
    QList<QObject*> list;
    if (auto inb = inbox()) {
        list.append((QObject*)inb);
    }
    list.append((QObject*)starredList());
    list.append(playlistContainer()->formattedPlaylists());
    return list;
}

QList<QSpotifyPlaylist *> QSpotifyUser::playlists() const
{
    return playlistContainer()->playlists();
}

QList<QObject*> QSpotifyUser::playlistsFlat() const
{
    return playlistContainer()->playlistsFlat();
}

bool QSpotifyUser::createPlaylist(const QString &name)
{
    if (name.trimmed().isEmpty())
        return false;

    QString n = name;
    if (n.size() > 255)
        n.resize(255);
    sp_playlist *pl = sp_playlistcontainer_add_new_playlist(m_playlistContainer->m_container, n.toUtf8().constData());
    return pl != nullptr;
}

bool QSpotifyUser::createPlaylistInFolder(const QString &name, QSpotifyPlaylist *folder)
{
    if (!folder || folder->type() != QSpotifyPlaylist::Folder)
        return createPlaylist(name);

    if (name.trimmed().isEmpty())
        return false;

    QString n = name;
    if (n.size() > 255)
        n.resize(255);
    sp_playlist *pl = sp_playlistcontainer_add_new_playlist(m_playlistContainer->m_container, n.toUtf8().constData());
    if (!pl)
        return false;

    int i = m_playlistContainer->m_playlists.indexOf(folder);
    if (i == -1)
        return true;

    sp_uint64 folderId = sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, i);
    int count = sp_playlistcontainer_num_playlists(m_playlistContainer->m_container);
    for (int j = i + 1; j < count; ++j) {
        if (folderId == sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, j))
            i = j;
    }
    sp_playlistcontainer_move_playlist(m_playlistContainer->m_container, count - 1, i, false);

    return true;
}

bool QSpotifyUser::createPlaylistFromTrack(QSpotifyTrack *track)
{
    if (!track)
        return false;

    sp_playlist *pl = sp_playlistcontainer_add_new_playlist(m_playlistContainer->m_container, track->name().toUtf8().constData());
    if (pl == nullptr)
        return false;
    sp_playlist_add_tracks(pl, const_cast<sp_track* const*>(&track->m_sp_track), 1, 0, QSpotifySession::instance()->spsession());
    return true;
}

bool QSpotifyUser::createPlaylistFromAlbum(QSpotifyAlbumBrowse *album)
{
    if (!album || !album->m_albumTracks || album->m_albumTracks->count() < 1)
        return false;

    QString playlistName = album->album()->artist() + QLatin1String(" - ") + album->album()->name();
    sp_playlist *pl = sp_playlistcontainer_add_new_playlist(m_playlistContainer->m_container, playlistName.toUtf8().constData());
    if (pl == nullptr)
        return false;

    int c = album->m_albumTracks->count();
    const sp_track *tracks[c];
    for (int i = 0; i < c; ++i)
        tracks[i] = album->m_albumTracks->at(i)->sptrack();
    sp_playlist_add_tracks(pl, const_cast<sp_track* const*>(tracks), c, 0, QSpotifySession::instance()->spsession());
    return true;
}

void QSpotifyUser::removePlaylist(QSpotifyPlaylist *playlist)
{
    if (!playlist)
        return;

    int i = m_playlistContainer->m_playlists.indexOf(playlist);
    if (i == -1)
        return;

    if (playlist->type() == QSpotifyPlaylist::Folder) {
        sp_uint64 folderId = sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, i);
        int count = sp_playlistcontainer_num_playlists(m_playlistContainer->m_container);
        for (int j = i + 1; j < count; ++j) {
            if (folderId == sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, j)) {
                sp_playlistcontainer_remove_playlist(m_playlistContainer->m_container, j);
                break;
            }
        }
    }
    sp_playlistcontainer_remove_playlist(m_playlistContainer->m_container, i);
}

void QSpotifyUser::deleteFolderAndContent(QSpotifyPlaylist *playlist)
{
    if (!playlist || playlist->type() != QSpotifyPlaylist::Folder)
        return;

    int i = m_playlistContainer->m_playlists.indexOf(playlist);
    if (i == -1)
        return;

    sp_uint64 folderId = sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, i);
    int count;
    sp_uint64 currId;
    do {
        sp_playlistcontainer_remove_playlist(m_playlistContainer->m_container, i);
        count = sp_playlistcontainer_num_playlists(m_playlistContainer->m_container);
        currId = sp_playlistcontainer_playlist_folder_id(m_playlistContainer->m_container, i);
    } while (i < count && currId != folderId);
    if (currId == folderId)
        sp_playlistcontainer_remove_playlist(m_playlistContainer->m_container, i);
}

bool QSpotifyUser::ownsPlaylist(QSpotifyPlaylist *playlist)
{
    if (!playlist)
        return false;
    return playlist->owner() == m_canonicalName;
}

bool QSpotifyUser::canModifyPlaylist(QSpotifyPlaylist *playlist)
{
    if (!playlist)
        return false;
    return ownsPlaylist(playlist) || playlist->collaborative();
}
