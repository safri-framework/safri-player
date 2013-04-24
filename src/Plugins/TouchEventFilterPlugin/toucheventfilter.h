#ifndef TOUCHEVENTFILTER_H
#define TOUCHEVENTFILTER_H

#include <QObject>

class TouchEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit TouchEventFilter(QObject *parent = 0);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void timer();

private:
    bool receiveClicks;
    bool pressed;

    
};

#endif // TOUCHEVENTFILTER_H
