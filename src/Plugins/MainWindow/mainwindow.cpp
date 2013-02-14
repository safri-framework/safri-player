#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPushButton>
#include <QSpacerItem>

#include <QDebug>
#include "Interfaces/iguicontroller.h"
#include "Interfaces/iplaylistwidget.h"
#include "icore.h"
#include <QWidget>

#include "../CorePlugin/CoreData/song.h"
#include "../CorePlugin/iplaylist.h"

#include "../../PluginSystem/pluginmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), visiblePlugins(0)
{
    ui->setupUi(this);
    readAndSetStylesheet();

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

    showTestPlaylist();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readAndSetStylesheet()
{

    QFile file;
       file.setFileName(":stylesheet/stylesheet.css");
       file.open(QFile::ReadOnly);
       QString styleSheet = QLatin1String(file.readAll());
       this->setStyleSheet(styleSheet);


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
    Core::Song *testMp31 = new Core::Song(1, "Test", 2012, "/home/sascha/hold_the_line.mp3", this);
    Core::Song *testMp32 = new Core::Song(2, "Test", 2012, "D:/Musik/Musik/Red Hot Chili Peppers/Red Hot Chili Peppers - Live/Live At Slane Castle (Audio DVD)/Parallel Universe.mp3", this);

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

    playList->insertMediaAt(0, songs);

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

    //playerWidget->setParent(ui->player_frame->layout());
    //qDebug()<< "Nullpointer: " << ui->player_frame->layout();


    if(playerWidget->getPreferedPosition() == IPlayerWidget::UNDER_PLAYLIST )
    {
        ui->playerWidget->layout()->addWidget(playerWidget);
    }
    else
    {
        ui->playerWidget_bottom->layout()->addWidget(playerWidget);
    }

    //ui->player_frame->layout()->addWidget(playerWidget);
    //playerWidget->show();
}

void MainWindow::changePlaylistWidget()
{
    Core::IPlaylistWidget* playlistWidget = guiController->getPlaylistWidget();
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
    PluginSystem::PluginManager::instance()->showPluginViewer();
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
