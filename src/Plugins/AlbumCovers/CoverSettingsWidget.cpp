#include "CoverSettingsWidget.h"
#include "ui_CoverSettingsWidget.h"

CoverSettingsWidget::CoverSettingsWidget(QWidget *parent) :
    Core::ISettingsModuleWidget(parent),
    ui(new Ui::CoverSettingsWidget)
{
    ui->setupUi(this);
    connect(ui->updateButton, SIGNAL(clicked()), this, SIGNAL(updateCovers()));
}

CoverSettingsWidget::~CoverSettingsWidget()
{
    delete ui;
}

QString CoverSettingsWidget::getTitle()
{
    return "Cover Settings";
}

QIcon CoverSettingsWidget::getIcon()
{
    return QIcon(":/icons/ressources/no_cover.png");
}

void CoverSettingsWidget::transferSettings()
{
}

bool CoverSettingsWidget::isModified()
{
    return false;
}
