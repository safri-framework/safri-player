#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPushButton>
#include <QSpacerItem>
#include <QSplitter>

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




    QPushButton* button1 = new QPushButton(this->ui->buttonspace);
    button1->setProperty("place","menu_left");
    button1->setProperty("type","menu_button");
    button1->setText("hello");
    button1->setCheckable(true);
    button1->setChecked(true);



    QPushButton* button2 = new QPushButton(this->ui->buttonspace);
    button2->setProperty("place","menu_left");
    button2->setProperty("type","menu_button_last");
    button2->setText("hello");
    button2->setCheckable(true);
    button2->setChecked(true);


    QSplitter* splitter = new QSplitter(Qt::Horizontal, this->ui->mainframe);
    splitter->addWidget(this->ui->widget_frame);
    splitter->addWidget(this->ui->player_frame);
    this->ui->mainframe->layout()->addWidget(splitter);

    this->ui->buttonspace->layout()->addWidget(button);
    this->ui->buttonspace->layout()->addWidget(button1);
    this->ui->buttonspace->layout()->addWidget(button2);

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

