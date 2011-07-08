#ifndef SONGINSERTER_H
#define SONGINSERTER_H

#include <QThread>
#include <QStringList>
#include <QTime>

#include "databasedao.h"
#include "audiofile.h"

class SongInserter : public QThread
{
    Q_OBJECT
    public:

        explicit SongInserter(QStringList *sFileList, QObject *parent = 0);
        void run();

    private:

        QStringList *fileList;



    signals:
        void songInserted(int value);

    public slots:

};

#endif // SONGINSERTER_H
