#pragma once

#ifdef NC_wheel_Intersecting_line_EXPORTS
#define NC_wheel_Intersecting_line_API __declspec(dllexport)
#else
#define NC_wheel_Intersecting_line_API __declspec(dllimport)
#endif

#include <vector>
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

namespace gongyi_input_namespace
{
	//工艺数据结构
	class NC_wheel_Intersecting_line_API gongyi_data
	{
	public:
		//砂轮位置序列
		std::vector<mat> pos;
		//砂轮数据
		mat wheel_data;
		//工艺颜色信息
		size_t rgb = 0;
	};
}

class NC_wheel_Intersecting_line_API gongyi_input
{
private:
	//总共工艺段数
	size_t gongyi_num_all = 0;
	//总共工艺段指针
	size_t gongyi_ptr = 0;


	//位置指针
	int pos_ptr = 0;

	//所有位置序列
	std::vector<mat> pos_all;
	//所有位置序列属于的工艺段号
	std::vector<size_t> pos_gongyi_num;

	//记录每一段工艺使用砂轮
	std::vector<mat> wheel;
	//记录每一段工艺颜色
	std::vector<size_t> gongyi_rgb;

public:
	gongyi_input();
	//输入工艺数据
	void push_back(gongyi_input_namespace::gongyi_data data);
	//复位指针
	void reset_ptr();
	//指针后移一位
	void last_ptr();
	//获取当前位置mat
	mat get_one_pos();
	//获取当前段颜色
	size_t get_one_rgb();
	//获取当前段的砂轮
	mat get_one_wheel();
	//获取当前工艺段号
	size_t get_one_gongy_num();
	//判断是最后一步工艺
	bool is_pos_end();
	//判断是是同段工艺最后一步
	bool is_duan_end();
};
