#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <playlist.h>
#include <QUrl>
class TreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TreeItem(Playlist* playlist, QString type, QString filename, QString text, TreeItem* treeParent, QObject *parent = 0);


    TreeItem* getParent();
    QList<TreeItem*>* getChilds();
    QString getFilename();
    QString getText();
    QString getType();
    Playlist* getPlaylist();

signals:
private:
    Playlist* playlist;
    QString text;
    TreeItem* treeParent;
    QList<TreeItem*>* childs;
    QString filename;
    QString type;

public slots:

};

#endif // TREEITEM_H
