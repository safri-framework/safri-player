#include "PlaylistTabWidget.h"
#include <QPushButton>
#include <QVariant>
#include <QDebug>

PlaylistTabWidget::PlaylistTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabsClosable(true);
    //this->setTabShape(QTabWidget::Triangular);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));

    QPushButton* addTabButton = new QPushButton(parent);
    addTabButton->setProperty("type", QVariant("addTabButton") );
    connect(addTabButton, SIGNAL (clicked() ), this, SLOT( onAddTabButtonClicked() ) );

    this->setCornerWidget(addTabButton, Qt::TopRightCorner );
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
