#include "addlidar.h"
#include "ui_addlidar.h"
#include "QMetaType"
#include <QIntValidator>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QRegExp>
#include <QDebug>

AddLidar::AddLidar(QWidget *parent) : QDialog(parent),
                                      ui(new Ui::AddLidar)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/leishen.ico"));
    setModal(true);
    // setFixedSize(size());
    this->setWindowFlags(Qt::FramelessWindowHint);
    // ui->widget->setParentWidget(this);
    // ui->widget->setTitleName(QStringLiteral("摄像头设置"));
    ui->comboBox->setEditable(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox->lineEdit()->setReadOnly(true);
    //    ShowData();
}

AddLidar::~AddLidar()
{
    delete ui;
}

void AddLidar::initcombox(QList<int> &items)
{
}
void AddLidar::ShowData(const QString &str)
{

    Json::Reader reader;
    Json::Value json_value;

    if (reader.parse(str.toStdString(), json_value))
    {

        ///////////////////////////////////////////////////////////////////////

        ui->XAngle->setText(QString("%1").arg(json_value["LidarPreset"]["XAngle"].asDouble()));
        ui->YAngle->setText(QString("%1").arg(json_value["LidarPreset"]["YAngle"].asDouble()));
        ui->ZAngle->setText(QString("%1").arg(json_value["LidarPreset"]["ZAngle"].asDouble()));

        ui->base_x->setText(QString("%1").arg(json_value["LidarPreset"]["Base_X"].asDouble()));
        ui->base_y->setText(QString("%1").arg(json_value["LidarPreset"]["Base_Y"].asDouble()));
        ui->base_z->setText(QString("%1").arg(json_value["LidarPreset"]["Base_Z"].asDouble()));

        ui->setradius->setText(QString("%1").arg(json_value["LidarPreset"]["paintarea_Radius"].asDouble()));

        ui->comboBox->setCurrentText(QString(json_value["LidarBase"]["LidarModel"].asInt()));
        ui->pos_x->setText(QString("%1").arg(json_value["LidarCameraBase"]["Pos_X"].asDouble()));
        ui->pos_y->setText(QString("%1").arg(json_value["LidarCameraBase"]["Pos_Y"].asDouble()));
        ui->pos_z->setText(QString("%1").arg(json_value["LidarCameraBase"]["Pos_Z"].asDouble()));
        ui->up_x->setText(QString("%1").arg(json_value["LidarCameraBase"]["Up_X"].asDouble()));
        ui->up_y->setText(QString("%1").arg(json_value["LidarCameraBase"]["Up_Y"].asDouble()));
        ui->up_z->setText(QString("%1").arg(json_value["LidarCameraBase"]["Up_Z"].asDouble()));
        ui->view_x->setText(QString("%1").arg(json_value["LidarCameraBase"]["View_X"].asDouble()));
        ui->view_y->setText(QString("%1").arg(json_value["LidarCameraBase"]["View_Y"].asDouble()));
        ui->view_z->setText(QString("%1").arg(json_value["LidarCameraBase"]["View_Z"].asDouble()));

        ui->lidarPort->setText(QString("%1").arg(json_value["LidarBase"]["lidarPort"].asDouble()));
        // ui->kValue->setText(QString("%1").arg(msg_.baseParams.lidarCluster.Kvalue));

        ui->dataAddress->setText(QString::fromStdString(json_value["LidarBase"]["DataAddress"].asString()));
        ui->lidarAddress->setText(QString::fromStdString(json_value["LidarBase"]["LidarAddress"].asString()));
        ui->serverIP->setText(QString::fromStdString(json_value["LidarBase"]["ServerAddress"].asString()));
        ui->serverPort->setText(QString("%1").arg(json_value["LidarBase"]["ServerPort"].asDouble()));

        ui->camera_ip->setText(QString::fromStdString(json_value["CameraBase"]["ip"].asString()));
        ui->camera_name->setText(QString::fromStdString(json_value["CameraBase"]["name"].asString()));
        ui->camera_key->setText(QString::fromStdString(json_value["CameraBase"]["code"].asString()));
        ui->lower_machine_ip->setText(QString::fromStdString(json_value["LowerMachineBase"]["ip"].asString()));
        ui->lower_machine_port->setText(QString("%1").arg(json_value["LowerMachineBase"]["port"].asInt()));

        ui->gound_grid_X->setText(QString("%1").arg(json_value["GroundParamIn"]["gridNumX"].asDouble()));
        ui->gound_grid_Y->setText(QString("%1").arg(json_value["GroundParamIn"]["gridNumY"].asDouble()));
        ui->gound_max_angle->setText(QString("%1").arg(json_value["GroundParamIn"]["max_monitor_angle"].asDouble()));
        ui->gound_min_angle->setText(QString("%1").arg(json_value["GroundParamIn"]["min_monitor_angle"].asDouble()));

        ui->ship_grid_X->setText(QString("%1").arg(json_value["ShipParamIn"]["gridNumX"].asDouble()));
        ui->ship_grid_Y->setText(QString("%1").arg(json_value["ShipParamIn"]["gridNumY"].asDouble()));
        ui->ship_max_angle->setText(QString("%1").arg(json_value["ShipParamIn"]["max_monitor_angle"].asDouble()));
        ui->ship_min_angle->setText(QString("%1").arg(json_value["ShipParamIn"]["min_monitor_angle"].asDouble()));
        ui->ship_bound_radius->setText(QString("%1").arg(json_value["ShipParamIn"]["boundRadius"].asDouble()));
        ui->ship_normal_radius->setText(QString("%1").arg(json_value["ShipParamIn"]["normalRadius"].asDouble()));
    }
}

void AddLidar::on_btn_sure_clicked()
{

    // 根节点
    Json::Value root;
    // 子节点
    Json::Value ComunicationData;
    // 子节点挂到根节点上
    root["ComunicationData"] = Json::Value(ComunicationData);

    // 子节点
    Json::Value LidarPreset;
    // 子节点属性
    LidarPreset["paintarea_Radius"] = Json::Value(ui->setradius->text().toFloat());
    LidarPreset["XAngle"] = Json::Value(ui->XAngle->text().toFloat());
    LidarPreset["YAngle"] = Json::Value(ui->YAngle->text().toFloat());
    LidarPreset["ZAngle"] = Json::Value(ui->ZAngle->text().toFloat());
    LidarPreset["Base_X"] = Json::Value(ui->base_x->text().toFloat());
    LidarPreset["Base_Y"] = Json::Value(ui->base_y->text().toFloat());
    LidarPreset["Base_Z"] = Json::Value(ui->base_z->text().toFloat());
    // 子节点挂到根节点上
    root["LidarPreset"] = Json::Value(LidarPreset);

    // 子节点
    Json::Value LidarBase;
    // 子节点属性
    LidarBase["lidarPort"] = Json::Value(ui->lidarPort->text().toInt());
    LidarBase["LidarAddress"] = Json::Value(ui->lidarAddress->text().toStdString());
    LidarBase["ServerPort"] = Json::Value(ui->serverPort->text().toInt());
    LidarBase["ServerAddress"] = Json::Value(ui->serverIP->text().toStdString());
    LidarBase["DataAddress"] = Json::Value(ui->dataAddress->text().toStdString());
    LidarBase["DeviceId"] = Json::Value(0);
    LidarBase["LidarModel"] = Json::Value(0);
    // 子节点挂到根节点上
    root["LidarBase"] = Json::Value(LidarBase);

    // 子节点
    Json::Value LidarCameraBase;
    // 子节点属性
    LidarCameraBase["Pos_X"] = Json::Value(ui->pos_x->text().toFloat());
    LidarCameraBase["Pos_Y"] = Json::Value(ui->pos_y->text().toFloat());
    LidarCameraBase["Pos_Z"] = Json::Value(ui->pos_z->text().toFloat());
    LidarCameraBase["View_X"] = Json::Value(ui->view_x->text().toFloat());
    LidarCameraBase["View_Y"] = Json::Value(ui->view_y->text().toFloat());
    LidarCameraBase["View_Z"] = Json::Value(ui->view_z->text().toFloat());
    LidarCameraBase["Up_X"] = Json::Value(ui->up_x->text().toFloat());
    LidarCameraBase["Up_Y"] = Json::Value(ui->up_y->text().toFloat());
    LidarCameraBase["Up_Z"] = Json::Value(ui->up_z->text().toFloat());
    // 子节点挂到根节点上
    root["LidarCameraBase"] = Json::Value(LidarCameraBase);

    // 子节点
    Json::Value CameraBase;
    // 子节点属性
    CameraBase["ip"] = Json::Value(ui->camera_ip->text().toStdString());
    CameraBase["code"] = Json::Value(ui->camera_key->text().toStdString());
    CameraBase["name"] = Json::Value(ui->camera_name->text().toStdString());
    // 子节点挂到根节点上
    root["CameraBase"] = Json::Value(CameraBase);

    // 子节点
    Json::Value LowerMachineBase;
    // 子节点属性
    LowerMachineBase["ip"] = Json::Value(ui->lower_machine_ip->text().toStdString());
    LowerMachineBase["port"] = Json::Value(ui->lower_machine_port->text().toInt());
    // 子节点挂到根节点上
    root["LowerMachineBase"] = Json::Value(LowerMachineBase);

    // 子节点
    Json::Value GroundParamIn;
    // 子节点属性
    GroundParamIn["gridNumX"] = Json::Value(ui->gound_grid_X->text().toFloat());
    GroundParamIn["gridNumY"] = Json::Value(ui->gound_grid_Y->text().toFloat());
    GroundParamIn["max_monitor_angle"] = Json::Value(ui->gound_max_angle->text().toDouble());
    GroundParamIn["min_monitor_angle"] = Json::Value(ui->gound_min_angle->text().toDouble());
    // 子节点挂到根节点上
    root["GroundParamIn"] = Json::Value(GroundParamIn);

    // 子节点
    Json::Value ShipParamIn;
    // 子节点属性
    ShipParamIn["gridNumX"] = Json::Value(ui->ship_grid_X->text().toFloat());
    ShipParamIn["gridNumY"] = Json::Value(ui->ship_grid_Y->text().toFloat());
    ShipParamIn["max_monitor_angle"] = Json::Value(ui->ship_max_angle->text().toDouble());
    ShipParamIn["min_monitor_angle"] = Json::Value(ui->ship_min_angle->text().toDouble());
    ShipParamIn["boundRadius"] = Json::Value(ui->ship_bound_radius->text().toFloat());
    ShipParamIn["normalRadius"] = Json::Value(ui->ship_normal_radius->text().toFloat());
    // 子节点挂到根节点上
    root["ShipParamIn"] = Json::Value(ShipParamIn);

    Json::FastWriter writer;
    auto str = writer.write(root);

    emit SendSet(QString::fromStdString(str));
    this->close();
}

void AddLidar::on_btn_no_clicked()
{
    this->close();
}
