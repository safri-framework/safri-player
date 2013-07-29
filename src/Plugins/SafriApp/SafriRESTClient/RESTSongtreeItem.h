#ifndef RESTSONGTREEITEM_H
#define RESTSONGTREEITEM_H

#include "CoreSupply/BasicTreeItem.h"

namespace SafriRESTClient
{
    class RESTClient;

    /**
     * @brief The RESTSongtreeItem class extends the BasicTreeItem with
     *        the ability to load it's child data from the Safri REST API
     *        on demand. On creation the number of childs must already be known
     *        an provided as prefetchedChildCount. The actual childs are
     *        fetched transparently on the first access by getChildAt(...).
     */
    class RESTSongtreeItem : public Core::BasicTreeItem
    {
        friend class RESTSongtree;

        Q_OBJECT
        public:

            explicit RESTSongtreeItem(RESTClient* client, int itemID = -1, int prefetchedChildCount = 0,
                                      Core::BasicTreeItem *parentItem = 0, QObject *parent = 0);

            explicit RESTSongtreeItem(RESTClient* client, QObject *parent);

            /**
             * @brief Overrides the basic implementation to handle the transparently
             *        fetched child data.
             * @return the number of child items.
             */
            virtual int             getChildCount();

            /**
             * @brief Overrides the basic implementation to handle the transparently
             *        fetched child data. On first call this function fetches the child
             *        data from the Safri REST API synchronously.
             * @param index of the wanted child.
             * @return the child item at the given index.
             */
            virtual ITreeItem*      getChildAt(int index);

        public slots:

            /**
             * @brief slot that handles the network REST reply
             */
            void                    RESTReply();

        private:

            void                    fetchChilds();

            RESTClient* client;

            //! holds the state if the childs are already loaded
            bool childsFetched;

            //! holds the number of childs before the childs are actualy loaded
            int prefetchedChildCount;

            //! ID of the tree item provided by the Safri REST API
            int itemID;
    };
}

#endif // RESTSONGTREEITEM_H
