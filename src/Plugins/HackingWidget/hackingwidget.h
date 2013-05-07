#ifndef HACKINGWIDGET_H
#define HACKINGWIDGET_H

#include <QWidget>
#include "HackingWidget_global.h"

namespace Ui {
class HACKINGWIDGETSHARED_EXPORT HackingWidget;
}

namespace Core { class IPlaybackController; class IAudioCollection; }

class HACKINGWIDGETSHARED_EXPORT HackingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HackingWidget(QWidget *parent = 0);
    ~HackingWidget();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_verticalSlider_sliderMoved(int position);

    void update(int currentTime);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void infoSlot();

private:
    Ui::HackingWidget *ui;
    Core::IAudioCollection* audioCollection;
    Core::IPlaybackController *playbackController;
};

#endif // HACKINGWIDGET_H
