#include "PlaylistTabWidget.h"
#include <QPushButton>
#include <QVariant>
#include <QDebug>
#include <QTabBar>
#include <QLineEdit>
#include "PlaylistView.h"

PlaylistTabWidget::PlaylistTabWidget(QWidget *parent) :
    QTabWidget(parent), tabIndexEdit(-1)
{
    this->setTabsClosable(true);
    //this->setTabShape(QTabWidget::Triangular);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));

    QPushButton* addTabButton = new QPushButton(parent);
    addTabButton->setProperty("type", QVariant("addTabButton") );
    connect(addTabButton, SIGNAL (clicked() ), this, SLOT( onAddTabButtonClicked() ) );

    this->setMovable(true);
    this->tabBar()->setExpanding(true);

    this->setCornerWidget(addTabButton, Qt::TopRightCorner );
}

void PlaylistTabWidget::removePlaylistTab(int index)
{
    onTabCloseRequested(index);
}

void PlaylistTabWidget::editTabName(int index)
{
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setProperty("type", "tabRename");

    lineEdit->setText( tabBar()->tabText(index) );
    lineEdit->selectAll();
    tabBar()->setTabText(index, "");

    tabIndexEdit = index;
    connect( lineEdit, SIGNAL( returnPressed() ), this, SLOT( tabTextEditedFinished() ) );

    this->tabBar()->setTabButton(index, QTabBar::LeftSide, lineEdit );

    lineEdit->setFocus();
}

void PlaylistTabWidget::onTabCloseRequested(int index)
{
    QWidget* tabWidgetToRemove = this->widget(index);
    this->removeTab(index);
    delete tabWidgetToRemove;

    if (this->count() < 1)
    {
        Q_EMIT lastTabRemoved(this);
    }
}

void PlaylistTabWidget::onAddTabButtonClicked()
{
    Q_EMIT addNewTab(this);
}

void PlaylistTabWidget::tabTextEditedFinished()
{
    QLineEdit* senderEdit = qobject_cast<QLineEdit*>( sender() );


    if (tabIndexEdit != -1)
    {

        tabBar()->setTabButton(tabIndexEdit, QTabBar::LeftSide, 0);
        tabBar()->setTabText(tabIndexEdit, senderEdit->text() );
        PlaylistView* playlistView = qobject_cast<PlaylistView*>( widget(tabIndexEdit) );
        playlistView->setName( senderEdit->text() );

        tabIndexEdit = -1;
    }

    senderEdit->deleteLater();
    senderEdit = 0;
}
