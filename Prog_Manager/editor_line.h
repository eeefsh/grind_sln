#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"generator_line.h"
#include"RenXian.h"
class  Cal_RenXian;
namespace editor_line
{
	//将起点终点反向得到新的线
	KongJianXian fanxiang(KongJianXian* line_ptr);
	//将已有空间线，进行旋转
	KongJianXian rotate(KongJianXian* line_ptr, mat33 SYS);
	//将已有空间线，进行平移
	KongJianXian trans(KongJianXian* line_ptr, vec3 O);
	//截取线已有线的一段，输入截取起点终点（0-1]，得到新的线
	KongJianXian cutting(KongJianXian* line_ptr, double start, double end);
	//沿终点切向延伸指定距离
	KongJianXian extend_end(KongJianXian* line_ptr, double add_dis);
	//沿起点切向延伸指定距离
	KongJianXian extend_start(KongJianXian* line_ptr, double add_dis);
	//拼接两条线，线1的终点是线2的起点 //若起点终点不重合、抛出错误
	KongJianXian joint_two_line(KongJianXian* line_ptr1, KongJianXian* line_ptr2);


	//将起点终点反向得到新的线
	//Cal_RenXian fanxiang(Cal_RenXian* line_ptr);
	//将已有刃线，进行旋转
	Cal_RenXian rotate(Cal_RenXian* line_ptr, mat33 SYS);
	//将已有刃线，进行平移
	Cal_RenXian trans(Cal_RenXian* line_ptr, vec3 O);
	//截取线已有刃线的一段，输入截取起点终点（0-1]，得到新的线
	Cal_RenXian cutting(Cal_RenXian* line_ptr, double start, double end);
	//沿终点切向延伸指定距离
	Cal_RenXian extend_end(Cal_RenXian* line_ptr, double add_dis);
	//沿起点切向延伸指定距离
	Cal_RenXian extend_start(Cal_RenXian* line_ptr, double add_dis);
	//拼接两条刃线，线1的终点是线2的起点
	Cal_RenXian joint_two_line(Cal_RenXian* line_ptr1, Cal_RenXian* line_ptr2);
	//对球头线设置偏心距
	Cal_RenXian set_pinxin_dis(Cal_RenXian* line_ptr, double in_dis);
}