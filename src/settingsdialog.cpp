#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);


    ui->pagesWidget->setCurrentIndex(0);

    ui->contentsWidget->setViewMode(QListView::IconMode);
    ui->contentsWidget->setIconSize(QSize(86, 74));
    ui->contentsWidget->setMovement(QListView::Static);
    ui->contentsWidget->setMaximumWidth(128);
    ui->contentsWidget->setSpacing(14);

    createIcons();
    ui->contentsWidget->setCurrentRow(0);


    this->setStyleSheet("");

    //(new CoverSettingsWidget)->show();

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::createIcons()
{
    QListWidgetItem *coverSettingsButton = new QListWidgetItem(ui->contentsWidget);

    coverSettingsButton->setIcon(QIcon("img/cover_settings_icon.png"));
    coverSettingsButton->setText(tr("Album Cover"));
    coverSettingsButton->setTextAlignment(Qt::AlignHCenter);
    coverSettingsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *databaseSettingsButton = new QListWidgetItem(ui->contentsWidget);

    databaseSettingsButton->setIcon(QIcon("img/music_icon.png"));
    databaseSettingsButton->setText(tr("Datenbank"));
    databaseSettingsButton->setTextAlignment(Qt::AlignHCenter);
    databaseSettingsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(ui->contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

}

void SettingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;


    ui->pagesWidget->setCurrentIndex(ui->contentsWidget->row(current));
}
