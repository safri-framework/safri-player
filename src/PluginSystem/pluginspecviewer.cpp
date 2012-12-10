#include "pluginspecviewer.h"
#include "ui_pluginspecviewer.h"
#include "pluginspec.h"

using namespace PluginSystem;

PluginSpecViewer::PluginSpecViewer(PluginSpec* pluginSpec, QWidget *parent) :
    QDialog(parent), ui(new Ui::PluginSpecViewer), pluginSpec(pluginSpec)
{
    ui->setupUi(this);
    this->setWindowTitle("Plugin " + pluginSpec->getName());
    ui->lblName->setText(pluginSpec->getName());
    ui->lblVersion->setText(pluginSpec->getVersion());
    ui->lblVendor->setText(pluginSpec->getVendor());
    ui->lblURL->setText(pluginSpec->getUrl());
    ui->txtDescription->setText(pluginSpec->getDescription());

}

PluginSpecViewer::~PluginSpecViewer()
{
    delete ui;
}
