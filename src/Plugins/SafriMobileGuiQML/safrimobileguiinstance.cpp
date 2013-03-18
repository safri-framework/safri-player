#include "safrimobileguiinstance.h"
#include <QDebug>
#include <QDeclarativeView>
#include <QDeclarativeItem>

SafriMobileGuiInstance::SafriMobileGuiInstance()
{

    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl("qrc:/test/qml/main.qml"));
    view->show();

}
