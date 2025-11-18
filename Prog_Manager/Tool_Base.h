#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"Tool_Canshu.h"
#include"Tool_Base_Members.h"


class List_of_XingXian;
class List_of_HouJiao;
class List_of_LuoXuan;
class List_of_FenDu;
class List_of_GongXu;
class List_of_ShaLun;
class Miller_GX_Base;

class CanShu_Geo_ZQ;
class CanShu_Geo_PD;
class CanShu_Geo_R;
class CanShu_Geo_CX;
class XingCan_GX;


//该文件包含刀具基础类的定义
// 
//1、存储结构决定了只要拿到刀具号，就可以从外存中访问到刀具所有信息

//铣刀基类
class Prog_Manager_API Tool_Base
	: public save_lib
{
public:
	double w_c2g = 0.0; //单独存，修改后，所有刀都用修改值
	//铣刀类型： 0-锥球、1-平底、2-圆角、3-成型
	int type_tool;

public:
	Tool_Base();

	//2 基本数据结构
public:
	Canshu_Tool_GongYong canshu_gg;

	List_of_XingXian* ptr_list_xx;
	List_of_HouJiao*  ptr_list_hj;
	List_of_FenDu*	  ptr_list_fd;
	List_of_LuoXuan*  ptr_list_lx;
	List_of_GongXu*   ptr_list_gx;
	List_of_ShaLun*   ptr_list_sl;

	vector<int> v_sel_gx;

	//3 初始化结构
public:
	virtual void init() = 0;

	//
	void clear_zhu_prog_then_gen();

	void cal_all_list();

	void set_sl_manager(wheel_output* in_ptr);
	//将选定的工序计算出对应刀路数据
	void cal_selected_gx_DL(int flag);//计算程序的状态标志，0-NC、1-2D、2-3D
private:
	void updata_all_obj_cal_state();
	void updata_all_gx_cal_flag(int flag);

	//4 主数据结构
public:
	wheel_output* ptr_sl_manager;
	//选择计算的工序下标
	vector<int> v_select_cal_gx_index;
	//程序树
	fangzhen_zhu* prog_zhu;

	vector<int> v_new_gx_type;

	//5 接口
public:
	void set_type(int in_type);
	//设置几何参数
	//不提成统一形参接口，就要放派生类实现5.19???
	//void set_geo_canshu();
	double get_delta_dis();
	int get_xx_count();

#pragma region 删除list对象
	//只能被成型刀调用 
public:
	//检查选择型线能删除 9.29
	bool check_sel_xx_can_del(int pos);
	bool del_a_xx(int pos);

	bool check_sel_hj_can_del(int pos);
	bool del_a_hj(int pos);

	bool check_sel_fd_can_del(int pos);
	bool del_a_fd(int pos);

	bool check_sel_lx_can_del(int pos);
	bool del_a_lx(int pos);
#pragma endregion


	
#pragma region 工序相关
public:
	//Miller_GX_Base* get_gx(int n_order);
	Miller_GX_Base* get_gx(int n_order);
#pragma region 设置工序参数，及磨削参数
public:
public:
	//修改为值传递，不用在前端new对象
	bool set_n_gx_canshu(int n_order, XingCan_GX* xc_canshu);
	bool get_n_gx_canshu(int n_order, XingCan_GX*& xc_canshu);
public:
	//前后刀磨削不同,重载-工序派生类提供 6.10
	bool set_n_gx_mo_canshu(int n_order, xt_Mo_HDM_CanShu& mo_canshu);
//	bool get_n_gx_mo_canshu(int n_order, xt_Mo_HDM_CanShu& mo_canshu);
	bool set_n_gx_mo_canshu(int n_order, xt_Mo_QDM_CanShu& mo_canshu);
//	bool get_n_gx_mo_canshu(int n_order, xt_Mo_QDM_CanShu& mo_canshu);
private:
	void renew_a_gx_of_xc(int in_pos, XingCan_GX* xc_canshu);
//	void renew_a_gx_of_mo(int n_order, xt_Mo_QDM_CanShu& mo_canshu);
#pragma endregion

#pragma region 工序显示列表
public:
	//提供显示工序列表的接口
	string get_gx_name(int n_order);
	string get_gx_type(int n_order);
	//string get_gx_sl_name(int n_order);//只能提供砂轮id，名称接口由上层提供 6.10
	int get_gx_sl_id(int n_order);
	string get_gx_jingeilv(int n_order);

#pragma endregion

#pragma region 工序的增删改查
public:
	//新建工序，根据当前刀的类型弹出对应对话框
	//全部默认构造出来、然后进行参数修改--管理写文件
	void new_a_gx_and_add_to_list(int gx_pos);   
	//选择砂轮，行号从0开始 
	void set_gx_sl_id(int n_order, int in_sl_id); //内部修改工序最新状态标志 25.9.29
	//修改工序名称，行号从0开始
	void set_new_gx_name(int n_order, string in_name); 

	void save_a_gx_obj_data(int n_order);

public:
	//删除选中工序，从0行开始
	bool del_a_gx(int order_pos);	//删除后，改变更新列表的内容
	//上移工序顺序--更新了工序显示列表，需要重新显示-不调用display
	bool move_up_a_gx(int order_pos); //顺序位置从0开始
	bool move_down_a_gx(int order_pos);

private:
	//不传位置 7.4
	//int new_a_gx(int gx_type, int in_pos); //1、new对象，2、设置name
	int new_a_gx(int gx_type, int in_pos); //1、new对象，2、设置name
	int set_cur_gx_name(string in_name);//数据存储流程部确定??? 6.10
	int save_cur_gx();
#pragma endregion

#pragma endregion
public:
	//设置刀具的安全点
	void set_anquandian(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p);
	Point_by_5axis get_gx_safe_p();
	Point_by_5axis get_sl_safe_p();
	Point_by_5axis get_cx_safe_p();
	
	//
	void set_sample_tool(xt_CanShu_Sample& in_sample);
	//勾选要计算的工序
	void set_sel_cal_gx(vector<int> in_v_sel);

#pragma region id访问接口
public:
	virtual int get_luoxuancao_lx_id() = 0;
	virtual int get_duanchicao_lx_id() = 0; //圆角、平底
	virtual int get_yuanjiaocao_lx_id() = 0;

	virtual int get_hdm_lx_id() = 0; //锥球、圆角
	virtual int get_hdm_pd_duan_lx_id() = 0; //平底-端
	virtual int get_hdm_pd_zhu_lx_id() = 0; //平底-螺

	virtual int get_hdm_hj_id() = 0; //锥球、圆角
	virtual int get_hdm_pd_duan_hj_id() = 0;
	virtual int get_hdm_pd_zhu_hj_id() = 0;
#pragma endregion

#pragma region 参数访问接口
public:
	void get_gonggong_canshu(Canshu_Tool_GongYong& ans_can);
	void set_gonggong_canshu(Canshu_Tool_GongYong& ans_can);
	void set_sample_canshu(double len, double ang);

public:
	virtual void get_cur_tool_canshu(CanShu_Geo_CX& ans_can);
	virtual void get_cur_tool_canshu(CanShu_Geo_ZQ& ans_can);
	virtual void get_cur_tool_canshu(CanShu_Geo_PD& ans_can);
	virtual void get_cur_tool_canshu(CanShu_Geo_R& ans_can);

	virtual void set_cur_tool_canshu(CanShu_Geo_CX& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_ZQ& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_PD& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_R& ans_can);

	virtual double get_D();
	virtual double get_renlen();
	virtual double get_alllen();
	virtual double get_rrr(); //8.21
#pragma endregion


	//6 其他
public:
	void set_gx_sl_pos_in_JC(int n_order, int in_pos);
	bool updata_gx_lastest_by_sl_edit(vector<int>& in_v_sl_id);


#pragma region 存储
private:
	int pos_xx_list;
	int pos_hj_list;
	int pos_lx_list;
	int pos_fd_list;
	int pos_gx_list;

public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		pos,
	//		type_tool,
	//		ptr_list_xx,
	//		ptr_list_hj,
	//		ptr_list_lx,
	//		ptr_list_fd,
	//		ptr_list_gx,
	//		v_select_cal_gx_index
	//	);
	//}
	//构造应该可以删除 6.11 zy ??? todo: 恢复原有的指针模式
	//Tool_Base() = default;
	//Tool_Base(
	//	int _pos,
	//	int _type_tool,
	//	const std::shared_ptr<List_of_XingXian>_ptr_list_xingxian,
	//	const std::shared_ptr<List_of_HouJiao>_ptr_list_houjiao,
	//	const std::shared_ptr<List_of_LuoXuan>_ptr_list_luoxuan,
	//	const std::shared_ptr<List_of_FenDu>_ptr_list_fendu,
	//	const std::shared_ptr<List_of_GongXu>_ptr_list_gongxu,
	//	const vector<int>_v_select_cal_gx_index
	//)
	//	:
	//	pos(_pos),
	//	type_tool(_type_tool),
	//	ptr_list_xx(_ptr_list_xingxian),
	//	ptr_list_hj(_ptr_list_houjiao),
	//	ptr_list_lx(_ptr_list_luoxuan),
	//	ptr_list_fd(_ptr_list_fendu),
	//	ptr_list_gx(_ptr_list_gongxu),
	//	v_select_cal_gx_index(_v_select_cal_gx_index)
	//{}

#pragma endregion

public:
	int pos;	//自身存储位置
	int save();
	virtual void load();
	int save_all();
	void set_pos(int in_pos);

};



//只管理号 或者id
//将刀具列表相关的内容打包
class Prog_Manager_API Tool_lib
	: public save_lib
{
public:
	Tool_lib();
	//文件中存在空行，按顺序读取不适用，该类沿用加载所有显示列表的模式
	//显示内容不进行存储 6.10 
private:
	vector<string> v_tool_name;	//刀具名称
	vector<string> v_tool_time;	//更新时间
	vector<string> v_tool_type;	//刀具类型
	vector<int> v_tool_pos;		//刀具存储位置

public:
	//刷新显示列表
	void display_tool_list();
	//按照指定类型刷新
	void display_tool_list_by_type(int in_type);

public:
	//
	int count();
	//
	int get_tool_pos(int n_order); 
	//
	string get_name(int n_order);
	//
	string get_time(int n_order);
	//
	string get_type(int n_order);

public:
	//增加一把刀的数据,写入文件，时间自动
	int add_a_row_data(int dao_type, string in_name);
	//修改刀具名称，行号从0开始
	void edit_name(int n_order, string in_name);
	//
	void del_a_tool(int n_order);

private:
	void get_tool_name(int in_pos, string& ans_name);
	void get_tool_time(int in_pos, time_updata& cur_tm);
	void time_to_string(time_updata cur_tm, string& s_time);
	void tool_type_to_string(int in_type, string& s_type);
};

//存储当前机床上的砂轮情况
class Prog_Manager_API JC_sl_lib
	: public save_lib
{
public:
	JC_sl_lib();

	//设置的时候
public:
	void load_slz(int n_order, int in_slz_num); 
	void unload_slz(int n_order); //砂轮组号 = -1

	//显示时候
public:
	int count(); //默认 = 6
	int get_slz_id(int n_order);

	//用的时候
public:
	bool is_slz_on(int n_order);
};
