#include "pch.h"
#include "wheel_output.h"
#include "wheel_define.h"
#include "line_manager.h"
using namespace wheel_namespace;


bool wheel_output::no_find_flag(std::set<wheel_database_namespace::list_time>& list_val, int pos)
{
    for (auto iter = list_val.begin(); iter != list_val.end(); ++iter)
    {
        if (iter->pos == pos)
        {
            return 0;
        }
    }
    return 1;
}

void wheel_output::get_x_max(mat val, double& ans)
{
    for (size_t i = 0; i < val.n_cols; i++)
    {
        if (val.col(i)[0] > ans)
        {
            ans = val.col(i)[0];
        }
    }
}

int wheel_output::get_wheel_Ry(int wheel_key, bool wai, double& Ry_ans)
{
    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto data = read_wheel(wheel_key);
    if (data.key_group == -1)
    {
        return 1;
    }
    if (wai)
    {
        Ry_ans = data.Ry1;
    }
    else
    {
        Ry_ans = data.Ry0;
    }
    return 0;
}

int wheel_output::get_wheel_L(int wheel_key, bool wai, double& L_ans)
{
    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto data = read_wheel(wheel_key);
    if (data.key_group == -1)
    {
        return 1;
    }
    if (wai)
    {
        L_ans = data.L1;
    }
    else
    {
        L_ans = data.L0;
    }
    return 0;
}

int wheel_output::get_wheel_r(int wheel_key, bool wai, double& r_ans)
{
    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto data = read_wheel(wheel_key);
    if (data.key_group == -1)
    {
        return 1;
    }
    
    if (wai)
    {
        if (!data.daozhuang)
        {
            r_ans = data.data[6];
        }
        else
        {
            r_ans = data.data[5];
        }
    }
    else
    {
        if (!data.daozhuang)
        {
            r_ans = data.data[5];
        }
        else
        {
            r_ans = data.data[6];
        }
    }
    return 0;
}

int wheel_output::get_wheel_group_name(int wheel_key, std::string& group_name)
{
    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto wheel_data_temp = read_wheel(wheel_key);
    if (wheel_data_temp.key_group == -1)
    {
        return 1;
    }
    auto data = read_group(wheel_data_temp.key_group);
    group_name = data.get_name();
    return 0;
}

int wheel_output::get_group_name(int group_key, std::string& group_name)
{
    if (no_find_flag(list_group_all, group_key))
    {
        return 1;
    }
    auto group_data = read_group(group_key);
    
    group_name = group_data.get_name();
    return 0;
}

int wheel_output::get_wheel_name(int wheel_key, std::string& wheel_name)
{

    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto wheel_data_temp = read_wheel(wheel_key);
    wheel_name = wheel_data_temp.get_name();
    return 0;
}

int wheel_output::get_2D_wheel_outline(int wheel_key, mat& ans)
{
    if (no_find_flag(list_wheel_all, wheel_key))
    {
        return 2;
    }
    auto data = read_wheel(wheel_key);
    if (data.key_group == -1)
    {
        return 1;
    }
    switch (data.type_wheel)
    {
        case _Ping:
        {
            ans = wheel_Ping_2D(data);
        }break;
        case _Beixing:
        {
            ans = wheel_Beixing_2D(data);
        }break;
        case _Yuanjiao:
        {
            ans = wheel_Yuanjiao_2D(data);
        }break;
        case _Diexing:
        {
            ans = wheel_Diexing_2D(data);
        }break;
        case _DXF:
        {
            ans = wheel_DXF_2D(data);
        }break;
        case _Jianjiao:
        {
            ans = wheel_Jianjiao_2D(data);
        }break;
        default:
            break;
    }
    return 0;
}


int wheel_output::get_group_show_outline(int group_key, std::vector<mat>& ans)
{
    if (no_find_flag(list_group_all, group_key))
    {
        return 1;
    }
    auto g_data = read_group(group_key);

    double gan_L = _I32_MIN;

    for (size_t i = 0; i < sizeof(g_data.weizhi) / sizeof(g_data.weizhi[0]); i++)
    {
        if (g_data.weizhi[i].key_wheel != -1)
        {
            auto w_data = read_wheel(g_data.weizhi[i].key_wheel);
            double temp = 0;
            switch (w_data.type_wheel)
            {
            case _Ping:
            {
                ans.push_back(wheel_Ping_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            case _Beixing:
            {
                ans.push_back(wheel_Beixing_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            case _Yuanjiao:
            {
                ans.push_back(wheel_Yuanjiao_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            case _Diexing:
            {
                ans.push_back(wheel_Diexing_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            case _DXF:
            {
                ans.push_back(wheel_DXF_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            case _Jianjiao:
            {
                ans.push_back(wheel_Jianjiao_2D(w_data));
                get_x_max(ans.back(), gan_L);
            }break;
            default:
                break;
            }
        }
    }
    ans.push_back(gan_2D(gan_L, g_data.gan_D, g_data.nut_L, g_data.nut_D));
    
    return 0;
}

int wheel_output::get_group_key_by_wheel_key(int wheel_key)
{
    auto data = read_wheel(wheel_key);
    return data.key_group;
}

int wheel_output::get_a_group_all_wheel_key(int group_key, std::vector<int>& ans)
{
    if (no_find_flag(list_group_all, group_key))
    {
        return 1;
    }

    auto data = read_group(group_key);

    for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
    {
        if (data.weizhi[i].key_wheel != -1)
        {
            ans.push_back(data.weizhi[i].key_wheel);
        }

    }
    return 0;
}


std::vector<int> wheel_output::get_edit_buff_wheel()
{
    std::vector<int> ans(edit_buff_wheel.begin(), edit_buff_wheel.end());
    edit_buff_wheel.clear();
    return ans;
}

//圆弧角度划分
vec wheel_output_namespace::wheel_outlines::rot_angle(double err, double r, double start, double end)
{
    double d = 2.0 * acos((r - err) / r) * (180.0 / datum::pi);
    vec temp = linspace(start, end, ceil(360.0 / d) + 1);
    return temp;
}

//获取圆弧插值点
//圆心，精度，半径，起始角度，结束角度
//err是插值后相邻两点的中点到圆心的距离偏差
std::vector<vec3> wheel_output_namespace::wheel_outlines::discrete_arc(vec c, double err, double r, double start, double end)
{
    std::vector<vec3> temp;
    vec r_normal = { r, 0.0, 0.0 };
    vec angle_temp = rot_angle(err, r, start, end);
    for (size_t i = 0; i < angle_temp.size(); i++)
    {
        temp.push_back(c + (tcRotZ(3, angle_temp[i]) * r_normal));
    }
    return temp;
}

mat wheel_output_namespace::wheel_outlines::wheel_Ping_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp;

    if (!data.daozhuang)
    {
        temp[0] = data.L0 - data.data[5];
        temp[1] = 0;
        temp[2] = 0;
        buff.push_back(temp);

        temp[0] = data.L0;
        temp[1] = data.Ry0;
        auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 180, 90 - data.data[3]);
        buff.insert(buff.end(), yuan.begin(), yuan.end());
        yuan.clear();

        temp[0] = data.L1;
        temp[1] = data.Ry1;
        yuan = discrete_arc(temp, data.data[6] * e, data.data[6], 90 - data.data[3], 0);
        buff.insert(buff.end(), yuan.begin(), yuan.end());

        temp[0] = data.L1 + data.data[6];
        temp[1] = 0;
        buff.push_back(temp);
    }
    else
    {
        temp[0] = data.L0 - data.data[6];
        temp[1] = 0;
        temp[2] = 0;
        buff.push_back(temp);

        temp[0] = data.L0;
        temp[1] = data.Ry0;
        auto yuan = discrete_arc(temp, data.data[6] * e, data.data[6], 180, 90 + data.data[3]);
        buff.insert(buff.end(), yuan.begin(), yuan.end());
        yuan.clear();

        temp[0] = data.L1;
        temp[1] = data.Ry1;
        yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 90 + data.data[3], 0);
        buff.insert(buff.end(), yuan.begin(), yuan.end());
        buff.push_back(vec({ data.L1 + data.data[5], 0.0, 0.0 }));
    }
    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::wheel_Beixing_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp;

    temp[0] = data.L0 - data.data[7] + data.data[5];
    temp[1] = 0;
    temp[2] = 0;
    buff.push_back(temp);

    temp[0] = data.L0 - data.data[7] + data.data[5];
    temp[1] = data.Ry0 - (data.data[7] - data.data[5]) * tan(data.data[4] / 180 * datum::pi);
    temp[1] = temp[1] + data.data[5] / cos(data.data[4] / 180 * datum::pi);
    buff.push_back(temp);

    temp[0] = data.L0;
    temp[1] = data.Ry0;
    auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 90 + data.data[4], 0 - data.data[3]);
    buff.insert(buff.end(), yuan.begin(), yuan.end());

    temp[1] = data.data[9] - (data.data[5] * sin(data.data[3] / 180 * datum::pi) + data.data[5]);
    temp[1] = temp[1] / cos(data.data[3] / 180 * datum::pi);
    vec3 temp_n({ 0,-temp[1],0 });
    temp = (tcRotZ(3, -data.data[3]) * temp_n) + yuan.back();
    buff.push_back(temp);

    double shendu = data.data[8] - (data.data[7] - (buff.back() - buff.front())[0]);
    shendu = shendu / cos(data.data[4] / 180 * datum::pi);
    temp_n[0] = -shendu;
    temp_n[1] = 0;
    temp_n[2] = 0;
    temp = (tcRotZ(3, data.data[4]) * temp_n) + buff.back();
    buff.push_back(temp);

    temp[1] = 0;
    temp[2] = 0;
    buff.push_back(temp);

    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::wheel_Yuanjiao_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp;

    temp[0] = data.L0 - data.data[5];
    temp[1] = 0;
    temp[2] = 0;
    buff.push_back(temp);

    temp[0] = data.L0;
    temp[1] = data.Ry0;
    auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 180, 0);
    buff.insert(buff.end(), yuan.begin(), yuan.end());

    temp[0] = data.L0 + data.data[5];
    temp[1] = 0;
    buff.push_back(temp);

    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::wheel_Diexing_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp;

    if (!data.daozhuang)
    {
        temp[0] = data.L0 + data.data[5] - data.data[7];
        temp[1] = 0;
        temp[2] = 0;
        buff.push_back(temp);

        temp[1] = data.Ry0 - (data.data[7] - data.data[5]) * tan((90 - data.data[3]) / 180 * datum::pi);
        temp[1] = temp[1] + data.data[5] / cos((90 - data.data[3]) / 180 * datum::pi);
        buff.push_back(temp);

        temp[0] = data.L0;
        temp[1] = data.Ry0;
        auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 180 - data.data[3], 0);
        buff.insert(buff.end(), yuan.begin(), yuan.end());

        temp[0] = data.L0 + data.data[5];
        temp[1] = 0;
        buff.push_back(temp);
    }
    else
    {
        temp[0] = data.L0 - data.data[5];
        temp[1] = 0;
        temp[2] = 0;
        buff.push_back(temp);

        temp[0] = temp[0] + data.data[5];
        temp[1] = data.Ry0;
        auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 180, data.data[3]);
        buff.insert(buff.end(), yuan.begin(), yuan.end());

        temp[0] = data.L0 - data.data[5] + data.data[7];
        temp[1] = data.Ry0 - (data.data[7] - data.data[5]) * tan((90 - data.data[3]) / 180 * datum::pi);
        temp[1] = temp[1] + data.data[5] / cos((90 - data.data[3]) / 180 * datum::pi);
        buff.push_back(temp);

        temp[1] = 0;
        buff.push_back(temp);
    }
    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::wheel_DXF_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp_n;
    auto dir = data.get_dir_dxf();
    line_manager line(dir);
    mat temp;
    line.get_curvature_point(e * 0.1, temp);

    temp_n = temp.col(0).rows(3, 5);
    temp_n[0] = temp_n[0] + data.L0;
    temp_n[1] = 0;
    buff.push_back(temp_n);

    for (size_t i = 0; i < temp.n_cols; i++)
    {
        temp_n = temp.col(i).rows(3, 5);
        temp_n[0] = temp_n[0] + data.L0;
        temp_n[1] = temp_n[1] + data.data[1] / 2;
        buff.push_back(temp_n);
    }
    temp_n = buff.back();
    temp_n[1] = 0;
    temp_n[2] = 0;
    buff.push_back(temp_n);

    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::wheel_Jianjiao_2D(wheel_data data, double e)
{
    std::vector<vec3> buff;
    vec3 temp;

    temp[0] = data.L0 - data.data[8] / 2;
    temp[1] = 0;
    temp[2] = 0;
    buff.push_back(temp);

    temp[1] = ((data.data[8] - data.data[7]) / 2) / tan(data.data[4] / 2 / 180 * datum::pi);
    temp[1] = (data.data[2] / 2 - temp[1]);
    buff.push_back(temp);

    temp[0] = data.L0 - data.data[7] / 2;
    temp[1] = data.data[2] / 2;
    buff.push_back(temp);

    temp[1] = data.Ry0 - data.data[7] / 2 * tan((90 - data.data[3] / 2) / 180 * datum::pi);
    temp[1] = temp[1] + data.data[5] / cos((90 - data.data[3] / 2) / 180 * datum::pi);
    buff.push_back(temp);

    temp[0] = data.L0;
    temp[1] = data.Ry0;
    auto yuan = discrete_arc(temp, data.data[5] * e, data.data[5], 180 - data.data[3] / 2, 0 + data.data[3] / 2);
    buff.insert(buff.end(), yuan.begin(), yuan.end());

    temp[0] = data.L0 + data.data[7] / 2;
    temp[1] = data.Ry0 - data.data[7] / 2 * tan((90 - data.data[3] / 2) / 180 * datum::pi);
    temp[1] = temp[1] + data.data[5] / cos((90 - data.data[3] / 2) / 180 * datum::pi);
    buff.push_back(temp);

    temp[0] = data.L0 + data.data[7] / 2;
    temp[1] = data.data[2] / 2;
    buff.push_back(temp);

    temp[0] = data.L0 + data.data[8] / 2;
    temp[1] = ((data.data[8] - data.data[7]) / 2) / tan(data.data[4] / 2 / 180 * datum::pi);
    temp[1] = (data.data[2] / 2 - temp[1]);
    buff.push_back(temp);

    temp[1] = 0;
    buff.push_back(temp);

    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}

mat wheel_output_namespace::wheel_outlines::gan_2D(double gan_L, double gan_D, double nut_L, double nut_D)
{
    std::vector<vec3> buff;
    vec3 temp = { 0,0,0 };
    buff.push_back(temp);

    temp[1] = gan_D / 2;
    buff.push_back(temp);

    temp[0] = gan_L;
    buff.push_back(temp);

    temp[1] = nut_D / 2;
    buff.push_back(temp);

    temp[0] = gan_L + nut_L;
    buff.push_back(temp);

    temp[1] = 0;
    buff.push_back(temp);

    mat ans(3, buff.size());
    for (size_t i = 0; i < buff.size(); ++i)
    {
        ans(0, i) = buff[i][0]; // 第一行 
        ans(1, i) = buff[i][1]; // 第二行 
        ans(2, i) = buff[i][2]; // 第三行 
    }
    return ans;
}
