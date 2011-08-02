#ifndef SETTINGSMODULEWIDGET_H
#define SETTINGSMODULEWIDGET_H

#include <QWidget>
#include "settingsmodule.h"

class SettingsModuleWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit SettingsModuleWidget(SettingsModule* settingsModule = 0, QWidget *parent = 0);

    signals:

    public slots:

        virtual void saveSettings() = 0;

    protected:

        SettingsModule* settingsModule;

};

#endif // SETTINGSMODULEWIDGET_H
