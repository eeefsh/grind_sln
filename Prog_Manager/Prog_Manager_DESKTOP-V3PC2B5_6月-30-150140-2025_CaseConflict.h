#pragma once
#include"Tool_Base.h"

#include"manager_h/MA_031401_NC_Prog_DebugTool.h"
#include"manager_h/MA_010101_NC_Prog_visualize_manager.h"
#include"manager_h/MA_010101_jiemian_show.h"
#include"manager_h/MA_010101_NC_wheel_Intersecting_line.h"
#include"manager_h/xt_glfw_setting.h"

class  fangzhen_3D;
class  fangzhen_2D;


class Prog_Manager_API Prog_manager
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
	wheel_output sl_manager;

	//当前打开的刀具，如果还没有打开则为nullptr
	Tool_Base* cur_tool_ptr;

public:
	Prog_manager();
	~Prog_manager();
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

public:
	vector<int> check_sl_is_on_lib();

#pragma region 仿真
	//仿真
//原始目的只有计算出选择的刀路构建程序树，
//磨削加工位姿也应该是刀具基类
public:
	//磨削程序偏置，不偏置在G54零点，x正向为A轴外侧 11.14
	vec3 Prog_NC_move = { 0.0,0.0,0.0 };
	void set_Prog_NC_move(vec3 in_move);

	fangzhen_3D* FZ_3D;


	fangzhen_2D* FZ_2D;
public:
	fangzhen_zhu* get_zhu_prog();

#pragma endregion

#pragma region 生成NC程序
public:
	string file_dir = "C:\\ml_240221";
	//生成NC程序
	void gen_NC_prog();

#pragma endregion


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

public:
	int get_new_gx_type(int order);
	string get_new_gx_name(int order);
	vector<string> v_gx_name_show;
private:
	void init_gx_type_name();
};



class Prog_Manager_API fangzhen_3D
{
public:
	//mat44 view_mat;		//视角位置  
	//mat44 base_mat;
public:
	fangzhen_3D();	//相关指针赋值 
	~fangzhen_3D();
public:
	//定义相关指针
	debug_tool* debug_tool_ptr;		//调试器
	//virtual_machine* machine_ptr;	//虚拟机
	visualize_manager* vis_manager_ptr;	//可视化管理
	fangzhen_zhu* zhu_fu_zi_prog_ptr;	//主副子程序

	int using_sl_num_3D = -1;
	int using_sl_pos = -1;
#pragma region 6工位砂轮库
public:
	//砂轮组id
	vector<int> sl_lib_3D;  //size = 6
	vector<vector<int>> sl_lib_on_sl_num; //每个砂轮组的上对应的砂轮key //最多18个砂轮 = 6*3
	//需要根据砂轮num，得到用哪个工位的砂轮组

	//一旦初始化完成，就和软件程序脱离关系，就要构建砂轮的索引关系
	void init_sl_lib_3D(Prog_manager* in_prog_ptr);
	//从仿真砂轮库中将显示外形设置好
	//bool change_sl(int sl_num);
	bool change_sl(int slz_pos, int in_sl_pos);
#pragma endregion

	//前端使用
public:
	void init(tcGLMatrixCtrl* mat_ptr, Prog_manager* in_prog_ptr);
	void set_show(vec& in_trans);

public:
	bool fangzhen_process();

	//可设置为私有

public:
	//只接stl --只有stl导入的工件坐标系不同，其他方式在同坐标系下构建的 8.21
	bool set_gj_by_stl_and_trans_pos(string in_dir, double in_acc_d, vec& in_trans);
	//圆柱形工件参数设置,
	bool set_gj_by_col_and_trans_pos(double D, double len, double in_acc_d);
	//工件外形为回转纵截面轮廓线由刀具参数得到，长度为刃长
	bool set_gj_by_rot_and_trans_pos(double D, double zhui, double len_ren, double len_all, double D_bing, double in_acc_d);

public:
	//显示计算的砂轮数据都由，工序对应的砂轮键号得到
	bool set_shaluncanshu(int in_slz_id, int in_sl_id);	//需要砂轮组的相关参数
	//设置主副子程序，复位操作需要
	bool set_fangzhen_zhu(fangzhen_zhu* in_ptr);
	//设置仿真环境的调试器，调试器要求已经设置好虚拟机
	bool set_debug_tool(debug_tool* in_debug);


	//仿真控制
private:
	//bool reset_button = 0;
	//bool play_or_pause = 0;	//1-播放、0-暂停
	//bool run_one = 0; //1-单步、0-全步

public:
	//void set_button_reset();
	void set_button_play();
	void set_button_pause();
	//void set_button_run_one();
	void set_button_reset_move_prog(); //工件没有复位

public:
	//隐藏部件，将选择部件信息传递到gl_jichuang
	void hide_parts(vector<bool>& v_hide);
public:
	//复位所有状态 //重新初始化工件及程序内容，挂上新的程序

	//reset_prog();
	//set_fangzhen_zhu();
#pragma region 复位参数
	//复位需要恢复工件的数据
	int cur_gj_init_type;
	double acc_d;
	vec trans_init;
	string gj_stl;

	double col_D;
	double col_len;

	double rot_D;
	double rot_zhui;
	double rot_len_ren;
	double rot_len_all;
	double rot_D_bing;
#pragma endregion

};


class Prog_Manager_API fangzhen_2D
{
public:
	fangzhen_2D();	//相关指针赋值
	~fangzhen_2D();	//相关指针赋值

public:
	double sf = 1;
	double tx = 0;
	double ty = 0;
	mat44 ls;
public:
	//定义相关指针
	debug_tool* debug_tool_ptr;		//调试器

	//鼠标视图控制类
	tcGLMatrixCtrl* mat_ctrl;

	//2D显示类
	int using_slz_num_2D;
	int using_sl_pos = -1;
	jiemian_show* show_ptr;
	Simulation2D vis_2D_manager;

	fangzhen_zhu* zhu_fu_zi_prog_ptr;	//主副子程序

	//按键控制
private:
	//bool reset_button = 0;
	//bool play_or_pause = 0;	//1-播放、0-暂停
	//bool run_one = 0; //1-单步、0-全步

	//int count_run_one = 0; //单步计数
	//int count_run_one_pre = -1;

	//int count_clear_screen = 0;
public:
	void set_button_reset();
	void set_button_play();
	void set_button_pause();
	void set_button_run_one();
	void set_button_clear_screen(); //单独按钮，缩放调用


#pragma region 6工位砂轮库
public:
	//存放砂轮的外形轮廓
	vector<vector<mat>> sl_lib_2D; //最多18个砂轮
	vector<vector<int>> sl_lib_on_sl_num; //6*(0-2)

	//一旦初始化完成，就和软件程序脱离关系，就要构建砂轮的索引关系
	void init_sl_lib_2D(Prog_manager* in_prog_ptr);

	//从仿真砂轮库中将显示外形设置好  
	//todo:--内部需要设置砂轮端面长度 9.24
	bool change_sl(int slz_num, int in_sl_pos);

	//每次换砂轮，对应的lenth_ckd_to_outface会变，
	//存放每个执行工序的长度，换刀时挨个更新。复位时更新索引
	//prog_manager直接准备好
public:
	vector<double> v_gx_lenth_ckd_to_inface;
	int index_ckd_out_face = 0; //执行工序外断面索引

	double lenth_ckd_to_inface;
	//设置砂轮端面长度需要的参数：法兰，厚度，圆角，内外
	void set_sl_duan_len(double fl, double hou, double r, int in_out_mo);
#pragma endregion

	//前端使用
public:
	void init(tcGLMatrixCtrl* mat_ptr, Prog_manager* in_prog_ptr);
	void set_show(double dlg_len,double dil_high, double in_xishu);

public:
	bool fangzhen_process();

	//可设置为私有
public:
	void set_mat_ctrl(tcGLMatrixCtrl* ptr);
	//设置主副子程序，复位操作需要
	bool set_fangzhen_zhu(fangzhen_zhu* in_ptr);
	//设置仿真环境的调试器，调试器要求已经设置好虚拟机
	bool set_debug_tool(debug_tool* in_debug);

public:
	//设置砂轮外形，保存要可更换
	bool set_sl_outline(mat& sl_outline);	//需要砂轮组的相关参数
	//设置工件直径、长度
	void set_gj_D_and_lenth(double gj_D, double gj_len);
	//设置截面的参考点及法向，输入vec8 = {n, p，旋转（Z+），偏移}
	//法向Z轴为工件回转轴{0,0,1}，刀尖指向刀柄
	void set_gj_jiemian(vec trans);  //0-空间任意点为参考时，调用

public:
	//该部分是为了得到与刃线上选择点垂直的界面
	//Miller_RenXian renxian_of_ckd;
	//设置当前工序仿真的刃线数据，默认给0号位的、11.19
	//要求：1-点2D就调用、2-多类型工序，给第一个。主要用于测试
	void set_renxian_of_ckd(Prog_manager* in_prog_ptr);

	bool ckd_type = 0; //0-空间任意，1-来自刃线
	vec trans_look_gj; //vec8 = { n, p，旋转（Z + ），偏移 }
	//根据长度,平面(0法向，1径向)，构造vec8。选取刃线上Z坐标最近的点(不改偏移)
	void set_gj_look_jiemian(double in_len, int in_n_or_d);
public:
	//距离测量缩放系数
	double xishu_ce_dis = 0.0;
	//dis = 像素距离 * （1/系数）*（2/730）



private:
	void trans_vec5_to_mat44(vec5 cur_coor, mat44& temp);
	void cal_gongjian_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& gj_abs_sys);
	void cal_shalun_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& sl_abs_sys);

	void cal_SL_to_GJ(mat44& gj_abs_sys, mat44& sl_abs_sys, mat44& gj_sys_sl);
};

