#ifndef AUDIOSQLSTORAGEADAPTER_H
#define AUDIOSQLSTORAGEADAPTER_H

#include "sqlstorageadapter.h"
#include <QUrl>

class AudioSQLStorageAdapter : public SQLStorageAdapter
{
    Q_OBJECT
    public:
        explicit AudioSQLStorageAdapter(QUrl filePath, QObject *parent = 0);

        virtual bool writeTableForDataItemType(Core::ITableModel* model, Core::DataItem::DATA_ITEM_TYPE type);
        virtual bool writeTable(Core::ITableModel* model, QString table);


    protected:

        virtual bool createDatabase();
        virtual bool checkDatabaseVersion();
        virtual bool checkIfDatabaseExists();

    private:

        bool writeGenreTable(Core::ITableModel* model);
        bool writeArtistTable(Core::ITableModel* model);
        bool writeAlbumTable(Core::ITableModel* model);
        bool writeArtistToAlbumTable(Core::ITableModel* model);
        bool writeSongTable(Core::ITableModel* model);
};

#endif // AUDIOSQLSTORAGEADAPTER_H
