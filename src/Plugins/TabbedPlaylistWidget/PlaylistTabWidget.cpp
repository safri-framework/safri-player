#include "PlaylistTabWidget.h"
#include <QPushButton>
#include <QVariant>
#include <QDebug>
#include <QLineEdit>
#include <QList>
#include "PlaylistView.h"

#include "PlaylistTabBar.h"

PlaylistTabWidget::PlaylistTabWidget(QWidget *parent) :
    QTabWidget(parent), tabIndexEdit(-1)
{

    PlaylistTabBar* playlistTabBar = new PlaylistTabBar(0);
    connect(playlistTabBar, SIGNAL( tabDoubleClicked(int) ), this, SLOT( onTabDoubleClicked(int) ) );

    this->setTabBar( playlistTabBar );

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
    qDebug() << "EDIT INDEX: " << index;
    connect( lineEdit, SIGNAL( editingFinished() ), this, SLOT( tabTextEditedFinished() ) );

    this->tabBar()->setTabButton(index, QTabBar::LeftSide, lineEdit );

    lineEdit->setFocus();
}

QSharedPointer<Core::IPlaylist> PlaylistTabWidget::getPlaylist(int index)
{
    PlaylistView* playlistView = qobject_cast<PlaylistView*>( widget(index)->findChildren<PlaylistView*>().at(0) );

    PlaylistModel* playlistModel = qobject_cast<PlaylistModel*>( playlistView->model() );

    return playlistModel->getPlaylist();
}

void PlaylistTabWidget::onTabCloseRequested(int index)
{
    abortTabTextEditing();

    QWidget* tabWidgetToRemove = this->widget(index);
    this->removeTab(index);
    delete tabWidgetToRemove;

    if (this->count() < 1)
    {
        Q_EMIT lastTabRemoved(this);
    }
}

void PlaylistTabWidget::onTabDoubleClicked(int index)
{
    // only edit tab, when it's not already beeing edited
    if (tabIndexEdit == -1)
    {
        editTabName(index);
    }
}

void PlaylistTabWidget::onAddTabButtonClicked()
{
    Q_EMIT addNewTab(this);
}

void PlaylistTabWidget::tabTextEditedFinished()
{
    if (tabIndexEdit != -1)
    {
        // we save the tabIndexEdit in a temporary variable
        // the removing of the LineEdit from the TabBar will trigger the editingFinished signal
        // again, an this function will be called recursively
        // to prevent the recursive call to process this editing again
        // we set tabIndexEdit to -1 emediately
        int tmpTabIndexEdit = tabIndexEdit;
        tabIndexEdit = -1;

        QLineEdit* senderEdit = qobject_cast<QLineEdit*>( sender() );

        tabBar()->setTabButton(tmpTabIndexEdit, QTabBar::LeftSide, 0);
        tabBar()->setTabText(tmpTabIndexEdit, senderEdit->text() );
        PlaylistView* playlistView = qobject_cast<PlaylistView*>( widget(tmpTabIndexEdit)->findChildren<PlaylistView*>().at(0) );
        playlistView->setName( senderEdit->text() );



        senderEdit->deleteLater();
        senderEdit = 0;
    }
}

void PlaylistTabWidget::abortTabTextEditing()
{
    if (tabIndexEdit != -1)
    {
        tabIndexEdit = -1;

        int tmpTabIndexEdit = tabIndexEdit;
        tabIndexEdit = -1;

        tabBar()->setTabButton(tmpTabIndexEdit, QTabBar::LeftSide, 0);
    }
}
