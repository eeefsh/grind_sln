#pragma once

#ifdef NC_Prog_Virtual_Machine_EXPORTS
#define NC_Prog_Virtual_Machine_API __declspec(dllexport)
#else
#define NC_Prog_Virtual_Machine_API __declspec(dllimport)
#endif

#include <vector>
#include <queue>
#include <map>
#include "manager_h/xt_armadillo_settings.h"
#include <stack>

#include <string>      // 用于 std::string  
#include <stack>       // 用于 std::stack  
#include <fstream>     // 用于 std::streampos  

using std::vector;
using std::queue;
using std::map;

//行程范围 24.2.26 zy
//  X (5, -420) 左为正 右为负
//  Y (5, -362) 里为正 外为负
//  Z (25, -193) 上为正 下为负
//  A (0, 360)  逆时针为正
//  C (-100, 100) 逆时针为正  0度垂直x轴

//24.2.27 zy  已备份2.26
//将变量容器改为map，可实现二次值覆盖，按编号查找


//虚拟机：用于表达程序接受程序的操作输出
class NC_Prog_Virtual_Machine_API virtual_machine
{
public:
	virtual_machine();
#pragma region 状态变量

	//G代码
private:
	int G00_03;
	int G17_19;
	int G43_44_49;//G43,G44,G49
	int G54_59;
	bool G90_91;
	bool G94_95;

private:
	double z_F;
	double z_S;

private:
	bool Spindle_on;
	bool Spindle_ccw;
	bool coolant_on;

private:
	vec5 SYS_Mac;
	vec5 SYS_Abs;
	vector<vec5> SYS_G54_59;

private:
	queue<vec5> cache;

private:
	//变量号  值
	map<int, double> BL_sharp;
	map<int, double> BL_at;

	int color_num;
	//vec BL_sharp;//1-400
	//vec BL_at;
	umat BL_at_JG;
private:
	int tool_using_num;  //只允许0-5, 正在使用的砂轮组
	int using_sl_pos_on_slz; //砂轮组上正在使用的2d仿真砂轮，的位置0,1,2

private:
	vec5 point_before;

private:
	int move_point_quatity;

#pragma endregion

	//按键控制
public:
	bool reset_button = 0;
	bool is_M30 = 0;
	bool play_or_pause = 0;	//1-播放、0-暂停
	bool run_one = 0; //1-单步、0-全步

	int count_run_one = 0; //单步计数
	//int count_run_one_pre = -1;

	int count_clear_screen = 0;

#pragma region 操作函数

public:
	void reset();

	void set_RGB(int color);
	int get_cur_color();
public:
	//变量读写-#变量
	bool BL_S_set(int i, double value);
	//变量读写-#变量
	bool BL_S_read(int i, double& ans);
	//变量读写-@变量
	bool BL_A_set(int i, double value);
	//变量读写-@变量
	bool BL_A_read(int i, double& ans);

	bool set_SYS_G54_G59(int i, vec sys_value);

	bool G54_G59(int i);

	//插补模式-快速
	bool G00();
	//插补模式-线性
	bool G01();
	//插补模式-圆弧
	bool G02();
	//插补模式-圆弧
	bool G03();

	//平面选择
	bool G17();
	bool G18();
	bool G19();
public:
	//插补： 将结果存入缓冲区
	bool Move_cal(vec5 point_in);

public:
	bool move_cal_to_cache(double x, double y, double z, double a, double c);

	//执行缓冲区，缓冲区为空则返回false（先检查，再执行）
	bool move_cache();

	//实际运动计算（坐标改变，求交等）（基础函数-子）
	bool move(vec5 point_mac);

	//设置进给率
	bool F(double f_in);
	//设置转速
	bool S(double S_in);

	//主轴控制-正转
	bool M03();
	//主轴控制-反转
	bool M04();
	//主轴控制-停止
	bool M05();

	//-换刀 --9.9
	bool M06(int tool_using);

	//冷却液
	bool M08();
	//冷却液
	bool M09();

	bool M30();

	//绝对坐标
	bool G90();
	//相对坐标
	bool G91();

#pragma endregion

	//需要做读变量的接口

public:

public:
	vec5 get_mac_sys();
	vec5 get_abs_sys();

public:
	//1-60 默认20
	void set_move_speed(int num);

public:
	bool is_cache_empty();

public:
	//检查变量值 24.2.27 zy
	double check_at_var_value(int index);
	double check_sharp_var_value(int index);
	//初始化机床存放绝对坐标的的变量 24.3.7 zy  
	//  ??? 已经有get_mac_sys(); 说明有地方更新了值
	//获取坐标点 》》计算变量值就是读取对应存放值
	//三中情况要更新对应变量值
	void init_SYS_coor();
	void renew_SYS_coor(vec5 tar_mac, vec5 tar_abs);
	//运动超程检测 24.3.8 zy
	int over_travel_check(vec5 tar_point);

	int get_using_tool();
	void set_using_sl_num_on_slz(int in_sl_num_on_slz);
	int get_using_sl_num_on_slz();

	void clear_cache();  //清空缓存
};

//class NC_Prog_Virtual_Machine_API file_manager
//{
//public:
//	file_manager();
//public:
//	std::string dir;
//	std::string b_name;
//	std::streampos position;
//	std::stack<std::string> file_stack;
//	std::stack<std::streampos> position_stack;
//public:
//	int file_num = 1;
//	bool file_check = 1;
//public:
//    bool file_pos_get(int nc_name);
//    bool save_now_file_pos();//M98使用
//    bool recovery_now_file_pos();
//	//bool file_pos_check();
//	//void file_name_get();
//	//M99使用
//};
