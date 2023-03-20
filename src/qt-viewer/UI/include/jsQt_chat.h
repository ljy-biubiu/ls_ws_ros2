#ifndef JsChatQt_H
#define JsChatQt_H

#include <QObject>
#include <QJsonObject>
#include "qjsondocument.h"
#include <qtimer.h>
#include <map>

#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebChannel>

class JsChatQt : public QObject
{
    Q_OBJECT
public:
    explicit JsChatQt(QObject *parent = nullptr);

public:
    void insertDataToWeb(const std::string &name,const std::string &data);
    void insertDataToWeb(const QString &name,const QString &data);
    QWebChannel* getChanel();

signals:
    void receiveTextFromWeb(const QString &test);       // JS给QT发送数据
    void signalToWeb(const QJsonObject &json);          // QT给JS发送数据

public slots:
    void sendTextToQT(const QString &test);

private:
    // 发送json数据给html
    void sendJsonToWeb(const QJsonObject _obj);
    void initTimer();
    const QJsonObject packMapToJson();
    std::map<std::string,std::string> my_map;

    QJsonObject obj;
    QTimer* myTimer =NULL;
    QWebEngineView* view;
    QWebChannel* channel;

signals:

};

#endif // JsChatQt_H
