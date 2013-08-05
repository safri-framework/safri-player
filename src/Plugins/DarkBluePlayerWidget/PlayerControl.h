#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include <QWidget>

class PlayerControl : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerControl(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void setPlaying(bool val);

signals:
    void playClicked();
    void playToggled(bool val);
    void previousClicked();
    void nextClicked();
    
public slots:

private:
    QImage* next;
    QImage* nextPressed;
    QImage* previous;
    QImage* previousPressed;
    QImage* playing;
    QImage* playingPressed;
    QImage* pause;
    QImage* pausePressed;
    QImage* progress;

    bool nextCurrentlyPressed;
    bool previousCurrentlyPressed;
    bool playPauseCurrentlyPressed;
    bool isPlaying;

};

#endif // PLAYERCONTROL_H
