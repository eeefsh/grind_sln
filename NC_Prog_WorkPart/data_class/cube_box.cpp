
#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "cube_box.h"

//#include<iostream>




cube_box::cube_box(double d):
	w1(d)
{

}

void cube_box::set_max_xyz(int3v Max_in)
{
	X_max =	Max_in.x;
	Y_max = Max_in.y;
	Z_max = Max_in.z;
}

void cube_box::set_min_xyz(int3v Min)
{
	X_min = Min.x;
	Y_min = Min.y;
	Z_min = Min.z;
}

void cube_box::init_box()
{
	int resultX = X_max - X_min;
	int resultY = Y_max - Y_min;
	int resultZ = Z_max - Z_min;
	w = static_cast<int>(w1 * 2.0 * 1000.0);
	int nx = resultX / w + 1;
	int ny = resultY / w + 1;
	int nz = resultZ / w + 1;
	if (nx % 2 == 0)
	{
		c_point.x = (X_max + X_min) / 2;
	}
	else
	{
		c_point.x = (X_max + X_min) / 2 + w / 2;
	}
	if (ny % 2 == 0)
	{
		c_point.y = (Y_max + Y_min) / 2;
	}
	else
	{
		c_point.y = (Y_max + Y_min) / 2 + w / 2;
	}
	if (nz % 2 == 0)
	{
		c_point.z = (Z_max + Z_min) / 2;
	}
	else
	{
		c_point.z = (Z_max + Z_min) / 2 + w / 2;
	}
	n = std::max({ nx, ny, nz });	

}

int3v cube_box::get_double3v()
{
	return c_point;
}

int cube_box::get_n()
{
	return n;
}

int cube_box::get_w()
{
	return w;
}