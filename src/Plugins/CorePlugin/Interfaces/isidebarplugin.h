#ifndef ISIDEBARPLUGIN_H
#define ISIDEBARPLUGIN_H

#include "../CorePlugin_global.h"
#include <QObject>
#include <QString>

class QWidget;

namespace Core
{
    class COREPLUGINSHARED_EXPORT ISideBarPlugin : public QObject
    {
        Q_OBJECT
        public:

            virtual ~ISideBarPlugin();

            virtual QWidget* getSideBarWidget() = 0;
            virtual QString getName() = 0;
            virtual QWidget* getMenuBarWidget() = 0;
            virtual bool isVisible() = 0;

        signals:

            void show(bool show);
    };
}

#endif // ISIDEBARPLUGIN_H
