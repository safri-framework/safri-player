#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDebug>
#include <QDirIterator>
#include <QInputDialog>
#include <QStringListModel>
#include <QIcon>
#include <QSplitter>
#include <QSystemTrayIcon>
#include <QTreeView>
#include<QxtGlobalShortcut>
#include <QAction>

#include "basedto.h"
#include "songtreemodel.h"
#include "songinserter.h"
#include "playlistmodel.h"
#include "taginserter.h"
#include "playerwidget.h"
#include "m3utranslator.h"
#include "aboutdialog.h"
#include "playercontext.h"
#include "headermanager.h"

#include <QSortFilterProxyModel>

class OSDisplay;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
QSortFilterProxyModel *proxyModel;
    bool click;
    Ui::MainWindow *ui;

    QSplitter *splitter;
    QList<BaseDTO::DTO_TYPE> *filters[4];

    PlaylistModel *playlistModel;


    void setupPlaylistModel();

    Playlist* lastPlaylist;

    PlayerContext *context;
    //QList<AudioFile*>* getSelectedAudioFiles();

    QSystemTrayIcon *trayIcon;

    void setupTreeViewTabs();

    QList<QWidget*> *treeViewTabs;
    QList<QTreeView*> *treeViews;
    QList<QLineEdit*> *searchEdits;

    OSDisplay* display;

    headerManager* playlistHeaderManager;
    headerManager* songTableHeaderManager;
    QAction* deletePlaylistItemAction;


private slots:

    void viewSettingsChanged(QString setting);

    void SetupSongTreeModels();

    void insertSongs(QStringList *files);

    void on_toggleView_clicked();
    void on_actionBereinigen_triggered();
    void on_action_Open_Settings_triggered();
    void on_action_about_SaFri_Player_triggered();
    void on_actionRestorePlaylist_triggered();
    void on_playlistView_customContextMenuRequested(QPoint pos);
    void on_fileSystemView_customContextMenuRequested(QPoint pos);
    void on_header_customContextMenuRequested(QPoint pos);
    void on_storedPlaylistView_clicked(QModelIndex index);
    void on_clearPlaylistButton_clicked();
    void on_actualPlayingPlaylistButton_clicked();
    void on_playlistView_doubleClicked(QModelIndex index);

    void on_actionOrdner_hinzufuegen_triggered();
    void on_actionSongs_hinzufuegen_triggered();
    void infoClicked();

    void setupSongTreeModelNumber(int treeviewNumber);

    void songTree_clicked(QModelIndex index);
    void songTree_doubleClicked(QModelIndex index);
    void songList_doubleClicked(QModelIndex index);
    void fileSystem_doubleClicked(QModelIndex index);
    void treeView_customContextMenuRequested(QPoint pos);


    void deleteSelectedSongActionSlot();

    void hideProgressBar();
    void refreshTreeView();

    void savePlaylistActioSlot();

    void DisablePlaylistViewSorting();
    void EnablePlaylistViewSorting();



public slots:

    void addPathRecursiveToDatabase(QString path);
    void updateProgressBar(int value);
    void setProgressBarRange(int min, int max);
    void setProgressBarText(QString text);
    void showNowplayingInfo(AudioFile* af);

    void searchEditTextChanged(const QString &searchString);
    void showFolderInFileSystem(QUrl* file);
};

#endif // MAINWINDOW_H
