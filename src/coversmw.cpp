#include "coversmw.h"
#include "ui_coversmw.h"

#include <QString>
#include <QMessageBox>


CoverSMW::CoverSMW(SettingsModule* settingsModule, QWidget *parent) :
    SettingsModuleWidget(settingsModule, parent), ui(new Ui::CoverSMW)
{
    ui->setupUi(this);

    QString filenamePatterns = this->settingsModule->getSetting("filenamePatterns").toString();
    QStringList filenamePatternsList = filenamePatterns.split(";", QString::SkipEmptyParts);

    this->filenamePatternModel = new QStringListModel(filenamePatternsList);

    ui->filenamePatternsView->setModel( filenamePatternModel  );

}

CoverSMW::~CoverSMW()
{
    delete ui;
}


void CoverSMW::saveSettings()
{
    QStringList filenamePatternsList = filenamePatternModel->stringList();
    QString filenamePatterns;

    foreach(QString filenamePattern, filenamePatternsList)
    {
        if (filenamePattern == "the answer to life, the universe and everything")
        {
            QMessageBox::critical(0, "the answer to life, the universe and everything", "42");
        }
        else
            filenamePatterns = filenamePatterns + filenamePattern + ";";
    }

    // remove last ';'
    filenamePatterns.remove( filenamePatterns.size() - 1, 1 );

    this->settingsModule->setSetting("filenamePatterns", filenamePatterns);

    this->settingsModule->saveSettings();

}

void CoverSMW::on_addCoverFilePattern_clicked()
{
    int row = filenamePatternModel->rowCount();
    filenamePatternModel->insertRow(row);
    filenamePatternModel->setData(filenamePatternModel->index(row), "%ARTIST - %ALBUM - Front.jpg", Qt::DisplayRole);
}

void CoverSMW::on_deleteCoverFilePattern_clicked()
{
   filenamePatternModel->removeRow( ui->filenamePatternsView->currentIndex().row() );
}

void CoverSMW::on_editCoverFilePattern_clicked()
{
    ui->filenamePatternsView->edit( ui->filenamePatternsView->currentIndex() );
}
