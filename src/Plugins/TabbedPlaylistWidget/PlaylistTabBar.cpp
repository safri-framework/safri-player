#include "PlaylistTabBar.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDebug>

PlaylistTabBar::PlaylistTabBar(QWidget *parent) :
    QTabBar(parent)
{
    this->setDrawBase(false);
    installEventFilter(this);
    //this->setMouseTracking(true);
    this->setAcceptDrops(true);
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

void PlaylistTabBar::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void PlaylistTabBar::dragMoveEvent(QDragMoveEvent *event)
{
    int tabIndexUnderDrag = tabAt( event->pos() );

    if ( tabIndexUnderDrag != currentIndex() )
    {
        setCurrentIndex(tabIndexUnderDrag);
    }

}
