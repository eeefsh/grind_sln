#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include"buchang_tance_zi.h"

//功能：将一个工序输入的点所探测的补偿值存放到机床对应变量
//输入对应关系：工序 - 点
//PS: 当前认为可以直接法向探测，AC已经调整到合适位置，
//因此外部输入需要考虑 12.6

class Prog_Manager_API buchang_tance_fu:
	public nc_program_fu
{
public:
	//01 构造与析构
	buchang_tance_fu(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main();
	//03 输入输出变量
	//

	int gx_type_in; //探测的工序类型
	vector<vec3> v_points_in; //一个工序可以对应多个点,G_P
	vector<vec3> v_nors_in;
	vector<double> v_A_in;
	vector<double> v_C_in;

	double dis_safe_in;  //统一成一把刀设置一次
	double dis_start_in;
	double dis_more_in;

	//04 函数调用
	nc_block diaoyong();

	//05 成员子函数
	F_zi_tance_3_axis zi_obj;

	//对外接口
public:
	//设置探测需要的几个距离
	void set_tance_dis(double in_safe, double in_start, double in_more);

private:
	//根据工序类型，探测点在模型的顺序，确定存储位置
	int find_num_BL_pos(int in_gx_type, int in_p_pos);
};

