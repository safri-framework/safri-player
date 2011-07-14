#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasecleaner.h"
#include "playlist.h"
#include "dtochanger.h"
#include <QStringList>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    DatabaseDAO::getPathlistBySearchString("Metzger");


    click = false;
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(ui->centralWidget);

    splitter->addWidget(ui->leftWidget);
    splitter->addWidget(ui->rightWidget);

    ui->horizontalLayout->addWidget(splitter);

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



    connect(ui->genreView, SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));
    connect(ui->artistView, SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));
    connect(ui->albumView, SIGNAL(clicked(QModelIndex)), this, SLOT(songTree_clicked(QModelIndex)));

    connect(ui->genreView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    connect(ui->artistView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    connect(ui->albumView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(songTree_doubleClicked(QModelIndex)));
    //ui->webView->setUrl(QUrl("test.htm"));

    context = new PlayerContext();

    connect(ui->playerWidget, SIGNAL(currentSourceChanged(AudioFile*)), context, SLOT(CurrentSourceChanged(AudioFile*)));
    connect(context->getWebPage(), SIGNAL(contentsChanged()), ui->webView, SLOT(reload()));

    ui->webView->setPage(context->getWebPage());

    // connect contextmenu signals for treeviews
    connect(ui->genreView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(ui->artistView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(ui->albumView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(ui->songView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeView_customContextMenuRequested(QPoint)));
    connect(ui->playerWidget, SIGNAL(viewModeChanged()), this, SLOT(on_toggleView_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SetupSongTreeModels()
{
    SongTreeModel *model;
    filters[0] = new QList<BaseDTO::DTO_TYPE>();
    filters[1] = new QList<BaseDTO::DTO_TYPE>();
    filters[2] = new QList<BaseDTO::DTO_TYPE>();
    filters[3] = new QList<BaseDTO::DTO_TYPE>();

    QString hierarchySettings = DatabaseDAO::getSetting("TREEVIEW1_HIERARCHY").at(0);
    QStringList tree1hierarchy = hierarchySettings.split("#", QString::SkipEmptyParts);



    foreach (QString dtotype, tree1hierarchy)
    {
        filters[0]->append(BaseDTO::stringToType(dtotype));
    }




    /*
    filters[0]->append(BaseDTO::GENRE);
    filters[0]->append(BaseDTO::DECADE);
    filters[0]->append(BaseDTO::ARTIST);
    filters[0]->append(BaseDTO::ALBUM);
    filters[0]->append(BaseDTO::SONG);
    */


    model = new SongTreeModel(filters[0]);

    ui->genreView->setModel(model);

    filters[1]->append(BaseDTO::ARTIST);
    filters[1]->append(BaseDTO::ALBUM);
    filters[1]->append(BaseDTO::SONG);

    model = new SongTreeModel(filters[1]);

    ui->artistView->setModel(model);


    filters[2]->append(BaseDTO::ALBUM);
    filters[2]->append(BaseDTO::SONG);

    model = new SongTreeModel(filters[2]);

    ui->albumView->setModel(model);

    filters[3]->append(BaseDTO::DECADE);
    filters[3]->append(BaseDTO::SONG);

    model = new SongTreeModel(filters[3]);

    ui->songView->setModel(model);

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

    if (!directory.isEmpty())
    {
        QStringList *files = new QStringList();
        QDir dir(directory);
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

void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}


void MainWindow::refreshTreeView()
{
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

void MainWindow::treeView_customContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();


    qDebug() << "huhu";
    QTreeView *treeView;

    switch (ui->tabWidget->currentIndex())
    {
        case 0:
            treeView = this->ui->genreView;
            break;
        case 1:
            treeView = this->ui->artistView;
            break;
        case 2:
            treeView = this->ui->albumView;
            break;
        case 3:
            treeView = this->ui->songView;
            break;
    }

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
    this->playlistModel->setPlaylist(lastPlaylist);
}

void MainWindow::on_action_about_SaFri_Player_triggered()
{
    AboutDialog* dialog = new AboutDialog(this);

    dialog->setSizeGripEnabled(false);
    dialog->showNormal();
}

void MainWindow::on_action_Open_Settings_triggered()
{
    SettingsDialog* settings = new SettingsDialog(this);

    settings->setStyleSheet("background-image:url();");

    settings->show();
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

void MainWindow::on_lineEdit_textChanged(QString text)
{
    QList<QString>* searchResult;
    searchResult = DatabaseDAO::getPathlistBySearchString(text);

    QList<AudioFile*>* AFList = new QList<AudioFile*>;

    foreach (QString string, *searchResult)
    {
        AFList->append(new AudioFile(string));
    }

Playlist* pl = new Playlist(AFList);
playlistModel->setPlaylist(pl);


}

bool view = true;
QMainWindow* testwindow;


void MainWindow::on_toggleView_clicked()
{

    if ( view)
    {

        testwindow = new QMainWindow(0,Qt::Window);
        //testwindow = new QMdiSubWindow(0, Qt::Window);

        testwindow->setCentralWidget(ui->playerWidget);

        //testwindow->setWidget(ui->playerWidget);

        testwindow->show();
        connect(testwindow,SIGNAL(destroyed()),this, SLOT(on_toggleView_clicked()));
        view = false;
        this->hide();
}
    else
    {


       testwindow->close();

       ui->widget_2->layout()->addWidget(ui->playerWidget);
       view = true;
       this->show();
    }
}






