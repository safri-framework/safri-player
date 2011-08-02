#include "settingsmanagerdialog.h"
#include "ui_settingsmanagerdialog.h"

#include <QListWidgetItem>

#include "settingsmanager.h"
#include "coversmw.h"
#include "viewsmw.h"

SettingsManagerDialog::SettingsManagerDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingsManagerDialog)
{
    ui->setupUi(this);

    CoverSMW* coverSettingsWidget = new CoverSMW( SettingsManager::getInstance()->getModule("core.albumCover") );
    settingsWidgetList.append(coverSettingsWidget);
    ui->moduleSettingsWidget->addWidget(coverSettingsWidget);

    ViewSMW* viewSettingsWidget = new ViewSMW( SettingsManager::getInstance()->getModule("core.view") );
    settingsWidgetList.append(viewSettingsWidget);
    ui->moduleSettingsWidget->addWidget(viewSettingsWidget);

    ui->moduleSettingsWidget->setCurrentIndex(0);

    ui->moduleIconListWidget->setViewMode(QListView::IconMode);
    ui->moduleIconListWidget->setIconSize(QSize(86, 74));
    ui->moduleIconListWidget->setMovement(QListView::Static);
    ui->moduleIconListWidget->setMaximumWidth(128);
    ui->moduleIconListWidget->setSpacing(14);

    createIcons();
    ui->moduleIconListWidget->setCurrentRow(0);

    this->setModal(true);
    this->setStyleSheet("background-image:url();");


}

SettingsManagerDialog::~SettingsManagerDialog()
{
    delete ui;
}

void SettingsManagerDialog::changeModuleSettingsWidget(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;


    ui->moduleSettingsWidget->setCurrentIndex(ui->moduleIconListWidget->row(current));
}

void SettingsManagerDialog::createIcons()
{
    QListWidgetItem *coverSettingsButton = new QListWidgetItem(ui->moduleIconListWidget);

    coverSettingsButton->setIcon(QIcon("img/cover_settings_icon.png"));
    coverSettingsButton->setText(tr("Album Cover"));
    coverSettingsButton->setTextAlignment(Qt::AlignHCenter);
    coverSettingsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *viewSettingsButton = new QListWidgetItem(ui->moduleIconListWidget);

    viewSettingsButton->setIcon(QIcon("img/view_settings_icon.png"));
    viewSettingsButton->setText(tr("Ansicht"));
    viewSettingsButton->setTextAlignment(Qt::AlignHCenter);
    viewSettingsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *databaseSettingsButton = new QListWidgetItem(ui->moduleIconListWidget);

    databaseSettingsButton->setIcon(QIcon("img/music_icon.png"));
    databaseSettingsButton->setText(tr("Datenbank"));
    databaseSettingsButton->setTextAlignment(Qt::AlignHCenter);
    databaseSettingsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    connect(ui->moduleIconListWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changeModuleSettingsWidget(QListWidgetItem*,QListWidgetItem*)));
}

void SettingsManagerDialog::saveSettings()
{
    int len = settingsWidgetList.size();

    for (int i = 0; i < len; i++)
    {
        settingsWidgetList.at(i)->saveSettings();
    }
}
