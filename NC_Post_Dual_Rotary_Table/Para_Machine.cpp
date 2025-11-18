#include"pch.h"
#include "Para_Machine.h"

Para_Machine::Para_Machine()
{
    GC_SYS_G = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
    GC_O_G = { 0.0,0.0,0.0 };
    w_c2g = 0.0;
}

Para_Machine::~Para_Machine()
{
    //std::cout << "Para_Machine has been deconstructed." << std::endl;
}

mat33 Para_Machine::get_GC_SYS_G()
{
    return GC_SYS_G;
}

void Para_Machine::set_GC_SYS_G(mat33 GC_SYS_G_in)
{
    GC_SYS_G = GC_SYS_G_in;
}

vec3 Para_Machine::get_GC_O_G()
{
    return GC_O_G;
}

void Para_Machine::set_GC_O_G(vec3 GC_O_G_in)
{
    GC_O_G = GC_O_G_in;
}

double Para_Machine::get_w_c2g()
{
    return w_c2g;
}

void Para_Machine::set_w_c2g(double w_c2g_in)
{
    w_c2g = w_c2g_in;
}

