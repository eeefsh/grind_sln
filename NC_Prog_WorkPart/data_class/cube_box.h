#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
#include "oc_point.h"



//限制范围的盒子
//分三步完成限制范围：
//1.设置 xyz的最大值
//2.设置 xyz的最小值
//3.初始方块
class NC_Prog_WorkPart_API cube_box
{
private:
	int	X_max = 0, Y_max = 0, Z_max = 0;
	int	X_min = 0, Y_min = 0, Z_min = 0;

	int3v c_point;
	double w1;
	int n = 0;
	int w = 2;
public:
	cube_box(double d);
	//步骤1
	//设置 xyz的最大值
	void set_max_xyz(int3v Max);
	//步骤2
	//设置 xyz的最小值
	void set_min_xyz(int3v Min);
	//步骤3
	//初始方块
	void init_box();


public:
	//获取中心位置
	int3v get_double3v();
	//获取边长按照精度划分后的段数
	int	get_n();
	//获取精度
	int get_w();
};
