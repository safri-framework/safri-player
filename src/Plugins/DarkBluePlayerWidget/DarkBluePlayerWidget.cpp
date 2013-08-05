#include "DarkBluePlayerWidget.h"
#include "ui_DarkBluePlayerWidget.h"
#include <QFile>
#include <pluginmanager.h>
#include <QResizeEvent>
#include <QDebug>

DarkBluePlayerWidget::DarkBluePlayerWidget(QWidget *parent) :
    IPlayerWidget(parent),
    ui(new Ui::DarkBluePlayerWidget),
    window(0),
    playerControl(0)
{
    ui->setupUi(this);
    loadStylesheet();

//    QMainWindow* window = qApp->findChildren<QMainWindow *>().at(0);
/*

*/
     connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));

}

DarkBluePlayerWidget::~DarkBluePlayerWidget()
{
    delete ui;
}

IPlayerWidget::PlayerWidgetPosition DarkBluePlayerWidget::getPreferedPosition()
{
    return IPlayerWidget::BOTTOM;
}

void DarkBluePlayerWidget::loadStylesheet()
{
    QFile file;

    file.setFileName(":stylesheet/DarkBluePlayerStylesheet.css");
    file.open(QFile::ReadOnly);

    QString styleSheet = QLatin1String( file.readAll() );
    file.close();

    this->setStyleSheet(styleSheet);
}

void DarkBluePlayerWidget::objectAddedToObjectPool(QObject * object)
{
    QMainWindow* mainWindow = qobject_cast<QMainWindow*>(object);
    if(mainWindow)
    {
      window = mainWindow->centralWidget();
      playerControl = new PlayerControl(window);
      window->installEventFilter(this);
      playerControl->move(window->width()/2-74, window->height()-93);
      playerControl->show();
    }
}

bool DarkBluePlayerWidget::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::Resize)
    {
            qDebug()<<"TEST";
            playerControl->move(window->width()/2-74, window->height()-88);
    }
    return false;
}


void DarkBluePlayerWidget::setVolumeEnabled(bool value)
{
    Q_UNUSED(value)
}

void DarkBluePlayerWidget::setSeekerEnabled(bool value)
{
    Q_UNUSED(value)
}
