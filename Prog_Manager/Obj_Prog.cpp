#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Obj_Prog.h"


void DL::RotX(double in_ang)
{
	mat rot_sys = tcRotX(3, in_ang);
	int count_p = Data.size();
	for (int i = 0; i < count_p; i++)
	{
		Data[i].G_P = rot_sys * Data[i].G_P;
		Data[i].G_SYS_HDM = rot_sys * Data[i].G_SYS_HDM;
		Data[i].G_SYS_SL = rot_sys * Data[i].G_SYS_SL;

		Data[i].JC_P = rot_sys * Data[i].JC_P;
		Data[i].JC_SYS_HDM = rot_sys * Data[i].JC_SYS_HDM;
		Data[i].JC_SYS_SL = rot_sys * Data[i].JC_SYS_SL;
	}
}

void DL::reset()
{
	Data.clear();
}

double DL::maxR()
{
	double max_r = 0.0;
	for (int i = 0; i < Data.size(); i++)
	{
		vec ls_p = Data[i].G_P;
		ls_p(0) = 0.0;
		double ls_r = norm(ls_p);
		if (max_r < ls_r)
		{
			max_r = ls_r;
		}
	}
	return max_r;
}

double DL::minX()
{
	double min_x = Data[0].G_P(0);
	return min_x;
}

DL::DL()
{
	//Spd_r_min = 0.0;
	//LengQueYe = 0;
	//anquandian = Point_by_5axis();

	Data.clear();
	Data.shrink_to_fit();
}

DL::~DL()
{
}

//DL DL::operator=(const DL& A)
//{
//	Spd_r_min = A.Spd_r_min;
//	LengQueYe = A.LengQueYe;
//	anquandian = A.anquandian;
//
//	Data = A.Data;
//	return *this;
//}

DL_P::DL_P()
{
	G_P = { 0.0,0.0,0.0 };
	G_SYS_HDM = eye(3, 3);
	G_SYS_SL = eye(3, 3);

	JC_P = zeros(3);
	JC_SYS_HDM = eye(3, 3);
	JC_SYS_SL = eye(3, 3);

	theta_nz = 0.0;
	theta_bd = 0.0;

	point_type = 0;
}

DL_P::~DL_P()
{
}

//DL_P DL_P::operator=(const DL_P& A)
//{
//	G_P = A.G_P;
//	G_SYS_HDM = A.G_SYS_HDM;
//	G_SYS_SL = A.G_SYS_SL;
//
//	JC_P = A.JC_P;
//	JC_SYS_HDM = A.JC_SYS_HDM;
//	JC_SYS_SL = A.JC_SYS_SL;
//
//	theta_nz = A.theta_nz;
//	theta_bd = A.theta_bd;
//
//	point_type = A.point_type;
//	return *this;
//}

Point_by_5axis::Point_by_5axis()
{
	X = 0.0;
	Y = 0.0;
	Z = 0.0;
	A = 0.0;
	C = 0.0;
}

Point_by_5axis::~Point_by_5axis()
{
}

void Point_by_5axis::Set_Point(double x, double y, double z, double a, double c)
{
	X = x;
	Y = y;
	Z = z;
	A = a;
	C = c;
}


//DL_P_fu_prog DL_P_fu_prog::operator=(const DL_P_fu_prog& A)
//{
//	JC_P = A.JC_P;
//	JC_SYS_HDM = A.JC_SYS_HDM;
//	JC_SYS_SL = A.JC_SYS_SL;
//
//	theta_nz = A.theta_nz;
//	theta_bd = A.theta_bd;
//
//	point_type = A.point_type;
//	return *this;
//}

DL_fu_prog::DL_fu_prog()
{
	Data.clear();
	Data.shrink_to_fit();
}

DL_fu_prog::~DL_fu_prog()
{
}

//DL_fu_prog DL_fu_prog::operator=(const DL_fu_prog& A)
//{
//	sl_data = A.sl_data;
//	anquandian = A.anquandian;
//	Data = A.Data;
//	return *this;
//}

//螺旋槽计算砂轮位姿25.3.25-精度不高，后续提高
//输入: 前刀面点、已有切削角度的砂轮坐标系，芯厚半径
//输出: 砂轮上转90度后下转的角度
double Cal_LXC_SL_SYS_by_XH(vec3 in_qdm_p, mat33& in_sys, double in_sl_R, double in_xinhou)
{
	//将砂轮上转90度，100%芯厚时位姿
	mat33 start_sys = in_sys * tcRotZ(3, 90.0);
	//砂轮以0为初始角，间隔1往下转(90°终止)，直到圆周上有点到回转轴半径小于芯厚
	double delta_ang_sl = 1.0;
	double cur_ang_sl = 0.0;

	bool is_end = 0;
	while (cur_ang_sl < 90.0)
	{
		//计算当前砂轮抽象圆的圆心
		mat33 cur_sys = start_sys * tcRotZ(3, -cur_ang_sl);  //A_SYS_B
		vec3 cur_o_p = in_qdm_p + cur_sys * (-tcX(3)) * in_sl_R;  //A_O_B

		//以前刀面点为初始点(A_P)，圆周离散，计算点到回转轴距离
		double delta_ang_p = 1.0;
		double cur_ang_p = 0.0;
		while (cur_ang_p < 90.0)
		{
			vec3 cal_p = cur_sys.i() * (in_qdm_p - cur_o_p); //前刀面在砂轮坐标系中位置 B_P = B_A * (A_P -A_O_B)
			cal_p = cur_sys * tcRotZ(3, cur_ang_p) * cal_p; //旋转坐标系 A_SYS_B * tcRot*B_P + A_O_B
			cal_p = cal_p + cur_o_p; //平移回原坐标系

			//计算点到回转轴距离
			double dis_zhou = sqrt(cal_p(0) * cal_p(0) + cal_p(1) * cal_p(1));
			if (dis_zhou < in_xinhou / 2.0)
			{
				is_end = 1;
				break;
			}
			cur_ang_p = cur_ang_p + delta_ang_p;
		}

		if (is_end)
		{
			break;
		}
		cur_ang_sl = cur_ang_sl + delta_ang_sl;
	}

	//输出当前砂轮转角
	return cur_ang_sl;
}

