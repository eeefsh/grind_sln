#include"pch.h"
#include "Para_Tools.h"

Para_Tools::Para_Tools()
{
    d_sl = 0.0;
    fl_sl = 0.0;
    r_sl = 0.0;
}

Para_Tools::~Para_Tools()
{
    //std::cout << "Para_Tools has been deconstructed." << std::endl;
}

double Para_Tools::get_d_sl()
{
    return d_sl;
}

void Para_Tools::set_d_sl(double d_sl_in)
{
    d_sl = d_sl_in;
}

double Para_Tools::get_fl_sl()
{
    return fl_sl;
}

void Para_Tools::set_fl_sl(double fl_sl_in)
{
    fl_sl = fl_sl_in;
}

double Para_Tools::get_r_sl()
{
    return r_sl;
}

void Para_Tools::set_r_sl(double r_sl_in)
{
    r_sl = r_sl_in;
}
