#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

#include"manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"
#include"manager_h/MA_010201_Cal_JiHe_JiBen.h"

#include"manager_h/MA_010601_Cal_JiHe_PointSort.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//计算过程参考系 不同于输出矩阵参考系、输出时转换

//增加纵截面长度坐标，统一成型刀的采样 9.30  等于z值 
//空间线类； 输出矩阵一行为一个：点 + 切向+纵截面长度坐标，n*7
class Prog_Manager_API KongJianXian
{
//初始化
public:
	KongJianXian();
	~KongJianXian();
	void set_delta_dis(double in_dis);
	//初始化空间线数据 输入计算好的有序点：3*n
	void init_data(mat& in_points);

//总体数据
private:
	//点的个数
	int count_p; 
	//点的间隔距离
	double delta_dis ;

//局部数据
private:
	//{点坐标 + 切向：n*6} //最后一点切向为前一点
	mat data;	 

//数据获取接口
public:
	//获取空间线的点间距
	double get_delta_dis();
	//获取空间线的点数量
	int count_points();
	//获取空间线的第i个点的坐标
	vec3 point(int i);
	//获取空间线的第i个点的切向
	vec3 T(int i);
	//获取空间线的所有点的坐标
	mat get_all_p();
	//获取空间线的所有点的切向
	mat get_all_T();
	//获取空间线的第i个点的纵截面长度坐标
	double get_lenth(int i);

//自身编辑
public:
	//将起点终点反向得到新的线
	void fanxiang();
	//将已有空间线，进行旋转
	void rotate(mat33 SYS);
	//将已有空间线，进行平移
	void trans(vec3 O);
	//截取线已有线的一段，输入截取起点终点（0-1]，得到新的线
	void cutting(double start, double end);
	//沿终点切向延伸指定距离
	void extend_end(double add_dis);
	//沿起点切向延伸指定距离--10.8 有错误不能使用
	void extend_start(double add_dis);
	//
	void join_a_line(KongJianXian& in_line2);
};









