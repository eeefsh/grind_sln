#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"Tool_Base.h"
#include"KongJianXian.h"
#include"Tool_Geo_Obj.h"

//锥球-刀对象类
class Prog_Manager_API Tool_ZQ
	: public Tool_Base
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_Geo_ZQ& in_data);

	//2 基本数据结构
public:
	CanShu_Geo_ZQ data_base;

	//3 初始化结构
public:
	//根据几何参数计算出4个list,工序在基类实现
	void init();
private:
	void init_self_list();

	//4 主数据结构
public:
	//计算出空间线，转换成对应的型线+螺旋线
	KongJianXian kjx_all;
	KongJianXian kjx_qiu;
	KongJianXian kjx_luo;

	vec3 p_WX_0; //零相位-在刀具坐标系中，螺旋线在端面交点


	//5 接口
public:
	Tool_ZQ();
	~Tool_ZQ();

	int get_luoxuancao_lx_id();
	int get_duanchicao_lx_id(); 
	int get_yuanjiaocao_lx_id();//

	int get_hdm_lx_id(); 
	int get_hdm_pd_duan_lx_id();// 
	int get_hdm_pd_zhu_lx_id(); //

	int get_hdm_hj_id(); 
	int get_hdm_pd_duan_hj_id();//
	int get_hdm_pd_zhu_hj_id();//

public:
	virtual void get_cur_tool_canshu(CanShu_Geo_ZQ& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_ZQ& ans_can);

	virtual double get_D();
	virtual double get_renlen();
	virtual double get_alllen();

private:
	//构造三个空间线
	void cal_kjx();

	//通过几何参数构造型线-放全局函数，多种刀调用，6.4
	//void cal_xx_lx_by_kjx(KongJianXian& in_kjx, Cal_XingXian& ans_xx, Cal_LouXuan& ans_lx);
	//void cal_xx_lx_of_luo(Cal_XingXian& ans_xx, Cal_LouXuan& ans_lx);
	//void cal_xx_lx_of_all(Cal_XingXian& ans_xx, Cal_LouXuan& ans_lx);
	
	//后角插值赋值,计算完空间线后调用
	void cal_hj_of_all(Cal_HouJiao* ans_hj);
	void cal_fd_of_all(Cal_FenDu& ans_fd);

public:
	int save();
	virtual void load();
};

//平底-刀对象类
class Prog_Manager_API Tool_PD
	: public Tool_Base
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_Geo_PD& in_data);

	//2 基本数据结构
public:
	CanShu_Geo_PD data_base;

	//3 初始化结构
public:
	void init();
private:
	void init_self_list();
	//4 主数据结构
public:	
	//计算出空间线，转换成对应的型线+螺旋线
	KongJianXian kjx_all;
	KongJianXian kjx_duan;
	KongJianXian kjx_luo;

	vec3 p_WX_0; //零相位+零长度基准点-在刀具坐标系中，螺旋线在端面交点

	//5 接口
public:
	Tool_PD();
	~Tool_PD();


	int get_luoxuancao_lx_id();
	int get_duanchicao_lx_id();
	int get_yuanjiaocao_lx_id();//

	int get_hdm_lx_id();//
	int get_hdm_pd_duan_lx_id();
	int get_hdm_pd_zhu_lx_id(); 

	int get_hdm_hj_id();//
	int get_hdm_pd_duan_hj_id();
	int get_hdm_pd_zhu_hj_id();

public:
	virtual void get_cur_tool_canshu(CanShu_Geo_PD& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_PD& ans_can);

	virtual double get_D();
	virtual double get_renlen();
	virtual double get_alllen();
private:
	//构造空间线
	void cal_kjx();

private:
	//通过几何参数构造型线
	void cal_hj_of_duan(Cal_HouJiao* ans_hj);
	void cal_hj_of_luo(Cal_HouJiao* ans_hj);

	void cal_fd_of_all(Cal_FenDu& ans_fd);

public:
	int save();
	virtual void load();
};

//圆角R-刀对象类
class Prog_Manager_API Tool_R
	: public Tool_Base
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_Geo_R& in_data);

	//2 基本数据结构
public:
	CanShu_Geo_R data_base;

	//3 初始化结构
public:
	void init();
private:
	void init_self_list();
	//4 主数据结构
public:
	//计算出空间线，转换成对应的型线+螺旋线
	KongJianXian kjx_all;
	KongJianXian kjx_duan;
	KongJianXian kjx_rrr;
	KongJianXian kjx_luo;
	vec3 p_WX_0; //零相位+零长度基准点-在刀具坐标系中，螺旋线在端面交点

	//5 接口
public:
	Tool_R();
	~Tool_R();

	int get_luoxuancao_lx_id();
	int get_duanchicao_lx_id();
	int get_yuanjiaocao_lx_id();

	int get_hdm_lx_id();
	int get_hdm_pd_duan_lx_id();//
	int get_hdm_pd_zhu_lx_id();//

	int get_hdm_hj_id();
	int get_hdm_pd_duan_hj_id();//
	int get_hdm_pd_zhu_hj_id();//

public:
	virtual void get_cur_tool_canshu(CanShu_Geo_R& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_R& ans_can);

	virtual double get_D();
	virtual double get_renlen();
	virtual double get_alllen();
	virtual double get_rrr(); //8.21
private:
	//构造空间线
	void cal_kjx();

private:
	//通过几何参数构造型线
	void cal_hj_of_all(Cal_HouJiao* ans_hj);

	void cal_fd_of_all(Cal_FenDu& ans_fd);
public:
	int save();
	virtual void load();
};

//成型-刀对象类
class Prog_Manager_API Tool_CX
	: public Tool_Base
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_Geo_CX& in_data);

	//2 基本数据结构
public:
	CanShu_Geo_CX data_base;

	//3 初始化结构
public:

	//4 主数据结构
public:
	void init();

	//5 接口
public:
	Tool_CX();
	~Tool_CX();

	int get_luoxuancao_lx_id();
	int get_duanchicao_lx_id();
	int get_yuanjiaocao_lx_id();

	int get_hdm_lx_id();
	int get_hdm_pd_duan_lx_id();//
	int get_hdm_pd_zhu_lx_id();//

	int get_hdm_hj_id();
	int get_hdm_pd_duan_hj_id();//
	int get_hdm_pd_zhu_hj_id();//
public:
	virtual void get_cur_tool_canshu(CanShu_Geo_CX& ans_can);
	virtual void set_cur_tool_canshu(CanShu_Geo_CX& ans_can);

	virtual double get_D();
	virtual double get_renlen();
	virtual double get_alllen();
private:
	/*void init_xx_list(int in_count, vector<CanShu_XingXian>& v_canshu, vector<int>& v_empty)
	{
		ptr_list_xx->count = in_count;
		for (int i = 0; i < v_canshu.size(); i++)
		{
			CanShu_XingXian ls_xx = v_canshu[i];

			Cal_XingXian* ptr_lx = new Cal_XingXian((Tool_Base*)this, ls_xx);
			ptr_lx->set_base_data(ls_xx);
			ptr_lx->init_data();

			ptr_list_xx->add_a_cal_data(ptr_lx);
		}
		for (int i = 0; i < v_empty.size(); i++)
		{
			ptr_list_xx->empty_index.push(v_empty[i]);
		}
	}


	void init_hj_list(int in_count, vector<CanShu_HouJiao>& v_canshu, vector<int>& v_empty)
	{
		ptr_list_hj->count = in_count;
		for (int i = 0; i < v_canshu.size(); i++)
		{
			CanShu_HouJiao ls_xx = v_canshu[i];

			Cal_HouJiao* ptr_lx = new Cal_HouJiao((Tool_Base*)this, ls_xx);
			ptr_lx->set_base_data(ls_xx);
			ptr_lx->init_data();

			ptr_list_hj->add_a_cal_data(ptr_lx);
		}
		for (int i = 0; i < v_empty.size(); i++)
		{
			ptr_list_hj->empty_index.push(v_empty[i]);
		}
	}
	void init_lx_list(int in_count, vector<CanShu_LuoXuan>& v_canshu, vector<int>& v_empty)
	{
		ptr_list_lx->count = in_count;
		for (int i = 0; i < v_canshu.size(); i++)
		{
			CanShu_LuoXuan ls_xx = v_canshu[i];

			Cal_LouXuan* ptr_lx = new Cal_LouXuan((Tool_Base*)this, ls_xx);
			ptr_lx->set_base_data(ls_xx);
			ptr_lx->init_data();

			ptr_list_lx->add_a_cal_data(ptr_lx);
		}
		for (int i = 0; i < v_empty.size(); i++)
		{
			ptr_list_lx->empty_index.push(v_empty[i]);
		}
	}
	void init_fd_list(int in_count, vector<CanShu_FenDu>& v_canshu, vector<int>& v_empty)
	{
		ptr_list_fd->count = in_count;
		for (int i = 0; i < v_canshu.size(); i++)
		{
			CanShu_FenDu ls_xx = v_canshu[i];

			Cal_FenDu* ptr_lx = new Cal_FenDu((Tool_Base*)this, ls_xx);
			ptr_lx->set_base_data(ls_xx);
			ptr_lx->init_data();

			ptr_list_fd->add_a_cal_data(ptr_lx);
		}
		for (int i = 0; i < v_empty.size(); i++)
		{
			ptr_list_fd->empty_index.push(v_empty[i]);
		}
	}*/

public:
	int save();
	void load();
};

