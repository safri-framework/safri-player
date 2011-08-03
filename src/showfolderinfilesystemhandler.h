#ifndef SHOWFOLDERINFILESYSTEMHANDLER_H
#define SHOWFOLDERINFILESYSTEMHANDLER_H

#include <QObject>
#include "mainwindow.h"

class ShowFolderInFileSystemHandler : public QObject
{
    Q_OBJECT
public:
    explicit ShowFolderInFileSystemHandler(QUrl* path, MainWindow* window, QObject *parent = 0);

signals:

private:
    QUrl* path;
    MainWindow* window;


public slots:
   void showFolderInFileSystem();
   void showFolderInExplorer();
};

#endif // SHOWFOLDERINFILESYSTEMHANDLER_H
