#include "databasecleaner.h"
#include "databasedao.h"

DatabaseCleaner::DatabaseCleaner(QObject *parent) :
    QThread(parent)
{




}

void DatabaseCleaner::run()
{

   DatabaseDAO::cleanDatabase();
   DatabaseDAO::deleteDoubleDatabaseEntries();



}
