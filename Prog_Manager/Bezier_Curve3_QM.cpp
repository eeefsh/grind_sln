#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS

#include "Bezier_Curve3_QM.h"
#include "manager_h/MA_010201_Cal_JiHe_JiBen.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include "manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"

namespace Bezier_Curve3_QM_namespace
{
	Bpoint::Bpoint(double x_, double y_, double z_, double ux_, double uy_, double uz_, double vx_, double vy_, double vz_)
		: x(x_), y(y_), z(z_),
		u_x(ux_), u_y(uy_), u_z(uz_),
		v_x(vx_), v_y(vy_), v_z(vz_) {
	}

	vec3 Bpoint::get_xyz_vec3()
	{
		vec3 ans = { x,y,z };
		return ans;
	}

	vec3 Bpoint::get_u_vec3()
	{
		vec3 ans = { u_x,u_y,u_z };
		return normalise(ans);
	}

	vec3 Bpoint::get_v_vec3()
	{
		vec3 ans = { v_x,v_y,v_z };
		return normalise(ans);
	}

	vec3 Bpoint::get_N_vec3()
	{
		vec3 temp_u = { u_x,u_y,u_z };
		vec3 temp_v = { v_x,v_y,v_z };
		return normalise(cross(temp_u, temp_v));
	}

	void Bpoint::set_xyz(vec3 p)
	{
		x = p(0);
		y = p(1);
		z = p(2);
	}

	void Bpoint::set_u(vec3 p)
	{
		u_x = p(0);
		u_y = p(1);
		u_z = p(2);
	}

	void Bpoint::set_v(vec3 p)
	{
		v_x = p(0);
		v_y = p(1);
		v_z = p(2);
	}

	void Bpoint::set_xyz(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Bpoint::set_u(double _x, double _y, double _z)
	{
		u_x = _x;
		u_y = _y;
		u_z = _z;
	}

	void Bpoint::set_v(double _x, double _y, double _z)
	{
		v_x = _x;
		v_y = _y;
		v_z = _z;
	}

	// 重载 + 运算符（成员函数形式）
	Bpoint Bpoint::operator+(const Bpoint& rhs) const
	{

		Bpoint temp;
		temp.x = x + rhs.x;
		temp.y = y + rhs.y;
		temp.z = z + rhs.z;

		return temp;
	}

	// 重载 - 运算符（成员函数形式）
	Bpoint Bpoint::operator-(const Bpoint& rhs) const
	{
		Bpoint temp;
		temp.x = x - rhs.x;
		temp.y = y - rhs.y;
		temp.z = z - rhs.z;


		return temp;
	}
	Bpoint Bpoint::operator/(double rhs) const
	{
		Bpoint ans;
		ans.x = x / rhs;
		ans.y = y / rhs;
		ans.z = z / rhs;
		return ans;
	}
	Bpoint operator*(double d, const Bpoint& obj)
	{
		Bpoint ans;
		ans.x = obj.x * d;
		ans.y = obj.y * d;
		ans.z = obj.z * d;
		return ans;
	}
	Bpoint operator*(const Bpoint& obj, double d)
	{
		Bpoint ans;
		ans.x = obj.x * d;
		ans.y = obj.y * d;
		ans.z = obj.z * d;
		return ans;
	}
	
	void Bezier_3(Bpoint p0, Bpoint p1, Bpoint p2, Bpoint p3, double t, Bpoint& ans) {
		// 计算伯恩斯坦基函数系数 
		double t2 = t * t;              // t² 
		double t3 = t2 * t;             // t³ 
		double mt = 1.0 - t;            // (1-t)
		double mt2 = mt * mt;           // (1-t)² 
		double mt3 = mt2 * mt;          // (1-t)³ 

		// 三次贝塞尔曲线公式 
		ans = p0 * mt3				// (1-t)³ * P0 
			+ p1 * (3 * mt2 * t)	// 3(1-t)²t * P1 
			+ p2 * (3 * mt * t2)	// 3(1-t)t² * P2 
			+ p3 * t3;				// t³ * P3 
	}

	double BezierArcLength(Bpoint P0, Bpoint P1, Bpoint P2, Bpoint P3, int N = 1000) 
	{
		double L = 0.0;
		Bpoint prev = P0;
		Bpoint curr;
		for (int i = 1; i <= N; ++i) 
		{
			double t = i / double(N);
			Bezier_3(P0, P1, P2, P3, t, curr); // 调用原有函数 
			L += norm((curr - prev).get_xyz_vec3()); // norm为向量模长计算 
			prev = curr;
		}
		return L;
	}

	// 线性插值函数：输入起始向量、目标向量、插值系数t，返回中间向量 
	vec3 lerpVec3(vec3 start, vec3 end, double t) 
	{
		// 计算差值向量并通过t参数插值 
		return normalise(start + t * (end - start));
	}

	// 返回类型为 std::pair<迭代器, 迭代器>
	std::pair<std::vector<double>::const_iterator, std::vector<double>::const_iterator>
		find_neighbors(const std::vector<double>& sorted_seq, double x)
	{
		auto it = std::lower_bound(sorted_seq.begin(), sorted_seq.end(), x);

		if (it == sorted_seq.begin()) {
			return std::make_pair(sorted_seq.end(), it); // x 比所有数小 
		}
		else if (it == sorted_seq.end()) {
			return std::make_pair(std::prev(it), sorted_seq.end());  // x 比所有数大 
		}
		else {
			return std::make_pair(std::prev(it), it); // x 在中间 
		}
	}
}

using namespace Bezier_Curve3_QM_namespace;

void Bezier_Curve3_QM::Init_input(std::vector<Bpoint> _all_point, unsigned int _rows, unsigned int _cols)
{
	all_point = _all_point;
	rows = _rows;
	cols = _cols;
	Check_Input();
	Jisuan_Changdu();
}


Bpoint Bezier_Curve3_QM::get_Bpoint(double u, double v)
{
	double u_L = u_Changdu_buff.back();
	double v_L = v_Changdu_buff.back();
	u_L = u * u_L;
	v_L = (1 - v) * v_L;

	int u1 = 0, u2 = 0;
	find_Weizhi(u_Changdu_buff, u_L, u1, u2);
	int v1 = 0, v2 = 0;
	find_Weizhi(v_Changdu_buff, v_L, v1, v2);

	auto new_u = (u_L - u_Changdu_buff[u1]) / (u_Changdu_buff[u2] - u_Changdu_buff[u1]);
	auto new_v = (v_L - v_Changdu_buff[v1]) / (v_Changdu_buff[v2] - v_Changdu_buff[v1]);
	auto p0 = get_a_Bpoint_in_vector(v1, u1);
	auto p1 = get_a_Bpoint_in_vector(v1, u2);
	auto p2 = get_a_Bpoint_in_vector(v2, u2);
	auto p3 = get_a_Bpoint_in_vector(v2, u1);

	Bpoint ans;
	Mian_min(p0, p1, p2, p3, new_u, new_v, ans);

	if (Reverse_flag)
	{
		vec3 temp_v = -ans.get_v_vec3();
		ans.set_v(temp_v);
	}
	return ans;
}

void Bezier_Curve3_QM::Reverse_Normal()
{
	Reverse_flag = !Reverse_flag;
}

void Bezier_Curve3_QM::get_row1_col1_L(double& row1_L, double& col1_L)
{
	row1_L = u_Changdu_buff.back();
	col1_L = v_Changdu_buff.back();
}

void Bezier_Curve3_QM::Jisuan_Changdu()
{
	std::vector<Bpoint> row_1;
	std::vector<Bpoint> col_1;
	get_row_1_col_1(row_1, col_1);
	Jisuan_u_Changdu(row_1);
	Jisuan_v_Changdu(col_1);
}

void Bezier_Curve3_QM::Jisuan_u_Changdu(std::vector<Bpoint>& row_1)
{
	vec3 temp_data;
	Bpoint Xudian_1u;
	Bpoint Xudian_2u;
	double L = 0;
	u_Changdu_buff.clear();
	u_Changdu_buff.push_back(0);

	for (size_t i = 0; i < row_1.size() - 1; i++)
	{

		auto d_1_3 = norm(((row_1[i] - row_1[i+1]) / 3).get_xyz_vec3());

		temp_data = (row_1[i].get_u_vec3() * d_1_3) + row_1[i].get_xyz_vec3();
		Xudian_1u.set_xyz(temp_data);
		temp_data = (row_1[i + 1].get_u_vec3() * (-d_1_3)) + row_1[i + 1].get_xyz_vec3();
		Xudian_2u.set_xyz(temp_data);

		L = L + BezierArcLength(row_1[i], Xudian_1u, Xudian_2u, row_1[i + 1]);
		u_Changdu_buff.push_back(L);
	}
}

void Bezier_Curve3_QM::Jisuan_v_Changdu(std::vector<Bpoint>& col_1)
{
	vec3 temp_data;
	Bpoint Xudian_1v;
	Bpoint Xudian_2v;
	double L = 0;
	v_Changdu_buff.clear();
	v_Changdu_buff.push_back(0);

	for (size_t i = 0; i < col_1.size() - 1; i++)
	{

		auto d_1_3 = norm(((col_1[i] - col_1[i + 1]) / 3).get_xyz_vec3());

		temp_data = (col_1[i].get_v_vec3() * (-d_1_3)) + col_1[i].get_xyz_vec3();
		Xudian_1v.set_xyz(temp_data);
		temp_data = (col_1[i + 1].get_v_vec3() * d_1_3) + col_1[i + 1].get_xyz_vec3();
		Xudian_2v.set_xyz(temp_data);

		/*auto d_1_3 = norm(((P_1 - P_2) / 3).get_xyz_vec3());

		temp_data = (P_1.get_v_vec3() * (-d_1_3)) + P_1.get_xyz_vec3();
		Xudian_1v.set_xyz(temp_data);
		temp_data = (P_2.get_v_vec3() * d_1_3) + P_2.get_xyz_vec3();
		Xudian_2v.set_xyz(temp_data);
		Bezier_3(P_1, Xudian_1v, Xudian_2v, P_2, v, ans);*/

		L = L + BezierArcLength(col_1[i], Xudian_1v, Xudian_2v, col_1[i + 1]);
		v_Changdu_buff.push_back(L);
	}
}



void Bezier_Curve3_QM::get_row_1_col_1(std::vector<Bpoint>& row_1, std::vector<Bpoint>& col_1)
{
	// --- 1. 清空输出容器 ---
	row_1.clear();
	col_1.clear();

	// --- 2. 校验数据有效性 --- 
	if (rows <= 0 || cols <= 0)
	{
		throw std::invalid_argument("Invalid matrix dimensions: rows and cols must be positive");
	}
	if (all_point.size() != rows * cols)
	{
		throw std::invalid_argument("Matrix data size does not match rows*cols");
	}

	// --- 3. 提取第一行 --- 
	row_1.reserve(cols);   // 预分配内存优化性能
	for (size_t i = 0; i < cols; ++i)
	{
		row_1.push_back(all_point[i]);
	}

	// --- 4. 提取第一列 ---
	col_1.reserve(rows);   // 预分配内存优化性能
	for (size_t row_idx = 0; row_idx < rows; ++row_idx)
	{
		size_t pos = row_idx * cols;  // 每行的首元素位置 
		col_1.push_back(all_point[pos]);
	}
}

Bpoint Bezier_Curve3_QM::get_a_Bpoint_in_vector(int row, int col)
{
	// 边界检查 
	if (row < 0 || row >= rows || col < 0 || col >= cols)
	{
		throw std::out_of_range("Index out of bounds");
	}

	// 计算一维索引（行优先顺序）
	int index = row * cols + col;
	return all_point[index];
}

void Bezier_Curve3_QM::find_Weizhi(std::vector<double>& all_L, double L, int& wei_1, int& wei_2)
{
	auto neighbors = find_neighbors(all_L, L);
	auto& left = neighbors.first;   // 左邻居迭代器 
	auto& right = neighbors.second;  // 右邻居迭代器

	// 输出结果 
	if (left == all_L.end())
	{
		//小于所有数，右邻居是right
		wei_1 = 0;
		wei_2 = 1;
	}
	else if (right == all_L.end())
	{
		//大于所有数，左邻居是left
		wei_1 = all_L.size() - 2;
		wei_2 = all_L.size() - 1;
	}
	else
	{
		//位于left和right之间
		wei_1 = left - all_L.begin();
		wei_2 = right - all_L.begin();
	}
}

void Bezier_Curve3_QM::Check_Input()
{
	if (rows * cols != all_point.size())
	{
		throw std::invalid_argument("输入点集不正确，请检查行列参数！");
	}
}

void Bezier_Curve3_QM::Mian_min(Bpoint& P_a, Bpoint& P_b, Bpoint& P_c, Bpoint& P_d, double u, double v, Bpoint& ans)
{
	Bpoint ab_p;
	Bpoint dc_p;
	get_a_Bpoint_u(P_a, P_b, u, ab_p);
	get_a_Bpoint_u(P_d, P_c, u, dc_p);
	get_a_Bpoint_v(ab_p, dc_p, v, ans);
}

void Bezier_Curve3_QM::get_a_Bpoint_u(Bpoint& P_1, Bpoint& P_2, double u, Bpoint& ans)
{
	vec3 temp_data;
	vec3 temp_u;
	vec3 temp_v;
	Bpoint Xudian_1u;
	Bpoint Xudian_2u;

	auto d_1_3 = norm(((P_1 - P_2) / 3).get_xyz_vec3());

	temp_data = (P_1.get_u_vec3() * d_1_3) + P_1.get_xyz_vec3();
	Xudian_1u.set_xyz(temp_data);
	temp_data = (P_2.get_u_vec3() * (-d_1_3)) + P_2.get_xyz_vec3();
	Xudian_2u.set_xyz(temp_data);
	Bezier_3(P_1, Xudian_1u, Xudian_2u, P_2, u, ans);
	temp_u = lerpVec3(P_1.get_u_vec3(), P_2.get_u_vec3(), u);
	temp_v = lerpVec3(P_1.get_v_vec3(), P_2.get_v_vec3(), u);
	ans.set_u(temp_u);
	ans.set_v(temp_v);
}

void Bezier_Curve3_QM::get_a_Bpoint_v(Bpoint& P_1, Bpoint& P_2, double v, Bpoint& ans)
{
	vec3 temp_data;
	vec3 temp_u;
	vec3 temp_v;
	Bpoint Xudian_1v;
	Bpoint Xudian_2v;

	auto d_1_3 = norm(((P_1 - P_2) / 3).get_xyz_vec3());

	temp_data = (P_1.get_v_vec3() * (-d_1_3)) + P_1.get_xyz_vec3();
	Xudian_1v.set_xyz(temp_data);
	temp_data = (P_2.get_v_vec3() * d_1_3) + P_2.get_xyz_vec3();
	Xudian_2v.set_xyz(temp_data);
	Bezier_3(P_1, Xudian_1v, Xudian_2v, P_2, v, ans);
	temp_u = lerpVec3(P_1.get_u_vec3(), P_2.get_u_vec3(), v);
	temp_v = lerpVec3(P_1.get_v_vec3(), P_2.get_v_vec3(), v);
	ans.set_u(temp_u);
	ans.set_v(temp_v);
}

//Bezier_Curve3_QM Get_Bezier_Curve3_QM_HZ(mat in_vec_p, mat in_vec_t, vec3 line_p, 
//	vec3 line_t, double in_num_u, double in_theta)
//{
//	double theta = fmin(fmax(in_theta, 0.0), 360.0);
//	//double num_u = in_num_u;
//	//double num_v = in_vec_p.n_cols;
// 
//	double num_u = in_vec_p.n_cols; //行
//	double num_v = in_num_u; //阵列个数=列 7.22zy 行列定义与输入不同
//
//	std::vector<Bpoint> vec_bp(num_u*num_v);
//
//	for (int u = 0; u < num_u; u++)
//	{
//		vec3 tri = in_vec_t.col(u);
//		vec3 p0 = tc_vec_prj_to_line(in_vec_p.col(u), line_p, line_t);
//		double R = tcDistance(p0, in_vec_p.col(u));
//		vec3 p1r = p0 + 1.0 * in_vec_t.col(u);
//		vec3 p1 = tc_vec_prj_to_line(p1r, line_p, line_t);
//		double r = tcDistance(p1, p1r);
//		mat33 G0;
//		G0.col(2) = line_t;
//		G0.col(0) = normalise(in_vec_p.col(u) - p0);
//		G0.col(1) = normalise(cross(G0.col(2), G0.col(0)));
//		for (int v = 0; v < num_v; v++)
//		{
//			Bpoint p_uv;
//			double t_now = theta * v / num_v;
//			vec3 p1r_theta = p1 + r * G0 * tcRotZ(3, t_now) * tcX(3);
//			p_uv.set_xyz(p0 + R * G0 * tcRotZ(3, t_now) * tcX(3));
//			p_uv.set_u(G0 * tcRotZ(3, t_now) * tcY(3));
//			p_uv.set_v(-normalise(p1r_theta - p0));
//			vec_bp[u * num_v + v] = p_uv;
//		}
//	}
//
//	Bezier_Curve3_QM xt_ans;
//	xt_ans.Init_input(vec_bp, num_u, num_v);
//
//
//	{
//		std::ofstream outFile1("points_xinhou.txt");
//		if (!outFile1.is_open()) {
//			std::cerr << "无法打开文件！" << std::endl;
//		}
//
//		// 设置输出格式（6位小数，科学计数法）
//		outFile1 << std::scientific << std::setprecision(6);
//
//		for (int i = 0; i < vec_bp.size(); i++)
//		{
//			// 获取当前 (u, v) 对应的点坐标（arma::vec3）
//			arma::vec3 point = vec_bp[i].get_xyz_vec3();
//
//			// 写入文件：x y z（每行一个点）
//			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
//		}
//		outFile1.close();
//
//
//		std::ofstream outFile("points_uvmian.txt");
//		if (!outFile.is_open()) {
//			std::cerr << "无法打开文件！" << std::endl;
//		}
//
//		// 设置输出格式（6位小数，科学计数法）
//		outFile << std::scientific << std::setprecision(6);
//
//		// 遍历 u 和 v（0.0 到 1.0，步长 0.01）
//		for (double u = 0.0; u <= 1.0; u += 0.01) {
//			for (double v = 0.0; v <= 1.0; v += 0.01) {
//				// 获取当前 (u, v) 对应的点坐标（arma::vec3）
//				arma::vec3 point = xt_ans.get_Bpoint(u, v).get_xyz_vec3();
//
//				// 写入文件：x y z（每行一个点）
//				outFile << point(0) << " " << point(1) << " " << point(2) << "\n";
//			}
//		}
//		outFile.close();
//	}
//
//	return xt_ans;
//}


//8.25 zy 可超出360
Bezier_Curve3_QM Get_Bezier_Curve3_QM_HZ(mat in_vec_p, mat in_vec_t, vec3 line_p,
	vec3 line_t, int in_num_u, double in_delta_theta)
{
	//double theta = fmin(fmax(in_theta, 0.0), 360.0);
	double delta_theta = in_delta_theta;
	//double num_u = in_num_u;
	//double num_v = in_vec_p.n_cols;

	double num_u = in_vec_p.n_cols; //行
	double num_v = in_num_u; //阵列个数=列 7.22zy 行列定义与输入不同

	std::vector<Bpoint> vec_bp(num_u * num_v);

	for (int u = 0; u < num_u; u++)
	{
		vec3 tri = in_vec_t.col(u);
		vec3 p0 = tc_vec_prj_to_line(in_vec_p.col(u), line_p, line_t);
		double R = tcDistance(p0, in_vec_p.col(u));
		vec3 p1r = p0 + 1.0 * in_vec_t.col(u);
		vec3 p1 = tc_vec_prj_to_line(p1r, line_p, line_t);
		double r = tcDistance(p1, p1r);
		mat33 G0;
		G0.col(2) = line_t;
		G0.col(0) = normalise(in_vec_p.col(u) - p0);
		G0.col(1) = normalise(cross(G0.col(2), G0.col(0)));
		for (int v = 0; v < num_v; v++)
		{
			Bpoint p_uv;
			double t_now = delta_theta * v ;
			vec3 p1r_theta = p1 + r * G0 * tcRotZ(3, t_now) * tcX(3);
			p_uv.set_xyz(p0 + R * G0 * tcRotZ(3, t_now) * tcX(3));
			p_uv.set_u(G0 * tcRotZ(3, t_now) * tcY(3));
			p_uv.set_v(-normalise(p1r_theta - p0));
			vec_bp[u * num_v + v] = p_uv;
		}
	}

	Bezier_Curve3_QM xt_ans;
	xt_ans.Init_input(vec_bp, num_u, num_v);


	{
		std::ofstream outFile1("points_xinhou.txt");
		if (!outFile1.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		for (int i = 0; i < vec_bp.size(); i++)
		{
			// 获取当前 (u, v) 对应的点坐标（arma::vec3）
			arma::vec3 point = vec_bp[i].get_xyz_vec3();

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();


		std::ofstream outFile("points_uvmian.txt");
		if (!outFile.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile << std::scientific << std::setprecision(6);

		// 遍历 u 和 v（0.0 到 1.0，步长 0.01）
		for (double u = 0.0; u <= 1.0; u += 0.01) {
			for (double v = 0.0; v <= 1.0; v += 0.01) {
				// 获取当前 (u, v) 对应的点坐标（arma::vec3）
				arma::vec3 point = xt_ans.get_Bpoint(u, v).get_xyz_vec3();

				// 写入文件：x y z（每行一个点）
				outFile << point(0) << " " << point(1) << " " << point(2) << "\n";
			}
		}
		outFile.close();
	}

	return xt_ans;
}

Bezier_Curve3_QM Get_Bezier_Curve3_QM_SL(mat in_qx_p, mat in_qx_t, mat in_ydx_p, mat in_ydx_v)
{
	double num_u = in_qx_p.n_cols;
	double num_v = in_ydx_p.n_cols;
	std::vector<Bpoint> vec_bp(num_u * num_v);
	//uv方向不满足芯厚曲面法向控制的定义  8.20 zy
	//for (int v = 0; v < num_v; v++)
	//{
	//	vec3 tri = in_ydx_p.col(v) - in_ydx_p.col(0);
	//	for (int u = 0; u < num_u; u++)
	//	{
	//		Bpoint p_uv;
	//		p_uv.set_xyz(in_qx_p.col(u) + tri);
	//		p_uv.set_u(in_qx_t.col(u));
	//		p_uv.set_v(in_ydx_v.col(u));
	//		vec_bp[v * num_u + u] = p_uv;
	//	}
	//}
	
	for (int u = 0; u < num_u; u++)
	{
		for (int v = 0; v < num_v; v++)
		{
			vec3 tri = in_ydx_p.col(v) - in_ydx_p.col(0);
			Bpoint p_uv;
			p_uv.set_xyz(in_qx_p.col(u) + tri);
			p_uv.set_u(in_ydx_v.col(v));
			p_uv.set_v(-in_qx_t.col(u));
			vec_bp[u * num_v + v] = p_uv;
		}
	}

	Bezier_Curve3_QM xt_ans;
	xt_ans.Init_input(vec_bp, num_u, num_v);


	{
		std::ofstream outFile1("points_xinhou.txt");
		if (!outFile1.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		for (int i = 0; i < vec_bp.size(); i++)
		{
			// 获取当前 (u, v) 对应的点坐标（arma::vec3）
			arma::vec3 point = vec_bp[i].get_xyz_vec3();

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();


		std::ofstream outFile("points_uvmian.txt");
		if (!outFile.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile << std::scientific << std::setprecision(6);

		// 遍历 u 和 v（0.0 到 1.0，步长 0.01）
		for (double u = 0.0; u <= 1.0; u += 0.01) {
			for (double v = 0.0; v <= 1.0; v += 0.01) {
				// 获取当前 (u, v) 对应的点坐标（arma::vec3）
				arma::vec3 point = xt_ans.get_Bpoint(u, v).get_xyz_vec3();

				// 写入文件：x y z（每行一个点）
				outFile << point(0) << " " << point(1) << " " << point(2) << "\n";
			}
		}
		outFile.close();
	}

	return xt_ans;
}

