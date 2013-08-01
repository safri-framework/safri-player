#include "DarkBluePlayerWidget.h"
#include "ui_DarkBluePlayerWidget.h"
#include <QFile>

DarkBluePlayerWidget::DarkBluePlayerWidget(QWidget *parent) :
    IPlayerWidget(parent),
    ui(new Ui::DarkBluePlayerWidget)
{
    ui->setupUi(this);
    loadStylesheet();
}

DarkBluePlayerWidget::~DarkBluePlayerWidget()
{
    delete ui;
}

IPlayerWidget::PlayerWidgetPosition DarkBluePlayerWidget::getPreferedPosition()
{
    return IPlayerWidget::BOTTOM;
}

void DarkBluePlayerWidget::loadStylesheet()
{
    QFile file;

    file.setFileName(":stylesheet/DarkBluePlayerStylesheet.css");
    file.open(QFile::ReadOnly);

    QString styleSheet = QLatin1String( file.readAll() );
    file.close();

    this->setStyleSheet(styleSheet);
}


void DarkBluePlayerWidget::setVolumeEnabled(bool value)
{
}

void DarkBluePlayerWidget::setSeekerEnabled(bool value)
{
}
