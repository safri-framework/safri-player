#ifndef RESTPLAYLIST_H
#define RESTPLAYLIST_H

#include <QObject>
#include <QList>
#include <QTimer>

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

            ~RESTPlaylist();

            bool isCurrentMedia(int index);
            void moveMedia(int fromPosition, int toPosition);
            void playPlaylistIndex(int index);
            int getSize();
            int getCurrentMediaPosition();
            void insertNodeAtPosition(int node, int position);
            bool isValid();
            void removeIndexFromPlaylist(int index);
            void setShuffle(bool enabled);
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
            void currentMediaPositionChanged(int oldIndex, int newIndex);
            /**
             * @brief this signal is emitted, when a media was moved on the playlist
             */
            void mediaMoved(int fromPosition, int toPosition);
            void resetModel();
            void beginResetModel();
            void endResetModel();
            void mediaDeleted(int index);


        private:

            RESTClient* client;
            QList<Core::MediaInfoContainer*> songList;
            int currentMediaPosition;
            bool m_valid;
            double displayedPlaylistVersion;
            void requestCurrentPlaylist();
            static const int VERSION_TIMER_INTERVAL = 1000;
            QTimer* versionCheckTimer;
            void setCurrentMediaPosition(int pos);

        private slots:
            void versionTimeoutSlot();
            void comparePlaylistVersion();


    };
}
#endif // RESTPLAYLIST_H
