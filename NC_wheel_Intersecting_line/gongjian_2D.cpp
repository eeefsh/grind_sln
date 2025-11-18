#include "pch.h"
#include "gongjian_2D.h"



void gongjian_2D::set_jiemian(mat44 _view)
{
	G_SYS_Look = _view;
}

void gongjian_2D::set_gj_line(mat line)
{
	data = line;
}

void gongjian_2D::set_gj_YuanZhu(double D, double L)
{
	int n = L / 0.001;
	vec x = linspace(0, L, n + 1);
	data.clear();
	data.set_size(3, x.size());
	for (size_t i = 0; i < data.n_cols; i++)
	{
		data.col(i)(0) = x(i);
		data.col(i)(1) = D / 2;
		data.col(i)(2) = 0;
	}
}

void gongjian_2D::set_gj_WeiZhi(mat _sys)
{
	sys = _sys;
}

mat gongjian_2D::get_look_points()
{
	if (data.n_cols == 0 || data.n_rows != 3)
	{
		//工件轮廓数据错误
		//需要设置正确的工件轮廓
		std::terminate();
	}

	mat data1 = tcRotY(3,180.0) * data;
	jie_mian_xian::set_jiemian(G_SYS_Look, data1);

	mat ans = get_outline_point(sys, 0);
	
	return ans;
}

gongjian_2D::gongjian_2D()
{
	sys.set_size(4, 4);
	sys.col(0) = { 1, 0, 0, 0 };
	sys.col(1) = { 0, 1, 0, 0 };
	sys.col(2) = { 0, 0, 1, 0 };
	sys.col(3) = { 0, 0, 0, 1 };
	n.set_size(3, 1);
	n(0) = 0;
	n(1) = 0;
	n(2) = 1;
	point.set_size(3, 1);
	point(0) = 0;
	point(1) = 0;
	point(2) = 0;
}
