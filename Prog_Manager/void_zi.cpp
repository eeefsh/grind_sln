#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "void_zi.h"

void_zi::void_zi(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_zi(father, nc_var_type)
{
	name = 403;
}

void_zi::~void_zi()
{
	int i = 1;
}

void void_zi::prog_main()
{

}

nc_block void_zi::diaoyong()
{
	nc_block ans_block(Process_K(0));
	{
		//1 分配内存
	// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_apply.diaoyong(count_all);
		//取分配结果

		//2 传参

		//3 转跳
		ans_block << M98(entrance, name);

		//4 传参
		//不传出，所以不写
		//ans_block << (tc_x = c_x);
		//ans_block << (tc_y = c_y);
		//ans_block << (tc_z = c_z);

		//5 回收
		// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_release.diaoyong(count_all, n_of_a_range, this_prog_start_pos);
	}
	return ans_block;
}
