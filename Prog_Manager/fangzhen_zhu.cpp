#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS

#include"fangzhen_zhu.h"

fangzhen_zhu::fangzhen_zhu()
	:nc_program_zhu_prog_2(0)
{
	set_progzhu_name(101 + name_zhu_i);
	//name_zhu_i++; //程序运行中，主程序生成号不增加文件
}

void fangzhen_zhu::set_cx_safe_p(Point_by_5axis& cx_safe_point, double safe_p_f)
{
	set_safe_p(
		cx_safe_point.X,
		cx_safe_point.Y,
		cx_safe_point.Z,
		cx_safe_point.A,
		cx_safe_point.C,
		safe_p_f
	);
}

void fangzhen_zhu::add_a_fu()
{	//第一步：为指针new成员
	Miller_DL_fu_prog* ptr = new Miller_DL_fu_prog(this, 0);

	//第二步：将指针push到主程序中
	push_my_fu(ptr);
}
