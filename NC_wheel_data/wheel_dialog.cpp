#include "pch.h"
#include "wheel_dialog.h"
#include "wheel_define.h"
constexpr auto M_PI = 3.14159265358979323846;   // pi;
using namespace wheel_namespace;
using namespace wheel_database_namespace;
using namespace wheel_dialog_namespace;

wheel_dialog::wheel_dialog()
{
}

int wheel_dialog::add_group(group_data val)
{
	for (size_t i = 0; i < sizeof(val.weizhi) / sizeof(val.weizhi[0]); i++)
	{
		if (val.weizhi[i].key_wheel != -1)
		{
			auto it = read_wheel( val.weizhi[i].key_wheel);
			switch (it.type_wheel)
			{
				case _Ping:
				{
					canshu_Ping_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break;
				case _Beixing:
				{
					canshu_Beixing_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break;
				case _Yuanjiao:
				{
					canshu_Yuanjiao_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break;
				case _Diexing:
				{
					canshu_Diexing_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break;
				case _DXF:
				{
					canshu_DXF_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break; 
				case _Jianjiao:
				{
					canshu_Jianjiao_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					edit_wheel(val.weizhi[i].key_wheel, it);
				}break;
				default:
					break;
			}
		}
	}
	
	return wheel_database::add_group(val);
}

void wheel_dialog::edit_wheel(int pos, wheel_data val)
{
	if (val.key_group != -1)
	{
		auto it = read_group(val.key_group);
		for (size_t i = 0; i < sizeof(it.weizhi) / sizeof(it.weizhi[0]); i++)
		{
			if (it.weizhi[i].key_wheel == val.key_wheel)
			{
				switch (val.type_wheel)
				{
					case _Ping:
					{
						canshu_Ping_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					case _Beixing:
					{
						canshu_Beixing_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					case _Yuanjiao:
					{
						canshu_Yuanjiao_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					case _Diexing:
					{
						canshu_Diexing_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					case _DXF:
					{
						canshu_DXF_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					case _Jianjiao:
					{
						canshu_Jianjiao_shalun::Jisuan_Yuanjiao(val, it.weizhi[i].distance, it.weizhi[i].cankao_flag);
					}break;
					default:
						break;
				}
				break;
			}
		}
	}
	wheel_database::edit_wheel(pos, val);
}

void wheel_dialog::edit_group(int pos, group_data val)
{
	for (size_t i = 0; i < sizeof(val.weizhi) / sizeof(val.weizhi[0]); i++)
	{
		if (val.weizhi[i].key_wheel != -1)
		{
			auto it = read_wheel(val.weizhi[i].key_wheel);
			switch (it.type_wheel)
			{
				case _Ping:
				{
					canshu_Ping_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
					
				}break;
				case _Beixing:
				{
					canshu_Beixing_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
				}break;
				case _Yuanjiao:
				{
					canshu_Yuanjiao_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
				}break;
				case _Diexing:
				{
					canshu_Diexing_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
				}break;
				case _DXF:
				{
					canshu_DXF_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
				}break;
				case _Jianjiao:
				{
					canshu_Jianjiao_shalun::Jisuan_Yuanjiao(it, val.weizhi[i].distance, val.weizhi[i].cankao_flag);
				}break;
				default:
					break;
			}
			wheel_database::edit_wheel(it.key_wheel, it);
		}
		
	}
	wheel_database::edit_group(pos, val);
}

wheel_list_data wheel_dialog::get_wheel_canshu(int pos)
{
	wheel_list_data temp;
	auto data = read_wheel(pos);
	temp.wheel_name = data.get_name();
	
	if (data.key_group == -1)
	{
		temp.falan = "--";
		temp.group_name = "--";
	}
	else
	{
		temp.falan.resize(50);
		snprintf(temp.falan.data(), 50, "%.3f", data.data[0]);
		temp.group_name = read_group(data.key_group).get_name();
	}

	temp.Zhijin_D.resize(50);
	snprintf(temp.Zhijin_D.data(), 50, "%.3f", data.data[1]);

	temp.Yuanjiao_1.resize(50);
	snprintf(temp.Yuanjiao_1.data(), 50, "%.3f", data.data[5]);

	switch (data.type_wheel)
	{
	case _Ping:
		temp.type = "平砂轮";
		temp.Yuanjiao_2.resize(50);
		snprintf(temp.Yuanjiao_2.data(), 50, "%.3f", data.data[6]);
		temp.Jiaodu.resize(50);
		snprintf(temp.Jiaodu.data(), 50, "%.3f", data.data[3]);
		break;
	case _Beixing:
		temp.type = "杯型";
		temp.Yuanjiao_2 = "--";
		temp.Jiaodu.resize(50);
		snprintf(temp.Jiaodu.data(), 50, "%.3f", data.data[4]);
		break;
	case _Yuanjiao:
		temp.type = "圆角型";
		temp.Yuanjiao_2 = "--";
		temp.Jiaodu = "--";
		break;
	case _Diexing:
		temp.type = "蝶形";
		temp.Yuanjiao_2 = "--";
		temp.Jiaodu.resize(50);
		snprintf(temp.Jiaodu.data(), 50, "%.3f", data.data[3]);
		break;
	case _DXF:
		temp.type = "型线";
		temp.Yuanjiao_2 = "--";
		temp.Jiaodu = "--";
		break;
	case _Jianjiao:
		temp.type = "尖角型";
		temp.Yuanjiao_2 = "--";
		temp.Jiaodu.resize(50);
		snprintf(temp.Jiaodu.data(), 50, "%.3f", data.data[3]);
		break;
	default:
		break;
	}
	temp.time_new = data.time_new.get_year_mon_day_hour_min_sec();
	temp.pos = data.key_wheel;
	return temp;
}

group_list_data wheel_dialog::get_group_canshu(int pos)
{
	group_list_data temp;
	auto data = read_group(pos);
	temp.pos = data.key_group;
	temp.time_new = data.time_new.get_year_mon_day_hour_min_sec();
	temp.group_name = data.get_name();
	int num = 0;
	for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
	{
		if (data.weizhi[i].key_wheel != -1)
		{
			num++;
		}
	}
	temp.n_wheel.resize(5);
	snprintf(temp.n_wheel.data(), 5, "%d", num);
	return temp;
}

group_creat_list_data wheel_dialog::get_group_creat_list_canshu(int pos)
{
	group_creat_list_data temp;
	auto data = read_wheel(pos);
	switch (data.type_wheel)
	{
	case _Ping:
		temp.wheel_type = "平砂轮";
		break;
	case _Beixing:
		temp.wheel_type = "杯型";
		temp.cankao = "--";
		break;
	case _Yuanjiao:
		temp.wheel_type = "圆角型";
		break;
	case _Diexing:
		temp.wheel_type = "蝶形";
		break;
	case _DXF:
		temp.wheel_type = "DXF型线";
		temp.cankao = "--";
		break;
	case _Jianjiao:
		temp.wheel_type = "尖角型";
		temp.cankao = "--";
		break;
	default:
		break;
	}
	temp.wheel_name = data.get_name();

	
	if (data.key_group == -1)
	{
		temp.dis = "0.000";
		if (data.type_wheel == _Ping || data.type_wheel == _Diexing || data.type_wheel == _Yuanjiao)
		{
			temp.cankao = "内侧";
		}
	}
	else
	{
		auto it = read_group(data.key_group);
		weizhi_cankao cankao_temp;
		for (size_t i = 0; i < sizeof(it.weizhi) / sizeof(it.weizhi[0]); i++)
		{
			if (it.weizhi[i].key_wheel == pos)
			{
				cankao_temp = it.weizhi[i];
			}
		}
		temp.dis.resize(50);
		snprintf(temp.dis.data(), 50, "%.3f", cankao_temp.distance);
		if (data.type_wheel == _Ping || data.type_wheel == _Diexing || data.type_wheel == _Yuanjiao)
		{
			if (cankao_temp.cankao_flag)
			{
				temp.cankao = "外侧";
			}
			else
			{
				temp.cankao = "内侧";
			}
		}
	}
	return temp;
}

void canshu_Ping_shalun::jisuan_canshu(bool flag)
{
	if (!flag)
	{
		Xiaoduan_D = Daduan_D / 2 - (Kuandu - Daduan_Yuanjiao_r) * tan(Jiaodu * M_PI / 180.0) - Daduan_Yuanjiao_r + Daduan_Yuanjiao_r / cos(Jiaodu * M_PI / 180.0);
		Xiaoduan_D = Xiaoduan_D * 2;
	}
	else
	{
		Daduan_D = Xiaoduan_D / 2 + (Kuandu - Daduan_Yuanjiao_r) * tan(Jiaodu * M_PI / 180.0) + Daduan_Yuanjiao_r - Daduan_Yuanjiao_r / cos(Jiaodu * M_PI / 180.0);
		Daduan_D = Daduan_D * 2;
	}
}

wheel_data canshu_Ping_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _Ping;
	data.daozhuang = daozhuang_flag;
	data.data[1] = Daduan_D;
	data.data[2] = Xiaoduan_D;
	data.data[3] = Jiaodu;
	data.data[5] = Daduan_Yuanjiao_r;
	data.data[6] = Xiaoduan_Yuanjiao_r;
	data.data[7] = Kuandu;
	data.Celiang_flag = Celiang_flag;
	data.set_name(name);
	return data;
}

void canshu_Ping_shalun::To_dialog_data(wheel_data data)
{
	daozhuang_flag = data.daozhuang;
	Daduan_D = data.data[1];
	Xiaoduan_D = data.data[2];
	Jiaodu = data.data[3];
	Daduan_Yuanjiao_r = data.data[5];
	Xiaoduan_Yuanjiao_r = data.data[6];
	Kuandu = data.data[7];
	Celiang_flag = data.Celiang_flag;
	name = data.get_name();
}

void canshu_Ping_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{

	double temp_r1_L = 0;
	double temp_r2_L = 0;
	double temp_r1_Ry = 0;
	double temp_r2_Ry = 0;
	double temp_r1_r = 0;
	double temp_r2_r = 0;

	if (!sl_data.daozhuang)
	{
		temp_r1_r = sl_data.data[5];
		temp_r2_r = sl_data.data[6];
		temp_r1_Ry = sl_data.data[1] / 2 - temp_r1_r;
		temp_r2_Ry = sl_data.data[2] / 2 - temp_r2_r / tan((90 + sl_data.data[3]) / 2 * M_PI / 180);
		temp_r1_L = temp_r1_r;
		temp_r2_L = sl_data.data[7] - temp_r2_r;
	}
	else
	{
		temp_r1_r = sl_data.data[6];
		temp_r2_r = sl_data.data[5];
		temp_r1_Ry = sl_data.data[2] / 2 - temp_r1_r / tan((90 + sl_data.data[3]) / 2 * M_PI / 180);
		temp_r2_Ry = sl_data.data[1] / 2 - temp_r2_r;
		temp_r1_L = temp_r1_r;
		temp_r2_L = sl_data.data[7] - temp_r2_r;
	}

	if (!cankao_flag)
	{
		temp_r1_L = temp_r1_L + distance;
		temp_r2_L = temp_r2_L + distance;
	}
	else
	{
		temp_r1_L = temp_r1_L + distance - sl_data.data[7];
		temp_r2_L = temp_r2_L + distance - sl_data.data[7];
	}

	sl_data.L0 = temp_r1_L;
	sl_data.L1 = temp_r2_L;
	sl_data.Ry0 = temp_r1_Ry;
	sl_data.Ry1 = temp_r2_Ry;

}

bool canshu_Shalun_group::add_wheel(int key_wheel, double distance, bool cankao_flag, bool one_cankao)
{
	if (wheel_buff.size() >= 9)
	{
		return 1;
	}
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		if (wheel_buff[i].key_wheel == key_wheel)
		{
			return 1;
		}
	}
	weizhi_cankao temp;
	temp.key_wheel = key_wheel;
	temp.distance = distance;
	temp.cankao_flag = cankao_flag;
	temp.one_cankao = one_cankao;
	wheel_buff.push_back(temp);
	return 0;
}

void canshu_Shalun_group::edit_a_wheel(int key_wheel, double distance, bool cankao_flag)
{
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		if (wheel_buff[i].key_wheel == key_wheel)
		{
			wheel_buff[i].cankao_flag = cankao_flag;
			if (wheel_buff[i].one_cankao)
			{
				wheel_buff[i].cankao_flag = 0;
			}
			wheel_buff[i].distance = distance;
		}
	}
}

void canshu_Shalun_group::del_wheel(int key_wheel)
{
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		if (wheel_buff[i].key_wheel == key_wheel)
		{
			wheel_buff.erase(wheel_buff.begin() + i);
			return;
		}
	}
}

bool canshu_Shalun_group::get_one_cankao_flag(int key_wheel)
{
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		if (wheel_buff[i].key_wheel == key_wheel)
		{
			return wheel_buff[i].one_cankao;
		}
	}
}

void canshu_Shalun_group::get_a_wheel_canshu(int key_wheel, double& distance, bool& cankao_flag, bool& one_cankao)
{
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		if (wheel_buff[i].key_wheel == key_wheel)
		{
			distance = wheel_buff[i].distance;
			cankao_flag = wheel_buff[i].cankao_flag;
			one_cankao = wheel_buff[i].one_cankao;
			return;
		}
	}
}

int canshu_Shalun_group::size()
{
	return wheel_buff.size();
}

void canshu_Shalun_group::Init(group_data data)
{

	for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
	{
		if (data.weizhi[i].key_wheel != -1)
		{
			wheel_buff.push_back(data.weizhi[i]);
		}
	}
	gan_D = data.gan_D;
	luomao_D = data.nut_D;
	luomao_L = data.nut_L;
	group_name = data.get_name();
}

double canshu_Shalun_group::get_gan_D()
{
	return gan_D;
}

double canshu_Shalun_group::get_luomao_D()
{
	return luomao_D;
}

double canshu_Shalun_group::get_luomao_L()
{
	return luomao_L;
}

group_data canshu_Shalun_group::To_group_data(std::string name, double gan_D, double luomao_D, double luomao_L, group_data ans)
{
	ans.time_new.set_current_time();
	ans.set_name(name);
	ans.gan_D = gan_D;
	ans.nut_D = luomao_D;
	ans.nut_L = luomao_L;
	wheel_database_namespace::weizhi_cankao temp[sizeof(ans.weizhi)/ sizeof(ans.weizhi[0])];
	for (size_t i = 0; i < wheel_buff.size(); i++)
	{
		temp[i] = wheel_buff[i];
	}
	std::copy(std::begin(temp), std::end(temp), std::begin(ans.weizhi));
	return ans;
}

void wheel_dialog_namespace::canshu_Beixing_shalun::jisuan_canshu()
{
	Neishen = Kuandu * 0.8;
}

wheel_data wheel_dialog_namespace::canshu_Beixing_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _Beixing;
	data.data[1] = Zhijing_D;
	data.data[3] = jiao_nei;
	data.data[4] = jiao_wai;
	data.data[5] = Yuanjiao_r;
	data.data[6] = Yuanjiao_r;
	data.data[7] = Kuandu;
	data.data[8] = Neishen;
	data.data[9] = Moliao;
	data.Celiang_flag = auto_Neishen;
	data.set_name(name);
	return data;
}

void wheel_dialog_namespace::canshu_Beixing_shalun::To_dialog_data(wheel_data data)
{
	Zhijing_D = data.data[1];
	jiao_nei = data.data[3];
	jiao_wai = data.data[4];
	Yuanjiao_r = data.data[5];
	Kuandu = data.data[7];
	Neishen = data.data[8];
	Moliao = data.data[9];
	auto_Neishen = data.Celiang_flag;
	name = data.get_name();
}

void wheel_dialog_namespace::canshu_Beixing_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{
	double temp_L = 0;
	double temp_Ry = 0;

	temp_Ry = sl_data.data[1] / 2 - sl_data.data[5];
	temp_L = sl_data.data[7] - sl_data.data[5];
	temp_L = temp_L + distance - sl_data.data[7];

	sl_data.L0 = temp_L;
	sl_data.L1 = temp_L;
	sl_data.Ry0 = temp_Ry;
	sl_data.Ry1 = temp_Ry;
}

wheel_data wheel_dialog_namespace::canshu_Diexing_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _Diexing;
	data.data[1] = Zhijing_D;
	data.data[3] = Jiaodu;
	data.data[5] = Yuanjiao_r;
	data.data[6] = Yuanjiao_r;
	data.data[7] = Kuandu;
	data.daozhuang = Chao_wai;
	data.set_name(name);
	return data;
}

void wheel_dialog_namespace::canshu_Diexing_shalun::To_dialog_data(wheel_data data)
{
	Zhijing_D = data.data[1];
	Jiaodu = data.data[3];
	Yuanjiao_r = data.data[5];
	Kuandu = data.data[7];
	Chao_wai = data.daozhuang;
	name = data.get_name();
}

void wheel_dialog_namespace::canshu_Diexing_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{
	double temp_L = 0;
	double temp_Ry = 0;

	temp_Ry = sl_data.data[1] / 2 - sl_data.data[5];


	if (!sl_data.daozhuang)
	{
		temp_L = sl_data.data[7] - sl_data.data[5];
	}
	else
	{
		temp_L = sl_data.data[5];
	}

	if (!cankao_flag)
	{
		temp_L = temp_L + distance;
	}
	else
	{
		temp_L = temp_L + distance - sl_data.data[7];
	}

	sl_data.L0 = temp_L;
	sl_data.L1 = temp_L;
	sl_data.Ry0 = temp_Ry;
	sl_data.Ry1 = temp_Ry;
}

wheel_data wheel_dialog_namespace::canshu_Yuanjiao_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _Yuanjiao;
	data.data[1] = Zhijing_D;
	data.data[5] = Yuanjiao_r;
	data.data[6] = Yuanjiao_r;
	data.set_name(name);
	return data;
}

void wheel_dialog_namespace::canshu_Yuanjiao_shalun::To_dialog_data(wheel_data data)
{
	Zhijing_D = data.data[1];
	Yuanjiao_r = data.data[5];
	name = data.get_name();
}

void wheel_dialog_namespace::canshu_Yuanjiao_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{
	double temp_L = 0;
	double temp_Ry = 0; 

	temp_Ry = sl_data.data[1] / 2 - sl_data.data[5];
	temp_L = sl_data.data[5];

	if (!cankao_flag)
	{
		temp_L = temp_L + distance;
	}
	else
	{
		temp_L = temp_L + distance - 2 * sl_data.data[5];
	}

	sl_data.L0 = temp_L;
	sl_data.L1 = temp_L;
	sl_data.Ry0 = temp_Ry;
	sl_data.Ry1 = temp_Ry;
}

void wheel_dialog_namespace::canshu_Jianjiao_shalun::jisuan_canshu()
{
	Jiti_jiao = Jiaodu;
	Jiti_D = Zhijing_D / 2;
	Jiti_kuan = Kuandu * 2;
}

wheel_data wheel_dialog_namespace::canshu_Jianjiao_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _Jianjiao;
	data.data[1] = Zhijing_D;
	data.data[2] = Jiti_D;
	data.data[3] = Jiaodu;
	data.data[4] = Jiti_jiao;
	data.data[5] = Yuanjiao_r;
	data.data[6] = Yuanjiao_r;
	data.data[7] = Kuandu;
	data.data[8] = Jiti_kuan;
	data.Celiang_flag = auto_Jiti;
	data.set_name(name);
	return data;
}

void wheel_dialog_namespace::canshu_Jianjiao_shalun::To_dialog_data(wheel_data data)
{
	Zhijing_D = data.data[1];
	Jiti_D = data.data[2];
	Jiaodu = data.data[3];
	Jiti_jiao = data.data[4];
	Yuanjiao_r = data.data[5];
	Kuandu = data.data[7];
	Jiti_kuan = data.data[8];
	auto_Jiti = data.Celiang_flag;
	name = data.get_name();
}

void wheel_dialog_namespace::canshu_Jianjiao_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{
	double temp_L = 0;
	double temp_Ry = 0;

	temp_Ry = sl_data.data[1] / 2 - sl_data.data[5];
	temp_L = distance;

	sl_data.L0 = temp_L;
	sl_data.L1 = temp_L;
	sl_data.Ry0 = temp_Ry;
	sl_data.Ry1 = temp_Ry;
}

wheel_data wheel_dialog_namespace::canshu_DXF_shalun::To_wheel_data(wheel_data data)
{
	data.time_new.set_current_time();
	data.type_wheel = _DXF;
	data.data[1] = Zhijing_D;
	data.data[5] = Yuanjiao_r;
	data.data[6] = Yuanjiao_r;
	data.data[7] = Zhouxiang;
	data.set_dir_dxf(dxf_dir);
	data.set_name(name);
	return data;
}

void wheel_dialog_namespace::canshu_DXF_shalun::To_dialog_data(wheel_data data)
{
	Zhijing_D = data.data[1];
	Yuanjiao_r = data.data[5];
	Zhouxiang = data.data[7];
	name = data.get_name();
	dxf_dir = data.get_dir_dxf();
}

void wheel_dialog_namespace::canshu_DXF_shalun::Jisuan_Yuanjiao(wheel_data& sl_data, double distance, bool cankao_flag)
{
	double temp_L = 0;
	double temp_Ry = 0;

	temp_Ry = sl_data.data[1] / 2 - sl_data.data[5];
	temp_L = sl_data.data[7];
	temp_L = temp_L + distance;
	
	sl_data.L0 = temp_L;
	sl_data.L1 = temp_L;
	sl_data.Ry0 = temp_Ry;
	sl_data.Ry1 = temp_Ry;
}
