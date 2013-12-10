#include "PlayerControl.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include "ProgressCircle.h"
PlayerControl::PlayerControl(QWidget *parent) :
    QWidget(parent),
    nextCurrentlyPressed(false),
    previousCurrentlyPressed(false),
    playPauseCurrentlyPressed(false),
    isPlaying(false),
    showSpinner(false),
    showProgress(false),
    count(0)
{
    next            = new QImage(":/control/Ressources/control/next_normal.png");
    nextPressed     = new QImage(":/control/Ressources/control/next_pressed.png");
    previous        = new QImage(":/control/Ressources/control/previous_normal.png");
    previousPressed = new QImage(":/control/Ressources/control/previous_pressed.png");
    playing         = new QImage(":/control/Ressources/control/playing.png");
    playingPressed  = new QImage(":/control/Ressources/control/playing_pressed.png");
    pause           = new QImage(":/control/Ressources/control/paused.png");
    pausePressed    = new QImage(":/control/Ressources/control/paused_pressed.png");
    progress    = new QImage(":/control/Ressources/control/progress.png");

    this->setMinimumHeight(65);
    this->setMaximumHeight(65);
    this->setMinimumWidth(149);
    this->setMaximumWidth(149);

    QTimer* rotationTimer = new QTimer(this);
    rotationTimer->setInterval(5);
    connect(rotationTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    rotationTimer->start();
}

void PlayerControl::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(!nextCurrentlyPressed)
        painter.drawImage(75,27, *next);
    else
       painter.drawImage(75,27, *nextPressed);

    if(!previousCurrentlyPressed)
        painter.drawImage(0,27, *previous);
    else
        painter.drawImage(0,27, *previousPressed);



    if(isPlaying)
    {
        if(!playPauseCurrentlyPressed)
            painter.drawImage(43,3, *playing);
        else
            painter.drawImage(43,3, *playingPressed);
    }
    else
    {
        if(!playPauseCurrentlyPressed)
            painter.drawImage(43,3, *pause);
        else
            painter.drawImage(43,3, *pausePressed);
    }

    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(QBrush(QColor(132,178,214,100)),4);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    if(showProgress)
        painter.drawArc(46,6,progress->width()-2, progress->height()-2, 90*16, -16*progressAngle);

    if(showSpinner)
    {
        pen = QPen(QBrush(QColor(90,168,202,200)),4);
        painter.setPen(pen);
        painter.drawArc(46,6,progress->width()-2, progress->height()-2, -16*rotation, 32);
        pen = QPen(QBrush(QColor(132,178,214,100)),4);
        painter.setPen(pen);
        painter.drawArc(46,6,progress->width()-2, progress->height()-2, -16*rotation2, 32);
        painter.drawArc(46,6,progress->width()-2, progress->height()-2, -16*rotation3, 32);
    }

     /*
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
     painter.translate(45+progress->width()/2,5+progress->height()/2);
     painter.rotate(rotation);
     painter.drawImage(progress->width()/-2, progress->height()/-2, *progress);
     */
}

void PlayerControl::mousePressEvent(QMouseEvent *event)
{
    if(event->x() > 105 && event->x() < 75 + next->width() && event->y() > 27 && event->y() < 27 + next->width())
        nextCurrentlyPressed = true;

    if(event->x() < next->width() -30 && event->y() > 27) //&& event->y() < 27 + next->width())
        previousCurrentlyPressed = true;

    if(event->x() > 43 && event->x() < 105)
    {
        playPauseCurrentlyPressed = true;
    }
    repaint();
}

void PlayerControl::mouseReleaseEvent(QMouseEvent *)
{

    if(playPauseCurrentlyPressed)
    {
        isPlaying = !isPlaying;
        Q_EMIT playToggled(isPlaying);
    }

    if(nextCurrentlyPressed)
    {
        Q_EMIT nextClicked();
    }

    if(previousCurrentlyPressed)
    {
        Q_EMIT previousClicked();
    }

    nextCurrentlyPressed = false;
    previousCurrentlyPressed = false;
    playPauseCurrentlyPressed = false;

    repaint();
}

void PlayerControl::setPlaying(bool val)
{
    isPlaying = val;
}

void PlayerControl::timeout()
{
    count = ++count %6;
    rotation = ++rotation%360;
    if (count % 2 == 0)
        rotation2 = ++rotation2%360;
    if (count % 3 == 0)
        rotation3 = ++rotation3%360;

    repaint();
}

int PlayerControl::getProgressAngle() const
{
    return progressAngle;
}

void PlayerControl::setProgressAngle(int value)
{
    progressAngle = value;
}

int PlayerControl::getProgress() const
{
    return (progressAngle/360) * 100 ;
}

void PlayerControl::setProgress(int value)
{
    progressAngle = value * 3.6;
}

bool PlayerControl::getShowSpinner() const
{
    return showSpinner;
}

void PlayerControl::setShowSpinner(bool value)
{
    showSpinner = value;
}

bool PlayerControl::getShowProgress() const
{
    return showProgress;
}

void PlayerControl::setShowProgress(bool value)
{
    showProgress = value;
}
