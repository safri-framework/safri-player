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


#include "qspotifyalbumbrowse.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QEvent>
#include <QtCore/QHash>
#include <QtCore/QMutex>

#include <libspotify/api.h>

#include "qspotifyalbum.h"
#include "qspotifyplaylist.h"
#include "qspotifyplayqueue.h"
#include "qspotifysession.h"
#include "qspotifytrack.h"
#include "qspotifytracklist.h"
#include "qspotifyuser.h"
#include "qspotifycachemanager.h"

static QHash<sp_albumbrowse*, QSpotifyAlbumBrowse*> g_albumBrowseObjects;
static QMutex g_mutex;

static void callback_albumbrowse_complete(sp_albumbrowse *result, void *)
{
    QMutexLocker lock(&g_mutex);
    QSpotifyAlbumBrowse *s = g_albumBrowseObjects.value(result);
    if (s)
        QCoreApplication::postEvent(s, new QEvent(QEvent::User));
}

QSpotifyAlbumBrowse::QSpotifyAlbumBrowse(QObject *parent)
    : QObject(parent)
    , m_sp_albumbrowse(nullptr)
    , m_album(nullptr)
    , m_albumTracks(nullptr)
    , m_artistObject(nullptr)
    , m_hasMultipleArtists(false)
    , m_busy(false)
{
    m_albumTracks = new QSpotifyTrackList(this);
}

QSpotifyAlbumBrowse::~QSpotifyAlbumBrowse()
{
    clearData();
}

bool QSpotifyAlbumBrowse::event(QEvent *e)
{
    if (e->type() == QEvent::User) {
        processData();
        e->accept();
        return true;
    }
    return QObject::event(e);
}

void QSpotifyAlbumBrowse::setAlbum(std::shared_ptr<QSpotifyAlbum> album)
{
    if (m_album == album)
        return;
    m_album = album;
    emit albumChanged();
    clearData();

    if (!m_album)
        return;

    m_busy = true;
    emit busyChanged();

    QMutexLocker lock(&g_mutex);
    m_sp_albumbrowse = sp_albumbrowse_create(QSpotifySession::instance()->spsession(), m_album->spalbum(), callback_albumbrowse_complete, nullptr);
    Q_ASSERT(m_sp_albumbrowse);
    g_albumBrowseObjects.insert(m_sp_albumbrowse, this);
}

int QSpotifyAlbumBrowse::trackCount() const
{
    return m_albumTracks->count();
}

void QSpotifyAlbumBrowse::clearData()
{
    if (m_sp_albumbrowse) {
        g_albumBrowseObjects.remove(m_sp_albumbrowse);
        sp_albumbrowse_release(m_sp_albumbrowse);
        m_sp_albumbrowse = nullptr;
    }
    m_albumTracks->clear();
    m_artistObject = nullptr;

    m_hasMultipleArtists = false;
    m_review.clear();
}

void QSpotifyAlbumBrowse::processData()
{
    if (m_sp_albumbrowse) {
        if (sp_albumbrowse_error(m_sp_albumbrowse) != SP_ERROR_OK)
            return;

        m_albumTracks->clear();
        int c = sp_albumbrowse_num_tracks(m_sp_albumbrowse);
        for (int i = 0; i < c; ++i) {
            if (auto track = sp_albumbrowse_track(m_sp_albumbrowse, i)) {
                auto qtrack = QSpotifyCacheManager::instance().getTrack(track);

                m_albumTracks->appendRow(qtrack);
                connect(qtrack.get(), SIGNAL(isStarredChanged()), this, SIGNAL(isStarredChanged()));
                connect(QSpotifySession::instance()->user()->starredList(), SIGNAL(tracksAdded(QVector<sp_track*>)), qtrack.get(), SLOT(onStarredListTracksAdded(QVector<sp_track*>)));
                connect(QSpotifySession::instance()->user()->starredList(), SIGNAL(tracksRemoved(QVector<sp_track*>)), qtrack.get(), SLOT(onStarredListTracksRemoved(QVector<sp_track*>)));
                if (qtrack->artists() != m_album->artist())
                    m_hasMultipleArtists = true;
                if (i == 0) {
                    m_artistObject = qtrack->artistObject();
                }
            }
        }

        m_review = QString::fromUtf8(sp_albumbrowse_review(m_sp_albumbrowse)).split(QLatin1Char('\n'), QString::SkipEmptyParts);
        if (m_review.isEmpty())
            m_review << QLatin1String("No review available");

        m_busy = false;
        emit busyChanged();

        emit tracksChanged();
    }
}

int QSpotifyAlbumBrowse::totalDuration() const
{
    return m_albumTracks->totalDuration();
}

void QSpotifyAlbumBrowse::play()
{
    if (m_albumTracks->isEmpty())
        return;

    QSpotifySession::instance()->playQueue()->playTrack(m_albumTracks, 0);
}

void QSpotifyAlbumBrowse::enqueue()
{
    if (m_albumTracks->isEmpty())
        return;

    QSpotifySession::instance()->playQueue()->enqueueTracks(m_albumTracks);
}

bool QSpotifyAlbumBrowse::isStarred() const
{
    int c = m_albumTracks->count();
    for (int i = 0; i < c; ++i) {
        if (!m_albumTracks->at(i)->isStarred())
            return false;
    }
    return true;
}

void QSpotifyAlbumBrowse::setStarred(bool s)
{
    int c = m_albumTracks->count();
    const sp_track *tracks[c];
    for (int i = 0; i < c; ++i)
        tracks[i] = m_albumTracks->at(i)->sptrack();
    sp_track_set_starred(QSpotifySession::instance()->spsession(), const_cast<sp_track* const*>(tracks), c, s);
}
