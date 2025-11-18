#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include"zi_JC_P_tance_3_axis.h"

//可用变量取件1901-1999
class Prog_Manager_API tance_fu_qdm :
	public nc_program_fu
{
public:
	//01 构造与析构
	tance_fu_qdm(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main(); //组织探前刀面流程 25.9.23

	//03 输入输出变量
	vec3 v_p_duan; //端面点
	double len_to_duan; //端面向刀柄长度
	double r_to_axis; //轴心向外半径, JC_Y正
	double ang_xie; //法向由斜角+前角得到
	double ang_qian;

	double A_ans_delta;   //探测点转到垂直面的A值

	//04 函数调用
	nc_block diaoyong();

	//05 成员子函数
	zi_JC_P_tance_3_axis zi_obj;

	//对外接口
public:
	void set_tance_input(vec3 in_v_p_duan, double in_len_to_duan, double in_r_to_axis,
		double in_ang_xie, double in_ang_qian);

//private:
//	//根据工序类型，探测点在模型的顺序，确定存储位置
//	int find_num_BL_pos(int in_gx_type, int in_p_pos);

};

