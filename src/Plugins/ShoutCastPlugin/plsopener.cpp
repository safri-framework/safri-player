#include "plsopener.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "Interfaces/IPlaylistFactory.h"
#include "shoutcaststream.h"
#include "Interfaces/ICore.h"
#include <QHash>
#include "Interfaces/IPlaybackController.h"

PlsOpener::PlsOpener(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

}

void PlsOpener::test()
{
    QString str = QString("[playlist]\n");
                str.append("NumberOfEntries=1\n");
                str.append("File1=http://62.75.157.223:8000/nerds\n");
                str.append("Title1=Nerds United Radio\n");
                str.append("Length1=-1\n");
                str.append("Version=2\n");
                playPlsFile(str);
}

void PlsOpener::playPlsFromWebUrl(QUrl url)
{
    networkManager->get(QNetworkRequest(url));
}

void PlsOpener::requestFinished(QNetworkReply *reply)
{
    QString replyString;
    if(reply->error() == QNetworkReply::NoError)
    {
            if (reply->isReadable())
            {
                //Assuming this is a human readable file replyString now contains the file
                replyString = QString::fromUtf8(reply->readAll().data());
                qDebug()<<replyString;
                playPlsFile(replyString);
            }
            reply->deleteLater();
    }
}

void PlsOpener::playPlsFile(QString pls)
{
    QHash<QString, int> urls;
    QHash<int, QString> descriptions;

    if(pls.contains("Version=2") && pls.contains("[playlist]"))
    {
        QTextStream fileStream(&pls);
        while (!fileStream.atEnd())
        {
            QString path = fileStream.readLine();
            //qDebug() <<"PATH:"<<path;
            if(path.startsWith("File"))
            {
                if(path.split("=").size() > 0)
                {
                    QString prefix = path.split("=").at(0);
                    QString url = path.split("=").at(1);

                    int id = prefix.at(prefix.size()-1).digitValue();

                    //qDebug()<<"ID"<<id;
                    //qDebug()<<"URL"<< url;
                    urls.insert(url, id);
                }
            }
            if(path.startsWith("Title"))
            {
                if(path.split("=").size() > 0)
                {
                    QString prefix = path.split("=").at(0);
                    QString title = path.split("=").at(1);
                    int id = prefix.at(prefix.size()-1).digitValue();
                    //qDebug()<<"ID"<<id;
                    //qDebug()<<"TITLE"<< title;
                    descriptions.insert(id, title);
                }
            }

        }


        QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
        for(int i=0; i < urls.size(); i++)
        {
            qDebug()<<"Hallo";
            QString url = urls.keys().at(i);
            int ID = urls.value(url);
            QString description = descriptions.value(ID);
            ShoutCastStream* stream = new ShoutCastStream(description, url);
            playList->appendMedia(stream);

        }
        Core::IPlaybackController* controller  = Core::ICore::playbackController();
        controller->stopAction()->trigger();
        controller->setPlaylist(playList);
        controller->playAction()->trigger();
    }
}

