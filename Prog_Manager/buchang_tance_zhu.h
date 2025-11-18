#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"buchang_tance_fu.h"

class Prog_Manager_API buchang_tance_zhu :
	public nc_program_zhu_prog_2
{
public:
	buchang_tance_zhu();

public:
	//void add_a_fu();
};