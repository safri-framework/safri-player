#ifndef COLLECTIONCONTROLLERSETTINGSDIALOG_H
#define COLLECTIONCONTROLLERSETTINGSDIALOG_H

#include <QWidget>
#include "Interfaces/ISettingsModuleWidget.h"
#include "Interfaces/ISettingsModule.h"

namespace Ui
{
    class CollectionControllerSettingsDialog;
}

class CollectionControllerSettingsDialog : public Core::ISettingsModuleWidget
{
    Q_OBJECT
    public:

        explicit CollectionControllerSettingsDialog(Core::ISettingsModule *settingsModule, QWidget *parent = 0);
        ~CollectionControllerSettingsDialog();
        QString     getTitle();
        QIcon       getIcon();

    public slots:

        virtual void    transferSettings();
        virtual bool    isModified();

    private:

        Ui::CollectionControllerSettingsDialog *ui;
        Core::ISettingsModule *settingsModule;
};

#endif // COLLECTIONCONTROLLERSETTINGSDIALOG_H
