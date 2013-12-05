#ifndef PROGRESSCIRCLE_H
#define PROGRESSCIRCLE_H

#include <QWidget>
#include <QImage>

class ProgressCircle : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressCircle(QWidget *parent = 0);

private:
    QImage* progress;
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *);
    
};

#endif // PROGRESSCIRCLE_H
