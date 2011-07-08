#include "databasesettingswidget.h"
#include "ui_databasesettingswidget.h"

DatabaseSettingsWidget::DatabaseSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseSettingsWidget)
{
    ui->setupUi(this);
}

DatabaseSettingsWidget::~DatabaseSettingsWidget()
{
    delete ui;
}
