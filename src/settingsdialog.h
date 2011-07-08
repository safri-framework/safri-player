#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

#include "coversettingswidget.h"
#include "databasesettingswidget.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit SettingsDialog(QWidget *parent = 0);
        ~SettingsDialog();

    public slots:
        void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    private:
        Ui::SettingsDialog *ui;

        void createIcons();
};

#endif // SETTINGSDIALOG_H
