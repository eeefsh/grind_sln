#pragma once
#ifdef NC_wheel_data_EXPORTS
#define NC_wheel_data_API __declspec(dllexport)
#else
#define NC_wheel_data_API __declspec(dllimport)
#endif
#include <fstream>
#include <iostream>
#include <vector>

namespace WheelDatabaseManager_namespace
{
    class update_time
    {
        time_t currentTime;
    public: 
        update_time();
        void get_tm(std::tm& val);
    };
}

//砂轮数据
class NC_wheel_data_API wheel_pack_data
{
public:
    char type = 0;
    char dxf_dir[43] = { 0 };
    char name_wheel[20] = { 0 };
    char name_group[20] = { 0 };
    char notes[100] = { 0 };
    WheelDatabaseManager_namespace::update_time set_time;
    double data1 = 0.0;
    double data2 = 0.0;
    double data3 = 0.0;
    double data4 = 0.0;
    double data5 = 0.0;
    double data6 = 0.0;
    double data7 = 0.0;
    double data8 = 0.0;
    double data9 = 0.0;
    std::string get_name_wheel();
};






//砂轮参考信息
class wheel_reference_information
{
public:
    double distance = 0.0;
    char name_wheel[20] = { 0 };
    char daozhuang = 0;
    char cankao_flag = 0;
    std::string get_name_wheel();
};

//砂轮杆数据
class wheel_pole_data
{
public:
    double D0 = 0.0;
    double D1 = 0.0;
    double D2 = 0.0;
    double D3 = 0.0;
    double L0 = 0.0;
    double L1 = 0.0;
    double L2 = 0.0;
    double L3 = 0.0;
};

//砂轮组数据
class NC_wheel_data_API group_pack_data
{
public:
    char name_group[20] = { 0 };
    wheel_reference_information wheel1;
    wheel_reference_information wheel2;
    wheel_reference_information wheel3;
    wheel_reference_information wheel4;
    wheel_pole_data pole;
    char notes[100] = { 0 };
    WheelDatabaseManager_namespace::update_time set_time;
};


//砂轮数据库
class NC_wheel_data_API WheelDatabaseManager
{
private:
    size_t size_num;
    std::streampos ptr_pos;
public:
    WheelDatabaseManager(std::string dir_val);
    bool insertWheeldata(wheel_pack_data& data);
    bool renewWheeldata(std::vector<wheel_pack_data>& data);
    bool readWheeldata(std::vector<wheel_pack_data>& data);
    size_t size();
private:
    void creat_bin(std::fstream& outFile);
    void find_empty_wheel(std::streampos& out);
    
};

//砂轮组数据库
class NC_wheel_data_API GroupDatabaseManager
{
private:
    size_t size_num;
    std::streampos ptr_pos;
public:
    GroupDatabaseManager(std::string dir_val);
    bool renewGroupdata(std::vector<group_pack_data>& data);
    bool readGroupdata(std::vector<group_pack_data>& data);
    size_t size();
private:
    void creat_bin(std::fstream& outFile);
};