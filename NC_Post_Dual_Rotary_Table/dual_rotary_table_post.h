#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif

#include"pch.h"
#include"Para_Point_Basic.h"
#include"Para_Tools.h"
#include"Para_Machine.h"
#include"Para_Coord_Values.h"
#include"Para_State_A.h"

//函数用于ISO标准双转台机床的后处理解算，基础场景
//输入：
//	Para_Path:刀路参数（G_O/G_N/G_SYS_D）
//  Para_State_A A轴状态参数:/A_before
//	Para_Machine:机床参数（GC_SYS_G/GC_O_G/W_c2g）
//	Para_Coord_Values：机床五轴坐标（JC_O_DC/An/C）
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
//版本信息：20240412_wld_修改
void NC_Post_Dual_Rotary_Table_API create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Point,
	Para_State_A& Para_State_A,
	Para_Machine& Para_Machine,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values
);


//函数用于ISO标准双转台机床的后处理解算，非圆磨削场景
//输入：
//	Para_Path:刀路参数（G_O/G_N/G_SYS_D/A_before/C_before）
//	Para_Coord_Values：机床五轴坐标（JC_O_DC/An/C）
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Point,
	Para_State_A& Para_State_A,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values);


//函数用于ISO标准双转台机床的后处理解算，快速计算场景
//输入：
//	Para_Path:刀路参数(G_O/G_N/G_SYS_D/A_before/C_before）
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Point,
	Para_State_A& Para_State_A,
	Para_Coord_Values& Para_Coord_Values);


//函数用于ISO标准双转台机床的后处理解算
//输入：
//	目标点：G_O_in-目标点，G_N_in-目标法向，G_SYS_D_in-刀具位姿（工件坐标系下）
//	机床参数：GC_SYS_G_in-夹具坐标系位姿，GC_O_G_in-夹具坐标系（原点）偏移，w_c2g_in-AC轴偏心距
//	刀具参数：r_sl_in-砂轮圆角半径，d_sl_in-砂轮直径，fl_sl_in-砂轮法兰长度
//	上一步刀路：A_before_in-上一步解算A坐标值，C_before_in-上一步解算C坐标值
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_dual_rotary_table_post_process(
	vec3& G_O, vec3& G_N, mat33& G_SYS_D,
	mat33& GC_SYS_G, vec3& GC_O_G, double& w_c2g,
	double& r_sl, double& d_sl, double& fl_sl,
	double& A_before, double& C_before,
	vec3& JC_O_DC, double& An, double& Cn);




//函数用于戴杰机床的后处理解算
//输入：
//	Para_Path:刀路参数（G_O/G_N/G_SYS_D/A_before/C_before）
//  Para_State_A A轴状态参数:/A_before
//	Para_Coord_Values：机床五轴坐标（JC_O_DC/An/C）
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_daijie_post_process(
	Para_Point_Basic& Para_Point,
	Para_State_A& Para_State_A,
	Para_Machine& Para_Machine,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values);



//函数用于ISO标准双转台机床的后处理解算
//输入：
//	目标点：G_O_in-目标点，G_N_in-目标法向，G_SYS_D_in-刀具位姿（工件坐标系下）
//	上一步刀路：A_before_in-上一步解算A坐标值，C_before_in-上一步解算C坐标值
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_dual_rotary_table_post_process(
	vec3& G_O, vec3& G_N, mat33& G_SYS_D,
	double& A_before, double& C_before,
	vec3& JC_O_DC, double& An, double& C);


//函数用于戴杰双转台机床的后处理解算
// 戴杰机床的AC轴方向与ISO标准机床相反
//输入：
//	目标点：G_O_in-目标点，G_N_in-目标法向，G_SYS_D_in-刀具位姿（工件坐标系下）
//	机床参数：GC_SYS_G_in-夹具坐标系位姿，GC_O_G_in-夹具坐标系（原点）偏移，w_c2g_in-AC轴偏心距
//	刀具参数：r_sl_in-砂轮圆角半径，d_sl_in-砂轮直径，fl_sl_in-砂轮法兰长度
//	上一步刀路：A_before_in-上一步解算A坐标值，C_before_in-上一步解算C坐标值
//输出：
//	JC_O_DC_out-机床XYZ坐标，An_out-机床A坐标，C_out-机床C坐标
//版本信息：工研所_重点实验室_zyw_202404
void NC_Post_Dual_Rotary_Table_API create_daijie_post_process(
	vec3& G_O, vec3& G_N, mat33& G_SYS_D,
	mat33& GC_SYS_G, vec3& GC_O_G, double& w_c2g,
	double& r_sl, double& d_sl, double& fl_sl,
	double& A_before, double& C_before_,
	vec3& JC_O_DC, double& An, double& Cn);


