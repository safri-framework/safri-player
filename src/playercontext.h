#ifndef PLAYERCONTEXT_H
#define PLAYERCONTEXT_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QBuffer>
#include <QByteArray>
#include <QTextStream>
#include <QFile>

#include "audiofile.h"
#include "databasedao.h"

class PlayerContext : public QObject
{
        Q_OBJECT
    public:

        explicit PlayerContext(QObject *parent = 0);
        QWebPage* getWebPage();

    private:

        QWebPage *webPage;
        QString templateHead;
        QString templateTail;
        QString templateDiscography;
        QString templateAlbum;
        QString templateTrack;

        QString readTemplate(QString filename);

    signals:

    public slots:

        void CurrentSourceChanged(AudioFile*);

};

#endif // PLAYERCONTEXT_H
