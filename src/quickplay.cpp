#include "quickplay.h"
#include "ui_quickplay.h"
#include "audiofile.h"
#include "playlist.h"



QuickPlay::QuickPlay(PlayerWidget* player, QWidget *parent) :
    QWidget(parent),player(player), results(0), ui(new Ui::QuickPlay)
{
    ui->setupUi(this);
    connect(ui->searchField, SIGNAL(textChanged(QString)), this, SLOT(searchEditTextChanged(QString)));
    connect(ui->searchField, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    //connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    this->ui->label->setText("");
    this->ui->searchField->setCursorPosition(0);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    this->activateWindow();
    this->show();
}

QuickPlay::~QuickPlay()
{
    delete ui;
}

void QuickPlay::searchEditTextChanged(const QString &searchString)
{
    results = DatabaseDAO::searchDataTable(searchString);
    this->ui->label->setText(QString::number(results->size())+" Lieder gefunden.");


}


void QuickPlay::returnPressed()
{
    QList<AudioFile*>* list = new QList<AudioFile*>();

    if(results && results->size() > 0)
    {
        for(int i  = 0; i < results->size(); i++)
        {
            list->append(new AudioFile(results->at(i)->value("FILENAME")));

        }

       Playlist* pl = new Playlist(list);
       player->setPlaylist(pl);
       player->playSongAt(0);
       this->close();


    }
}
void QuickPlay::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }

}

