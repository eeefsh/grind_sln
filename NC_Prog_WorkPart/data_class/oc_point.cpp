#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "oc_point.h"


int3v::int3v():
    x(0),
    y(0),
    z(0)
{
	
}

int3v::int3v(int x_in, int y_in, int z_in)
{
	x = x_in;
	y = y_in;
	z = z_in;
}



int3v::~int3v()
{
    int i = 0;
}

double3v int3v::turn_point_double(double w)
{
    double3v doublep;
    doublep.x = static_cast<double>(x) / 1000.0;
    doublep.y = static_cast<double>(y) / 1000.0;
    doublep.z = static_cast<double>(z) / 1000.0;
    return doublep;
}

double roundToNearest(double num, double distance)
{
    if (distance < 0.001)
    {
        distance = 0.001;
    }
    return round(num / ((2.0 * distance))) * ((2.0 * distance));
}

int3v double3v::turn_point_int(double w)
{
    
    /*int x0 = static_cast<int>(roundToNearest(x, w) * 1000.0);
    int y0 = static_cast<int>(roundToNearest(y, w) * 1000.0);
    int z0 = static_cast<int>(roundToNearest(z, w) * 1000.0);*/
    
    int x0 = static_cast<int>(round(roundToNearest(x, w) * 1000.0));
    int y0 = static_cast<int>(round(roundToNearest(y, w) * 1000.0));
    int z0 = static_cast<int>(round(roundToNearest(z, w) * 1000.0));
   
    return int3v(x0, y0, z0);
}


