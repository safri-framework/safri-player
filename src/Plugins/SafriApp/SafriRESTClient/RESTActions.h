#ifndef RESTACTIONS_H
#define RESTACTIONS_H

#include <QString>

namespace RESTAction
{
    const QString PLAYER_PLAY         = "player?action=play";
    const QString PLAYER_PAUSE        = "player?action=pause";
    const QString PLAYER_STOP         = "player?action=stop";
    const QString PLAYER_NEXT         = "player?action=next";
    const QString PLAYER_PREVIOUS     = "player?action=previous";
    const QString PLAYER_SEEK         = "player?action=seek&playTime=%%SEEKTO%%";
    const QString PLAYER_STATUS       = "player?action=getStatus";
    const QString PLAYER_VOLUME       = "player?action=setVolume&volume=%%VOLUME%%";
    const QString SONGTREE_GET_ITEM   = "songtree?id=%%ITEMID%%";
}

#endif // RESTACTIONS_H
