#ifndef DATABASEDAO_H
#define DATABASEDAO_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QRegExp>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QImage>
#include <QMap>
#include "dtomapentry.h"


#include "basedto.h"
#include "audiofile.h"

/**
    \brief  This class provides the database access functionality.


*/
class DatabaseDAO
{

    public:

        typedef QMap<QString, QString> ColumnData;
        typedef QList< ColumnData* > DataTable;

    private:

        static QSqlDatabase database;
        static QStringList albumCoverFilePatterns;

        static DataTable* dataTable;

    protected:

    public:
        DatabaseDAO();

        static QSqlDatabase &getDatabase();

        //! Returns the next database record id for the given DTO Type
        static int nextSequenceVal(BaseDTO::DTO_TYPE type);

        static int insertAlbum(QString album, int artistID, QString coverFileName);
        static int insertAlbum(QString album, int artistID);
        static int insertArtist(QString artist);
        static int insertGenre(QString genre);
        static int insertSong(AudioFile &aFile);

        static int insertSongWithCover(AudioFile &aFile);

        static int getIDFromArtist(QString artist);
        static int getIDFromGenre(QString genre);
        static int getIDFromAlbum(QString album, int artistID);


        static void setGenreID(QString filename, int id);
        static void setArtistID(QString filename, int id);
        static void setAlbumID(QString filename, int id);





        static QList<AudioFile*> *getAudioFilesByBaseDTO(BaseDTO *dto);
        static QList<QUrl> getUrlsByBaseDTO(BaseDTO *dto);

        static BaseDTO* getDiscographyFromArtist(QString artist);

        static void refreshAlbumCoverFilePatterns();
        static QString findAlbumCover(AudioFile &file);

        static QString getAlbumCover(int id);
        static QString getAlbumCoverByAudioFile(AudioFile* af);

        static void getSongDTO(BaseDTO* dto, QList<BaseDTO*>*);
        static int deleteSongByID(QList<int>* id);

        static void deleteSongTreeDTOMap(QMap<int, DTOMapEntry*> *current);
        static BaseDTO* BuildSongTree(QList<BaseDTO::DTO_TYPE> *treeHierarchy, DataTable* dataTable = 0);

        static QMap<QUrl, int> *getAllSongsAsUrl();
        static int cleanDatabase();
        static void deleteDoubleDatabaseEntries();
        static void sortTree(BaseDTO *root);

        static void createCoverPreviewImage(QString coverFile, int albumID);
        static void changeAlbumCover(QString filename, int album_id);

        static void loadDataTable();

        static DataTable* searchDataTable(QString searchString);
        static DataTable* getDataTableCopy();
        static DataTable* getDataTablePtr();

        static bool removeModuleSettings(QString modulename);
        static bool insertModuleSettings(QMap<QString, QVariant> settings);
        static QMap<QString, QVariant> getModuleSettings(QString modulename);
        static void saveDirtyEntrys(int flags);
        static void updateSongInfo(ColumnData* data);

        static void deleteUserDataTable(DatabaseDAO::DataTable* table);

    };

#endif // DATABASEDAO_H
