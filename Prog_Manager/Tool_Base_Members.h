#pragma once


//该文件包含刀具类基本成员的类定义
#include "manager_h/xt_armadillo_settings.h"
#include <queue>
#include "Tool_Geo_Obj.h"
#include "Tool_Canshu.h"
#include "Miller_GX_Base.h"

using namespace std;

class Prog_Manager_API GongYong_Canshu;
class Prog_Manager_API List_of_XingXian;
class Prog_Manager_API List_of_FenDu;
class Prog_Manager_API List_of_LuoXuan;
class Prog_Manager_API List_of_HouJiao;
class Prog_Manager_API List_of_GongXu;

class Prog_Manager_API Miller_gx_base;

class Prog_Manager_API Cal_XingXian;
class Prog_Manager_API Cal_LouXuan;
class Prog_Manager_API Cal_FenDu;
class Prog_Manager_API Cal_QDM;
class Prog_Manager_API Cal_HouJiao;



//型线表
class Prog_Manager_API List_of_XingXian
	: public save_lib
{
	//1 基本设置接口
public:


	//2 基本数据结构
public:
	obj_list_data base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:
	int pos=-1; //与刀同步 6.15 
	Tool_Base* ptr_tool; //为了传给列表中的对象 6.12
	vector<Cal_XingXian*>  v_obj_ptr;

	//5 结果计算接口
public:
	bool add_obj(string name, string file_dir, CanShu_XingXian canshu_obj);
	bool edit_obj(int show_order, string name, string file_dir, CanShu_XingXian canshu_obj);
	bool del_obj(int show_order);
	bool get_obj(int show_order, string& name, string& file_dir, CanShu_XingXian& canshu_obj);
	
	Cal_XingXian* get_obj(int in_id);
	int get_count();
	bool swap_order(int order_1, int order_2);
	void cal_self();




	//6 其他
public:
	List_of_XingXian();
	~List_of_XingXian();

public:
	int save();
	void load();
	void init_guanxi();
};

//分度表
class Prog_Manager_API List_of_FenDu
	: public save_lib
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	obj_list_data base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:
	Tool_Base* ptr_tool;
	vector<Cal_FenDu*>  v_obj_ptr;

	//5 结果计算接口
public:
	bool add_obj(CanShu_FenDu in_data);
	bool edit_obj(int show_order, CanShu_FenDu in_data);
	bool del_obj(int order);
	bool swap_order(int order_1, int order_2);
	bool get_obj(int show_order, CanShu_FenDu& in_data);

	Cal_FenDu* get_obj(int in_id);
	int get_count();
	void cal_self();
public:
	List_of_FenDu();
	~List_of_FenDu();

public:
	int pos; //自身存储位置
	int save();
	void load();

public:
	void init_guanxi();
};

//螺旋表
class Prog_Manager_API List_of_LuoXuan
	: public save_lib
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	obj_list_data base_data;
	vector<int> v_pos;
	//3 初始化结构
public:

	//4 主数据结构
public:
	Tool_Base* ptr_tool;

	queue<int> empty_index;
	vector<Cal_LouXuan*>  v_obj_ptr;


	//5 结果计算接口
public:
	bool add_obj(CanShu_LuoXuan in_data);
	bool edit_obj(int show_order, CanShu_LuoXuan in_data);
	bool del_obj(int show_order);
	bool swap_order(int order_1, int order_2);
	bool get_obj(int show_order, CanShu_LuoXuan& in_data);

	Cal_LouXuan* get_obj(int in_id);
	int get_count();

	void cal_self();

	//6 其他
public:
	List_of_LuoXuan();
	~List_of_LuoXuan();

	int get_n_lx_type(int index);

private:
//public:
//	template <class Archive>
//	void serialize(Archive& ar) {
//		ar(count, empty_index, v_list);// 需要单独处理指针序列化);
//	}
//	List_of_LuoXuan() = default;
//	List_of_LuoXuan(
//		int _count,
//		const std::queue<int>& _empty_index,  // 使用const引用
//		const std::vector<std::shared_ptr<Cal_LouXuan>>& _v_list
//	) : count(_count),  empty_index(_empty_index), v_list(_v_list)
//	{}

public:
	int pos; //自身存储位置
	int save();
	void load();
	void init_guanxi();
};

//后角表
class Prog_Manager_API List_of_HouJiao
	: public save_lib
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	obj_list_data base_data;
	vector<int> v_pos;
	//3 初始化结构
public:

	//4 主数据结构
public:
	Tool_Base* ptr_tool;

	queue<int> empty_index;
	vector<Cal_HouJiao*>  v_obj_ptr;
	// 修改v_list类型
	//std::vector<std::shared_ptr<Cal_HouJiao>> v_list;

	//5 结果计算接口
public:
	bool add_obj(CanShu_HouJiao in_data);
	bool edit_obj(int show_order, CanShu_HouJiao in_data);
	bool del_obj(int show_order);
	bool swap_order(int order_1, int order_2);
	bool get_obj(int show_order, CanShu_HouJiao in_data);


	Cal_HouJiao* get_obj(int in_id);

	int get_count();

	void cal_self();
	//6 其他
public:
	List_of_HouJiao();
	~List_of_HouJiao();


public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(count, empty_index, v_list);// 需要单独处理指针序列化);
	//}
	//List_of_HouJiao() = default;
	//List_of_HouJiao(
	//	int _count,
	//	const std::queue<int>& _empty_index,  // 使用const引用
	//	const std::vector<std::shared_ptr<Cal_HouJiao>>& _v_list
	//) : count(_count), empty_index(_empty_index), v_list(_v_list)
	//{}

public:
	int pos; //自身存储位置
	int save();
	void load();
	void init_guanxi();
};

//工序表
class Prog_Manager_API List_of_GongXu
	: public save_lib
{
	//1 基本设置接口
public:
	void add_obj(Miller_GX_Base* in_data);

	//2 基本数据结构
public:
	obj_list_data base_data;
	vector<int> v_pos;
	//3 初始化结构
public:

	//4 主数据结构
public:
	Tool_Base* ptr_tool;

	queue<int> empty_index;
	vector<Miller_GX_Base*>  v_obj_ptr;


	//5 结果计算接口
public:
	void cal_self();

	bool add_obj(int type, string name);
	bool del_obj(int order);
	bool swap_order(int order_1, int order_2);


	bool get_obj_gongxu_name(int show_index, string& name);
	bool set_obj_gongxu_name(int show_index, string& name);
	bool get_obj_gongxu_data(int show_index, save_lib* p);
	bool set_obj_gongxu_data(int show_index, save_lib* p);
	bool get_obj_gongxu_basedata(int show_index, gx_base_canshu& data);
	bool set_obj_gongxu_basedata(int show_index, gx_base_canshu& data);

	//bool get_obj_gongxu_miller_canshu(int show_index, char* p, int size);
	//bool set_obj_gongxu_miller_canshu(int show_index, char* p, int size);
	//bool get_obj_gongxu_mo_mian_canshu(int show_index, char* p, int size);
	//bool set_obj_gongxu_mo_mian_canshu(int show_index, char* p, int size);
	
	bool get_obj_gongxu_range(int show_index, xt_CanShu_Range& data);
	bool set_obj_gongxu_range(int show_index, xt_CanShu_Range& data);
	bool get_obj_sample(int show_index, xt_CanShu_Sample& data);
	bool set_obj_sample(int show_index, xt_CanShu_Sample& data);
	bool get_obj_gongxu_jintuidao(int show_index, xt_CanShu_JinTuiDao& data);
	bool set_obj_gongxu_jintuidao(int show_index, xt_CanShu_JinTuiDao& data);
	bool get_obj_gongxu_bianhuan(int show_index, xt_CanShu_MoXue_BianHuan& data);
	bool set_obj_gongxu_bianhuan(int show_index, xt_CanShu_MoXue_BianHuan& data);
	bool get_obj_gongxu_xunhuan(int show_index, xt_CanShu_MoXue_XunHuan& data);
	bool set_obj_gongxu_xunhuan(int show_index, xt_CanShu_MoXue_XunHuan& data);
	bool get_obj_gongxu_zhenlie(int show_index, xt_CanShu_MoXue_ZhenLie& data);
	bool set_obj_gongxu_zhenlie(int show_index, xt_CanShu_MoXue_ZhenLie& data);
	bool get_obj_gongxu_fangfa(int show_index, CanShu_HDM_MoXue_FangFa& data);
	bool set_obj_gongxu_fangfa(int show_index, CanShu_HDM_MoXue_FangFa& data);
	bool get_obj_gongxu_fangfa(int show_index, CanShu_QDM_MoXue_FangFa& data);
	bool set_obj_gongxu_fangfa(int show_index, CanShu_QDM_MoXue_FangFa& data);
	bool get_obj_gongxu_sudu(int show_index, CanShu_SuDu& data);
	bool set_obj_gongxu_sudu(int show_index, CanShu_SuDu& data);
	bool get_obj_gongxu_A_before(int show_index, double& data);
	bool set_obj_gongxu_A_before(int show_index, double& data);

	//???

	Miller_GX_Base* get_obj(int in_id);
	int get_count();
	void del_a_gx(int in_order);
	void swap_gx(int up, int down);
	Miller_GX_Base* gen_gx(int type);

	//void cal_self();
	//6 其他
public:
	List_of_GongXu();
	~List_of_GongXu();

public:


public:
	int pos; //自身存储位置
	int save();
	void load();
	void load_gx_v_pos();

	void init_guanxi();
};

//砂轮表 - 工序在用
class Prog_Manager_API List_of_ShaLun
	: public save_lib
{
	//1 基本设置接口
public:
	void add_obj(int sl_id, Miller_GX_Base* in_p);

	//2 基本数据结构
public:
	vector<int> v_sl_id;
	//3 初始化结构
public:

	//4 主数据结构
public:
	Tool_Base* ptr_tool;

	vector<Miller_GX_Base*>  v_obj_ptr;

	//5 结果计算接口
public:
	void cal_self();

	//用工序list填充基本数据 25.10.31
	void load();

	int get_count();
	Miller_GX_Base* get_obj(int i);

	//6 其他
public:
	List_of_ShaLun();
	~List_of_ShaLun();

};


