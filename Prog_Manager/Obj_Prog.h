#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/xt_armadillo_settings.h"

#include"TooL_canshu_2.h"
class xt_gx_shalun;


#pragma pack(push, 8)
//机床点
class Prog_Manager_API Point_by_5axis
{
public:
	double X;
	double Y;
	double Z;
	double A;
	double C;
public:
	//标准构造函数
	Point_by_5axis();
	~Point_by_5axis();
	//设置点坐标
	void Set_Point(double x, double y, double z, double a, double b);
};

//刀路点
class Prog_Manager_API DL_P
{
	//与后处理坐标系一致
	//X轴是长度方向，Z轴是半径方向
public:
	vec G_P;
	mat G_SYS_HDM; //因此不增加前刀面坐标系 12.20 zy
	mat G_SYS_SL;

public:
	//后处理后的数据
	vec JC_P;
	mat JC_SYS_HDM;  //后处理结束后赋值为vec3，即点的法向，24.12.5 zy 
	mat JC_SYS_SL;

public:
	double theta_nz; 
	double theta_bd;
	double theta_fx; 
	double theta_xq; //相切角
	//表示刀路类型，磨削-0，进-1,退-2,接近-3，远离-4，起始安全-5，结束安全-6
	int point_type;
public:
	DL_P();
	~DL_P();

};

//刀路数据
class Prog_Manager_API DL
{
public:
	//double Spd_r_min;//砂轮线速度 5.13del
	//int LengQueYe;//冷却液状态
	//Point_by_5axis anquandian;

	vector<DL_P> Data;
public:
	//将刀路数据(G_SYS)整体旋转指定角度
	void RotX(double in_ang);
	void reset();
public:
	double maxR();
	double minX();
public:
	DL();
	~DL();
};

//副程序刀路点
//class DL_P_fu_prog
//{
//public:
//	vec G_P; //空间点
//	mat G_SYS_HDM;
//	mat G_SYS_SL;
//public:
//	//后处理后的数据
//	vec JC_P;
//	mat JC_SYS_HDM;
//	mat JC_SYS_SL;
//
//	vec JC_P_DC;
//public:
//	double theta_nz;
//	double theta_bd;
//	int point_type;
//	//表示刀路类型，磨削-0，进-1,退-2,接近-3，远离-4，起始安全-5，结束安全-6
//
//public:
//	DL_P_fu_prog();
//	~DL_P_fu_prog();
//};


//副程序刀路--用于仿真
class Prog_Manager_API DL_fu_prog
{
public:
	int sl_pos_in_JC_lib; //机床砂轮库位置 T(n)- 25.5.21
	int sl_pos_in_slz;	//在砂轮组上的位置
public:
	xt_gx_shalun sl_data;
	Point_by_5axis anquandian;
	vector<DL_P> Data;
public:
	int gx_type;

public:
	DL_fu_prog();
	~DL_fu_prog();
};


#pragma pack(pop)

class xt_CanShu_JinTuiDao;
class xt_CanShu_MoXue_BianHuan;
class xt_CanShu_MoXue_XunHuan;
class xt_CanShu_JinTuiDao;
class xt_CanShu_JinTuiDao;
class xt_CanShu_JinTuiDao;
class xt_CanShu_JinTuiDao;
class xt_CanShu_MoXue_SuDu;


//DL XiDao_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu)
//{
//#pragma region 变量声明
//	vec G_JinDaoDian, JC_JinDaoDian;
//	vec G_TuiDaoDian, JC_TuiDaoDian;
//	vec G_JieJinDian, JC_JieJinDian;
//	vec G_YuanLiDian, JC_YuanLiDian;
//	vec G_AnQuanDianStart, JC_AnQuanDianStart;
//	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
//	vec Start_QieXiang;
//	vec End_QieXiang;
//
//	int feibiao_xishu = -1;
//
//#pragma endregion
//
//#pragma region 计算进刀点
//	//计算进刀方向向量-
//	if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴反方向
//		Start_QieXiang = -in_DaoLu.Data.at(0).G_SYS_HDM.col(0);
//	}
//	else
//	{
//		//X轴绕Z旋转进刀角度
//		Start_QieXiang = tcRotZ(3, 180.0 - in_JinTuiDaoCanShu.JinDaoJiaoDu) * tcX(3);
//	}
//	//第一个磨削点+进刀距离*进刀方向
//	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + in_DaoLu.Data.at(0).G_P;
//	JC_JinDaoDian = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz * feibiao_xishu) * G_JinDaoDian; //扭转角度的正负8.12mark
//#pragma endregion
//
//#pragma region 计算退刀点
//	//计算退刀方向向量+
//	if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴切向
//		End_QieXiang = in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_HDM.col(0);
//	}
//	else
//	{
//		//X轴绕Z轴旋转退刀角度
//		End_QieXiang = tcRotZ(3, in_JinTuiDaoCanShu.TuiDaoJiaoDu) * tcX(3);
//	}
//	//最后磨削点+退刀距离*退刀方向
//	G_TuiDaoDian = End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P;
//	JC_TuiDaoDian = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz * feibiao_xishu) * G_TuiDaoDian;
//#pragma endregion
//
//#pragma region 计算安全点
//	double AnQuanR = 0.0;
//	double AnQuanX = 0.0;
//	AnQuanR = in_DaoLu.anquandian.X + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
//	AnQuanX = in_DaoLu.anquandian.Z - in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi;
//	G_AnQuanDianStart = { AnQuanX ,AnQuanR ,0.0 };
//	G_AnQuanDianEnd = { AnQuanX ,AnQuanR ,0.0 };
//	JC_AnQuanDianStart = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz) * G_AnQuanDianStart;
//	JC_AnQuanDianEnd = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz * feibiao_xishu) * G_AnQuanDianEnd;
//#pragma endregion
//
//#pragma region 计算接近点
//	vec LSvec1, LSvec2;
//	//指向安全点的方向向量
//	LSvec1 = normalise(G_AnQuanDianStart - G_JinDaoDian);
//	//指向接近点方向的方向向量
//	LSvec2 = normalise(tcRotZ(3, 180.00 - in_JinTuiDaoCanShu.JieJinJiaoDu) * tcX(3));
//	if (LSvec2(1) <= LSvec1(1))
//	{
//		//说明先到达纵向安全距离位置
//		G_JieJinDian = G_JinDaoDian + (G_JinDaoDian(0) - AnQuanX) / cos(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu)) * LSvec2;
//	}
//	else
//	{
//		//说明先到达径向安全距离位置
//		G_JieJinDian = G_JinDaoDian + (AnQuanR - G_JinDaoDian(1)) / sin(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu)) * LSvec2;
//	}
//	JC_JieJinDian = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz * feibiao_xishu) * G_JieJinDian;
//#pragma endregion
//
//#pragma region 计算远离点
//	vec LSvec3;
//	//指向远离点方向的方向向量
//	LSvec3 = normalise(tcRotZ(3, in_JinTuiDaoCanShu.YuanLiJiaoDu) * tcX(3));
//	G_YuanLiDian = G_TuiDaoDian + (AnQuanR - G_TuiDaoDian(1)) / sin(tcRadians(in_JinTuiDaoCanShu.YuanLiJiaoDu)) * LSvec3;
//	JC_YuanLiDian = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz * feibiao_xishu) * G_YuanLiDian;
//#pragma endregion
//
//#pragma region 将结果插入队列
//	//在前后各复制三个元素
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//
//	//起始安全点
//	in_DaoLu.Data.at(0).G_P = G_AnQuanDianStart;
//	in_DaoLu.Data.at(0).JC_P = JC_AnQuanDianStart;
//	in_DaoLu.Data.at(0).point_type = 5;
//	//接近点
//	in_DaoLu.Data.at(1).G_P = G_JieJinDian;
//	in_DaoLu.Data.at(1).JC_P = JC_JieJinDian;
//	in_DaoLu.Data.at(1).point_type = 3;
//	//进刀点
//	in_DaoLu.Data.at(2).G_P = G_JinDaoDian;
//	in_DaoLu.Data.at(2).JC_P = JC_JinDaoDian;
//	in_DaoLu.Data.at(2).point_type = 1;
//	//结束安全点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P = G_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P = JC_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).point_type = 6;
//	//远离点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_P = G_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).JC_P = JC_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).point_type = 4;
//	//退刀点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_P = G_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).JC_P = JC_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).point_type = 2;
//#pragma endregion
//
//	return in_DaoLu;
//}

////前刀面进退刀计算-刀柄指向刀尖
//DL XiDao_QDM_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu);
//
////luoxuancao进退刀计算
//DL XiDao_LXC_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu);
//
////后刀面进退刀计算
//DL XiDao_HDM_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu);
//
////磨削路径变换
//DL XiDao_HDM_MoXue_BianHuan(DL& in_DaoLu, xt_CanShu_MoXue_BianHuan& in_BianHuan);
//
////磨削路径循环
//DL XiDao_HDM_MoXue_XunHuan(DL& in_DaoLu, xt_CanShu_MoXue_XunHuan& in_XunHuan);
//
////磨削路径阵列
//DL XiDao_HDM_MoXue_ZhenLie(DL& in_DaoLu, xt_CanShu_MoXue_ZhenLie& in_ZhenLie);
//
////刀路，转机床刀路
//DL NC_DaoLu_Cal(DL& in_DaoLu, CanShu_shalun_cal_DL& in_Shalun, xt_CanShu_MoXue_SuDu& in_Sudu);
//
//double Cal_LXC_SL_SYS_by_XH(vec3 in_qdm_p, mat33& in_sys, double in_sl_R, double in_xinhou);