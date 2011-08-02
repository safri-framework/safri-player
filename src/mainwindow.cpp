#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasecleaner.h"
#include "playlist.h"
#include "dtochanger.h"
#include <QStringList>
#include <QMdiSubWindow>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include "datatablemodel.h"
#include "showfolderinfilesystemhandler.h"
#include "settingsmanager.h"
#include "settingsmodule.h"
#include "selectedfilesystemindexactionhandler.h"
#include "settingsmanagerdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{










    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        const QIcon* icon = new QIcon("img/sf_icon.png");
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(*icon);
        trayIcon->setVisible(true);
    }
    else
    {

        trayIcon = 0;
    }


    lastPlaylist  = 0;

    click = false;
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(ui->centralWidget);

    splitter->addWidget(ui->leftWidget);
    splitter->addWidget(ui->rightWidget);

    ui->horizontalLayout->addWidget(splitter);

    setupTreeViewTabs();

    SetupSongTreeModels();
    setupPlaylistModel();

    ui->progressBar->setVisible(false);

    connect(ui->actionSavePlaylist, SIGNAL(triggered()), this, SLOT(savePlaylistActioSlot()));
    connect(ui->savePlaylistButton, SIGNAL(clicked()), ui->actionSavePlaylist, SLOT(trigger()));
    connect(ui->restorePlaylistButton, SIGNAL(clicked()), ui->actionRestorePlaylist, SLOT(trigger()));

    ui->playlistView->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->storedPlaylistView->setModel( new QStringListModel(M3uTranslator::getPlaylists()) );

    ui->mainToolBar->addAction(ui->actionOrdner_hinzufuegen);
    ui->mainToolBar->addAction(ui->actionSongs_hinzufuegen);
    ui->mainToolBar->setStyleSheet("background-image:url();");



    connect(treeViews->at(0), SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));
    connect(treeViews->at(1), SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));
    connect(treeViews->at(2), SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));

    connect(treeViews->at(0), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    connect(treeViews->at(1), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    connect(treeViews->at(2), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    connect(treeViews->at(3), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songList_doubleClicked(QModelIndex)));
    connect(treeViews->at(4), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(fileSystem_doubleClicked(QModelIndex)));

    //ui->webView->setUrl(QUrl("test.htm"));

    context = new PlayerContext();

    connect(ui->playerWidget, SIGNAL(currentSourceChanged(AudioFile*)), context, SLOT(CurrentSourceChanged(AudioFile*)));
    connect(context->getWebPage(), SIGNAL(contentsChanged()), ui->webView, SLOT(reload()));

    ui->webView->setPage(context->getWebPage());

    // connect contextmenu signals for treeviews
    connect(treeViews->at(0), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(treeViews->at(1), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(treeViews->at(2), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
  //connect(treeViews->at(3), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(treeViews->at(4), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_fileSystemView_customContextMenuRequested(QPoint)));

    connect(ui->playerWidget, SIGNAL(viewModeChanged()), this, SLOT(on_toggleView_clicked()));
     connect(this->ui->playerWidget, SIGNAL(currentSourceChanged(AudioFile*)),this, SLOT(showTrayIconSongInfoMessage(AudioFile*)));

    ui->playlistView->setHeaderHidden(false);

    connect(SettingsManager::getInstance()->getModule("core.view"), SIGNAL(settingsChanged()), this, SLOT(SetupSongTreeModels()));

 }





void MainWindow::setupTreeViewTabs()
{
    this->treeViewTabs = new QList<QWidget*>();
    this->searchEdits = new QList<QLineEdit*>();
    this->treeViews = new QList<QTreeView*>();

    QStringList captions;

    captions << "Genre" << "Interpret" << "Album" << "Song" << "FileSystem";

    for (int i = 4; i >= 0; i--)
    {
        QWidget* currentTabWidget = new QWidget(this->ui->treeViewTabWidget);
        QLayout* layout = new QVBoxLayout();

        QLineEdit* searchEdit = new QLineEdit();
        QTreeView* treeView = new QTreeView();

        searchEdit->setPlaceholderText("Suche");
        connect(searchEdit, SIGNAL(textChanged(QString)), this, SLOT(searchEditTextChanged(QString)));

        treeView->setDragEnabled(true);

        treeView->setDragDropMode(QAbstractItemView::DragDrop);
        treeView->setAnimated(true);
        treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        treeView->setExpandsOnDoubleClick(false);

        if (i != 3 )
        {
            treeView->setSortingEnabled(false);
                treeView->setHeaderHidden(true);
        }
        else
        {
            // different settings for song - view as list


            treeView->setRootIsDecorated(false);
            treeView->setHeaderHidden(false);
            treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

        }




        if ( i != 4) layout->addWidget(searchEdit);

        layout->addWidget(treeView);

        currentTabWidget->setLayout(layout);

        treeViewTabs->push_front(currentTabWidget);
        searchEdits->push_front(searchEdit);
        treeViews->push_front(treeView);

        this->ui->treeViewTabWidget->insertTab(0, currentTabWidget, captions.at(i));
    }

    this->ui->treeViewTabWidget->setCurrentIndex(0);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SetupSongTreeModels()
{
    SettingsModule* settings = SettingsManager::getInstance()->getModule("core.view");
    int treeviewCount = settings->getSetting("treeviewCount").toInt();

    for (int treeviewNumber = 0; treeviewNumber < treeviewCount; treeviewNumber++)
    {
        SongTreeModel *model;
        filters[treeviewNumber] = new QList<BaseDTO::DTO_TYPE>();

        QString hierarchySettings = settings->getSetting("treeview" + QString::number(treeviewNumber+1) + "Hierarchy").toString();
        QStringList treeHierarchy = hierarchySettings.split(";", QString::SkipEmptyParts);

        foreach (QString dtotype, treeHierarchy)
        {
            filters[treeviewNumber]->append(BaseDTO::stringToType(dtotype));
        }

        model = new SongTreeModel(filters[treeviewNumber]);
        connect(model, SIGNAL(songsToInsertInDatabase(QStringList*)), this, SLOT(insertSongs(QStringList*)));

        treeViews->at(treeviewNumber)->setModel(model);
    }

    DataTableModel* tableModel = new DataTableModel(DatabaseDAO::getDataTableCopy());
    treeViews->at(3)->setModel(tableModel);









QFileSystemModel *fileSystemModel = new QFileSystemModel(this);
//proxyModel = new QSortFilterProxyModel(this);
// Set the Root Path
fileSystemModel->setRootPath(fileSystemModel->myComputer().toString());




// Assign the Model to the Proxy and the Proxy to the View

fileSystemModel->setReadOnly(true);
//proxyModel->setSourceModel(fileSystemModel);
treeViews->at(4)->setModel(fileSystemModel);
// Fix the TreeView on the Root Path of the Model

//treeViews->at(4)->setCurrentIndex(rootModelIndex);
treeViews->at(4)->setColumnHidden(1, true);
treeViews->at(4)->setColumnHidden(2, true);
treeViews->at(4)->setColumnHidden(3, true);
treeViews->at(4)->adjustSize();




}


void MainWindow::setProgressBarRange(int min, int max)
{
    this->ui->progressBar->setRange(min, max);
}


void MainWindow::setProgressBarText(QString text)
{
    this->ui->progressBar->text() = text;

}



void MainWindow::setupPlaylistModel()
{
    playlistModel = new PlaylistModel(new Playlist(new QList<AudioFile*>()));

    connect(playlistModel, SIGNAL(taggerStarted()), this, SLOT(DisablePlaylistViewSorting()));
    connect(playlistModel, SIGNAL(taggerFinished()), this, SLOT(EnablePlaylistViewSorting()));

    ui->playlistView->setModel(playlistModel);
}


void MainWindow::insertSongs(QStringList *files)
{

    ui->progressBar->setValue(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(files->size());
    ui->progressBar->setVisible(true);

    SongInserter *thread = new SongInserter(files);
    connect(thread, SIGNAL(songInserted(int)), this, SLOT(updateProgressBar(int)));
    connect(thread, SIGNAL(finished()), this, SLOT(hideProgressBar()));
    connect(thread, SIGNAL(finished()), this, SLOT(refreshTreeView()));

    thread->start();
}





void MainWindow::on_actionSongs_hinzufuegen_triggered()
{
    QStringList filesStack = QFileDialog::getOpenFileNames(this, tr("Select Music Files"),
        QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (!filesStack.isEmpty())
    {

        QStringList *files = new QStringList(filesStack);

        insertSongs(files);
    }
}

void MainWindow::on_actionOrdner_hinzufuegen_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Music Files"),
        QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    addPathRecursiveToDatabase(directory);
}

void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}


void MainWindow::refreshTreeView()
{


    DatabaseDAO::loadDataTable();
    SetupSongTreeModels();

}


void MainWindow::hideProgressBar()
{
    ui->progressBar->setVisible(false);
}

void MainWindow::songTree_clicked(QModelIndex index)
{
    if (!this->click){
        if ( index.isValid() )
        {
            lastPlaylist = this->playlistModel->getPlaylist();

            BaseDTO *dto = static_cast<BaseDTO*>( index.internalPointer() );
            QList<AudioFile*> *songCollection;

            if (dto->getType() != BaseDTO::SONG)
            {
                songCollection = DatabaseDAO::getAudioFilesByBaseDTO(dto);

                Playlist *newPlaylist = new Playlist(songCollection);
                this->playlistModel->setPlaylist(newPlaylist);

            }




        }
    }
    else
    {
        click = false;
    }
}

void MainWindow::on_playlistView_doubleClicked(QModelIndex index)
{
   ui->playerWidget->setPlaylist(((PlaylistModel*)ui->playlistView->model())->getPlaylist());
   ui->playerWidget->playSongAt(index.row());
}

void MainWindow::on_actualPlayingPlaylistButton_clicked()
{
    if(ui->playerWidget->getPlaylist() != 0)
    {
        ((PlaylistModel*)(ui->playlistView->model()))->setPlaylist(ui->playerWidget->getPlaylist());

    }
}

void MainWindow::on_clearPlaylistButton_clicked()
{
    ((PlaylistModel*)(ui->playlistView->model()))->setPlaylist(new Playlist(new QList<AudioFile*>()));
}


void MainWindow::savePlaylistActioSlot()
{

    bool chooseNewPlaylistName = false;
    QString playlistName;

    do
    {
        chooseNewPlaylistName = false;

        playlistName = QInputDialog::getText(this, "Playliste speichern", "Geben Sie ihrer Playliste einen Namen:", QLineEdit::Normal, playlistName);


        if ( QFile::exists(M3uTranslator::playlistNameToAbsPath(playlistName)))
        {
            if ( QMessageBox::warning(this, "Playliste existiert bereits.", "Möchten sie die bereits existierende Playliste überschreiben?",
                                      QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            {

                chooseNewPlaylistName = true;

            }
        }


    }
    while( chooseNewPlaylistName );



    M3uTranslator::savePlaylistToM3u(((PlaylistModel*)(ui->playlistView->model()))->getPlaylist(), M3uTranslator::playlistNameToAbsPath(playlistName));

    ((QStringListModel*)ui->storedPlaylistView->model())->setStringList( M3uTranslator::getPlaylists()  );
}

void MainWindow::on_storedPlaylistView_clicked(QModelIndex index)
{
    QString playlistName = ((QStringListModel*)ui->storedPlaylistView->model())->data(index, Qt::DisplayRole).toString();
    this->playlistModel->setPlaylist(M3uTranslator::getPlaylistFromM3u(M3uTranslator::playlistNameToAbsPath(playlistName)));

}


void MainWindow::on_playlistView_customContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();

    menu->addAction("Entfernen", this, SLOT(deleteSelectedSongActionSlot()));
    menu->exec(QCursor::pos());


}

void MainWindow::on_fileSystemView_customContextMenuRequested(QPoint pos)
{

    int tabIndex = this->ui->treeViewTabWidget->currentIndex();
    QTreeView* view = treeViews->at(tabIndex);
    QModelIndex index = view->indexAt(pos);
    selectedFileSystemIndexActionHandler* handler = new selectedFileSystemIndexActionHandler(view, this, &index);




    QMenu* menu = new QMenu();

    menu->addAction("zur Bibliothek hinzufügen", handler, SLOT(addSelectedIndexRecursiveToDatabase()));
    menu->exec(QCursor::pos());


}







void MainWindow::treeView_customContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();



    QTreeView *treeView = treeViews->at(ui->treeViewTabWidget->currentIndex());

    QModelIndex index = treeView->indexAt(pos);

    BaseDTO *dto = static_cast<BaseDTO*>(index.internalPointer());

    // make a copy of the dto, to separte it from the tree as a single DTO object
    BaseDTO* dto_copy = new BaseDTO(dto->getID(), dto->getText(), dto->getType());




    DTOChanger *changer = new DTOChanger(dto_copy, index);

    connect(changer, SIGNAL(ModelIndexDataChanged(QModelIndex)), treeView, SLOT(update(QModelIndex)));

    switch (dto_copy->getType() )
    {
        case BaseDTO::ALBUM:

            menu->addAction("Albumcover ändern", changer, SLOT(changeAlbumCover()));
            menu->exec(QCursor::pos());
            break;
        case BaseDTO::SONG:
            QList<AudioFile*>* afList = DatabaseDAO::getAudioFilesByBaseDTO(dto_copy);
            QString path = afList->at(0)->fileName();
            QUrl* url = new QUrl(path);
            ShowFolderInFileSystemHandler* handler = new ShowFolderInFileSystemHandler(url, this);

            menu->addAction("Ordner anzeigen", handler, SLOT(showFolderInFileSystem()));


            menu->exec(QCursor::pos());
    }


}

void MainWindow::deleteSelectedSongActionSlot()
{
    QModelIndexList indexes = ui->playlistView->selectedIndexes();

    if (indexes.size() > 0)
    {
        ((PlaylistModel*)(ui->playlistView->model()))->getPlaylist()->deleteSong(indexes.at(0).row());
    }
}


void MainWindow::DisablePlaylistViewSorting()
{

    ui->playlistView->setSortingEnabled(false);
}

void MainWindow::EnablePlaylistViewSorting()
{
    ui->playlistView->setSortingEnabled(true);

    // don't modify the sorting of the playlist when tagger thread finished
    // just enable the sorting and let the user choose if
    // he want's other sorting than the default inserted order
    ui->playlistView->sortByColumn(-1, Qt::AscendingOrder);
}

void MainWindow::on_actionRestorePlaylist_triggered()
{
    if (lastPlaylist) this->playlistModel->setPlaylist(lastPlaylist);
}

void MainWindow::on_action_about_SaFri_Player_triggered()
{
    AboutDialog* dialog = new AboutDialog(this);

    dialog->setSizeGripEnabled(false);
    dialog->showNormal();
}

void MainWindow::on_action_Open_Settings_triggered()
{
    SettingsManagerDialog* settingsDialog = new SettingsManagerDialog(this);

    if (settingsDialog->exec() == QDialog::Accepted)
    {
        // save changed settings to database
        settingsDialog->saveSettings();
    }

}

void MainWindow::on_actionBereinigen_triggered()
{

  ui->progressBar->setRange(0,0);
  ui->progressBar->show();
  DatabaseCleaner* cleaner = new DatabaseCleaner();
  cleaner->start();
  connect(cleaner, SIGNAL(finished()),this, SLOT(hideProgressBar()));
  connect(cleaner, SIGNAL(finished()),this, SLOT(refreshTreeView()));



}

void MainWindow::songTree_doubleClicked(QModelIndex index)
{
    this->click = true;
    if ( index.isValid() )
    {
        lastPlaylist = this->playlistModel->getPlaylist();

        BaseDTO *dto = static_cast<BaseDTO*>( index.internalPointer() );
        QList<AudioFile*> *songCollection;


            songCollection = DatabaseDAO::getAudioFilesByBaseDTO(dto);

            Playlist *newPlaylist = new Playlist(songCollection);

            this->ui->playerWidget->setPlaylist(newPlaylist);
            this->ui->playerWidget->playSongAt(0);

            this->playlistModel->setPlaylist(newPlaylist);



    }

}

void MainWindow::songList_doubleClicked(QModelIndex index)
{

    int row = index.row();
    QList<AudioFile*> *songCollection = new QList<AudioFile*>;
    DataTableModel* model = static_cast<DataTableModel*>(treeViews->at(3)->model());
    QString path = model->getDataTable()->at(row)->value("FILENAME");
    songCollection->append(new AudioFile(path));
    qDebug()<<songCollection->size();
    Playlist *newPlaylist = new Playlist(songCollection);
    this->ui->playerWidget->setPlaylist(newPlaylist);
    this->ui->playerWidget->playSongAt(0);
    this->playlistModel->setPlaylist(newPlaylist);


}



bool view = true;
QMainWindow* testwindow = 0;

void MainWindow::on_toggleView_clicked()
{

    if ( view)
    {

        testwindow = new QMainWindow(0,Qt::Window);
        testwindow->setCentralWidget(ui->playerWidget);
        testwindow->show();
        connect(testwindow,SIGNAL(destroyed()),this, SLOT(on_toggleView_clicked()));
        view = false;
        this->hide();
    }
    else
    {
       testwindow->close();
       testwindow = 0;
       ui->widget_2->layout()->addWidget(ui->playerWidget);
       view = true;
       this->show();
    }
}


void MainWindow::showTrayIconSongInfoMessage(AudioFile* af)
{

    if (trayIcon)
    {
        QString artist = af->getArtist();
        QString title = af->getTitle();

        QString message = artist+" - "+title;
        if (this->isMinimized() || (testwindow && testwindow->isMinimized()))
        {

            this->trayIcon->showMessage("aktueller Song:", message);

        }

    }
}


void MainWindow::searchEditTextChanged(const QString &searchString)
{
    int index = ui->treeViewTabWidget->currentIndex();

    if ( index == 3 )
    {
        // different handling of song table
        if ( searchString.isEmpty() )
        {
            DataTableModel* tableModel = new DataTableModel(DatabaseDAO::getDataTableCopy());
            this->treeViews->at(index)->setModel(tableModel);
        }
        else
        {
            DatabaseDAO::DataTable* results = DatabaseDAO::searchDataTable(searchString);
            DataTableModel* tableModel = new DataTableModel(results);
            this->treeViews->at(index)->setModel(tableModel);
        }

    }
    else
    {
        if ( searchString.isEmpty() )
        {
            SongTreeModel *model = new SongTreeModel(filters[index]);

            this->treeViews->at(index)->setModel(model);
        }
        else
        {
            DatabaseDAO::DataTable* results = DatabaseDAO::searchDataTable(searchString);

            SongTreeModel *model = new SongTreeModel(filters[index], results);

            this->treeViews->at(index)->setModel(model);
            this->treeViews->at(index)->expandAll();
        }
    }
}



void MainWindow::showFolderInFileSystem(QUrl* file)
{

    QFileSystemModel* model = static_cast<QFileSystemModel*>(treeViews->at(4)->model());

    qDebug()<<"Debug2"<<file->toString();
    qDebug()<<model;

    QModelIndex index = model->index(file->toString());
    qDebug()<<index;
    treeViews->at(4)->setCurrentIndex(index);
    treeViews->at(4)->expand(index);
    this->ui->treeViewTabWidget->setCurrentIndex(4);


}


void MainWindow::addPathRecursiveToDatabase(QString path)
{

        if (!path.isEmpty())
        {
            QStringList *files = new QStringList();
            QDir dir(path);
            QStringList filters;
            filters << "*.mp3" << "*.wma" << "*.ogg";
            dir.setNameFilters(filters);

            QDirIterator lukeFileWalker(dir, QDirIterator::Subdirectories);


            while (lukeFileWalker.hasNext())
            {
                lukeFileWalker.next();
                files->append(lukeFileWalker.fileInfo().absoluteFilePath());
            }


            insertSongs(files);
        }
}





void MainWindow::fileSystem_doubleClicked(QModelIndex index)
{
    qDebug()<<"test";
    const QFileSystemModel* model = static_cast<const QFileSystemModel*>(index.model());
    QFileInfo info = model->fileInfo(index);
    QList<AudioFile*>* audioFileList = new QList<AudioFile*>;
    if (info.isDir())
    {
        QStringList *files = new QStringList();
        QDir dir(info.absoluteFilePath());
        QStringList filters;
        filters << "*.mp3" << "*.wma" << "*.ogg";
        dir.setNameFilters(filters);

        QDirIterator lukeFileWalker(dir, QDirIterator::Subdirectories);


        while (lukeFileWalker.hasNext())
        {
            lukeFileWalker.next();
            files->append(lukeFileWalker.fileInfo().absoluteFilePath());
        }

        for (int i = 0; i < files->size(); i++)
        {

            audioFileList->append(new AudioFile(files->at(i)));

        }

    }
    else
    {

        audioFileList->append(new AudioFile(info.absoluteFilePath()));

    }

    if (audioFileList->size() > 0)
    {
        Playlist* pl = new Playlist(audioFileList);

        this->ui->playerWidget->setPlaylist(pl);
        this->ui->playerWidget->playSongAt(0);

        this->playlistModel->setPlaylist(pl);
    }
}

