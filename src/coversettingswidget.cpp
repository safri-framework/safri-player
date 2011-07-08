#include "coversettingswidget.h"
#include "ui_coversettingswidget.h"

CoverSettingsWidget::CoverSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverSettingsWidget)
{
    ui->setupUi(this);


    QStringList values = DatabaseDAO::getSetting("ALBUM_COVER_FILENAME");
    filenamePatternModel = new QStringListModel(values);

    ui->filenamePatterns->setModel(filenamePatternModel);

}

CoverSettingsWidget::~CoverSettingsWidget()
{
    delete ui;
}

void CoverSettingsWidget::on_addCoverFilePattern_clicked()
{
    filenamePatternModel->insertRow(filenamePatternModel->rowCount());
}
