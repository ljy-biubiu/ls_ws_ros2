#include "lslidar_driver/lslidar_driver.h"
#include "std_msgs/msg/string.h"

using namespace lslidar_ch_driver;
volatile sig_atomic_t flag = 1;

static void my_handler(int sig)
{
    flag = 0;
}

int cnt_lslidar{0};

#include <iostream>
#include <chrono>
#include <thread>

void TimerCallback()
{
    while (true)
    {
        // std::cout << "Timer triggered!" << std::endl;
        std::cout << "cnt_lslidar:" << cnt_lslidar << std::endl;
        cnt_lslidar = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 定时器间隔，单位：毫秒
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    signal(SIGINT, my_handler);
    auto node = std::make_shared<lslidar_ch_driver::LslidarChDriver>();
    if (!node->initialize())
    {
        RCLCPP_ERROR(node->get_logger(), "cannot initialize lslidar driver.");
        return 0;
    }

    std::thread timerThread(TimerCallback); // 开启定时器线程
    // 结束定时器线程
    timerThread.detach();

    while (rclcpp::ok())
    {
        node->polling();
    }
    rclcpp::shutdown();
    return 0;
}
