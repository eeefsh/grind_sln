#pragma once
#ifdef NC_RotateShow_EXPORTS
#define NC_RotateShow_API __declspec(dllexport)
#else
#define NC_RotateShow_API __declspec(dllimport)
#endif
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"


//传入回转体截面轮廓线点数据，将点数据显示为图形
//创建一个OpenGL显示类，自动申请一个list，作为其显示输出接口
//通过计算函数改变list内容
// 
//回转体显示类
//
//第一步:通过传入回转体截面轮廓线点数据，实现初始化；
// 
//第二步:创造一个3D显示的list
//第二步:创造一个2D显示的list
// 
//第三步:loop_show函数放入循环体，传入变换矩阵可更新显示位置
class NC_RotateShow_API RotateShow
{
private:
	int my_list;
	mat show_data;
	double max_y;
	unsigned char colour[3];
public:
	//传入回转体横截面，一列一个点xyz，n个点
	//一列一个点 【x(砂轮轴线方向)，y（半径方向坐标），0】
	RotateShow(mat _data);
	~RotateShow();
	//计算显示列表：3D模型
	void init_show3D();
	//计算显示列表：2D轮廓
	void init_show2D();
	//显示：传入4阶变换矩阵-参考位置
	void loop_show(mat& t_Matrix);
	//显示
	void loop_show();
	//颜色设置0-255
	void set_color(int r, int g, int b);
private:
	//寻找最大y值
	void find_max_y();
	//圆弧角度划分
	//返回值是角度按照精度分段
	vec rot_angle(double err, double r_l, double start, double end);
	//画list3D
	void draw3D(mat& temp0, mat& temp1);
	//画list3D
	void draw2D();
};