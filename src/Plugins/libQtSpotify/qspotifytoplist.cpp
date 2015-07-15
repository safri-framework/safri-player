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


#include "qspotifytoplist.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QEvent>
#include <QtCore/QMutex>

#include <libspotify/api.h>

#include "qspotifyalbum.h"
#include "qspotifyartist.h"
#include "qspotifyplaylist.h"
#include "qspotifysession.h"
#include "qspotifytrack.h"
#include "qspotifytracklist.h"
#include "qspotifyuser.h"
#include "qspotifycachemanager.h"

#include "listmodels/qspotifyalbumlist.h"
#include "listmodels/qspotifyartistlist.h"

static QHash<sp_toplistbrowse *, QSpotifyToplist *> g_toplistObjects;
static QMutex g_mutex, busyMutex;

class QSpotifyToplistCompleteEvent : public QEvent
{
public:
    QSpotifyToplistCompleteEvent(sp_toplistbrowse *tlbrowse)
        : QEvent(Type(QEvent::User))
        , m_tlbrowse(tlbrowse)
    { }

    sp_toplistbrowse *toplistBrowse() const { return m_tlbrowse; }

private:
    sp_toplistbrowse *m_tlbrowse;
};

static void callback_toplistbrowse_complete(sp_toplistbrowse *result, void *)
{
    QMutexLocker lock(&g_mutex);
    QSpotifyToplist *tl = g_toplistObjects.value(result);
    if (tl)
        QCoreApplication::postEvent(tl, new QSpotifyToplistCompleteEvent(result));
}

QSpotifyToplist::QSpotifyToplist(QObject *parent)
    : QObject(parent)
    , m_sp_browsetracks(nullptr)
    , m_sp_browseartists(nullptr)
    , m_sp_browsealbums(nullptr)
    , m_busy(false)
{
    m_trackResults = new QSpotifyTrackList(this);
    m_albumResults = new QSpotifyAlbumList(this);
    m_artistResults = new QSpotifyArtistList(this);
}

QSpotifyToplist::~QSpotifyToplist()
{
    clear();
}

void QSpotifyToplist::updateResults()
{
    QDateTime currentTime = QDateTime::currentDateTime();

    if (m_busy || (m_lastUpdate.isValid() && m_lastUpdate.secsTo(currentTime) < 7200))
        return;

    m_lastUpdate = currentTime;

    clear();

    setBusy(true);

    QMutexLocker lock(&g_mutex);
    m_sp_browsetracks = sp_toplistbrowse_create(QSpotifySession::instance()->spsession(), SP_TOPLIST_TYPE_TRACKS, SP_TOPLIST_REGION_EVERYWHERE, NULL, callback_toplistbrowse_complete, 0);
    g_toplistObjects.insert(m_sp_browsetracks, this);
    m_sp_browseartists = sp_toplistbrowse_create(QSpotifySession::instance()->spsession(), SP_TOPLIST_TYPE_ARTISTS, SP_TOPLIST_REGION_EVERYWHERE, NULL, callback_toplistbrowse_complete, 0);
    g_toplistObjects.insert(m_sp_browseartists, this);
    m_sp_browsealbums = sp_toplistbrowse_create(QSpotifySession::instance()->spsession(), SP_TOPLIST_TYPE_ALBUMS, SP_TOPLIST_REGION_EVERYWHERE, NULL, callback_toplistbrowse_complete, 0);
    g_toplistObjects.insert(m_sp_browsealbums, this);

}

void QSpotifyToplist::clear()
{
    m_trackResults->clear();
    m_albumResults->clear();
    m_artistResults->clear();

    emit resultsChanged();

    QMutexLocker lock(&g_mutex);
    if (m_sp_browsetracks)
        sp_toplistbrowse_release(m_sp_browsetracks);
    g_toplistObjects.remove(m_sp_browsetracks);
    m_sp_browsetracks = nullptr;
    if (m_sp_browseartists)
        sp_toplistbrowse_release(m_sp_browseartists);
    g_toplistObjects.remove(m_sp_browseartists);
    m_sp_browseartists = nullptr;
    if (m_sp_browsealbums)
        sp_toplistbrowse_release(m_sp_browsealbums);
    g_toplistObjects.remove(m_sp_browsealbums);
    m_sp_browsealbums = nullptr;
}

bool QSpotifyToplist::event(QEvent *e)
{
    if (e->type() == QEvent::User) {
        QSpotifyToplistCompleteEvent *ev = static_cast<QSpotifyToplistCompleteEvent *>(e);
        populateResults(ev->toplistBrowse());
        e->accept();
        return true;
    }
    return QObject::event(e);
}

void QSpotifyToplist::populateResults(sp_toplistbrowse *tl)
{
    if (sp_toplistbrowse_error(tl) != SP_ERROR_OK)
        return;

    if (tl == m_sp_browsetracks) {
        int c = sp_toplistbrowse_num_tracks(tl);
        for (int i = 0; i < c; ++i) {
            if (auto strack = sp_toplistbrowse_track(tl, i)) {
                auto track = QSpotifyCacheManager::instance().getTrack(strack);

                m_trackResults->appendRow(track);
                connect(QSpotifySession::instance()->user()->starredList(), SIGNAL(tracksAdded(QVector<sp_track*>)), track.get(), SLOT(onStarredListTracksAdded(QVector<sp_track*>)));
                connect(QSpotifySession::instance()->user()->starredList(), SIGNAL(tracksRemoved(QVector<sp_track*>)), track.get(), SLOT(onStarredListTracksRemoved(QVector<sp_track*>)));
            }
        }
    }

    if (tl == m_sp_browseartists) {
        int c = sp_toplistbrowse_num_artists(tl);
        for (int i = 0; i < c; ++i) {
            std::shared_ptr<QSpotifyArtist> artist = QSpotifyCacheManager::instance().getArtist(sp_toplistbrowse_artist(tl, i));
            artist->init();
            m_artistResults->appendRow(artist);
        }
    }

    if (tl == m_sp_browsealbums) {
        int c = sp_toplistbrowse_num_albums(tl);
        for (int i = 0; i < c; ++i) {
            sp_album *a = sp_toplistbrowse_album(tl, i);
            std::shared_ptr<QSpotifyAlbum> album = QSpotifyCacheManager::instance().getAlbum(a);
            m_albumResults->appendRow(album);
        }
    }

    if (m_trackResults->count() > 0 && m_artistResults->count() > 0 && m_albumResults->count() > 0) {
        setBusy(false);
    }

    emit resultsChanged();
}

void QSpotifyToplist::setBusy(bool busy)
{
    QMutexLocker lock(&busyMutex);
    m_busy = busy;
    emit busyChanged();
}
