#pragma once
#include "wheel_define.h"
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "manager_h/MA_010101_gy_dll_time_updata.h"

namespace wheel_database_namespace
{
    //文件索引类
    class list_time
    {
    public:
        int pos = 0;
        time_updata time;
        bool operator<(const list_time& other) const {
            bool flag = 0;
            if (time == other.time)
            {
                flag = pos < other.pos;
            }
            else
            {
                flag = time < other.time;
            }
            //从大到小排序
            return !flag;
        }
    };

    //砂轮数据类
    class wheel_data
    {
        //砂轮名称
        char name_wheel[50] = { 0 };

        //dxf路径文件位置
        char dir_dxf[256] = { 0 };

    public:
        //砂轮主键编号
        int key_wheel = -1;

        //砂轮类型标记
        int type_wheel = -1;

        //砂轮组主键编号
        int key_group = -1;

        //倒装标志
        //0:正 1:反
        bool daozhuang = 0;

        //测量大小端标志
        //0:大 1:小
        bool Celiang_flag = 0;

        //砂轮参数数据
        //0:法兰长度，1:大端直径，2:小端直径，3:角度1，
        //4:角度2，5:大端圆角，6:小端圆角,7:宽度
        double data[10] = { 0 };

        //圆角参考长度L0
        double L0 = 0;

        //圆角参考长度L1
        double L1 = 0;

        //圆角参考半径Ry0
        double Ry0 = 0;

        //圆角参考半径Ry1
        double Ry1 = 0;

        //更新时间
        time_updata time_new;

        //设置名称
        void set_name(std::string name);

        //获取名称字符串
        std::string get_name();

        //设置dxf路径
        void set_dir_dxf(std::string name);

        //获取dxf路径字符串
        std::string get_dir_dxf();

        //清除数据
        void clear();
    };

    //砂轮位置参考信息类
    class weizhi_cankao
    {
    public:
        //当前位置使用砂轮主键编号
        int key_wheel = -1;
        //参考距离
        double distance = 0;
        //参考位置标记
        //0：内
        //1：外
        bool cankao_flag = 0;

        //1：只有一个参考面的标志
        bool one_cankao = 0;
    };

    //砂轮组数据类
    class group_data
    {
        //砂轮组名称
        char name_group[50] = { 0 };

    public:
        //砂轮组主键编号
        int key_group = -1;

        //在机床上的刀架号
        //没有安装在机床上时为-1
        int num_daojia = -1;

        //砂轮杆直径
        double gan_D = 0;

        //螺帽直径
        double nut_D = 0;

        //螺帽长度
        double nut_L = 0;

        //砂轮安装位置
        weizhi_cankao weizhi[9];

        //更新时间
        time_updata time_new;

        //设置名称
        void set_name(std::string name);

        //获取名称字符串
        std::string get_name();

        //清除数据
        void clear();
    };

    //砂轮和砂轮组文件读写类
    class data_rw
    {
        //路径文件
        std::fstream file;

        //砂轮参数文件路径
        std::string dir;

    public:
        //初始化文件路径
        void Init_dir(std::string& _dir);

        //写数据到砂轮文件
        //位置指针：pos
        //数据：val
        void writeToFile(std::streampos pos, wheel_data& val);

        //读砂轮文件数据到内存
        //位置指针：pos
        //数据：val
        void readFromFile(std::streampos pos, wheel_data& val);

        //写数据到砂轮组文件
        //位置指针：pos
        //数据：val
        void writeToFile(std::streampos pos, group_data& val);

        //读砂轮组文件数据到内存
        //位置指针：pos
        //数据：val
        void readFromFile(std::streampos pos, group_data& val);

    };

    //索引读写类
    class list_rw
    {
        //路径文件
        std::fstream file;

        //砂轮参数文件路径
        std::string dir;

    public:
        //被删除后的空位
        std::vector<int> pos_temp;

        //初始化文件路径
        void Init_dir(std::string& _dir);

        //写数据到索引文件
        void writeToList(std::set<list_time>& val);

        //读索引数据到内存
        void readFromList(std::set<list_time>& val);
    };
}

//砂轮数据库类
class NC_wheel_data_API wheel_database
{

//文件读写相关内容
private:

    //砂轮索引读写对象
    wheel_database_namespace::list_rw rw_list_wheel;

    //砂轮数据读写对象
    wheel_database_namespace::data_rw rw_data_wheel;

    //砂轮组索引读写对象
    wheel_database_namespace::list_rw rw_list_group;

    //砂轮组数据读写对象
    wheel_database_namespace::data_rw rw_data_group;

private:

    //设置砂轮上砂轮组主键
    void set_wheel_group_key(wheel_database_namespace::group_data& val);

    void clear_wheel_group_key(wheel_database_namespace::group_data& val);

    
public:
    //全部砂轮索引
    static std::set<wheel_database_namespace::list_time> list_wheel_all;

    //全部砂轮组索引
    static std::set<wheel_database_namespace::list_time> list_group_all;

    ////全部砂轮索引
    //std::set<wheel_database_namespace::list_time> list_wheel_all;

    ////全部砂轮组索引
    //std::set<wheel_database_namespace::list_time> list_group_all;

    //被修改的砂轮id缓存
    static std::set<int> edit_buff_wheel;

protected:

    //初始化数据库文件路径
    //1.砂轮索引文件路径
    //2.砂轮数据文件路径
    //3.砂轮组索引文件路径
    //4.砂轮组数据文件路径
    void Init_Dir(
        std::string dir_list_wheel,
        std::string dir_data_wheel,
        std::string dir_list_group,
        std::string dir_data_group);

    //添加一个砂轮到文件
    int add_wheel(wheel_database_namespace::wheel_data val);

    //添加一个砂轮组到文件
    int add_group(wheel_database_namespace::group_data val);

    //从文件删除砂轮
    void delete_wheel(int pos);

    //从文件删除砂轮组
    void delete_group(int pos);

    //修改砂轮数据到文件
    //flag = 1,修改砂轮组主键
    //flag = 0,不修改砂轮组主键
    void edit_wheel(int pos, wheel_database_namespace::wheel_data val, bool flag = 0);

    //修改砂轮组数据到文件
    void edit_group(int pos, wheel_database_namespace::group_data val);

    //从文件读取砂轮数据
    wheel_database_namespace::wheel_data read_wheel(int pos);

    //从文件读取砂轮组数据
    wheel_database_namespace::group_data read_group(int pos);

    
};
