#pragma once
#ifdef NC_Prog_visualize_manager_EXPORTS
#define NC_Prog_visualize_manager_API __declspec(dllexport)
#else
#define NC_Prog_visualize_manager_API __declspec(dllimport)
#endif
#include"manager_h/xt_armadillo_settings.h"
class NC_Prog_visualize_manager_API gyGLColor
{
public:
	fvec4 color_amb;
	fvec4 color_diff;
	fvec4 color_spec;
	float shin;

public:
	//д╛хо{1.0,1.0,1.0,1.0}
	gyGLColor();
	~gyGLColor();

public:
	void set_red();
	void set_yellow();
	void set_green();
	void set_blue();
	void set_purple();
	void set_orange();
	void set_pink();
	void set_gray();
	void set_brown();
	void set_sea_blue();
	void set_violet();
	void set_silver();
	void set_gold();
	void set_turquoise();
	void color_product(int num);
	void color_product();
};

