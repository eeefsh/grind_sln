#include "pch.h"
#define NC_wheel_Intersecting_line_EXPORTS
#include "jiemian.h"

vec jiemian_namespace::get_jiemian_heng(double d)
{
    vec n = { 0,0,1 };
    vec p = { 0,0,d };
   
    return join_cols(n, p);
}

vec jiemian_namespace::get_jiemian_zhou(vec base_p, double angle, double d)
{
    base_p(2) = 0;
    vec n = tcRotZ(3, 90) * base_p;
    vec p = d * normalise(n);
   
    return join_cols(n, p);
}

vec jiemian_namespace::get_jiemian_fa(mat val, double d)
{
    if (val.col(0)(2) - val.col(1)(2) < 0)
    {
        for (size_t i = 1; i < val.n_cols; i++)
        {
            if (val.col(i)(2) >= d && val.col(i - 1)(2) <= d)
            {
                vec n = val.col(i) - val.col(i - 1);
                vec p = { 0,0,d };
                return join_cols(n, p);
            }
        }
    }
    else
    {
        for (size_t i = 1; i < val.n_cols; i++)
        {
            if (val.col(i)(2) <= d && val.col(i - 1)(2) >= d)
            {
                vec n = val.col(i - 1) - val.col(i);
                vec p = { 0,0,d };
                return join_cols(n, p);
            }
        }
    }
}

vec jiemian_namespace::get_jiemian_renyi(double angle_zhou, double angle_jing, double d)
{
    vec p = { 0,0,d };
    vec n = tcRotZ(3, angle_zhou) * tcRotX(3, angle_jing) * tcZ(3);
    
    return join_cols(n, p);
}
