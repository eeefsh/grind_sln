#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "QuMian_Grovving.h"
using namespace QuMian_Grovving_namespace;
using namespace Bezier_Curve3_QM_namespace;
void QuMian_Grovving_namespace::Gpoint::set_N(vec3 p)
{
	set_u(p);
}

void QuMian_Grovving_namespace::Gpoint::set_Qie(vec3 p)
{
	set_v(p);
}

void QuMian_Grovving_namespace::Gpoint::set_N(double _x, double _y, double _z)
{
	set_u(_x, _y, _z);
}

void QuMian_Grovving_namespace::Gpoint::set_Qie(double _x, double _y, double _z)
{
	set_v(_x, _y, _z);
}

vec3 QuMian_Grovving_namespace::Gpoint::get_N_vec3()
{
	return get_u_vec3();
}

vec3 QuMian_Grovving_namespace::Gpoint::get_Qie_vec3()
{
	return get_v_vec3();
}

mat44 QuMian_Grovving_namespace::Gpoint::get_WZ_mat44()
{
	mat44 ans = eye<mat>(4, 4); // 初始化为单位矩阵 

	// 1. 计算Y轴向量（法向量与切向量的叉积）
	vec3 y_axis = cross(get_u_vec3(), get_v_vec3());

	// 2. 计算Z轴向量（假设Z轴已通过get_N_vec3()获得）
	vec3 z_axis = get_u_vec3();
	vec3 x_axis = get_v_vec3(); // 保证右手系 

	// 3. 填充矩阵前三列 
	ans.col(0).head(3) = x_axis;
	ans.col(1).head(3) = y_axis;
	ans.col(2).head(3) = z_axis;

	// 4. 设置原点位置（第四列）
	ans.col(3).head(3) = get_xyz_vec3();
	// 5. 最后一行固定为 [0,0,0,1]
	ans.row(3) = rowvec{ 0, 0, 0, 1 };
	return ans;
}

void QuMian_Grovving_namespace::Gpoint::set_Z_normal(vec3 p)
{
	set_u(p);
}

void QuMian_Grovving_namespace::Gpoint::set_X_normal(vec3 p)
{
	set_v(p);
}

void QuMian_Grovving_namespace::Gpoint::set_Z_normal(double _x, double _y, double _z)
{
	set_u(_x, _y, _z);
}

void QuMian_Grovving_namespace::Gpoint::set_X_normal(double _x, double _y, double _z)
{
	set_v(_x, _y, _z);
}

vec3 QuMian_Grovving_namespace::Gpoint::get_Z_normal()
{
	return get_u_vec3();
}

vec3 QuMian_Grovving_namespace::Gpoint::get_X_normal()
{
	return get_v_vec3();
}

vec3 QuMian_Grovving_namespace::Gpoint::get_Y_normal()
{
	return cross(get_Z_normal(), get_X_normal());
}


void QuMian_Grovving::Set_QDM(std::vector<Gpoint>& p)
{
	QDM_point_all = p;
}

void QuMian_Grovving::Set_XHM(Bezier_Curve3_QM* p)
{
	XHM = p;
}

void QuMian_Grovving::Set_SL_data(double _sl_YuanjiaoR, double _sl_HuizhuanR, double _sl_Qiexuejiao, bool _sl_Zhou_N_flag)
{
	sl_YuanjiaoR = _sl_YuanjiaoR;
	sl_HuizhuanR = _sl_HuizhuanR;
	sl_Qiexuejiao = _sl_Qiexuejiao;
	sl_Zhou_N_flag = _sl_Zhou_N_flag;
}

bool QuMian_Grovving::Get_SL_WZ(std::vector<Gpoint>& ans)
{
	ans.clear();
	if (Init_Zhuangtai(cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v))
	{
		return 1;
	}
	Gpoint buff;

	//初始位移角根据顺逆磨削偏移一定大小，确定求解值 25.8.19 wld
	for (size_t i = 45; i > 0; i = i / 2)
	{
	
		if (Reverse_flag)
		{
			cs_SL_Weiyi_jiao = cs_SL_Weiyi_jiao - i;
			if (Xiangjiao(QDM_point_all.back(), cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v))
			{
				break;
			}
			else
			{
				cs_SL_Weiyi_jiao = cs_SL_Weiyi_jiao + i;
			}
		}
		else
		{
			cs_SL_Weiyi_jiao = cs_SL_Weiyi_jiao + i;
			if (Xiangjiao(QDM_point_all[0], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v))
			{
				break;
			}
			else
			{
				cs_SL_Weiyi_jiao = cs_SL_Weiyi_jiao - i;
			}
		}
	}
	
	

	for (size_t i = 0; i < QDM_point_all.size(); i++)
	{
		if (Reverse_flag)
		{
			buff = Optimize(QDM_point_all[QDM_point_all.size() - i - 1], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v);

		}
		else
		{
			buff = Optimize(QDM_point_all[i], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v);
		}
		if (!state_ok)
		{
			return 1;
		}
		if (!sl_Zhou_N_flag)
		{
			buff.set_Z_normal(-(buff.get_Z_normal()));
		}
		ans.push_back(buff);
	}
	//ans.pop_back();
	//ans.erase(ans.begin());

	return 0;
}

bool QuMian_Grovving::Get_SL_WZ_1(std::vector<Gpoint>& ans)
{
	ans.clear();
	Gpoint buff;
	for (size_t i = 0; i < QDM_point_all.size(); i++)
	{

		if (Reverse_flag)
		{
			if (inside_Init_Zhuangtai(QDM_point_all[QDM_point_all.size() - i - 1], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v))
			{
				return 1;
			}
			buff = Optimize(QDM_point_all[QDM_point_all.size() - i - 1], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v);
		}
		else
		{
			if (inside_Init_Zhuangtai(QDM_point_all[i], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v))
			{
				return 1;
			}
			buff = Optimize(QDM_point_all[i], cs_SL_Weiyi_jiao, cs_SL_point_t, cs_QM_u, cs_QM_v);
		}
		if (!sl_Zhou_N_flag)
		{
			buff.set_Z_normal(-(buff.get_Z_normal()));
		}
		ans.push_back(buff);
	}
	return 0;
}

void QuMian_Grovving::Grinding_route(bool _Reverse_flag)
{
	Reverse_flag = _Reverse_flag;
}

vec3 QuMian_Grovving::SL_Dong_point_out(mat44& sys, double _SL_point_t)
{
	return SL_Dong_point(sys, _SL_point_t);
}

bool QuMian_Grovving::Init_Zhuangtai(double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new)
{
	Bpoint min_P;
	vec3 Touying_QDM;
	Gpoint QDM_p0;
	if (Reverse_flag)
	{
		QDM_p0 = QDM_point_all.back();
	}
	else
	{
		QDM_p0 = QDM_point_all.front();
	}
	_SL_point_t = 0;
	min_P = find_min_dis_point(QDM_p0, _u_new, _v_new);
	Touying_QDM = (min_P - QDM_p0).get_xyz_vec3();
	Touying_QDM = tc_point_prj_to_plane(Touying_QDM, QDM_p0.get_xyz_vec3(), QDM_p0.get_N_vec3());

	vec3 target_vec = normalise(Touying_QDM - dot(QDM_p0.get_Qie_vec3(), Touying_QDM) * QDM_p0.get_Qie_vec3());
	
	_Weiyi_jiao = deltaRotAngle(target_vec, normalise(Touying_QDM), QDM_p0.get_N_vec3());
	if (Reverse_flag)
	{
		_Weiyi_jiao = 180 - _Weiyi_jiao;
	}
	if (norm(Touying_QDM) > sl_HuizhuanR)
	{
		return 1;
	}
	else
	{
		return 0;
	}



}

bool QuMian_Grovving::inside_Init_Zhuangtai(Gpoint& QDM_p0, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new)
{
	Bpoint min_P;
	vec3 Touying_QDM;
	_SL_point_t = 0;
	min_P = find_min_dis_point(QDM_p0, _u_new, _v_new);

	Touying_QDM = (min_P - QDM_p0).get_xyz_vec3();
	Touying_QDM = tc_point_prj_to_plane(Touying_QDM, QDM_p0.get_xyz_vec3(), QDM_p0.get_N_vec3());
	Touying_QDM = normalise(Touying_QDM);
	vec3 target_vec = normalise(QDM_p0.get_Qie_vec3() - dot(QDM_p0.get_Qie_vec3(), Touying_QDM) * Touying_QDM);

	_Weiyi_jiao = deltaRotAngle(QDM_p0.get_Qie_vec3(), target_vec, QDM_p0.get_N_vec3());
	if (Reverse_flag)
	{
		_Weiyi_jiao = 180 - _Weiyi_jiao;
	}
	if (norm(Touying_QDM) > sl_HuizhuanR)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Bpoint QuMian_Grovving::find_min_dis_point(Gpoint& QDM_p, double& _u_new, double& _v_new)
{
	const int MAX_ITER = 1000;       // 最大迭代次数 
	//const double TOLERANCE = 1e-9;  // 收敛阈值 
	double STEP_SIZE = 1;   // 学习率 
	const double d_TOLERANCE = 1e-4;// 收敛阈值 
	const double decay_rate = 0.9;      // 学习率衰减率
	// 初始化参数 
	double u = _u_new, v = _v_new;
	vec3 target_p = QDM_p.get_xyz_vec3();
	Bpoint current;
	vec3 surface_p;
	vec3 u_tangent;
	vec3 v_tangent;
	vec3 normal;
	vec3 residual;
	double min_distance= std::numeric_limits<double>::max();
	for (int iter = 0; iter < MAX_ITER; ++iter) 
	{
		// 获取当前曲面点信息 
		current = XHM->get_Bpoint(u, v);
		surface_p = current.get_xyz_vec3();
		u_tangent = current.get_u_vec3();
		v_tangent = current.get_v_vec3();
		normal = current.get_N_vec3();

		// 计算残差向量 
		residual = target_p - surface_p;
		double distance = norm(residual, 2);

		// 投影到切平面（牛顿法迭代）
		mat22 jacobian;
		jacobian(0, 0) = dot(u_tangent, u_tangent);
		jacobian(0, 1) = dot(u_tangent, v_tangent);
		jacobian(1, 0) = jacobian(0, 1);  // 对称矩阵 
		jacobian(1, 1) = dot(v_tangent, v_tangent);

		vec2 gradient;
		gradient(0) = dot(residual, u_tangent);
		gradient(1) = dot(residual, v_tangent);

		// 解线性方程组 J * delta = grad 
		vec2 delta = solve(jacobian, gradient);
		double row1_L, col1_L;

		XHM->get_row1_col1_L(row1_L, col1_L);
		// 更新参数（带边界约束）
		double new_u = u + STEP_SIZE * delta(0) / row1_L;
		double new_v = v + STEP_SIZE * delta(1) / col1_L;
		new_u = std::clamp(new_u, 0.0, 1.0);
		new_v = std::clamp(new_v, 0.0, 1.0);

		STEP_SIZE = 0.1 * (1.0 / (1.0 + decay_rate * iter));
		// 收敛判断 
		/*if (std::abs(new_u - u) < TOLERANCE &&
			std::abs(new_v - v) < TOLERANCE) {
			break;
		}*/
		if (distance < min_distance)
		{
			if (abs(distance - min_distance) < d_TOLERANCE)
			{
				break;
			}
			min_distance = distance;
		}

		u = new_u;
		v = new_v;
		
	}
	_u_new = u;
	_v_new = v;
	return XHM->get_Bpoint(u, v);
}

mat44 QuMian_Grovving::set_QDM_p_sys_buff(Gpoint& QDM_p)
{
	QDM_sys_buff = QDM_p.get_WZ_mat44();
	return QDM_sys_buff;
}

mat44 QuMian_Grovving::SL_wz_sys(Gpoint& QDM_p, double SL_Weiyi_jiao)
{
	SL_sys_buff = eye<mat>(4, 4);

	SL_sys_buff = set_QDM_p_sys_buff(QDM_p) * SL_sys_buff;
	SL_sys_buff = SL_sys_buff * tcRotZ(4, SL_Weiyi_jiao);
	SL_sys_buff = SL_sys_buff * tcRotY(4, sl_Qiexuejiao);
	SL_sys_buff.col(3)= SL_sys_buff.col(3) +  QDM_sys_buff.col(2)* sl_YuanjiaoR;
	SL_sys_buff = SL_sys_buff * tcTranslate(-(sl_HuizhuanR - sl_YuanjiaoR), 0, 0);

	//SL_sys_buff = SL_sys_buff * tcTranslate(0, 0, sl_YuanjiaoR);
	//SL_sys_buff = rotate_coord_around_axis(SL_sys_buff, QDM_sys_buff, SL_Weiyi_jiao, 2);
	
	return SL_sys_buff;
}

vec3 QuMian_Grovving::SL_Dong_point(mat44& sys, double _SL_point_t)
{
	vec4 p = { sl_HuizhuanR - sl_YuanjiaoR,0,0,1 };

	p = tcRotZ(4, _SL_point_t) * p;
	p = sys * p;
	SL_Dong_point_buff = p.head(3);
	return SL_Dong_point_buff;
}

vec3 QuMian_Grovving::SL_Dong_point_Qie(mat44& sys, double _SL_point_t)
{
	vec4 p = { 0,1,0,0 };
	p = tcRotZ(4, _SL_point_t) * p;
	p = sys * p;
	vec3 ans;
	ans = p.head(3);
	return ans;
}
Gpoint QuMian_Grovving::Optimize(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new)
{
	const int max_iter = 200;					// 最大迭代次数
	const int max_num = 4;						// 最大不变次数
	const double tolerance = 1e-3;				// 收敛容差
	const double dt = 1e-4;						// 求导步长
	const double decay_rate = 0.5;				// 位移角增量衰减率
	double Weiyi_jiao_increment = 2;			// 位移角增量

	double Weiyi_jiao = _Weiyi_jiao;
	double SL_point_t = _SL_point_t;
	double u_new = _u_new;
	double v_new = _v_new;
	
	double min_theta = std::numeric_limits<double>::max();
	double f_theta_last = std::numeric_limits<double>::max();
	unsigned char num = 0;
	for (size_t i = 0; i < max_iter; i++)
	{
		bool xiangjiao_flag = Xiangjiao(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		if (xiangjiao_flag)//判断相交
		{
			double f_theta = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
			if (abs(f_theta) < min_theta)
			{
				min_theta = abs(f_theta);
				Weiyi_jiao = _Weiyi_jiao;
				SL_point_t = _SL_point_t;
				u_new = _u_new;
				v_new = _v_new;
			}

			if (abs(f_theta_last - f_theta) < tolerance)
			{
				num++;
				if (num >= max_num)
				{
					_Weiyi_jiao = Weiyi_jiao;
					_SL_point_t = SL_point_t;
					_u_new = u_new;
					_v_new = v_new;
					break;
				}
			}
			else
			{
				num = 0;
			}

			f_theta_last = f_theta;
			
			double f_theta_daoshu = f_tiaojian_daoshu(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new, dt);


			_Weiyi_jiao = _Weiyi_jiao - (f_theta / f_theta_daoshu);
			Weiyi_jiao_increment = -(f_theta / f_theta_daoshu);
			//if (abs(Weiyi_jiao_increment) > 80.0)
			//{
			//	_Weiyi_jiao = _Weiyi_jiao - Weiyi_jiao_increment;
			//	Weiyi_jiao_increment *= 0.5;
			//	_Weiyi_jiao += Weiyi_jiao_increment;
			//}
			if (min_theta < tolerance)
			{
				//相切了
				_Weiyi_jiao = Weiyi_jiao;
				_SL_point_t = SL_point_t;
				_u_new = u_new;
				_v_new = v_new;
				break;
			}

		}
		else
		{
			if (i == 0)
			{
				do
				{
					if (Reverse_flag)//前刀面点y方向指向芯厚面，调整旋转方向25-8-12gqx
					{
						_Weiyi_jiao = _Weiyi_jiao + Weiyi_jiao_increment;
					}
					else
					{
						_Weiyi_jiao = _Weiyi_jiao - Weiyi_jiao_increment;
					}
					if (abs(_Weiyi_jiao) > 1000)
					{
						state_ok = 0;
						return Gpoint();
					}
				} while (!Xiangjiao(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new));
			}
			else
			{
				Weiyi_jiao_increment = Weiyi_jiao_increment * decay_rate;
				if (Reverse_flag)//前刀面点y方向指向芯厚面，调整旋转方向25-8-12gqx
				{
					_Weiyi_jiao = _Weiyi_jiao - (Weiyi_jiao_increment);
				}
				else
				{
					_Weiyi_jiao = _Weiyi_jiao - Weiyi_jiao_increment;
				}
				
			}
		}
	}


	_Weiyi_jiao = Weiyi_jiao;
	_SL_point_t = SL_point_t;
	_u_new = u_new;
	_v_new = v_new;

	Gpoint ans;
	SL_sys_buff = SL_wz_sys(QDM_p, _Weiyi_jiao);

	vec3 temp_ans;
	temp_ans = SL_sys_buff.col(3).head(3);
	ans.set_xyz(temp_ans);
	temp_ans = SL_sys_buff.col(0).head(3);
	ans.set_X_normal(temp_ans);
	temp_ans = SL_sys_buff.col(2).head(3);
	ans.set_Z_normal(temp_ans);
	return ans;
}

double QuMian_Grovving::f_tiaojian(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new)
{
	vec3 point_Qie;
	vec3 mian_p_N;
	SL_sys_buff = SL_wz_sys(QDM_p, _Weiyi_jiao);
	point_Qie = SL_Dong_point_Qie(SL_sys_buff, _SL_point_t);
	mian_p_N = XHM->get_Bpoint(_u_new, _v_new).get_N_vec3();
	//double jia_jiao = acos(abs(dot(point_Qie, mian_p_N)));//计算夹角
	double jia_jiao = acos((dot(point_Qie, mian_p_N)));//计算夹角 8.18
	jia_jiao = jia_jiao * 180 / datum::pi;
	//return abs(jia_jiao - 90);
	return jia_jiao - 90;
}

double QuMian_Grovving::f_tiaojian_daoshu(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new, double dt)
{
	double Weiyi_jiao = _Weiyi_jiao;
	double SL_point_t = _SL_point_t;
	double u_new = _u_new;
	double v_new = _v_new;
	double f0 = 0, f1 = 0;
	double ans;
	double dt_o = dt;

	while (1)
	{
		_Weiyi_jiao = Weiyi_jiao;
		//if (Reverse_flag)
		//{
		//	f0 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		//	_Weiyi_jiao += dt;
		//	if (Xiangjiao(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new))
		//	{
		//		f1 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		//	}
		//	else
		//	{
		//		f1 = f0;//不能进入
		//	}
		//	ans = (f1 - f0) / dt;
		//}
		//else
		//{
		//	f0 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		//	_Weiyi_jiao += dt;
		//	if (Xiangjiao(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new))
		//	{
		//		f1 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		//	}
		//	else
		//	{
		//		f1 = f0;
		//	}
		//	ans = (f1 - f0) / dt;
		//}

		f0 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		_Weiyi_jiao += dt;
		if (Xiangjiao(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new))
		{
			f1 = f_tiaojian(QDM_p, _Weiyi_jiao, _SL_point_t, _u_new, _v_new);
		}
		else
		{
			f1 = f0;
		}
		ans = (f1 - f0) / dt;
		if (abs(f1 - f0) < dt_o)
		{
			dt = dt * 10;
		}
		else
		{
			break;
		}
	} 
	
	


	_Weiyi_jiao = Weiyi_jiao;
	_SL_point_t = SL_point_t;
	_u_new = u_new;
	_v_new = v_new;
	return ans;
}

bool QuMian_Grovving::Xiangjiao(Gpoint& QDM_p, double& _Weiyi_jiao, double& _SL_point_t, double& _u_new, double& _v_new)
{
	const int max_iter = 10;       // 最大迭代次数 
	const double tolerance = 1e-6;  // 收敛容差 
	const double tolerance2 = 1e-9;  // 收敛容差 
	const double step_size = 0.001;  // 初始步长 
	double distance;


	// 初始化变量 
	double t = _SL_point_t;
	double u = _u_new;
	double v = _v_new;

	// 获取初始坐标系 
	mat44 wz_sys = SL_wz_sys(QDM_p, _Weiyi_jiao);

	// 搜索方向 
	double delta = Reverse_flag ? -step_size : step_size;

	// 首先尝试在初始点附近寻找解 
	for (int iter = 0; iter < max_iter; ++iter)
	{
		// 获取当前圆上点和曲面点 
		vec3 dong_p = SL_Dong_point(wz_sys, t);
		Bpoint mian_p = XHM->get_Bpoint(u, v);
		mian_p.set_xyz(mian_p.get_xyz_vec3() + mian_p.get_N_vec3() * sl_YuanjiaoR);//曲面偏置一个圆角半径
		vec3 xyz = mian_p.get_xyz_vec3();

		// 计算残差向量 
		vec3 F = dong_p - xyz;
		distance = arma::norm(F);

		// 检查是否收敛 
		if (distance < tolerance) {
			_SL_point_t = t;
			_u_new = u;
			_v_new = v;
			distance = 0;
			return true;
		}
		

		// 计算雅可比矩阵 
		// 数值方法计算偏导数 
		vec3 dong_p_t = SL_Dong_point(wz_sys, t + delta /10.0) - SL_Dong_point(wz_sys, t - delta/10.0);
		//vec3 dong_p_u = SL_Dong_point(wz_sys, t) - SL_Dong_point(wz_sys, t); // 实际上u不影响dong_p 

		Bpoint mian_p_u = XHM->get_Bpoint(u + step_size, v);
		mian_p_u.set_xyz(mian_p_u.get_xyz_vec3() + mian_p_u.get_N_vec3() * sl_YuanjiaoR);//曲面偏置一个圆角半径
		Bpoint mian_p_v = XHM->get_Bpoint(u, v + step_size);
		mian_p_v.set_xyz(mian_p_v.get_xyz_vec3() + mian_p_v.get_N_vec3() * sl_YuanjiaoR);//曲面偏置一个圆角半径

		vec3 dx_du = (mian_p_u.get_xyz_vec3() - xyz) / step_size;
		vec3 dx_dv = (mian_p_v.get_xyz_vec3() - xyz) / step_size;

		arma::mat33 J;
		J.col(0) = dong_p_t / (2 * delta / 10.0);  // dF/dt 
		J.col(1) = -dx_du;                  // dF/du 
		J.col(2) = -dx_dv;                  // dF/dv 

		// 解线性方程组 J * delta_x = -F 
		arma::vec3 delta_x;
		if (!arma::solve(delta_x, J, -F)) {
			// 矩阵奇异，无法求解 
			break;
		}

		// 更新变量 
		t += delta_x(0);
		u += delta_x(1);
		v += delta_x(2);

		// 确保参数在有效范围内 
		t = fmod(t, 360.0);
		if (t < 0) t += 360.0;
		u = std::max(0.0, std::min(1.0, u));
		v = std::max(0.0, std::min(1.0, v));
	}

	return false;
}

//bool QuMian_Grovving::Xiangjiao(Gpoint& QDM_p, double& _Weiyi_jiao,
//	double& _SL_point_t, double& _u_new, double& _v_new)
//{
//	constexpr int max_iter = 10;
//	constexpr double tolerance = 1e-6;
//	constexpr double tolerance2 = 1e-9;
//	constexpr double step_size = 0.001;
//	constexpr double h = 1e-5;
//	constexpr double MIN_PARAM = 0.0;
//	constexpr double MAX_PARAM = 1.0;
//	constexpr double FULL_CIRCLE = 360.0;
//
//	// 初始化
//	double t = _SL_point_t;
//	double u = _u_new;
//	double v = _v_new;
//	double prev_distance = std::numeric_limits<double>::max();
//
//	mat44 wz_sys = SL_wz_sys(QDM_p, _Weiyi_jiao);
//	const double delta = Reverse_flag ? -step_size : step_size;
//
//	for (int iter = 0; iter < max_iter; ++iter)
//	{
//		// 当前点计算 
//		const vec3 dong_p = SL_Dong_point(wz_sys, t);
//		Bpoint mian_p = XHM->get_Bpoint(u, v);
//		mian_p.set_xyz(mian_p.get_xyz_vec3() + mian_p.get_N_vec3() * sl_YuanjiaoR);
//		const vec3 xyz = mian_p.get_xyz_vec3();
//
//		// 残差计算 
//		const vec3 F = dong_p - xyz;
//		const double distance = arma::norm(F);
//
//		// 收敛检查 
//		/*if (distance < tolerance ||
//			(iter > 0 && std::abs(distance - prev_distance) < tolerance2))*/
//		if (distance < tolerance)
//		{
//			_SL_point_t = t;
//			_u_new = u;
//			_v_new = v;
//			return true;
//		}
//		prev_distance = distance;
//
//		// 雅可比矩阵计算
//		const vec3 dong_p_t = (SL_Dong_point(wz_sys, t + h) - SL_Dong_point(wz_sys, t - h)) / (2 * h);
//
//		Bpoint mian_p_u = XHM->get_Bpoint(u + step_size, v);
//		mian_p_u.set_xyz(mian_p_u.get_xyz_vec3() + mian_p_u.get_N_vec3() * sl_YuanjiaoR);
//		Bpoint mian_p_v = XHM->get_Bpoint(u, v + step_size);
//		mian_p_v.set_xyz(mian_p_v.get_xyz_vec3() + mian_p_v.get_N_vec3() * sl_YuanjiaoR);
//
//		const vec3 dx_du = (mian_p_u.get_xyz_vec3() - xyz) / step_size;
//		const vec3 dx_dv = (mian_p_v.get_xyz_vec3() - xyz) / step_size;
//
//		arma::mat33 J;
//		J.col(0) = dong_p_t;
//		J.col(1) = -dx_du;
//		J.col(2) = -dx_dv;
//
//		// 求解线性系统 
//		arma::vec3 delta_x;
//		if (!arma::solve(delta_x, J, -F, arma::solve_opts::fast)) {
//			break;
//		}
//
//		// 更新参数
//		t = fmod(t + delta_x(0), FULL_CIRCLE);
//		if (t < 0) t += FULL_CIRCLE;
//		u = std::clamp(u + delta_x(1), MIN_PARAM, MAX_PARAM);
//		v = std::clamp(v + delta_x(2), MIN_PARAM, MAX_PARAM);
//	}
//
//	return false;
//}

mat44 QuMian_Grovving_namespace::rotate_coord_around_axis(const mat44& coord_a, const mat44& coord_b, double angle_deg, int axis)
{
	// 参数校验 
	if (axis < 0 || axis > 2)
	{
		throw std::invalid_argument("Axis must be 0(X), 1(Y) or 2(Z)");
	}

	// 角度转弧度 
	const double angle_rad = datum::pi * angle_deg / 180.0;

	// 步骤1：计算坐标系B的逆变换 
	mat44 inv_b = inv(coord_b);

	// 步骤2：构建旋转矩阵（在B的局部坐标系下）
	mat44 rotation = eye<mat>(4, 4);
	const double cos_theta = cos(angle_rad);
	const double sin_theta = sin(angle_rad);

	switch (axis)
	{
	case 0: // X轴旋转 
		rotation(1, 1) = cos_theta;
		rotation(1, 2) = -sin_theta;
		rotation(2, 1) = sin_theta;
		rotation(2, 2) = cos_theta;
		break;
	case 1: // Y轴旋转 
		rotation(0, 0) = cos_theta;
		rotation(0, 2) = sin_theta;
		rotation(2, 0) = -sin_theta;
		rotation(2, 2) = cos_theta;
		break;
	case 2: // Z轴旋转 
		rotation(0, 0) = cos_theta;
		rotation(0, 1) = -sin_theta;
		rotation(1, 0) = sin_theta;
		rotation(1, 1) = cos_theta;
		break;
	}

	// 步骤3：复合变换 = B * 旋转 * B⁻¹ * A 
	return coord_b * rotation * inv_b * coord_a;
}
