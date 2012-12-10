#ifndef PLUGINSPECVIEWER_H
#define PLUGINSPECVIEWER_H

#include <QDialog>

namespace Ui {
class PluginSpecViewer;
}

namespace PluginSystem
{
    class PluginSpec;
    class PluginSpecViewer : public QDialog
    {
        Q_OBJECT
        public:
            explicit PluginSpecViewer(PluginSpec* pluginSpec, QWidget *parent = 0);
            ~PluginSpecViewer();

        private:
            Ui::PluginSpecViewer *ui;
            PluginSpec *pluginSpec;
    };
}
#endif // PLUGINSPECVIEWER_H
