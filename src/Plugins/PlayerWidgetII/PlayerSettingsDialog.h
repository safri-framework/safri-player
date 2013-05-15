#ifndef PLAYERSETTINGSDIALOG_H
#define PLAYERSETTINGSDIALOG_H

#include <QWidget>
#include "Interfaces/ISettingsModuleWidget.h"
#include "Interfaces/ISettingsModule.h"

namespace Ui
{
    class PlayerSettingsDialog;
}

class PlayerSettingsDialog : public Core::ISettingsModuleWidget
{
    Q_OBJECT
    public:

        explicit PlayerSettingsDialog(Core::ISettingsModule *settingsModule, QWidget *parent = 0);
        ~PlayerSettingsDialog();
        QString     getTitle();
        QIcon       getIcon();

    public slots:

        virtual void transferSettings();
        virtual bool isModified();

    private:

        Ui::PlayerSettingsDialog *ui;
        Core::ISettingsModule *settingsModule;
};

#endif // PLAYERSETTINGSDIALOG_H
