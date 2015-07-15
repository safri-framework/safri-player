#ifndef SPOTIFYLOOKUPSIDEBARWIDGET_H
#define SPOTIFYLOOKUPSIDEBARWIDGET_H

#include <QtWidgets/QPushButton>
#include <QObject>
#include "Interfaces/ISideBarPlugin.h"
#include "SpotifySearch.h"

using namespace Core;

class SpotifyLookupSidebarWidget : public ISideBarPlugin
{
    Q_OBJECT

public:
    explicit SpotifyLookupSidebarWidget();

    QWidget* getSideBarWidget();
    QString getName();
    QWidget *getMenuBarWidget();
    bool isVisible();


private:
    SpotifySearch* _search;
    QPushButton* _button;

signals:

public slots:

};

#endif // SPOTIFYLOOKUPSIDEBARWIDGET_H
