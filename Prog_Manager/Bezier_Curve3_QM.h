#pragma once
#include"manager_h/xt_armadillo_settings.h"

namespace Bezier_Curve3_QM_namespace
{
	//贝塞尔曲面专用点类型
	class Bpoint
	{
	private:
		double x = 0;
		double y = 0;
		double z = 0;

		double u_x = 0;
		double u_y = 0;
		double u_z = 0;

		double v_x = 0;
		double v_y = 0;
		double v_z = 0;

	public:
		Bpoint(double x_, double y_, double z_,
			double ux_, double uy_, double uz_,
			double vx_, double vy_, double vz_);
		Bpoint() {};
		vec3 get_xyz_vec3();
		vec3 get_u_vec3();
		vec3 get_v_vec3();
		vec3 get_N_vec3();

		void set_xyz(vec3 p);
		void set_u(vec3 p);
		void set_v(vec3 p);

		void set_xyz(double _x, double _y, double _z);
		void set_u(double _x, double _y, double _z);
		void set_v(double _x, double _y, double _z);

		// 重载 + 运算符（成员函数形式）
		Bpoint operator+(const Bpoint& rhs) const;

		// 重载 - 运算符（成员函数形式）
		Bpoint operator-(const Bpoint& rhs) const;
		friend Bpoint operator*(double d, const Bpoint& obj);
		friend Bpoint operator*(const Bpoint& obj, double d);

		Bpoint operator/(double rhs) const;
	};
	
	void Bezier_3(const Bpoint p0, const Bpoint p1, const Bpoint p2, const Bpoint p3, double t, Bpoint& ans);
}


//三次贝塞尔曲面类
class Bezier_Curve3_QM
{
	using Bpoint = Bezier_Curve3_QM_namespace::Bpoint;
public:

	/// @brief 初始化输入贝塞尔曲面专用类型的点
	/// @param _all_point 以二维数组规则有序输入的vector<Bpoint>
	/// @param _rows 设置行数
	/// @param _cols 设置列数
	void Init_input(std::vector<Bpoint> _all_point, unsigned int _rows, unsigned int _cols);

	/// @brief 输入uv参数获取面上的点
	/// @param u 切向参数[0-1]
	/// @param v 切向参数[0-1]
	/// @return 贝塞尔曲面专用点类型
	Bpoint get_Bpoint(double u, double v);

	//曲面法向方向切换,属于模态指令，后续取点也将持续该方向
	//(内部将翻转v切向,使得法向n=cross(u,v))
	void Reverse_Normal();

	//获取第一行和第一列的长度
	void get_row1_col1_L(double& row1_L, double& col1_L);

private:
	std::vector<Bpoint> all_point;
	unsigned int rows = 0;
	unsigned int cols = 0;
	bool Reverse_flag = 0;	//法向翻转标记

	std::vector<double> u_Changdu_buff;
	std::vector<double> v_Changdu_buff;

	void Jisuan_Changdu();
	void Jisuan_u_Changdu(std::vector<Bpoint>& row_1);
	void Jisuan_v_Changdu(std::vector<Bpoint>& col_1);

	void get_row_1_col_1(std::vector<Bpoint>& row_1, std::vector<Bpoint>& col_1);
	Bpoint get_a_Bpoint_in_vector(int row, int col);
	
	void find_Weizhi(std::vector<double>& all_L, double L, int& wei_1, int& wei_2);

	void Check_Input();

	/// @brief 最小面插值函数
	/// @param P_a 
	/// @param P_b 
	/// @param P_c 
	/// @param P_d 
	/// @param u 
	/// @param v 
	/// @param ans 
	void Mian_min(Bpoint& P_a, Bpoint& P_b, Bpoint& P_c, Bpoint& P_d, double u, double v, Bpoint& ans);
	void get_a_Bpoint_u(Bpoint& P_1, Bpoint& P_2, double u, Bpoint& ans);
	void get_a_Bpoint_v(Bpoint& P_1, Bpoint& P_2, double v, Bpoint& ans);
};

//输入曲线(点+切向)、轴，按右手定理旋转in_theta(角度)形成回转体，形成贝塞尔曲面
//曲线由离散点及点切向（3*n矩阵）组成，应分布均匀；曲线、轴必须共面
//u法向为回转，in_num_u个点；v法向沿轴向，点数in_vec_p.n_cols
Bezier_Curve3_QM Get_Bezier_Curve3_QM_HZ(mat in_vec_p, mat in_vec_t,
	vec3 line_p, vec3 line_t, double in_num_u, double in_theta);

//输入曲线(点+切向)、引导线(点+切向)，曲线为u方向，引导线为v方向
//u方向点的数量由曲线决定、v方向点的数量由引导线决定
Bezier_Curve3_QM Get_Bezier_Curve3_QM_SL(mat in_qx_p, mat in_qx_t, mat in_ydx_p, mat in_ydx_v);

//in_num_u阵列个数，in_delta_theta 阵列步长角度
Bezier_Curve3_QM Get_Bezier_Curve3_QM_HZ(mat in_vec_p, mat in_vec_t, vec3 line_p,
	vec3 line_t, int in_num_u, double  in_delta_theta);

//1、旋转范围？ 6.14
//2、平面线与回转轴相交？

