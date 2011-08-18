#ifndef QUICKPLAY_H
#define QUICKPLAY_H

#include <QWidget>
#include "databasedao.h"
#include "playerwidget.h"
#include "QMainWindow"
#include <QKeyEvent>

namespace Ui {
    class QuickPlay;
}

class QuickPlay : public QWidget
{
    Q_OBJECT

public:
    explicit QuickPlay(PlayerWidget* player, QWidget *parent = 0);
    ~QuickPlay();
    void keyPressEvent ( QKeyEvent * event );

private:
    PlayerWidget* player;
    Ui::QuickPlay *ui;
    DatabaseDAO::DataTable* results;
    QMainWindow* window;
private slots:


    void searchEditTextChanged(const QString &searchString);
    void returnPressed();
};

#endif // QUICKPLAY_H
