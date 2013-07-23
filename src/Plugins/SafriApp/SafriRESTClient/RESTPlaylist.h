#ifndef RESTPLAYLIST_H
#define RESTPLAYLIST_H

#include <QObject>
#include <QList>

// forward declaration
namespace Core
{
    class MediaInfoContainer;
}

namespace SafriRESTClient
{
    class RESTClient;

    class RESTPlaylist : public QObject
    {
        Q_OBJECT
        public:

            explicit RESTPlaylist(RESTClient *restClient, QObject *parent = 0);

            bool isCurrentMedia(int index);
            void moveMedia(int fromPosition, int toPosition);
            int getSize();
            int getCurrentMediaPosition();
            void insertNodeAtPosition(int node, int position);
            bool isValid();
            Core::MediaInfoContainer* getMediaInfoAt(int position);

        public slots:

            /**
             * @brief slot that handles the network REST reply for the current playlist
             */
            void getCurrentPlaylistReply();

        signals:

            /**
             * @brief this signal is emitted, when the playlist is fully loaded
             */
            void valid(bool);

            /**
             * @brief this signal is emitted, when a media was moved on the playlist
             */
            void mediaMoved(int fromPosition, int toPosition);

        private:

            RESTClient* client;
            QList<Core::MediaInfoContainer*> songList;
            int currentMediaPosition;
            bool m_valid;

            void requestCurrentPlaylist();
    };
}
#endif // RESTPLAYLIST_H
