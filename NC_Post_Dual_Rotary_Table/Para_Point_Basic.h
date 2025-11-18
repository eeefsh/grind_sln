#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif


#include"pch.h"
class NC_Post_Dual_Rotary_Table_API Para_Point_Basic
{
public:
	Para_Point_Basic();
	~Para_Point_Basic();
private:
	vec3 G_O;
	vec3 G_N;
	mat33 G_SYS_D;

public:
	vec3 get_G_O();
	void set_G_O(vec3  G_O_in);
	vec3 get_G_N();
	void set_G_N(vec3 G_N_in);
	mat33 get_G_SYS_D();
	void set_G_SYS_D(mat33 G_SYS_D_in);
};
