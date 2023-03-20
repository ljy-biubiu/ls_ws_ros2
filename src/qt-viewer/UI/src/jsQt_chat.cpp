#include "jsQt_chat.h"
#include "qdebug.h"

JsChatQt::JsChatQt(QObject *parent) : QObject(parent)
{
    //    myTimer = new QTimer(this);
    //    myTimer->start(100);
    initTimer();
    channel = new QWebChannel(this);
    // 向web客户端注册对象，使得web客户端可以通过该对象调用QT的槽函数
    // 参数一：web端使用的标识(可以乱写，但必须与web中对应)    参数二：传送过去的QT对象
    channel->registerObject(QString::fromLocal8Bit("doc"), this);
}


//每100ms发1次信息到web
void JsChatQt::initTimer()
{
    myTimer = new QTimer(this);
    myTimer->start(100);
    connect(myTimer,&QTimer::timeout,[=](){
        QJsonObject data = packMapToJson();
        if(!data.isEmpty())
        {
            this->sendJsonToWeb(data);
        }
    });
}

QWebChannel* JsChatQt::getChanel()
{
    return this->channel;
}

void JsChatQt::insertDataToWeb(const QString &msg_name,const QString &msg_data)
{
    std::string name = msg_name.toStdString();
    std::string data = msg_data.toStdString();
    my_map.insert(std::pair<std::string, std::string>(name, data));

    //    my_map.push(data);
}

void JsChatQt::insertDataToWeb(const std::string &name,const std::string &data)
{
    my_map.insert(std::pair<std::string, std::string>(name, data));
}

const QJsonObject JsChatQt::packMapToJson()
{
    // 定义json
    QJsonObject json;

    std::map<std::string, std::string>::iterator iter;
    iter = my_map.begin();

    while (iter != my_map.end())
    {
        json.insert(iter->first.c_str(), iter->second.c_str());
        iter++;
    }
    my_map.clear();
    return json;
}


// 给JS发送Json数据
void JsChatQt::sendJsonToWeb(const QJsonObject _obj)
{
    // 临时存储当前主程序发送给JS的数据，这里我还定义了一个函数用于返回obj的，只是没有写出来！
    if (this->obj != _obj) {
        obj = _obj;
    }

    // 通过信号带参的的形式进行发送
    emit signalToWeb(_obj);		// 这个是QT发送给JS
}

// JS调用此函数传参，带数据给QT
void JsChatQt::sendTextToQT(const QString &test)
{
    // 发射信号，将数据传给主窗体
    emit receiveTextFromWeb(test);		// 这个是JS发送给QT
}
