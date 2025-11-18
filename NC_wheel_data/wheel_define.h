#pragma once
#ifdef NC_wheel_data_EXPORTS
#define NC_wheel_data_API __declspec(dllexport)
#else
#define NC_wheel_data_API __declspec(dllimport)
#endif
namespace wheel_namespace
{
	constexpr auto _Ping = 100;
	constexpr auto _Beixing = 101;
	constexpr auto _Yuanjiao = 102;
	constexpr auto _Diexing = 103;
	constexpr auto _DXF = 104;
	constexpr auto _Jianjiao = 105;
}
