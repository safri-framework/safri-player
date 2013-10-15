#ifndef SAFRIMOBILEGUIINSTANCE_H
#define SAFRIMOBILEGUIINSTANCE_H

#include "SafriMobileGuiQML_global.h"
#include <QObject>
#include <QtQuick/QQuickItem>
#include "Interfaces/ICore.h"
#include "iplaybackcontroller.h"
#include "Interfaces/IAudioCollection.h"
#include "Songtree/songtree.h"
#include "Interfaces/itreeitemtype.h"
#include "Songtree/songtreemodel.h"


using namespace Core;

class SongTreeModel;


class SAFRIMOBILEGUIQMLSHARED_EXPORT SafriMobileGuiInstance: public QObject
{
    Q_OBJECT
public:
    SafriMobileGuiInstance();

public slots:
    void playPauseSlot();

private slots:
    void stateChanged(Core::playState state);
    void playModelIndex(QVariant var);
    void testPlay();


private:
    QQuickItem* playPauseButton;
    QQuickItem* prevButton;
    QQuickItem* nextButton;
    QQuickItem* silentButton;

    SongTreeModel* getSongtreeModel();
    QMap<QUrl, IAudioCollection*> audioCollMap;
    void test();
    QList<ITreeItemType*>*  treeHierarchy;
    QList<Song*> songList;
    SongTree* tree;
    SongTreeModel* model;
    QQuickItem* songTree;
};

#endif // SAFRIMOBILEGUIINSTANCE_H
