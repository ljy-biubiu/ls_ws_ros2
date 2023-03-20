#ifndef WEBUI_H
#define WEBUI_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebChannel>
#include "qurl.h"
#include "jsQt_chat.h"

namespace Ui
{
    class WebUi;
}

class WebUi : public QWidget
{
    Q_OBJECT

public:
    explicit WebUi(QWidget *parent = nullptr);
    ~WebUi();

private:
    Ui::WebUi *ui;
    QWebEngineView *view;
    QWebChannel *channel;
    JsChatQt *js_chat_qt;
};

#endif // WEBUI_H
