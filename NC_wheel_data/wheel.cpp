#include "pch.h"
#include "wheel.h"
#include "line_manager.h"

wheel::wheel()
{
	using namespace wheel_namespace;

	wheel_namespace::wheel_type temp;
	//更新砂轮类型列表
	temp.type = "1A1";
	temp.type_id = _1A1;
	wheel_type_all.push_back(temp);
	temp.type = "1V1";
	temp.type_id = _1V1;
	wheel_type_all.push_back(temp);
	temp.type = "14E1";
	temp.type_id = _14E1;
	wheel_type_all.push_back(temp);
	temp.type = "DXF";
	temp.type_id = _DXF;
	wheel_type_all.push_back(temp);
}

void wheel::Init_Dir(std::string dir_list_wheel, std::string dir_data_wheel, std::string dir_list_group, std::string dir_data_group)
{
	wheel_database::Init_Dir(dir_list_wheel, dir_data_wheel, dir_list_group, dir_data_group);
}

wheel_namespace::wheel_list_data wheel::get_wheel_canshu(int pos)
{
	using namespace wheel_namespace;
	wheel_namespace::wheel_list_data temp;

	auto data = read_wheel(pos);

	temp.wheel_name = data.get_name();
	if (data.key_group != -1)
	{
		temp.group_name = read_group(data.key_group).get_name();
	}
	switch (data.type_wheel)
	{
	case _14E1:
	{
		temp.type = "14E1";
	}break;
	case _1A1:
	{
		temp.type = "1A1";
	}break;
	case _1V1:
	{
		temp.type = "1V1";
	}break;
	case _DXF:
	{
		temp.type = "DXF";
	}break;
	default:
		break;
	}
	
	temp.time_new = data.time_new.get_year_mon_day_hour_min_sec();
	temp.pos = data.key_wheel;
	return temp;
}

wheel_namespace::group_list_data wheel::get_group_canshu(int pos)
{
	using namespace wheel_namespace;
	wheel_namespace::group_list_data temp;

	auto data = read_group(pos);
	temp.group_name = data.get_name();
	temp.pos = data.key_group;
	temp.time_new = data.time_new.get_year_mon_day_hour_min_sec();
	for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
	{
		if (data.weizhi[i].key_wheel == -1)
		{
			continue;
		}
		temp.wheel_name[i] = read_wheel(data.weizhi[i].key_wheel).get_name();
	}
	
	return temp;
}

int wheel::get_wheel_edit_key_buff()
{
	int ans = wheel_edit_key_buff;
	wheel_edit_key_buff = -1;
	return ans;
}

void wheel::set_wheel_edit_key_buff(int pos)
{
	wheel_edit_key_buff = pos;
}

int wheel::temp_add(int pos)
{
	auto it = read_wheel(pos);
	if (it.key_group != -1)
	{
		return 2;
	}
	for (size_t i = 0; i < list_wheel_temp.size(); i++)
	{
		if (list_wheel_temp[i] == pos)
		{
			return 1;
		}
	}
	list_wheel_temp.push_back(pos);
	list_wheel_cankao_temp.emplace_back();
	list_wheel_cankao_temp.back().set_type(it.type_wheel);
	return 0;
}


void wheel::to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_14E1& val)
{
	//temp.type_wheel = wheel_namespace::_14E1;
	temp.set_name(val.name);
	temp.data[0] = val.A;
	temp.data[1] = val.D;
	temp.data[2] = val.J;
	temp.data[3] = val.r_z;
	temp.data[4] = val.T;
	temp.data[5] = val.U;
	temp.data[6] = val.V;
}

void wheel::to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_1A1& val)
{
	//temp.type_wheel = wheel_namespace::_1A1;
	temp.set_name(val.name);
	temp.data[0] = val.D;
	temp.data[1] = val.r_l;
	temp.data[2] = val.r_r;
	temp.data[3] = val.T;
}

void wheel::to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_1V1& val)
{
	//temp.type_wheel = wheel_namespace::_1V1;
	temp.set_name(val.name);
	temp.data[0] = val.D;
	temp.data[1] = val.r_l;
	temp.data[2] = val.r_r;
	temp.data[3] = val.S;
	temp.data[4] = val.T;
}

void wheel::to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_DXF& val)
{
	temp.type_wheel = wheel_namespace::_DXF;
	temp.set_name(val.name);
	temp.set_dir_dxf(val.dir);
}

int wheel::wheel_add(wheel_namespace::canshu_14E1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	int ans = add_wheel(temp);
	
	return ans;
}

int wheel::wheel_add(wheel_namespace::canshu_1A1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	int ans = add_wheel(temp);

	return ans;
}

int wheel::wheel_add(wheel_namespace::canshu_1V1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	int ans = add_wheel(temp);

	return ans;
}

int wheel::wheel_add(wheel_namespace::canshu_DXF val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	int ans = add_wheel(temp);

	return ans;
}

void wheel::wheel_edit(int pos, wheel_namespace::canshu_14E1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	edit_wheel(pos, temp);
}

void wheel::wheel_edit(int pos, wheel_namespace::canshu_1A1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	edit_wheel(pos, temp);
}

void wheel::wheel_edit(int pos, wheel_namespace::canshu_1V1 val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	edit_wheel(pos, temp);
}

void wheel::wheel_edit(int pos, wheel_namespace::canshu_DXF val)
{
	wheel_database_namespace::wheel_data temp;

	to_wheel_data(temp, val);

	edit_wheel(pos, temp);
}

void wheel::wheel_out(wheel_namespace::canshu_14E1& val, int _pos)
{
	int pos = wheel_edit_key_buff;
	if (_pos != -1)
	{
		pos = _pos;
	}
	if (pos == -1)
	{

	}
	else
	{
		auto temp_data = read_wheel(pos);

		val.name = temp_data.get_name();
		val.A = temp_data.data[0];
		val.D = temp_data.data[1];
		val.J = temp_data.data[2];
		val.r_z = temp_data.data[3];
		val.T = temp_data.data[4];
		val.U = temp_data.data[5];
		val.V = temp_data.data[6];
	}
}

void wheel::wheel_out(wheel_namespace::canshu_1A1& val, int _pos)
{
	int pos = wheel_edit_key_buff;
	if (_pos != -1)
	{
		pos = _pos;
	}
	if (pos == -1)
	{

	}
	else
	{
		auto temp_data = read_wheel(pos);

		val.name = temp_data.get_name();
		val.D = temp_data.data[0];
		val.r_l = temp_data.data[1];
		val.r_r = temp_data.data[2];
		val.T = temp_data.data[3];
	}
}

void wheel::wheel_out(wheel_namespace::canshu_1V1& val, int _pos)
{
	int pos = wheel_edit_key_buff;
	if (_pos != -1)
	{
		pos = _pos;
	}
	if (pos == -1)
	{

	}
	else
	{
		auto temp_data = read_wheel(pos);

		val.name = temp_data.get_name();
		val.D = temp_data.data[0];
		val.r_l = temp_data.data[1];
		val.r_r = temp_data.data[2];
		val.S = temp_data.data[3];
		val.T = temp_data.data[4];
	}
}

void wheel::wheel_out(wheel_namespace::canshu_DXF& val, int _pos)
{
	int pos = wheel_edit_key_buff;
	if (_pos != -1)
	{
		pos = _pos;
	}
	if (pos == -1)
	{

	}
	else
	{
		auto temp_data = read_wheel(pos);

		val.name = temp_data.get_name();
		val.dir = temp_data.get_dir_dxf();
	}
}


bool wheel::wheel_delete(int pos)
{
	for (size_t i = 0; i < list_wheel_temp.size(); i++)
	{
		if (list_wheel_temp[i] == pos)
		{
			return 1;
		}
	}
	auto temp = read_wheel(pos);

	if (temp.key_group != -1)
	{
		return 1;
	}
	delete_wheel(pos);
	return 0;
}

int wheel::get_wheel_type(int pos)
{
	return read_wheel(pos).type_wheel;
}

int wheel::group_add(wheel_namespace::canshu_Group val)
{
	wheel_database_namespace::group_data temp;
	to_group_data(temp, val);
	int pos = add_group(temp);
	return pos;
}

void wheel::group_edit(int pos, wheel_namespace::canshu_Group val)
{
	wheel_database_namespace::group_data temp;

	to_group_data(temp, val);

	edit_group(pos, temp);
}

bool wheel::group_delete(int pos)
{
	delete_group(pos);
	return 0;
}

void wheel::set_group_edit_key_buff(int pos)
{
	group_edit_key_buff = pos;
}

int wheel::get_group_edit_key_buff()
{
	int ans = group_edit_key_buff;
	group_edit_key_buff = -1;
	return ans;
}

void wheel::group_out(wheel_namespace::canshu_Group& val)
{
	int pos = group_edit_key_buff;

	if (pos != -1)
	{

		auto it = read_group(pos);
		
		val.D0 = it.gan[0];
		val.D1 = it.gan[1];
		val.D2 = it.gan[2];
		val.L0 = it.gan[3];
		val.L1 = it.gan[4];
		val.L2 = it.gan[5];

		val.D3 = it.nut[0];
		val.L3 = it.nut[1];

		if (list_wheel_temp.size() == 0)
		{
			for (size_t i = 0; i < sizeof(it.weizhi) / sizeof(it.weizhi[0]); i++)
			{
				if (it.weizhi[i].key_wheel != -1)
				{
					list_wheel_temp.push_back(it.weizhi[i].key_wheel);
					list_wheel_cankao_temp.emplace_back();
				}
			}

			for (size_t i = 0; i < list_wheel_temp.size(); i++)
			{
				list_wheel_cankao_temp[i].set_cankao(it.weizhi[i].cankao_flag);
				list_wheel_cankao_temp[i].set_daozhuang(it.weizhi[i].daozhuang_flag);
				list_wheel_cankao_temp[i].set_distance(it.weizhi[i].distance);
				list_wheel_cankao_temp[i].set_r(it.weizhi[i].cankao_r);
				list_wheel_cankao_temp[i].set_d(it.weizhi[i].cankao_d);
				list_wheel_cankao_temp[i].set_l(it.weizhi[i].cankao_l);
				int type = get_wheel_type(it.weizhi[i].key_wheel);
				list_wheel_cankao_temp[i].set_type(type);
				list_wheel_cankao_temp[i].set_yuanjiao_flag(it.weizhi[i].yuanjiao_flag);
			}
		}
		

		val.name = it.get_name();
	}
}

void wheel::to_group_data(wheel_database_namespace::group_data& temp, wheel_namespace::canshu_Group& val)
{
	temp.gan[0] = val.D0;
	temp.gan[1] = val.D1;
	temp.gan[2] = val.D2;
	temp.gan[3] = val.L0;
	temp.gan[4] = val.L1;
	temp.gan[5] = val.L2;

	temp.nut[0] = val.D3;
	temp.nut[1] = val.L3;

	for (size_t i = 0; i < val.list_wheel_temp.size(); i++)
	{
		temp.weizhi[i].cankao_flag = val.list_wheel_cankao_temp[i].is_cankao_Left();
		temp.weizhi[i].daozhuang_flag = val.list_wheel_cankao_temp[i].is_daozhuang();
		temp.weizhi[i].distance = val.list_wheel_cankao_temp[i].get_distance();
		temp.weizhi[i].cankao_r = val.list_wheel_cankao_temp[i].get_r();
		temp.weizhi[i].cankao_d = val.list_wheel_cankao_temp[i].get_d();
		temp.weizhi[i].cankao_l = val.list_wheel_cankao_temp[i].get_l();
		temp.weizhi[i].yuanjiao_flag = val.list_wheel_cankao_temp[i].get_yuanjiao_flag();
		temp.weizhi[i].key_wheel = val.list_wheel_temp[i];
	}
	temp.set_name(val.name);
}

void wheel::clear_list_wheel_temp()
{
	list_wheel_temp.clear();
}

void wheel::clear_list_wheel_cankao_temp()
{
	list_wheel_cankao_temp.clear();
}

void wheel::jisuan_d_r_l(int n)
{
	using namespace wheel_namespace;
	auto data = read_wheel(list_wheel_temp[n]);
	switch (data.type_wheel)
	{
	case _DXF:
	{

	}break;
	case _1A1:
	{
		canshu_1A1 temp;
		d_r_l_1A1(temp, n, list_wheel_temp[n]);
	}break;
	case _1V1:
	{
		canshu_1V1 temp;
		d_r_l_1V1(temp, n, list_wheel_temp[n]);
	}break;
	case _14E1:
	{
		canshu_14E1 temp;
		d_r_l_14E1(temp, n, list_wheel_temp[n]);
	}break;
	default:
		break;
	}

}

void wheel::set_bit(unsigned char& val, int bit, bool in)
{
	unsigned char temp = 0;
	if (in)
	{
		temp = 1;
		temp = temp << bit;
		val = val | temp;
	}
	else
	{
		temp = 1;
		temp = temp << bit;
		temp = ~temp;
		val = val & temp;
	}
}

void wheel::d_r_l_1A1(wheel_namespace::canshu_1A1 data, int n, int pos)
{
	wheel_out(data, pos);
	double distance = list_wheel_cankao_temp[n].get_distance();
	unsigned char flag = 0;
	set_bit(flag, 2, list_wheel_cankao_temp[n].is_cankao_Left());
	set_bit(flag, 1, list_wheel_cankao_temp[n].get_yuanjiao_flag() - 1);
	set_bit(flag, 0, list_wheel_cankao_temp[n].is_daozhuang());
	switch (flag)
	{
	//右 l 正
	case 0:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.T + data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_l);
	}break;
	//右 l 反
	case 1:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_l);
	}break;
	//右 r 正
	case 2:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//右 r 反
	case 3:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.T + data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//左 l 正
	case 4:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_l);
	}break;
	//左 l 反
	case 5:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.T - data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_l);
	}break;
	//左 r 正
	case 6:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.T - data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//左 r 反
	case 7:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	default:
		break;
	}
}

void wheel::d_r_l_1V1(wheel_namespace::canshu_1V1 data, int n, int pos)
{
	wheel_out(data, pos);
	double distance = list_wheel_cankao_temp[n].get_distance();
	unsigned char flag = 0;

	double d_l = ((data.D / 2 - data.r_r) - (data.T - 2 * data.r_r) / tan(data.S * datum::pi / 180.0))
		+ (data.r_r - data.r_l) * tan((data.S / 2) * datum::pi / 180.0);

	set_bit(flag, 2, list_wheel_cankao_temp[n].is_cankao_Left());
	set_bit(flag, 1, list_wheel_cankao_temp[n].get_yuanjiao_flag() - 1);
	set_bit(flag, 0, list_wheel_cankao_temp[n].is_daozhuang());


	switch (flag)
	{
		//右 l 正
	case 0:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.T + data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(d_l);
	}break;
	//右 l 反
	case 1:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(d_l);
	}break;
	//右 r 正
	case 2:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//右 r 反
	case 3:
	{
		list_wheel_cankao_temp[n].set_l(distance - data.T + data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//左 l 正
	case 4:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(d_l);
	}break;
	//左 l 反
	case 5:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.T - data.r_l);
		list_wheel_cankao_temp[n].set_r(data.r_l);
		list_wheel_cankao_temp[n].set_d(d_l);
	}break;
	//左 r 正
	case 6:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.T - data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	//左 r 反
	case 7:
	{
		list_wheel_cankao_temp[n].set_l(distance + data.r_r);
		list_wheel_cankao_temp[n].set_r(data.r_r);
		list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_r);
	}break;
	default:
		break;
	}
}

void wheel::d_r_l_14E1(wheel_namespace::canshu_14E1 data, int n, int pos)
{
	wheel_out(data, pos);
	double distance = list_wheel_cankao_temp[n].get_distance();

	if (list_wheel_cankao_temp[n].is_cankao_Left())
	{
		list_wheel_cankao_temp[n].set_l(distance + data.T / 2);
	}
	else
	{
		list_wheel_cankao_temp[n].set_l(distance - data.T / 2);
	}
	list_wheel_cankao_temp[n].set_r(data.r_z);
	list_wheel_cankao_temp[n].set_d(data.D / 2 - data.r_z);
}


wheel_group* wheel::get_a_group_ptr(int group_key)
{
	using namespace wheel_namespace;
	wheel_group* ptr = new wheel_group;
	auto data = read_group(group_key);
	ptr->set_wheel_pole(data.gan[0], data.gan[1], data.gan[2], data.gan[3], data.gan[4], data.gan[5]);
	ptr->set_nut(data.nut[1], data.nut[0]);
	for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
	{
		if (data.weizhi[i].key_wheel != -1)
		{
			auto shalun = read_wheel(data.weizhi[i].key_wheel);
			switch (shalun.type_wheel)
			{
			case _14E1:
			{
				wheel_14E1 sl;
				sl.set_wheel(shalun);
				ptr->add_wheel(sl, data.weizhi[i].daozhuang_flag, data.weizhi[i].cankao_flag, data.weizhi[i].distance);
			}break;
			case _1A1:
			{
				wheel_1A1 sl;
				sl.set_wheel(shalun);
				ptr->add_wheel(sl, data.weizhi[i].daozhuang_flag, data.weizhi[i].cankao_flag, data.weizhi[i].distance);
			}break;
			case _1V1:
			{
				wheel_1V1 sl;
				sl.set_wheel(shalun);
				ptr->add_wheel(sl, data.weizhi[i].daozhuang_flag, data.weizhi[i].cankao_flag, data.weizhi[i].distance);
			}break;
			case _DXF:
			{
				wheel_dxf sl;
				sl.set_wheel(shalun);
				ptr->add_wheel(sl, data.weizhi[i].daozhuang_flag, data.weizhi[i].cankao_flag, data.weizhi[i].distance);
			}break;
			default:
				break;
			}
		}
	}


	return ptr;
}

wheel_group* wheel::get_a_group_ptr_by_wheel(int wheel_key)
{
	wheel_group* ptr = nullptr;
	auto data = read_wheel(wheel_key);
	if (data.key_group == -1)
	{
		return ptr;
	}
	ptr = get_a_group_ptr(data.key_group);
	return ptr;
}

int wheel::get_group_key_by_wheel(int wheel_key)
{
	auto data = read_wheel(wheel_key);
	return data.key_group;
}

void wheel::get_d_r_l(int wheel_key, bool flag, double& d, double& r, double& l)
{
	using namespace wheel_namespace;
	auto data_wheel = read_wheel(wheel_key);
	auto data_group = read_group(data_wheel.key_group);
	for (size_t i = 0; i < sizeof(data_group.weizhi) / sizeof(data_group.weizhi[0]); i++)
	{
		if (data_group.weizhi[i].key_wheel == wheel_key)
		{
			list_wheel_temp.clear();
			list_wheel_temp.push_back(wheel_key);
			list_wheel_cankao_temp.clear();
			list_wheel_cankao_temp.emplace_back();
			list_wheel_cankao_temp[0].set_cankao(data_group.weizhi[i].cankao_flag);
			list_wheel_cankao_temp[0].set_daozhuang(data_group.weizhi[i].daozhuang_flag);
			list_wheel_cankao_temp[0].set_distance(data_group.weizhi[i].distance);
			if (data_group.weizhi[i].daozhuang_flag)
			{
				if (flag)
				{
					list_wheel_cankao_temp[0].set_yuanjiao_flag(2);
				}
				else
				{
					list_wheel_cankao_temp[0].set_yuanjiao_flag(1);
				}
			}
			else
			{
				if (flag)
				{
					list_wheel_cankao_temp[0].set_yuanjiao_flag(1);
				}
				else
				{
					list_wheel_cankao_temp[0].set_yuanjiao_flag(2);
				}
			}
			jisuan_d_r_l(0);
			d = list_wheel_cankao_temp[0].get_d() * 2;
			l = list_wheel_cankao_temp[0].get_l();
			r = list_wheel_cankao_temp[0].get_r();
			list_wheel_temp.clear();
			list_wheel_cankao_temp.clear();
		}
	}
}

mat wheel::get_2D_wheel_outline(int wheel_key)
{
	using namespace wheel_namespace;
	auto data = read_wheel(wheel_key);
	if (data.key_group == -1)
	{
		//错误：砂轮不在砂轮组上
		std::terminate();
	}
	auto group_data = read_group(data.key_group);
	
	bool dz_flag = 0;
	bool ck_flag = 0;
	double ck_d = 0;

	for (size_t i = 0; i < 3; i++)
	{
		if (group_data.weizhi[i].key_wheel == wheel_key)
		{
			dz_flag = group_data.weizhi[i].daozhuang_flag;
			ck_flag = group_data.weizhi[i].cankao_flag;
			ck_d = group_data.weizhi[i].distance;
			break;
		}
		else
		{
			if (i == 2)
			{
				//错误：砂轮不在当前砂轮组上，数据库损坏导致
				std::terminate();
			}
		}
	}
	wheel_namespace::port_getData ls_getData;
	switch (data.type_wheel)
	{
	case _14E1:
	{
		wheel_14E1 sl;
		sl.set_wheel(data);
		ls_getData = sl;
		//return sl.get_outline();
	}break;
	case _1A1:
	{
		wheel_1A1 sl;
		sl.set_wheel(data);
		ls_getData = sl;
		//return sl.get_outline();
	}break;
	case _1V1:
	{
		wheel_1V1 sl;
		sl.set_wheel(data);
		ls_getData = sl;
		//return sl.get_outline();
	}break;
	case _DXF:
	{
		wheel_dxf sl;
		sl.set_wheel(data);
		ls_getData = sl;
		//return sl.get_outline();
	}break;
	default:
		break;
	}
	wheel_group temp;

	temp.set_wheel_pole(group_data.gan[0], group_data.gan[1], group_data.gan[2], group_data.gan[3], group_data.gan[4], group_data.gan[5]);
	temp.set_nut(group_data.nut[1], group_data.nut[0]);
	temp.add_wheel(ls_getData, dz_flag, ck_flag, ck_d);
	mat ans;
	temp.get_wheel_outline(ans);

	return ans;
}

double wheel::get_wheel_T(int wheel_key)
{
	using namespace wheel_namespace;
	auto data = read_wheel(wheel_key);
	switch (data.type_wheel)
	{
	case _14E1:
	{
		canshu_14E1 temp;
		wheel_out(temp, wheel_key);
		return temp.T;
	}break;
	case _1V1:
	{
		canshu_1V1 temp;
		wheel_out(temp, wheel_key);
		return temp.T;
	}break;
	case _1A1:
	{
		canshu_1A1 temp;
		wheel_out(temp, wheel_key);
		return temp.T;
	}break;
	case _DXF:
	{
		return 0;
	}break;
	default:
		break;
	}
	return 0;
}

std::vector<int> wheel::get_a_group_all_wheel_key(int group_key)
{
	auto data = read_group(group_key);
	std::vector<int> ans;
	for (size_t i = 0; i < sizeof(data.weizhi) / sizeof(data.weizhi[0]); i++)
	{
		if (data.weizhi[0].key_wheel != -1)
		{
			ans.push_back(data.weizhi[0].key_wheel);
		}
	}
	return ans;
}

namespace wheel_namespace
{
	bool group_wheel_cankao::is_daozhuang()
	{
		return _is_daozhuang;
	}
	bool group_wheel_cankao::is_cankao_Left()
	{
		return _is_cankao_Left;
	}
	double group_wheel_cankao::get_distance()
	{
		return distance;
	}
	void group_wheel_cankao::set_daozhuang(bool val)
	{
		_is_daozhuang = val;
	}

	void group_wheel_cankao::set_cankao(bool val)
	{
		_is_cankao_Left = val;
	}

	void group_wheel_cankao::set_distance(double val)
	{
		distance = val;
	}

	double group_wheel_cankao::get_r()
	{
		return r;
	}

	double group_wheel_cankao::get_d()
	{
		return d;
	}

	double group_wheel_cankao::get_l()
	{
		return l;
	}

	void group_wheel_cankao::set_r(double val)
	{
		r = val;
	}

	void group_wheel_cankao::set_d(double val)
	{
		d = val;
	}

	void group_wheel_cankao::set_l(double val)
	{
		l = val;
	}
	double group_wheel_cankao::get_type()
	{
		return type;
	}
	void group_wheel_cankao::set_type(double val)
	{
		type = val;
	}

	int group_wheel_cankao::get_yuanjiao_flag()
	{
		return yuanjiao_flag;
	}

	void group_wheel_cankao::set_yuanjiao_flag(int val)
	{
		yuanjiao_flag = val;
	}

}

namespace wheel_namespace
{

	vec arc::rot_angle(double err, double r, double start, double end)
	{
		double d = 2.0 * acos((r - err) / r) * (180.0 / datum::pi);
		vec temp = linspace(start, end, ceil(360.0 / d) + 1);
		return temp;
	}

	vec_point arc::discrete_arc(vec c, double err, double r, double start, double end)
	{
		wheel_namespace::vec_point temp;
		vec r_normal = { r, 0.0, 0.0 };
		vec angle_temp = rot_angle(err, r, start, end);
		for (size_t i = 0; i < angle_temp.size(); i++)
		{
			temp.push_back(c + (tcRotZ(3, angle_temp[i]) * r_normal));
		}
		return temp;
	}
}

namespace wheel_namespace
{
	RotateOutline::RotateOutline() :
		flag(1)
	{
	}

	void RotateOutline::get_outline(std::vector<vec>& val)
	{
		val.reserve(outline.size());
		for (size_t i = 0; i < outline.size(); i++)
		{
			val.push_back(outline[i]);
		}
	}

	void RotateOutline::get_outline(mat& val)
	{
		val.clear();
		val.set_size(3, outline.size());

		for (size_t i = 0; i < outline.size(); i++)
		{
			val.col(i) = outline[i];
		}
	}

	mat RotateOutline::get_outline()
	{
		mat val;
		val.set_size(3, outline.size());
		for (size_t i = 0; i < outline.size(); i++)
		{
			val.col(i) = outline[i];
		}
		return val;
	}

	void RotateOutline::get_outline(vec_point& val)
	{

		val = outline;
	}

	void RotateOutline::turn_over()
	{
		flag = !flag;
		mat temp = tcRotY(3, 180.0);
		outline.transformation(temp);
		outline.resort();
	}

}

namespace wheel_namespace
{
	vec_point::vec_point() :
		size_n(0),
		show_data(3, 200)
	{
	}

	void vec_point::push_back(const vec& val)
	{
		if (show_data.n_cols == size_n)
		{
			//mat temp();
			show_data.insert_cols(show_data.n_cols, zeros<mat>(3, 100));
		}
		show_data.col(size_n) = val;
		size_n++;
	}

	unsigned int vec_point::size()
	{
		return size_n;
	}

	void vec_point::clear()
	{
		size_n = 0;
		show_data.clear();
		show_data = zeros<mat>(3, 200);
	}

	void vec_point::insert_back(std::vector<vec>& val)
	{
		for (size_t i = 0; i < val.size(); i++)
		{
			push_back(val[i]);
		}
	}
	
	void vec_point::insert_back(vec_point& val)
	{
		for (size_t i = 0; i < val.size(); i++)
		{
			push_back(val[i]);
		}
	}

	vec_point& vec_point::transformation(mat& val)
	{
		show_data = val * show_data;
		return *this;
	}
	
	vec vec_point::operator[](unsigned int index)
	{
		if (index > size_n - 1)
		{
			//索引越界异常
			terminate();
		}
		return show_data.col(index);
	}

	void vec_point::resort()
	{
		mat temp;
		temp.set_size(3, size_n);
		for (size_t i = 0; i < size_n; i++)
		{
			temp.col(i) = show_data.col(size_n - i - 1);
		}
		for (size_t i = 0; i < size_n; i++)
		{
			show_data.col(i) = temp.col(i);
		}
	}
}

namespace wheel_namespace
{
	double wheel_output_base::get_D(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_T(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_R_l(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_R_r(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_R_acc(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_S(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_J(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_U(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_R_z(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_V(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	double wheel_output_base::get_a(bool& is_wrong)
	{
		is_wrong = 1;
		return -1;
	}

	std::string wheel_output_base::get_dir(bool& is_wrong)
	{
		is_wrong = 1;
		return std::string();
	}
	bool wheel_output_base::set_D(double val)
	{
		return true;
	}
	bool wheel_output_base::set_T(double val)
	{
		return true;
	}
	bool wheel_output_base::set_R_l(double val)
	{
		return true;
	}
	bool wheel_output_base::set_R_r(double val)
	{
		return true;
	}
	bool wheel_output_base::set_R_acc(double val)
	{
		return true;
	}
	bool wheel_output_base::set_S(double val)
	{
		return true;
	}
	bool wheel_output_base::set_J(double val)
	{
		return true;
	}
	bool wheel_output_base::set_U(double val)
	{
		return true;
	}
	bool wheel_output_base::set_R_z(double val)
	{
		return true;
	}
	bool wheel_output_base::set_V(double val)
	{
		return true;
	}
	bool wheel_output_base::set_a(double val)
	{
		return true;
	}
	bool wheel_output_base::set_dir(std::string val)
	{
		return true;
	}
	wheel_output_base::~wheel_output_base()
	{

	}
}

#pragma region wheel_14E1

wheel_14E1::wheel_14E1() :
	D(10.0),
	J(5.0),
	T(2.0),
	U(1.0),
	r_z(0.1),
	V(45.0),
	a(45.0),
	r_acc(0.01)
{
	renew_outline();
}

void wheel_14E1::set_wheel(double _D, double _J, double _T, double _U, double _r_z, double _V, double _a, double _r_acc)
{
	D = _D;
	J = _J;
	T = _T;
	U = _U;
	r_z = _r_z;
	V = _V;
	a = _a;
	r_acc = _r_acc;
	renew_outline();
}

void wheel_14E1::set_wheel(wheel_database_namespace::wheel_data data, bool _flag, double _r_acc)
{
	
	a = data.data[0];
	D = data.data[1];
	J = data.data[2];
	r_z = data.data[3];
	T = data.data[4];
	U = data.data[5];
	V = data.data[6];

	r_acc = _flag;
	flag = _r_acc;
}

double wheel_14E1::get_T()
{
	return T;
}

double wheel_14E1::get_D(bool& is_wrong)
{
	is_wrong = 0;
	return D;
}

double wheel_14E1::get_J(bool& is_wrong)
{
	is_wrong = 0;
	return J;
}

double wheel_14E1::get_T(bool& is_wrong)
{
	is_wrong = 0;
	return T;
}

double wheel_14E1::get_U(bool& is_wrong)
{
	is_wrong = 0;
	return U;
}

double wheel_14E1::get_R_z(bool& is_wrong)
{
	is_wrong = 0;
	return r_z;
}

double wheel_14E1::get_V(bool& is_wrong)
{
	is_wrong = 0;
	return V;
}

double wheel_14E1::get_a(bool& is_wrong)
{
	is_wrong = 0;
	return a;
}

double wheel_14E1::get_R_acc(bool& is_wrong)
{
	is_wrong = 0;
	return r_acc;
}

bool wheel_14E1::set_D(double val)
{
	D = val;
	return false;
}

bool wheel_14E1::set_J(double val)
{
	J = val;
	return false;
}

bool wheel_14E1::set_T(double val)
{
	T = val;
	return false;
}

bool wheel_14E1::set_U(double val)
{
	U = val;
	return false;
}

bool wheel_14E1::set_R_z(double val)
{
	r_z = val;
	return false;
}

bool wheel_14E1::set_V(double val)
{
	V = val;
	return false;
}

bool wheel_14E1::set_a(double val)
{
	a = val;
	return false;
}

bool wheel_14E1::set_R_acc(double val)
{
	r_acc = val;
	return false;
}

void wheel_14E1::renew_outline()
{
	wheel_namespace::vec_point temp;

	outline.clear();

	outline.push_back(vec({ 0.0, 0.0, 0.0 }));
	outline.push_back(vec({ 0.0, J / 2.0, 0.0 }));

	double T_U_2 = (T - U) / 2.0;
	double T_U_y = T_U_2 / tan(a * datum::pi / 180.0);
	outline.push_back(vec({ T_U_2, (J / 2.0) + T_U_y, 0.0 }));

	vec c5 = { T / 2.0, D / 2.0 - r_z, 0.0 };
	temp = discrete_arc(c5, r_acc, r_z, 180.0 - (V / 2.0), 90.0 - ((180.0 - V) / 2.0));

	double temp_a = (U / 2) - (r_z / cos((V / 2) * datum::pi / 180.0));
	double temp_b = temp_a / tan((V / 2) * datum::pi / 180.0);

	outline.push_back(vec({ T_U_2, (D / 2.0 - r_z) - temp_b, 0.0 }));

	outline.insert_back(temp);

	outline.push_back(vec({ T_U_2 + U, (D / 2.0 - r_z) - temp_b, 0.0 }));
	outline.push_back(vec({ T_U_2 + U, (J / 2.0) + T_U_y, 0.0 }));

	outline.push_back(vec({ T, J / 2.0, 0.0 }));

	outline.push_back(vec({ T, 0.0, 0.0 }));
	if (!flag)
	{
		turn_over();
		flag = 0;
	}
}

#pragma endregion

#pragma region wheel_1A1

wheel_1A1::wheel_1A1() :
	D(10.0),
	T(4.0),
	r_l(0.1),
	r_r(0.1),
	r_acc(0.01)
{
	renew_outline();
}

void wheel_1A1::set_wheel(double _D, double _T, double _r_l, double _r_r, double _r_acc)
{
	D = _D;
	T = _T;
	r_l = _r_l;
	r_r = _r_r;
	r_acc = _r_acc;
	renew_outline();
}

void wheel_1A1::set_wheel(wheel_database_namespace::wheel_data data, bool _flag, double _r_acc)
{
	
	D = data.data[0];
	r_l = data.data[1];
	r_r = data.data[2];
	T = data.data[3];

	r_acc = _r_acc;
	flag = _flag;

	renew_outline();
}

double wheel_1A1::get_T()
{
	return T;
}

double wheel_1A1::get_D(bool& is_wrong)
{
	is_wrong = 0;
	return D;
}

double wheel_1A1::get_T(bool& is_wrong)
{
	is_wrong = 0;
	return T;
}

double wheel_1A1::get_R_l(bool& is_wrong)
{
	is_wrong = 0;
	return r_l;
}

double wheel_1A1::get_R_r(bool& is_wrong)
{
	is_wrong = 0;
	return r_r;
}

double wheel_1A1::get_R_acc(bool& is_wrong)
{
	is_wrong = 0;
	return r_acc;
}

bool wheel_1A1::set_D(double val)
{
	D = val;
	return false;
}

bool wheel_1A1::set_T(double val)
{
	T = val;
	return false;
}

bool wheel_1A1::set_R_l(double val)
{
	r_l = val;
	return false;
}

bool wheel_1A1::set_R_r(double val)
{
	r_r = val;
	return false;
}

bool wheel_1A1::set_R_acc(double val)
{
	r_acc = val;
	return false;
}

void wheel_1A1::renew_outline()
{
	wheel_namespace::vec_point temp;

	outline.clear();
	outline.push_back(vec({ 0.0, 0.0, 0.0 }));

	vec c0 = { 0.0 + r_l, D / 2.0 - r_l, 0.0 };
	vec c1 = { T - r_r, D / 2.0 - r_r, 0.0 };

	temp = discrete_arc(c0, r_acc, r_l, 180.0, 90.0);
	outline.insert_back(temp);

	temp = discrete_arc(c1, r_acc, r_r, 90.0, 0.0);
	outline.insert_back(temp);

	outline.push_back(vec({ T, 0.0, 0.0 }));
	if (!flag)
	{
		turn_over();
		flag = 0;
	}
}

#pragma endregion

#pragma region wheel_1V1

wheel_1V1::wheel_1V1() :
	D(10.0),
	T(4.0),
	r_l(0.1),
	r_r(0.1),
	S(45.0),
	r_acc(0.01)
{
	renew_outline();
}

void wheel_1V1::set_wheel(double _D, double _T, double _r_l, double _r_r, double _S, double _r_acc)
{
	D = _D;
	T = _T;
	r_l = _r_l;
	r_r = _r_r;
	S = _S;
	r_acc = _r_acc;
	renew_outline();
}

void wheel_1V1::set_wheel(wheel_database_namespace::wheel_data data, bool _flag, double _r_acc)
{
	D = data.data[0];
	r_l = data.data[1];
	r_r = data.data[2];
	S = data.data[3];
	T = data.data[4];

	r_acc = _r_acc;
	flag = _flag;

	renew_outline();
}

double wheel_1V1::get_T()
{
	return T;
}

double wheel_1V1::get_D(bool& is_wrong)
{
	is_wrong = 0;
	return D;
}

double wheel_1V1::get_T(bool& is_wrong)
{
	is_wrong = 0;
	return T;
}

double wheel_1V1::get_R_l(bool& is_wrong)
{
	is_wrong = 0;
	return r_l;
}

double wheel_1V1::get_R_r(bool& is_wrong)
{
	is_wrong = 0;
	return r_r;
}

double wheel_1V1::get_R_acc(bool& is_wrong)
{
	is_wrong = 0;
	return r_acc;
}

double wheel_1V1::get_S(bool& is_wrong)
{
	is_wrong = 0;
	return S;
}

bool wheel_1V1::set_D(double val)
{
	D = val;
	return false;
}

bool wheel_1V1::set_T(double val)
{
	T = val;
	return false;
}

bool wheel_1V1::set_R_l(double val)
{
	r_l = val;
	return false;
}

bool wheel_1V1::set_R_r(double val)
{
	r_r = val;
	return false;
}

bool wheel_1V1::set_R_acc(double val)
{
	r_acc = val;
	return false;
}

bool wheel_1V1::set_S(double val)
{
	S = val;
	return false;
}

void wheel_1V1::renew_outline()
{
	wheel_namespace::vec_point temp;

	outline.clear();
	outline.push_back(vec({ 0.0, 0.0, 0.0 }));

	vec c0 = { 0.0 + r_l,
		((D / 2.0 - r_r) - (T - 2.0 * r_r) / tan(S * datum::pi / 180.0))
		+ (r_r - r_l) * tan((S / 2) * datum::pi / 180.0),
		0.0 };
	vec c1 = { T - r_r, D / 2.0 - r_r , 0.0 };

	temp = discrete_arc(c0, r_acc, r_l, 180.0, 180.0 - S);
	outline.insert_back(temp);

	temp = discrete_arc(c1, r_acc, r_r, 180.0 - S, 0.0);
	outline.insert_back(temp);

	outline.push_back(vec({ T, 0.0, 0.0 }));
	if (!flag)
	{
		turn_over();
		flag = 0;
	}
}

#pragma endregion

#pragma region wheel_DXF

wheel_dxf::wheel_dxf() :
	r_acc(0.01),
	houdu(0.0)
{

}

void wheel_dxf::set_wheel(std::string filename, double _r_acc)
{
	filename_dir = filename;
	r_acc = _r_acc;
	renew_outline();
}

void wheel_dxf::set_wheel(wheel_database_namespace::wheel_data data, bool _flag, double _r_acc)
{
	r_acc = _r_acc;
	flag = _flag;
	filename_dir = data.get_dir_dxf();
	renew_outline();
}

double wheel_dxf::get_T()
{
	return houdu;
}

double wheel_dxf::get_T(bool& is_wrong)
{
	is_wrong = 0;
	return houdu;
}

double wheel_dxf::get_R_acc(bool& is_wrong)
{
	is_wrong = 0;
	return r_acc;
}

std::string wheel_dxf::get_dir(bool& is_wrong)
{
	is_wrong = 0;
	return filename_dir;
}

bool wheel_dxf::set_R_acc(double val)
{
	r_acc = val;
	return false;
}

bool wheel_dxf::set_dir(std::string val)
{
	filename_dir = val;
	return false;
}

void wheel_dxf::renew_outline()
{
	double t0 = DBL_MAX;
	double t1 = DBL_MIN;
	mat temp;
	line_manager line(filename_dir);
	line.get_curvature_point(r_acc, temp);
	outline.clear();
	for (size_t i = 0; i < temp.n_cols; i++)
	{
		outline.push_back(temp.col(i).rows(3, 5));
		if (outline[i][0] < t0)
		{
			t0 = outline[i][0];
		}
		if (outline[i][0] > t1)
		{
			t1 = outline[i][0];
		}
	}
	houdu = t1 - t0;
	if (!flag)
	{
		turn_over();
		flag = 0;
	}
}
#pragma endregion

#pragma region wheel_Pole

wheel_pole::wheel_pole() :
	D0(70.0),
	D1(50.0),
	D2(40.0),
	L0(20.0),
	L1(100.0),
	L2(30.0)
{
	renew_outline();
}

void wheel_pole::set_pole(double _D0, double _D1, double _D2, double _L0, double _L1, double _L2)
{
	D0 = _D0;
	D1 = _D1;
	D2 = _D2;
	L0 = _L0;
	L1 = _L1;
	L2 = _L2;
	renew_outline();
}

void wheel_pole::set_pole(wheel_database_namespace::group_data data)
{
	D0 = data.gan[0];
	D1 = data.gan[1];
	D2 = data.gan[2];
	L0 = data.gan[3];
	L1 = data.gan[4];
	L2 = data.gan[5];
	renew_outline();
}

void wheel_pole::renew_outline()
{
	outline.clear();
	outline.push_back(vec({ 0.0, 0.0, 0.0 }));
	outline.push_back(vec({ 0.0, D0 / 2.0, 0.0 }));

	outline.push_back(vec({ L0, D0 / 2.0, 0.0 }));
	outline.push_back(vec({ L0, D1 / 2.0, 0.0 }));

	outline.push_back(vec({ L1, D1 / 2.0, 0.0 }));
	outline.push_back(vec({ L1, D2 / 2.0, 0.0 }));

	outline.push_back(vec({ L1 + L2, D2 / 2.0, 0.0 }));
	outline.push_back(vec({ L1 + L2, 0.0, 0.0 }));

}
#pragma endregion

#pragma region wheel_group

wheel_group::wheel_group() :
	show_data{ nullptr, nullptr, nullptr, nullptr, nullptr },
	nut_L(0.0),
	max_num(0)
{
}

wheel_group::~wheel_group()
{
	for (size_t i = 0; i < 5; i++)
	{
		if (show_data[i] != nullptr)
		{
			delete show_data[i];
			show_data[i] = nullptr;
		}
	}
}

void wheel_group::set_wheel_pole(
	double _D0, double _D1, double _D2,
	double _L0, double _L1, double _L2)
{
	nut_L = _L1;
	pole.set_pole(_D0, _D1, _D2, _L0, _L1, _L2);
	show_data[0] = new mat;
	pole.get_outline(*(show_data[0]));
}

void wheel_group::set_nut(double _L3, double _D3)
{
	nut.set_wheel(_D3, _L3, 1.0, 1.0);
	show_data[1] = new mat;
	nut.get_outline(*(show_data[1]));

	for (size_t i = 0; i < show_data[1]->n_cols; i++)
	{
		show_data[1]->col(i)[0] = show_data[1]->col(i)[0] + nut_L;
	}
}

void wheel_group::is_data_n(size_t& n)
{
	n = 0;
	for (size_t i = 2; i < 5; i++)
	{
		if (show_data[i] == nullptr)
		{
			n = i;
			break;
		}
	}
}


void wheel_group::add_wheel(wheel_namespace::port_getData& val, bool dz_flag, bool ck_flag, double ck_d)
{
	if (max_num == 3)
	{
		return;
	}
	mat outline_point;
	if (dz_flag)
	{
		val.turn_over();
		val.get_outline(outline_point);
		double t = val.get_T();
		for (size_t i = 0; i < outline_point.n_cols; i++)
		{
			outline_point.col(i)[0] = outline_point.col(i)[0] + t;
		}
	}
	else
	{
		val.get_outline(outline_point);
	}
	//参考左
	if (ck_flag)
	{
		for (size_t i = 0; i < outline_point.n_cols; i++)
		{
			outline_point.col(i)[0] = outline_point.col(i)[0] + ck_d;
		}
		size_t n = 0;
		is_data_n(n);
		if (n != 0)
		{
			show_data[n] = new mat(outline_point);
			max_num++;
		}
	}
	//参考右
	else
	{
		double t = val.get_T();
		for (size_t i = 0; i < outline_point.n_cols; i++)
		{
			outline_point.col(i)[0] = outline_point.col(i)[0] + ck_d - t;
		}
		size_t n = 0;
		is_data_n(n);
		if (n != 0)
		{
			show_data[n] = new mat(outline_point);
			max_num++;
		}
	}
}

void wheel_group::get_show_outlines(std::vector<mat>& mat_vec)
{
	for (size_t i = 0; i < 5; i++)
	{
		if (show_data[i] != nullptr)
		{
			mat_vec.push_back(*(show_data[i]));
		}
	}
}

std::vector<mat> wheel_group::get_show_outlines()
{
	std::vector<mat> mat_vec;
	get_show_outlines(mat_vec);
	return mat_vec;
}

void wheel_group::get_wheel_outline(mat& val)
{
	size_t n = 0;
	for (size_t i = 2; i < 5; i++)
	{
		if (show_data[i] != nullptr)
		{
			n = n + show_data[i]->n_cols;
		}
	}
	val.resize(3, n);
	n = 0;
	for (size_t i = 2; i < 5; i++)
	{
		if (show_data[i] != nullptr)
		{
			for (size_t j = 0; j < show_data[i]->n_cols; j++)
			{
				val.col(n) = show_data[i]->col(j);
				n++;
			}
		}
	}
}

mat wheel_group::get_wheel_outline()
{
	mat val;
	get_wheel_outline(val);
	return val;
}

#pragma endregion