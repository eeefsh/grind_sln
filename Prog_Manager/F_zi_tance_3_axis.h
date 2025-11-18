#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/MA_031301_NC_Prog_Block_Prog_Struct.h"

//#include"G_zi_back_safe_pos.h"

//类-三轴探测，A/C必须按戴杰的定义输入（而非机标定义）
class Prog_Manager_API F_zi_tance_3_axis :
    public nc_program_zi
{
public:
	//01 构造与析构
	F_zi_tance_3_axis(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main();

	//03 输入输出变量
		//输入变量
	nc_block tc_G5X_in; //用 G56 = 2.0
	nc_block tc_back_safe_global_in; //控制是否回全局安全位置，1表示回，设置G57
	nc_block tc_safe_G5X_in;   //G57 =3.0
	nc_block tc_back_safe_local_in; //控制是否回局部安全位置
	nc_block tc_need_cu_in;  //控制粗探开关

	nc_block_vec3 tc_targ_point_in;
	nc_block tc_A_in;
	nc_block tc_C_in;
	nc_block_vec3 tc_targ_N_in;

	nc_block tc_dis_safe_in;  //1.0
	nc_block tc_dis_start_in;  //10.0
	nc_block tc_dis_more_in;  //max5.0

	//输出变量
	nc_block_vec3 tc_ans_point_out;

	//04 函数调用
	nc_block diaoyong(
		nc_block& tc_G5X, nc_block& tc_back_safe_global, nc_block& tc_safe_G5X, nc_block& tc_back_safe_local, nc_block& tc_need_cu,
		nc_block_vec3& tc_targ_point,nc_block& tc_A,nc_block& tc_C,nc_block_vec3& tc_targ_N,
		nc_block& tc_dis_safe,nc_block& tc_dis_start,nc_block& tc_dis_more,
		nc_block_vec3& tc_ans_point
	);

	//05 成员子函数
	//G_zi_back_safe_pos back_safe_pos;
	//06 系统使用函数
	nc_block choose_G5X(nc_block& G5X);
	nc_block xiaoxi();
	nc_block goto_anquan_pos_by_Y_XYZ();
	nc_block tc_inner_X_coorMac();
	nc_block tc_inner_Y_coorMac();
	nc_block tc_inner_Z_coorMac();
	nc_block tc_inner_A_coorMac();
	nc_block tc_inner_C_coorMac();
	nc_block tc_inner_X_coorAbs();
	nc_block tc_inner_Y_coorAbs();
	nc_block tc_inner_Z_coorAbs();
	nc_block tc_inner_A_coorAbs();
	nc_block tc_inner_C_coorAbs();
	nc_block tc_tance_done();
};

