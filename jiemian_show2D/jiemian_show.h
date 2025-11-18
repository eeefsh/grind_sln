#pragma once

#ifdef jiemian_show_EXPORTS
#define jiemian_show_API __declspec(dllexport)
#else
#define jiemian_show_API __declspec(dllimport)
#endif

#include "manager_h/MA_010101_NC_wheel_Intersecting_line.h"

//控制显示截面
class jiemian_show_API jiemian_show
{
public:
	GLint list_line = 0;
	double dis_bilichi = 0.0;
private:

	double H = 100;
	double L = 100;
	GLint list_start = 0;
	GLint gj = 0;
	
	double init = 1;
	//显示视口矩阵
	mat44 view;

public:
	vec3 view_point_before;
	vec3 view_dir_before;
	mat44 scale_mat_before;
	
	
public:
	int show_flag = 0;
	jiemian_show();

	~jiemian_show();

	//设置2D显示
	void set_2D_OpenGl_show();

	//画2D工件截面
	//输入mat3*n
	void draw_gj_2D(mat& val);

	//画截面线
	//输入轮廓点
	//mat3*n
	void draw_line(std::vector<mat>& val);

	//画截面线
	//输入轮廓点 
	//mat3*n 
	void draw_line(mat& val);

	//清除画的内容
	void redraw();

	//设置窗口：长和高,初始放大系数
	void set_L_H(double _L, double _H, double init_xs);

	//获取控制视口矩阵
	//输入：窗口点1，窗口点2 
	//返回：视口矩阵
	mat44 get_Ctrl_view(vec2 point_1, vec2 point_2, double& ans_d_fangda_xishu);

	//获取控制视口矩阵，鼠标指向哪里就在哪里缩放
	//输入：鼠标光标点，缩放系数
	//返回：视口矩阵
	//mat44 get_Ctrl_view(vec2 point, double xishu);

	//复位视口矩阵
	mat44 reset_view();

	void Calls();
};

