#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include<map>
#include"octree.h"

using namespace std;

class NC_Prog_WorkPart_API index_cells
{
//表面点索引
public:
	//空间层级索引
	octree oc_tree;	
	//坐标位置索引
	map<int3v, obj_cell*>  map_pos;

	//精度 
	double accuracy;

//构造、析构
public:
	index_cells();
	~index_cells();

//增加对象
public:
	void add_cell_to_map(obj_cell* cp);
	void add_cell_to_tree(obj_cell* cp);

//删除对象
public:
	void del_cell(obj_cell* cp, octree*& ptr_zu, int aim_depth);

//初始化对象
public:
	// 初始化索引里所有cell 的面状态
	void init_all_cells_face_num(double d);

public:
	void set_acc(double d);

public:
	//变形产生一个新cell 并赋值一个外面
	obj_cell* new_a_cutted_cell(int3v& op,int cutting_dir);
	//判断指定方位面所对的邻点是否存在
	bool is_the_point_exist(int3v& op);
	//判断指定方位面所对的邻点所夹斜点是否存在
	bool is_the_point_exist_at_xie(int3v& op);
	//判断现在的外是否与保留相对  11.17 加
	bool is_opp_save_and_now(vector<int>& save_out, vector<int>& now_out);

private:

};
