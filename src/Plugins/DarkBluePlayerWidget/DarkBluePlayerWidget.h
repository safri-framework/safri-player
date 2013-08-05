#ifndef DARKBLUEPLAYERWIDGET_H
#define DARKBLUEPLAYERWIDGET_H

#include "Interfaces/IPlayerWidget.h"
#include <QMainWindow>
#include "PlayerControl.h"

namespace Ui {
class DarkBluePlayerWidget;
}

class DarkBluePlayerWidget : public IPlayerWidget
{
    Q_OBJECT
    
    public:

        explicit DarkBluePlayerWidget(QWidget *parent = 0);
        ~DarkBluePlayerWidget();

        virtual PlayerWidgetPosition    getPreferedPosition();
        virtual void                    setVolumeEnabled(bool value);
        virtual void                    setSeekerEnabled(bool value);

    private:

        void loadStylesheet();
        Ui::DarkBluePlayerWidget *ui;
        QWidget* window;
        PlayerControl* playerControl;

    private slots:
        void objectAddedToObjectPool(QObject* object);

protected:
        bool eventFilter(QObject *obj, QEvent *event);

};

#endif // DARKBLUEPLAYERWIDGET_H
