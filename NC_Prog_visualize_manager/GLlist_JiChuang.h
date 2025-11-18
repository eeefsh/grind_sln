#pragma once
#ifdef NC_Prog_visualize_manager_EXPORTS
#define NC_Prog_visualize_manager_API __declspec(dllexport)
#else
#define NC_Prog_visualize_manager_API __declspec(dllimport)
#endif
//using namespace std;

#include <string>
#include<vector>
#include"GLlist_Color.h"
#include"GLlist_Pbody.h"

class RotateShow;
//专门显示机床的类
class NC_Prog_visualize_manager_API GLlist_JiChuang
{
public:
	//存储机床部件的vector
	//0：基座  1：X轴部件  2：Y轴部件  3：Z轴部件
	//4：A轴部件    5：C轴部件
	vector<GLlist_Pbody*> base;
	vector<GLlist_Pbody*> Xaxis;
	vector<GLlist_Pbody*> Yaxis;
	vector<GLlist_Pbody*> Zaxis;
	vector<GLlist_Pbody*> Aaxis;
	vector<GLlist_Pbody*> Caxis;
	
	GLlist_Pbody* Part;
	vector<RotateShow*> Tool;
	
	//部件显示隐藏容器 base,X,Y,Z,
	vector<bool> v_hide;

private:
	//3*2矩阵，xyz最大最小
	mat range_xyz;

public:
	GLlist_JiChuang();
	~GLlist_JiChuang();

public:
	bool init();
	bool init_part_by_stl(string dir);
	//传入砂轮组数据
	bool init_tool(vector<mat>& _point);
	//卸载砂轮
	bool unload_tool();

public:

	//
	void show(
		mat44& base_in,
		double x,
		double y,
		double z,
		double a,
		double c
	);

public:
	double get_max_x();
	double get_max_y();
	double get_max_z();
	double get_min_x();
	double get_min_y();
	double get_min_z();
};

