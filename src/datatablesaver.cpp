#include "datatablesaver.h"
#include "audiofile.h"

DataTableSaver::DataTableSaver(int flags, QObject *parent) :
    QThread(parent), flags(flags)
{




   // QList<AudioFile*>* af = new QList<AudioFile*>;
qDebug()<<"konstruktor";




}

void DataTableSaver::run()
{
    Q_EMIT setRange(0,0);
    Q_EMIT showProgressBar();

    DatabaseDAO::DataTable* dataTable = DatabaseDAO::getDataTablePtr();
    columnList = new QList<DatabaseDAO::ColumnData*>();
    Q_EMIT setProgressBarText(tr("Speichern vorbereiten.."));
    for (int i = 0; i < dataTable->size(); i++)
    {
        DatabaseDAO::ColumnData* column = dataTable->at(i);
        if (column->value("DIRTY") == "TRUE")
        {

                columnList->append(column);
                qDebug()<<"es passiert was";

        }
    }



    Q_EMIT setRange(0, columnList->size());


    Q_EMIT setProgressBarText(tr("Ändere Datenbankeinträge..."));

    for (int i = 0; i < columnList->size(); i++)
    {
        DatabaseDAO::updateSongInfo(columnList->at(i));
        if (flags == 0)


        if (this->flags == 1)
        {


        }
        Q_EMIT songSaved(i+1);
    }


    if (flags == 1)
    {
        Q_EMIT setRange(0, columnList->size());




        for (int i = 0; i < columnList->size(); i++)
        {
            qDebug()<<"taggen";
            DatabaseDAO::ColumnData* column = dataTable->at(i);
            Q_EMIT setProgressBarText(tr("tagge ") + column->value("ARTIST")+" - " + column->value("SONG"));
            AudioFile af(column->value("FILENAME"));
            QString artist = column->value("ARTIST");
            QString album = column->value("ALBUM");
            QString genre =column->value("GENRE");
            af.setTags(artist, album, genre);
            Q_EMIT songSaved(i+1);
        }

    }

Q_EMIT hideProgressBar();
}
