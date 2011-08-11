#include "headermanager.h"
#include <QDebug>
headerManager::headerManager(QHeaderView* header, QObject *parent) :
    header(header), QObject(parent)
{


}


headerManager::headerManager(QTreeView* view, QObject *parent) :
    view(view), QObject(parent)
{
    this->mapper = new QSignalMapper();

    actionList = new QList<QAction*>;
    this->header = view->header();

    qDebug()<< QString::number(header->count());






    for (int i = 0; i < header->count(); i++)
    {

        const QString headerText = view->model()->headerData(i, Qt::Horizontal).toString();



        QAction* action = new QAction(headerText, this);

        action->setCheckable(true);
        if(header->isSectionHidden(i))
        {
            action->setChecked(false);

        }
        else
        {
            action->setChecked(true);

        }
    connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(action, i);
    actionList->append(action);
    }

    if (!(header->count() - 1 > header->hiddenSectionCount()) )
    {
     qDebug()<<"jetzt geht nix mehr!";
        for(int i = 0; i < actionList->size(); i++)
        {
            if (actionList->at(i)->isChecked())
                actionList->at(i)->setDisabled(true);
        }

    }


connect(mapper, SIGNAL(mapped(int)), this, SLOT(toggleSection(int)));



resizeActionGroup = new QActionGroup(this);
resizeActionGroup->setExclusive(true);



QAction* windowSize = new QAction("nach Fenstergröße", resizeActionGroup);
QAction* columnSize = new QAction("nach Zeilenlänge", resizeActionGroup);
QAction* manualResize = new QAction("manuell", resizeActionGroup);
windowSize->setActionGroup(resizeActionGroup);
columnSize->setActionGroup(resizeActionGroup);
manualResize->setActionGroup(resizeActionGroup);

windowSize->setCheckable(true);
columnSize->setCheckable(true);
manualResize->setCheckable(true);


resizeActionGroup->addAction(windowSize);
resizeActionGroup->addAction(columnSize);
resizeActionGroup->addAction(manualResize);

connect(windowSize, SIGNAL(triggered()), this, SLOT(autoResizeAvailableSpace()));
connect(columnSize, SIGNAL(triggered()), this, SLOT(autoResizeContent()));
connect(manualResize, SIGNAL(triggered()), this, SLOT(manualResizing()));

windowSize->trigger();
//manualResize->trigger();
windowSize->setChecked(true);







}

void headerManager::toggleSection(int i)
{
    //actionList->at(i)->toggle();
    if (header->isSectionHidden(i))
        header->showSection(i);
    else
     header->hideSection(i);



}


void headerManager::showSection()
{
    header->showSection(indexToEdit);
}

void headerManager::hideSection()
{
    header->hideSection(indexToEdit);
}

void headerManager::showAll()
{
    for (int i = 0 ; i < header->count(); i++)
    {
        header->showSection(i);
    }
}

void headerManager::setIndexToEdit(int index)
{
    this->indexToEdit = index;
}


void headerManager::manualResizing()
{
    header->setStretchLastSection(true);
    for (int i = 0; i < header->count(); i++)
    {
      header->setResizeMode(i, QHeaderView::Interactive);
    }

}

void headerManager::autoResizeContent()
{
    for(int i = 0; i < header->count(); i++)
    {
        QString headerText = view->model()->headerData(i, Qt::Horizontal).toString();
        if (headerText == "Track" || headerText == "Jahr" || headerText == "Länge" )
            header->setResizeMode(QHeaderView::ResizeToContents);
        else
            header->setResizeMode(QHeaderView::Fixed);
    }
}


QActionGroup* headerManager::getResizeActionGroup()
{
    return resizeActionGroup;
}


QList<QAction*>* headerManager::getActions()
{
    return actionList;
}

void headerManager::autoResizeAvailableSpace()
{

        header->setStretchLastSection(false);
        for (int i = 0; i <header->count(); i++)
        {
            QString headerText = view->model()->headerData(i, Qt::Horizontal).toString();
            if (headerText == "Track" || headerText == "Jahr" || headerText == "Länge" )
            {
               header->setResizeMode(i, QHeaderView::Fixed);
               header->resizeSection(i, 55);
            }
            else
            {
                header->setResizeMode(i,QHeaderView::Stretch);
            }
        }
}



