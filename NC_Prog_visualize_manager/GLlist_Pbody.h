#pragma once
#ifdef NC_Prog_visualize_manager_EXPORTS
#define NC_Prog_visualize_manager_API __declspec(dllexport)
#else
#define NC_Prog_visualize_manager_API __declspec(dllimport)
#endif

#include "GLlist_Color.h"
#include"manager_h/xt_glfw_setting.h"
#include"manager_h/MA_020101_File_STL.h"

//openGL显示中的一个刚体的list，
class NC_Prog_visualize_manager_API GLlist_Pbody
{
private:
	xt_STL_Data stl_reader;
	//3*2矩阵，xyz最大最小
	mat range_xyz;

	GLint body_glList;//几何体的List_num
	//颜色信息
private:
	GLfloat materialAmb[4];
	GLfloat materialDiff[4];
	GLfloat materialSpec[4];
	GLfloat materialSHIN;
private:

	//GLlist_Color* color;
	bool is_show;
	//偏置参数x
	double x_offset;
	//偏置参数y
	double y_offset;
	//偏置参数z
	double z_offset;
public:
	//空构造，需读取STL
	GLlist_Pbody();
	~GLlist_Pbody();

public:
	//读取刚体的STL
	bool read_stl(std::string dir);
	void draw();
	//设置材质list
	bool set_color(fvec4 amb, fvec4 diff, fvec4 spec, float shin);
	bool set_color(gyGLColor& color);
	//设置偏置,移动部件位置
	void set_offset(double x, double y, double z);
	//显示，之前需读取STL并设置颜色
	void show(mat44& pos);

public:
	double get_max_x();
	double get_max_y();
	double get_max_z();
	double get_min_x();
	double get_min_y();
	double get_min_z();

	mat get_box();

public:
	//切换显示
	void turnOn();
	//切换显示
	void turnOff();
};
