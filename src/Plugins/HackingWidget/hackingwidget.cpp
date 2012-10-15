#include "hackingwidget.h"
#include "ui_hackingwidget.h"
#include "icore.h"
#include "Interfaces/IAudioBackend.h"

HackingWidget::HackingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HackingWidget)
{
    ui->setupUi(this);
}

HackingWidget::~HackingWidget()
{
    delete ui;
}

void HackingWidget::on_pushButton_clicked()
{
    Core::ICore::audioBackend()->setVolume( ui->lineEdit->text().toInt() );
}
