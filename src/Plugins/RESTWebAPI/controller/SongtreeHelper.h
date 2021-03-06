#ifndef SONGTREEHELPER_H
#define SONGTREEHELPER_H
#include "Songtree/SongTree.h"
#include <QObject>
#include "Interfaces/ITreeItemType.h"
#include "Interfaces/IAudioCollection.h"
#include "Songtree/SongTreeItem.h"

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
    static QString getMediaFilePath(QString collection, int id, QString type);

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
