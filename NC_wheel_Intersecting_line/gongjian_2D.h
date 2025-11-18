#pragma once
#ifdef NC_wheel_Intersecting_line_EXPORTS
#define NC_wheel_Intersecting_line_API __declspec(dllexport)
#else
#define NC_wheel_Intersecting_line_API __declspec(dllimport)
#endif
#include "jiaoxian_wheel.h"

class NC_wheel_Intersecting_line_API gongjian_2D:
	jie_mian_xian
{
	mat sys;
	//工件轮廓3*n
	mat data;
	//法向
	vec n;
	//截面点
	vec point;
	//视口矩阵
	mat44 G_SYS_Look;
public:
	//设置截面
	//输入：面法向vec(3)，面上任意点vec(3)
	void set_jiemian(mat44 _view);

	//输入型线，X轴为长度轴，一列一个点
	void set_gj_line(mat line);

	//设置圆柱工件
	//输入直接D，长度L
	void set_gj_YuanZhu(double D, double L);

	//设置工件位置
	//sys: mat4*4
	void set_gj_WeiZhi(mat _sys);

	//获取工件显示截线数据
	mat get_look_points();

	gongjian_2D();
};

