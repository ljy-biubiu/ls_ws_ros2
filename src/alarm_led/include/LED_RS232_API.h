/***********************************************************
 *  Copyright (c) 2023 LeiShenLidar . All rights reserved.
 *  @filename    LED_RS232_API.cpp
 *  @author      ZhongHai
 *  @date        2023/05/10-18:00
 *  @version     v1.1
 ************************************************************/
#ifndef PORTSECURITY_LED_RS232_API_H
#define PORTSECURITY_LED_RS232_API_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_msgs/msg/int8_multi_array.hpp>
#include <vector>

// int StartAlarmLight();
void *StartAlarmLight(void *);
void *test_fun(void *);
int LEDContrlAPI(int AlarmState);
int ledAlarmControlfun();
void *RS232_ReceiveDataProcess(void *);
int RS232_ReceiveBytes(int fd, void *revbuf, int count);
int RS232_SendBytes(int fd, void *sendbuf, int count);
int CheckDataPackage(unsigned char *data_buff, unsigned int rx_size);
int openSerialPort(int baudrate, const char *deviceAddr);

// std::vector<int> electric_relay_flags;
// void parameterServerCallback(const std_msgs::msg::String::SharedPtr msg);
// void electric_relay_callback(const std_msgs::msg::Int8MultiArray::SharedPtr msg);
void timerCallback();
void alarm_led_callback(const std_msgs::msg::Int8::SharedPtr msg);

// auto alarm_control_sub = node->create_subscription<std_msgs::msg::Int8>(
//     "/alarm_led/led_control",
//     rclcpp::QoS{1},
//     [node](const std_msgs::msg::Int8::SharedPtr msg)
//     { alarm_led_callback(msg); });
int delay_cnt = -1;
bool delay_flag = false;
rclcpp::Node::SharedPtr node;
rclcpp::TimerBase::SharedPtr timer_;

#endif // PORTSECURITY_LED_RS232_API_H
