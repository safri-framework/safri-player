#ifndef SELECTEDFILESYSTEMINDEXACTIONHANDLER_H
#define SELECTEDFILESYSTEMINDEXACTIONHANDLER_H

#include <QObject>
#include <QModelIndex>
#include <QTreeView>
#include "mainwindow.h"
class selectedFileSystemIndexActionHandler : public QObject
{
    Q_OBJECT
public:
    explicit selectedFileSystemIndexActionHandler(QTreeView* treeview, MainWindow* window, QModelIndex* index, QObject *parent = 0);

signals:
private:

   QTreeView* treeview;
   QModelIndex*  index;
   MainWindow* window;
public slots:
   void addSelectedIndexRecursiveToDatabase();

};

#endif // SELECTEDFILESYSTEMINDEXACTIONHANDLER_H
