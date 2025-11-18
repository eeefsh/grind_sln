#include "pch.h"
#define NC_Prog_visualize_manager_EXPORTS
#include "GLlist_Color.h"
#include"manager_h/xt_glfw_setting.h"

gyGLColor::gyGLColor()
{
	//使用GLAD来加载OpenGL
	::gladLoadGL();
	color_amb = { 1.0,0,0,1.0 };//红色
	color_diff = { 1.0,0,0,1.0 };//红色
	color_spec = { 1.0,0,0,1.0 };//红色
	shin = 1.0;
}

gyGLColor::~gyGLColor()
{
}

void gyGLColor::set_red()
{
	color_amb = { 1.0,0,0,1.0 };//红色
	color_diff = { 1.0,0,0,1.0 };//红色
	color_spec = { 1.0,0,0,1.0 };//红色
	shin = 1.0;
}

void gyGLColor::set_yellow()
{
	color_amb = { 1.0,1.0,0.0,1.0 };//红色
	color_diff = { 1.0,1.0,0.0,1.0 };//红色
	color_spec = { 1.0,1.0,0.0,1.0 };//红色
	shin = 1.0;
}

void gyGLColor::set_green()
{
	color_amb = { 0.0,1.0,0.0,1.0 };//红色
	color_diff = { 0.0,1.0,0.0,1.0 };//红色
	color_spec = { 0.0,1.0,0.0,1.0 };//红色
	shin = 1.0;
}

void gyGLColor::set_blue()
{
	color_amb = { 0.0,0,1.0,1.0 };//红色
	color_diff = { 0.0,0,1.0,1.0 };//红色
	color_spec = { 0.0,0,1.0,1.0 };//红色
	shin = 1.0;
}
void gyGLColor::set_purple()
{
	color_amb = { 1.0, 0.0, 1.0, 1.0 };
	color_diff = { 1.0, 0.0, 1.0, 1.0 };
	color_spec = { 1.0, 0.0, 1.0, 1.0 };
	shin = 1.0;
}
// 橙色 
void gyGLColor::set_orange()
{
	color_amb = { 1.0, 0.5, 0.0, 1.0 };
	color_diff = { 1.0, 0.5, 0.0, 1.0 };
	color_spec = { 1.0, 0.5, 0.0, 1.0 };
	shin = 1.0;
}

// 粉色 
void gyGLColor::set_pink()
{
	color_amb = { 1.0, 0.5, 0.5, 1.0 };
	color_diff = { 1.0, 0.5, 0.5, 1.0 };
	color_spec = { 1.0, 0.5, 0.5, 1.0 };
	shin = 1.0;
}

// 灰色 
void gyGLColor::set_gray()
{
	color_amb = { 0.5, 0.5, 0.5, 1.0 };
	color_diff = { 0.5, 0.5, 0.5, 1.0 };
	color_spec = { 0.5, 0.5, 0.5, 1.0 };
	shin = 1.0;
}

// 棕色 
void gyGLColor::set_brown()
{
	color_amb = { 0.5, 0.25, 0.0, 1.0 };
	color_diff = { 0.5, 0.25, 0.0, 1.0 };
	color_spec = { 0.5, 0.25, 0.0, 1.0 };
	shin = 1.0;
}

// 海蓝色 
void gyGLColor::set_sea_blue()
{
	color_amb = { 0.0, 0.5, 1.0, 1.0 };
	color_diff = { 0.0, 0.5, 1.0, 1.0 };
	color_spec = { 0.0, 0.5, 1.0, 1.0 };
	shin = 1.0;
}

// 紫罗兰色 
void gyGLColor::set_violet()
{
	color_amb = { 0.5, 0.0, 1.0, 1.0 };
	color_diff = { 0.5, 0.0, 1.0, 1.0 };
	color_spec = { 0.5, 0.0, 1.0, 1.0 };
	shin = 1.0;
}

// 银色 
void gyGLColor::set_silver()
{
	color_amb = { 0.75, 0.75, 0.75, 1.0 };
	color_diff = { 0.75, 0.75, 0.75, 1.0 };
	color_spec = { 0.75, 0.75, 0.75, 1.0 };
	shin = 1.0;
}

// 金色 
void gyGLColor::set_gold()
{
	color_amb = { 1.0, 0.84, 0.0, 1.0 };
	color_diff = { 1.0, 0.84, 0.0, 1.0 };
	color_spec = { 1.0, 0.84, 0.0, 1.0 };
	shin = 1.0;
}
void gyGLColor::set_turquoise()
{
	color_amb = { 0.25, 0.88, 0.82, 1.0 };
	color_diff = { 0.25, 0.88, 0.82, 1.0 };
	color_spec = { 0.25, 0.88, 0.82, 1.0 };
	shin = 1.0;
}
void gyGLColor::color_product(int num)
{
	num = num % 14;
	switch (num) {
	case 0:
		set_red();
		break;
	case 1:
		set_yellow();
		break;
	case 2:
		set_green();
		break;
	case 3:
		set_blue();
		break;
	case 4:
		set_purple();
		break;
	case 5:
		set_orange();
		break;
	case 6:
		set_pink();
		break;
	case 7:
		set_gray();
		break;
	case 8:
		set_brown();
		break;
	case 9:
		set_sea_blue();
		break;
	case 10:
		set_violet();
		break;
	case 11:
		set_silver();
		break;
	case 12:
		set_gold();
		break;
	case 13:
		set_turquoise();
		break;
	default:
		break;

	}
}
void gyGLColor::color_product()
{
	std::default_random_engine engine(std::time(nullptr));
	std::uniform_int_distribution<int> dist(0, 14);
	int rand_num = dist(engine);

	// 根据随机数调用不同的set函数
	switch (rand_num) {
	case 0:
		set_red();
		break;
	case 1:
		set_yellow();
		break;
	case 2:
		set_green();
		break;
	case 3:
		set_blue();
		break;
	case 4:
		set_purple();
		break;
	case 5:
		set_orange();
		break;
	case 6:
		set_pink();
		break;
	case 7:
		set_gray();
		break;
	case 8:
		set_brown();
		break;
	case 9:
		set_sea_blue();
		break;
	case 10:
		set_violet();
		break;
	case 11:
		set_silver();
		break;
	case 12:
		set_gold();
		break;
	case 13:
		set_turquoise();
		break;
	default:
		break;
	}
}