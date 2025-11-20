#include "pch.h"
#define NC_Prog_Virtual_Machine_EXPORTS
#include "virtual_machine.h"
#include"manager_h/xt_armadillo_settings.h"
using namespace arma;

#define BUZHIXING 999999.123456

virtual_machine::virtual_machine()
{
	tool_using_num = -1;
	reset();

	//
}

void virtual_machine::reset()
{
	G00_03 = 1;
	G17_19 = 0;
	G43_44_49 = 2;
	G54_59 = 0;
	G90_91 = 0;
	G94_95 = 0;

	z_F = 0.0;
	z_S = 0.0;

	color_num = -1;

	Spindle_on = false;
	Spindle_ccw = true;
	coolant_on = false;

	SYS_Mac.fill(0.0);

	point_before(0) = 0.0;
	point_before(1) = 0.0;
	point_before(2) = 0.0;
	point_before(3) = 0.0;
	point_before(4) = 0.0;

	vec5 ls_vec;
	ls_vec = { 0.0,0.0,0.0,0.0,0.0 };
	if (SYS_G54_59.size() < 3)
	{
		for (int i = 0; i < 6; ++i)
		{
			SYS_G54_59.push_back(ls_vec);
		}
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{
			SYS_G54_59[i]=ls_vec;
		}
	}
	

	ls_vec = { 
		-219.832,
		-350.927,
		-149.50,
		0.0,
		0.0 
	};
	SYS_G54_59[0] = ls_vec;

	ls_vec = {
		-113.926000000,
		13.173000000,
		104.0,
		0.0,
		0.0
	};
	SYS_G54_59[3] = ls_vec;
	
	ls_vec = {
		-113.926000000,
		13.173000000,
		105.0,
		0.0,
		0.0
	};
	SYS_G54_59[2] = ls_vec;
	
	SYS_Abs = SYS_Mac - SYS_G54_59[G54_59];

	while (!cache.empty())
	{
		cache.pop();
	}

	init_SYS_coor();
	
}

void virtual_machine::set_RGB(int color)
{
	int i = 1;
	color_num = color;
}

int virtual_machine::get_cur_color()
{
	return color_num;
}

bool virtual_machine::BL_S_set(int i, double value)
{
	if (i > 0 && i < 200001)
	{
		if (BL_sharp.end() == BL_sharp.find(i))
		{
			BL_sharp.insert({ i,value });
		}
		else
		{
			BL_sharp.find(i)->second = value;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool virtual_machine::BL_S_read(int i, double& ans)
{
	if (i > 0 && i < 200001)
	{
		ans = BL_sharp.find(i)->second;
		return true;
	}
	else
	{
		return false;
	}
}


bool virtual_machine::BL_A_set(int i, double value)
{
	if (i > 0 && i < 200001)
	{
		if (BL_at.end() == BL_at.find(i))
		{
			BL_at.insert({ i,value });
		}
		else
		{
			BL_at.find(i)->second = value;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool virtual_machine::BL_A_read(int i, double& ans)
{
	if (i > 0 && i < 200001)
	{
		ans = BL_at.find(i)->second;
		return true;
	}
	else
	{
		return false;
	}
}


bool virtual_machine::set_SYS_G54_G59(int i, vec sys_value)
{
	if (i < 5 && i >= 0)
	{
		SYS_G54_59[i] = sys_value;
		SYS_Abs = SYS_Mac - SYS_G54_59[G54_59];
		return true;
	}
	else
	{
		return false;
	}
}

bool virtual_machine::G54_G59(int i)
{
	if (i < 6 && i >= 0)
	{
		G54_59 = i;
		SYS_Abs = SYS_Mac - SYS_G54_59[G54_59];
		return true;
	}
	else
	{
		return false;
	}
}

bool virtual_machine::G00()
{
	G00_03 = 0;
	return true;
}

bool virtual_machine::G01()
{
	G00_03 = 1;
	return true;
}

bool virtual_machine::G02()
{
	G00_03 = 2;
	return true;
}

bool virtual_machine::G03()
{
	G00_03 = 3;
	return true;
}

bool virtual_machine::G17()
{
	G17_19 = 0;
	return true;
}

bool virtual_machine::G18()
{
	G17_19 = 1;
	return true;
}

bool virtual_machine::G19()
{
	G17_19 = 2;
	return true;
}

using namespace arma;

bool virtual_machine::Move_cal(vec5 point_in)
{
	//运动超程检测
	/*int is_over = over_travel_check(point_in);
	if (is_over != -1)
	{
		return false;
	}*/
	//规定 99999.123456代表不填
	vec5 tar_point_1 = point_in;//绝对坐标
	vec5 tar_point_2 = point_in;//相对坐标
	vec5 tar_point = { 0,0,0,0,0 };//机床坐标下的目标
	for (int i = 0; i < 5; i++)
	{
		if (
			point_in[i] > BUZHIXING - 1.0
			&&
			point_in[i] < BUZHIXING + 1.0
			)
		{
			tar_point_1(i) = point_before(i) - SYS_G54_59[G54_59](i);
			tar_point_2(i) = 0.0;
		}
	}

	if (G90_91)
	{
		tar_point = SYS_G54_59[G54_59] + tar_point_1;
	}
	else
	{
		tar_point = point_before + tar_point_2;
	}

	if (G00_03 == 1)
	{
		//插补次数，需要计算
		if (move_point_quatity > 80 || move_point_quatity < 1)
		{
			//test 24.2.22
			move_point_quatity = 30;
		}
		int n = move_point_quatity;
		vec delta_move = (tar_point - point_before) / double(n);

		//11.8 非磨削点距离过大插值 
		if (norm((tar_point.subvec(0, 2) - point_before.subvec(0, 2))) > 10.0)
		{
			n = 20;
			delta_move = delta_move / n;
		}

		if (norm((tar_point.subvec(3, 4) - point_before.subvec(3, 4))) > 40.0)
		{
			n = 20;
			delta_move = delta_move / n;
		}
			
		for (int i = 0; i < n; i++)
		{
			cache.push(point_before + double(i + 1) * delta_move);
		}
	}

	else if (G00_03 == 0)
	{
		//插补次数，需要计算
		int n = 1;
		vec delta_move = (tar_point - point_before) / double(n);
		for (int i = 0; i < n; i++)
		{
			cache.push(point_before + double(i + 1) * delta_move);
		}
	}
	else
	{
		//不支持其他运动
		return false;
	}

	point_before = tar_point;

	//位置变化后，更新机床变量
	renew_SYS_coor(tar_point_2, tar_point_1);

	return true;
}

bool virtual_machine::move_cal_to_cache(double x, double y, double z, double a, double c)
{
	vec5 point_in = { x, y, z, a, c };

	Move_cal(point_in);

	return false;
}


bool virtual_machine::move_cache()
{
	if (!cache.empty())
	{
		SYS_Mac = cache.front();
		cache.pop();
		SYS_Abs = SYS_Mac - SYS_G54_59[G54_59];
		return true;
	}
	else
	{
		return false;
	}
}

bool virtual_machine::move(vec5 point_mac)
{
	SYS_Mac = point_mac;
	SYS_Abs = SYS_Mac - SYS_G54_59[G54_59];
	return false;
}

bool virtual_machine::F(double f_in)
{
	z_F = f_in;
	return true;
}

bool virtual_machine::S(double S_in)
{
	z_S = S_in;
	return false;
}

bool virtual_machine::M03()
{
	Spindle_on = true;
	Spindle_ccw = true;
	return true;
}

bool virtual_machine::M04()
{
	Spindle_on = true;
	Spindle_ccw = false;
	return true;
}

bool virtual_machine::M05()
{
	Spindle_on = false;
	Spindle_ccw = true;
	return true;
}

bool virtual_machine::M06(int tool_using)
{
	tool_using_num = tool_using;
	return true;
}

bool virtual_machine::M08()
{
	coolant_on = true;
	return true;
}

bool virtual_machine::M09()
{
	coolant_on = false;
	return true;
}

bool virtual_machine::M30()
{
	is_M30 = 1;
	return true;
}

bool virtual_machine::G90()
{
	G90_91 = true;
	return true;
}

bool virtual_machine::G91()
{
	G90_91 = false;
	return true;
}

//mat virtual_machine::get_BL_sharp()
//{
//	return BL_sharp;
//}
//
//mat virtual_machine::get_BL_at()
//{
//	return BL_at;
//}

vec5 virtual_machine::get_mac_sys()
{
	return SYS_Mac;
}

vec5 virtual_machine::get_abs_sys()
{
	return SYS_Abs;
}

void virtual_machine::set_move_speed(int num)
{
	if (num >= 1 && num <= 80)
	{
		move_point_quatity = num;
	}
}

bool virtual_machine::is_cache_empty()
{
	return cache.empty();
}

double virtual_machine::check_at_var_value(int index)
{

	return BL_at.find(index)->second;
}

double virtual_machine::check_sharp_var_value(int index)
{
	return BL_sharp.find(index)->second;
}

void virtual_machine::init_SYS_coor()
{
	//mac = 1441-1445
	//abs = 1361-1365


	//BL_S_set(1441, 0.123);
	//BL_sharp.insert({ 1441, 0.123 });
	//BL_sharp.insert({ 1442, 0.123 });
	//BL_sharp.insert({ 1443, 0.123 });
	//BL_sharp.insert({ 1444, 0.123 });
	//BL_sharp.insert({ 1445, 0.123 });
	//BL_sharp.insert({ 1361, 0.123 });
	//BL_sharp.insert({ 1362, 0.123 });
	//BL_sharp.insert({ 1363, 0.123 });
	//BL_sharp.insert({ 1364, 0.123 });
	//BL_sharp.insert({ 1365, 0.123 });
	//BL_sharp.insert({ 1608, 0.123 });

}

void virtual_machine::renew_SYS_coor(vec5 tar_mac, vec5 tar_abs)
{

	BL_S_set(1441, tar_mac(0));
	BL_S_set(1442, tar_mac(1));
	BL_S_set(1443, tar_mac(2));
	BL_S_set(1444, tar_mac(3));
	BL_S_set(1445, tar_mac(4));

	BL_S_set(1361, tar_abs(0));
	BL_S_set(1362, tar_abs(1));
	BL_S_set(1363, tar_abs(2));
	BL_S_set(1364, tar_abs(3));
	BL_S_set(1365, tar_abs(4));

	BL_S_set(1999, 999.12345);
}

int virtual_machine::over_travel_check(vec5 tar_point)
{
	//界面强制弹出对话框，显示对应超程
	if (tar_point(0) > BUZHIXING - 0.000001 &&
		tar_point(0) < BUZHIXING + 0.000001)
	{
		//不执行
	}
	else if (tar_point(0) > 5.0 || tar_point(0) < -420.0)
	{
		return 0;
	}
	if (tar_point(1) > BUZHIXING - 0.000001 &&
		tar_point(1) < BUZHIXING + 0.000001)
	{
		//不执行
	}
	else if (tar_point(1) > 5.0 || tar_point(1) < -362.0)
	{
		return 1;
	}
	if (tar_point(2) > BUZHIXING - 0.000001 &&
		tar_point(2) < BUZHIXING + 0.000001)
	{
		//不执行
	}
	else if (tar_point(2) > 25.0 || tar_point(2) < -193.0)
	{
		return 2;
	}
	if (tar_point(4) > BUZHIXING - 0.000001 &&
		tar_point(4) < BUZHIXING + 0.000001)
	{
		//不执行
	}
	else if (tar_point(4) > 100.0 || tar_point(4) < -100.0)
	{
		return 4;
	}
	return -1; //没有超
}

int virtual_machine::get_using_tool()
{
	return tool_using_num;
}

void virtual_machine::set_using_sl_num_on_slz(int in_sl_num_on_slz)
{
	using_sl_pos_on_slz = in_sl_num_on_slz;
}

int virtual_machine::get_using_sl_num_on_slz()
{
	return using_sl_pos_on_slz;
}

void virtual_machine::clear_cache()
{
	while (!cache.empty()) {
		cache.pop();
	}
}




