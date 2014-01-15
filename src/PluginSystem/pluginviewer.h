#ifndef PLUGINVIEWER_H
#define PLUGINVIEWER_H

#include "PluginSystem_global.h"

#include <QWidget>
#include <QDialog>
#include <QList>
#include <pluginspec.h>

namespace Ui {
class PluginViewer;
}

namespace PluginSystem
{
    class PLUGINSYSTEMSHARED_EXPORT PluginViewer : public QDialog
    {
        Q_OBJECT

        public:
            explicit PluginViewer(QList<PluginSpec*> plugins, QHash<QString, bool> config, QWidget *parent = 0);
            ~PluginViewer();

    private slots:
        void on_btnClose_clicked();

        void on_btnDetails_clicked();

        void on_pushButton_clicked();

    private:
            Ui::PluginViewer *ui;
            QList<PluginSpec*> plugins;
            QHash<QString, bool> config;
    };
}

#endif // PLUGINVIEWER_H
