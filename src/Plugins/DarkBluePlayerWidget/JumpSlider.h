#ifndef JUMPSLIDER_H
#define JUMPSLIDER_H

#include <QSlider>

class JumpSlider : public QSlider
{
    Q_OBJECT
    public:

        explicit JumpSlider(QWidget *parent = 0);

    protected:

        void mousePressEvent ( QMouseEvent * event );

private slots:

        void slotSliderMoved(int val);
};

#endif // JUMPSLIDER_H
