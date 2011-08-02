#include "selectedfilesystemindexactionhandler.h"
#include <QFileSystemModel>
selectedFileSystemIndexActionHandler::selectedFileSystemIndexActionHandler(QTreeView* treeview, MainWindow* window, QModelIndex* index, QObject *parent) :
  treeview(treeview), window(window), index(index), QObject(parent)
{
}


void selectedFileSystemIndexActionHandler::addSelectedIndexRecursiveToDatabase()
{




    QFileSystemModel* model = static_cast<QFileSystemModel*>(treeview->model());
    QString path = model->filePath(*index);
    window->addPathRecursiveToDatabase(path);


}
