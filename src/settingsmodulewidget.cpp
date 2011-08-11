#include "settingsmodulewidget.h"

SettingsModuleWidget::SettingsModuleWidget(SettingsModule* settingsModule, QWidget *parent) :
    QWidget(parent), settingsModule(settingsModule)
{
}

bool SettingsModuleWidget::isModified()
{
    return  settingsModule->isModified();
}
