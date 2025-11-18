#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/MA_010101_NC_wheel_data.h"
#include"Obj_Prog.h"
#include"fangzhen_zhu.h"
#include"Tool_Base.h"
#include"Storage_manager.h"

using namespace QuMian_Grovving_namespace;
using namespace Bezier_Curve3_QM_namespace;

class Prog_Manager_API Cal_XinHouMian;
class Prog_Manager_API Cal_XingXian;
class Prog_Manager_API Cal_LouXuan;
class Prog_Manager_API Cal_FenDu;
class Prog_Manager_API Cal_QDM;
class Prog_Manager_API Cal_HouJiao;
class Prog_Manager_API XingCan_GX;


//工序产生一个副程序，每个工序都有自己的副程序类 8.23
//构建出主副子程序类，在当前项目其他文件中 8.23

class Prog_Manager_API Miller_GX_Base
	: public save_lib
{
public:
	Miller_GX_Base();
	~Miller_GX_Base();
	
	//2 基本数据结构
public:
	gx_base_canshu base_data;

	//操作
public:

	//3 初始化结构
public:
	virtual void init_prog_of_gx() = 0;

	virtual void init_guanxi();

	//
	virtual void init_shalun() = 0;
	//
	virtual void init_duixiang() = 0;

	//4 主数据结构
public:
	Tool_Base* ptr_tool; //放基类

	bool is_lastest = 0; //不存储

	xt_gx_shalun sl;
	//目标前刀面对象
	//Cal_QDM* ptr_mian;
	////抽样、范围以及部分变换以后
	//Cal_QDM  obj_mian; //改为对象成员5.20
	//计算出基本刀路
	DL DL_base;
	//对基本刀路增加进退刀
	DL DL_end;
	//增加循环和阵列后形成副程序
	Miller_DL_fu_prog* prog_of_gx;
	//工序勾选刃，替代阵列 9.2
	int selected_ren[6];

	//5 接口
public:
	//virtual void cal_DL() = 0;
	//等价于cal_DL()
	virtual void init_data() = 0; 


	virtual void speak_father_del_guanxi();

#pragma region 参数访问
public:
	string get_name();
	string get_type_of_string(); //要结合刀type 6.11
	int get_sl_id();
	double get_jingeilv(); 

	virtual int get_hj_id();
	virtual int get_lx_id();

#pragma endregion

#pragma region 设置磨面参数
public:
	//提供设置磨面参数的接口。obj工序类都重写 7.16 
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);

#pragma endregion


#pragma region 刀路变换
public:
	//mo_type：前刀面=0，后刀面=1
	DL XiDao_JinTuiDao(int mo_type, DL& in_DaoLu, xt_CanShu_JinTuiDao in_JinTuiDaoCanShu);

	//磨削路径变换-不变安全点
	DL XiDao_HDM_MoXue_BianHuan(DL& in_DaoLu, xt_CanShu_MoXue_BianHuan& in_BianHuan);

	//磨削路径循环
	DL XiDao_HDM_MoXue_XunHuan(DL& in_DaoLu, xt_CanShu_MoXue_XunHuan& in_XunHuan);

	//磨削路径阵列
	DL XiDao_HDM_MoXue_ZhenLie(DL& in_DaoLu, xt_CanShu_MoXue_ZhenLie& in_ZhenLie);

public:
	//标准机床
	vec trans_G_to_JC_in_BiaoZhun(vec& G_P,double a, double c);
	mat trans_G_to_JC_in_BiaoZhun(mat& G_SYS,double a, double c);

	//在戴杰机床中转换
	vec trans_G_to_JC_in_DaiJie(vec& G_P, double a, double c);
	mat trans_G_to_JC_in_DaiJie(mat& G_SYS, double a, double c);

	//ac是戴杰机床的值
	vec trans_G_to_JC_in_ABS(vec& G_P, double a, double c);

	//直角坐标转极坐标
	//i=0,1,2 分别代表转动轴为XYZ,相位0分别为Y，Z，X
	vec3 tcCartesian_to_Polar(vec3 cart_P, int i);
	//i=0,1,2 分别代表转动轴为XYZ,相位0分别为Y，Z，X
	vec3 tcPolar_to_Cartesian(vec3 polar_P, int i);

#pragma endregion

#pragma region 存储
//public:
//	template <class Archive>
//	void serialize(Archive& ar) {
//		ar(
//			shalun_id,
//			pos,
//			type_gx
//		);
//	}
//	Miller_GX_Base() = default;
//	Miller_GX_Base(
//		int _shalun_id,
//		int _pos,
//		int _type
//	)
//		:
//		shalun_id(_shalun_id),
//		pos(_pos),
//		type_gx(_type)
//	{}

#pragma endregion
public:
	int pos;	//存储位置
	virtual int save(int pos);
	virtual void load(int pos);

	//计算程序的状态标志，0-NC、1-2D、2-3D 25.9.17
	int flag_cal_prog = 0;
};

//磨前刀面类-作为工序的成员
class Prog_Manager_API Miller_Mo_QDM 
	: public Miller_GX_Base
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_XinHouMian& in_data);

	//2 基本数据结构
public:
	xt_Mo_QDM_CanShu base_data; 


	//3 初始化结构
public:
	//串联计算流程
	void init();

	//初始化砂轮
	virtual void init_shalun();
	//初始化面-- 
	virtual void init_duixiang();
	//抽样、范围以及部分变换
	virtual void init_DL_base();
	//对基本刀路增加进退刀
	virtual void init_DL_end();
	//增加循环和阵列后形成副程序
	virtual void init_prog_of_gx();

	//4 主数据结构
public:
	//顺磨or逆磨 8.16
	bool Reverse_flag = 0;
	CanShu_QianJiao canshu_qianjiao;
	Cal_XinHouMian obj_xinhou;
	Cal_QDM obj_mian;
	//计算出砂轮的参数
	//xt_gx_shalun sl;
	////目标前刀面对象
	//Cal_QDM* ptr_mian;
	//抽样、范围以及部分变换以后
	Cal_QDM  obj_mian_end; //改为对象成员5.20
	////计算出基本刀路
	//DL DL_base;
	////对基本刀路增加进退刀
	//DL DL_end;
	////增加循环和阵列后形成副程序
	//Miller_DL_fu_prog* prog_of_gx;

	Cal_LouXuan* ptr_lx;
	
	//5 接口
public:
	//计算刀路生成副程序，先
	virtual void cal_DL();
	virtual void init_data();
	//提供一个虚接口，派生类重写，构造出磨需要的数据 6.5
	virtual void init_mo_data() = 0;

	void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);

private:
	int cal_DL_by_qx_xh();
	//增加c_before 7.23
	void cal_DL_P_by_G_SYS_SL(DL_P& ans_DL_P, double& A_before, double& C_before);

public:
	virtual int save(int pos);
	virtual void load(int pos);
};

//磨后刀面类
class Prog_Manager_API Miller_Mo_HDM 
	: public Miller_GX_Base
{
	//1 基本设置接口
public:
	//void set_base_data(CanShu_XinHouMian& in_data);

	//2 基本数据结构
public:
	xt_Mo_HDM_CanShu base_data; 

	//3 初始化结构
public:
	void init();

	//初始化砂轮
	virtual void init_shalun();
	//初始化面
	virtual void init_duixiang();
	//抽样、范围以及部分变换
	virtual void init_DL_base();
	//对基本刀路增加进退刀
	virtual void init_DL_end();
	//增加循环和阵列后形成副程序
	virtual void init_prog_of_gx();

	//4 主数据结构
public:
	int lx_pos;
	int hj_pos;
	Cal_HDM obj_mian;
	//选择磨削的第几后刀面-此类计算需要6.5
	int sel_hdm_id; // 1、2、3  

	//顺磨or逆磨 8.21
	bool Reverse_flag = 0;

	////计算出砂轮的参数
	//xt_gx_shalun sl;
	////目标前刀面对象
	//Cal_HDM* ptr_mian;
	//抽样、范围以及部分变换以后
	Cal_HDM  obj_mian_end;
	//计算出基本刀路
	//DL DL_base;
	////对基本刀路增加进退刀
	//DL DL_end;
	////增加循环和阵列后形成副程序
	//Miller_DL_fu_prog* prog_of_gx;

	Cal_HouJiao* ptr_hj = nullptr;
	Cal_LouXuan* ptr_lx = nullptr;
		
	//5 接口
public:
	//计算刀路生成副程序，先
	virtual void cal_DL();
	virtual void init_data();
	//提供一个虚接口，派生类重写，构造出磨需要的数据 6.5
	virtual void init_mo_data() = 0;

	void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
private:
	//hdm_sel=0,1,2
	//xz_v和wy_v应等于hdm中的数量
	//结果输出到DL_base中
	void cal_DL_by_xz_wy(vec xz_v, vec wy_v, Cal_HDM* hdm, int hdm_sel, bool in_other);
	//hdm_sel=0,1,2
	//bd_v和wy_v应等于hdm中的数量
	//结果输出到DL_base中
	void cal_DL_by_bd_wy(vec bd_v, vec wy_v, Cal_HDM* hdm, int hdm_sel);
	//hdm_sel=0,1,2
	//qx_v和wy_v应等于hdm中的数量
	//结果输出到DL_base中
	//
	void cal_DL_by_qx_wy(vec qx_v, vec wy_v, Cal_HDM* hdm, int hdm_sel, double A_before_in);


private:
	//进退刀，变换等放到刀基类6.6

#pragma region 存储
public:
	/*template <class Archive>
	void serialize(Archive& ar) {
		ar(
			lx_id,
			hj_id,
			mo_canshu,
			sel_hdm_id
		);
	}
	Miller_Mo_HDM() = default;
	Miller_Mo_HDM(
		int _lx_id,
		int _hj_id,
		const xt_Mo_HDM_CanShu& _mo_canshu,
		int _sel_hdm_id
	)
		:
		lx_id(_lx_id),
		hj_id(_hj_id),
		mo_canshu(_mo_canshu),
		sel_hdm_id(_sel_hdm_id)
	{}*/

#pragma endregion
public:
	virtual int save(int pos);
	virtual void load(int pos);
};




