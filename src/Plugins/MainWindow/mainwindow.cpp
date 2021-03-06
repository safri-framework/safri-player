
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPushButton>
#include <QSpacerItem>

#include <QDebug>
#include "Interfaces/IGUIController.h"
#include "Interfaces/IPlaylistWidget.h"
#include "Interfaces/ISafriSkin.h"
#include "Interfaces/ICore.h"
#include <QWidget>

#include "../CorePlugin/CoreData/Song.h"
#include "Interfaces/IPlaylist.h"

#include "Interfaces/ICollectionController.h"
#include "Interfaces/IMediaTagger.h"
#include "CoreSupply/FileSystemInserter.h"

#include "../../PluginSystem/pluginmanager.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), visiblePlugins(0)
{
    ui->setupUi(this);

    Core::ISafriSkin* skin = Core::ICore::instance()->skin();
    if(skin)
        this->setStyleSheet(skin->getStyleSheet());

    splitter = new QSplitter(Qt::Horizontal, this->ui->mainframe);
    splitter->addWidget(this->ui->widget_frame);
    splitter->addWidget(this->ui->player_frame);
    this->ui->mainframe->layout()->addWidget(splitter);
    lastSplitterSize.append(300);
    lastSplitterSize.append(700);

    closeSidebarTimeline = new QTimeLine(ANIMATION_DURATION, this);
    closeSidebarTimeline->setUpdateInterval(20);
    connect(closeSidebarTimeline, SIGNAL(frameChanged(int)), this, SLOT(closeSidebar(int)));

    openSidebarTimeline = new QTimeLine(ANIMATION_DURATION, this);
    openSidebarTimeline->setUpdateInterval(5);
    connect(openSidebarTimeline, SIGNAL(frameChanged(int)), this, SLOT(openSidebar(int)));


    guiController = Core::ICore::guiController();
    connect(guiController, SIGNAL(playerWidgetChanged()), this, SLOT(changePlayerWidget()));
    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(pluginAdded(QObject*)));


    QList<Core::ISideBarPlugin*> pluginList = PluginSystem::PluginManager::instance()->getObjects<Core::ISideBarPlugin>();
    this->plugins.append(pluginList);

    for(int i = 0; i < pluginList.size(); i++)
    {
        addPlugin(pluginList.at(i));
    }
    connect(guiController, SIGNAL(playlistWidgetChanged()), this, SLOT(changePlaylistWidget()));

    changePlayerWidget();
    changePlaylistWidget();

    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));

    showTestPlaylist();
    this->setWindowTitle("Safri-Player");
    this->show();
    qDebug() << "KONSTRUKTOR MainWindow";

}

MainWindow::~MainWindow()
{
    qDebug() << "DESTRUKTOR MainWindow";
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "close Event";
    //event->ignore();
    Core::ICore::close();
    event->accept();
}

void MainWindow::addPlugin(Core::ISideBarPlugin *plugin)
{
    QWidget* sidebarWidget = plugin->getSideBarWidget();
    QWidget* menuBarWidget = plugin->getMenuBarWidget();
    QPushButton* tabButton = qobject_cast<QPushButton*>(menuBarWidget);
    if(tabButton && tabButton->property("style").toString() == "tabStyle" )
    {
            this->ui->buttonspace->layout()->addWidget(tabButton);
            tabButtons.append(tabButton);
            if(tabButtons.size() <= 1)
            {
                tabButton->setProperty("place","menu_left");
                tabButton->setProperty("type","menu_button_last");
                tabButton->setIconSize(QSize(48,48));
            }
            else
            {
                QPushButton* lastBtn = tabButtons.at(tabButtons.size()-2);

                lastBtn->setProperty("type","menu_button");
                tabButton->setProperty("place","menu_left");
                tabButton->setProperty("type","menu_button_last");
                tabButton->setIconSize(QSize(48,48));
            }
        }
    else
    {
        this->ui->sidebar_widget_space->layout()->addWidget(menuBarWidget);
    }


    if(sidebarWidget)
    {
        connect(plugin, SIGNAL(show(bool)), this, SLOT(showRequest(bool)));
        if(plugin->isVisible())
        {
            qDebug()<<"VISIBLE";
            this->ui->widget_frame->layout()->addWidget(plugin->getSideBarWidget());
            plugin->getSideBarWidget()->show();
            visiblePlugins++;
        }


        if(visiblePlugins == 0)
        {
            this->ui->widget_frame->setMaximumWidth(0);
            this->ui->widget_frame->setMinimumWidth(0);
        }
    }
}

void MainWindow::showTestPlaylist()
{
    Core::Song *testMp31 = new Core::Song("audio/mpeg", 1, "Test", 2012, "/home/sascha/hold_the_line.mp3", this);
    Core::Song *testMp32 = new Core::Song("audio/mpeg",2, "Test", 2012, "D:/Musik/Musik/Red Hot Chili Peppers/Red Hot Chili Peppers - Live/Live At Slane Castle (Audio DVD)/Parallel Universe.mp3", this);

    Core::Artist *artist = new Core::Artist(1, "Artist Foo", this);
    Core::Album  *album = new Core::Album(1, "Album Foo", this);
    Core::Genre *genre = new Core::Genre(1, "Genre Foo", this);

    testMp31->setAlbum(album);
    testMp31->setArtist(artist);
    testMp31->setGenre(genre);

    testMp32->setAlbum(album);
    testMp32->setArtist(artist);
    testMp32->setGenre(genre);

    QList<Core::Item*> songs;
    songs.append(testMp31);
    songs.append(testMp32);

    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
    Core::ICore::guiController()->getPlaylistWidget()->showPlaylist(playList);
}

void MainWindow::sideBarButtonClicked(bool checked)
{
    if(checked)
        visiblePlugins++;
    else
        visiblePlugins--;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonID = button->property("id").toInt();
    Q_UNUSED(buttonID)
}

void MainWindow::changePlayerWidget()
{
    IPlayerWidget* playerWidget = guiController->getPlayerWidget();
    if(playerWidget->getPreferedPosition() == IPlayerWidget::UNDER_PLAYLIST )
    {
        ui->playerWidget->layout()->addWidget(playerWidget);
    }
    else
    {
        ui->playerWidget_bottom->layout()->addWidget(playerWidget);
    }
}

void MainWindow::changePlaylistWidget()
{
    Core::IPlaylistWidget* playlistWidget = guiController->getPlaylistWidget();
    playlistWidget->setParent(this);
    ui->playlistWidget->layout()->addWidget(playlistWidget);
}

void MainWindow::showRequest(bool show)
{
    Core::ISideBarPlugin* plugin = qobject_cast<Core::ISideBarPlugin*>(sender());
    QWidget* pluginWidget = plugin->getSideBarWidget();
    if(pluginWidget)
    {
        if(show )
        {
            this->ui->widget_frame->layout()->addWidget(pluginWidget);
            pluginWidget->show();
            visiblePlugins++;
            if (visiblePlugins == 1)
            showSidebar(true);

        }
        else
        {
            qDebug()<<"HIDE";
            this->ui->widget_frame->layout()->removeWidget(pluginWidget);
            pluginWidget->hide();
            visiblePlugins--;
            if (visiblePlugins == 0)
            showSidebar(false);
        }
    }

}

void MainWindow::pluginAdded(QObject *plugin)
{
    Core::ISideBarPlugin* sidebarPlugin = qobject_cast<Core::ISideBarPlugin*>(plugin);
    if(sidebarPlugin)
    {
        addPlugin(sidebarPlugin);
    }
}



void MainWindow::showSidebar(bool visible)
{
    if(visible)
    {
        guiController->getPlaylistWidget()->isAnimated(true);
        //this->ui->widget_frame->hide();
        this->ui->widget_frame->setMaximumWidth(0);
        this->ui->widget_frame->setMinimumWidth(0);
        openSidebarTimeline->setFrameRange( lastSplitterSize.at(0),0);
        openSidebarTimeline->start();
       // splitter->setSizes(lastSplitterSize);

    }
    else
    {
        lastSplitterSize.clear();
        lastSplitterSize.append(splitter->sizes());
        closeSidebarTimeline->setFrameRange(splitter->sizes().at(0), 0);
        closeSidebarTimeline->start();
    }

}

void MainWindow::on_actionPlugins_show_triggered()
{
    QWidget* viewer = PluginSystem::PluginManager::instance()->getPluginViewer();
    viewer->setStyleSheet(this->styleSheet());
    viewer->show();
}

void MainWindow::closeSidebar(int l)
{


    this->ui->widget_frame->setMaximumWidth(l);
    this->ui->widget_frame->setMinimumWidth(l);
    if (l==0)
        guiController->getPlaylistWidget()->isAnimated(false);

}

void MainWindow::openSidebar(int r)
{

    QList<int> list;
    this->ui->widget_frame->setMaximumWidth(lastSplitterSize.at(0)-r);
    list.append(lastSplitterSize.at(0)-r);
            list.append( lastSplitterSize.at(1)+r);
    splitter->setSizes(list);

    if(r == 0)
    {
        this->ui->widget_frame->setMinimumWidth(200);
        this->ui->widget_frame->setMaximumWidth(30000);
        guiController->getPlaylistWidget()->isAnimated(false);
        //this->ui->widget_frame->show();
    }
}

void MainWindow::on_actionAdd_folder_triggered()
{

    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Music Files"),
     QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0));

    if(!directory.isEmpty())
    {
        qDebug()<<directory;

        Core::ICollectionController *cc = 0;
        cc = Core::ICore::collectionController();

        if(!cc)
            return;
        QList<Core::IMediaTagger*> taggers = PluginSystem::PluginManager::instance()->getObjects<Core::IMediaTagger>();

        QList<Core::IMediaCollection*> collections = cc->getCollections("org.safri.collection.audio");

        Core::IMediaCollection *collection = collections.at(0);
        qDebug() << collection->getName();

        Core::FileSystemInserter* inserter = new Core::FileSystemInserter(collection);

        if(taggers.size() > 0)
            inserter->insertMedia(QUrl(directory), taggers.at(0));
        else
            qDebug()<<"No Media-Taggers found!";
    }
}

void MainWindow::on_actionSave_triggered()
{
    Core::ICore::collectionController()->saveCollections();
}

void MainWindow::on_actionSettings_triggered()
{
    Core::ICore::showSettingsDialog(this);
}

void MainWindow::objectAddedToObjectPool(QObject *object)
{
    Core::ISafriSkin *skin = qobject_cast<Core::ISafriSkin*>(object);
    if (skin != 0)
    {
        qDebug() << "IMainWindowSkin class added: " << skin->getName();
        this->setStyleSheet(skin->getStyleSheet());
    }
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}
