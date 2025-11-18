#include "pch.h"
#define NC_wheel_Intersecting_line_EXPORTS
#include "jiaoxian_wheel.h"
#include "jiaoxian_wheel.h"

namespace jiaoxian_wheel_namespace
{
	// 计算向量 v 在向量 u 上的投影向量
	vec calculateProjection(const vec& u, const vec& v)
	{
		// 计算向量 u 和向量 v 的内积
		double dot_product = dot(u, v);

		// 计算向量 u 的范数的平方
		double norm_squared = dot(u, u);

		// 计算投影向量
		vec projection = (dot_product / norm_squared) * u;

		return projection;
	}
	jiaoxian_wheel::jiaoxian_wheel() :
		lunkuo_point({ 0,0,0 }),
		jiemian_n({ 0,0,0 }),
		jiemian_p({ 0,0,0 }),
		Theta(0.0)
	{
		No1_Function();
	}


	mat pre_point_grow(mat& val, vec n_in)
	{
		vec3 point_now;
		vec3 point_before;
		point_before = val.col(0);
		int count = 0;
		mat ans(3, val.n_cols * 10);

		int n = 1;
		double dn = 1.0;
		ans.col(count) = point_before;
		count++;

		for (int i = 1; i < val.n_cols; i++)
		{
			point_now = val.col(i);
			vec temp = point_now - point_before;
			vec temp_dir = normalise(temp);
			n = 1.0 / std::max((1.0 - abs(dot(temp_dir, n_in))), 0.02);
			dn = n;
			temp = temp / dn;
			while (n > 0)
			{
				if (count == ans.n_cols)
				{
					ans.insert_cols(ans.n_cols,1000);
				}
				ans.col(count) = point_before + n * temp;
				count++;
				n--;
			}
			point_before = point_now;			
		}
		ans.shed_cols(count - 1, ans.n_cols - 1);
		return ans;
	}

	mat jiaoxian_wheel::get_point(mat& val, vec n_in, vec p_in, double acc, bool flag)
	{

		double bbb = val.col(0)(0);
		double bbb1 = val.col(0)(1);
		double bbb2 = val.col(0)(2);
		double bbb3 = val.col(1)(0);
		double bbb4 = val.col(1)(1);
		double bbb5 = val.col(1)(2);

	
		jiemian_n = normalise(n_in);
		jiemian_p = p_in;

		//面法向和砂轮轴线夹角
		double jiao_2 = tcDegree(acos(dot(jiemian_n, tcX(3))));
		  
		if (flag)
		{
			if (jiao_2 < 30.0)
			{
				acc = 0.05 * (jiao_2 / 30.0)* (jiao_2 / 30.0);
			}
			if (jiao_2 > 150.0)
			{
				jiao_2 = 180.0 - jiao_2;
				acc = 0.05 * (jiao_2 / 30.0) * (jiao_2 / 30.0);
			}
			if (acc < 0.0001)
			{
				acc = 0.0001;
			}
			lunkuo_point = val;
			No1_Function();
			line_add_point(lunkuo_point, acc);
		}
		else
		{
			
			lunkuo_point = val;
			lunkuo_point = pre_point_grow(val, n_in);
			//No1_Function();
			//line_add_point(lunkuo_point, 0.001);

		}
		Theta = acos(dot(jiemian_n, tcX(3)) / norm(jiemian_n));

		//平行标记
		double PX_flag = norm(cross(jiemian_n, tcX(3)));

		//
		if (PX_flag > 0.00000001)
		{
			int count = 0;
			vec phi_all = Phi();
			double phi_0p = Phi_0();
			//phi_all.print();
			mat ans(3, phi_all.size());

			for (size_t i = 0; i < lunkuo_point.n_cols; i++)
			{
				if (lunkuo_point.col(i)(2) == 1.0)
				{
					lunkuo_point.col(i)(2) = 0;
					ans.col(count) = tcRotX(3, tcDegree(phi_0p)) * tcRotX(3, tcDegree(phi_all(count))) * lunkuo_point.col(i);
					count++;
				}
			}
			mat ans_2(3, phi_all.size());
			for (size_t i = 0; i < ans_2.n_cols; i++)
			{
				ans_2.col(i) = tcRotX(3, -2 * tcDegree(phi_all(ans_2.n_cols - i - 1))) * ans.col(ans_2.n_cols - i - 1);
			}
			return join_rows(ans, ans_2);
		}
		else
		{
			vec ans_vec(3);
			bool flag = 0;
			for (size_t i = 1; i < lunkuo_point.n_cols; i++)
			{				
				double epsilon = 5e-2;
				if (lunkuo_point.col(i)(0) >= jiemian_p(0) - epsilon &&
					lunkuo_point.col(i - 1)(0) <= jiemian_p(0) + epsilon)
				{
					double bl = (jiemian_p(0) - lunkuo_point.col(i - 1)(0)) / (lunkuo_point.col(i)(0) - lunkuo_point.col(i - 1)(0));
					double ls_y = lunkuo_point.col(i - 1)(1) + bl * (lunkuo_point.col(i)(1) - lunkuo_point.col(i - 1)(1));
					double ls_x = jiemian_p(0);
					ans_vec(0) = ls_x;
					ans_vec(1) = ls_y;
					ans_vec(2) = 0;
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				mat ans(3, 360);
				for (size_t i = 0; i < 360; i++)
				{
					ans.col(i) = tcRotX(3, 1 * i) * ans_vec;
				}
				return ans;
			}
			mat aaa(3, 1, fill::zeros);
			return aaa;
		}
	}

	void jiaoxian_wheel::No1_Function()
	{
		//去头去尾
		lunkuo_point.shed_col(0);
		lunkuo_point.shed_col(lunkuo_point.n_cols - 1);
		
	}

	vec jiaoxian_wheel::Phi()
	{
		vec ans(lunkuo_point.n_cols);
		vec Tn(3);
		int count = 0;
		double d = 0;

		for (size_t i = 0; i < lunkuo_point.n_cols; i++)
		{
			Tn = get_Tn(get_p_x(lunkuo_point.col(i)));
			if (norm(Tn) != 0.0)
			{
				d = norm(Tn) / sin(Theta);
				double aaa = lunkuo_point.col(i)(1);
				if (d > lunkuo_point.col(i)(1))
				{
					continue;
				}
				//方向判断
				vec nn = jiemian_n;
				nn(0) = 0;
				double temp = dot(Tn, nn);
				if (temp > 0)
				{
					ans(count) = acos(d / lunkuo_point.col(i)(1));
					//记录交点
					lunkuo_point.col(i)(2) = 1;
					count++;
				}
				else if (temp < 0)
				{
					ans(count) = tcRadians(180) - acos(d / lunkuo_point.col(i)(1));
					//记录交点
					lunkuo_point.col(i)(2) = 1;
					count++;
				}
				//else
				//{
				//	//方向判断
				//	temp = dot(Tn, tcZ(3));
				//	if (temp > 0)
				//	{
				//		ans(count) = acos(d / lunkuo_point.col(i)(1));
				//		//记录交点
				//		lunkuo_point.col(i)(2) = 1;
				//		count++;
				//	}
				//	else if (temp < 0)
				//	{
				//		ans(count) = tcRadians(180) - acos(d / lunkuo_point.col(i)(1));
				//		//记录交点
				//		lunkuo_point.col(i)(2) = 1;
				//		count++;
				//	}
				//}
				//double temp = dot(Tn, tcY(3));
				//if (temp > 0)
				//{
				//	ans(count) = acos(d / lunkuo_point.col(i)(1));
				//	//记录交点
				//	lunkuo_point.col(i)(2) = 1;
				//	count++;
				//}
				//else if (temp < 0)
				//{
				//	ans(count) = tcRadians(180) - acos(d / lunkuo_point.col(i)(1));
				//	//记录交点
				//	lunkuo_point.col(i)(2) = 1;
				//	count++;
				//}
				//else
				//{
				//	//方向判断
				//	temp = dot(Tn, tcZ(3));
				//	if (temp > 0)
				//	{
				//		ans(count) = acos(d / lunkuo_point.col(i)(1));
				//		//记录交点
				//		lunkuo_point.col(i)(2) = 1;
				//		count++;
				//	}
				//	else if (temp < 0)
				//	{
				//		ans(count) = tcRadians(180) - acos(d / lunkuo_point.col(i)(1));
				//		//记录交点
				//		lunkuo_point.col(i)(2) = 1;
				//		count++;
				//	}
				//}
			}
			else
			{
				ans(count) = tcRadians(90.0);
				//记录交点
				lunkuo_point.col(i)(2) = 1;
				count++;
			}
		}
		ans.resize(count);
		return ans;
	}

	double jiaoxian_wheel::Phi_0()
	{
		vec ty_n = jiemian_n;
		ty_n(0) = 0;
		double ans = acos(dot(ty_n, tcY(3)) / (norm(ty_n) * norm(tcY(3))));

		if (ty_n(2) < 0)
		{
			return -ans;
		}

		return ans;
	}

	void jiaoxian_wheel::line_add_point(mat& val, double acc)
	{
		double last;
		double next;
		double d = 0;
		int num = 0;
		for (size_t i = 0; i < val.n_cols - 2; i++)
		{
			last = norm(val.col(i + 1) - val.col(i));
			next = norm(val.col(i + 2) - val.col(i + 1));
			d = next - last;
			if (d > 0.001)
			{
				num = i + 1;
				break;
			}
		}

		double n = floor(norm(val.col(num + 1) - val.col(num)) / acc);
		double dt = norm(val.col(num + 1) - val.col(num)) / n;

		vec last_n = normalise(val.col(num + 1) - val.col(num));

		mat ans(3, (int)(n - 1) + val.n_cols);
		ans.cols(0, num) = val.cols(0, num);
		for (size_t i = 1; i < (int)n; i++)
		{
			ans.col(num + i) = (i * dt * last_n) + val.col(num);
		}
		ans.cols(num + n, ans.n_cols - 1) = val.cols(num + 1, val.n_cols - 1);

		val.resize(3, ans.n_cols);
		val = ans;
	}

	vec jiaoxian_wheel::get_p_x(vec val)
	{
		val(1) = 0;
		val(2) = 0;
		return val;
	}

	vec jiaoxian_wheel::get_Tn(vec val)
	{
		vec ans = jiaoxian_wheel_namespace::calculateProjection(jiemian_n, jiemian_p - val);
		return ans;
	}
}





mat jie_mian_xian::findRotationMatrixToZ(vec n)
{
	// 标准化输入向量 n
	vec n_norm = normalise(n);

	// 如果向量已经指向 z 方向，不需要旋转，返回单位矩阵
	if (approx_equal(n_norm, vec({ 0, 0, 1 }), "absdiff", 1e-10))
	{
		return arma::eye(3, 3); // 返回 3x3 单位矩阵
	}

	// 计算旋转轴 k = n_norm x (0, 0, 1)
	vec k = cross(n_norm, vec({ 0, 0, 1 }));
	double k_norm = norm(k);

	// 计算旋转角度 theta
	double cos_theta = n_norm(2); // n_norm 和 (0, 0, 1) 的点积为 n_norm(2)
	double theta = std::acos(cos_theta);

	// 如果 k 的模为零，表示向量 n 在 -z 方向
	if (k_norm < 1e-10)
	{
		return mat({
			{ -1,  0,  0 },
			{ 0, -1,  0 },
			{ 0,  0,  1 }
			});
	}

	// 标准化旋转轴
	k /= k_norm;

	// 构造旋转矩阵的反对称矩阵 K
	mat K = {
		{ 0, -k(2),  k(1) },
		{ k(2),     0, -k(0) },
		{ -k(1),  k(0),     0 }
	};

	// 使用 Rodrigues’ 旋转公式计算旋转矩阵 R
	mat R = eye(3, 3) + std::sin(theta) * K + (1 - std::cos(theta)) * (K * K);

	return R;
}

jie_mian_xian::jie_mian_xian()
{

}

void jie_mian_xian::set_jiemian(mat44 _view, mat val)
{
	G_N.resize(4);
	G_N = _view.col(2);
	G_P.resize(4);
	G_P = _view.col(3);

	G_SYS_View = _view;

	val_wheel.reset();
	val_wheel = val;
}

mat jie_mian_xian::get_outline_point(mat& G_SYS_SL, bool flag)
{

	vec SL_N = inv(G_SYS_SL) * G_N;
	vec SL_P = inv(G_SYS_SL) * G_P;
	SL_N.shed_row(3);
	SL_P.shed_row(3);
	mat out=val_wheel.cols(0, val_wheel.n_cols-1).t();
	out.save("jjj.txt", raw_ascii);
	mat SL_jiao_points = jiaoxian.get_point(val_wheel, SL_N, SL_P, 0.02, flag);

	vec temp_vec(SL_jiao_points.n_cols, fill::ones);
	mat ans = join_cols(SL_jiao_points, temp_vec.t());
	ans = G_SYS_SL * ans;

	ans = inv(G_SYS_View) * ans;
	ans.shed_row(3);

	return ans;
}

