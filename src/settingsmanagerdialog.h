#ifndef SETTINGSMANAGERDIALOG_H
#define SETTINGSMANAGERDIALOG_H

#include <QDialog>
#include <QList>

class QListWidgetItem;
class SettingsModuleWidget;

namespace Ui
{
    class SettingsManagerDialog;
}

class SettingsManagerDialog : public QDialog
{
    Q_OBJECT

    public:

        explicit SettingsManagerDialog(QWidget *parent = 0);
        ~SettingsManagerDialog();

    public slots:

        void changeModuleSettingsWidget(QListWidgetItem *current, QListWidgetItem *previous);
        void saveSettings();

    private:

        Ui::SettingsManagerDialog *ui;
        QList<SettingsModuleWidget*> settingsWidgetList;

        void createIcons();
};

#endif // SETTINGSMANAGERDIALOG_H
