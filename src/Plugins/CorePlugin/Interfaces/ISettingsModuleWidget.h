#ifndef ISETTINGSMODULEWIDGET_H
#define ISETTINGSMODULEWIDGET_H

#include <QWidget>
#include <QIcon>
#include "CorePlugin_global.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT ISettingsModuleWidget : public QWidget
    {
        Q_OBJECT
        public:

            explicit            ISettingsModuleWidget(QWidget *parent = 0);
            virtual QString     getTitle() = 0;
            virtual QIcon       getIcon() = 0;

        public slots:

            virtual void transferSettings() = 0;
            virtual bool isModified() = 0;
    };
}

#endif // ISETTINGSMODULEWIDGET_H
