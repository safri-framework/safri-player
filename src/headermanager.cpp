#include "headermanager.h"

headerManager::headerManager(QHeaderView* header, QObject *parent) :
    header(header), QObject(parent)
{
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
