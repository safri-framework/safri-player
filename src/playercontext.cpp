#include "playercontext.h"

PlayerContext::PlayerContext(QObject *parent) :
    QObject(parent), webPage(0)
{
    webPage = new QWebPage();

    templateHead = readTemplate("template_head.html");
    templateTail = readTemplate("template_tail.html");
    templateDiscography = readTemplate("template_discography.html");
    templateAlbum = readTemplate("template_album.html");
    templateTrack = readTemplate("template_track.html");
}


QWebPage* PlayerContext::getWebPage()
{
    return webPage;
}

void PlayerContext::CurrentSourceChanged(AudioFile* file)
{

    /*
    QString noAlbumCover("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");


    QString htmlSource = templateHead + templateDiscography + templateTail;

    htmlSource.replace( QRegExp("%%ARTIST%%"), file->getArtist() );

    QString discography;


    BaseDTO *artistDTO = DatabaseDAO::getDiscographyFromArtist(file->getArtist());
    int albumCount = artistDTO->getChildren()->size();

    for (int i = 0; i < albumCount; i++)
    {
        BaseDTO *albumDTO = artistDTO->getChildren()->at(i);

        if (albumDTO != 0)
        {
            QString albumCoverFilename = DatabaseDAO::getAlbumCover (albumDTO->getID() );
            QString coverData = noAlbumCover;

            if (!albumCoverFilename.trimmed().isEmpty())
            {
                QImage image(albumCoverFilename);

                image = image.scaled(53, 53, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "JPG"); // writes image into ba in PNG format

                coverData = ba.toBase64();

                buffer.close();
            }

            QString album = templateAlbum;
            album.replace( QRegExp("%%ARTIST%%"), file->getArtist() );
            album.replace( QRegExp("%%ALBUM%%"), albumDTO->getText() );
            album.replace( QRegExp("%%ALBUM_ID%%"), QString::number(albumDTO->getID()) );
            album.replace( QRegExp("%%COVER_FILE%%"), albumCoverFilename );
            album.replace( QRegExp("%%COVER_DATA%%"), coverData );

            int songCount = albumDTO->getChildren()->size();
            QString tracks;


            for (int j = 0; j < songCount; j++)
            {
                BaseDTO *song = albumDTO->getChildren()->at(j);

                if (song != 0)
                {
                    QString track = templateTrack;
                    track.replace( QRegExp("%%TRACK_NO%%"), QString::number(j + 1) );
                    track.replace( QRegExp("%%TRACK_TITLE%%"), song->getText() );

                    tracks += "\n" + track;
                }
            }


            album.replace( QRegExp("%%TRACKS%%"), tracks );

            discography += album;
        }


    }


    htmlSource.replace( QRegExp("%%DISCOGRAPHY%%"), discography );


    QFile htmlFile("discography.html");


    if (!htmlFile.open(QFile::WriteOnly))
    {

        qDebug() << "Datei konnte nich geöffnet werden!  " << htmlFile.errorString();
             return;
    }

    QTextStream fileStream(&htmlFile);


    fileStream << htmlSource;

    htmlFile.close();


    //webPage->mainFrame()->setHtml(htmlSource);
    webPage->mainFrame()->setUrl(QUrl("discography.html"));
    */

 //   webPage->mainFrame()->setUrl( QUrl("http://musicbrainz.org/search?query=" + file->getArtist() + "&type=artist"));

        webPage->mainFrame()->setUrl( QUrl("http://de.wikipedia.org/wiki/" + file->getArtist()));


}

QString PlayerContext::readTemplate(QString filename)
{
    QFile file( filename );
    QString content;

    file.open(QIODevice::ReadOnly);
    QTextStream fileStream(&file);

    content = fileStream.readAll();

    file.close();

    return content;
}



/*

void PlayerContext::CurrentSourceChanged(AudioFile* file)
{
    QString head("<html>\n\t<head>\n\t</head>\n\t<body>\n\t\t<script type='text/javascript'> function toggleBlock(ID) {if ( document.getElementById(ID).style.display != 'none' ) {document.getElementById(ID).style.display = 'none';} else {if ( ID[0] != 'T' ) {document.getElementById(ID).style.display = 'inline';} else {document.getElementById(ID).style.display = 'inline';}}}\n\t\t</script>");

    QString noAlbumCover("data:image/png;base64,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");
    QString tail("\n\t</body>\n</html>");

    QString htmlSource = head;


    BaseDTO *artistDTO = DatabaseDAO::getDiscographyFromArtist(file->getArtist());

    int albumCount = artistDTO->getChildren()->size();

    for (int i = 0; i < albumCount; i++)
    {
        BaseDTO *albumDTO = artistDTO->getChildren()->at(i);
        if (albumDTO != 0)
        {
            QString albumCoverFilename = DatabaseDAO::getAlbumCover (albumDTO->getID() );

            QString albumCover = noAlbumCover;

            if (!albumCoverFilename.trimmed().isEmpty())
            {
                QImage image(albumCoverFilename);

                image = image.scaled(53, 53, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "JPG"); // writes image into ba in PNG format

                albumCover = "data:image/png;base64," + ba.toBase64();
            }

            htmlSource += "\n\t\t<table id='album' border=0>\n\t\t<tr class='album-header' onClick=\"toggleBlock('ID" + QString::number(albumDTO->getID()) + "')\">";
            htmlSource += "\n\t\t\t<td>";

            if (!albumCoverFilename.trimmed().isEmpty())
            {
                htmlSource += "<a href=\"file:\\" + albumCoverFilename + "\">";
                htmlSource += "<img src='" + albumCover + "' />";
                htmlSource += "</a>";
            }
            else
            {
                htmlSource += "<img src='" + albumCover + "' />";
            }


            htmlSource += "\n\t\t\t</td><td>" + file->getArtist() + " - " + albumDTO->getText() + "</td></tr>";
        }

        int songCount = albumDTO->getChildren()->size();

        if (songCount > 0)
        {

            htmlSource += "<tr class='album-body'><td colspan=2><table style='display:none;' id='ID" + QString::number(albumDTO->getID()) + "'>";


            for (int j = 0; j < songCount; j++)
            {
                BaseDTO *song = albumDTO->getChildren()->at(j);


                htmlSource += "<tr><td>" + QString::number(j+1) + "</td><td>" + song->getText() + "</td></tr>";

            }

            htmlSource += "</table></td></tr>";

        }

        htmlSource += "</table>";
    }


        htmlSource += tail;


        QFile htmlFile("discography.html");


        if (!htmlFile.open(QFile::WriteOnly))
        {

            qDebug() << "Datei konnte nich geöffnet werden!  " << htmlFile.errorString();
                 return;
        }

        QTextStream fileStream(&htmlFile);


        fileStream << htmlSource;

        htmlFile.close();


    webPage->mainFrame()->setHtml(htmlSource);
}

*/
