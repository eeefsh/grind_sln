#pragma once

#ifdef gy_dll_time_updata_EXPORTS
#define gy_dll_time_updata_API __declspec(dllexport)
#else
#define gy_dll_time_updata_API __declspec(dllimport)
#endif
#include<string>
#include <ctime>
//更新时间
class gy_dll_time_updata_API time_updata
{
    time_t currentTime;
public:
    time_updata();
    //设置为当前时间
    void set_current_time();
    //清除时间
    void clear();

    //获取时间tm
    std::tm get_tm();

    // 返回表示每分钟秒数的字符串 - [0, 60] 包括闰秒
    std::string get_sec();

    // 返回表示每小时分钟数的字符串 - [0, 59]
    std::string get_min();

    // 返回表示每天小时数的字符串 - [0, 23]
    std::string get_hour();

    // 返回表示每月日期的字符串 - [1, 31]
    std::string get_mday();

    // 返回表示月份的字符串 - [1, 12]
    std::string get_mon();

    // 返回表示年数的字符串
    std::string get_year();

    // 返回表示自星期日以来天数的字符串 - [0, 6]
    std::string get_wday();

    // 返回表示自一月一日以来天数的字符串 - [0, 365]
    std::string get_yday();

    // 返回表示夏令时标志的字符串
    std::string get_isdst();

    // 返回表示年，月，日，时:分:秒的字符串
    std::string get_year_mon_day_hour_min_sec();

    bool operator<(const time_updata& other) const
    {
        return difftime(currentTime, other.currentTime) < 0;
    }
    bool operator==(const time_updata& other) const
    {
        return difftime(currentTime, other.currentTime) == 0;
    }
};

