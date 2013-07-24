#ifndef SAFRIMOBILEGUIINSTANCE_H
#define SAFRIMOBILEGUIINSTANCE_H

#include "SafriApp_global.h"
#include <QObject>
#include <QtQuick/QQuickItem>
#include "icore.h"
#include "iplaybackcontroller.h"
#include "Interfaces/IAudioCollection.h"
#include "Songtree/songtree.h"
#include "Interfaces/itreeitemtype.h"
#include "Songtree/songtreemodel.h"
#include <QSortFilterProxyModel>
#include "playlistmodel.h"

#include "IAppController.h"

using namespace Core;

class SongTreeModel;
class QQmlContext;

class SAFRIAPPSHARED_EXPORT ViewController: public QObject
{
    Q_OBJECT
    public:
        ViewController(IAppController* appController);

    public slots:
        void playPauseSlot();
        bool eventFilter(QObject *obj, QEvent *event);

    signals:

        void requestConnect(QString host, int port);
        void requestDisconnect();

    private slots:
        void stateChanged(Core::playState state);
        void playModelIndex(QVariant var);
        void enqueueModelIndex(QVariant var);

        void testPlay();
        void volumeSlot(QVariant vol);
        void setMusicProgress(int val);
        void updateMedia(Core::Media* media);
        void changePos(QVariant from, QVariant to);
        void removeFromPlaylist(QVariant index);
        void backClicked();
        void playPlaylistIndex(QVariant index);
        void newPlaylistModel();

        void connectTo(QVariant host, QVariant port);
        void disconnect();

    private:
        IAppController* appController;
        QQuickItem* playPauseButton;
        QQuickItem* prevButton;
        QQuickItem* nextButton;
        QQuickItem* silentButton;
        QObject* dialerView;
        QObject* musicProgress;
        QObject* currentSongDisplay;
        QObject* playlistView;
        QObject* settingsDialog;
        QObject* menuItemDisconnect;
        QAbstractItemModel* model;
        QQuickItem* songTree;
        QSortFilterProxyModel* proxy;
        int currentSongLength;
        QAbstractItemModel* plModel;
        QQmlContext* context;
        QSharedPointer<Core::IPlaylist> playList;
};

#endif // SAFRIMOBILEGUIINSTANCE_H
