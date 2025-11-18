#include "pch.h"
#define NC_wheel_Intersecting_line_EXPORTS
#include "gongyi_input.h"


gongyi_input::gongyi_input()
{
}

void gongyi_input::push_back(gongyi_input_namespace::gongyi_data data)
{
	//¼ÇÂ¼¹¤ÒÕ¶Î±àºÅ
	size_t temp = gongyi_num_all;
	std::vector<size_t> temp_vec;
	for (size_t i = 0; i < data.pos.size(); i++)
	{
		temp_vec.push_back(temp);
	}


	wheel.push_back(data.wheel_data);
	gongyi_rgb.push_back(data.rgb);
	

	pos_all.insert(pos_all.end(), data.pos.begin(), data.pos.end());
	pos_gongyi_num.insert(pos_gongyi_num.end(), temp_vec.begin(), temp_vec.end());

	gongyi_num_all++;
}

void gongyi_input::reset_ptr()
{
	pos_ptr = 0;
}

void gongyi_input::last_ptr()
{
	pos_ptr++;
}

mat gongyi_input::get_one_pos()
{
	return pos_all[pos_ptr];
}

size_t gongyi_input::get_one_rgb()
{
	return gongyi_rgb[get_one_gongy_num()];
}

mat gongyi_input::get_one_wheel()
{
	return wheel[get_one_gongy_num()];
}

size_t gongyi_input::get_one_gongy_num()
{
	return pos_gongyi_num[pos_ptr];
}

bool gongyi_input::is_pos_end()
{
	if (pos_all.begin() + pos_ptr+1 == pos_all.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool gongyi_input::is_duan_end()
{
	if (pos_gongyi_num[pos_ptr] != pos_gongyi_num[pos_ptr + 1])
	{
		return true;
	}
	else
	{
		return false;
	}
}
