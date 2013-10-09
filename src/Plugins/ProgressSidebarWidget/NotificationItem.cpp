#include "NotificationItem.h"
#include "ui_NotificationItem.h"

NotificationItem::NotificationItem(QString progressName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationItem)
{
    ui->setupUi(this);
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
    this->ui->label->setText(progressName);
}

NotificationItem::~NotificationItem()
{
    delete ui;
}

void NotificationItem::setProgressValue(int current, int max, int min)
{
    this->ui->progressBar->setValue(current);
    this->ui->progressBar->setMaximum(max);
    this->ui->progressBar->setMinimum(min);
}
