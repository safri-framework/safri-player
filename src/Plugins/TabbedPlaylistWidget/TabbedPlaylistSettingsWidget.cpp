#include "TabbedPlaylistSettingsWidget.h"
#include "ui_TabbedPlaylistSettingsWidget.h"

#include "Settings/SettingsModule.h"

TabbedPlaylistSettingsWidget::TabbedPlaylistSettingsWidget(Core::ISettingsModule *settingsModule, QWidget *parent) :
    ISettingsModuleWidget(parent),
    ui(new Ui::TabbedPlaylistSettingsWidget), settingsModule(settingsModule)
{
    ui->setupUi(this);
    ui->checkSaveTabsOnClose->setChecked( settingsModule->getSetting("saveTabsOnClose").toBool() );
}

TabbedPlaylistSettingsWidget::~TabbedPlaylistSettingsWidget()
{
    delete ui;
}

QString TabbedPlaylistSettingsWidget::getTitle()
{
    return "Tabbed Playlist";
}

QIcon TabbedPlaylistSettingsWidget::getIcon()
{
    return QIcon();
}

void TabbedPlaylistSettingsWidget::transferSettings()
{
    settingsModule->setSetting("saveTabsOnClose", ui->checkSaveTabsOnClose->isChecked() );
}

bool TabbedPlaylistSettingsWidget::isModified()
{
    return settingsModule->isModified();
}
