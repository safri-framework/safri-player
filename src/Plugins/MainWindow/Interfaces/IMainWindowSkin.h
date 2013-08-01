#ifndef IMAINWINDOWSKIN_H
#define IMAINWINDOWSKIN_H

#include <QObject>
#include <QString>
#include "MainWindow_global.h"

class MAINWINDOWSHARED_EXPORT IMainWindowSkin : public QObject
{
    Q_OBJECT
    public:

        explicit IMainWindowSkin(QObject *parent = 0);

        virtual QString getName() = 0;
        virtual QString getStylesheet() = 0;
    
};

#endif // IMAINWINDOWSKIN_H
