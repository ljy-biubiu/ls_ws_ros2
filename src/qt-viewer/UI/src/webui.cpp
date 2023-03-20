#include "webui.h"
#include "ui_webui.h"

WebUi::WebUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebUi)
{
    ui->setupUi(this);
    js_chat_qt = new JsChatQt();




    this->ui->web_widget->page()->setWebChannel(js_chat_qt->getChanel());
    this->ui->web_widget->setUrl(QUrl("qrc:/web_ui/dynamic-data.html"));

    QDateTime curDateTime=QDateTime::currentDateTime();
    static QTimer* myTimer = new QTimer(this);

    connect(myTimer,&QTimer::timeout,[=](){
        //onBtnSend_clicked();

        QJsonObject json;
        json.insert("name","运华大厦");
        json.insert("time",curDateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QJsonDocument doc(json);
        QString json_str  = QString(doc.toJson(QJsonDocument::Indented));


        js_chat_qt->insertDataToWeb(std::string("pointcloud"),std::string("[]asdasd[]dasd][]dsad[]dasd"));
        js_chat_qt->insertDataToWeb("warm_datas",json_str.toStdString());
    });

    myTimer->start(3000);
    
}

WebUi::~WebUi()
{
    delete ui;
}
