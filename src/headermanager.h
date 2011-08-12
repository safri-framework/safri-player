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
    QAction* getAlternatingRowColorAction();
signals:

public slots:

    void showSection();
    void hideSection();
    void showAll();

    void manualResizing();
    void autoResizeContent();
    void autoResizeAvailableSpace();
    void toggleSection(int i);
    void toggleAlternatingRowColors(bool value);

private:
    QHeaderView* header;
    int indexToEdit;
    QList<QAction*>* actionList;
    QActionGroup* resizeActionGroup;
    QAction* alternatingRowColorAction;
   QSignalMapper* mapper;
   QTreeView* view;
};

#endif // HEADERMANAGER_H
