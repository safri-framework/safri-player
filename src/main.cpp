#include <QtGui/QApplication>
#include <QSplashScreen>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication::setStyle("plastique");

    QApplication a(argc, argv);



    QPixmap pixmap("img/splashscreen.png");
    QSplashScreen splash(pixmap);

    splash.show();
    a.processEvents();

    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
