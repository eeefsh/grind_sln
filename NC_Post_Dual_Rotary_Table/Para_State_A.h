#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif

#include"pch.h"


class NC_Post_Dual_Rotary_Table_API Para_State_A
{
public:
	Para_State_A();
	~Para_State_A();
private:
	double A_before;
	double C_before; //2024.11.14 zy
public:
	double get_A_before();
	void set_A_before(double A_before_in);
	double get_C_before();
	void set_C_before(double C_before_in);
};

