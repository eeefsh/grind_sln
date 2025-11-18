#include"pch.h"
#include "Para_State_A.h"

Para_State_A::Para_State_A()
{
	A_before = 0.0;
}

Para_State_A::~Para_State_A()
{
	//std::cout << "Path_Para has been deconstructed" << endl;
}

double Para_State_A::get_A_before()
{
	return A_before;
}

void Para_State_A::set_A_before(double A_before_in)
{
	A_before = A_before_in;
}

double Para_State_A::get_C_before()
{
	return C_before;
}

void Para_State_A::set_C_before(double C_before_in)
{
	C_before = C_before_in;
}
