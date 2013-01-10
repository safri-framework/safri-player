#include "pluginviewer.h"
#include "ui_pluginviewer.h"
#include "pluginviewermodel.h"
#include "pluginspecviewer.h"

#include <QDebug>

using namespace PluginSystem;

PluginViewer::PluginViewer(QList<PluginSystem::PluginSpec *> plugins, QWidget *parent) :
    QDialog(parent), ui(new Ui::PluginViewer), plugins(plugins)
{
    ui->setupUi(this);

    PluginviewerModel* model = new PluginviewerModel(plugins, this);
    ui->pluginTableView->setModel(model);
}

PluginViewer::~PluginViewer()
{
    delete ui;
}


void PluginSystem::PluginViewer::on_btnClose_clicked()
{
    this->close();
}

void PluginSystem::PluginViewer::on_btnDetails_clicked()
{
    int index = ui->pluginTableView->currentIndex().row();
    PluginSpec* pluginSpec = plugins.at(index);

    PluginSpecViewer *viewer = new PluginSpecViewer(pluginSpec, this);
    viewer->show();
}
