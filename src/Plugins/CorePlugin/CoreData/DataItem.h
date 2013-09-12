#ifndef DATAITEM_H
#define DATAITEM_H

#include "../CorePlugin_global.h"
#include "Item.h"

#include <QObject>
#include <QString>

namespace Core
{
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT DataItem : public Item
    {
        Q_OBJECT

        public:

            /**
                \brief      List of possible data items

                This enumeration describes the types of database entities which a
                data item can represent.
            */
            enum DATA_ITEM_TYPE { NONE, GENRE, ALBUM, ARTIST, SONG, CD, TAG, DECADE, YEAR, AUDIO_STREAM, ALBUMARTIST };

            /**
                \brief	Constructs a data item which represents the given parameters.
            */
            explicit DataItem(int sID, QString sName, DATA_ITEM_TYPE sType, QObject *parent = 0);
            explicit DataItem(int sID, QString sName, DATA_ITEM_TYPE sType, bool temp, QObject *parent = 0);

            ~DataItem();

            DataItem::DATA_ITEM_TYPE getType() const;
            int getID() const;
            QString getName() const;
            bool isTemporary() const;


            void setName(QString sName);
            void setID(int sID);

            /**
                \brief	Converts the given DATA_ITEM_TYPE to a QString representation.

                \param      type DATA_ITEM_TYPE to convert
                \returns    the QString representation of the DATA_ITEM_TYPE
            */
            static QString typeToString(DATA_ITEM_TYPE type);
            static DataItem::DATA_ITEM_TYPE stringToType(QString type);

            IMediaCollection* getMediaCollection();
            void setMediaCollection(IMediaCollection* sMediaCollection);


        protected:

            //! The type of database entity of the data item
            DataItem::DATA_ITEM_TYPE type;

            //! The database record id
            int id;

            //! The database record name
            QString name;

            //! data items flagged as "temporary", will not be rewritten into the database.
            bool temporary;

            IMediaCollection* mediaCollection;

    };
}

#endif // DATAITEM_H
