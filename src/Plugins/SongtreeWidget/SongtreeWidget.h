
#ifndef SONGTREEWIDGET_H
#define SONGTREEWIDGET_H
#include "SongtreeWidget_global.h"
#include "../CorePlugin/Interfaces/IAudioCollection.h"
#include "../CorePlugin/Songtree/SongTreeModel.h"
#include "../CorePlugin/Songtree/SongTreeProxyModel.h"
#include "../CorePlugin/Songtree/SongTree.h"
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
    QList<IAudioCollection*> audioCollList;
    void buildHierarchy();
    //QList<ITreeItemType*>*  treeHierarchy;
    SongtreeProxyModel* searchProxy;
    QMap<int, QList<ITreeItemType*>*> hierarchyList;

private slots:
    void newAudioCollectionAvailable(QUrl collURL);
    void addNewCollection(IMediaCollection* collection);
    void removeCollection(QUrl collURL);
    void returnPressed();
    void on_treeView_doubleClicked(const QModelIndex &index);
    void loadSongtreeModel(int hierarchy);
    void textEdited(QString string);
};

#endif // SONGTREEWIDGET_H

