#pragma once
#ifdef NC_Prog_Show_WorkPart_and_ShaLun_EXPORTS
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllexport)
#else
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllimport)
#endif
#include"manager_h\MA_010101_NC_Prog_WorkPart.h"
#include"../show_data_send/show_send.h"
//class show_send;

class NC_Prog_Show_WorkPart_and_ShaLun_API show_gj_sl
{
public:
	vector<show_send*> all_part;


public:
	show_gj_sl();
	~show_gj_sl();

public:
	void show(mat44& A);



private:
	//void display_fresh_a_list(octree* cur_zu, int list_index);

};


