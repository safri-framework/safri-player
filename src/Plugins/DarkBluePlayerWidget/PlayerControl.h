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

    bool getShowProgress() const;
    void setShowProgress(bool value);

    bool getShowSpinner() const;
    void setShowSpinner(bool value);

    int getProgress() const;
    void setProgress(int value);

    int getProgressAngle() const;
    void setProgressAngle(int value);

signals:
    void playClicked();
    void playToggled(bool val);
    void previousClicked();
    void nextClicked();
    
private slots:
    void timeout();
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
    bool showProgress;
    bool showSpinner;
    int rotation;
    int rotation2;
    int rotation3;
    int count;
    int progressAngle;

};

#endif // PLAYERCONTROL_H
