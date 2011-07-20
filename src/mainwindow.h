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


#include "basedto.h"
#include "songtreemodel.h"
#include "songinserter.h"
#include "playlistmodel.h"
#include "taginserter.h"
#include "playerwidget.h"
#include "m3utranslator.h"
#include "aboutdialog.h"
#include "playercontext.h"
#include "settingsdialog.h"

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

    bool click;
    Ui::MainWindow *ui;


    QList<BaseDTO::DTO_TYPE> *filters[4];

    PlaylistModel *playlistModel;

    void SetupSongTreeModels();
    void setupPlaylistModel();

    Playlist* lastPlaylist;

    PlayerContext *context;
    void insertSongs(QStringList *files);

    QSystemTrayIcon *trayIcon;

    void setupTreeViewTabs();

    QList<QWidget*> *treeViewTabs;
    QList<QTreeView*> *treeViews;
    QList<QLineEdit*> *searchEdits;


private slots:





    void on_toggleView_clicked();
    void on_actionBereinigen_triggered();
    void on_action_Open_Settings_triggered();
    void on_action_about_SaFri_Player_triggered();
    void on_actionRestorePlaylist_triggered();
    void on_playlistView_customContextMenuRequested(QPoint pos);
    void on_storedPlaylistView_clicked(QModelIndex index);
    void on_clearPlaylistButton_clicked();
    void on_actualPlayingPlaylistButton_clicked();
    void on_playlistView_doubleClicked(QModelIndex index);
    void on_actionOrdner_hinzufuegen_triggered();
    void on_actionSongs_hinzufuegen_triggered();


    void songTree_clicked(QModelIndex index);
    void songTree_doubleClicked(QModelIndex index);

    void treeView_customContextMenuRequested(QPoint pos);


    void deleteSelectedSongActionSlot();

    void hideProgressBar();
    void refreshTreeView();

    void savePlaylistActioSlot();

    void DisablePlaylistViewSorting();
    void EnablePlaylistViewSorting();

public slots:

    void updateProgressBar(int value);
    void setProgressBarRange(int min, int max);
    void setProgressBarText(QString text);
    void showTrayIconSongInfoMessage(AudioFile* af);

};

#endif // MAINWINDOW_H
