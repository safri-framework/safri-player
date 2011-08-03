#include "showfolderinfilesystemhandler.h"
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>
ShowFolderInFileSystemHandler::ShowFolderInFileSystemHandler(QUrl* path, MainWindow* window, QObject *parent) :
     window(window), QObject(parent)
{
    QFileInfo fi(path->toString());
    this->path = new QUrl( fi.absolutePath());
    qDebug()<<this->path->toString();
}


void ShowFolderInFileSystemHandler::showFolderInFileSystem()
{

    window->showFolderInFileSystem(path);
    qDebug()<<"trigger";
}

void ShowFolderInFileSystemHandler::showFolderInExplorer()
{


    QString path2 = QDir::toNativeSeparators(path->toString());
    QDesktopServices::openUrl(QUrl("file:///" + path2));
}
