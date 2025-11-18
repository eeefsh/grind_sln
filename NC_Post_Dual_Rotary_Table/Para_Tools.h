#pragma once

#ifdef NC_Post_Dual_Rotary_Table_EXPORTS
#define NC_Post_Dual_Rotary_Table_API __declspec(dllexport)
#else
#define NC_Post_Dual_Rotary_Table_API __declspec(dllimport)
#endif

#include<iostream>
#include"manager_h/xt_armadillo_settings.h"


class NC_Post_Dual_Rotary_Table_API Para_Tools
{
public:
	Para_Tools();
	~Para_Tools();
private:
	double d_sl;
	double fl_sl;//从圆角圆心沿轴线到参考点的距离
	double r_sl;
public:
	double get_d_sl();
	void set_d_sl(double d_sl_in);
	double get_fl_sl();
	void set_fl_sl(double fl_sl_in);
	double get_r_sl();
	void set_r_sl(double r_sl_in);
};

