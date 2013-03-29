#ifndef PLSOPENER_H
#define PLSOPENER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class PlsOpener : public QObject
{
    Q_OBJECT
public:
    explicit PlsOpener(QObject *parent = 0);
    void test();
    void playPlsFromWebUrl(QUrl url);
signals:
    
private slots:
    void requestFinished(QNetworkReply* reply);

public slots:
private:
    QNetworkAccessManager*  networkManager;
    void playPlsFile(QString pls);
};

#endif // PLSOPENER_H
