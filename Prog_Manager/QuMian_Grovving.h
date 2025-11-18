#pragma once
#include "manager_h/MA_010201_Cal_JiHe_JiBen.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include "manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"
#include "Bezier_Curve3_QM.h"

class QuMian_Grovving;
namespace QuMian_Grovving_namespace
{
	//芯厚面计算专用点类
	class Gpoint :
		private Bezier_Curve3_QM_namespace::Bpoint
	{
	public:
		using Bpoint::set_xyz;
		using Bpoint::get_xyz_vec3;
		void set_N(vec3 p);
		void set_Qie(vec3 p);
		void set_N(double _x, double _y, double _z);
		void set_Qie(double _x, double _y, double _z);
		vec3 get_N_vec3();
		vec3 get_Qie_vec3();
		//获取位置4*4齐次变换矩阵
		//第一列为x向量
		//第二列为y向量
		//第三列为z向量
		//第四列为点位置
		mat44 get_WZ_mat44();
	private:
		void set_Z_normal(vec3 p);
		void set_X_normal(vec3 p);
		void set_Z_normal(double _x, double _y, double _z);
		void set_X_normal(double _x, double _y, double _z);
		vec3 get_Z_normal();
		vec3 get_X_normal();
		vec3 get_Y_normal();
		friend class QuMian_Grovving;
	};

	/// @brief 计算坐标系A绕坐标系B的指定轴旋转后的新坐标系
	/// @param coord_a 待旋转的坐标系A（4x4齐次变换矩阵）
	/// @param coord_b 参考坐标系B（4x4齐次变换矩阵）
	/// @param angle_deg 旋转角度（度）
	/// @param axis 旋转轴（0:X轴，1:Y轴，2:Z轴）
	/// @return 旋转后的新坐标系（4x4矩阵）
	mat44 rotate_coord_around_axis(const mat44& coord_a, const mat44& coord_b, double angle_deg, int axis);
}


class QuMian_Grovving
{
	using Gpoint = QuMian_Grovving_namespace::Gpoint;	//芯厚面计算专用点类
	using Bpoint = Bezier_Curve3_QM_namespace::Bpoint;	//贝塞尔曲面专用点类
private:
	Bezier_Curve3_QM* XHM;				//芯厚面
	std::vector<Gpoint> QDM_point_all;	//前刀面点集
	double sl_YuanjiaoR = 0;			//砂轮圆角半径
	double sl_HuizhuanR = 0;			//砂轮回转半径
	double sl_Qiexuejiao = 0;			//砂轮切削角度（角度制）
	bool sl_Zhou_N_flag = 1;			//砂轮轴反向设置标记0：砂轮轴与前刀面法向相反 1：砂轮轴与前刀面法向相同（默认）
	bool Reverse_flag = 0;				//顺逆路径磨削设置标记0：顺路径磨削，1：逆路径磨削
	bool state_ok = 1;					//0:优化失败（死性循环） 1:优化成功
public:
	bool get_state_ok()
	{
		return state_ok;
	}
	//设置前刀面点
	void Set_QDM(std::vector<Gpoint>& p);

	/// @brief 初始化输入贝塞尔曲面专用类型的点
	/// @param p 以二维数组规则有序输入的vector<Bpoint>
	/// @param rows 设置行数
	/// @param cols 设置列数
	void Set_XHM(Bezier_Curve3_QM* p);

	/// @brief 设置砂轮参数
	/// @param _sl_YuanjiaoR 砂轮圆角半径
	/// @param _sl_HuizhuanR 砂轮回转半径
	/// @param _sl_Qiexuejiao 切削角度
	/// @param _sl_Zhou_N 砂轮轴反向设置：0：砂轮轴与前刀面法向相反 1：砂轮轴与前刀面法向相同（默认）
	void Set_SL_data(double _sl_YuanjiaoR, double _sl_HuizhuanR, double _sl_Qiexuejiao, bool _sl_Zhou_N_flag = 1);

	//获取砂轮位置状态
	//获取失败返回1，成功返回0
	bool Get_SL_WZ(std::vector<Gpoint>& ans);

	/// @brief 顺逆路径磨削设置
	/// @param Reverse 0：顺路径磨削，1：逆路径磨削
	void Grinding_route(bool _Reverse_flag = 0);

	//(测试使用)获取砂轮动点位置
	vec3 SL_Dong_point_out(mat44& sys, double _SL_point_t);
private:
	double cs_SL_point_t = 0;		//砂轮点控制参数(0-360角度)
	double cs_SL_Weiyi_jiao = 0;	//砂轮位移角
	double cs_QM_u = 0.5;			//曲面控制参数u
	double cs_QM_v = 0.5;			//曲面控制参数v
private:
	mat44 QDM_sys_buff;
	mat44 SL_sys_buff;
	vec3 SL_Dong_point_buff;

private:
	//初始状态设置,设置4个关键参数，如果初始状态不满足相切返回1，满足相切返回0
	bool Init_Zhuangtai(double& _Weiyi_jiao,double& _SL_point_t, double& _u_new, double& _v_new);
	//内部初始状态
	bool inside_Init_Zhuangtai(Gpoint& QDM_p0, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new);
	//寻找曲面和输入点的最近点
	Bpoint find_min_dis_point(Gpoint& QDM_p, double& _u_new, double& _v_new);
	//根据前刀面点设置临时相对坐标系
	mat44 set_QDM_p_sys_buff(Gpoint& QDM_p);
	//获取砂轮变换后的坐标信息
	mat44 SL_wz_sys(Gpoint& QDM_p, double SL_Weiyi_jiao);
	//获取砂轮动点位置
	vec3 SL_Dong_point(mat44& sys, double _SL_point_t);
	//获取砂轮动点切向
	vec3 SL_Dong_point_Qie(mat44& sys, double _SL_point_t);
	
	//优化函数
	Gpoint Optimize(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new);
	//牛顿迭代法目标函数（曲面法向和圆上动点切向夹角与90度的差值）
	double f_tiaojian(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new);
	//牛顿迭代法目标函数导数
	double f_tiaojian_daoshu(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new, double dt);
	
	//相交返回1，不相交返回0
	bool Xiangjiao(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new);

	//获取砂轮位置状态
	//获取失败返回1，成功返回0
	bool Get_SL_WZ_1(std::vector<Gpoint>& ans);
	
};

