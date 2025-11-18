#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
/// <summary>
/// 说明：
///		半棱模型的三角网路
/// 
/// ***********************************************
/// 第1次编辑
/// 时间：2023-10-6
/// 编辑：文立东
/// 文件：
///		tri_meshB.h
///		tri_meshB.cpp
///		triB_ralations.h
///		triB_ralations.cpp
///		triB_coordinate.h
///		triB_coordinate.cpp
/// ***********************************************

/// </summary>
#include "triB_coodinate.h"
#include "triB_ralations.h"
#include <map>
#include "tri_meshA.h"
#include"manager_h/xt_armadillo_settings.h"
#include"manager_h/MA_020101_File_STL.h"
using namespace std;

class tri_meshB_V;
class tri_meshB_E;
class tri_meshB_F;
class tri_meshB;

class NC_Prog_WorkPart_API tri_meshB
{
public:
	int count;
public:
	map<triB_coor_3d,tri_meshB_V*> all_vertex;
	map<triB_coor_2ptr,tri_meshB_E*> all_edge;
	map<triB_coor_3ptr_sorted,tri_meshB_F*> all_face;

//访问功能
public:
	//
	int reset_allface_visited();
	//
	bool get_a_unvisited_face(int visit, tri_meshB_F*& ans);

//形成
public:
	bool init(string dir);
	bool init(xt_STL_Data data);

public:
	//创建一个面，但没有建立相邻关系，即对棱关系
	bool create_a_face(tri_meshA_F* fa,tri_meshB_F*& ans);

	//与已有面创建相邻关系
	bool construct_nerb_ralation(tri_meshB_F* face_in);
	

public:
	bool find_v(triB_coor_3d& coor, tri_meshB_V*& ans);
	bool find_e(triB_coor_2ptr& coor, tri_meshB_E*& ans);
	bool find_f(triB_coor_3ptr_sorted& coor, tri_meshB_F*& ans);

public:
	bool insert_v(triB_coor_3d& coor,tri_meshB_V* v_in);
	bool insert_e(triB_coor_2ptr& coor, tri_meshB_E* e_in);
	bool insert_f(triB_coor_3ptr_sorted& coor, tri_meshB_F* f_in);

public:
	bool delete_v(triB_coor_3d& coor);
	bool delete_e(triB_coor_2ptr& coor);
	bool delete_f(triB_coor_3ptr_sorted& coor);

public:
	bool is_normal_out();
	void change_normal_out();
};

class NC_Prog_WorkPart_API tri_meshB_F
{
//属性
public:
	triB_coor_3ptr_sorted coor;
	vec3 normal;

public:
	int has_been_visited;

//关系
public:
	triB_ralation_manager_be2bf edges;

//形成
public:
	tri_meshB_F(triB_coor_3ptr_sorted& coor_in);
	~tri_meshB_F();

public:
	//i 0-2
	tri_meshB_E* get_edge(int i);
	//i 0-2
	tri_meshB_V* get_double3v(int i);

	tri_meshB_F* create_a_oppo_face();
	 vec3 cal_zhongxin();
	 vec3 cal_normal();
	 vec3 get_normal();
	 void change_normal();

 //遍历相关功能
public:
	//1 重置所有面的访问标志为0
	void reset_visited();
	//2 判断是否已访问，如果等于则已访问
	bool has_visited(int i);
	//3 设置已访问，将标志设置为i
	void visit(int i);

};

class NC_Prog_WorkPart_API tri_meshB_E
{
//属性
public:
	triB_coor_2ptr coor;

//关系
public:
	triB_ralation_bv2be* start;
	triB_ralation_bv2be* end;
	triB_ralation_be2bf* face_ral;
	tri_meshB_E* before;
	tri_meshB_E* next;
	tri_meshB_E* oppo;

//形成
public:
	tri_meshB_E(triB_coor_2ptr& coor_in);

	~tri_meshB_E();

	friend void make_pair(tri_meshB_E* e1, tri_meshB_E* e2);

	tri_meshB_E* create_oppo_edge();

	tri_meshB_V* get_start_p();
	tri_meshB_V* get_end_p();

	vec3 get_vec3();

	void swap_start_end();
};

class NC_Prog_WorkPart_API tri_meshB_V
{
//属性
public:
	triB_coor_3d coor;

//关系
public:
	triB_ralation_manager_bv2be in;
	triB_ralation_manager_bv2be out;

//形成
public:
	tri_meshB_V(triB_coor_3d coor_in);

	~tri_meshB_V();

	vec3 get_vec3();

};