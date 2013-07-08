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
using namespace Core;

class SongTreeModel;
class QQmlContext;

class SAFRIAPPSHARED_EXPORT SafriAppInstance: public QObject
{
    Q_OBJECT
public:
    SafriAppInstance();

public slots:
    void playPauseSlot();

private slots:
    void stateChanged(Core::playState state);
    void playModelIndex(QVariant var);
    void testPlay();
    void volumeSlot(QVariant vol);
    void setMusicProgress(int val);
    void updateMedia(Core::Media* media);
    void changePos(QVariant from, QVariant to);

private:
    QQuickItem* playPauseButton;
    QQuickItem* prevButton;
    QQuickItem* nextButton;
    QQuickItem* silentButton;
    QObject* dialerView;
    QObject* musicProgress;
    QObject* currentSongDisplay;
    QObject* playlistView;
    SongTreeModel* getSongtreeModel();
    QMap<QUrl, IAudioCollection*> audioCollMap;
    void test();
    QList<ITreeItemType*>*  treeHierarchy;
    QList<Song*> songList;
    SongTree* tree;
    SongTreeModel* model;
    QQuickItem* songTree;
    QSortFilterProxyModel* proxy;
    int currentSongLength;
    PlaylistModel* plModel;
    QQmlContext* context;
    QSharedPointer<Core::IPlaylist> playList;
};

#endif // SAFRIMOBILEGUIINSTANCE_H
