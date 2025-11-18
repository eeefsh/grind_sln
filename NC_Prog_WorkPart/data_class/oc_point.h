#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include"manager_h/xt_armadillo_settings.h"

class NC_Prog_WorkPart_API double3v;

//int坐标
class NC_Prog_WorkPart_API int3v
{
public:
	int	x = 0;
	int	y = 0;
	int	z = 0;
public:
	int3v();
    ~int3v();

	int3v(int x_in, int y_in, int z_in);

    bool operator<(const int3v& p) const {

        //double  err_now = 0.0001;
        if (x < p.x )
        {
            return true;
        }
        else if (x > p.x )
        {
            return false;
        }
        else
        {
            if (y < p.y)
            {
                return true;
            }
            else if (y > p.y)
            {
                return false;
            }
            else
            {
                if (z < p.z)
                {
                    return true;
                }
            }
        }
        return false;
    }

public:
	double3v turn_point_double(double w);
};

class NC_Prog_WorkPart_API double3v
{
public:
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
public:
    double3v() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
public:
    double3v(vec3 v3)
    {
        x = v3(0);
        y = v3(1);
        z = v3(2);
    }

    double3v(int xin, int yin, int zin)
    {
        x = double (xin);
        y = double (yin);
        z = double (zin);
    }

    bool operator<(const double3v& p) const {

        double  err_now = 0.001;
        if (x < p.x - err_now)
        {
            return true;
        }
        else if (x > p.x - err_now && x < p.x + err_now)
        {
            if (y < p.y - err_now)
            {
                return true;
            }
            else if (y > p.y - err_now && y < p.y + err_now)
            {
                if (z < p.z - err_now)
                {
                    return true;
                }
            }
        }
        return false;
    }
	
    int3v turn_point_int(double w);
};

class NC_Prog_WorkPart_API mesh_cutted
{
    //自 前  左   前左
public:
    double3v p1;
    double3v p2;
    double3v p3;
    double3v p4;
};

class NC_Prog_WorkPart_API mesh_tri
{
public:
    double3v p1;
    double3v p2;
    double3v p3;
    char color = 0;
};


