#pragma once
#include <vector>
#include <string>
#include "wheel_database.h"
#include "wheel_define.h"

namespace wheel_dialog_namespace
{
    class NC_wheel_data_API canshu_Ping_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Daduan_D = 80;
        double Xiaoduan_D = 80;
        double Daduan_Yuanjiao_r = 0.001;
        double Xiaoduan_Yuanjiao_r = 0.001;
        double Jiaodu = 0;
        double Kuandu = 10;
        //0:大端朝向内侧，1:小端朝向内侧
        bool daozhuang_flag = 0;
        //0:测量大端，1:测量小端
        bool Celiang_flag = 0;
        //部分参数计算
        //flag=0用大端圆角计算
        //flag=1用小端圆角计算
        void jisuan_canshu(bool flag);
        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());
        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class NC_wheel_data_API canshu_Beixing_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Zhijing_D = 80;
        double Kuandu = 30;
        double Neishen = 20;
        double Yuanjiao_r = 0.001;
        double Moliao = 10;
        double jiao_nei = 0;
        double jiao_wai = 30;
        bool auto_Neishen = 1;
        //部分参数计算
        void jisuan_canshu();
        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());
        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class NC_wheel_data_API canshu_Diexing_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Zhijing_D = 80;
        double Yuanjiao_r = 0.001;
        double Jiaodu = 40;
        double Kuandu = 10;
        bool Chao_wai = 0;
        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());
        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class NC_wheel_data_API canshu_Yuanjiao_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Zhijing_D = 80;
        double Yuanjiao_r = 5;

        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());

        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class NC_wheel_data_API canshu_Jianjiao_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Zhijing_D = 80;
        double Yuanjiao_r = 0.001;
        double Jiaodu = 45;
        double Kuandu = 5;
        double Jiti_D = 40;
        double Jiti_jiao = 45;
        double Jiti_kuan = 10;
        bool auto_Jiti = 1;
        
        //部分参数计算
        void jisuan_canshu();
        
        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());

        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class NC_wheel_data_API canshu_DXF_shalun
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        std::string name;
        double Yuanjiao_r = 0;
        double Zhijing_D = 0;
        double Zhouxiang = 0;
        std::string dxf_dir;

        //数据转换到数据库数据
        wheel_data To_wheel_data(wheel_data data = wheel_data());

        //数据转换到数据库数据
        void To_dialog_data(wheel_data data);

        static void Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag);
    };

    class wheel_list_data
    {
    public:
        std::string wheel_name;
        std::string group_name;
        std::string type;
        std::string falan;
        std::string Zhijin_D;
        std::string Jiaodu;
        std::string Yuanjiao_1;
        std::string Yuanjiao_2;
        std::string time_new;
        int pos = 0;
    };

    class group_list_data
    {
    public:
        std::string group_name;
        std::string n_wheel;
        std::string time_new;
        int pos = 0;
    };

    class NC_wheel_data_API canshu_Shalun_group
    {
        using weizhi_cankao = wheel_database_namespace::weizhi_cankao;
        using group_data = wheel_database_namespace::group_data;

        double gan_D = 0;
        double luomao_D = 0;
        double luomao_L = 0;
    public:
        std::string group_name;
        std::vector<weizhi_cankao> wheel_buff;
        //安装一个砂轮,砂轮已经被选择就返回1
        bool add_wheel(int key_wheel, double distance, bool cankao_flag, bool one_cankao);
        //编辑一个砂轮安装参数
        void edit_a_wheel(int key_wheel, double distance, bool cankao_flag);
        //删除一个砂轮
        void del_wheel(int key_wheel);
        bool get_one_cankao_flag(int key_wheel);
        void get_a_wheel_canshu(int key_wheel, double& distance, bool& cankao_flag, bool& one_cankao);
        int size();
        void Init(group_data data);
        double get_gan_D();
        double get_luomao_D();
        double get_luomao_L();
        group_data To_group_data(std::string name, double gan_D, double luomao_D, double luomao_L, group_data ans = group_data());
    };

    class group_creat_list_data
    {
    public:
        std::string wheel_type;
        std::string wheel_name;
        std::string dis;
        std::string cankao;
    };
};

//砂轮库界面使用类
class NC_wheel_data_API wheel_dialog :
    public wheel_database
{
    using group_data = wheel_database_namespace::group_data;
    using wheel_data = wheel_database_namespace::wheel_data;
    using canshu_Ping_shalun = wheel_dialog_namespace::canshu_Ping_shalun;
    using wheel_list_data = wheel_dialog_namespace::wheel_list_data;
    using group_list_data = wheel_dialog_namespace::group_list_data;
    using canshu_Shalun_group = wheel_dialog_namespace::canshu_Shalun_group;
    using group_creat_list_data = wheel_dialog_namespace::group_creat_list_data;
public:
    wheel_dialog();

    //初始化数据库文件路径
    //1.砂轮索引文件路径
    //2.砂轮数据文件路径
    //3.砂轮组索引文件路径
    //4.砂轮组数据文件路径
    using wheel_database::Init_Dir;

    //添加一个砂轮到文件
    using wheel_database::add_wheel;

    //添加一个砂轮组到文件
    int add_group(group_data val);

    //从文件删除砂轮
    using wheel_database::delete_wheel;
    //从文件删除砂轮组
    using wheel_database::delete_group;
    //从文件读取一个砂轮数据
    using wheel_database::read_wheel;
    //从文件修改一个砂轮数据
    void edit_wheel(int pos, wheel_data val);

    //从文件修改一个砂轮组数据
    void edit_group(int pos, group_data val);

    //从文件读取砂轮组数据
    using wheel_database::read_group;

    //获取砂轮列表参数
    wheel_list_data get_wheel_canshu(int pos);

    //获取砂轮组列表参数
    group_list_data get_group_canshu(int pos);

    //获取砂轮组列表参数
    group_creat_list_data get_group_creat_list_canshu(int pos);
};

