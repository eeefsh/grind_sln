#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include"Miller_GX_Base.h"
#include"Miller_GX_CanShu.h"


class Miller_Mo_QDM;

//成型刀开槽 -0
class Prog_Manager_API Miller_GX_KaiCao
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_KaiCao base_data;
	virtual int get_lx_id();

	//3 初始化结构
public:

	//4 主数据结构
public:


	//5 接口
public:

	void init_guanxi();
	//5.0-构造
	Miller_GX_KaiCao(int in_type, Tool_Base* in_ptr);
	Miller_GX_KaiCao();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_KaiCao& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	//void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)override;
	//void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)override;
	//end
	virtual void init_mo_data();

	virtual void speak_father_del_guanxi();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();
	//应该放到基类，传参重载两种形式 7.24
	//void init_mo_canshu();

#pragma region 存储
public:
//	template <class Archive>
//	void serialize(Archive& ar) {
//		ar(
//			base_data
//		);
//	}
//	Miller_GX_KaiCao() = default;
//	Miller_GX_KaiCao(
//		CanShu_GX_KaiCao _base_data
//	)
//		:
//		base_data(_base_data)
//	{}
//public:
#pragma endregion
public:
	int save(int pos);
	void load(int pos);

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_KaiCao& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_KaiCao& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//普通铣刀螺旋槽 -1
class Prog_Manager_API Miller_GX_LXC 
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_LXC base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_LXC(int in_type, Tool_Base* in_ptr);
	Miller_GX_LXC();
	////5.1-设置工序参数：
	////不提成统一形参接口???
	void set_gx_canshu(CanShu_GX_LXC& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数: 设置完整
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	); 
	//}
	//Miller_GX_LXC() = default;
	//Miller_GX_LXC(
	//	CanShu_GX_LXC _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}

#pragma endregion
public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_LXC& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_LXC& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//普通铣刀端齿槽-球头 -2
class Prog_Manager_API Miller_GX_DCC_qiu
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_DCC_qiu base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_DCC_qiu(int in_type, Tool_Base* in_ptr);
	Miller_GX_DCC_qiu();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_DCC_qiu& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();

#pragma region 存储
//public:
//	template <class Archive>
//	void serialize(Archive& ar) {
//		ar(
//			base_data
//		);
//	}
//	Miller_GX_DCC_qiu() = default;
//	Miller_GX_DCC_qiu(
//		CanShu_GX_DCC_qiu _base_data
//	)
//		:
//		base_data(_base_data)
//	{}

#pragma endregion
public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_DCC_qiu& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_DCC_qiu& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//普通铣刀端齿槽-平底 -3
class Prog_Manager_API Miller_GX_DCC_ping
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_DCC_ping base_data;

	//3 初始化结构
public:


	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_DCC_ping(int in_type, Tool_Base* in_ptr);
	Miller_GX_DCC_ping();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_DCC_ping& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_DCC_ping() = default;
	//Miller_GX_DCC_ping(
	//	CanShu_GX_ping _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}
#pragma endregion
public:
	int save(int pos);
	void load(int pos);
public:
		//将参数读到对话框
		void get_canshu(CanShu_GX_DCC_ping& ans);
		//A设置球头容屑槽参数
		void set_canshu(CanShu_GX_DCC_ping& ptr);
		//A.1设置球头容屑槽参数
		void set_canshu(XingCan_GX* ptr);
};

//普通铣刀-圆角前刀面 -4
class Prog_Manager_API Miller_GX_DCC_yuanjiao
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_DCC_yuanjiao base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_DCC_yuanjiao(int in_type, Tool_Base* in_ptr);
	Miller_GX_DCC_yuanjiao();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_DCC_yuanjiao& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_DCC_yuanjiao() = default;
	//Miller_GX_DCC_yuanjiao(
	//	CanShu_GX_yuanjiao _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}
#pragma endregion

public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_DCC_yuanjiao& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_DCC_yuanjiao& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//成型-磨后刀面 -5
class Prog_Manager_API Miller_GX_CX_HDM
	: public Miller_Mo_HDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_CX_HDM base_data;
	virtual int get_hj_id();
	virtual int get_lx_id();

	//3 初始化结构
public:

	//4 主数据结构
public:


	//5 接口
public:
	void init_guanxi();
	virtual void speak_father_del_guanxi();

	//5.0-构造
	Miller_GX_CX_HDM(int in_type, Tool_Base* in_ptr);
	Miller_GX_CX_HDM();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_CX_HDM& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_CX_HDM() = default;
	//Miller_GX_CX_HDM(
	//	CanShu_GX_CX_HDM _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}

#pragma endregion
public:
	int save(int pos);
	void load(int pos);

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_CX_HDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_CX_HDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//锥球-磨后刀面 -6
class Prog_Manager_API Miller_GX_ZQ_HDM
	: public Miller_Mo_HDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_ZQ_HDM base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_ZQ_HDM(int in_type, Tool_Base* in_ptr);
	Miller_GX_ZQ_HDM();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_ZQ_HDM& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_ZQ_HDM() = default;
	//Miller_GX_ZQ_HDM(
	//	CanShu_GX_ZQ_HDM _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}

#pragma endregion
public:
	int save(int pos);
	void load(int pos);

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_ZQ_HDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_ZQ_HDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//磨端后刀面- -7
class Prog_Manager_API Miller_GX_PD_duan_HDM
	: public Miller_Mo_HDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_PD_duan_HDM base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_PD_duan_HDM(int in_type, Tool_Base* in_ptr);
	Miller_GX_PD_duan_HDM();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_PD_duan_HDM& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_PD_duan_HDM() = default;
	//Miller_GX_PD_duan_HDM(
	//	CanShu_GX_PD_duan_HDM _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}
#pragma endregion
public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_PD_duan_HDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_PD_duan_HDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//平底-磨柱体后刀面 -8
class Prog_Manager_API Miller_GX_PD_zhu_HDM
	: public Miller_Mo_HDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_PD_zhu_HDM base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_PD_zhu_HDM(int in_type, Tool_Base* in_ptr);
	Miller_GX_PD_zhu_HDM();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_PD_zhu_HDM& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();

#pragma region 存储
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		base_data
	//	);
	//}
	//Miller_GX_PD_zhu_HDM() = default;
	//Miller_GX_PD_zhu_HDM(
	//	CanShu_GX_PD_zhu_HDM _base_data
	//)
	//	:
	//	base_data(_base_data)
	//{}
#pragma endregion
public:
	int save(int pos);
	void load(int pos);

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_PD_zhu_HDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_PD_zhu_HDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//圆角R-磨后刀面 -9 
class Prog_Manager_API Miller_GX_R_HDM
	: public Miller_Mo_HDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_R_HDM base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:

	//5 接口
public:
	//5.0-构造
	Miller_GX_R_HDM(int in_type, Tool_Base* in_ptr);
	Miller_GX_R_HDM();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_R_HDM& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();

public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_R_HDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_R_HDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};

//刀间间隙 -10
class Prog_Manager_API Miller_GX_DJJX
	: public Miller_Mo_HDM
{	
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_DJJX base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:
	Miller_GX_DJJX(int in_type, Tool_Base* in_ptr);

	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_DJJX& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	virtual void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo);
	virtual void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo);
	//end
	virtual void init_mo_data();

private:
	void gen_HDM_data();
	//产生后刀面刃线，点+后刀面坐标系，12*n，精度0.001 9.17
	mat gen_hdm_rx_by_canshu();

public:
	Miller_GX_DJJX();
	~Miller_GX_DJJX();

public:
	int save(int pos);
	void load(int pos);
public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_DJJX& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_DJJX& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};


//成型刀端齿槽-11 继承前刀面
class Prog_Manager_API Miller_GX_KaiCao_2
	: public Miller_Mo_QDM
{
	//1 基本设置接口
public:

	//2 基本数据结构
public:
	CanShu_GX_KaiCao_2 base_data;

	//3 初始化结构
public:

	//4 主数据结构
public:


	//5 接口
public:
	//5.0-构造
	Miller_GX_KaiCao_2(int in_type, Tool_Base* in_ptr);
	Miller_GX_KaiCao_2();
	//5.1-设置工序参数：
	void set_gx_canshu(CanShu_GX_KaiCao_2& in_canshu);
	//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整
	void set_shalun_id(int in_id);
	//5.2-设置磨削参数
	//void set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)override;
	//void set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)override;
	//end
	virtual void init_mo_data();

private:
	//5.3-生成前刀面数据-默认从刀list选择开螺旋槽的螺旋
	void gen_QDM_data();
	//5.4-初始化芯厚参数
	void init_xinhou();

public:
	int save(int pos);
	void load(int pos);

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_KaiCao_2& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_KaiCao_2& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_GX* ptr);
};