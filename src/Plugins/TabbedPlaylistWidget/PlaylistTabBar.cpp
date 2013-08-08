#include "PlaylistTabBar.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

PlaylistTabBar::PlaylistTabBar(QWidget *parent) :
    QTabBar(parent)
{
    this->setDrawBase(false);
    installEventFilter(this);
}

bool PlaylistTabBar::eventFilter(QObject *object, QEvent *event)
{
    bool result = QObject::eventFilter(object, event);

    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        int tabIndexClicked = tabAt( mouseEvent->pos() );

        if (tabIndexClicked != -1)
        {
            Q_EMIT tabDoubleClicked(tabIndexClicked);
            return true;
        }
        else
        {
            return false;
        }
    }

    return result;
}
