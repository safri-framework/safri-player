#include "toucheventfilter.h"
#include <QEvent>
#include <QTimer>
#include <QDebug>
TouchEventFilter::TouchEventFilter(QObject *parent) : receiveClicks(true), pressed(false),
    QObject(parent)
{
}


bool TouchEventFilter::eventFilter(QObject *obj, QEvent *event)
{


  //  qDebug()<<event->type();
    return false;

    /*
    if(event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease)
        return false;



    if(event->type() == QEvent::TouchUpdate)
    {
        qDebug()<<"TOUCH"<<obj<<"  "<<obj->objectName();
    }

    if(event->type() == QEvent::MouseButtonPress)
        qDebug()<<"PRESS"<<obj<<"  "<<obj->objectName();
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        qDebug()<<"RELEASE"<<obj<<"  "<<obj->objectName();
    }
    {

    if(receiveClicks)
        std::system("CLS");

    qDebug()<<"pressed: "<<pressed<<"   cann receive: "<<receiveClicks;

    if(receiveClicks && event->type() == QEvent::MouseButtonPress)
    {
        receiveClicks = false; QEvent::MouseButtonRelease)
             {
        pressed = true;
        QTimer::singleShot(200, this, SLOT(timer()));
        qDebug()<<"PRESS";
       // QObject::eventFilter(obj, event);
        return false;
    }

    if (pressed && event->type() == QEvent::MouseButtonRelease)
    {
       // QObject::eventFilter(obj, event);
        pressed = false;
        qDebug()<<"RELEASE";
        return false;
    }



   qDebug()<<"blockS";
   return true;
    */
}

void TouchEventFilter::timer()
{
    receiveClicks = true;

}
