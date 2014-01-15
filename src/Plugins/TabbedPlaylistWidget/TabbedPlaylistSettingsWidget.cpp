#include "TabbedPlaylistSettingsWidget.h"
#include "ui_TabbedPlaylistSettingsWidget.h"

#include "Settings/SettingsModule.h"

TabbedPlaylistSettingsWidget::TabbedPlaylistSettingsWidget(Core::ISettingsModule *settingsModule, QWidget *parent) :
    ISettingsModuleWidget(parent),
    ui(new Ui::TabbedPlaylistSettingsWidget), settingsModule(settingsModule)
{
    ui->setupUi(this);

    bool saveTabsOnClose = settingsModule->getSetting("saveTabsOnClose").toBool();
    bool loadTabsOnStart = settingsModule->getSetting("loadTabsOnStart").toBool();

    if (saveTabsOnClose)
    {
        ui->radioSaveTabsOnClose->setChecked(true);
    }
    else
    {
        if (loadTabsOnStart)
        {
            ui->radioLoadTabsOnStart->setChecked(true);
        }
        else
        {
            ui->radioEmptyPlaylistOnStart->setChecked(true);
        }
    }

    //ui->checkSaveTabsOnClose->setChecked( settingsModule->getSetting("saveTabsOnClose").toBool() );
}

TabbedPlaylistSettingsWidget::~TabbedPlaylistSettingsWidget()
{
    delete ui;
}

QString TabbedPlaylistSettingsWidget::getTitle()
{
    return "Playliste";
}

QIcon TabbedPlaylistSettingsWidget::getIcon()
{
    return QIcon();
}

void TabbedPlaylistSettingsWidget::transferSettings()
{
    //settingsModule->setSetting("saveTabsOnClose", ui->checkSaveTabsOnClose->isChecked() );

    if ( ui->radioSaveTabsOnClose->isChecked() )
    {
        settingsModule->setSetting("saveTabsOnClose", true );
        settingsModule->setSetting("loadTabsOnStart", true );
    }
    else
    {
        settingsModule->setSetting("saveTabsOnClose", false );

        if ( ui->radioLoadTabsOnStart->isChecked() )
        {
            settingsModule->setSetting("loadTabsOnStart", true );
        }
        else
        {
            settingsModule->setSetting("loadTabsOnStart", false );
        }
    }

}

bool TabbedPlaylistSettingsWidget::isModified()
{
    return settingsModule->isModified();
}
