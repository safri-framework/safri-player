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
            this->ui->widget_frame->layout()->addWidget(plugin->getSideBarWidget());
            plugin->getSideBarWidget()->show();
            visiblePlugins++;
        }


        if(visiblePlugins == 0)
        {
            showSidebar(true);
            showSidebar(false);
        }
    }
}

void MainWindow::sideBarButtonClicked(bool checked)
{
    if(checked)
        visiblePlugins++;
    else
        visiblePlugins--;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonID = button->property("id").toInt();
}

void MainWindow::changePlayerWidget()
{
    QWidget* playerWidget = guiController->getPlayerWidget();

    //playerWidget->setParent(ui->player_frame->layout());
    //qDebug()<< "Nullpointer: " << ui->player_frame->layout();

    //ui->playerWidget->layout()->addWidget(playerWidget);

    //ui->player_frame->layout()->addWidget(playerWidget);
    //playerWidget->show();
}

void MainWindow::changePlaylistWidget()
{
    //Core::IPlaylistWidget* playlistWidget = guiController->getPlaylistWidget();
    //playlistWidget->show();
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
        this->ui->widget_frame->setMaximumWidth(3000);
        this->ui->widget_frame->setMinimumWidth(200);
        splitter->setSizes(lastSplitterSize);
    }
    else
    {
        this->ui->widget_frame->setMaximumWidth(0);
        this->ui->widget_frame->setMinimumWidth(0);
        lastSplitterSize = splitter->sizes();
        QList<int> list;
        list.append(0);
        list.append(600);
        splitter->setSizes(list);
    }

}
