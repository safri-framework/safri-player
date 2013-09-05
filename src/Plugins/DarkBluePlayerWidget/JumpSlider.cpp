#include "JumpSlider.h"
#include <QDebug>
#include <QMouseEvent>
#include <QStyleOptionSlider>

JumpSlider::JumpSlider(QWidget *parent) :
    QSlider(parent)
{
    connect(this, SIGNAL(sliderMoved(int)), this, SLOT(slotSliderMoved(int)));
}

void JumpSlider::mousePressEvent(QMouseEvent * event)
{
    qDebug() << "mousePressEvent";


    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    if (event->button() == Qt::LeftButton &&
        sr.contains(event->pos()) == false)
    {
      int newVal;
      if (orientation() == Qt::Vertical)
         newVal = minimum() + ((maximum()-minimum()) * (height()-event->y())) / height();
      else
         newVal = minimum() + ((maximum()-minimum()) * event->x()) / width();

      if (invertedAppearance() == true)
          newVal = maximum() - newVal;

      setValue(newVal);
      Q_EMIT sliderMoved(newVal);

      event->accept();
    }
    QSlider::mousePressEvent(event);
}

void JumpSlider::slotSliderMoved(int val)
{
    qDebug() << "sliderMoved: " << val;
}
