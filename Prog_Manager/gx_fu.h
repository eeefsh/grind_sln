#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/xt_armadillo_settings.h"
#include"manager_h/MA_031301_NC_Prog_Block_Prog_Struct.h"
#include"TooL_canshu_2.h"
#include"void_zi.h"


using namespace arma;
class xt_CanShu_MoXue_ZhenLie;


class Prog_Manager_API Miller_DL_fu_prog :
	public nc_program_fu
{
public:
	//01 构造与析构
	Miller_DL_fu_prog(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main();

	//03 输入输出变量
	//DL_fu_prog gx_DL;	//其他属性+砂轮-去除工件坐标系
	//刀路指针、循环阵列参数 6.15
	DL* ptr_DL;
	int sl_pos_in_JC_lib;
	int sl_pos_in_slz;
	int gx_type;
	xt_gx_shalun sl_canshul;
	//阵列参数只需要分度度对应位置 6.20
	vector<double> v_fd;
	int selected_ren[6];//工序勾选刃，替代阵列 9.2
	Point_by_5axis gx_safe_point;
	Point_by_5axis sl_safe_point;

	double SL_zhuansu;
	CanShu_SuDu sudu_lilun;

	//将刀路数据转换为副程序刀路,增加工序类型12.5
	void set_gx_DL(int in_gx_type, DL* in_DL, 
		int in_sl_pos_JC_lib, int in_sl_pos_slz, 
		xt_gx_shalun& in_sl, vector<double>& in_v_fd);
	//void set_gx_DL(int in_gx_type, DL& in_DL, int in_sl_pos_JC_lib, int in_sl_pos_slz, CanShu_shalun_cal_DL& in_sl, Point_by_5axis& in_anquandian);
	//将当前刀路使用的砂轮换上
	void trans_sl_to_M06();
	//将副程序刀路解算为砂轮参考点的G01 ，可实现砂轮的参数补偿 8.25
		//副程序有不同类型，type 不同，生成G代码模式不同 6.14 ????
	void trans_DL_to_G01();

	void set_jingeilv(CanShu_SuDu in_sudu);

	//04 函数调用
	nc_block diaoyong();

	//05 成员子函数
	//void_zi zi_obj;
private:
	//根据工序类型判断是否刃线有球
	int is_has_qiu_car_gx(int in_gx_type);

	//根据工序类型分配补偿值对应机床变量号
	//按照工序顺序，从1650开始，每个工序不等
	void set_num_in_JC_BL(int in_gx_type, int& num1, int& num2, int& num3, int& num4);
	//根据点(工件坐标系)计算所在刃线模型的位置
	double cal_p_in_bu_mode_pos(vec3 in_p);

};


class Prog_Manager_API Miller_DL_fu_prog2;