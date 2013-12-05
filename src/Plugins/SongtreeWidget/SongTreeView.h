#ifndef SONGTREEVIEW_H
#define SONGTREEVIEW_H

#include <QTreeView>

class SongTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit SongTreeView(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void focusOutEvent(QFocusEvent *event);
    
};

#endif // SONGTREEVIEW_H
