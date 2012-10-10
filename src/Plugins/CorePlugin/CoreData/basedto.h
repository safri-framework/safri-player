#ifndef BASEDTO_H
#define BASEDTO_H

#include "../CorePlugin_global.h"

#include <QObject>
#include <QString>

namespace Core
{
    class COREPLUGINSHARED_EXPORT BaseDTO : public QObject
    {
        Q_OBJECT

        public:

            /**
                \brief      List of possible DTO Types

                This enumeration describes the types of database entities which a
                BaseDTO can represent.
            */
            enum DTO_TYPE { NONE, GENRE, ALBUM, ARTIST, SONG, CD, TAG, DECADE, YEAR };

            /**
                \brief	Constructs a BaseDTO object which represents the given parameters.
            */
            explicit BaseDTO(int sID, QString sName, DTO_TYPE sType, QObject *parent = 0);
            explicit BaseDTO(int sID, QString sName, DTO_TYPE sType, bool temp, QObject *parent = 0);


            ~BaseDTO();

            BaseDTO::DTO_TYPE

            getType() const;
            int getID() const;
            QString getName() const;
            bool getTemporary() const;


            void setName(QString sName);
            void setID(int sID);

            /**
                \brief	Converts the given DTO_TYPE_NEW to a QString representation.

                \param      type DTO_TYPE to convert
                \returns    the QString representation of the DTO_TYPE
            */
            static QString typeToString(DTO_TYPE type);
            static BaseDTO::DTO_TYPE stringToType(QString type);

        protected:

            //! The type of database entity of the BaseDTO object
            BaseDTO::DTO_TYPE type;

            //! The database record id
            int id;

            //! The database record name
            QString name;

            //! BaseDTO objects, flagged as "temporary", will not be rewritten into the database.
            bool temporary;

    };
}

#endif // BASEDTO_H
