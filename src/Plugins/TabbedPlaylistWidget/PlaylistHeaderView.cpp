#include "PlaylistHeaderView.h"
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>
#include "Interfaces/ICore.h"
#include "Settings/SettingsManager.h"

PlaylistHeaderView::PlaylistHeaderView(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent)
{
    qDebug() << "PlaylistHeaderView";

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect( this, SIGNAL( customContextMenuRequested(QPoint) ), this, SLOT( onContextMenuRequested(QPoint) ) );

    setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    Core::SettingsModule* settingsModule = Core::ICore::settingsManager()->getModule("org.safri.playlist");
    connect( settingsModule, SIGNAL( settingsChanged(QString) ), this, SLOT( settingsChanged(QString) ) );
}

PlaylistHeaderView::~PlaylistHeaderView()
{
}

void PlaylistHeaderView::setModel(QAbstractItemModel *model)
{
    QHeaderView::setModel(model);

    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");
    QString selectedHeaders = settings->getSetting("selectedHeaders").toString();

    setSectionVisibilityFromSettings(selectedHeaders);
}

void PlaylistHeaderView::onContextMenuRequested(QPoint pos)
{
    QMenu* contextMenu = new QMenu("Kontext menü", this);
    QMenu* columnSubMenu;
    QAction* selectColumnAction;
    QSignalMapper selectColumnSignalMapper;

    columnSubMenu = contextMenu->addMenu("Spalten");

    for (int i = 1; i < count(); i++)
    {
        selectColumnAction = new QAction( model()->headerData(i, Qt::Horizontal).toString() , columnSubMenu);

        selectColumnAction->setCheckable(true);
        selectColumnAction->setChecked( !isSectionHidden(i) );

        connect( selectColumnAction, SIGNAL( triggered() ), &selectColumnSignalMapper, SLOT( map() ) );
        selectColumnSignalMapper.setMapping(selectColumnAction, i);

        columnSubMenu->addAction(selectColumnAction);
    }

    connect(&selectColumnSignalMapper, SIGNAL( mapped(int) ), this, SLOT( toggleSectionVisibility(int) ) );

    contextMenu->exec(mapToGlobal(pos));


    QList<QAction*> columnActions = columnSubMenu->actions();

    for (int i = 0; i < columnActions.size(); i++)
    {
        delete columnActions.at(i);
    }

    delete columnSubMenu;
    delete contextMenu;
}

void PlaylistHeaderView::toggleSectionVisibility(int section)
{
    setSectionHidden(section, ! isSectionHidden(section) );

    saveSectionVisibilitySettings();
}

void PlaylistHeaderView::saveSectionVisibilitySettings()
{
    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");

    QString selectedHeaders = "";

    for (int i = 1; i < count(); i++)
    {
        if ( !isSectionHidden(i) )
        {
            if ( !selectedHeaders.isEmpty() )
            {
                selectedHeaders += ";";
            }

            selectedHeaders += QString::number(i);
        }
    }

    settings->setSetting("selectedHeaders", selectedHeaders);
    Core::ICore::settingsManager()->saveSettings();
}

void PlaylistHeaderView::settingsChanged(QString setting)
{
    if ( setting == "selectedHeaders" )
    {
        Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");
        QString selectedHeaders = settings->getSetting("selectedHeaders").toString();

        setSectionVisibilityFromSettings(selectedHeaders);
    }
}

void PlaylistHeaderView::setSectionVisibilityFromSettings(QString selectedHeaders)
{
    QStringList selectedHeadersList = selectedHeaders.split(";", QString::SkipEmptyParts);
    bool hide;

    if ( count() >= 0)
    {
        setSectionHidden(0, false);

        for (int i = 1; i < count(); i++)
        {
            hide = ! selectedHeadersList.contains( QString::number(i) );

            setSectionHidden(i, hide);
        }
    }
}
