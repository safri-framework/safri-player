#include "ProgressCircle.h"
#include <QPainter>


ProgressCircle::ProgressCircle(QWidget *parent) :
    QWidget(parent),
    rotation(0)
{
    progress = new QImage(":/control/Ressources/control/progress.png");
    this->setMinimumHeight(progress->height());
    this->setMaximumHeight(progress->height());
    this->setMinimumWidth(progress->width());
    this->setMaximumWidth(progress->width());
    timer = new QTimer(this);
    timer->setInterval(20);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));

}

void ProgressCircle::rotate()
{
    rotation +=1;
    rotation %= 360;
    this->update();
}

void ProgressCircle::paintEvent(QPaintEvent *)
{


}
