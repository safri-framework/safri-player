#ifndef SAFRIAPPINSTANCE_H
#define SAFRIAPPINSTANCE_H

#include <QObject>

// forward declarations
class IAppController;
class ViewController;


/**
 * @brief   This class is the actual instance of the SafriApp.
 *
 *          It is responsible to create the view and the right AppController,
 *          and manages the switching between the local/REST AppController.
 */
class SafriAppInstance : public QObject
{
    Q_OBJECT
    public:

        explicit SafriAppInstance(QObject *parent = 0);

    signals:

        /**
         * @brief this signal is emitted, when we switched between local and REST AppController
         * @param the new appController
         */
        void appControllerChanged(IAppController* appController);

    private slots:
    
        void connectTo(QString host, int port);
        void disconnect();

    private:

        IAppController*             appController;
        ViewController*             viewController;
        bool                        isRESTClient;


};

#endif // SAFRIAPPINSTANCE_H
