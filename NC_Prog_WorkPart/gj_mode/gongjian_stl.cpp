#include "../pch.h"
#define NC_Prog_WorkPart_EXPORTS

#include "gongjian_stl.h"


gongjian_stl::gongjian_stl()
{
}

gongjian_stl::~gongjian_stl()
{
}

void gongjian_stl::read_stl(string file_path)
{
	//1 ¹¹½¨Èý½ÇÍøÂç
	/*xt_STL_Data data;
	data.read_file(file_path);*/

	mesh_gj.init(file_path);
	mesh_gj.change_normal_out();

	//list_num_stl = glGenLists(1);
}


void gongjian_stl::send_stl_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num)
{
	vector<mesh_cutted> temp;
	mesh_cutted tri_nor;
	auto itend = mesh_gj.all_face.end();
	for (auto it = mesh_gj.all_face.begin(); it != itend; it++)
	{
		tri_nor.p1 = it->second->get_double3v(0)->get_vec3();
		tri_nor.p2 = it->second->get_double3v(1)->get_vec3();
		tri_nor.p3 = it->second->get_double3v(2)->get_vec3();
		tri_nor.p4 = it->second->get_normal();
		temp.emplace_back(tri_nor);
	}
	show_data.emplace_back(temp);

	//renew_list_num.push_back(0);
}



