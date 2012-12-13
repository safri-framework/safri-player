#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void sideBarButtonClicked(bool checked);
    void changePlayerWidget();
};

#endif // MAINWINDOW_H
