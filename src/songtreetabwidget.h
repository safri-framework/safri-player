#ifndef SONGTREETABWIDGET_H
#define SONGTREETABWIDGET_H

#include <QTabWidget>

class SongtreeTabWidget : public QTabWidget
{
    Q_OBJECT
    public:
        explicit SongtreeTabWidget(QWidget *parent = 0);

    signals:

    public slots:

        void customContextMenuRequested(QPoint);
        void changeCurrentTreeviewHierarchy(QString hierarchy);

};

#endif // SONGTREETABWIDGET_H
