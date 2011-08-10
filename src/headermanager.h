#ifndef HEADERMANAGER_H
#define HEADERMANAGER_H

#include <QObject>
#include <QHeaderView>

class headerManager : public QObject
{
    Q_OBJECT
public:
    explicit headerManager(QHeaderView* header, QObject *parent = 0);
    void setIndexToEdit(int index);
signals:

public slots:

    void showSection();
    void hideSection();
    void showAll();
private:
    QHeaderView* header;
    int indexToEdit;

};

#endif // HEADERMANAGER_H
