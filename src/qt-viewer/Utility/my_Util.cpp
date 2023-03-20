
#include "my_Util.h"

//对比俩个字符串是否相同
bool MyUtil::compare_write_data(char *buf1, char *buf2)
{
    for (int i = 0; i < sizeof(buf1); i++)
    {
        if (buf1[i] != buf2[i])
        {
            return false;
        }
    }
    return true;
}


// 字符串分割
std::vector<std::string> MyUtil::split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern; // 扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

//获取当前日期时间
const std::string MyUtil::getCurDate()
{
    time_t now = time(nullptr);
    tm *t = localtime(&now);

    //std::string str =  std::to_string(t->tm_year + 1900) + "/" + std::to_string(t->tm_mon + 1) + "/" + std::to_string(t->tm_mday) + "-" + std::to_string(t->tm_hour) + "/" + std::to_string(t->tm_min) + "/" + std::to_string(t->tm_sec);
    std::string str =    std::to_string(t->tm_mday) + "-" +std::to_string(t->tm_hour) + ":" + std::to_string(t->tm_min) + ":" + std::to_string(t->tm_sec);
    return str;
}

//
double MyUtil::timeMs() {
    timespec ts{};
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / (1000.0 * 1000.0);
}

unsigned long long MyUtil::timeUs() {
    timespec ts{};
    timespec_get(&ts, TIME_UTC);
    return (unsigned long long) (ts.tv_sec * 1000.0 * 1000.0 + ts.tv_nsec / (1000.0));
}

