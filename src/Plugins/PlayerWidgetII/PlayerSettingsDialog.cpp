#include "PlayerSettingsDialog.h"
#include "ui_PlayerSettingsDialog.h"

PlayerSettingsDialog::PlayerSettingsDialog(Core::ISettingsModule *settingsModule, QWidget *parent) :
    ISettingsModuleWidget(parent), ui(new Ui::PlayerSettingsDialog), settingsModule(settingsModule)
{
    ui->setupUi(this);
}

PlayerSettingsDialog::~PlayerSettingsDialog()
{
    delete ui;
}

QString PlayerSettingsDialog::getTitle()
{
    return "Player";
}

QIcon PlayerSettingsDialog::getIcon()
{
    return QIcon(":/icons/SAFRI_UI/player_icon.png");
}

void PlayerSettingsDialog::transferSettings()
{
}

bool PlayerSettingsDialog::isModified()
{
    if ( settingsModule )
    {
        return settingsModule->isModified();
    }
    else
    {
        return false;
    }
}
