#pragma once

#include "NC_Prog_nb_NC_Block.h"

#ifdef NC_Prog_nb_NC_Block_EXPORTS
#define NC_Prog_nb_NC_Block_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_API __declspec(dllimport)
#endif


//大部分需要做接口
#pragma region 程序块生成函数声明

#pragma region 变量生成

// 申请变量函数 - 单程序块
//向变量管理器申请变量
NC_Prog_nb_NC_Block_API nb_NC_block& nb_new_BL_Block();

// 申请变量函数 - 单程序块
//向变量管理器申请变量
NC_Prog_nb_NC_Block_API nb_NC_block& nb_new_BL_Block(int no);

//申请指定坐标的变量
NC_Prog_nb_NC_Block_API nb_NC_block& nb_BL_Block(int type, int no);

//申请@号变量
NC_Prog_nb_NC_Block_API nb_NC_block& nb_BL(int no);

//申请@号变量
NC_Prog_nb_NC_Block_API nb_NC_block& nb_BL(nb_NC_block& block_in);

//子程序开始
void NC_Prog_nb_NC_Block_API nb_ProBegin();

//子程序结束
void NC_Prog_nb_NC_Block_API nb_ProEnd();

#pragma endregion

#pragma region 函数计算

NC_Prog_nb_NC_Block_API nb_NC_block& nb_FuHao(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_abs(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_acos(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_asin(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_atan(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_cos(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_sin(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_tan(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_ceil(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_floor(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_round(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_exp(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_ln(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_sqrt(nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_max(nb_NC_block&, nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_min(nb_NC_block&, nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_pow(nb_NC_block&, nb_NC_block&);
NC_Prog_nb_NC_Block_API nb_NC_block& nb_ChangShu(double d);

#pragma endregion

#pragma region 运算符重载

//正
NC_Prog_nb_NC_Block_API nb_NC_block& operator+(nb_NC_block&);

//负
NC_Prog_nb_NC_Block_API nb_NC_block& operator-(nb_NC_block&);

//减号
NC_Prog_nb_NC_Block_API nb_NC_block& operator-(nb_NC_block&, nb_NC_block&);

//减号
NC_Prog_nb_NC_Block_API nb_NC_block& operator-(nb_NC_block&, double d_in);

//加号
NC_Prog_nb_NC_Block_API nb_NC_block& operator+(nb_NC_block&, nb_NC_block&);

//加号
NC_Prog_nb_NC_Block_API nb_NC_block& operator+(nb_NC_block&, double d_in);

//乘号
NC_Prog_nb_NC_Block_API nb_NC_block& operator*(nb_NC_block&, nb_NC_block&);

//乘号
NC_Prog_nb_NC_Block_API nb_NC_block& operator*(nb_NC_block&, double d_in);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator/(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator/(nb_NC_block&, double d_in);

//求模
NC_Prog_nb_NC_Block_API nb_NC_block& operator%(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator%(nb_NC_block&, double d_in);

//<
NC_Prog_nb_NC_Block_API nb_NC_block& operator<(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator<(nb_NC_block&, double d_in);

//>
NC_Prog_nb_NC_Block_API nb_NC_block& operator>(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator>(nb_NC_block&, double d_in);

//<=
NC_Prog_nb_NC_Block_API nb_NC_block& operator<=(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator<=(nb_NC_block&, double d_in);

//>=
NC_Prog_nb_NC_Block_API nb_NC_block& operator>=(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator>=(nb_NC_block&, double d_in);

//==
NC_Prog_nb_NC_Block_API nb_NC_block& operator==(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator==(nb_NC_block&, double d_in);

//!=
NC_Prog_nb_NC_Block_API nb_NC_block& operator!=(nb_NC_block&, nb_NC_block&);

//除号
NC_Prog_nb_NC_Block_API nb_NC_block& operator!=(nb_NC_block&, double d_in);

//&&
NC_Prog_nb_NC_Block_API nb_NC_block& operator&&(nb_NC_block&, nb_NC_block&);

//^
NC_Prog_nb_NC_Block_API nb_NC_block& operator^(nb_NC_block&, nb_NC_block&);

//||
NC_Prog_nb_NC_Block_API nb_NC_block& operator||(nb_NC_block&, nb_NC_block&);

//<<
NC_Prog_nb_NC_Block_API nb_NC_block& operator<<(nb_NC_block&, nb_NC_block&);

//非
NC_Prog_nb_NC_Block_API nb_NC_block& operator!(nb_NC_block&);

//-
NC_Prog_nb_NC_Block_API nb_NC_block& operator-(double d_in, nb_NC_block& block_in);

//+
NC_Prog_nb_NC_Block_API nb_NC_block& operator+(double d_in, nb_NC_block& block_in);

//*
NC_Prog_nb_NC_Block_API nb_NC_block& operator*(double d_in, nb_NC_block& block_in);

//除
NC_Prog_nb_NC_Block_API nb_NC_block& operator/(double d_in, nb_NC_block& block_in);

//%
NC_Prog_nb_NC_Block_API nb_NC_block& operator%(double d_in, nb_NC_block& block_in);

//<
NC_Prog_nb_NC_Block_API nb_NC_block& operator<(double d_in, nb_NC_block& block_in);

//>
NC_Prog_nb_NC_Block_API nb_NC_block& operator>(double d_in, nb_NC_block& block_in);

//<=
NC_Prog_nb_NC_Block_API nb_NC_block& operator<=(double d_in, nb_NC_block& block_in);

//>=
NC_Prog_nb_NC_Block_API nb_NC_block& operator>=(double d_in, nb_NC_block& block_in);

//==
NC_Prog_nb_NC_Block_API nb_NC_block& operator==(double d_in, nb_NC_block& block_in);

//!=
NC_Prog_nb_NC_Block_API nb_NC_block& operator!=(double d_in, nb_NC_block& block_in);

//= 这个函数有两个
NC_Prog_nb_NC_Block_API nb_NC_block& nb_SET_VALUE(nb_NC_block& zuobian, nb_NC_block& youbian);

#pragma endregion

#pragma region M代码

//M00
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M00();

//M01
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M01();

//M02
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M02();

//M03
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M03();

//M04
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M04();

//M05
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M05();

//M06
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M06(int tool_using, int sl_num_on_slz);

//M08
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M08();

//M09
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M09();

//M30
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M30();

//M13
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M13();

//M14
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M14();

//M15
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M15();

#pragma endregion

#pragma region G代码

//G00
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G00();

//G01
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01();

//G04
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G04();

//G52
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G52();

//G53
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G53();

//G54
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G54();

//G55
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G55();

//G56
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G56();

//G57
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G57();

//G58
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G58();

//G59
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G59();

//G90
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G90();

//Set_RGB
NC_Prog_nb_NC_Block_API nb_NC_block& nb_Set_RGB(int color);

//WAIT
NC_Prog_nb_NC_Block_API nb_NC_block& nb_WAIT();

//M98
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M98(nb_NC_block* targer_prog_root, int name_number);

//M99
NC_Prog_nb_NC_Block_API nb_NC_block& nb_M99();

NC_Prog_nb_NC_Block_API nb_NC_block& nb_S_speed(int s);

//S2_speed
NC_Prog_nb_NC_Block_API nb_NC_block& nb_S2_speed(int s);

//G91
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G91();

#pragma endregion

#pragma region 运动控制

//!=
NC_Prog_nb_NC_Block_API nb_NC_block& nb_F(double d_in);

//基础G31，其他G31调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X_Y_Z_A_C(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c
);

//基础运动生成，其他运动调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X_Y_Z_A_C(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c
);

//基础运动生成，其他运动调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X_Y_Z_A_C_F(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c,
	nb_NC_block& f
);

//基础运动生成，其他运动调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X_Y_Z_A_C_F(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c,
	nb_NC_block& f
);

//基础运动生成，其他运动调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_X_Y_Z_A_C_F(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c,
	nb_NC_block& f
);

//基础运动生成，其他运动调用此函数
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_X_Y_Z_A_C(
	nb_NC_block& x,
	nb_NC_block& y,
	nb_NC_block& z,
	nb_NC_block& a,
	nb_NC_block& c
);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X(nb_NC_block& x);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_Y(nb_NC_block& y);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_Z(nb_NC_block& z);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_A(nb_NC_block& a);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_C(nb_NC_block& c);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X_Y_Z(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X_F(nb_NC_block& x, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_Y_F(nb_NC_block& y, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_Z_F(nb_NC_block& z, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_A_F(nb_NC_block& a, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_C_F(nb_NC_block& c, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X(nb_NC_block& x);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_Y(nb_NC_block& y);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_Z(nb_NC_block& z);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_A(nb_NC_block& a);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_C(nb_NC_block& c);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X_Y_Z(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X_F(nb_NC_block& x, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_Y_F(nb_NC_block& y, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_Z_F(nb_NC_block& z, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_A_F(nb_NC_block& a, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_C_F(nb_NC_block& c, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G31_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_X_F(nb_NC_block& x, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_Y_F(nb_NC_block& y, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_Z_F(nb_NC_block& z, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_A_F(nb_NC_block& a, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_C_F(nb_NC_block& c, nb_NC_block& f);

//运动生成
NC_Prog_nb_NC_Block_API nb_NC_block& nb_G01_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f);

#pragma endregion

#pragma region 逻辑结构（非接口）

NC_Prog_nb_NC_Block_API nb_NC_block& IF_zi(nb_NC_block& tiaojian);

NC_Prog_nb_NC_Block_API nb_NC_block& NEXT_zi();

NC_Prog_nb_NC_Block_API nb_NC_block& BACK_zi();

NC_Prog_nb_NC_Block_API nb_NC_block& END_zi();

NC_Prog_nb_NC_Block_API nb_NC_block& EXIT_zi();

#pragma endregion

#pragma region 逻辑结构

NC_Prog_nb_NC_Block_API nb_NC_block& nb_WHILE_K(nb_NC_block& tiaojian, nb_NC_block& xunhuanti);

NC_Prog_nb_NC_Block_API nb_NC_block& nb_IF_K(nb_NC_block& tiaojian, nb_NC_block& zhuti);

NC_Prog_nb_NC_Block_API nb_NC_block& nb_IF_ELSE_K(
	nb_NC_block& tiaojian,
	nb_NC_block& zhuti1,
	nb_NC_block& zhuti2
);

NC_Prog_nb_NC_Block_API nb_NC_block& nb_IF_ELSEIF_ELSE_K(
	nb_NC_block& tiaojian1, nb_NC_block& zhuti1,
	nb_NC_block& tiaojian2, nb_NC_block& zhuti2,
	nb_NC_block& zhuti3
);

NC_Prog_nb_NC_Block_API nb_NC_block& nb_Process_K(int i);
#pragma endregion

