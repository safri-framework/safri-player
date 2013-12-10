#ifndef PROGRESSCIRCLE_H
#define PROGRESSCIRCLE_H

#include <QWidget>
#include <QImage>
#include <QTimer>

class ProgressCircle : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressCircle(QWidget *parent = 0);

private:
    QImage* progress;
    QTimer* timer;
    int rotation;
    int speed;
signals:
    
public slots:
    void rotate();
    void setRotaion(int speed);

protected:
    void paintEvent(QPaintEvent *);
    
};

#endif // PROGRESSCIRCLE_H
