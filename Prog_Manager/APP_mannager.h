#pragma once
#include"Tool_Base.h"
#include"Tool_Obj.h"
#include"manager_h\MA_031401_NC_Prog_DebugTool.h"


class Prog_Manager_API APP_manager
	: public save_lib
{
#pragma region 基本数据结构
public:

public:
	//刀具程序库
	Tool_lib obj_tool_lib;

	//当前机床砂轮状态
	JC_sl_lib obj_JC_sl_lib;

	//砂轮库
	wheel sl_manager;

	//当前打开的刀具，如果还没有打开则为nullptr
	Tool_Base* cur_tool_ptr;

public:
	APP_manager();
	~APP_manager();
#pragma endregion

	//交互
public:
	//前提刀已经打开 6.10
	string get_cur_tool_name();

	void add_a_tool(int dao_type, string in_name);

	//根据读取的数据新建一把已有刀对象、将刀指针赋值
	//从刀具列表索引中打开，刀具列表链接到存储位置 5.23
	bool open_a_tool(int n_order);
private:
	bool new_a_tool(int dao_type);

#pragma region 仿真
	//仿真
//原始目的只有计算出选择的刀路构建程序树，
//磨削加工位姿也应该是刀具基类
#pragma endregion


public:
	//磨削程序偏置，不偏置在G54零点，x正向为A轴外侧 11.14
	vec3 Prog_NC_move = { 0.0,0.0,0.0 };
	void set_Prog_NC_move(vec3 in_move);

#pragma region 探测功能
public:
	bool is_gen_tance_prog = 0;
	vec3 tance_start_p = { 0.0,0.0,0.0 };
	vec3 tance_few_dis = { 0.0,0.0,0.0 };
	double dis_jiagong_to_tance = 0.0; //相对探测端面往内缩，防止端面不平整度

	//磨削前的定位探测
	void gen_tance_prog_of_first(double dis_safe_in, double dis_start_in, double dis_more_in);
	//探测选定工序
	void gen_tance_prog_of_sel_gx(double dis_safe_in, double dis_start_in, double dis_more_in);
private:
	//根据工序类型拿对应的探测输入 //需要前刀面的法向,刃线改为刀路做输入
	//当前就要考虑每个点的探测AC,,可能存在问题
	void get_a_gx_tance_input(Miller_GX_Base* in_gx_ptr, DL& in_ans_DL, vector<vec3>& ans_v_points, vector<vec3>& ans_v_nors, vector<double>& ans_v_A, vector<double>& ans_v_C);
	//计算工件坐标系下探测点对应绝对坐标系的点，法向，AC, --改为形参，不修改值1.3
	void cal_G_p_tance_AC(vec3 ans_point, mat33 ans_sys, int in_type, double& ans_A, double& ans_C);
#pragma endregion

#pragma region 生成NC程序
public:
	string file_dir = "C:\\ml_240221"; 
	//生成NC程序
	void gen_NC_prog();

#pragma endregion


};



