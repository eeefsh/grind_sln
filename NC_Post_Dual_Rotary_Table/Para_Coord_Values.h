#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif

#include"pch.h"


class NC_Post_Dual_Rotary_Table_API Para_Coord_Values
{
public:
	Para_Coord_Values();
	~Para_Coord_Values();
private:
	vec3 JC_O_D;	//磨削接触点
	vec3 JC_N;		//接触点法向
	vec3 JC_O_DC;  //砂轮参考点
	mat33 JC_SYS_D;
	double An;
	double Cn;
public:
	vec3 get_JC_O_DC();
	void set_JC_O_DC(vec3 JC_O_DC_in);
	vec3 get_JC_O_D();
	void set_JC_O_D(vec3 JC_O_D_in);
	vec3 get_JC_N();
	void set_JC_N(vec3 JC_N_in);
	mat get_JC_SYS_D();
	void set_JC_SYS_D(mat JC_SYS_D_in);
	double get_An();
	void set_An(double An_in);
	double get_Cn();
	void set_Cn(double Cn_in);
};

