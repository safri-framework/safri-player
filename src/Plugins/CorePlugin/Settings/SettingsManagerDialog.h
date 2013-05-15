#ifndef SETTINGSMANAGERDIALOG_H
#define SETTINGSMANAGERDIALOG_H

#include <QDialog>
#include <QList>

class QListWidgetItem;

namespace Ui
{
    class SettingsManagerDialog;
}

namespace Core
{
    class ISettingsModuleWidget;
    class SettingsManager;

    class SettingsManagerDialog : public QDialog
    {
        Q_OBJECT
        public:

            explicit SettingsManagerDialog(SettingsManager* settingsManager, QWidget *parent = 0);
            ~SettingsManagerDialog();

            void saveSettings();

        private slots:

            void changeSettingsModuleWidget(QListWidgetItem *current, QListWidgetItem *previous);

        private:

            Ui::SettingsManagerDialog *ui;
            SettingsManager* settingsManager;
            QList<ISettingsModuleWidget*> settingsModuleWidgets;
    };
}

#endif // SETTINGSMANAGERDIALOG_H
