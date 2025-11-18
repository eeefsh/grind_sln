#pragma once

#ifdef NC_wheel_Intersecting_line_EXPORTS
#define NC_wheel_Intersecting_line_API __declspec(dllexport)
#else
#define NC_wheel_Intersecting_line_API __declspec(dllimport)
#endif

#include"manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
namespace jiemian_namespace
{
	//获取横截面
	//返回值vec(6)前3行为面法向，后3行为面上的点
	//输入距离参考截面的距离
	vec NC_wheel_Intersecting_line_API get_jiemian_heng(double d);

	//获取轴向截面
	//返回值前3行为面法向，后3行为面上的点
	//输入刃线参考点、旋转角度、偏置距离
	vec NC_wheel_Intersecting_line_API get_jiemian_zhou(vec base_p, double angle, double d);

	//获取法向截面
	//返回值前3行为面法向，后3行为面上的点
	//输入型线母线（每列一个点）、轴线上的参考距离
	vec NC_wheel_Intersecting_line_API get_jiemian_fa(mat val, double d);

	//获取任意截面
	//返回值前3行为面法向，后3行为面上的点
	//输入轴向旋转角度、径向旋转角度、轴线上的参考距离
	//先旋转径向角度，再旋转轴向角度
	vec NC_wheel_Intersecting_line_API get_jiemian_renyi(double angle_zhou, double angle_jing, double d);
}