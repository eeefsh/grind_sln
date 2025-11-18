#pragma once
#ifdef NC_Prog_Show_WorkPart_and_ShaLun_EXPORTS
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllexport)
#else
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllimport)
#endif
#include"manager_h/xt_glfw_setting.h"
#include"manager_h/MA_010101_NC_Prog_WorkPart.h"


class NC_Prog_Show_WorkPart_and_ShaLun_API show_send
{
private:
	//get_send_data* ptr_data;
	//vector<int> all_list_start;
	map<int, int> in_list_to_start; //组号，list号

public:
	bool is_show = true;

public:
	void load_stl_data(gongjian* ptr);
	void load_init_data(gongjian* ptr);
	void load_cut_data(gongjian* ptr);
	void load_mesh_data(gongjian* ptr);

	void load_cutted_data(gongjian* ptr); //加载的是已经构成多边形的数据

	void load_shalun_data(shalun* ptr);

	void show(mat44& A);



public:
	show_send();
	~show_send();
};

