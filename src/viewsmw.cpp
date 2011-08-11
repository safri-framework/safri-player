#include "viewsmw.h"
#include "ui_viewsmw.h"

#include <QStringListModel>
#include <QStringList>
#include <QDebug>

ViewSMW::ViewSMW(SettingsModule* settingsModule, QWidget *parent) :
    SettingsModuleWidget(settingsModule, parent), ui(new Ui::ViewSMW)
{
    ui->setupUi(this);

    QStringList baseDTOStringRepresentation;
    baseDTOStringRepresentation << "Interpret" << "Album" << "Titel" << "Genre" << "Dekade" << "Unbenutzt";

    QStringListModel* baseDTOStringModel = new QStringListModel(baseDTOStringRepresentation);

    ui->treeview1_level1->setModel(baseDTOStringModel);
    ui->treeview1_level2->setModel(baseDTOStringModel);
    ui->treeview1_level3->setModel(baseDTOStringModel);
    ui->treeview1_level4->setModel(baseDTOStringModel);
    ui->treeview1_level5->setModel(baseDTOStringModel);

    ui->treeview2_level1->setModel(baseDTOStringModel);
    ui->treeview2_level2->setModel(baseDTOStringModel);
    ui->treeview2_level3->setModel(baseDTOStringModel);
    ui->treeview2_level4->setModel(baseDTOStringModel);

    QString treeview1Hierarchy = this->settingsModule->getSetting("treeview1Hierarchy").toString();

    QStringList treeview1HierarchyList = treeview1Hierarchy.split(";", QString::SkipEmptyParts);

    // TODO: exorcism ;)
    treeview1HierarchyList << "Unbenutzt" << "Unbenutzt" << "Unbenutzt";

    ui->treeview1_level1->setCurrentIndex( getIndexFromString(treeview1HierarchyList.at(0))  );
    ui->treeview1_level2->setCurrentIndex( getIndexFromString(treeview1HierarchyList.at(1))  );
    ui->treeview1_level3->setCurrentIndex( getIndexFromString(treeview1HierarchyList.at(2))  );
    ui->treeview1_level4->setCurrentIndex( getIndexFromString(treeview1HierarchyList.at(3))  );
    ui->treeview1_level5->setCurrentIndex( getIndexFromString(treeview1HierarchyList.at(4))  );

    QStringList nowplayingDisplays;
    nowplayingDisplays << "Taskleisten Icon" << "On-Screen Display" << "keine Anzeige";

    ui->cmbNowplayingDisplay->setModel( new QStringListModel(nowplayingDisplays) );

    if ( settingsModule->getSetting("showTrayBalloon").toBool() )
    {
        ui->cmbNowplayingDisplay->setCurrentIndex(0);
    }
    else if ( settingsModule->getSetting("showOSDisplay").toBool() )
    {
        ui->cmbNowplayingDisplay->setCurrentIndex(1);
    }
    else
    {
        ui->cmbNowplayingDisplay->setCurrentIndex(2);
    }

    ui->spnDisplayTime->setValue( settingsModule->getSetting("nowplayingDisplayTime").toInt() );
}

ViewSMW::~ViewSMW()
{
    delete ui;
}


void ViewSMW::transferSettings()
{
    QString treeview1Hierarchy;

    if (getStringFromIndex(ui->treeview1_level1->currentIndex()) != "")
        treeview1Hierarchy = treeview1Hierarchy + getStringFromIndex(ui->treeview1_level1->currentIndex()) + ";";
    if (getStringFromIndex(ui->treeview1_level2->currentIndex()) != "")
        treeview1Hierarchy = treeview1Hierarchy + getStringFromIndex(ui->treeview1_level2->currentIndex()) + ";";
    if (getStringFromIndex(ui->treeview1_level3->currentIndex()) != "")
        treeview1Hierarchy = treeview1Hierarchy + getStringFromIndex(ui->treeview1_level3->currentIndex()) + ";";
    if (getStringFromIndex(ui->treeview1_level4->currentIndex()) != "")
        treeview1Hierarchy = treeview1Hierarchy + getStringFromIndex(ui->treeview1_level4->currentIndex()) + ";";
    if (getStringFromIndex(ui->treeview1_level5->currentIndex()) != "")
        treeview1Hierarchy = treeview1Hierarchy + getStringFromIndex(ui->treeview1_level5->currentIndex()) + ";";

    this->settingsModule->setSetting("treeview1Hierarchy", treeview1Hierarchy);

    switch ( ui->cmbNowplayingDisplay->currentIndex() )
    {
        case 0:

            settingsModule->setSetting("showTrayBalloon", 1);
            settingsModule->setSetting("showOSDisplay", 0);
            break;

        case 1:

            settingsModule->setSetting("showTrayBalloon", 0);
            settingsModule->setSetting("showOSDisplay", 1);
            break;

        case 2:

            settingsModule->setSetting("showTrayBalloon", 0);
            settingsModule->setSetting("showOSDisplay", 0);
            break;
    }

    settingsModule->setSetting("nowplayingDisplayTime", ui->spnDisplayTime->value());

}

int ViewSMW::getIndexFromString(QString string)
{
    if (string == "ARTIST")
        return 0;
    if (string == "ALBUM")
        return 1;
    if (string == "SONG")
        return 2;
    if (string == "GENRE")
        return 3;
    if (string == "DECADE")
        return 4;

    return 5;
}

QString ViewSMW::getStringFromIndex(int index)
{
    switch (index)
    {
        case 0:
            return "ARTIST";
        case 1:
            return "ALBUM";
        case 2:
            return "SONG";
        case 3:
            return "GENRE";
        case 4:
            return "DECADE";
    }

    return "";
}

void ViewSMW::on_save_clicked()
{
    this->transferSettings();
}
