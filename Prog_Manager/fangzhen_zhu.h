#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"gx_fu.h"
//只允许一个主程序且包含所有副
#include"buchang_tance_fu.h"
#include"length_tance_fu.h"  

class Prog_Manager_API fangzhen_zhu:
	public nc_program_zhu_prog_2
{
public:
	fangzhen_zhu();

public:
	void set_cx_safe_p(Point_by_5axis& cx_safe_point, double safe_p_f);

public:
	void add_a_fu();
};