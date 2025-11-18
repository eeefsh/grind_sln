#ifdef NC_Prog_visualize_manager_EXPORTS
#define NC_Prog_visualize_manager_API __declspec(dllexport)
#else
#define NC_Prog_visualize_manager_API __declspec(dllimport)
#endif

#include"GLlist_JiChuang.h"
//#include"manager_h/MA_040295_GL_Machine.h"
//#include"manager_h/MA_010101_NC_Prog_WorkPart.h"
#include"manager_h/MA_010101_NC_Prog_Show_WorkPart_and_ShaLun.h"
#include"manager_h/MA_010101_NC_wheel_data.h"
#include"manager_h/MA_010101_NC_RotateShow.h"
#include"manager_h/MA_040101_GL_MatrixCtrl.h"
#include"manager_h/MA_030201_NC_Prog_Virtual_Machine.h"



class NC_Prog_visualize_manager_API visualize_manager
{
public:
	bool is_lookat_gongjian = 1; //固定工件视口
	vec3 pos_gj_trans = { 0.0,0.0,-4.0 };//在机床0点，正面观察工件运动 x右平移 , y上平移, z+长度缩短

public:
	//12.22 增加鼠标视图控制类
	tcGLMatrixCtrl* mat_ctrl;	//控制改变view 

public:
	wheel_output* sl_manager;	//砂轮组指针 只用来获取数据
	//int sl_id; //根据id在砂轮库取数据 6.20 ???

	GLlist_JiChuang* jichuang_gl_ptr;	//gl机床指针

	gongjian* gj_data_ptr;	//工件数据指针
	//砂轮数据指针 用于计算碰撞，外形由砂轮组获取
	shalun* sl_data_ptr;

	tanzhen_Z* tanzhen_Z_ptr;

	virtual_machine* vir_mac_ptr;
public:
	show_send* gj_gl_stl;
	show_send* gj_gl_cut;
	//show_send* gj_gl_mesh;

	show_send* gj_gl_cutted;

	show_send* sl_gl_ptr;

public:
	bool is_show_mesh = false; //test 显示最终网格

	//管理部件显示开关  对接界面交互控制
	void set_hide_parts(vector<bool>& v_hide);

	//探针开关  打开时检测 探针与工件 
	bool is_tance = false;

public:
	visualize_manager();
	~visualize_manager();

public:
	//初始化工件， 输入stl文件路径，精度
	//trans  （x角度，y角度，z角度，x平移， y平移，z平移）
	//xyz相对于绝对坐标系不是自身坐标系，旋转的顺序为：xyz；
	void init_gj_by_stl(string file, vec trans, double acc_d);
	//初始化工件， 输入圆柱形参数(直径D、长度len)、精度
	void init_gj_by_col(double D, double len, double acc_d);
	//初始化工件， 输入回转形工件dxf文件，离散精度
	void init_gj_by_dxf(string file, double acc_d);
	//初始化工件， 输入回转形工件外形轮廓，离散精度
	void init_gj_by_rot(mat& gj_outline, double acc_d);

public:
	//加载砂轮数据，用于碰撞，用于显示
	void load_shalun(int slz_id, int sl_id);
	void unload_shalun();

	//初始视口位置
	void init_mat_ctrl(tcGLMatrixCtrl* ptr);
	//设置视口矩阵
	void set_view_mat(mat44& view);
	//设置机床位置矩阵
	void set_base_mat(mat44& base);
	//计算工件在A轴上的装夹矩阵 外露长度
	void cal_gj_clamp_mat(mat44& matA, double out_len);
	//计算砂轮在Z轴上的装夹矩阵 外露长度
	void cal_sl_clamp_mat(mat44& matZ, double out_len);
	//显示当前系统状态 
	//参数1：五个机床内部轴坐标
	//参数2：机床位置
	//参数3：视角位置
	bool show_now_state(vec5& ls_mac_sys, vec5& ls_abs_sys, int color, mat44& base, mat44& view);

	bool show_end_state(vec5& ls_mac_sys, vec5& ls_abs_sys, int color, mat44& base, mat44& view);
private:
	//初始化砂轮组，砂轮组在界面交互时，构造增加砂轮
	void init_wheel_group_peng_data(int sl_id);
	//计算初始视口矩阵
	void cal_scale(vec3& ls_scale, vec3& p);

	//计算各坐标轴物体位置矩阵
	void cal_axis_pos_mat(vec5& ls_mac_sys,
		mat44& base,
		mat44& matX,
		mat44& matY,
		mat44& matZ,
		mat44& matA,
		mat44& matC);

	//void cal_AZ_axis_mat(vec5& ls_mac_sys, mat& base_in, mat& matA, mat& matZ);
	void cal_gongjian_abs_mat(vec5& ls_abs_sys, mat44& base_in ,mat44& gongjian_mat);
	void cal_shalun_abs_mat(vec5& ls_abs_sys, mat44& base_in, mat44& shalun_mat);

	void cal_gongjian_mac_mat(vec5& ls_mac_sys, mat44& base_in, mat44& gongjian_mat);
	void cal_shalun_mac_mat(vec5& ls_mac_sys, mat44& base_in, mat44& shalun_mat);
	//工件 -A  砂轮 - Z 位置
	void cal_cut_sport(mat44& A, mat44& Z, int color);

	//检查部件间的碰撞 不包括工件与砂轮
	bool check_all_prat_peng();
	//3*2矩阵，xyz最大最小
	bool check_two_prat_AABB_peng(mat& A_box, mat& B_box);
	//显示系统各部件
	void show_parts(vec5& ls_mac_sys, vec5& ls_abs_sys, mat44& base);

private:
	bool check_peng_Ztanzhen_and_gj(mat44 mat_a, mat44 mat_z);
	bool check_peng_point_and_box(vec3 tz_point, mat44 mat_a, octree* cur_box);
	//提供查看探针碰撞时，机床数据,直接访问虚拟机存的
	void tc_inner_ABS(vec5& abs_coor);
	void tc_inner_MCA(vec5& mac_coor);
};