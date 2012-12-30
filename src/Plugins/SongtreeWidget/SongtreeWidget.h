/*
#ifndef SONGTREEWIDGET_H
#define SONGTREEWIDGET_H
#include "SongtreeWidget_global.h"
#include "../CorePlugin/Interfaces/IAudioCollection.h"
#include "../CorePlugin/Songtree/songtreemodel.h"
#include <QWidget>

namespace Ui {
class SongtreeWidget;
}

class SongtreeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SongtreeWidget(QWidget *parent = 0);
    ~SongtreeWidget();
    
private:
    Ui::SongtreeWidget *ui;
    Core::IAudioCollection* audioCollection;
    SongTreeModel* model;
    void loadAudioCollection();
    void loadSongtreeModel();

};

#endif // SONGTREEWIDGET_H
*/
