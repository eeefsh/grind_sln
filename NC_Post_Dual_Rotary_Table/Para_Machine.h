#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif

#include"pch.h"

class NC_Post_Dual_Rotary_Table_API Para_Machine
{
public:
	Para_Machine();
	~Para_Machine();
private:
	mat33 GC_SYS_G;
	vec3 GC_O_G;
	double w_c2g;
public:
	mat33 get_GC_SYS_G();
	void set_GC_SYS_G(mat33 GC_SYS_G_in);

	vec3 get_GC_O_G();
	void set_GC_O_G(vec3 GC_O_G_in);

	double get_w_c2g();
	void set_w_c2g(double w_c2g_in);

};

