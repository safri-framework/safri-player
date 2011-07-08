#ifndef BASEDTO_H
#define BASEDTO_H

#include <QObject>
#include <QString>
#include <QList>

class DTOChanger;

/**
    \brief	Base Data Transfer Object

                Base Data Transfer Object for all database-objects. Different BaseDTO
                Objects can be linked together to build up a hirachical tree-structure
                of database objects. Each BaseDTO gets a type, which indicates the type
                of database object it represents and holds the record ID and the
                corresponding name of it.
*/
class BaseDTO : public QObject
{
    Q_OBJECT

    friend class DTOChanger;



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
        explicit BaseDTO(int sID, QString sText, DTO_TYPE sType, QObject *parent = 0);

        QList<BaseDTO*> *getChildren();
        BaseDTO         *getParentDTO();

        void setChildren(QList<BaseDTO*> *sChilds);
        void setParent(BaseDTO* sParent);

        BaseDTO::DTO_TYPE        getType();
        BaseDTO::DTO_TYPE        getParentType();
        BaseDTO::DTO_TYPE        getChildrenType();

        int getID();
        QString getText() const;


	/**
            \brief	Converts the given DTO_TYPE_NEW to a QString representation.

            \param      type DTO_TYPE to convert
            \returns    the QString representation of the DTO_TYPE
	*/
        static QString typeToString(DTO_TYPE type);
        static BaseDTO::DTO_TYPE stringToType(QString type);
        static bool sortAtoZ( const BaseDTO *dto1, const BaseDTO *dto2);


    protected:

        //! The tree childs of the BaseDTO object
        QList<BaseDTO*> *childs;

        //! The tree parent of the BaseDTO object
        BaseDTO         *parentDTO;

        //! The type of database entity of the BaseDTO object
        BaseDTO::DTO_TYPE        type;

        //! The database record id
        int id;

        //! The database record name
        QString text;

};

#endif // BASEDTO_H
