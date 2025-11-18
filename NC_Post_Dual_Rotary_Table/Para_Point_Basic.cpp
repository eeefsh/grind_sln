#include"pch.h"
#include "Para_Point_Basic.h"

Para_Point_Basic::Para_Point_Basic()
{
    G_O = { 0.0,0.0,0.0 };
    G_N = { 0.0,0.0,1.0 };
    G_SYS_D = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
}

Para_Point_Basic::~Para_Point_Basic()
{
    //std::cout << "Path_Para has been deconstructed" << endl;
}

vec3 Para_Point_Basic::get_G_O()
{
    return G_O;
}

void Para_Point_Basic::set_G_O(vec3 G_O_in)
{
    G_O = G_O_in;
}

vec3 Para_Point_Basic::get_G_N()
{
    return G_N;
}

void Para_Point_Basic::set_G_N(vec3 G_N_in)
{
    G_N = G_N_in;
}

mat33 Para_Point_Basic::get_G_SYS_D()
{
    return G_SYS_D;
}

void Para_Point_Basic::set_G_SYS_D(mat33 G_SYS_D_in)
{
    G_SYS_D = G_SYS_D_in;
}