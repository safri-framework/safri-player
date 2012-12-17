#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Interfaces/isidebarplugin.h"
#include <QPushButton>
#include "pluginmanager.h"
#include <QSplitter>


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
    
private:
    Ui::MainWindow *ui;
    void readAndSetStylesheet();
    int visiblePlugins;
    Core::IGUIController* guiController;
    QList<Core::ISideBarPlugin*> plugins;
    QList<QWidget*> sidebarWidgets;
    QList<QPushButton*> tabButtons;
    void addPlugin(Core::ISideBarPlugin* plugin);
    QSplitter* splitter;
    QList<int> lastSplitterSize;
private slots:
    void sideBarButtonClicked(bool checked);
    void changePlayerWidget();
    void showRequest(bool show);

public slots:
    void pluginAdded(QObject* plugin);
    void showSidebar(bool visible);
};

#endif // MAINWINDOW_H
