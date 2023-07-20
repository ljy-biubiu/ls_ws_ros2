#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include "LED_RS232_API.h"

using namespace std;
#define TEST_FUN 1
#define DBUG_MODE 0
#define CHECK_MAX_NUM 5
#define Music_Time 9

int tty_fd = 0;
int play_state = 0;
int play_contrl = 0;
int commanded_state = 0;
int connect_state = 0;
pthread_t test_thread_id;
pthread_t RS232_ReceiveDataProcessthread_id;
pthread_t alarm_thread_id;
unsigned char buff[16];                               // 存放数据或者命令
unsigned char CheckCmd[4] = {0xAA, 0x01, 0x00, 0xAB}; // 查询播放状态
unsigned char PlayCmd[4] = {0xAA, 0x02, 0x00, 0xAC};  // 触发报警命令
unsigned char StopCmd[4] = {0xAA, 0x03, 0x00, 0xAD};  // 停止报警命令

const int DELAY_CNT = 50;

void alarm_led_callback(const std_msgs::msg::Int8::SharedPtr msg)
{
    if (msg->data != 0)
    {
        LEDContrlAPI(1);
        delay_cnt = DELAY_CNT;
        delay_flag = true;
    }
    else if (msg->data == 0 && delay_flag == false)
    {
        LEDContrlAPI(0);
    }
}

void timerCallback()
{
    if (delay_cnt--, delay_cnt == 0)
        delay_flag = false;
}

int main(int argc, char **argv)
{

    /*.创建报警灯服务*/
    if (pthread_create(&alarm_thread_id, NULL, StartAlarmLight, (void *)&tty_fd) == 0) // 创建线程
    {
        pthread_detach(alarm_thread_id); // 设置分离属性，让线程结束之后自己释放资源
    }
    else
    {
        cout << "alarm_thread_id thread create failed !" << endl;
    }

    //************************************ros****************************************//
    setvbuf(stdout, nullptr, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
    node = rclcpp::Node::make_shared("alarm_led_node");
    RCLCPP_INFO(node->get_logger(), " alarm_led_node initialized ");

    std::string device_ip_;
    int device_port_;
    node->declare_parameter<std::string>("device_ip", "10.60.28.241");
    node->get_parameter("device_ip", device_ip_);

    node->declare_parameter<int>("device_port", 50000);
    node->get_parameter("device_port", device_port_);

    timer_ =
        node->create_wall_timer(100ms, timerCallback);

    // std::cout << device_port_ << std::endl;
    // std::cout << device_ip_ << std::endl;

    // auto parameter_server_pub_ =
    //     node->create_publisher<std_msgs::msg::String>("/params_config/parameter_server", rclcpp::QoS{1}.transient_local());

    // auto parameter_server_sub = node->create_subscription<std_msgs::msg::String>(
    //     "/params_config/parameter_server",
    //     rclcpp::QoS{1}.transient_local(),
    //     [node](const std_msgs::msg::String::SharedPtr msg)
    //     { parameterServerCallback(msg); });

    auto alarm_control_sub = node->create_subscription<std_msgs::msg::Int8>(
        "/alarm_led/led_control",
        rclcpp::QoS{1},
        [node](const std_msgs::msg::Int8::SharedPtr msg)
        { alarm_led_callback(msg); });

    rclcpp::spin(node);
    rclcpp::shutdown();
    //************************************ros****************************************//
}

int openSerialPort(int serialBaudRate, const char *deviceAddr)
{
    struct termios options;
    int ret = -1;
    cout << "serialBaudRate =" << serialBaudRate << endl;
    switch (serialBaudRate)
    {
    case 600:
        serialBaudRate = B600;
        break;
    case 1200:
        serialBaudRate = B1200;
        break;
    case 2400:
        serialBaudRate = B2400;
        break;
    case 4800:
        serialBaudRate = B4800;
        break;
    case 9600:
        serialBaudRate = B9600;
        break;
    case 19200:
        serialBaudRate = B19200;
        break;
    case 38400:
        serialBaudRate = B38400;
        break;
    case 57600:
        serialBaudRate = B57600;
        break;
    case 115200:
        serialBaudRate = B115200;
        break;
    case 230400:
        serialBaudRate = B230400;
        break;
    case 460800:
        serialBaudRate = B460800;
        break;
    case 576000:
        serialBaudRate = B576000;
        break;
    case 921600:
        serialBaudRate = B921600;
        break;
    default:
        serialBaudRate = B9600;
        break;
    }
    tty_fd = open(deviceAddr, O_RDWR | O_NOCTTY | O_NDELAY); // 打开串口设备
    if (tty_fd < 0)
    {
        cout << "open " << deviceAddr << " failed !!!" << endl;
        close(tty_fd);
        return -1;
    }
    else
    {
        cout << "open " << deviceAddr << " sucessful ! " << endl;
    }
    if (fcntl(tty_fd, F_SETFL, 0) < 0) /*清除串口非阻塞标志*/
    {
        cout << "fcntl failed!" << endl;
        close(tty_fd);
        return -1;
    }

    memset(&options, 0, sizeof(options));
    ret = tcgetattr(tty_fd, &options); // 获取原有的串口属性的配置
    if (ret != 0)
    {
        cout << "tcgetattr() failed:" << deviceAddr << endl;
        close(tty_fd);
        return -1;
    }
    cfsetispeed(&options, serialBaudRate);
    cfsetospeed(&options, serialBaudRate);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;
    options.c_cc[VTIME] = 1;                         /* 非规范模式读取时的超时时间，单位0.1s；*/
    options.c_cc[VMIN] = 1;                          /* 非规范模式读取时的最小字符数*/
    tcflush(tty_fd, TCIFLUSH);                       /* tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */
    if ((tcsetattr(tty_fd, TCSANOW, &options)) != 0) /*激活配置*/
    {
        cout << "tcsetattr( )  failed" << endl;
        close(tty_fd);
        return -1;
    }
    return 0;
}

int RS232_SendBytes(int fd, void *sendbuf, int count)
{
    int ret = -1;
    ret = write(fd, sendbuf, count); // 发送查询报警灯播放状态命令
    if (ret < 0)
    {
        cout << "\nwrite() error:" << strerror(errno) << endl;
        close(fd);
        return -1;
    }
    else
        return ret;
}

int RS232_ReceiveBytes(int fd, void *revbuf, int count)
{
    int ret = -1;
    ret = read(fd, revbuf, count); // 发送查询报警灯播放状态命令
    if (ret < 0)
    {
        cout << "read() error:" << strerror(errno) << endl;
        close(fd);
        return -1;
    }
    else
        return ret;
}

/*
函数功能: 串口数据接收处理
*/
void *RS232_ReceiveDataProcess(void *)
{
    cout << "RS232_ReceiveDataProcess thread create Success !" << endl;
    int Receive_rv = -1;
    fd_set rset;
    int i;
    int Cmd_len = 0;
    while (1)
    {
        memset(buff, 0, sizeof(buff));
        Cmd_len = 0;
        FD_ZERO(&rset);
        FD_SET(tty_fd, &rset);
        Receive_rv = select(tty_fd + 1, &rset, NULL, NULL, NULL);
        if (Receive_rv < 0)
        {
            cout << "select( ) failed !!!" << endl;
            close(tty_fd);
        }
        if (Receive_rv == 0)
        {
            cout << "select( ) time out !!!" << endl;
            close(tty_fd);
        }
        do
        {
            Receive_rv = RS232_ReceiveBytes(tty_fd, buff + Cmd_len, sizeof(buff) - Cmd_len);
            Cmd_len += Receive_rv;
            // cout<<"\n***Receive_num="<<Receive_rv<<"  Cmd_len="<< Cmd_len;
        } while (Cmd_len < 5); // 需要等待的字节数为5个

#if DBUG_MODE
        cout << "\nReceive_num=" << Receive_rv << "  Cmd_len=" << Cmd_len;
#endif
        if (Cmd_len == 5) // 判断是否是报警灯的回应数据
        {
            if ((CheckDataPackage(buff, Cmd_len) == 0) /*校验数据包是否正确*/)
            {
                if (buff[0] == 0xAA && buff[1] == 0x01 && buff[2] == 0x01) // 更报警灯新标志位
                {
                    connect_state = 1;
                    if (buff[3] == 0x00) // 报警器不在播放
                    {
                        play_state = 0;
                        commanded_state = 0;
                    }
                    else if (buff[3] == 0x01) // 报警器在播放
                    {
                        play_state = 1;
                        commanded_state = 1; // 表示已经进入过报警控制过
                    }
                    else
                    {
                        play_state = 0;
                    }
                }
#if DBUG_MODE
                printf(" Data：%X %X %X %X %X  PlayState = %d \n", buff[0], buff[1], buff[2], buff[3], buff[4], play_state);
#endif
            }
            else
            {
                cout << "Data Package CRC Error !!!" << endl;
            }
        }
        else if (Receive_rv < 0 || Receive_rv == 0)
        {
            connect_state = 0;
            cout << "The serial device file does not exist !" << endl;
            close(tty_fd);
        }
        else
        {
            cout << " Data Package Size Error!!!" << endl;
        }
        Cmd_len = 0;
    }
}

/*
 报警灯API服务函数,监控报警灯API改变的报警标志位，并根据标志位控制报警灯

*/
int ledAlarmControlfun()
{
    int i = 0;
    int ret = -1;
    static int noACK, noACK1;
    while (1)
    {
        usleep(10 * 1000);
        if (play_contrl == true)
        {
            commanded_state = true;              // 表示已经进入过报警控制过
            while (play_state && i < Music_Time) // 在报警
            {
                if (play_contrl == 0) // 突然又要关闭报警灯
                {
                    cout << "\nSTOP_PALY !" << endl;
                    goto STOP_PALY;
                }
                else
                {
                    ret = RS232_SendBytes(tty_fd, CheckCmd, 4); // 发送查询报警灯播放状态命令
                    if (ret > 0)
                    {
#if DBUG_MODE
                        cout << "CheckCmd send sucessful"
                             << "(num=" << i << ")" << endl;
#endif
                    }
                    else
                    {
                        cout << "CheckCmd send failed !!!"
                             << "(num=" << i << ")" << endl;
                    }
                    usleep(1000 * 1000);
                    i++;
                }
            }
            i = 0;
            play_state = false;
            while (play_state == false && i < CHECK_MAX_NUM) // 不在报警
            {
                RS232_SendBytes(tty_fd, PlayCmd, 4); // 发送报警命令
                usleep(200 * 1000);
                RS232_SendBytes(tty_fd, CheckCmd, 4); // 发送查询命令
                usleep(100 * 1000);
                i++;
                if (i == CHECK_MAX_NUM)
                {
                    cout << "Device NO ACK !!! "
                         << "(noACK_NUM=" << noACK << ")" << endl;
                    noACK++;
                }
            }
            if (i < CHECK_MAX_NUM)
            {
#if DBUG_MODE
                cout << "Device Alarm Success ! (Check_num=" << i << ")" << endl;
#endif
            }
            i = 0;
        }
        else // 停止报警
        {
        STOP_PALY:
            i = 0;
            while (play_state && i < CHECK_MAX_NUM) // 一直发送停止报警灯播放命令，直到报警器超时或者停止报警
            {
                RS232_SendBytes(tty_fd, StopCmd, 4);
                usleep(200 * 1000);
                RS232_SendBytes(tty_fd, CheckCmd, 4); // 发送查询命令
                i++;
            }
            if (commanded_state) // 上一次报警过
            {
                if (i < CHECK_MAX_NUM)
                {
#if DBUG_MODE
                    cout << "Device Stop Alarm Success ! (Check_num=" << i << ")" << endl;
#endif
                    commanded_state = 0;
                    play_state = 0;
                }
                if (i == CHECK_MAX_NUM)
                {
                    cout << "Device Stop Alarm No ACK !!! (noACK_NUM=" << noACK1 << ")" << endl;
                    noACK1++;
                }
            }
            i = 0;
        }
    }
}

/*
函数功能: 校验数据包是否正确
*/
int CheckDataPackage(unsigned char *data_buff, unsigned int rx_size)
{
    unsigned int checksum = 0;
    int i;
    if (rx_size > 8 || rx_size < 4)
    {
#if DBUG_MODE
        cout << "报警灯命令回应错误! " << endl;
#endif
        return -1;
    }
    for (i = 0; i < rx_size - 1; i++)
    {
        checksum += data_buff[i];
    }
    if (checksum != data_buff[rx_size - 1])
    {
#if DBUG_MODE
        cout << "校验和错误! " << endl;
#endif
        return -1;
    }
    return 0;
}

/*
函数功能: 测试报警灯
*/
void *test_fun(void *dev)
{
    int Chose_state = 0;
    cout << "test_fun thread create success !" << endl;
    while (1)
    {
        printf("请选择报警状态 0=关  1=开 ：");
        scanf("%d", &Chose_state);
        LEDContrlAPI(Chose_state);
    }
}

/*
函数功能: 报警灯控制API
*/
int LEDContrlAPI(int AlarmState)
{
#if DBUG_MODE
    cout << "Call LEDContrlAPI  Success ! (AlarmState = " << AlarmState << ")" << endl;
#endif
    play_contrl = AlarmState;
    return 0;
}

/*
函数功能: 报警灯控制主程序
*/
void *StartAlarmLight(void *)
{
    int ret = -1;
    int i = 0;
    /*1.打开串口*/
    openSerialPort(9600, "/dev/ttyUSB0");
    /*2.创建串口数据接收处理线程*/
    if (pthread_create(&RS232_ReceiveDataProcessthread_id, NULL, RS232_ReceiveDataProcess, (void *)&tty_fd) == 0) // 创建线程
    {
        pthread_detach(RS232_ReceiveDataProcessthread_id); // 设置分离属性，让线程结束之后自己释放资源
    }
    else
    {
        cout << "RS232_ReceiveDataProcess thread create failed !" << endl;
    }
    /*3.创建报警灯测试线程*/
#if TEST_FUN
    if (pthread_create(&test_thread_id, NULL, test_fun, (void *)&tty_fd) == 0) // 创建线程
    {
        pthread_detach(test_thread_id); // 设置分离属性，让线程结束之后自己释放资源
    }
    else
    {
        cout << "test_fun thread create failed !" << endl;
    }
#endif
    /*4.调用报警灯API服务函数*/
    ledAlarmControlfun();
    close(tty_fd);

    // return 0;
}
