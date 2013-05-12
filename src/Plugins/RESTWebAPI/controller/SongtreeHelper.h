#ifndef SONGTREEHELPER_H
#define SONGTREEHELPER_H
#include "Songtree/songtree.h"
#include <QObject>
#include  "Interfaces/itreeitemtype.h"
#include "Interfaces/IAudioCollection.h"
#include "Songtree/songtreeitem.h"

class SongtreeHelper : public QObject
{
    Q_OBJECT

public:
    explicit SongtreeHelper(QByteArray sessionID, QObject *parent = 0);
    ~SongtreeHelper();
    void buildNewTree();
    QJsonArray getRootNodes();
    QJsonArray getChilds(int id);
    QJsonArray addToPlaylist(int nodeId, int pos);

signals:
    
public slots:
    void sessionExpired(QByteArray id);

private:
    QMap<QUrl, Core::IAudioCollection*> audioCollMap;

    Core::SongTree* currentTree;
    QMap<int, Core::SongTreeItem*> itemMap;
    QMap<Core::SongTreeItem*, int> idMap;
    int idCounter;
    QList<Core::ITreeItemType*>* treeHierarchy;
    QByteArray parentSession;

};

#endif // SONGTREEHELPER_H
