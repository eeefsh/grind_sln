#include "pch.h"
#define gy_dll_time_updata_EXPORTS
#include "time_updata.h"

time_updata::time_updata()
{
    set_current_time();
}

void time_updata::set_current_time()
{
    currentTime = time(nullptr);
}

void time_updata::clear()
{
    time_t temp;
    temp = 0;
    currentTime = temp;
}

std::tm time_updata::get_tm()
{
    std::tm val;
    localtime_s(&val, &currentTime);
    return val;
}

std::string time_updata::get_sec()
{
    std::string temp;

    if (get_tm().tm_sec < 10)
    {
        temp="0"+ std::to_string(get_tm().tm_sec);
    }
    else
    {
        temp = std::to_string(get_tm().tm_sec);
    }
    return temp;
}

std::string time_updata::get_min()
{
    std::string temp;

    if (get_tm().tm_min < 10)
    {
        temp = "0" + std::to_string(get_tm().tm_min);
    }
    else
    {
        temp = std::to_string(get_tm().tm_min);
    }
    return temp;
}

std::string time_updata::get_hour()
{
    std::string temp;

    if (get_tm().tm_hour < 10)
    {
        temp = "0" + std::to_string(get_tm().tm_hour);
    }
    else
    {
        temp = std::to_string(get_tm().tm_hour);
    }
    return temp;
}

std::string time_updata::get_mday()
{
    std::string temp;

    if (get_tm().tm_mday < 10)
    {
        temp = "0" + std::to_string(get_tm().tm_mday);
    }
    else
    {
        temp = std::to_string(get_tm().tm_mday);
    }
    return temp;
}

std::string time_updata::get_mon()
{
    std::string temp;

    if (get_tm().tm_mon < 9)
    {
        temp = "0" + std::to_string(get_tm().tm_mon + 1);
    }
    else
    {
        temp = std::to_string(get_tm().tm_mon + 1);
    }
    return temp;
}

std::string time_updata::get_year()
{
    std::string temp;
    temp = std::to_string(get_tm().tm_year + 1900);
    return temp;
}

std::string time_updata::get_wday()
{
    std::string temp;
    temp = std::to_string(get_tm().tm_wday);
    return temp;
}

std::string time_updata::get_yday()
{
    std::string temp;
    temp = std::to_string(get_tm().tm_yday);
    return temp;
}

std::string time_updata::get_isdst()
{
    std::string temp;
    temp = std::to_string(get_tm().tm_isdst);
    return temp;
}

std::string time_updata::get_year_mon_day_hour_min_sec()
{
    std::string temp;
    temp = get_year() + ',' + get_mon() + ',' + get_mday() + "  " + get_hour() + ':' + get_min() + ':' + get_sec();
    return temp;
}
