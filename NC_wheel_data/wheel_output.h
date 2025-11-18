#pragma once
#include "wheel_database.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

namespace wheel_output_namespace
{
    class NC_wheel_data_API wheel_outlines
    {
        using wheel_data = wheel_database_namespace::wheel_data;
    public:
        //圆弧角度划分
        static vec rot_angle(double err, double r, double start, double end);
        //获取圆弧插值点
        //圆心，精度，半径，起始角度，结束角度
        //err是插值后相邻两点的中点到圆心的距离偏差
        static std::vector<vec3> discrete_arc(vec c, double err, double r, double start, double end);

        static mat wheel_Ping_2D(wheel_data data, double e = 0.1);
        static mat wheel_Beixing_2D(wheel_data data, double e = 0.1);
        static mat wheel_Yuanjiao_2D(wheel_data data, double e = 0.1);
        static mat wheel_Diexing_2D(wheel_data data, double e = 0.1);
        static mat wheel_DXF_2D(wheel_data data, double e = 0.1);
        static mat wheel_Jianjiao_2D(wheel_data data, double e = 0.1);
        static mat gan_2D(double gan_L, double gan_D, double nut_L, double nut_D);
    };
}

//砂轮数据输出类
class NC_wheel_data_API wheel_output :
    private wheel_database,
    private wheel_output_namespace::wheel_outlines
{
    using wheel_data = wheel_database_namespace::wheel_data;
    using group_data = wheel_database_namespace::group_data;

    
private:
    bool no_find_flag(std::set<wheel_database_namespace::list_time>& list_val, int pos);
    void get_x_max(mat val, double& ans);
    
public:
    //初始化数据库文件路径
    //1.砂轮索引文件路径
    //2.砂轮数据文件路径
    //3.砂轮组索引文件路径
    //4.砂轮组数据文件路径
    using wheel_database::Init_Dir;
    
    /// @brief 获取砂轮圆角圆心到砂轮回转中心的径向距离Ry值
    /// @param wheel_key: 砂轮键值
    /// @param wai: 0内圆角，1外圆角
    /// @param Ry_ans: 结果:圆角圆心到砂轮回转中心的径向距离
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_wheel_Ry(int wheel_key, bool wai, double& Ry_ans);

    /// @brief 获取砂轮圆角圆心在砂轮杆上到参考点的轴向距离L值
    /// @param wheel_key: 砂轮键值
    /// @param wai: 0内圆角，1外圆角
    /// @param Ry_ans: 结果:圆角圆心在砂轮杆上到参考点的轴向距离
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_wheel_L(int wheel_key, bool wai, double& L_ans);

    /// @brief 获取砂轮圆角圆角半径r值
    /// @param wheel_key: 砂轮键值
    /// @param wai: 0内圆角，1外圆角
    /// @param Ry_ans: 结果:圆角半径
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_wheel_r(int wheel_key, bool wai, double& r_ans);

    /// @brief 获取砂轮所在砂轮组名称
    /// @param wheel_key: 砂轮键值
    /// @param group_name: 砂轮组名称
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_wheel_group_name(int wheel_key, std::string& group_name);

    /// @brief 获取砂轮组名称
    /// @param group_key: 砂轮组键值
    /// @param group_name: 砂轮组名称
    /// @return 0:获取成功，1:没有找到砂轮组
    int get_group_name(int group_key, std::string& group_name);

    /// @brief 获取砂轮所在砂轮名称
    /// @param wheel_key: 砂轮键值
    /// @param wheel_name: 砂轮名称
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_wheel_name(int wheel_key, std::string& wheel_name);

    /// @brief 获取在砂轮组上的2D砂轮轮廓，包含位置信息
    /// @param wheel_key 砂轮主键
    /// @param ans 每列为一个点x、y、z的mat 3*n
    /// @return 0:获取成功，1:砂轮未安装到砂轮组，2:没有找到砂轮
    int get_2D_wheel_outline(int wheel_key, mat& ans);

    /// @brief 获取在砂轮组的显示轮廓，砂轮杆参考点位于坐标系原点
    /// @param group_key 砂轮组主键
    /// @param ans 每列为一个点x、y、z的mat 3*n的vector
    /// @return 0:获取成功，1:没有找到砂轮组
    int get_group_show_outline(int group_key, std::vector<mat>& ans);
    
    /// @brief 获取砂轮所在砂轮组的键值
    /// @param wheel_key 
    /// @return 返回砂轮组的键值，如果返回值为-1，则没有砂轮组
    int get_group_key_by_wheel_key(int wheel_key);

    /// @brief 获取砂轮组所有砂轮的键值
    /// @param group_key 
    /// @param ans 
    /// @return 0:获取成功，1:未找到砂轮组
    int get_a_group_all_wheel_key(int group_key, std::vector<int>& ans);

    //获取被修改砂轮的id，函数调用后将清空缓存
    std::vector<int> get_edit_buff_wheel();

};