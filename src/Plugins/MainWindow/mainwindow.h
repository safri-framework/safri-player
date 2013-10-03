#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "Interfaces/ISideBarPlugin.h"
#include <QPushButton>
#include "pluginmanager.h"
#include <QSplitter>
#include <Interfaces/IPlayerWidget.h>
#include <QTimeLine>


#define ANIMATION_DURATION 300

namespace Ui {
class MainWindow;
}
namespace Core {
class IGUIController;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    protected:

        void closeEvent(QCloseEvent *event);

    private:

        Ui::MainWindow *ui;
        int visiblePlugins;
        Core::IGUIController* guiController;
        QList<Core::ISideBarPlugin*> plugins;
        QList<QWidget*> sidebarWidgets;
        QList<QPushButton*> tabButtons;
        void addPlugin(Core::ISideBarPlugin* plugin);
        QSplitter* splitter;
        QList<int> lastSplitterSize;

        void showTestPlaylist();
        QTimeLine* closeSidebarTimeline;
        QTimeLine* openSidebarTimeline;

    private slots:

        void sideBarButtonClicked(bool checked);
        void changePlayerWidget();
        void changePlaylistWidget();
        void showRequest(bool show);

        void on_actionPlugins_show_triggered();

        void closeSidebar(int l);
        void openSidebar(int r);



        void on_actionAdd_folder_triggered();

        void on_actionSave_triggered();

        void on_actionSettings_triggered();

        void objectAddedToObjectPool(QObject *object);

        void on_actionClose_triggered();

public slots:

        void pluginAdded(QObject* plugin);
        void showSidebar(bool visible);
};

#endif // MAINWINDOW_H
