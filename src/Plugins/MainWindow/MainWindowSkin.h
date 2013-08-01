#ifndef MAINWINDOWSKIN_H
#define MAINWINDOWSKIN_H

#include "Interfaces/IMainWindowSkin.h"

class MAINWINDOWSHARED_EXPORT MainWindowSkin : public IMainWindowSkin
{
    Q_OBJECT
    public:

        explicit MainWindowSkin(QString sName, QString sStylesheetFile, QObject *parent = 0);

        QString getName();
        QString getStylesheet();

    private:

        QString name;
        QString stylesheetFile;
};

#endif // MAINWINDOWSKIN_H
