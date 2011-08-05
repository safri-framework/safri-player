#ifndef OSDISPLAY_H
#define OSDISPLAY_H

#include <QWidget>

class AudioFile;
class QTimer;

namespace Ui
{
    class OSDisplay;
}

class OSDisplay : public QWidget
{
    Q_OBJECT

    public:
        explicit OSDisplay(QWidget *parent = 0);
        ~OSDisplay();

        void showCurrentSong(AudioFile* af);

    protected:

        void mousePressEvent(QMouseEvent* event);

    private:
        Ui::OSDisplay *ui;
        QRegion roundedRect(const QRect& rect, int r);

        QTimer* timer;
};

#endif // OSDISPLAY_H
