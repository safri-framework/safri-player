#include "MainWindowSkin.h"

#include <QFile>

MainWindowSkin::MainWindowSkin(QString sName, QString sStylesheetFile, QObject *parent) :
    IMainWindowSkin(parent), name(sName), stylesheetFile(sStylesheetFile)
{
}

QString MainWindowSkin::getName()
{
    return name;
}

QString MainWindowSkin::getStylesheet()
{
    QFile file;

    file.setFileName(stylesheetFile);
    file.open(QFile::ReadOnly);

    QString styleSheet = QLatin1String( file.readAll() );
    file.close();

    return styleSheet;
}
