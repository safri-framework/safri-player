#ifndef HACKINGWIDGET_H
#define HACKINGWIDGET_H

#include <QWidget>
#include "HackingWidget_global.h"

namespace Ui {
class HACKINGWIDGETSHARED_EXPORT HackingWidget;
}

class HACKINGWIDGETSHARED_EXPORT HackingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HackingWidget(QWidget *parent = 0);
    ~HackingWidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::HackingWidget *ui;
};

#endif // HACKINGWIDGET_H
