#ifndef VIEWSMW_H
#define VIEWSMW_H

#include "settingsmodulewidget.h"

namespace Ui
{
    class ViewSMW;
}

class ViewSMW : public SettingsModuleWidget
{
    Q_OBJECT

    public:
        explicit ViewSMW(SettingsModule* settingsModule, QWidget *parent = 0);
        ~ViewSMW();

    public slots:

        virtual void saveSettings();

private slots:
    void on_save_clicked();

private:
        Ui::ViewSMW *ui;

        int getIndexFromString(QString string);
        QString getStringFromIndex(int index);
};

#endif // VIEWSMW_H
