#pragma once

#ifdef NC_wheel_Intersecting_line_EXPORTS
#define NC_wheel_Intersecting_line_API __declspec(dllexport)
#else
#define NC_wheel_Intersecting_line_API __declspec(dllimport)
#endif

#include"manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

namespace jiaoxian_wheel_namespace
{
	//对砂轮求交的基础模块
	class jiaoxian_wheel
	{
	private:
		//砂轮轮廓点
		mat lunkuo_point;
		//截面法向
		vec jiemian_n;
		//截面点
		vec jiemian_p;
		//截面法向和轮廓点坐标x轴的夹角
		double Theta;
	public:
		
		jiaoxian_wheel();

		//获取交线点
		//输入砂轮轮廓点、面法向、面上任意点
		mat get_point(mat& val, vec n_in, vec p_in, double acc, bool flag = 1);
	private:
		//初始化步骤
		void No1_Function();
		//偏角计算序列
		//使用后在轮廓点里z值记录了会相交的点，z为1
		vec Phi();
		//初始偏角
		double Phi_0();
		//加密点
		void line_add_point(mat& val, double acc);
		//获取x轴投影点
		vec get_p_x(vec val);
		//投影点到面最近处向量
		//输入投影点
		vec get_Tn(vec val);
	};
}

//第一步设置相交面
//第二步输入砂轮位置矩阵获得截面线轮廓点
//输入的砂轮轴线为x轴，砂轮左侧贴近yz平面
class NC_wheel_Intersecting_line_API jie_mian_xian
{
private:
	//截面法向
	vec G_N;
	//截面上任意点
	vec G_P;
	//砂轮轮廓(由砂轮库生成)
	mat val_wheel;
	jiaoxian_wheel_namespace::jiaoxian_wheel jiaoxian;
	// 计算一个旋转矩阵，将向量 n 旋转到 z 方向 (0, 0, 1),GPT
	mat findRotationMatrixToZ(vec n);
	//视口矩阵
	mat44 G_SYS_View;
public:

	jie_mian_xian();
	//设置截面
	//输入：面法向vec(3)，面上任意点vec(3)，输入砂轮轮廓点(由砂轮库生成)
	void set_jiemian(mat44 _view, mat val);
	//获取截面交线点
	//输入砂轮位置 4阶矩阵
	mat get_outline_point(mat& sys, bool flag = 1);

	
};