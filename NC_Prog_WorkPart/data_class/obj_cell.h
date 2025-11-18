#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
//#include"manager_h/xt_armadillo_settings.h"

#include "oc_point.h"
#include"octree.h"
using namespace std;

class octree;

class NC_Prog_WorkPart_API obj_cell
{
private:
	//中心位置坐标
	int3v c_point;
	//父级指针
	octree* father;
	//在父级下的位置[0-7]
	unsigned char place_flag;

	//点盒面状态信息
	//上 下 左 右 前 后
	//5 4 3 2 1 0
	//1 代表外
	unsigned char num;

public:
	//颜色
	unsigned char color_num = -1;
	//工序刀路计数
	unsigned char count_cut = 0;

public:

	obj_cell();
	obj_cell(int3v op);


	obj_cell(double acc, double3v &op);

	//根据点的法向构造一个只有一个初始面为外的obj
	obj_cell(double acc, double3v op, double3v fa);

	~obj_cell();

public:
	//获取当前坐标
	double3v get_double3v(double acc);
	int3v get_int3v();

	//获取父级指针
	octree* get_father_octree();

	//向上获取倒数第n层树指针
	octree* get_up_octree(int n);	//对象层为0层

	//获取外接球半径
	//double get_r();
	//转到工件坐标系
	void cal_o_sys(double xfa, double yfa, double zfa, double err, vec3& O, mat33& SYS);

public:
	//对指定面赋值为1
	void set_face_out(int v_in);
	//对指定面赋值为0
	void set_face_in(int v_in);
	void set_color(unsigned char c_num);
	void set_count_cut(unsigned char cut_num);
public:
	//获取所有状态为0的面
	void get_all_face_dir_in(vector<int>& v_in);
	//获取所有状态为1的面
	void get_all_face_dir_out(vector<int>& v_out);

public:
	//根据obj的6面状态计算该obj的法向
	double3v cal_normal();

	
public:
	//获取当前点的外面位置
	int get_a_wai();
	//获取外面周围四个相邻面的位置：0-5
	void get_wai_side(int index, vector<int>& v_side);
	//获取外面相对面位置
	int cal_duimian_num(int wai);

	//计算指定位置旁边点坐标
	//上 下 左 右 前 后
	//5 4 3 2 1 0
	int3v cal_side_p_int(int pos, double w);
	//计算指定位置旁边点与当前点的所夹的点坐标，out为当前为1的面
	int3v cal_xie_side(int out, int pos, double w);

	bool is_the_side_out(int pos);
	unsigned char get_num();

private:
	friend class octree;
};