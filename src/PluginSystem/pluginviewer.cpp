#include "pluginviewer.h"
#include "ui_pluginviewer.h"
#include "pluginviewermodel.h"
#include "pluginspecviewer.h"

#include <QDebug>
#include <QProcess>

using namespace PluginSystem;

PluginViewer::PluginViewer(QList<PluginSystem::PluginSpec *> plugins,QHash<QString, bool> config, QWidget *parent) :
    QDialog(parent), ui(new Ui::PluginViewer), plugins(plugins),config(config)
{
    ui->setupUi(this);

    PluginviewerModel* model = new PluginviewerModel(plugins, config, this);
    ui->pluginTableView->setModel(model);
    ui->pluginTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void PluginSystem::PluginViewer::on_pushButton_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
