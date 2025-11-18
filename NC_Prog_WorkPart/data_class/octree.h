#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
#include <queue>
#include"cube_box.h"
#include"obj_cell.h"

using namespace std;


class obj_cell;

//八叉树类
//使用前需要init_tree()初始化
class  NC_Prog_WorkPart_API octree
{
	/*  ****************** 属性相关的成员 *****************  */
private:
	//中心位置坐标
	int3v c_point;
	//在父级下的位置[0-7]
	unsigned char place_flag;
	//当前八叉树深度
	unsigned char depth;//最底层是1，越往上越大
	//当前边长 一行n个cell n数量 L就是n*cell边长
	int L;

	/*  ****************** 指针相关的成员 *****************  */
private:
	//父级指针
	octree* father;
	//子级指针[0-7]
	octree* child[8];

	/*  ****************** 初始化的相关函数 *****************  */
public:
	octree();
	octree(
		octree* p, 
		int L_in, 
		unsigned char depth_in, 
		int3v C_point_in,
		unsigned char Place_flag_in
	);
	//八叉树初始化
	//输入限制范围的box
	void init_tree(cube_box& box);

	/*  ****************** 析构函数 *****************  */
public:

	~octree();


	/*  ****************** 改索引对象的相关函数 *****************  */
public:
	//加入索引对象
	//需要传入用new创建的对象
	//添加错误将返回false
	bool add_obj(obj_cell* p);
	//删除索引对象
	//只能删除new创建的对象
	void delete_obj(obj_cell* p , octree*& ptr_zu , int aim_depth);

	/*  ****************** 查询指针的相关函数 *****************  */
public:

	//获取当前子级下八叉树指针队列
	//返回获取到数量<=8
	unsigned char get_child_octree(queue<octree*>& ptrVector);
	//获取当前子级下对象指针队列
	//返回获取到数量<=8
	unsigned char get_child_obj(queue<obj_cell*> &ptrVector);
	//获取父级指针
	octree* get_father_octree();
	//获取当前节点下全部对象指针
	void get_all_obj(queue<obj_cell*>& ptrVector);

	/*  ****************** 获取属性的相关函数 *****************  */
public:
	//获取当前坐标
	double3v get_double3v(double acc_d);
	//返回外接圆半径
	double get_r(double acc_d);
	//获取倒数第n层最多有多少节点
	unsigned int get_nodes2last(unsigned char n);
	
	int3v get_c_point();

public:
	//判断到达最底层
	//返回1:到达最底层
	//返回0:没有到达最底层
	bool is_bottom();
	//获取当前深度
	unsigned char get_depth();
	//获取当前宽度L
	int get_L();

private:
	//判断没有子级
	//返回0:没有子级
	//返回1:有子级
	bool has_child();
	//判断到达最顶层
	//返回1:到达最顶层
	//返回0:没有到达最顶层
	bool is_top();
};
