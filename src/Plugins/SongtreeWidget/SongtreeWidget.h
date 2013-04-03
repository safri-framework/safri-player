
#ifndef SONGTREEWIDGET_H
#define SONGTREEWIDGET_H
#include "SongtreeWidget_global.h"
#include "../CorePlugin/Interfaces/IAudioCollection.h"
#include "../CorePlugin/Songtree/songtreemodel.h"
#include "../CorePlugin/Songtree/songtree.h"
#include "../CorePlugin/Interfaces/ICollectionController.h"
#include <QWidget>

namespace Ui {
class SongtreeWidget;
}

class SONGTREEWIDGETSHARED_EXPORT SongtreeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SongtreeWidget(QWidget *parent = 0);
    ~SongtreeWidget();
    
private:
    Ui::SongtreeWidget *ui;
    ICollectionController* collController;
    SongTreeModel* model;
    SongTree* tree;
    QList<Song*> songList;
    QMap<QUrl, IAudioCollection*> audioCollMap;
    void loadAudioCollections();
    void loadSongtreeModel();
    void buildHierarchy();
    QList<ITreeItemType*>*  treeHierarchy;


private slots:
    void newAudioCollectionAvailable(QUrl collURL);
    void removeCollection(QUrl collURL);

    void on_treeView_doubleClicked(const QModelIndex &index);
};

#endif // SONGTREEWIDGET_H

