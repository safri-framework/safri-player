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
#include <QProcess>
#include <qglobal.h>
#include "osdisplay.h"
#include "safedplaylistmodel.h"
#include <QHeaderView>
#include "headermanager.h"
#include "quickplay.h"
#include "m3utranslator.h"
#include <QSignalMapper>
#include "datatablesaver.h"
#include <QRegExp>
#include <Phonon/BackendCapabilities>


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

    splitter = new QSplitter(ui->centralWidget);

    splitter->addWidget(ui->leftWidget);
    splitter->addWidget(ui->rightWidget);

    ui->horizontalLayout->addWidget(splitter);

    setupTreeViewTabs();

    SetupSongTreeModels();
    setupPlaylistModel();


    ui->progressBar->setVisible(false);

   this->ui->playlistView->header()->setObjectName("playlistHeader");


    connect(ui->actionSavePlaylist, SIGNAL(triggered()), this, SLOT(savePlaylistActioSlot()));
    connect(ui->savePlaylistButton, SIGNAL(clicked()), ui->actionSavePlaylist, SLOT(trigger()));
    connect(ui->restorePlaylistButton, SIGNAL(clicked()), ui->actionRestorePlaylist, SLOT(trigger()));

    ui->playlistView->setContextMenuPolicy(Qt::CustomContextMenu);


    //ui->storedPlaylistView->setModel( new QStringListModel(M3uTranslator::getPlaylists()) );



    ui->storedPlaylistView->setModel( new SafedPlaylistModel() );
    ui->storedPlaylistView->setContextMenuPolicy(Qt::CustomContextMenu);
   // connect(this->ui->storedPlaylistView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_storedPlaylistView_customContextMenuRequested(QPoint)));

    saveDataTableChanges = new QAction(QIcon("img/save.png"),"Änderungen speichern", this);
    connect(saveDataTableChanges, SIGNAL(triggered()), this, SLOT(saveDataTableChangesSlot()));
    saveDataTableChanges->setEnabled(false);



    ui->mainToolBar->addAction(saveDataTableChanges);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionOrdner_hinzufuegen);
    ui->mainToolBar->addAction(ui->actionSongs_hinzufuegen);

    ui->mainToolBar->setStyleSheet("background-image:url();");

    //this->ui->playerWidget->setStyleSheet("background-color: green");


    QStringList* availableMime = PlayerWidget::getSupportedFileTypes();
   for (int i = 0; i < availableMime->size();i++)
   {
     qDebug()<< availableMime->at(i);
   }



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


    QHeaderView* songListHeader = treeViews->at(3)->header();
    songListHeader->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->playlistView->setHeaderHidden(false);






    // connect contextmenu signals for treeviews
    connect(treeViews->at(0), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(treeViews->at(1), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(treeViews->at(2), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
  //connect(treeViews->at(3), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(songListHeader, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(on_header_customContextMenuRequested(QPoint)));
    connect(treeViews->at(4), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_fileSystemView_customContextMenuRequested(QPoint)));

    connect(ui->playerWidget, SIGNAL(viewModeChanged()), this, SLOT(on_toggleView_clicked()));
     connect(this->ui->playerWidget, SIGNAL(currentSourceChanged(AudioFile*)),this, SLOT(showNowplayingInfo(AudioFile*)));



    connect(SettingsManager::getInstance()->getModule("core.view"), SIGNAL(settingsChanged(QString)), this, SLOT(viewSettingsChanged(QString)));


    display = new OSDisplay(0);






this->deletePlaylistItemAction = new QAction("Aus Playliste entfernen", this);
deletePlaylistItemAction->setShortcut(QKeySequence::Delete);
  this->ui->playlistView->addAction(deletePlaylistItemAction);
connect(this->deletePlaylistItemAction, SIGNAL(triggered()), this, SLOT(deleteSelectedSongActionSlot()));
deletePlaylistItemAction->setEnabled(true);


    quickPlayShortcut = new QxtGlobalShortcut(QKeySequence("Alt+Q"), this);
    quickPlayShortcut->setEnabled(true);

    connect(this->quickPlayShortcut, SIGNAL(activated()), this, SLOT(startQuickPlayer()));
 }


bool fileSystem = false;


void MainWindow::viewSettingsChanged(QString setting)
{
    if (setting.contains("treeview") && setting.contains("Hierarchy"))
    {
       setting.replace(QRegExp("treeview"),"");
       setting.replace(QRegExp("Hierarchy"),"");

       int treeviewNr = setting.toInt();

       // -1: settings start counting at 1 / GUI at 0
       setupSongTreeModelNumber(treeviewNr - 1);
    }
}

void MainWindow::setupTreeViewTabs()
{

    this->treeViewTabs = new QList<QWidget*>();
    this->searchEdits = new QList<QLineEdit*>();
    this->treeViews = new QList<QTreeView*>();

    QStringList captions;

    captions << "Genre" << "Interpret" << "Album" << "Song" << "Datei";

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
        treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
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

        treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
    trayIcon->setVisible(false);
}

void MainWindow::setupSongTreeModelNumber(int treeviewNumber)
{
    qDebug()<<"update treeview"<<treeviewNumber;
    SettingsModule* settings = SettingsManager::getInstance()->getModule("core.view");

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
    connect(model, SIGNAL(DirtyDataTable()), this, SLOT(dataTableDataChanged()));

    treeViews->at(treeviewNumber)->setModel(model);
}

void MainWindow::SetupSongTreeModels()
{
    qDebug()<<"setupSongtreeModels";
    SettingsModule* settings = SettingsManager::getInstance()->getModule("core.view");
    int treeviewCount = settings->getSetting("treeviewCount").toInt();

    for (int treeviewNumber = 0; treeviewNumber < treeviewCount; treeviewNumber++)
    {
        setupSongTreeModelNumber(treeviewNumber);
    }

    DataTableModel* tableModel = new DataTableModel(DatabaseDAO::getDataTableCopy());
    treeViews->at(3)->setModel(tableModel);








    if (!fileSystem)
    {
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

    }
    fileSystem = true;
    QHeaderView* songListHeader = treeViews->at(3)->header();
    songListHeader->hideSection(2);
    songListHeader->hideSection(3);
    songTableHeaderManager = new headerManager(treeViews->at(3));

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
    ui->playlistView->header()->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(playlistModel, SIGNAL(taggerStarted()), this, SLOT(DisablePlaylistViewSorting()));
    connect(playlistModel, SIGNAL(taggerFinished()), this, SLOT(EnablePlaylistViewSorting()));
    connect(ui->playlistView->header(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_header_customContextMenuRequested(QPoint)));

    ui->playlistView->setModel(playlistModel);
    ui->playlistView->setAlternatingRowColors(true);
    ui->playlistView->hideColumn(4);
    ui->playlistView->hideColumn(5);
    playlistHeaderManager = new headerManager(ui->playlistView);

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


    //DatabaseDAO::loadDataTable();
    SetupSongTreeModels();
    qDebug()<<"refresh TreeView";

}


void MainWindow::hideProgressBar()
{
    ui->progressBar->setVisible(false);
}



void MainWindow::showProgressBar()
{
    ui->progressBar->setVisible(true);
}

void MainWindow::songTree_clicked(QModelIndex index)
{
    qDebug()<< " klick ";
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
        bool ok;
        playlistName = QInputDialog::getText(this, "Playliste speichern", "Geben Sie ihrer Playliste einen Namen:", QLineEdit::Normal, playlistName, &ok);
        if (!ok)
        {
           qDebug()<<"cancel";
           return;
        }
        if (playlistName.isNull())
        {
            qDebug()<<"isnull";
            if (QMessageBox::warning(this, "Dateiname ungültig", "Bitte geben Sie einen Dateinamen ein",
                                     QMessageBox::Ok) == QMessageBox::Ok);
            chooseNewPlaylistName = true;
        }
        else
        {

            if ( QFile::exists(M3uTranslator::playlistNameToAbsPath(playlistName)))
            {
                if ( QMessageBox::warning(this, "Playliste existiert bereits.", "Möchten Sie die bereits existierende Playliste überschreiben?",
                                          QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
                {

                    chooseNewPlaylistName = true;

                }
                else
                {
                    chooseNewPlaylistName = false;
                }
            }
        }


    }
    while( chooseNewPlaylistName );


    qDebug()<<"alles oK";
    M3uTranslator::savePlaylistToM3u(((PlaylistModel*)(ui->playlistView->model()))->getPlaylist(), M3uTranslator::playlistNameToAbsPath(playlistName));

    ui->storedPlaylistView->setModel( new SafedPlaylistModel() );
}

void MainWindow::on_storedPlaylistView_clicked(QModelIndex index)
{
    QString playlistName = ((QStringListModel*)ui->storedPlaylistView->model())->data(index, Qt::DisplayRole).toString();
    this->playlistModel->setPlaylist(M3uTranslator::getPlaylistFromM3u(M3uTranslator::playlistNameToAbsPath(playlistName)));

}


void MainWindow::on_playlistView_customContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();
    if (this->ui->playlistView->selectedIndexes().size()>0)
    {
        const QModelIndex index = this->ui->playlistView->selectedIndexes().at(0);
        AudioFile* af = ((PlaylistModel*)(ui->playlistView->model()))->getPlaylist()->getAudioFileAt(index.row());
        QFileInfo info(af->fileName());
        QUrl url(info.absoluteFilePath());
        ShowFolderInFileSystemHandler* handler = new ShowFolderInFileSystemHandler(&url,this);

        menu->addAction(deletePlaylistItemAction);
        menu->addAction("Ordner anzeigen", handler, SLOT(showFolderInFileSystem()));
        menu->addAction("In Explorer öffnen", handler, SLOT(showFolderInExplorer()));
        menu->exec(QCursor::pos());
    }

}

void MainWindow::on_fileSystemView_customContextMenuRequested(QPoint pos)
{

    int tabIndex = this->ui->treeViewTabWidget->currentIndex();
    QTreeView* view = treeViews->at(tabIndex);
    QModelIndex index = view->indexAt(pos);
    if (index.isValid())
    {
        const QFileSystemModel* model = static_cast<const QFileSystemModel*>(index.model());
        QFileInfo info = model->fileInfo(index);
        ShowFolderInFileSystemHandler* showHandler = new ShowFolderInFileSystemHandler(new QUrl(info.absoluteFilePath()+"/wuseldusel"), this);

        selectedFileSystemIndexActionHandler* handler = new selectedFileSystemIndexActionHandler(view, this, &index);




        QMenu* menu = new QMenu();



        if (info.isDir())
        {
            menu->addAction("In Explorer öffnen", showHandler, SLOT(showFolderInExplorer()));
            menu->addAction("zur Bibliothek hinzufügen", handler, SLOT(addSelectedIndexRecursiveToDatabase()));

        }
        else
        {
            if(PlayerWidget::getSupportedFileTypes()->contains(info.suffix().toLower()))
            {
                menu->addAction("zur Bibliothek hinzufügen", handler, SLOT(addSelectedIndexRecursiveToDatabase()));

            }

        }
        menu->exec(QCursor::pos());
    }

}







void MainWindow::treeView_customContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();



    QTreeView *treeView = treeViews->at(ui->treeViewTabWidget->currentIndex());

    QModelIndex index = treeView->indexAt(pos);

    if (index.isValid())
    {

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
                QFileInfo info(path);
                QUrl* url = new QUrl(info.absoluteFilePath());

                ShowFolderInFileSystemHandler* handler = new ShowFolderInFileSystemHandler(url, this);

                menu->addAction("Ordner anzeigen", handler, SLOT(showFolderInFileSystem()));
                menu->addAction("In Explorer öffnen", handler, SLOT(showFolderInExplorer()));

                menu->exec(QCursor::pos());
        }
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


void MainWindow::showNowplayingInfo(AudioFile* af)
{
    if ( QApplication::activeWindow() == 0 )
    {
        SettingsModule* viewSettings = SettingsManager::getInstance()->getModule("core.view");

        bool showTrayBalloon = viewSettings->getSetting("showTrayBalloon").toBool();
        bool showOSDisplay = viewSettings->getSetting("showOSDisplay").toBool();

        if (showOSDisplay)
        {
            display->showCurrentSong(af);
        }

        if (showTrayBalloon && trayIcon)
        {
            QString artist = af->getArtist();
            QString title = af->getTitle();

            QString message = artist + " - " + title;

            this->trayIcon->showMessage("aktueller Song:", message);
        }

    }
}

void MainWindow::searchEditTextChanged(const QString &searchString)
{
    int index = ui->treeViewTabWidget->currentIndex();

    delete this->treeViews->at(index)->model();

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
            connect(model, SIGNAL(DirtyDataTable()), this, SLOT(dataTableDataChanged()));
        }
        else
        {
            DatabaseDAO::DataTable* results = DatabaseDAO::searchDataTable(searchString);

            SongTreeModel *model = new SongTreeModel(filters[index], results);

            DatabaseDAO::deleteUserDataTable(results);

            this->treeViews->at(index)->setModel(model);
            connect(model, SIGNAL(DirtyDataTable()), this, SLOT(dataTableDataChanged()));
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
            QStringList filters = *PlayerWidget::getSupportedFileTypes();
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

    const QFileSystemModel* model = static_cast<const QFileSystemModel*>(index.model());
    QFileInfo info = model->fileInfo(index);
    QList<AudioFile*>* audioFileList = new QList<AudioFile*>;
    if (info.isDir())
    {
        QStringList *files = new QStringList();
        QDir dir(info.absoluteFilePath());
        QStringList filters = *PlayerWidget::getSupportedFileTypes();
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
        QString suffix = "*."+info.suffix();
        if(PlayerWidget::getSupportedFileTypes()->contains(suffix.toLower()))
        {
            audioFileList->append(new AudioFile(info.absoluteFilePath()));
        }
        else
        {

       QString path = QDir::toNativeSeparators(info.absoluteFilePath());
       QDesktopServices::openUrl(QUrl("file:///" + path));

        }
    }

    if (audioFileList->size() > 0)
    {
        Playlist* pl = new Playlist(audioFileList);

        this->ui->playerWidget->setPlaylist(pl);
        this->ui->playerWidget->playSongAt(0);

        this->playlistModel->setPlaylist(pl);

    }
}

void MainWindow::on_header_customContextMenuRequested(QPoint pos)
{

    QMenu* menu = new QMenu();



    headerManager* manager;
    if (this->ui->playlistView->hasFocus())
    {
        manager = playlistHeaderManager;
    }
    else
    {
        manager = songTableHeaderManager;

    }








    menu->addActions(*(manager->getActions()));
    menu->addSeparator();
    QMenu* subMenu;
    subMenu = menu->addMenu("Spaltengröße anpassen");
    subMenu->addActions(manager->getResizeActionGroup()->actions());
    menu->addAction(manager->getAlternatingRowColorAction());
    menu->exec(QCursor::pos());




}



void MainWindow::keyPressEvent ( QKeyEvent * event )
{

    if (event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
    {
        int index = ui->treeViewTabWidget->currentIndex();
        if (index <= 2 || index == 4)
        {
            QTreeView *treeView = treeViews->at(index);
            treeView->clearSelection();
            disconnect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)) );
            qDebug()<<"deaktiviert";

        }
    }
    if (event->key() == Qt::Key_Alt)
    {
        int tabIndex = this->ui->treeViewTabWidget->currentIndex();
        if (tabIndex < 3)
        {
            SongTreeModel* model = static_cast<SongTreeModel*>(treeViews->at(tabIndex)->model());
            model->allowEditTags();
             qDebug()<<"edit aktiviert";
        }
    }

}
void MainWindow::keyReleaseEvent(QKeyEvent * event)
{

    if (event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
    {
        int index = ui->treeViewTabWidget->currentIndex();
        if (index <= 2)
        {
            QTreeView *treeView = treeViews->at(index);

            connect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)) );
            qDebug()<<"aktiviert";
        }
    }
    if (event->key() == Qt::Key_Alt)
    {
        int tabIndex = this->ui->treeViewTabWidget->currentIndex();
        if (tabIndex < 3)
        {
            SongTreeModel* model = static_cast<SongTreeModel*>(treeViews->at(tabIndex)->model());
            model->denyEditTags();
            qDebug()<<"edit deaktiviert";
        }
    }

}




void MainWindow::startQuickPlayer()
{


    QuickPlay* quickplay = new QuickPlay(this->ui->playerWidget, this);

}

void MainWindow::on_storedPlaylistView_customContextMenuRequested(QPoint pos)
{

    QModelIndex index = this->ui->storedPlaylistView->indexAt(pos);
    TreeItem *item = static_cast<TreeItem*>( index.internalPointer() );
    qDebug()<<item->getType();


    if (item->getType() == "PLAYLIST")
    {

        QMenu* menu = new QMenu();
        QAction* deletePlaylist = menu->addAction("Playliste löschen");
        QSignalMapper* mapper = new QSignalMapper(this);


        mapper->setMapping(deletePlaylist, index.data().toString() );
        connect(deletePlaylist, SIGNAL(triggered()), mapper, SLOT(map()));
        connect(mapper, SIGNAL(mapped(QString)),this, SLOT(deletePlaylist(QString)));

        menu->exec(QCursor::pos());
    }


}

void MainWindow::deletePlaylist(QString path)
{

    qDebug()<<M3uTranslator::deletePlaylist(M3uTranslator::playlistNameToAbsPath(path));
    ui->storedPlaylistView->setModel( new SafedPlaylistModel() );

}

void MainWindow::dataTableDataChanged()
{
    saveDataTableChanges->setIcon(QIcon("img/save_possible.png"));
    saveDataTableChanges->setEnabled(true);
    refreshTreeView();


}

void MainWindow::saveDataTableChangesSlot()
{
    QStringList items;
         items << tr(".. nur in der Datenbank") << tr("..auch in den Tags") ;

         bool ok;
         QString item = QInputDialog::getItem(this, tr("Speichern"),
                                              tr("Änderungen speichern.."), items, 0, false, &ok);
         if (ok && !item.isEmpty())
         {
             saveDataTableChanges->setIcon(QIcon("img/save.png"));
             saveDataTableChanges->setDisabled(true);
             DataTableSaver* saver;

             if (item == ".. nur in der Datenbank")
             {
                 saver = new DataTableSaver(0, this);


             }


             if (item == "..auch in den Tags")
             {
                saver = new DataTableSaver(1, this);

             }


             connect(saver, SIGNAL(setRange(int,int)), this, SLOT(setProgressBarRange(int,int)));
             connect(saver, SIGNAL(songSaved(int)), this, SLOT(updateProgressBar(int)));
             connect(saver, SIGNAL(setProgressBarText(QString)), this, SLOT(setProgressBarText(QString)));
             connect(saver, SIGNAL(showProgressBar()), this, SLOT(showProgressBar()));
             connect(saver, SIGNAL(hideProgressBar()), this, SLOT(hideProgressBar()));
             saver->run();




         }
         else
         {

         }


}

