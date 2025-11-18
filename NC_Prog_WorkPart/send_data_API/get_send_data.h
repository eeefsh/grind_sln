#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
#include<vector>
using std::vector;
#include "../data_class/oc_point.h"


class NC_Prog_WorkPart_API get_send_data
{
public:
	get_send_data();
	~get_send_data();
	virtual void send_data(vector<vector<mesh_cutted>>& show_data,
		vector<int>& renew_list_num, vector<int>& del_list_num) = 0;
};

