#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->descriptionLabel->setText(QString("<h4>Abschlussprojekt zur Lehrveranstaltung \"Qt\"<br>") +
                                  "an der FH Kaiserslautern Standort Zweibr�cken.</h4>" +
                                  "Im Team:\n<b>Sa</b>scha M�nzberg und <b>Fri</b>edemann Metzger");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
