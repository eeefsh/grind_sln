#include"pch.h"
#include "Para_Coord_Values.h"

Para_Coord_Values::Para_Coord_Values()
{
	JC_O_D = { 0.0,0.0,0.0 };
	JC_O_DC = { 0.0,0.0,0.0 };
	JC_N = { 0.0,0.0,0.0 };
	JC_SYS_D = eye(3, 3);
	An = 0.0;
	Cn = 0.0;
}

Para_Coord_Values::~Para_Coord_Values()
{
	//std::cout << "Path_Coord_Values  has been deconstructed." << endl;
}

vec3 Para_Coord_Values::get_JC_O_DC()
{
	return JC_O_DC;
}

void Para_Coord_Values::set_JC_O_DC(vec3 JC_O_DC_in)
{
	JC_O_DC = JC_O_DC_in;
}

vec3 Para_Coord_Values::get_JC_O_D()
{
	return JC_O_D;
}

void Para_Coord_Values::set_JC_SYS_D(mat JC_SYS_D_in)
{
	JC_SYS_D = JC_SYS_D_in;
}

void Para_Coord_Values::set_JC_O_D(vec3 JC_O_D_in)
{
	JC_O_D = JC_O_D_in;
}

vec3 Para_Coord_Values::get_JC_N()
{
	return JC_N;
}

void Para_Coord_Values::set_JC_N(vec3 JC_N_in)
{
	JC_N = JC_N_in;
}

mat Para_Coord_Values::get_JC_SYS_D()
{
	return JC_SYS_D;
}

double Para_Coord_Values::get_An()
{
	return An;
}

void Para_Coord_Values::set_An(double An_in)
{
	An = An_in;
}

double Para_Coord_Values::get_Cn()
{
	return Cn;
}

void Para_Coord_Values::set_Cn(double Cn_in)
{
	Cn = Cn_in;
}