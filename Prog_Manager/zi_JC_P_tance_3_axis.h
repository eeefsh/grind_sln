#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/MA_031301_NC_Prog_Block_Prog_Struct.h"
#include"nc_frame.h"

class Prog_Manager_API zi_JC_P_tance_3_axis:
	public nc_program_zi
{
public:
	//01 构造与析构
	zi_JC_P_tance_3_axis(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main();

	//03 输入输出变量
	//输入变量
	nc_block_vec3 tc_JC_P_in; 
	nc_block_vec3 tc_JC_N_in; 
	nc_block tc_A_in; 
	nc_block tc_C_in; 
	nc_block tc_safe_plane_in;

	//输出变量
	nc_block_vec3 tc_JC_P_out;


	//04 函数调用
	nc_block diaoyong(nc_block_vec3& tc_JC_P, nc_block_vec3& tc_JC_N, 
		nc_block& tc_A, nc_block& tc_C, nc_block& tc_safe_plane,
		nc_block_vec3& ans_tc_JC_P);

	//05 成员子函数

	//06 系统使用函数
	//nc_frame内定义
public:
	nc_block detectP(nc_block_vec3 p, nc_block_vec3 n, nc_block an, nc_block cn, nc_block safe_plane, nc_block_vec3 ans_p);

	nc_block detectShake();

	nc_block detectCompensateError(nc_block_vec3 targ_n, nc_block error_probe);

	nc_block detectArriveLocalSafe(nc_block_vec3 p, nc_block safe_plane);

	nc_block detectBackLocalSafe(nc_block safe_plane);;
};

