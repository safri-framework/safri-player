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


#ifndef QSPOTIFYALBUMBROWSE_H
#define QSPOTIFYALBUMBROWSE_H

#include <memory>

#include <QtCore/QStringList>

class QSpotifyAlbum;
class QSpotifyTrackList;
class QSpotifyArtist;
struct sp_albumbrowse;

class QSpotifyAlbumBrowse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int trackCount READ trackCount NOTIFY tracksChanged)
    Q_PROPERTY(int totalDuration READ totalDuration NOTIFY tracksChanged)
    Q_PROPERTY(QSpotifyArtist* artistObject READ artistObject NOTIFY tracksChanged)
    Q_PROPERTY(bool isStarred READ isStarred WRITE setStarred NOTIFY isStarredChanged)
    Q_PROPERTY(bool hasMultipleArtists READ hasMultipleArtists NOTIFY albumChanged)
    Q_PROPERTY(QStringList review READ review NOTIFY tracksChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
public:
    QSpotifyAlbumBrowse(QObject *parent = 0);
    ~QSpotifyAlbumBrowse();

    std::shared_ptr<QSpotifyAlbum>  album() const { return m_album; }
    void setAlbum(std::shared_ptr<QSpotifyAlbum> album);

    Q_INVOKABLE QSpotifyTrackList *tracks() const { return m_albumTracks; }
    int trackCount() const;
    int totalDuration() const;
    QSpotifyArtist *artistObject() const { return m_artistObject; }
    bool hasMultipleArtists() const { return m_hasMultipleArtists; }

    QStringList review() const { return m_review; }

    bool busy() const { return m_busy; }

    bool event(QEvent *);

    Q_INVOKABLE void play();
    Q_INVOKABLE void enqueue();

    bool isStarred() const;
    void setStarred(bool s);

Q_SIGNALS:
    void albumChanged();
    void tracksChanged();
    void isStarredChanged();
    void busyChanged();

private:
    void clearData();
    void processData();

    sp_albumbrowse *m_sp_albumbrowse;

    std::shared_ptr<QSpotifyAlbum> m_album;
    QSpotifyTrackList *m_albumTracks;
    QSpotifyArtist *m_artistObject;

    QStringList m_review;

    bool m_hasMultipleArtists;

    bool m_busy;

    friend class QSpotifyPlaylist;
    friend class QSpotifyUser;
};

#endif // QSPOTIFYALBUMBROWSE_H
