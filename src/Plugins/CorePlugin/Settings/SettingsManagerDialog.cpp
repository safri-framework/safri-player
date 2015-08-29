#include "SettingsManagerDialog.h"
#include "Settings/SettingsManager.h"
#include "ui_SettingsManagerDialog.h"
#include "Interfaces/ISettingsModuleWidget.h"
#include "pluginmanager.h"
#include <QListWidgetItem>

using namespace Core;

SettingsManagerDialog::SettingsManagerDialog(SettingsManager *settingsManager, QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsManagerDialog), settingsManager(settingsManager), settingsModuleWidgets()
{
    ui->setupUi(this);

    settingsModuleWidgets = PluginSystem::PluginManager::getObjects<Core::ISettingsModuleWidget>();
    ISettingsModuleWidget*  settingsWidget;
    QListWidgetItem* listWidgetItem;
    QColor bgColor = QColor(212, 208, 200);

    for (int i = 0; i < settingsModuleWidgets.size(); i++)
    {
        settingsWidget = settingsModuleWidgets.at(i);
        ui->settingsModuleWidgets->addWidget(settingsWidget);

        listWidgetItem = new QListWidgetItem(ui->settingsModuleIconList);

        listWidgetItem->setIcon(settingsWidget->getIcon());
        listWidgetItem->setText(settingsWidget->getTitle());
        listWidgetItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        listWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        listWidgetItem->setBackgroundColor(bgColor);
    }

    //ui->settingsModuleIconList->setViewMode(QListView::IconMode);
    ui->settingsModuleIconList->setIconSize(QSize(32, 32));
    ui->settingsModuleIconList->setMovement(QListView::Static);
    //ui->settingsModuleIconList->setMaximumWidth(128);
    //ui->settingsModuleIconList->setSpacing(14);
    //ui->settingsModuleIconList->setGridSize(QSize(90, 90));

    ui->settingsModuleIconList->setCurrentRow(0);

    connect(ui->settingsModuleIconList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changeSettingsModuleWidget(QListWidgetItem*,QListWidgetItem*)));

    this->setModal(true);
    //this->setStyleSheet("background-image:url();");
}

SettingsManagerDialog::~SettingsManagerDialog()
{

    int settingsModuleCount = settingsModuleWidgets.size();
    ISettingsModuleWidget* moduleWidget;

    for (int i = 0; i < settingsModuleCount; i++)
    {
        moduleWidget = settingsModuleWidgets.at(i);
        moduleWidget->setParent(0);
    }

    delete ui;
}

void SettingsManagerDialog::saveSettings()
{
    int settingsModuleCount = settingsModuleWidgets.size();
    ISettingsModuleWidget* moduleWidget;
    bool hasModifiedSettings = false;

    for (int i = 0; i < settingsModuleCount; i++)
    {
        moduleWidget = settingsModuleWidgets.at(i);
        moduleWidget->transferSettings();

        if ( moduleWidget->isModified() )
        {
            hasModifiedSettings = true;
        }

    }

    if ( hasModifiedSettings )
    {
        settingsManager->saveSettings();
    }
}

void SettingsManagerDialog::changeSettingsModuleWidget(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui->settingsModuleWidgets->setCurrentIndex(ui->settingsModuleIconList->row(current));
}
