#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include"RenXian.h"
#include"Obj_Prog.h"
#include"Storage_manager.h"
#include"manager_h/MA_010101_Read_dxf_manager.h"

//所有自定义类的类型声明



//工序 公共形参类
class Prog_Manager_API XingCan_Miller_GX
{
public:
	//工序类型
	int gx_type;

#pragma region 工序参数指针
	//工序类型参数指针: 锥度球头
public:
	CanShu_ZQ_QDM* can_zq_qdm;		//球头：球头前刀面
	Canshu_ZQ_LXC* can_zq_lxc;	//球头：螺旋前刀面
	Canshu_ZQ_HDM_1* can_zq_hdm_1;	//球头：第一后刀面-球
	Canshu_ZQ_HDM_2* can_zq_hdm_2;//球头：第2后刀面-球
	Canshu_ZQ_HDM_3* can_zq_hdm_3;//球头：第2后刀面-球
	CanShu_ZQ_DaoTiJianXi* can_zq_dt_jx;//
	CanShu_ZQ_DaoJianJianXi* can_zq_dj_jx;
	CanShu_ZQ_DaoJianFenXieCao* can_zq_dj_fxc;

	//工序类型参数指针: 平底铣刀
public:
	CanShu_PD_DCC* can_pd_dcc;
	CanShu_PD_DHDM_1* can_pd_dhdm_1;
	CanShu_PD_DHDM_2* can_pd_dhdm_2;
	CanShu_PD_DHDM_3* can_pd_dhdm_3;
	CanShu_PD_LXC* can_pd_lxc;
	CanShu_PD_HDM_1* can_pd_hdm_1;
	CanShu_PD_HDM_2* can_pd_hdm_2;
	CanShu_PD_HDM_3* can_pd_hdm_3;
	CanShu_PD_DaoTiJianXi* can_pd_dt_jx;

	//工序类型参数指针: 圆角铣刀
public:
	CanShu_R_QDM_R* can_r_qdm;
	CanShu_R_HDM_1* can_r_hdm_1;
	CanShu_R_HDM_2* can_r_hdm_2;
	CanShu_R_HDM_3* can_r_hdm_3;
	CanShu_R_LXC* can_r_lxc;
	CanShu_R_DaoTiJianXi* can_r_dt_jx;
	CanShu_R_DaoJianJianXi* can_r_dj_jx;
	CanShu_R_DaoJianFenXieCao* can_r_dj_fxc;

	//成型刀
public:
	CanShu_GX_CX_KaiCao* can_cx_kaicao;
	CanShu_GX_CX_HDM_1* can_cx_hdm_1;
	CanShu_GX_CX_HDM_2* can_cx_hdm_2;
#pragma endregion

public:
	XingCan_Miller_GX(); //后续加成员，要在内部初始化指针 ???
	~XingCan_Miller_GX();
	XingCan_Miller_GX(int in_type);

#pragma region 参数指针赋值
	//设置不同类型指针内部参数的函数
public:
	bool set_CanShu_ZQ_QDM(CanShu_ZQ_QDM& in_ptr);
	bool set_Canshu_ZQ_LXC(Canshu_ZQ_LXC& in_ptr);
	bool set_Canshu_ZQ_HDM_1(Canshu_ZQ_HDM_1& in_ptr);
	bool set_Canshu_ZQ_HDM_2(Canshu_ZQ_HDM_2& in_ptr);
	bool set_Canshu_ZQ_HDM_3(Canshu_ZQ_HDM_3& in_ptr);
	bool set_CanShu_ZQ_DaoTiJianXi(CanShu_ZQ_DaoTiJianXi& in_ptr);
	bool set_CanShu_ZQ_DaoJianJianXi(CanShu_ZQ_DaoJianJianXi& in_ptr);
	bool set_CanShu_ZQ_DaoJianFenXieCao(CanShu_ZQ_DaoJianFenXieCao& in_ptr);

	bool set_CanShu_PD_DCC(CanShu_PD_DCC& in_ptr);
	bool set_CanShu_PD_DHDM_1(CanShu_PD_DHDM_1& in_ptr);
	bool set_CanShu_PD_DHDM_2(CanShu_PD_DHDM_2& in_ptr);
	bool set_CanShu_PD_DHDM_3(CanShu_PD_DHDM_3& in_ptr);
	bool set_CanShu_PD_LXC(CanShu_PD_LXC& in_ptr);
	bool set_CanShu_PD_HDM_1(CanShu_PD_HDM_1& in_ptr);
	bool set_CanShu_PD_HDM_2(CanShu_PD_HDM_2& in_ptr);
	bool set_CanShu_PD_HDM_3(CanShu_PD_HDM_3& in_ptr);
	bool set_CanShu_PD_DaoTiJianXi(CanShu_PD_DaoTiJianXi& in_ptr);

	bool set_CanShu_R_QDM_R(CanShu_R_QDM_R& in_ptr);
	bool set_CanShu_R_HDM_1(CanShu_R_HDM_1& in_ptr);
	bool set_CanShu_R_HDM_2(CanShu_R_HDM_2& in_ptr);
	bool set_CanShu_R_HDM_3(CanShu_R_HDM_3& in_ptr);
	bool set_CanShu_R_LXC(CanShu_R_LXC& in_ptr);
	bool set_CanShu_R_DaoTiJianXi(CanShu_R_DaoTiJianXi& in_ptr);
	bool set_CanShu_R_DaoJianJianXi(CanShu_R_DaoJianJianXi& in_ptr);
	bool set_CanShu_R_DaoJianFenXieCao(CanShu_R_DaoJianFenXieCao& in_ptr);

	bool set_CanShu_GX_CX_KaiCao(CanShu_GX_CX_KaiCao& in_ptr);
	bool set_CanShu_GX_CX_HDM_1(CanShu_GX_CX_HDM_1& in_ptr);
	bool set_CanShu_GX_CX_HDM_2(CanShu_GX_CX_HDM_2& in_ptr);
#pragma endregion

	//对外接口
public:
	int get_gx_type();
};

//工序类-锥度球头前刀面-0
class Prog_Manager_API Miller_GX_ZQ_QDM : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_ZQ_QDM  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_ZQ_QDM& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_ZQ_QDM& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();

	void cal_new_renxian(double per_start, Cal_RenXian& in_rx);
	//计算引导面
	void cal_leadface(Cal_RenXian& in_rx, mat& data_qdm);

	void cal_xinhou_hz(double D_sl, double R_xh, double in_ang_in, mat& px, mat& nx);
private:
	//直线-圆弧-直线芯厚。直线不满足顶角。--10.28 zy
	//输入：前刀面点、顶角（X轴夹角）、芯厚圆半径、出线角度（Z轴夹角）、砂轮半径
	//输出：芯厚面的点 n*3
	void cal_xinhoumian(vec3 qdm_p, double ang_up, double R_xin,
		double ang_out, double R_sl, double ang_zhuan, mat& px);
	//要求前刀面的点在Z轴上、没有就取近似的
	double cal_Offset_Height(double z_p, double r, double angleDegrees);
	void findCircle2Center(double h1, double r, double h2, double R2,
		double& ans_x, double& ans_y);
	//根据芯厚控制的参数，产生芯厚面（类似于型线），要求等间距
	void cal_xinhoumian(mat& px, mat& nx, double sl_D);
	void cal_xinhoumian(Cal_RenXian& ans_rx, mat& px, mat& nx);
public:
	Miller_GX_ZQ_QDM();
	~Miller_GX_ZQ_QDM();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_ZQ_QDM(Miller_D_ZQ* in_ptr);

#pragma region 存储
public:
	Miller_GX_ZQ_QDM(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
#pragma endregion
};

//工序-锥度球头螺旋槽-1
class Prog_Manager_API Miller_GX_ZQ_LXC : public Miller_GX_Base
{
	//输入数据
public:
	//计算参数
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	Canshu_ZQ_LXC  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(Canshu_ZQ_LXC& ans);
private:
	//A设置设置周刃螺旋槽参数
	void set_canshu(Canshu_ZQ_LXC& ptr);
public:
	//A.1设置周刃螺旋槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();

	void cal_new_renxian(Cal_RenXian& in_rx);
	//计算引导面--根据前角类型（0法向、1径向）计算实际旋转矩阵11.6
	void cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm);
private:
	//根据芯厚控制的参数，产生芯厚面（类似于型线），要求等间距
	  //芯厚线在工件坐标系 9.9
	void cal_xinhoumian(mat& px, mat& nx, double sl_D);
public:
	Miller_GX_ZQ_LXC();
	~Miller_GX_ZQ_LXC();
	Miller_GX_ZQ_LXC(Miller_D_ZQ* in_ptr);
	// 通过 Miller_GX_Base 继承
	virtual void set_shalun_set();
	virtual void set_sudu_set();

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_LXC(int in_name);
public:

	virtual int Save();
	virtual void Load(int in_pos);
	//因为成员参数数据名字相同，所以函数实现相同，不可提到基类里

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//

};

//工序-锥度球头第一后刀面-2
class Prog_Manager_API Miller_GX_ZQ_HDM_1 : public Miller_GX_Base
{
public:
	//Miller_D_Base* self_Dao;
	Canshu_ZQ_HDM_1 data_canshu;//自身参数

public:
	//将参数读到对话框
	void get_canshu(Canshu_ZQ_HDM_1& ans);
	//A设置设置后刀面参数
	void set_canshu(Canshu_ZQ_HDM_1& ptr);
	//A.1设置后刀面参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写--补偿由副程序提供函数
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();
	void cal_new_hdm(mat& in_mat);  //12*n
	//计算后刀面磨削角度插值
	void cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy);

private:
	//根据引导刃线生成引导面
	void gen_leadface_by_ren(Cal_RenXian& in_line);
	//根据芯厚控制的参数，产生芯厚面（类似于型线），要求等间距
	void cal_xinhoumian(mat& px, mat& nx, double sl_D);

public:
	Miller_GX_ZQ_HDM_1();
	~Miller_GX_ZQ_HDM_1();
	Miller_GX_ZQ_HDM_1(Miller_D_ZQ* in_ptr);
	virtual void set_shalun_set();
	virtual void set_sudu_set();

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_HDM_1(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//

};

//工序-锥度球头第二后刀面-3
class Prog_Manager_API Miller_GX_ZQ_HDM_2 : public Miller_GX_Base
{
public:
	//Miller_D_Base* self_Dao;
	Canshu_ZQ_HDM_2 data_canshu;//自身参数

public:
	//将参数读到对话框
	void get_canshu(Canshu_ZQ_HDM_2& ans);
	//A设置设置后刀面参数
	void set_canshu(Canshu_ZQ_HDM_2& ptr);
	//A.1设置后刀面参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();

	//计算后刀面磨削角度插值
	void cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy);

public:
	Miller_GX_ZQ_HDM_2();
	~Miller_GX_ZQ_HDM_2();
	Miller_GX_ZQ_HDM_2(Miller_D_ZQ* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_HDM_2(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//

};

//工序-锥度球头第三后刀面-4
class Prog_Manager_API Miller_GX_ZQ_HDM_3 : public Miller_GX_Base
{
public:
	//Miller_D_Base* self_Dao;
	Canshu_ZQ_HDM_3 data_canshu;//自身参数

public:
	//将参数读到对话框
	void get_canshu(Canshu_ZQ_HDM_3& ans);
	//A设置设置后刀面参数
	void set_canshu(Canshu_ZQ_HDM_3& ptr);
	//A.1设置后刀面参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

	//计算后刀面磨削角度插值
	void cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy);


public:
	Miller_GX_ZQ_HDM_3();
	~Miller_GX_ZQ_HDM_3();
	Miller_GX_ZQ_HDM_3(Miller_D_ZQ* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_HDM_3(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//

};

//工序-锥度球头刀体间隙-5
class Prog_Manager_API Miller_GX_ZQ_DaoTiJianXi : public Miller_GX_Base
{
	//输入数据
public:
	//计算参数
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_ZQ_DaoTiJianXi  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_ZQ_DaoTiJianXi& ans);
	//A设置设置周刃螺旋槽参数
	void set_canshu(CanShu_ZQ_DaoTiJianXi& ptr);
	//A.1设置周刃螺旋槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
public:
	//计算
	virtual void cal_base_DL(); //父项铣刀不提供对应刃线，工序自身算11.15
public:
	Miller_GX_ZQ_DaoTiJianXi();
	~Miller_GX_ZQ_DaoTiJianXi();
	Miller_GX_ZQ_DaoTiJianXi(Miller_D_ZQ* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_DaoTiJianXi(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//

};

//工序-锥度球头刀尖间隙-6
class Prog_Manager_API Miller_GX_ZQ_DaoJianJianXi : public Miller_GX_Base
{
	//输入数据
public:
	//计算参数
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_ZQ_DaoJianJianXi  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_ZQ_DaoJianJianXi& ans);
	//A设置设置周刃螺旋槽参数
	void set_canshu(CanShu_ZQ_DaoJianJianXi& ptr);
	//A.1设置周刃螺旋槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
public:
	//计算
	virtual void cal_base_DL();

	//mat base_p_djjx;//指向刀尖 3*n
	//vector<mat33> base_sys_djjx;  //X切向、Z法向
	void cal_leadline(double in_pos_ang, mat& base_p_djjx, vector<mat33>& base_sys_djjx);
public:
	Miller_GX_ZQ_DaoJianJianXi();
	~Miller_GX_ZQ_DaoJianJianXi();
	Miller_GX_ZQ_DaoJianJianXi(Miller_D_ZQ* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_DaoJianJianXi(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
	void set_self_dao(Miller_D_Base* in_ptr);
};

//工序-锥度球头刀尖分屑槽-7
class Prog_Manager_API Miller_GX_ZQ_DaoJianFenXieCao : public Miller_GX_Base
{
	//输入数据
public:
	//计算参数
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_ZQ_DaoJianFenXieCao  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_ZQ_DaoJianFenXieCao& ans);
	//A设置设置周刃螺旋槽参数
	void set_canshu(CanShu_ZQ_DaoJianFenXieCao& ptr);
	//A.1设置周刃螺旋槽参数
	void set_canshu(XingCan_Miller_GX& ptr);
public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
public:
	//计算
	virtual void cal_base_DL();
public:
	Miller_GX_ZQ_DaoJianFenXieCao();
	~Miller_GX_ZQ_DaoJianFenXieCao();
	Miller_GX_ZQ_DaoJianFenXieCao(Miller_D_ZQ* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_ZQ_DaoJianFenXieCao(int in_name);
public:
	virtual int Save();
	virtual void Load(int in_pos);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
	void set_self_dao(Miller_D_Base* in_ptr);
};

//工序类-平底铣刀端齿容屑槽-8
class Prog_Manager_API Miller_GX_PD_DCC : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_DCC  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_DCC& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_DCC& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();


	void  cal_leadface(Cal_RenXian& in_rx, mat& data_qdm);
	//计算引导面
	void cal_leadface_caodi(Cal_RenXian& in_rx, mat& data_qdm);

	void cal_sl_weiyi_ang(double in_D_gj, double in_ang_caoding, double in_D_sl, double& out_ang_ans);

	//中间结果数据
public:
	//Miller_QDM data_face;	//前刀面

public:
	Miller_GX_PD_DCC();
	~Miller_GX_PD_DCC();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_DCC(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_DCC(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第一端后刀面-9
class Prog_Manager_API Miller_GX_PD_DHDM_1 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_DHDM_1  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_DHDM_1& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_DHDM_1& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_DHDM_1();
	~Miller_GX_PD_DHDM_1();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_DHDM_1(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_DHDM_1(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第二端后刀面-10
class Prog_Manager_API Miller_GX_PD_DHDM_2 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_DHDM_2  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_DHDM_2& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_DHDM_2& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_DHDM_2();
	~Miller_GX_PD_DHDM_2();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_DHDM_2(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_DHDM_2(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第三端后刀面-11
class Prog_Manager_API Miller_GX_PD_DHDM_3 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_DHDM_3  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_DHDM_3& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_DHDM_3& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_DHDM_3();
	~Miller_GX_PD_DHDM_3();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_DHDM_3(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_DHDM_3(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-螺旋槽-12
class Prog_Manager_API Miller_GX_PD_LXC : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_LXC  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_LXC& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_LXC& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

	//计算引导面
	void cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm);

	void cal_xinhoumian(mat& px, mat& nx, double sl_D);

private:
	//根据引导刃线生成引导面
	void gen_leadface_by_ren(Cal_RenXian& in_line);


public:
	Miller_GX_PD_LXC();
	~Miller_GX_PD_LXC();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_LXC(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_LXC(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第一后刀面-13
class Prog_Manager_API Miller_GX_PD_HDM_1 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_HDM_1  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_HDM_1& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_HDM_1& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_HDM_1();
	~Miller_GX_PD_HDM_1();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_HDM_1(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_HDM_1(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第二后刀面-14
class Prog_Manager_API Miller_GX_PD_HDM_2 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_HDM_2  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_HDM_2& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_HDM_2& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);


public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_HDM_2();
	~Miller_GX_PD_HDM_2();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_HDM_2(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_HDM_2(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-第三后刀面-15
class Prog_Manager_API Miller_GX_PD_HDM_3 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_HDM_3  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_HDM_3& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_HDM_3& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_HDM_3();
	~Miller_GX_PD_HDM_3();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_HDM_3(Miller_D_PD* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_HDM_3(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-平底铣刀-刀体间隙-16
class Prog_Manager_API Miller_GX_PD_DaoTiJianXi : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_PD_DaoTiJianXi  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_PD_DaoTiJianXi& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_PD_DaoTiJianXi& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_PD_DaoTiJianXi();
	~Miller_GX_PD_DaoTiJianXi();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_PD_DaoTiJianXi(Miller_D_PD* in_ptr);


	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_PD_DaoTiJianXi(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-圆角前刀面-17
class Prog_Manager_API Miller_GX_R_QDM_R : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_QDM_R  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_QDM_R& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_QDM_R& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();
	//计算引导面
	void cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm);

private:
	//根据引导刃线生成引导面
	void gen_leadface_by_ren(Cal_RenXian& in_line);


public:
	Miller_GX_R_QDM_R();
	~Miller_GX_R_QDM_R();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_QDM_R(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_QDM_R(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-第一后刀面-18
class Prog_Manager_API Miller_GX_R_HDM_1 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_HDM_1  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_HDM_1& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_HDM_1& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

	void cal_cha_ang(int p_count_hen, int p_count_rrr, int p_count_hdm, vector<double>& ans_qie, vector<double>& ans_wy);

public:
	Miller_GX_R_HDM_1();
	~Miller_GX_R_HDM_1();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_HDM_1(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_HDM_1(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-第二后刀面-19
class Prog_Manager_API Miller_GX_R_HDM_2 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_HDM_2  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_HDM_2& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_HDM_2& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

	void cal_cha_ang(int p_count_hen, int p_count_rrr, int p_count_hdm, vector<double>& ans_qie, vector<double>& ans_wy);

public:
	Miller_GX_R_HDM_2();
	~Miller_GX_R_HDM_2();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_HDM_2(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_HDM_2(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-第三后刀面-20
class Prog_Manager_API Miller_GX_R_HDM_3 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_HDM_3  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_HDM_3& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_HDM_3& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();


public:
	Miller_GX_R_HDM_3();
	~Miller_GX_R_HDM_3();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_HDM_3(Miller_D_R* in_ptr);


	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_HDM_3(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-螺旋槽-21
class Prog_Manager_API Miller_GX_R_LXC : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_LXC  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_LXC& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_LXC& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

	void cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm);

public:
	Miller_GX_R_LXC();
	~Miller_GX_R_LXC();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_LXC(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_LXC(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-刀体间隙-22
class Prog_Manager_API Miller_GX_R_DaoTiJianXi : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_DaoTiJianXi  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_DaoTiJianXi& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_DaoTiJianXi& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();
public:
	Miller_GX_R_DaoTiJianXi();
	~Miller_GX_R_DaoTiJianXi();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_DaoTiJianXi(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_DaoTiJianXi(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-刀尖间隙-23
class Prog_Manager_API Miller_GX_R_DaoJianJianXi : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_DaoJianJianXi  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_DaoJianJianXi& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_DaoJianJianXi& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();

public:
	Miller_GX_R_DaoJianJianXi();
	~Miller_GX_R_DaoJianJianXi();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_DaoJianJianXi(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_DaoJianJianXi(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-圆角R刀-刀尖分屑槽-24
class Prog_Manager_API Miller_GX_R_DaoJianFenXieCao : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_R_DaoJianFenXieCao  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_R_DaoJianFenXieCao& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_R_DaoJianFenXieCao& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);
public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:

	//计算基本刀路
	void cal_base_DL();
	//计算引导面
	void cal_leadface(Cal_RenXian& in_rx, mat& data_qdm);

public:
	Miller_GX_R_DaoJianFenXieCao();
	~Miller_GX_R_DaoJianFenXieCao();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_R_DaoJianFenXieCao(Miller_D_R* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_R_DaoJianFenXieCao(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-成型刀-开槽-25
class Prog_Manager_API Miller_GX_CX_KaiCao : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	//CanShu_GX_CX_KaiCao  data_canshu;		//工序所需参数

	Cal_QDM ptr_qdm;
	Cal_XinHouMian ptr_xhm;
	CanShu_QDM_FangFa ptr_gy;

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_CX_KaiCao& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_CX_KaiCao& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
	void cal_base_DL();

private:
	//根据螺旋的槽类型参数构造出型线对应的刃线 -4.15
	void cal_xiecao_by_zhuan_qing(Cal_XingXian& in_xx, double in_zhuan, double in_qing, Cal_RenXian& ans_rx);
	void cal_xiecao_by_pian_qing(Cal_XingXian& in_xx, double in_pian, double in_qing, Cal_RenXian& ans_rx);
	void cal_luoxuan_by_luo_angle(Cal_XingXian& in_xx, double in_luo_ang, Cal_RenXian& ans_rx);
	void cal_luoxuan_by_daocheng(Cal_XingXian& in_xx, double in_daocheng, Cal_RenXian& ans_rx);
private:
	void cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm);

	void rotate_by_buchang(mat& in_qdm, double in_ang);
	//芯厚输入不确定 3.11
	void cal_xinhoumian(mat& px, mat& nx, double sl_D);

public:
	Miller_GX_CX_KaiCao();
	~Miller_GX_CX_KaiCao();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_CX_KaiCao(Miller_D_CX* in_ptr);


	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_CX_KaiCao(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-成型刀-后刀面-26
class Prog_Manager_API Miller_GX_CX_HDM_1 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	//CanShu_GX_CX_HDM_1  data_canshu;		//工序所需参数

	Cal_HDM* ptr_hdm;
	CanShu_HDM_FangFa canshu_ff;

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_CX_HDM_1& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_CX_HDM_1& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();
	void cal_cha_ang(int count_p, vector<double>& ans_qie, vector<double>& ans_wy);



public:
	Miller_GX_CX_HDM_1();
	~Miller_GX_CX_HDM_1();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_CX_HDM_1(Miller_D_CX* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_CX_HDM_1(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};

//工序类-成型刀-后刀面2-27
class Prog_Manager_API Miller_GX_CX_HDM_2 : public Miller_GX_Base
{
	//基本数据结构
public:
	//Miller_D_Base* self_Dao;	//父项铣刀指针
	CanShu_GX_CX_HDM_2  data_canshu;		//工序所需参数

public:
	//将参数读到对话框
	void get_canshu(CanShu_GX_CX_HDM_2& ans);
	//A设置球头容屑槽参数
	void set_canshu(CanShu_GX_CX_HDM_2& ptr);
	//A.1设置球头容屑槽参数
	void set_canshu(XingCan_Miller_GX& ptr);

public:
	//生成工序副程序--工序重写
	virtual void gen_prog_of_gx(fangzhen_zhu* zhu_ptr);
private:
	//计算基本刀路
	void cal_base_DL();
	void cal_cha_ang(int count_p, vector<double>& ans_qie, vector<double>& ans_wy);


public:
	Miller_GX_CX_HDM_2();
	~Miller_GX_CX_HDM_2();
	//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
	Miller_GX_CX_HDM_2(Miller_D_CX* in_ptr);

	//*************以下接口（包括构造函数格式）用于对象存储和恢复********//	
public:
	Miller_GX_CX_HDM_2(int in_name);
public:
	int Save() override;
	void Load(int in_pos)override;

	void set_self_dao(Miller_D_Base* in_ptr);
	//*************以上接口（包括构造函数格式）用于对象存储和恢复********//
};






















