#include "PlaylistTabWidget.h"
#include <QPushButton>
#include <QVariant>

PlaylistTabWidget::PlaylistTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabsClosable(true);
    //this->setTabShape(QTabWidget::Triangular);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));

    QPushButton* addTabButton = new QPushButton(parent);
    addTabButton->setProperty("type", QVariant("addTabButton") );

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
