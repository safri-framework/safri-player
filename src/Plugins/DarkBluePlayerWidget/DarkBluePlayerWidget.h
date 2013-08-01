#ifndef DARKBLUEPLAYERWIDGET_H
#define DARKBLUEPLAYERWIDGET_H

#include "Interfaces/IPlayerWidget.h"

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
};

#endif // DARKBLUEPLAYERWIDGET_H
