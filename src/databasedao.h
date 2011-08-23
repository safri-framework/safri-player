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

        /**
            \brief  Prepares the SQL WHERE statement to load the DTO children of a BaseDTO object

                    This function prepares the SQL WHERE statement to load only DTO objects
                    which has the given attributes along the tree path up to the root. (I.e.
                    load only songs from the genre rock and a particular artist.)

            \returns the sql where statement
        */
        static QString prepareWHEREStatement(BaseDTO *dto);


    public:
        DatabaseDAO();

        static QSqlDatabase &getDatabase();

        /**
            \brief Loads the tree DTO children of the given DTO object

            This function returns the BaseDTO objects (DTO-children) for the next tree level of
            the given dto object. The requested tree hierachy can be specified with the
            treeHierarchy parameter.

            \param  the parent dto object
            \param  the requested tree hierarchy
            \returns the child DTO objects
        */
        static QList<BaseDTO*> *loadDTOChildren(BaseDTO *dto, QList<BaseDTO::DTO_TYPE> *treeHierarchy);

        /**
            \brief  Fills (respectively  sets) the child DTO objects of the given DTO object.

            \param  the parent dto object
            \param  the requested tree hierarchy
        */
        static void fillDTO(BaseDTO *dto, QList<BaseDTO::DTO_TYPE> *treeHierarchy);

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

    };

#endif // DATABASEDAO_H
