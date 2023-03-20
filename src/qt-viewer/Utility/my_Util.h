#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>

// 时间处理头文件
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;

class MyUtil
{
public:
    //对比俩个字符串是否相同
	static bool compare_write_data(char *buf1, char *buf2);
    //按****标志位分割字符串
	static std::vector<std::string> split(std::string str, std::string pattern);
    //获取当前日期时间
	static const std::string getCurDate();

    //毫秒
    double timeMs();
    //微秒
    unsigned long long timeUs();
};

#endif
