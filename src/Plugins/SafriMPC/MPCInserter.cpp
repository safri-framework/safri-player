#include "MPCInserter.h"
#include <QPushButton>

#include "Interfaces/ICore.h"
#include "Interfaces/IMediaCollection.h"
#include "Interfaces/ICollectionController.h"
#include "CoreData/MediaInfoContainer.h"
#include "pluginmanager.h"

MPCInserter::MPCInserter(QObject *parent) :
    QObject(parent)
{
    _pSocket = new QTcpSocket( this );
    connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );
    _pSocket->connectToHost("127.0.0.1", 6600);
    if( _pSocket->waitForConnected() ) {
        qDebug()<<"CONNECTED";
        _pSocket->write(QString("listallinfo\n").toUtf8());
    }

    Core::IMediaCollection* mediaCollection = Core::ICore::createMediaCollection("org.safri.collection.audio", "MPD Collection");
    _audioCollection = qobject_cast<Core::IAudioCollection*>(mediaCollection);
    PluginSystem::PluginManager::instance()->addObject(_audioCollection);

}

void MPCInserter::readTcpData()
{
    qDebug()<<"-----------------------------------------------------------------";

    Core::MediaInfoContainer* container = 0;
    while(!_pSocket->atEnd())
    {
        QString answer = (_pSocket->readLine());
        qDebug()<<answer;
        answer.remove(answer.size()-1,1);
        if(answer.startsWith("file:"))
        {
            if(container)
            {
                _audioCollection->addMedia(*container);
                delete container;
                container = 0;
            }

            container = new Core::MediaInfoContainer(QUrl(answer));
            container->setMediaInfo(Core::InfoURL, answer.remove(0,6));
            container->setMediaInfo(Core::InfoTitle, answer);
            qDebug()<<answer;
        }

        if(answer.startsWith("Album: "))
        {
            container->setMediaInfo(Core::InfoAlbum, answer.remove(0,7));
        }
        else if(answer.startsWith("Artist: "))
        {
            container->setMediaInfo(Core::InfoArtist, answer.remove(0,8));
        }
        else if(answer.startsWith("Title: "))
        {
            container->setMediaInfo(Core::InfoTitle, answer.remove(0,7));
        }
        else if(answer.startsWith("Genre: "))
        {
            container->setMediaInfo(Core::InfoGenre, answer.remove(0,7));
        }
        else if(answer.startsWith("Time: "))
        {
            container->setMediaInfo(Core::InfoLength, answer.remove(0,6).toInt());
        }
        else if(answer.startsWith("Track: "))
        {
            container->setMediaInfo(Core::InfoTrack, answer.remove(0,7).toInt());
        }
        else if(answer.startsWith("Date: "))
        {
            container->setMediaInfo(Core::InfoYear, answer.remove(0,6).toInt());
        }
        else if(answer.startsWith("Composer: "))
        {
            container->setMediaInfo(Core::InfoAlbumArtist, answer.remove(0,10).toInt());

        }
    }
    delete container;
}

void MPCInserter::test()
{
    _pSocket->write(QString("listallinfo\n").toUtf8());

}
