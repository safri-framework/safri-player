#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPushButton>
#include <QSpacerItem>
#include <QSplitter>
#include <QDebug>
#include "Interfaces/iguicontroller.h"
#include "icore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);
    readAndSetStylesheet();
    QPushButton* button = new QPushButton(this->ui->buttonspace);
    button->setProperty("place","menu_left");
    button->setProperty("type","menu_button");
    button->setText("hello");
    button->setCheckable(true);
    button->setChecked(true);
    button->setProperty("id",0);




    QPushButton* button1 = new QPushButton(this->ui->buttonspace);
    button1->setProperty("place","menu_left");
    button1->setProperty("type","menu_button");
    button1->setText("hello");
    button1->setCheckable(true);
    button1->setChecked(true);
    button1->setProperty("id",1);


    QPushButton* button2 = new QPushButton(this->ui->buttonspace);
    button2->setProperty("place","menu_left");
    button2->setProperty("type","menu_button_last");
    button2->setText("hello");
    button2->setCheckable(true);
    button2->setChecked(true);
    button2->setProperty("id",2);


    QSplitter* splitter = new QSplitter(Qt::Horizontal, this->ui->mainframe);
    splitter->addWidget(this->ui->widget_frame);
    splitter->addWidget(this->ui->player_frame);
    this->ui->mainframe->layout()->addWidget(splitter);

    this->ui->buttonspace->layout()->addWidget(button);
    this->ui->buttonspace->layout()->addWidget(button1);
    this->ui->buttonspace->layout()->addWidget(button2);


    QWidget* w1 = new QWidget();
    QWidget* w2 = new QWidget();
    QWidget* w3 = new QWidget();

    QList<QWidget*>* widgetList = new QList<QWidget*>();
    QList<QPushButton*>* buttonList = new QList<QPushButton*>();


    buttonList->append(button);
    buttonList->append(button1);
    buttonList->append(button2);
    widgetList->append(w1);
    widgetList->append(w2);
    widgetList->append(w3);

    Q_ASSERT(widgetList->size() == buttonList->size());

    for(int i = 0; i<widgetList->size(); i++)
    {
        //connect(buttonList.at(i), SIGNAL(clicked(bool)), widgetList.at(i), SLOT(setVisible(bool)));
        connect(buttonList->at(i), SIGNAL(clicked(bool)), this, SLOT(sideBarButtonClicked(bool)));
    }

    guiController = Core::ICore::guiController();
    connect(guiController, SIGNAL(playerWidgetChanged()), this, SLOT(changePlayerWidget()));
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

    ui->player_frame->layout()->addWidget(playerWidget);
    //playerWidget->show();
}

