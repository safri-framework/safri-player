#include "CollectionControllerSettingsDialog.h"
#include "ui_CollectionControllerSettingsDialog.h"

CollectionControllerSettingsDialog::CollectionControllerSettingsDialog(Core::ISettingsModule *settingsModule, QWidget *parent) :
    ISettingsModuleWidget(parent), ui(new Ui::CollectionControllerSettingsDialog), settingsModule(settingsModule)
{
    ui->setupUi(this);
    ui->leCollectionName->setText( settingsModule->getSetting("defaultCollectionName").toString() );
}

CollectionControllerSettingsDialog::~CollectionControllerSettingsDialog()
{
    delete ui;
}

QString CollectionControllerSettingsDialog::getTitle()
{
    return "Collection";
}

QIcon CollectionControllerSettingsDialog::getIcon()
{
    return QIcon(":/icons/ressources/collection_icon.png");
}

void CollectionControllerSettingsDialog::transferSettings()
{
    settingsModule->setSetting("defaultCollectionName", ui->leCollectionName->text() );
}

bool CollectionControllerSettingsDialog::isModified()
{
    return settingsModule->isModified();
}
