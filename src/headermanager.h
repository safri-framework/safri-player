#ifndef HEADERMANAGER_H
#define HEADERMANAGER_H

#include <QObject>
#include <QHeaderView>
#include <QAction>
#include <QTreeView>
#include <QSignalMapper>
#include <QActionGroup>

class headerManager : public QObject
{
    Q_OBJECT
public:
    explicit headerManager(QHeaderView* header, QObject *parent = 0);
     explicit headerManager(QTreeView* view, QObject *parent = 0);
    void setIndexToEdit(int index);
    QList<QAction*>* getActions();
    QActionGroup* getResizeActionGroup();
signals:

public slots:

    void showSection();
    void hideSection();
    void showAll();

    void manualResizing();
    void autoResizeContent();
    void autoResizeAvailableSpace();
    void toggleSection(int i);

private:
    QHeaderView* header;
    int indexToEdit;
    QList<QAction*>* actionList;
    QActionGroup* resizeActionGroup;
   QSignalMapper* mapper;
   QTreeView* view;
};

#endif // HEADERMANAGER_H
