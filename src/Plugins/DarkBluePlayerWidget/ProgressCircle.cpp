#include "ProgressCircle.h"
#include <QPainter>


ProgressCircle::ProgressCircle(QWidget *parent) :
    QWidget(parent)
{
    progress = new QImage(":/control/Ressources/control/progress.png");
}

void ProgressCircle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
}
