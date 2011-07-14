 #include "databasedao.h"

QSqlDatabase DatabaseDAO::database;
QStringList DatabaseDAO::albumCoverFilePatterns;

DatabaseDAO::DatabaseDAO()
{
}


QSqlDatabase &DatabaseDAO::getDatabase()
{

    // check if the database is already open
    if ( !database.open() )
    {

        // otherwise open a new database connection

        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("sqlitedatabaseV2.db");

        /*
        database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName("localhost");
        database.setDatabaseName("safriplayer");
        database.setUserName("root");
        database.setPassword("");
        */

        if( !database.open() )
        {
          qDebug() << database.lastError();
          qFatal("Failed to connect to database.");
        }

    }

    return database;
}

QString DatabaseDAO::prepareWHEREStatement(BaseDTO *dto)
{
    QString whereStatement;
    QString wherePart = " %DTOTYPE_ID = %ID ";


    while (dto != 0)
    {
        if (dto->getParentDTO() != 0)
        {
            // replace the possible AND-shadow with a real "AND" operator
            whereStatement.replace(QRegExp("%AND_SHADOW"), " AND ");

            // add a new where part to the where statement
            whereStatement += wherePart;

            // replace the placeholder with apropriate values
            whereStatement.replace(QRegExp("%DTOTYPE"), BaseDTO::typeToString( dto->getType() ));
            whereStatement.replace(QRegExp("%ID"), QString::number( dto->getID() ));

            // insert "shadow" AND operator, unneeded shadows will be cut off after the loop
            whereStatement += " %AND_SHADOW ";

        }
        dto = dto->getParentDTO();
    }

    // cut off unused "shadow" operators
    whereStatement.replace(QRegExp("%AND_SHADOW"), " ");

    return whereStatement;
}

QList<BaseDTO*> *DatabaseDAO::loadDTOChildren(BaseDTO *dto, QList<BaseDTO::DTO_TYPE> *treeHierarchy)
{

    QString sqlStatement;
    QString whereStatement;
    QList<BaseDTO*> *linkedDTOs = new QList<BaseDTO*>();
    BaseDTO *father = dto->getParentDTO();

    int index;

    BaseDTO::DTO_TYPE currentType = dto->getType();

    if (father != 0)
    {
        index = treeHierarchy->indexOf(currentType) + 1;
    }
    else
    {
        index = 0;
    }

    if ( index >= treeHierarchy->length() )
    {
        return 0;
    }

    if ( dto->getChildren() != 0)
    {
        return 0;
    }

    BaseDTO::DTO_TYPE requestType = treeHierarchy->at(index);
    QString reqTypeStr = BaseDTO::typeToString(requestType);

    // if there are already child DTOs loaded return
    if (dto->getChildren() != 0)
    {
        return 0;
    }

    // select the appropriate base SELECT statement according to the requested children DTO Type
    if (requestType == BaseDTO::SONG)
    {
        sqlStatement = "SELECT SONG, ID FROM SONG %WHERE_STATEMENT ORDER BY SONG";

    }
    else
    {
        sqlStatement = "SELECT %TABLE, ID FROM %TABLE WHERE ID IN ( SELECT %TABLE_ID FROM SONG %WHERE_STATEMENT ) ORDER BY %TABLE";

        sqlStatement.replace(QRegExp("%TABLE"), reqTypeStr);
    }

    whereStatement = DatabaseDAO::prepareWHEREStatement(dto);

    if (whereStatement.length() > 0)
    {
        sqlStatement.replace(QRegExp("%WHERE_STATEMENT"), "WHERE " + whereStatement);
    }
    else
    {
        // remove unused placeholder
       sqlStatement.replace(QRegExp("%WHERE_STATEMENT"), " ");
    }


    //qDebug() << sqlStatement;

    QSqlQuery query(getDatabase());
    query.exec(sqlStatement);

    int idIndex = query.record().indexOf("ID");
    int strIndex = query.record().indexOf(reqTypeStr);

    while ( query.next() )
    {
        int id = query.value(idIndex).toInt();
        QString string = query.value(strIndex).toString();

        BaseDTO *base = new BaseDTO(id, string, requestType);

        base->setParent(dto);

        linkedDTOs->append(base);

    }

    return linkedDTOs;

}


void DatabaseDAO::fillDTO(BaseDTO *dto, QList<BaseDTO::DTO_TYPE> *treeHierarchy)
{
    QList<BaseDTO*> *linkedDTOs = DatabaseDAO::loadDTOChildren(dto, treeHierarchy);

    if ( (linkedDTOs != 0) && (linkedDTOs->length() > 0))
    {
        dto->setChildren(linkedDTOs);
    }
}




int DatabaseDAO::getIDFromArtist(QString artist)
{

    QString queryStmt = "SELECT ID FROM ARTIST WHERE ARTIST = :ARTIST";

    QSqlQuery query(getDatabase());

    query.prepare(queryStmt);
    query.bindValue(":ARTIST", artist);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }

    int id = -1;

    if ( query.next() )
    {
        id = query.value( query.record().indexOf("ID") ).toInt();
    }


    return id;

}

int DatabaseDAO::getIDFromGenre(QString genre)
{

    QString queryStmt = "SELECT ID FROM GENRE WHERE GENRE = :GENRE";

    QSqlQuery query(getDatabase());

    query.prepare(queryStmt);
    query.bindValue(":GENRE", genre);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }

    int id = -1;

    if ( query.next() )
    {
        id = query.value( query.record().indexOf("ID") ).toInt();
    }


    return id;

}

int DatabaseDAO::getIDFromAlbum(QString album, int artistID)
{

    QString queryStmt = "SELECT ID FROM ALBUM WHERE ARTIST_ID = :ARTIST_ID AND ALBUM = :ALBUM";

    QSqlQuery query(getDatabase());


    query.prepare(queryStmt);
    query.bindValue(":ARTIST_ID", artistID);
    query.bindValue(":ALBUM", album);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }

    int id = -1;

    if ( query.next() )
    {
        id = query.value( query.record().indexOf("ID") ).toInt();
    }


    return id;

}


int DatabaseDAO::nextSequenceVal(BaseDTO::DTO_TYPE type)
{

    QString sequenceName = "SEQ_%DTOTYPE_ID";
    sequenceName.replace(QRegExp("%DTOTYPE"), BaseDTO::typeToString(type));


    QString updateStmt = "UPDATE SEQUENCES SET %SEQ_NAME = %SEQ_NAME + 1";
    QString selectStmt = "SELECT %SEQ_NAME FROM SEQUENCES";

    updateStmt.replace(QRegExp("%SEQ_NAME"), sequenceName);
    selectStmt.replace(QRegExp("%SEQ_NAME"), sequenceName);

    QSqlQuery query(getDatabase());

    if ( !query.exec(updateStmt))
    {
        qDebug() << "ERROR: " << updateStmt;
    }

    if ( !query.exec(selectStmt))
    {
        qDebug() << "ERROR: " << selectStmt;
    }

    int id = -1;

    if ( query.next() )
    {
        id = query.value( query.record().indexOf(sequenceName) ).toInt();
    }

    return id;
}

int DatabaseDAO::insertAlbum(QString album, int artistID)
{

    QSqlQuery query(getDatabase());
    int id = DatabaseDAO::nextSequenceVal(BaseDTO::ALBUM);


    QString queryString = "INSERT INTO ALBUM (ID, ALBUM, ARTIST_ID) VALUES( :ID, :ALBUM, :ARTIST_ID )";

    query.prepare(queryString);
    query.bindValue(":ID", id);
    query.bindValue(":ALBUM", album);
    query.bindValue(":ARTIST_ID", artistID);



    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

    return id;

}

int DatabaseDAO::insertAlbum(QString album, int artistID, QString coverFileName)
{

    QSqlQuery query(getDatabase());
    int id = DatabaseDAO::nextSequenceVal(BaseDTO::ALBUM);

    QString queryString = "INSERT INTO ALBUM (ID, ALBUM, ARTIST_ID, ALBUM_COVER) VALUES( :ID, :ALBUM, :ARTIST_ID, :COVER_FILE )";

    query.prepare(queryString);
    query.bindValue(":ID", id);
    query.bindValue(":ALBUM", album);
    query.bindValue(":ARTIST_ID", artistID);
    query.bindValue(":COVER_FILE", coverFileName);


    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

    return id;
}

int DatabaseDAO::insertArtist(QString artist)
{

    QSqlQuery query(getDatabase());
    int id = DatabaseDAO::nextSequenceVal(BaseDTO::ARTIST);

    QString queryString = "INSERT INTO ARTIST (ID, ARTIST) VALUES ( :ID, :ARTIST )";

    query.prepare(queryString);
    query.bindValue(":ID", id);
    query.bindValue(":ARTISTS", artist);


    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

    return id;

}

int DatabaseDAO::insertGenre(QString genre)
{

    QSqlQuery query(getDatabase());
    int id = DatabaseDAO::nextSequenceVal(BaseDTO::GENRE);


    QString queryString = "INSERT INTO GENRE (ID, GENRE) VALUES (:ID, :GENRE)";

    query.prepare(queryString);
    query.bindValue(":ID", id);
    query.bindValue(":GENRE", genre);


    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

    return id;

}


int DatabaseDAO::insertSongWithCover(AudioFile &aFile)
{
    QSqlQuery query(getDatabase());

    int song_id = DatabaseDAO::nextSequenceVal(BaseDTO::SONG);
    int artist_id = DatabaseDAO::getIDFromArtist(aFile.getArtist());
    int album_id = DatabaseDAO::getIDFromAlbum(aFile.getAlbum(), artist_id);
    int genre_id = DatabaseDAO::getIDFromGenre(aFile.getGenre());

    if (artist_id < 0)
        artist_id = DatabaseDAO::insertArtist(aFile.getArtist());

    if (album_id < 0)
    {
        if (aFile.getAlbum() != "Unbekannt")
        {
            QString albumCoverFile = findAlbumCover(aFile).trimmed();
            album_id = DatabaseDAO::insertAlbum(aFile.getAlbum(), artist_id, albumCoverFile);


            if ( !albumCoverFile.isEmpty() )
            {
                DatabaseDAO::createCoverPreviewImage(albumCoverFile, album_id);
            }

        }
        else
        {
            qDebug() << "Album unbekannt";
        }
    }

    if (genre_id < 0)
        genre_id = DatabaseDAO::insertGenre(aFile.getGenre());


    QString insertStmt = "INSERT INTO SONG (ID, SONG, ARTIST_ID, GENRE_ID, ALBUM_ID, YEAR, COMMENT, TRACK_NUMBER, FILENAME) "
                         "VALUES (:ID, :SONG, :ARTIST_ID, :GENRE_ID, :ALBUM_ID, :YEAR, :COMMENT, :TRACK, :FILENAME)";

    query.prepare(insertStmt);
        query.bindValue(":ID", song_id);
        query.bindValue(":SONG", aFile.getTitle());
        query.bindValue(":ARTIST_ID", artist_id);
        query.bindValue(":GENRE_ID", genre_id);
        query.bindValue(":ALBUM_ID", album_id);
        query.bindValue(":YEAR", aFile.getYear());
        query.bindValue(":COMMENT", aFile.getComment());
        query.bindValue(":TRACK", aFile.getTrack());
        query.bindValue(":FILENAME", aFile.fileName());


        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << query.executedQuery();
        }

        return song_id;

}

void DatabaseDAO::createCoverPreviewImage(QString coverFile, int album_id)
{
    QImage image(coverFile);

    if ( !image.isNull() )
    {
        image = image.scaled(43, 43, Qt::IgnoreAspectRatio, Qt::FastTransformation);

        image.save("covers\\" + QString::number(album_id) + ".jpg", "JPG", 60);
    }
}

int DatabaseDAO::insertSong(AudioFile &aFile)
{
    QSqlQuery query(getDatabase());

    int song_id = DatabaseDAO::nextSequenceVal(BaseDTO::SONG);
    int artist_id = DatabaseDAO::getIDFromArtist(aFile.getArtist());
    int album_id = DatabaseDAO::getIDFromAlbum(aFile.getAlbum(), artist_id);
    int genre_id = DatabaseDAO::getIDFromGenre(aFile.getGenre());

    if (artist_id < 0)
        artist_id = DatabaseDAO::insertArtist(aFile.getArtist());

    if (album_id < 0)
        album_id = DatabaseDAO::insertAlbum(aFile.getAlbum(), artist_id);

    if (genre_id < 0)
        genre_id = DatabaseDAO::insertGenre(aFile.getGenre());


    QString insertStmt = "INSERT INTO SONG (ID, SONG, ARTIST_ID, GENRE_ID, ALBUM_ID, YEAR, COMMENT, TRACK_NUMBER, FILENAME) "
                         "VALUES (:ID, :SONG, :ARTIST_ID, :GENRE_ID, :ALBUM_ID, :YEAR, :COMMENT, :TRACK, :FILENAME)";

    query.prepare(insertStmt);
        query.bindValue(":ID", song_id);
        query.bindValue(":SONG", aFile.getTitle());
        query.bindValue(":ARTIST_ID", artist_id);
        query.bindValue(":GENRE_ID", genre_id);
        query.bindValue(":ALBUM_ID", album_id);
        query.bindValue(":YEAR", aFile.getYear());
        query.bindValue(":COMMENT", aFile.getComment());
        query.bindValue(":TRACK", aFile.getTrack());
        query.bindValue(":FILENAME", aFile.fileName());


        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << query.executedQuery();
        }

        return song_id;

}

QList<QUrl> DatabaseDAO::getUrlsByBaseDTO(BaseDTO *dto)
{

    // Kopieren, damit die Datenstruktur des TreeModels nicht verändert wird
    // linkedDTOs werden nicht gesetzt, damit die loadLinkedDTOs die geänderten DTOs nachläd
    BaseDTO *dto_copy = new BaseDTO( dto->getID(), dto->getText(), dto->getType());
    dto_copy->setParent(dto->getParentDTO());

    QList<QUrl> urlCollection;
    QList<BaseDTO*> *songs;

    if (dto->getType() != BaseDTO::SONG)
    {

        songs = new QList<BaseDTO*>();
        getSongDTO(dto, songs);

//        QList<BaseDTO::DTO_TYPE> *songFilter = new QList<BaseDTO::DTO_TYPE>();
//        while (dto != 0)
//        {
//           songFilter->insert(0, dto->getType());
//           dto = dto->getParentDTO();
//        }


//        int filterIndex = songFilter->indexOf(dto_copy->getType()) + 1;

//        songFilter->insert(filterIndex, BaseDTO::SONG);


//         songs = DatabaseDAO::loadDTOChildren(dto_copy, songFilter);

    }
    else
    {
        songs = new QList<BaseDTO*>();
        songs->append(dto);

    }

















    QString filename;
    QString queryString = "SELECT filename FROM Song WHERE ID IN (";
    QSqlQuery query;


    for (int counter = 0; counter < songs->length(); counter ++)
    {

        queryString.append(QString::number(songs->at(counter)->getID()));
        if (counter < songs->length()-1)
        {
           queryString.append(", ");
        }

    }


    queryString.append(" ) ORDER BY filename");
    // qDebug() << queryString;

    if ( !query.exec(queryString))
    {
        // qDebug() << "ERROR: " << queryString;
    }
    while ( query.next() )
    {
       filename  = query.value( query.record().indexOf("FILENAME") ).toString();
       urlCollection.append(QUrl::fromLocalFile(filename));

    }


    return urlCollection;

}


void DatabaseDAO::getSongDTO(BaseDTO* dtos, QList<BaseDTO*>* list)
{
if (dtos->getChildren())
    {
    for (int i = 0; i < dtos->getChildren()->length(); i++)
    {


        getSongDTO(dtos->getChildren()->at(i), list);



    }



}
if (dtos->getType() == BaseDTO::SONG)
{
    list->append(dtos);
}

}



QList<AudioFile*> *DatabaseDAO::getAudioFilesByBaseDTO(BaseDTO *dto)
{
    QList<QUrl> urls = DatabaseDAO::getUrlsByBaseDTO(dto);
    QList<AudioFile*> *audioFiles = new QList<AudioFile*>();

    foreach (QUrl url, urls)
    {
        AudioFile *newAudioFile = new AudioFile(url.toLocalFile());
        audioFiles->append(newAudioFile);
    }

    return audioFiles;
}

BaseDTO* DatabaseDAO::getDiscographyFromArtist(QString artist)
{
    int id = getIDFromArtist(artist);

    BaseDTO *rootDTO = new BaseDTO(0, "", BaseDTO::ARTIST);
    BaseDTO *artistDTO = new BaseDTO(id, artist, BaseDTO::ARTIST);

    artistDTO->setParent(rootDTO);

    QList<BaseDTO*> *children = new QList<BaseDTO*>();
    children->append(artistDTO);

    rootDTO->setChildren(children);

    QList<BaseDTO::DTO_TYPE> treeHierarchy;

    treeHierarchy.append(BaseDTO::ARTIST);
    treeHierarchy.append(BaseDTO::ALBUM);
    treeHierarchy.append(BaseDTO::SONG);

    fillDTO(artistDTO, &treeHierarchy);

    int albumCount = artistDTO->getChildren()->size();

    for (int i = 0; i < albumCount; i++)
    {
        fillDTO(artistDTO->getChildren()->at(i), &treeHierarchy);
    }

    return artistDTO;
}

void DatabaseDAO::loadAlbumCoverFilePatterns()
{
    albumCoverFilePatterns = getSetting("ALBUM_COVER_FILENAME");
}


QString DatabaseDAO::findAlbumCover(AudioFile &file)
{
    QFileInfo fInfo(file.url().toLocalFile());
    QDir baseDir(fInfo.path());

    for (int i = 0; i < albumCoverFilePatterns.size(); i++)
    {
        QString expandedCoverFilename = albumCoverFilePatterns.at(i);

        expandedCoverFilename.replace(QRegExp("%ARTIST"), file.getArtist());
        expandedCoverFilename.replace(QRegExp("%ALBUM"), file.getAlbum());

        QFileInfo testForAlbumImage(baseDir, expandedCoverFilename);

        //qDebug() << "testing for " << testForAlbumImage.filePath() << " existing: " << testForAlbumImage.exists();

        if ( testForAlbumImage.exists() )
        {          

            return testForAlbumImage.filePath();
        }
    }

    return "";
}

QString DatabaseDAO::getAlbumCover(int album_id)
{
    QString queryStmt = "SELECT ALBUM_COVER FROM ALBUM WHERE ID = :ID";

    QSqlQuery query(getDatabase());

    query.prepare(queryStmt);
    query.bindValue(":ID", album_id);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }

    QString fileName;

    if ( query.next() )
    {
        fileName = query.value( query.record().indexOf("ALBUM_COVER") ).toString();
    }


    return fileName;
}

QStringList DatabaseDAO::getSetting(QString setting)
{
    QString queryStmt = "SELECT VALUE FROM Settings WHERE Setting = :SETTING";
    QStringList values;
    QSqlQuery query(getDatabase());

    query.prepare(queryStmt);
    query.bindValue(":SETTING", setting);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }

    while ( query.next() )
    {
        values.append( query.value(0).toString() );
    }

    return values;
}

void DatabaseDAO::deleteSetting(QString setting)
{
    QString queryStmt = "DELETE FROM Settings WHERE Setting = :SETTING";
    QSqlQuery query(getDatabase());

    query.prepare(queryStmt);
    query.bindValue(":SETTING", setting);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryStmt;
    }
}

void DatabaseDAO::insertSetting(QString setting, QString value)
{
    QSqlQuery query(getDatabase());

    QString queryString = "INSERT INTO Settings (Setting, Value) VALUES ( :SETTING, :VALUE)";

    query.prepare(queryString);
    query.bindValue(":SETTING", setting);
    query.bindValue(":VALUE", value);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

}








void DatabaseDAO::LoadSongTree(BaseDTO *rootDTO, QList<BaseDTO::DTO_TYPE> *treeHierarchy)
{
    QSqlQuery query(getDatabase());

    QString queryString = "SELECT song.year, song, song.id AS SongID, genre, genre.id AS GenreID, album, album.id AS AlbumID, artist, artist.id AS ArtistID FROM song, genre, album, artist WHERE (song.album_id = album.id) AND song.genre_id = genre.id AND song.artist_id = artist.id  ;";
    QMap<int, DTOMapEntry*> *rootMap = new QMap<int, DTOMapEntry*>();

    query.prepare(queryString);

    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
        qDebug() << query.lastError();
    }

    while ( query.next() )
    {

        QMap<int, DTOMapEntry*> *currentMap = rootMap;
        BaseDTO *currentDTO = rootDTO;

        for (int i = 0; i < treeHierarchy->length(); i++)
        {

            int id ;
            QString text;



            BaseDTO::DTO_TYPE currentType = treeHierarchy->at(i);

            int year;


            switch (currentType)
            {
                case BaseDTO::DECADE:

                    year  = query.value( query.record().indexOf("year" ) ).toInt();
                    if (year != 0)
                    {
                        id = year - (year % 10);
                        text = QString::number(id);

                    }
                    else
                    {
                        id = 0;
                        text = "Unbekannt";
                    }
                    break;

                case BaseDTO::YEAR:

                    year  = query.value( query.record().indexOf("year" ) ).toInt();
                    if (year != 0)
                    {
                        id = year;
                        text = QString::number(id);

                    }
                    else
                    {
                        id = 0;
                        text = "Unbekannt";
                    }

                    break;

                default:

                    id = query.value( query.record().indexOf( BaseDTO::typeToString(currentType) + "ID" ) ).toInt();
                    text = query.value( query.record().indexOf( BaseDTO::typeToString(currentType)) ).toString();


                    break;
            }


            const DTOMapEntry *mapEntry = currentMap->value(id);

            if ( !mapEntry )
            {
                BaseDTO *newDTO = new BaseDTO(id, text, currentType);
                newDTO->setParent(currentDTO);
                currentDTO->getChildren()->append(newDTO);

                QMap<int, DTOMapEntry*> *newMap = new QMap<int, DTOMapEntry*>();

                DTOMapEntry *newMapEntry = new DTOMapEntry(newMap, newDTO);
                currentMap->insert(id, newMapEntry);

                currentMap = newMap;
                currentDTO = newDTO;
            }
            else
            {
                currentMap = mapEntry->getChildren();
                currentDTO = mapEntry->getDTO();

            }



        }


    }

    sortTree(rootDTO);
}

QMap<QUrl, int> *DatabaseDAO::getAllSongsAsUrl()
{
    QSqlQuery query(getDatabase());
    QString queryString = "SELECT filename, id FROM song";


    QMap<QUrl, int>* fileMap = new QMap<QUrl, int>();

    query.prepare(queryString);


    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }

    while ( query.next() )
    {
        QString filename  = query.value( query.record().indexOf("FILENAME") ).toString();
        int id = query.value( query.record().indexOf("id") ).toInt();
        fileMap->insert(QUrl::fromLocalFile(filename), id);
    }

    return fileMap;

}

int DatabaseDAO::cleanDatabase()
{
    QList<int>* toDelete = new QList<int>;

    QMap<QUrl, int>* pathlist = getAllSongsAsUrl();
    QList<QUrl> keys = pathlist->keys();

    for (int i = 0; i < keys.length(); i++)
    {
        QFileInfo* file = new QFileInfo(keys.at(i).toLocalFile());
        if (!file->exists())
        {
         toDelete->append(pathlist->value(keys.at(i)));
        }


    }

    return deleteSongByID(toDelete);
}


int DatabaseDAO::deleteSongByID(QList<int>* id)
{
    if (id->length()>0)
    {

        QSqlQuery query(getDatabase());
        QString queryString = "DELETE from Song where id in (";

        for (int i = 0; i < id->length()- 1; i++)
        {
            queryString.append(QString::number(id->at(i))+", ");

        }

        queryString.append(QString::number(id->at(id->length()-1)) + ")");
        query.prepare(queryString);
        if (!query.exec())
        {
            qDebug() <<"ERROR: "<< queryString;
            return -1;
        }

    }


return id->length();


}

void DatabaseDAO::sortTree(BaseDTO *root)
{
    for (int i = 0; root->getChildren() != 0 && i < root->getChildren()->length();i++)
    {
        sortTree(root->getChildren()->at(i));
    }
    qSort(root->getChildren()->begin(),root->getChildren()->end(), BaseDTO::sortAtoZ);

}






void DatabaseDAO::deleteDoubleDatabaseEntries()
{
    QSqlQuery query(getDatabase());
    QSqlQuery query2(getDatabase());
    QString queryString = "Select filename, id from song group by filename HAVING count(*) > 1";
    QString deleteQueryString = "Delete FROM song WHERE filename = ? AND id <> ?";



    query.prepare(queryString);


    if ( !query.exec())
    {
        qDebug() << "ERROR: " << queryString;
    }



    while ( query.next() )
    {
        QString filename  = query.value( query.record().indexOf("filename") ).toString();
        int id = query.value( query.record().indexOf("id") ).toInt();
        query2.prepare(deleteQueryString);
        query2.bindValue(0, filename);
        query2.bindValue(1, id);

        if (!query2.exec())
        {
            qDebug()<<"ERROR:" << query.lastError();
            qDebug()<<query.lastQuery();
        }

    }
}


void DatabaseDAO::changeAlbumCover(QString filename, int album_id)
{
    QSqlQuery query(getDatabase());
    QString updateString = "UPDATE Album SET album_cover = :FILENAME WHERE id = :ID";


    query.prepare(updateString);
    query.bindValue(":FILENAME", filename);
    query.bindValue(":ID", album_id);

    if ( !query.exec() )
    {
        qDebug() << "ERROR: " << updateString << query.lastError();
    }
    else
    {
        DatabaseDAO::createCoverPreviewImage(filename, album_id);
    }
}
QMap<QString, QString>* searchMap = 0;

QList<QString>* DatabaseDAO::getPathlistBySearchString(QString searchString)
{
    QList<QString>* result = new QList<QString>;


    if (!searchMap)
    {
        qDebug()<<"nur einmal!";
        QSqlQuery query(getDatabase());

        QString queryString = "SELECT filename,  song, artist, album FROM song, artist, album WHERE (song.album_id = album.id) AND (song.artist_id = artist.id)";
        //                              0         1       2       3

        searchMap = new QMap<QString, QString>;

        query.prepare(queryString);

        if ( !query.exec())
        {
            qDebug() << "ERROR: " << queryString;
            qDebug() << query.lastError();
        }

        while ( query.next() )
        {
            QString searchIndex;
            searchIndex = query.value(1).toString()+" ";
            searchIndex.append(query.value(2).toString()+" ");
            searchIndex.append(query.value(3).toString());

            searchMap->insert(searchIndex, query.value(0).toString());

        }


    }

    QMapIterator<QString, QString> i(*searchMap);
        while (i.hasNext())
    {
        i.next();
        if (i.key().toLower().contains(searchString.toLower()))
        {
            result->append(i.value());

        }


    }

return result;

}



void DatabaseDAO::resetSearchMap()
{

    delete searchMap;

    searchMap = 0;

}
