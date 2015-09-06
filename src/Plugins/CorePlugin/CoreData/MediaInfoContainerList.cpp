#include "MediaInfoContainerList.h"
#include <QVariantList>
#include <QJsonDocument>


Core::MediaInfoContainerList::MediaInfoContainerList(QObject *parent) :
    QObject(parent)
{
}

void Core::MediaInfoContainerList::addMediaInfoContainer(MediaInfoContainer container)
{
    _list.append(QVariant(container.infoMap));
}

QString Core::MediaInfoContainerList::toJson()
{
    return QJsonDocument::fromVariant(_list).toJson();
}

bool Core::MediaInfoContainerList::fromJson(QString json)
{
    QJsonParseError error;
    QVariantList list = QJsonDocument::fromJson(json.toUtf8(), &error).toVariant().toList();
    if(error.error == QJsonParseError::NoError)
    {
        _list = list;
        return true;
    }

    return false;
}

int Core::MediaInfoContainerList::size()
{
    return _list.size();
}

Core::MediaInfoContainer Core::MediaInfoContainerList::getContainerAt(int index)
{
    MediaInfoContainer container;
    if(index < _list.size())
        container.infoMap = _list.at(index).toMap();

    return container;
}
