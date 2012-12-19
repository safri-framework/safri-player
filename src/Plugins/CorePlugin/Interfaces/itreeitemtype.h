#ifndef ITREEITEMTYPE_H
#define ITREEITEMTYPE_H

#include <QString>

namespace Core
{
    class Song;
    class DataItem;
    #define BaseDTO DataItem   // TODO: remove!
    /**
        \brief Interface for individual song tree item types

        This is the interface for individual song tree item type implementations.
    */
    class ITreeItemType
    {
        public:

            virtual ~ITreeItemType() = 0;

            /**
                \returns    the type name for this type
            */
            virtual QString getTypeName() = 0;

            /**
                \param      the song for which the node name should be generated
                \returns    the node name for the given song according to the type
            */
            virtual QString getNodeName(Song* song) = 0;

            /**
                \param      the song for which the BaseDTO should returned
                \returns    the BaseDTO for the given song according to the type
            */
            virtual BaseDTO* getNodeDTO(Song* song) = 0;

            /**
                \brief      generates an item hash from the given song
                \param      the song for which the item hash should be gererated
                \returns    the hash
            */
            virtual QString getHash(Song* song) = 0;

            /**
                \brief      generates a list of ContextMenu actions according to this type
                \param      the clicked SongTreeItem
                \returns    a list of QActions, 0 if no context-menu supported
            */
    };
}

#endif // ITREEITEMTYPE_H
