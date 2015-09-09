#ifndef SPOTIFYLOOKUPSIDEBARWIDGET_H
#define SPOTIFYLOOKUPSIDEBARWIDGET_H

#include <QtWidgets/QPushButton>
#include <QObject>
#include "Interfaces/ISideBarPlugin.h"
#include "SpotifySearch.h"
#include <QtQuickWidgets/QQuickWidget>
#include <QQuickView>
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
    QQuickView* _quickview;
    QWidget* _quickviewWrapper;
    QWidget* _widget;
signals:

public slots:

};

#endif // SPOTIFYLOOKUPSIDEBARWIDGET_H
