#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include<string>
using std::string;
#include"../tri_mesh/tri_meshB.h"
#include"../data_class/oc_point.h"
#include"manager_h/xt_glfw_setting.h"
//#include"../send_data_API/get_send_data.h"

class NC_Prog_WorkPart_API gongjian_stl
{
public:
	//保存mesh_gj
	tri_meshB mesh_gj;

//public:
//	//stl显示列表起始号
//	GLint list_num_stl;

public:
	gongjian_stl();
	~gongjian_stl();

public:
	//读STL文件 显示工件模型 保存mesh_gj 
	//gongjian_stl(string file_path);
	void read_stl(string file_path);


	//12.8 增加数据的发送
	void send_stl_data(vector<vector<mesh_cutted>>& show_data , 
		vector<int>& renew_list_num, vector<int>& del_list_num);

	//void init_stl_list();
};



