#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
/// <summary>
/// 说明：
///		每个三角形由3个点组成
///		点没有重复
///		三角形没有重复
/// 
/// ***********************************************
/// 第1次编辑
/// 时间：2023-10-6
/// 编辑：文立东
/// 文件：
///		tri_meshA.h
///		tri_meshA.cpp
///		triA_ralations.h
///		triA_ralations.cpp
///		triA_coordinate.h
///		triA_coordinate.cpp
/// ***********************************************

/// </summary>
 
class tri_meshA_V;
class tri_meshA_F;

#include "triA_coordinate.h"
#include "triA_ralations.h"
#include <map>
#include <string>
#include"manager_h/xt_armadillo_settings.h"
#include"manager_h/MA_020101_File_STL.h"
using namespace std;
class NC_Prog_WorkPart_API tri_meshA
{
public:
	int count;
public:
	map<triA_coor_3d,tri_meshA_V*> manager_v;
	map<triA_coor_3ptr, tri_meshA_F*> manager_f;

//获得整体信息
public:
	int get_count();
//访问功能
public:
	//
	int reset_allface_visited();
	//
	bool get_a_unvisited_face(int visit, tri_meshA_F*& ans);

public:
	//1 主要功能：初始化
	bool init(string dir);
	bool init(xt_STL_Data data);

public:
	//1.1 创建一个面，包括3个点，并建立关系
	bool create_a_face(
		fvec3 p1,fvec3 p2,fvec3 p3
	);
public:
	//1.1.1新建一个点，并插入到管理器中，但没有建立关系
	bool insert_a_vertex(double p1, double p2, double p3, tri_meshA_V*& ans);
	//1.1.2新建一个面，并插入到管理器中，但没有建立关系
	bool insert_a_face(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3, tri_meshA_F*& ans);
public:
	//1.1.1.1
	bool has_this_3d(double p1, double p2, double p3, tri_meshA_V*& ans);
	//1.1.2.1
	bool has_this_3ptr(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3, tri_meshA_F*& ans);
};

class NC_Prog_WorkPart_API tri_meshA_V
{
public:
	triA_coor_3d coor;


public:
	triA_ralation_manager_av2af ral;

public:
	tri_meshA_V();
	tri_meshA_V(double p1, double p2, double p3);

public:
	//1 统计邻面数量
	int count_nerb_face();
	//2 获得第i个位置的邻面
	bool get_nerb_face(int i, tri_meshA_F*& nerb_face);
	//3 获得位置数量
	int get_pos_count();

public:
	//2.1 判断此面是否为邻面
	bool has_this_face(tri_meshA_F*& face_ral);

//属性获得
public:
	//访问坐标
	triA_coor_3d get_coor();
};

class NC_Prog_WorkPart_API tri_meshA_F
{
public:
	triA_coor_3ptr coor;
public:
	triA_ralation_manager_av2af ral;

public:
	int has_been_visited;


//遍历相关功能
public:
	//1 重置所有面的访问标志为0
	void reset_visited();
	//2 判断是否已访问，如果等于则已访问
	bool has_visited(int i);
	//3 设置已访问，将标志设置为i
	void visit(int i);

//访问相关功能
public:
	//4 获得第i个位置的相邻面，并返回公共点
	//i为0-2；
	bool get_nerb_face(int i, tri_meshA_F*& nerb_face, tri_meshA_V*& p1, tri_meshA_V*& p2);
	//5 获得三角形给定两点的另外一点
	//这里不判断输入两点的正确性
	tri_meshA_V* get_the_other_v_of_f(tri_meshA_V*& p1, tri_meshA_V*& p2);
	//6 获得第m个点（不是m位置）
	//m：0-2
	tri_meshA_V* get_a_vertex_of_f(int m);

//属性获得
public:
	//访问坐标
	triA_coor_3ptr get_coor();

public:
	tri_meshA_F();
	tri_meshA_F(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3);

};
