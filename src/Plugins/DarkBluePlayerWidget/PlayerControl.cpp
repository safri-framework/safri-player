#include "PlayerControl.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
PlayerControl::PlayerControl(QWidget *parent) :
    QWidget(parent),
    nextCurrentlyPressed(false),
    previousCurrentlyPressed(false),
    playPauseCurrentlyPressed(false),
    isPlaying(false)
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

     painter.drawImage(44,5, *progress);
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
