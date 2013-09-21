#ifndef TABBEDPLAYLISTSETTINGSWIDGET_H
#define TABBEDPLAYLISTSETTINGSWIDGET_H

#include "Interfaces/ISettingsModuleWidget.h"

namespace Ui
{
    class TabbedPlaylistSettingsWidget;
}

namespace Core
{
    class ISettingsModule;
}

class TabbedPlaylistSettingsWidget : public Core::ISettingsModuleWidget
{
    Q_OBJECT
    public:

        explicit TabbedPlaylistSettingsWidget(Core::ISettingsModule *settingsModule, QWidget *parent = 0);
        ~TabbedPlaylistSettingsWidget();
        QString     getTitle();
        QIcon       getIcon();

    public slots:

        virtual void    transferSettings();
        virtual bool    isModified();

    private:

        Ui::TabbedPlaylistSettingsWidget *ui;
        Core::ISettingsModule *settingsModule;
};

#endif // TABBEDPLAYLISTSETTINGSWIDGET_H
