#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include "relay16.h"

/*
电气连接：接常开端子
网路继电器
ip   地址:192.168.2.6
WEB用户名：123456
WEB密  码：123456
*/

#define DBUG_MODE 0
#define TESTFUN 1
#define CHECK_MAX_NUM 5
#define RING_TIME 5

//--------------------------------------
using std::placeholders::_1;
using namespace std::chrono_literals;
//-----------------------------------------

int anyGpioControl(unsigned char pin, bool pinState ,bool clear_state);
int sendCmdToRelay(const unsigned char *buff);
unsigned char sendbuff[10]={0};

int main(int argc, char **argv)
{

	//*******************************init*********************************//
	for (int i = 0; i < 16; i++)
	{
		electric_relay_flags.push_back(0);
	}

	//*******************************创建继电器工作线程*********************************//
	if (pthread_create(&main_thread_id, 0, dowork, (void *)&tcp_client_data) != 0) // 1.
	{
		std::cout << "Error creating electric_relay" << std::endl;
	}
	//************************************ros****************************************//
	setvbuf(stdout, nullptr, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	node = rclcpp::Node::make_shared("electric_relay_node");
	RCLCPP_INFO(node->get_logger(), " electric_relay_node initialized ");

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

	auto parameter_server_pub_ =
		node->create_publisher<std_msgs::msg::String>("/params_config/parameter_server", rclcpp::QoS{1}.transient_local());

	auto parameter_server_sub = node->create_subscription<std_msgs::msg::String>(
		"/params_config/parameter_server",
		rclcpp::QoS{1}.transient_local(),
		[node](const std_msgs::msg::String::SharedPtr msg)
		{ parameterServerCallback(msg); });

	auto electric_relay_control_sub = node->create_subscription<std_msgs::msg::Int8MultiArray>(
		"/electric_relay/electric_relay_control",
		rclcpp::QoS{1},
		[node](const std_msgs::msg::Int8MultiArray::SharedPtr msg)
		{ electric_relay_callback(msg); });

	rclcpp::spin(node);
	rclcpp::shutdown();
	//************************************ros****************************************//

	return 0;
}

void parameterServerCallback(const std_msgs::msg::String::SharedPtr msg)
{
}

void timerCallback()
{
	for (int i = 0; i < electric_relay_flags.size(); i++)
	{
		if (electric_relay_flags[i] != 0)
		{
			electric_relay_flags[i] = electric_relay_flags[i] + 1;
		}

		if (electric_relay_flags[i] > RING_TIME * 10)
		{
			electric_relay_flags[i] = 0;
		}
	}
}

void electric_relay_callback(const std_msgs::msg::Int8MultiArray::SharedPtr msg)
{
	std::cout << "----------" << std::endl;

	int rak{0};
	int control_result{0};
	std_msgs::msg::Int8MultiArray msg_change;
	for(int i{0} ; 16>i ; i++)
	{
		msg_change.data.push_back(0);
	}
	


	for (auto cmd : msg->data)
	{
		// usleep(5 * 1000);
		if (cmd == 1) // 报警
		{
			electric_relay_flags[rak] = 1; // 设置为1，开始计时，直至将该值置为0
		}

		if (electric_relay_flags[rak] != 0)
		{
			//control_result = control_result + securityRelayAlarmSingnalAPI(rak, 1);
			msg_change.data[rak] = 1;
		}
		else
		{
			//control_result = control_result + securityRelayAlarmSingnalAPI(rak, cmd);
			msg_change.data[rak] = 0;
		}
		rak++;
	}
	
	
	//short int control_alarm_sum{0};
	
	//for(auto dat : msg_change.data)
	//{
	//	control_alarm_sum = control_alarm_sum | dat;
	//	control_alarm_sum<<1;
	//}
	
	
	
	anyGpioControl( 1 , msg_change.data[0] ,1);
	std::cout<<"the 1 lidar is "<< msg_change.data[0]<<std::endl;
	for(int i{2};i<=msg_change.data.size();i++)
	{
		anyGpioControl(i, msg_change.data[i-1] ,0);
		std::cout<<"the "<<std::to_string(i) << " lidar is "<< std::to_string(msg_change.data[i-1])<<std::endl;
	}
	sendCmdToRelay(sendbuff);
	
	

	if (control_result != 0)
	{
		//RCLCPP_ERROR_STREAM(node->get_logger(), "control_result vuale :" + std::to_string(control_result) + ", control electric_relay fail!!!!");
	}
	std::cout << "----------2222" << std::endl;
}

void *dowork(void *)
{
	// int tcp_server_port;  //服务器的端口号
	int tcp_server_fd;		// 服务器套接字描述符
	int *tcp_client_fd = 0; // 客户端套接字描述符(定义为指针是为了后面好创建客户端信息链表)
	int Contrl_thread_state = 0;
	int ret = 0;
	int reuse = 1;
	struct sockaddr_in tcp_server; // 地址结构体

	/*此处调用设置IP和端口的API*/
	SetTcpServerConfigAPI("10.60.28.240", 8234);

	/*1. 创建网络套接字*/
	tcp_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_server_fd < 0)
	{
		printf("TCP服务器端套接字创建失败!\n");
		exit(1);
	}
	if (setsockopt(tcp_server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) // 给套接字应用SO_REUSEADDR套接字选项,以便端口可以马上重用
	{
		perror("setsockopt failed");
		exit(1);
	}
	/*2. 绑定端口号,创建红绿灯控制器TCP服务器*/
	tcp_server.sin_family = AF_INET;			 // IPV4协议类型
	tcp_server.sin_port = htons(TCP_ServerPort); // 端口号赋值,将本地字节序转为网络字节序
	// tcp_server.sin_addr.s_addr=INADDR_ANY; //将本地IP地址赋值给结构体成员
	tcp_server.sin_addr.s_addr = inet_addr(TCP_ServerIP);

	if (bind(tcp_server_fd, (const struct sockaddr *)&tcp_server, sizeof(struct sockaddr)) < 0)
	{
		printf("TCP服务器端口绑定失败!\n");
		// exit(1);
		void *pv = nullptr;
		return pv;
	}
	/*3. 设置监听的客户端数量*/
	listen(tcp_server_fd, 100);
	/*4. 等待客户端连接*/
	tcp_client_data.addrlen = sizeof(struct sockaddr);
	while (1)
	{
#if TESTFUN
		if (Contrl_thread_state == 0) // 实际放入项目上使用时该步骤可以注释掉，不用开启这个线程
		{
			if (pthread_create(&test_thread_id, 0, test_fun, (void *)&tcp_client_data) == 0) // 创建test线程
			{
				Contrl_thread_state = 1;
				pthread_detach(test_thread_id);
			}
			else
			{
				printf("test线程创建失败！\n");
			}
		}
#endif

		tcp_client_data.clientfd = accept(tcp_server_fd, (struct sockaddr *)&tcp_client_data.sockaddr, &tcp_client_data.addrlen); // 等待客户端
		if (tcp_client_data.clientfd < 0)
		{
			printf("TCP服务器:等待客户端连接失败！！！\n");
		}
		else
		{
			printf("\n已经连接的客户端信息: %s:%d\n", inet_ntoa(tcp_client_data.sockaddr.sin_addr), ntohs(tcp_client_data.sockaddr.sin_port)); // 打印连接的客户端地址信息
			tcp_client_data.connect_state = 0;
			if (pthread_create(&tcp_thread_id, 0, SocketPthread_func, (void *)&tcp_client_data) == 0) // 1. 创建线程
			{
				tcp_client_data.connect_state = 1;
				tcp_client_data.ClientThread_id = tcp_thread_id;
				strcpy(tcp_client_data.ip, inet_ntoa(tcp_client_data.sockaddr.sin_addr));
				tcp_client_data.port = ntohs(tcp_client_data.sockaddr.sin_port);
				pthread_detach(tcp_thread_id); // 2. 设置分离属性,让线程结束之后自己释放资源SN_EW_ALL_OFF
				DisplayListDeviceInfo();
				write(tcp_client_data.clientfd, ALL_OFF, sizeof(ALL_OFF)); // 关闭所有的开关
				usleep(500 * 1000);
			}
		}
	}
}




/*

举例子：一次控制1 2 3 13 号开启，15号关闭
anyGpioControl(1,1,1);
anyGpioControl(2,1,0);
anyGpioControl(3,1,0);
anyGpioControl(13,1,0);
anyGpioControl(15,0,0);
sendCmdToRelay(sendbuff);

*/

int anyGpioControl(unsigned char pin, bool pinState ,bool clear_state)
{
	int i=0;
	unsigned char temp=0;
	if(clear_state)
	{
		relayCmd.contrlBit=0x0000;
		relayCmd.enablelBit=0xFFFF;
	}
	if(pinState)
		relayCmd.contrlBit |=  (1<<(pin-1));
	else
		relayCmd.contrlBit &=  ~(1<<(pin-1));
	relayCmd.enablelBit |= (1<<(pin-1));	
	relayCmd.crcH=0;
	for(i=2;i<=7;i++)
	 relayCmd.crcH += *((unsigned char *)&relayCmd+i);
	relayCmd.crcL=relayCmd.crcH*2;
	memcpy(sendbuff,&relayCmd,10);
	temp=sendbuff[4];
	sendbuff[4]=sendbuff[5];
	sendbuff[5]=temp;
	temp=sendbuff[6];
	sendbuff[6]=sendbuff[7];
	sendbuff[7]=temp;
	#if DBUG_MODE
	for(i=0;i<sizeof(sendbuff);i++) printf("%.2X ",*(sendbuff+i));
	printf("sendbuff_len=%d \n",sizeof(sendbuff));
	#endif
	return 0;
}



int sendCmdToRelay(const unsigned char *buff)
{
	int sendCmdNum=0;
	tcp_client_data.ack=0;
	sendCmdNum=0;
	while(tcp_client_data.ack==0 && sendCmdNum <CHECK_MAX_NUM)
	{
		write(tcp_client_data.clientfd,buff,sizeof(buff));//发送命令
		usleep(1000*50);
		sendCmdNum++;
	}
	#if DBUG_MODE
	printf("sendbuff_check_num=%d \n",sendCmdNum);
	#endif
	if(sendCmdNum == CHECK_MAX_NUM) return -1;
	return 0;
}


/*
红绿灯控制API接口函数
参数
	gpioNum: 选择GPIO口编号 1~16
	gpioState:使能  1表示开启  0表示关闭
	return 0 表示正常
*/
int securityRelayAlarmSingnalAPI(int gpioNum, int gpioState)
{
	int i = 0;
	printf("securityRelayAlarmSingnalAPI is called ! GPIO_%d = %d \n", gpioNum, gpioState);
	tcp_client_data.ack = 0;
	if (tcp_client_data.connect_state)
	{
		if (gpioState)
		{
			while (!tcp_client_data.ack && i < CHECK_MAX_NUM)
			{
				write(tcp_client_data.clientfd, gpio_16pin_on[gpioNum], 10);
				usleep(50 * 1000);
				i++;
			}
		}
		else
		{
			while (!tcp_client_data.ack && i < CHECK_MAX_NUM)
			{
				write(tcp_client_data.clientfd, gpio_16pin_off[gpioNum], 10);
				usleep(50 * 1000);
				i++;
			}
		}
		if (i == CHECK_MAX_NUM)
		{
			printf("Send command failure !\n");
			return -1;
		}
	}
	else
	{
		printf("Controller offline ...... ! \n");
		return -2;
	}
	return 0;
}

/*
设置安防继电器服务端的TCP ip和端口
*/
int SetTcpServerConfigAPI(const char *tcp_server_ip, int tcp_server_port)
{
	memcpy(TCP_ServerIP, tcp_server_ip, strlen(tcp_server_ip));
	TCP_ServerPort = tcp_server_port;
#if DBUG_MODE
	printf("\nTCPServerIP: %s  TCPServerPort: %d\n", TCP_ServerIP, TCP_ServerPort);
#endif
	return 0;
}

/*
函数功能:  红绿灯TCP服务端处理函数
*/
void *SocketPthread_func(void *dev)
{
	char RxData[8] = {0}; // 存放接收的数据
	fd_set readfds;		  // 读事件的文件操作集合
	int select_state;	  // 接收返回值
	unsigned int rx_cnt;
	while (1)
	{
		FD_ZERO(&readfds);														/*5.1 清空文件操作集合*/
		FD_SET(tcp_client_data.clientfd, &readfds);								/*5.2 添加要监控的文件描述符*/
		select_state = select(tcp_client_data.clientfd + 1, &readfds, 0, 0, 0); /*5.3 监控文件描述符*/
		if (select_state > 0)													// 表示有事件产生
		{
			if (FD_ISSET(tcp_client_data.clientfd, &readfds)) /*5.4 测试指定的文件描述符是否产生了读事件*/
			{
				rx_cnt = read(tcp_client_data.clientfd, RxData, sizeof(RxData)); /*5.5 读取数据*/
#if DBUG_MODE
// printf("\n服务端收到数据包%d字节 rx_cnt=%s  ",rx_cnt,RxData);
#endif
				// if( rx_cnt==3 && RxData.Cmd[0]==0x4F && RxData.Cmd[1]==0x4B && RxData.Cmd[2]==0x21)
				if (!strcmp(RxData, "OK!"))
				{
					if (tcp_client_data.clientfd == tcp_client_data.clientfd)
					{
						tcp_client_data.ack = 1;
						tcp_client_data.connect_state = 1;
#if DBUG_MODE
						printf("clientfd= %d 数据：%s     客户端IP:%s   connect_state = %d  thread_id=%ld\n",
							   tcp_client_data.clientfd, RxData, tcp_client_data.ip, tcp_client_data.connect_state, tcp_client_data.ClientThread_id);
#endif
					}
					memset(RxData, 0, sizeof(RxData));
				}
				else if (rx_cnt == 0)
				{
					printf("对方已断开连接.....\n");
					break;
				}
				else
				{
					printf("数据包大小接收不正确!\n");
				}
			}
		}
		else if (select_state < 0) // 表示产生了错误
		{
			printf("select函数产生异常!\n");
			break;
		}
	}
	tcp_client_data.connect_state = 0;
	printf("\n已经删除clientfd=%d  IP= %s 的连接!!!\n", tcp_client_data.clientfd, tcp_client_data.ip);
	close(tcp_client_data.clientfd); /*6. 关闭连接*/
}

void CloseSocketfd()
{
	int ret;
	close(tcp_client_data.clientfd);					   /*关闭tcp套接字*/
	ret = pthread_cancel(tcp_client_data.ClientThread_id); /*取消TCP线程*/
	if (ret != 0)
	{
		printf("Traffic light pthread cancel is failed ...\n");
	}
	printf("TCP thread is canceled !!!\n");
}

void DisplayListDeviceInfo()
{
	printf("\n已经连接的客户端信息 Device IP=%s  port=%d clientfd=%d connect_state=%d command_ack=%d ClientThread_id=%ld\n\n",
		   tcp_client_data.ip, tcp_client_data.port, tcp_client_data.clientfd, tcp_client_data.connect_state, tcp_client_data.ack, tcp_client_data.ClientThread_id);
}

/*
红绿灯调试函数
当 TESTFUN 为0 的时候该线程不会创建
*/
void *test_fun(void *)
{
	int Chose_state, gpio_num, gpio_state, i;
#if DBUG_MODE
	printf("test_fun线程创建成功！！！\n");
#endif
	while (!tcp_client_data.connect_state)
	{
		printf("\n服务器等待红绿灯上线中......\n");
		sleep(1);
		while (tcp_client_data.connect_state)
		{
			if (Chose_state != 5)
				system("clear");
			printf("\n*****************************\n");
			printf("	1.全开\n");
			printf("	2.全关\n");
			printf("	3.单个开关控制\n");
			printf("	4.自检测试\n");
			printf("	5.打印客户端信息\n");
			printf("*****************************\n");
			printf("请选择状态 ：");
			scanf("%d", &Chose_state);
			switch (Chose_state)
			{
			case 1:
			{
				write(tcp_client_data.clientfd, ALL_ON, sizeof(ALL_ON));
				usleep(500 * 1000);
			}
			break;
			case 2:
			{
				write(tcp_client_data.clientfd, ALL_OFF, sizeof(ALL_OFF));
				usleep(500 * 1000);
			}
			break;
			case 3:
			{
				printf("请输入 开关编号  开关状态 (例如 10 1): ");
				scanf("%d %d", &gpio_num, &gpio_state);
				securityRelayAlarmSingnalAPI(gpio_num, gpio_state);
				usleep(500 * 1000);
			}
			break;
			case 4:
			{
				printf("\n网络继电器自检测试中 ......\n");
				write(tcp_client_data.clientfd, ALL_ON, sizeof(ALL_ON));
				sleep(1);
				write(tcp_client_data.clientfd, ALL_OFF, sizeof(ALL_OFF));
				sleep(1);
				for (i = 0; i < 16; i++)
				{
					write(tcp_client_data.clientfd, gpio_16pin_on[i], 10);
					usleep(500 * 1000);
				}
				for (i = 0; i < 16; i++)
				{
					write(tcp_client_data.clientfd, gpio_16pin_off[i], 10);
					usleep(500 * 1000);
				}
			}
			case 5:
			{
				DisplayListDeviceInfo();
				break;
			}
			default:
				break;
			}
		}
	}
}

/*
开 1：CCDDA10100010001A448
开 2: CCDDA10100020002A64C
开 3：CCDDA10100040004AA54
开 4：CCDDA10100080008B264
开 5：CCDDA10100100010C284
开 6：CCDDA10100200020E2C4
开 7：CCDDA101004000402244
开 8：CCDDA10100800080A244
开 9：CCDDA10101000100A448
开10：CCDDA10102000200A64C
开11：CCDDA10104000400AA54
开12：CCDDA10108000800B264
开13：CCDDA10110001000C284
开14：CCDDA10120002000E2C4
开15：CCDDA101400040002244
开16：CCDDA10180008000A244

关 1：CCDDA10100000001A346
关 2：CCDDA10100000002A448
关 3：CCDDA10100000004A64C
关 4：CCDDA10100000008AA54
关 5：CCDDA10100000010B264
关 6：CCDDA10100000020C284
关 7：CCDDA10100000040E2C4
关 8：CCDDA101000000802244
关 9：CCDDA10100000100A346
关10：CCDDA10100000200A448
关11：CCDDA10100000400A64C
关12：CCDDA10100000800AA54
关13：CCDDA10100001000B264
关14：CCDDA10100002000C284
关15：CCDDA10100004000E2C4
关16：CCDDA101000080002244

全开：CCDDA101FFFFFFFF9E3C
全关：CCDDA1010000FFFFA040

以上指令为16进制byte   CC  DD  A1 。。字节发送

unsigned char OUT1_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x01,0x00,0x01,0xA4,0x48};//开1号
unsigned char OUT1_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x01,0xA3,0x46};//关1号
unsigned char OUT2_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x02,0x00,0x02,0xA6,0x4C};//开2号
unsigned char OUT2_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x02,0xA4,0x48};//关2号
unsigned char OUT3_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x04,0x00,0x04,0xAA,0x54};//开3号
unsigned char OUT3_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x04,0xA6,0x4C};//关3号
unsigned char OUT4_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x08,0x00,0x08,0xB2,0x64};//开4号
unsigned char OUT4_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x08,0xAA,0x54};//关4号

unsigned char OUT5_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x10,0x00,0x10,0xC2,0x84};//开5号
unsigned char OUT5_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x10,0xB2,0x64};//关5号
unsigned char OUT6_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x20,0x00,0x20,0xE2,0xC4};//开6号
unsigned char OUT6_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x20,0xC2,0x84};//关6号
unsigned char OUT7_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x40,0x00,0x40,0x22,0x44};//开7号
unsigned char OUT7_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x40,0xE2,0xC4};//关7号
unsigned char OUT8_ON[]={0xCC,0xDD,0xA1,0x01,0x00,0x80,0x00,0x80,0xA2,0x44};//开8号
unsigned char OUT8_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x00,0x80,0x22,0x44};//关8号

unsigned char OUT9_ON[]={0xCC,0xDD,0xA1,0x01,0x01,0x00,0x01,0x00,0xA4,0x48};//开9号
unsigned char OUT9_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x01,0x00,0xA3,0x46};//关9号
unsigned char OUT10_ON[]={0xCC,0xDD,0xA1,0x01,0x02,0x00,0x02,0x00,0xA6,0x4C};//开10号
unsigned char OUT10_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x02,0x00,0xA4,0x48};//关10号
unsigned char OUT11_ON[]={0xCC,0xDD,0xA1,0x01,0x04,0x00,0x04,0x00,0xAA,0x54};//开11号
unsigned char OUT11_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x04,0x00,0xA6,0x4C};//关11号
unsigned char OUT12_ON[]={0xCC,0xDD,0xA1,0x01,0x08,0x00,0x08,0x00,0xB2,0x64};//开12号
unsigned char OUT12_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x08,0x00,0xAA,0x54};//关12号

unsigned char OUT13_ON[]={0xCC,0xDD,0xA1,0x01,0x10,0x00,0x10,0x00,0xC2,0x84};//开13号
unsigned char OUT13_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x10,0x00,0xB2,0x64};//关13号
unsigned char OUT14_ON[]={0xCC,0xDD,0xA1,0x01,0x20,0x00,0x20,0x00,0xE2,0xC4};//开14号
unsigned char OUT14_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x20,0x00,0xC2,0x84};//关14号
unsigned char OUT15_ON[]={0xCC,0xDD,0xA1,0x01,0x40,0x00,0x40,0x00,0x22,0x44};//开15号
unsigned char OUT15_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x40,0x00,0xE2,0xC4};//关15号
unsigned char OUT16_ON[]={0xCC,0xDD,0xA1,0x01,0x80,0x00,0x80,0x00,0xA2,0x44};//开16号
unsigned char OUT16_OFF[]={0xCC,0xDD,0xA1,0x01,0x00,0x00,0x80,0x00,0x22,0x44};//关16号

*/
