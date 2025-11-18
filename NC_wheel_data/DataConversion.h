#pragma once
#ifdef NC_wheel_data_EXPORTS
#define NC_wheel_data_API __declspec(dllexport)
#else
#define NC_wheel_data_API __declspec(dllimport)
#endif
#include"wheel.h"
#include"WheelDatabaseManager.h"



//数据转换类
class NC_wheel_data_API DataConversion
{
public:
	//砂轮的数据转换
	wheel_pack_data wheel_to_pack(my_function::port_getData* val);
	//砂轮组的数据转换
	//group_pack_data group_to_pack(T val);
};


