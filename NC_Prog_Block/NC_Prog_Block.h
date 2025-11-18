#pragma once
/*
*	******************使用模板的说明*****************
* 
*	1、替换解决方案中所有的 “NC_Prog_Block” 为 自定义的项目名
*	2、替换要最终输出的头文件为 自定义的项目名
*	3、本项目最终输出的dll、lib文件已设置成以 项目名 命名
*	4、模板设置了环境变量 xt_import_vc_dir 指向总的库目录（需要按照制定的结构存放库）
*	5、 参照 引用额外的库的说明 引用库
*  
*/

#ifdef NC_Prog_Block_EXPORTS
#define NC_Prog_Block_API __declspec(dllexport)
#else
#define NC_Prog_Block_API __declspec(dllimport)
#endif

/*  ****************** 引用额外的库的说明 ******************
*	
*	1、本项目模板默认包含NC_Prog_Block的设置作为实例，如下
*	2、请参照NC_Prog_Block_settings.h文件内容和安置路径设置其他库
*	3、可能还需要进行一些手动操作，详情见xt_armadillo_settings.h中说明
*	4、将上一层相关库关联信息代码复制到 生成后事件
*/

#include "manager_h/MA_030201_NC_Prog_Virtual_Machine.h"
#include "manager_h\MA_031001_NC_Prog_nb_NC_Block.h"
#include "manager_h/MA_031101_NC_Prog_nb_NC_Block_matrix.h"


#include <string>
using std::string;

class nc_block;
class nc_block_vec3;
class nc_block_matrix33;
class nb_NC_block;
class nb_NC_block_vec3;
class nb_NC_block_matrix33;
class virtual_machine;
extern class NC_control_message;
class nc_program;

void NC_Prog_Block_API reset_var_manager();

class NC_Prog_Block_API nc_block
{
public:
	nb_NC_block* block;

public:
	nc_block();
public:
	nc_block(const nc_block&);
public:
	nc_block(nb_NC_block&);

public:
	~nc_block();

public:
	void set_null();

public:
	void set_model();

public:
	void release_block_tree();
public:
	void replace(nc_block);

	friend class nc_block_matrix33;
	friend class nc_block_vec3;

public:
	std::string write_code();
public:
	void zhixing();

public:
	void set_machine(virtual_machine* pmachine);

public:
	//设置断点
	void set_stop();

public:
	//当出现错误需要重新执行时使用
	//只需要调用树根的reset();
	void reset();

	//友元函数定义
#pragma region friend funs
	friend NC_Prog_Block_API nc_block FuHao(nc_block);
	friend NC_Prog_Block_API nc_block abs(nc_block);
	friend NC_Prog_Block_API nc_block acos(nc_block);
	friend NC_Prog_Block_API nc_block asin(nc_block);
	friend NC_Prog_Block_API nc_block atan(nc_block);
	friend NC_Prog_Block_API nc_block cos(nc_block);
	friend NC_Prog_Block_API nc_block sin(nc_block);
	friend NC_Prog_Block_API nc_block tan(nc_block);
	friend NC_Prog_Block_API nc_block ceil(nc_block);
	friend NC_Prog_Block_API nc_block floor(nc_block);
	friend NC_Prog_Block_API nc_block round(nc_block);
	friend NC_Prog_Block_API nc_block exp(nc_block);
	friend NC_Prog_Block_API nc_block ln(nc_block);
	friend NC_Prog_Block_API nc_block sqrt(nc_block);
	friend NC_Prog_Block_API nc_block max(nc_block, nc_block);
	friend NC_Prog_Block_API nc_block min(nc_block, nc_block);
	friend NC_Prog_Block_API nc_block pow(nc_block, nc_block);
	friend NC_Prog_Block_API nc_block ChangShu(double d);

	//非
	friend NC_Prog_Block_API nc_block operator!(nc_block);

	//-
	friend NC_Prog_Block_API nc_block operator-(double d_in, nc_block block_in);

	//+
	friend NC_Prog_Block_API nc_block operator+(double d_in, nc_block block_in);

	//*
	friend NC_Prog_Block_API nc_block operator*(double d_in, nc_block block_in);

	//除
	friend NC_Prog_Block_API nc_block operator/(double d_in, nc_block block_in);

	//%
	friend NC_Prog_Block_API nc_block operator%(double d_in, nc_block block_in);

	//<
	friend NC_Prog_Block_API nc_block operator<(double d_in, nc_block block_in);

	//>
	friend NC_Prog_Block_API nc_block operator>(double d_in, nc_block block_in);

	//<=
	friend NC_Prog_Block_API nc_block operator<=(double d_in, nc_block block_in);

	//>=
	friend NC_Prog_Block_API nc_block operator>=(double d_in, nc_block block_in);

	//==
	friend NC_Prog_Block_API nc_block operator==(double d_in, nc_block block_in);

	//!=
	friend NC_Prog_Block_API nc_block operator!=(double d_in, nc_block block_in);

	//2025.2.20
	friend NC_Prog_Block_API nc_block operator*(nc_block block_in1, nc_block block_in2);

	//乘号
	friend NC_Prog_Block_API nc_block operator*(nc_block block_in1, nc_block block_in2);

	friend NC_Prog_Block_API nc_block operator-(nc_block block_in1, nc_block block_in2);

	//减号
	friend NC_Prog_Block_API nc_block operator-(nc_block block_in1, double d_in);

	//加号
	friend NC_Prog_Block_API nc_block operator+(nc_block block_in1, nc_block block_in);

	//加号
	friend NC_Prog_Block_API nc_block operator+(nc_block block_in1, double d_in);

	////乘号
	//friend NC_Prog_Block_API nc_block& operator*(nc_block block_in);

	//乘号
	friend NC_Prog_Block_API nc_block operator*(nc_block block_in1, double d_in);

	//除号
	friend NC_Prog_Block_API nc_block operator/(nc_block block_in1,nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator/(nc_block block_in1, double d_in);

	//求模
	friend NC_Prog_Block_API nc_block operator%(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator%(nc_block block_in1, double d_in);

	//<
	friend NC_Prog_Block_API nc_block operator<(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator<(nc_block block_in1, double d_in);

	//>
	friend NC_Prog_Block_API nc_block operator>(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator>(nc_block block_in1, double d_in);

	//<=
	friend NC_Prog_Block_API nc_block operator<=(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator<=(nc_block block_in1, double d_in);

	//>=
	friend NC_Prog_Block_API nc_block operator>=(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator>=(nc_block block_in1, double d_in);

	//==
	friend NC_Prog_Block_API nc_block operator==(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator==(nc_block block_in1, double d_in);

	//!=
	friend NC_Prog_Block_API nc_block operator!=(nc_block block_in1, nc_block block_in);

	//除号
	friend NC_Prog_Block_API nc_block operator!=(nc_block block_in1, double d_in);

	//&&
	friend NC_Prog_Block_API nc_block operator&&(nc_block block_in1, nc_block block_in);

	//^
	friend NC_Prog_Block_API nc_block operator^(nc_block block_in1, nc_block block_in);

	//||
	friend NC_Prog_Block_API nc_block operator||(nc_block block_in1, nc_block block_in);

	////=
	//friend NC_Prog_Block_API nc_block& operator=(nc_block block_in1, nc_block block_in);

	////=
	//friend NC_Prog_Block_API nc_block& operator=(nc_block block_in1, double d_in);


	friend NC_Prog_Block_API nc_block operator<<(nc_block& block_in1, nc_block block_in);

	friend NC_Prog_Block_API void operator>>(std::ofstream& oss, nc_block block_in);

	//= 这个函数有两个
	friend NC_Prog_Block_API nc_block SET_VALUE(nc_block zuobian, nc_block youbian);


	//M00
	friend NC_Prog_Block_API nc_block M00();

	//M01
	friend NC_Prog_Block_API nc_block M01();

	//M02
	friend NC_Prog_Block_API nc_block M02();

	//M03
	friend NC_Prog_Block_API nc_block M03();

	//M04
	friend NC_Prog_Block_API nc_block M04();

	//M05
	friend NC_Prog_Block_API nc_block M05();

	//M06
	friend NC_Prog_Block_API nc_block M06(int tool_using, int in_sl_pos_on_slz);

	//M08
	friend NC_Prog_Block_API nc_block M08();

	//M09
	friend NC_Prog_Block_API nc_block M09();

	//M30
	friend NC_Prog_Block_API nc_block M30();

	//M13
	friend NC_Prog_Block_API nc_block M13();

	//M14
	friend NC_Prog_Block_API nc_block M14();

	//M15
	friend NC_Prog_Block_API nc_block M15();

	//G00
	friend NC_Prog_Block_API nc_block G00();

	//G01
	friend NC_Prog_Block_API nc_block G01();

	//G04
	friend NC_Prog_Block_API nc_block G04();

	//G52
	friend NC_Prog_Block_API nc_block G52();

	//G53
	friend NC_Prog_Block_API nc_block G53();

	//G54
	friend NC_Prog_Block_API nc_block G54();

	//G55
	friend NC_Prog_Block_API nc_block G55();

	//G56
	friend NC_Prog_Block_API nc_block G56();

	//G57
	friend NC_Prog_Block_API nc_block G57();

	//G58
	friend NC_Prog_Block_API nc_block G58();

	//G59
	friend NC_Prog_Block_API nc_block G59();

	//G90
	friend NC_Prog_Block_API nc_block G90();

	//Set_RGB
	friend NC_Prog_Block_API nc_block Set_RGB(int color);

	//WAIT
	friend NC_Prog_Block_API nc_block WAIT();

	//M98
	friend NC_Prog_Block_API nc_block M98(nc_block targer_block,int name_num);

	//M99
	friend NC_Prog_Block_API nc_block M99();

	friend NC_Prog_Block_API nc_block S_speed(int s);

	friend NC_Prog_Block_API nc_block S2_speed(int s);
	//G91
	friend NC_Prog_Block_API nc_block G91();


	//!=
	friend NC_Prog_Block_API nc_block F(double d_in);

	//基础运动生成，其他运动调用此函数
	friend NC_Prog_Block_API nc_block X_Y_Z_A_C(
		nc_block x,
		nc_block y,
		nc_block z,
		nc_block a,
		nc_block c
	);

	//基础运动生成，其他运动调用此函数
	friend NC_Prog_Block_API nc_block X_Y_Z_A_C_F(
		nc_block x,
		nc_block y,
		nc_block z,
		nc_block a,
		nc_block c,
		nc_block f
	);

	//基础G31，其他G31调用此函数
	friend NC_Prog_Block_API nc_block G31_X_Y_Z_A_C(
		nc_block x,
		nc_block y,
		nc_block z,
		nc_block a,
		nc_block c
	);

	//基础运动生成，其他运动调用此函数
	friend NC_Prog_Block_API nc_block G31_X_Y_Z_A_C_F(
		nc_block x,
		nc_block y,
		nc_block z,
		nc_block a,
		nc_block c,
		nc_block f
	);

	//基础运动生成，其他运动调用此函数
	friend NC_Prog_Block_API nc_block G01_X_Y_Z_A_C_F(
		nc_block x,
		nc_block y,
		nc_block z,
		nc_block a,
		nc_block c,
		nc_block f
	);

	friend NC_Prog_Block_API nc_block G01_X_Y_Z_A_C(
		nc_block x, nc_block y, nc_block z,
		nc_block a, nc_block c);

	//运动生成
	friend NC_Prog_Block_API nc_block X(nc_block x);

	//运动生成
	friend NC_Prog_Block_API nc_block Y(nc_block y);

	//运动生成
	friend NC_Prog_Block_API nc_block Z(nc_block z);

	//运动生成
	friend NC_Prog_Block_API nc_block A(nc_block a);

	//运动生成
	friend NC_Prog_Block_API nc_block C(nc_block c);

	//运动生成
	friend NC_Prog_Block_API nc_block X_Y_Z(nc_block x, nc_block y, nc_block z);

	//运动生成
	friend NC_Prog_Block_API nc_block X_F(nc_block x, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block Y_F(nc_block y, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block Z_F(nc_block z, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block A_F(nc_block a, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block C_F(nc_block c, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_X(nc_block x);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_Y(nc_block y);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_Z(nc_block z);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_A(nc_block a);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_C(nc_block c);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_X_Y_Z(nc_block x, nc_block y, nc_block z);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_X_F(nc_block x, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_Y_F(nc_block y, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_Z_F(nc_block z, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_A_F(nc_block a, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_C_F(nc_block c, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G31_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_X_F(nc_block x, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_Y_F(nc_block y, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_Z_F(nc_block z, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_A_F(nc_block a, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_C_F(nc_block c, nc_block f);

	//运动生成
	friend NC_Prog_Block_API nc_block G01_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

	friend NC_Prog_Block_API nc_block BREAK();

	friend NC_Prog_Block_API nc_block WHILE_K(nc_block tiaojian, nc_block xunhuanti);

	friend NC_Prog_Block_API nc_block IF_K(nc_block tiaojian, nc_block zhuti);

	friend NC_Prog_Block_API nc_block IF_ELSE_K(
		nc_block tiaojian,
		nc_block zhuti1,
		nc_block zhuti2
	);

	friend NC_Prog_Block_API nc_block IF_ELSEIF_ELSE_K(
		nc_block tiaojian1, nc_block zhuti1,
		nc_block tiaojian2, nc_block zhuti2,
		nc_block zhuti3
	);

	friend NC_Prog_Block_API nc_block Process_K(int i);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, nc_block_vec3 vec1);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(vec3 vec, nc_block_vec3 vec1);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, vec3 vec1);

	//矩阵乘向量
	friend NC_Prog_Block_API nc_block_vec3 operator*(mat33 mat_in, nc_block_vec3 vec_in);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, nc_block_vec3 vec2);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(vec3 vec1, nc_block_vec3 vec2);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, vec3 vec2);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

	friend NC_Prog_Block_API nc_block& new_BL_Block();

	friend NC_Prog_Block_API nc_block_matrix33 RotX(nc_block);

	friend NC_Prog_Block_API nc_block_matrix33 RotY(nc_block);

	friend NC_Prog_Block_API nc_block_matrix33 RotZ(nc_block);

	friend NC_Prog_Block_API nc_block norm(nc_block_vec3);

	friend NC_Prog_Block_API nc_block_vec3 normalise(nc_block_vec3);

	//friend NC_Prog_Block_API nc_block Recover_block();

	//friend NC_Prog_Block_API bool reset_block();

	//friend NC_Prog_Block_API bool Recover_nc_code();

#pragma endregion

	//接口函数
public:

	//构造程序接口
#pragma region 程序块运算函数

	//负号
	nc_block operator-();

	//减号
	//nc_block& operator-(nc_block block_in);

	////减号
	//nc_block& operator-(double d_in);

	////加号
	//nc_block& operator+(nc_block block_in);

	////加号
	//nc_block& operator+(double d_in);

	//////乘号
	////nc_block& operator*(nc_block block_in);

	////乘号
	//nc_block& operator*(double d_in);

	////除号
	////nc_block& operator/(nc_block block_in);

	////除号
	//nc_block& operator/(double d_in);

	////求模
	//nc_block& operator%(nc_block block_in);

	////除号
	//nc_block& operator%(double d_in);

	////<
	//nc_block& operator<(nc_block block_in);

	////除号
	//nc_block& operator<(double d_in);

	////>
	//nc_block& operator>(nc_block block_in);

	////除号
	//nc_block& operator>(double d_in);

	////<=
	//nc_block& operator<=(nc_block block_in);

	////除号
	//nc_block& operator<=(double d_in);

	////>=
	//nc_block& operator>=(nc_block block_in);

	////除号
	//nc_block& operator>=(double d_in);

	//==
	//nc_block& operator==(nc_block block_in);

	////除号
	//nc_block& operator==(double d_in);

	////!=
	//nc_block& operator!=(nc_block block_in);

	////除号
	//nc_block& operator!=(double d_in);

	////&&
	//nc_block& operator&&(nc_block block_in);

	////^
	//nc_block& operator^(nc_block block_in);

	////||
	//nc_block& operator||(nc_block block_in);

	//=
	nc_block operator=(nc_block block_in);

	//=
	nc_block operator=(double d_in);


	//nc_block& operator<<(nc_block block_in);

#pragma endregion

public:
};

class NC_Prog_Block_API nc_block_matrix33
{
public:
	nb_NC_block_matrix33* block_mat;

public:
	bool is_BL_now = false;

public:
	~nc_block_matrix33();

public:
	nc_block_matrix33();
	nc_block_matrix33(nc_block_matrix33&);
public:
	nc_block_matrix33(nb_NC_block_matrix33&);

public:
	void replace(nc_block_matrix33);

public:
	//访问元素
	nc_block operator()(int i, int j);
	//ZYW-240110
	// 矩阵加矩阵
	nc_block_matrix33 operator+(nc_block_matrix33 mat);
	//矩阵加矩阵
	nc_block_matrix33 operator+(mat33 mat);

	//矩阵乘向量
	nc_block_vec3 operator*(nc_block_vec3);
	//矩阵乘向量
	nc_block_vec3 operator*(vec3);
	//矩阵乘矩阵
	nc_block_matrix33 operator*(nc_block_matrix33);
	//矩阵乘矩阵
	nc_block_matrix33 operator*(mat33);
	//矩阵乘数
	nc_block_matrix33 operator*(double& dou);
	//矩阵乘数
	nc_block_matrix33 operator*(nc_block bl);
	//访问列
	nc_block_vec3 col(int i);
	//设置元素程序块，将输入程序块挂在矩阵指定位置上
	void set_nc_Block(int i, int j, nc_block block_in);

	nc_block& operator=(nc_block_matrix33);

	nc_block& operator=(mat33);

	friend class nc_block_vec3;
	friend class nc_block;
	friend NC_Prog_Block_API nc_block_matrix33& new_BL_Mat();

	friend NC_Prog_Block_API nc_block_matrix33& new_uninit_BL_Mat();
	//矩阵乘矩阵
	friend NC_Prog_Block_API nc_block_matrix33 operator*(mat33 mat_in, nc_block_matrix33 mat_in1);

	friend NC_Prog_Block_API nc_block_matrix33 operator*(double dou, nc_block_matrix33 mat_in1);

	friend NC_Prog_Block_API nc_block_matrix33 operator*(nc_block bl, nc_block_matrix33 mat_in1);

	friend NC_Prog_Block_API nc_block_matrix33 RotX(nc_block);

	friend NC_Prog_Block_API nc_block_matrix33 RotY(nc_block);

	friend NC_Prog_Block_API nc_block_matrix33 RotZ(nc_block);
};

class NC_Prog_Block_API nc_block_vec3
{
public:
	nb_NC_block_vec3* block_vec;

public:
	~nc_block_vec3();
	
public:
	nc_block_vec3();
	nc_block_vec3(nc_block_vec3&);
public:
	nc_block_vec3(nb_NC_block_vec3&);

public:
	void replace(nc_block_vec3);

	//设置元素程序块，将输入程序块挂在矩阵指定位置上
	void set_nc_Block(int i, nc_block block_in);

public:
	//访问元素
	nc_block operator() (int i);
	//向量相加
	nc_block_vec3 operator+(nc_block_vec3 vec);
	//向量相加
	nc_block_vec3 operator+(vec3 vec);
	//向量相减
	nc_block_vec3 operator-(nc_block_vec3 vec);
	//向量相减
	nc_block_vec3 operator-(vec3 vec);
	//向量乘数
	nc_block_vec3 operator*(double& dou);
	//向量乘数
	nc_block_vec3 operator*(nc_block bl);

	nc_block& operator=(nc_block_vec3 vec);

	nc_block& operator=(vec3 vec);

	friend class nc_block_matrix33;
	friend class nc_block;

	friend NC_Prog_Block_API nc_block_vec3& new_BL_Vec();

	friend NC_Prog_Block_API nc_block_vec3& new_uninit_BL_Vec();

	//向量相加
	friend NC_Prog_Block_API nc_block_vec3 operator+(vec3 vec, nc_block_vec3 vec1);

	//向量相减
	friend NC_Prog_Block_API nc_block_vec3 operator-(vec3 vec, nc_block_vec3 vec1);

	//数乘向量
	friend NC_Prog_Block_API nc_block_vec3 operator*(double dou, nc_block_vec3 vec1);

	//数乘向量
	friend NC_Prog_Block_API nc_block_vec3 operator*(nc_block dou, nc_block_vec3 vec1);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, nc_block_vec3 vec1);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(vec3 vec, nc_block_vec3 vec1);

	//向量点乘
	friend NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, vec3 vec1);

	//向量叉乘
	friend NC_Prog_Block_API nc_block_vec3 cross(nc_block_vec3 vec, nc_block_vec3 vec1);

	//向量叉乘
	friend NC_Prog_Block_API nc_block_vec3 cross(vec3 vec, nc_block_vec3 vec1);

	//向量叉乘
	friend NC_Prog_Block_API nc_block_vec3 cross(nc_block_vec3 vec, vec3 vec1);

	friend NC_Prog_Block_API nc_block_vec3 operator*(mat33 mat_in, nc_block_vec3 vec_in);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, nc_block_vec3 vec2);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(vec3 vec1, nc_block_vec3 vec2);

	//两向量夹角 生成code
	friend NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, vec3 vec2);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, nc_block_vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, vec3 vec3, nc_block ans);

	//a到b绕c的转角，c需要垂直于a，b
	friend NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

	friend NC_Prog_Block_API nc_block norm(nc_block_vec3);

	friend NC_Prog_Block_API nc_block_vec3 normalise(nc_block_vec3);

};

//接口函数

#pragma region 变量生成

// 申请变量函数 - 单程序块
//向变量管理器申请变量
NC_Prog_Block_API nc_block& new_BL_Block();

//申请变量函数-向量程序块
//向变量管理器申请变量
NC_Prog_Block_API nc_block_vec3& new_BL_Vec();

NC_Prog_Block_API nc_block_vec3& new_uninit_BL_Vec();

NC_Prog_Block_API nc_block_matrix33& new_uninit_BL_Mat();

//申请变量函数-矩阵程序块
//向变量管理器申请变量
NC_Prog_Block_API nc_block_matrix33& new_BL_Mat();

//申请指定变量 0：@    1:#
NC_Prog_Block_API nc_block BL_Block(int type, int no);

//生成@ 变量 new的区别在于is_BL_now为true
NC_Prog_Block_API nc_block& new_BL(int no);

//生成@ 变量 new的区别在于is_BL_now为true
NC_Prog_Block_API nc_block& new_BL(nc_block block);

//生成@ 变量
NC_Prog_Block_API nc_block BL(int no);

//生成@ 变量
NC_Prog_Block_API nc_block BL(nc_block no);

//子程序开始
void NC_Prog_Block_API ProBegin();

//子程序结束
void NC_Prog_Block_API ProEnd();

#pragma endregion

#pragma region 函数计算

NC_Prog_Block_API nc_block FuHao(nc_block);
NC_Prog_Block_API nc_block abs(nc_block);
NC_Prog_Block_API nc_block acos(nc_block);
NC_Prog_Block_API nc_block asin(nc_block);
NC_Prog_Block_API nc_block atan(nc_block);
NC_Prog_Block_API nc_block cos(nc_block);
NC_Prog_Block_API nc_block sin(nc_block);
NC_Prog_Block_API nc_block tan(nc_block);
NC_Prog_Block_API nc_block ceil(nc_block);
NC_Prog_Block_API nc_block floor(nc_block);
NC_Prog_Block_API nc_block round(nc_block);
NC_Prog_Block_API nc_block exp(nc_block);
NC_Prog_Block_API nc_block ln(nc_block);
NC_Prog_Block_API nc_block sqrt(nc_block);
NC_Prog_Block_API nc_block max(nc_block, nc_block);
NC_Prog_Block_API nc_block min(nc_block, nc_block);
NC_Prog_Block_API nc_block pow(nc_block, nc_block);
NC_Prog_Block_API nc_block ChangShu(double d);

#pragma endregion

#pragma region 运算符重载

//非
NC_Prog_Block_API nc_block operator!(nc_block);

//-
NC_Prog_Block_API nc_block operator-(double d_in, nc_block block_in);

//+
NC_Prog_Block_API nc_block operator+(double d_in, nc_block block_in);

//*
NC_Prog_Block_API nc_block operator*(double d_in, nc_block block_in);

//除
NC_Prog_Block_API nc_block operator/(double d_in, nc_block block_in);

//%
NC_Prog_Block_API nc_block operator%(double d_in, nc_block block_in);

//<
NC_Prog_Block_API nc_block operator<(double d_in, nc_block block_in);

//>
NC_Prog_Block_API nc_block operator>(double d_in, nc_block block_in);

//<=
NC_Prog_Block_API nc_block operator<=(double d_in, nc_block block_in);

//>=
NC_Prog_Block_API nc_block operator>=(double d_in, nc_block block_in);

//==
NC_Prog_Block_API nc_block operator==(double d_in, nc_block block_in);

//!=
NC_Prog_Block_API nc_block operator!=(double d_in, nc_block block_in);

//乘号
NC_Prog_Block_API nc_block operator*(nc_block block_in1, nc_block block_in2);

NC_Prog_Block_API nc_block operator-(nc_block block_in1, nc_block block_in2);

//减号
NC_Prog_Block_API nc_block operator-(nc_block block_in1, double d_in);

//加号
NC_Prog_Block_API nc_block operator+(nc_block block_in1, nc_block block_in);

//加号
NC_Prog_Block_API nc_block operator+(nc_block block_in1, double d_in);

////乘号
//NC_Prog_Block_API nc_block& operator*(nc_block block_in);

//乘号
NC_Prog_Block_API nc_block operator*(nc_block block_in1, double d_in);

//除号
NC_Prog_Block_API nc_block operator/(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator/(nc_block block_in1, double d_in);

//求模
NC_Prog_Block_API nc_block operator%(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator%(nc_block block_in1, double d_in);

//<
NC_Prog_Block_API nc_block operator<(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator<(nc_block block_in1, double d_in);

//>
NC_Prog_Block_API nc_block operator>(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator>(nc_block block_in1, double d_in);

//<=
NC_Prog_Block_API nc_block operator<=(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator<=(nc_block block_in1, double d_in);

//>=
NC_Prog_Block_API nc_block operator>=(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator>=(nc_block block_in1, double d_in);

//==
NC_Prog_Block_API nc_block operator==(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator==(nc_block block_in1, double d_in);

//!=
NC_Prog_Block_API nc_block operator!=(nc_block block_in1, nc_block block_in);

//除号
NC_Prog_Block_API nc_block operator!=(nc_block block_in1, double d_in);

//&&
NC_Prog_Block_API nc_block operator&&(nc_block block_in1, nc_block block_in);

//^
NC_Prog_Block_API nc_block operator^(nc_block block_in1, nc_block block_in);

//||
NC_Prog_Block_API nc_block operator||(nc_block block_in1, nc_block block_in);

////=
//NC_Prog_Block_API nc_block& operator=(nc_block block_in1, nc_block block_in);
//
////=
//NC_Prog_Block_API nc_block& operator=(nc_block block_in1, double d_in);


NC_Prog_Block_API nc_block operator<<(nc_block& block_in1, nc_block block_in);

//2025.2.18
NC_Prog_Block_API void operator>>(std::ofstream& oss, nc_block block_in);

//NC_Prog_Block_API string operator<<(string ans, nc_block& block_in);

//= 这个函数有两个
NC_Prog_Block_API nc_block SET_VALUE(nc_block zuobian, nc_block youbian);

#pragma endregion

#pragma region M代码

//M00
NC_Prog_Block_API nc_block M00();

//M01
NC_Prog_Block_API nc_block M01();

//M02
NC_Prog_Block_API nc_block M02();

//M03
NC_Prog_Block_API nc_block M03();

//M04
NC_Prog_Block_API nc_block M04();

//M05
NC_Prog_Block_API nc_block M05();

//M06
NC_Prog_Block_API nc_block M06(int tool_using, int in_sl_pos_on_slz);

//M08
NC_Prog_Block_API nc_block M08();

//M09
NC_Prog_Block_API nc_block M09();

//M30
NC_Prog_Block_API nc_block M30();

//M13
NC_Prog_Block_API nc_block M13();

//M14
NC_Prog_Block_API nc_block M14();

//M15
NC_Prog_Block_API nc_block M15();
#pragma endregion

#pragma region G代码

//G00
NC_Prog_Block_API nc_block G00();

//G01
NC_Prog_Block_API nc_block G01();

//G04
NC_Prog_Block_API nc_block G04();

//G52
NC_Prog_Block_API nc_block G52();

//G53
NC_Prog_Block_API nc_block G53();

//G54
NC_Prog_Block_API nc_block G54();

//G55
NC_Prog_Block_API nc_block G55();

//G56
NC_Prog_Block_API nc_block G56();

//G57
NC_Prog_Block_API nc_block G57();

//G58
NC_Prog_Block_API nc_block G58();

//G59
NC_Prog_Block_API nc_block G59();

//G90
NC_Prog_Block_API nc_block G90();

//Set_RGB
NC_Prog_Block_API nc_block Set_RGB(int color);

//WAIT
NC_Prog_Block_API nc_block WAIT();

//M98
NC_Prog_Block_API nc_block M98(nc_block targer_block, int name_num);

//M99
NC_Prog_Block_API nc_block M99();

//S_speed
NC_Prog_Block_API nc_block S_speed(int s);

//S2_speed
NC_Prog_Block_API nc_block S2_speed(int s);

//G91
NC_Prog_Block_API nc_block G91();

#pragma endregion

#pragma region 运动控制

//!=
NC_Prog_Block_API nc_block F(double d_in);

//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block X_Y_Z_A_C(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c
);

//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block X_Y_Z_A_C(
	double& x,
	double& y,
	double& z,
	double& a,
	double& c
);

//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block X_Y_Z_A_C_F(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c,
	nc_block f
);

NC_Prog_Block_API nc_block X_Y_Z_A_C_F(
	double& x,
	double& y,
	double& z,
	double& a,
	double& c,
	double& f
);

//运动生成
NC_Prog_Block_API nc_block X(nc_block x);

//运动生成
NC_Prog_Block_API nc_block Y(nc_block y);

//运动生成
NC_Prog_Block_API nc_block Z(nc_block z);

//运动生成
NC_Prog_Block_API nc_block A(nc_block a);

//运动生成
NC_Prog_Block_API nc_block C(nc_block c);

//运动生成
NC_Prog_Block_API nc_block X_Y_Z(nc_block x, nc_block y, nc_block z);

//运动生成
NC_Prog_Block_API nc_block X_F(nc_block x, nc_block f);

//运动生成
NC_Prog_Block_API nc_block Y_F(nc_block y, nc_block f);

//运动生成
NC_Prog_Block_API nc_block Z_F(nc_block z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block A_F(nc_block a, nc_block f);

//运动生成
NC_Prog_Block_API nc_block C_F(nc_block c, nc_block f);

//运动生成
NC_Prog_Block_API nc_block X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

#pragma region G31基础

//基础G31，其他G31调用此函数
NC_Prog_Block_API nc_block G31_X_Y_Z_A_C(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c
);

//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block G31_X_Y_Z_A_C_F(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c,
	nc_block f
);

#pragma endregion

#pragma region G31 单轴 不带F

//运动生成
NC_Prog_Block_API nc_block G31_X(nc_block x);

//运动生成
NC_Prog_Block_API nc_block G31_Y(nc_block y);

//运动生成
NC_Prog_Block_API nc_block G31_Z(nc_block z);

//运动生成
NC_Prog_Block_API nc_block G31_A(nc_block a);

//运动生成
NC_Prog_Block_API nc_block G31_C(nc_block c);

//运动生成
NC_Prog_Block_API nc_block G31_X(double x);

//运动生成
NC_Prog_Block_API nc_block G31_Y(double y);

//运动生成
NC_Prog_Block_API nc_block G31_Z(double z);

//运动生成
NC_Prog_Block_API nc_block G31_A(double a);

//运动生成
NC_Prog_Block_API nc_block G31_C(double c);

#pragma endregion

#pragma region G31 单轴带F

//运动生成
NC_Prog_Block_API nc_block G31_X_F(nc_block x, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_Y_F(nc_block y, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_Z_F(nc_block z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_A_F(nc_block a, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_C_F(nc_block c, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_X_F(double x, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_Y_F(double y, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_Z_F(double z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_A_F(double a, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_C_F(double c, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_X_F(nc_block x, double f);

//运动生成
NC_Prog_Block_API nc_block G31_Y_F(nc_block y, double f);

//运动生成
NC_Prog_Block_API nc_block G31_Z_F(nc_block z, double f);

//运动生成
NC_Prog_Block_API nc_block G31_A_F(nc_block a, double f);

//运动生成
NC_Prog_Block_API nc_block G31_C_F(nc_block c, double f);

//运动生成
NC_Prog_Block_API nc_block G31_X_F(double x, double f);

//运动生成
NC_Prog_Block_API nc_block G31_Y_F(double y, double f);

//运动生成
NC_Prog_Block_API nc_block G31_Z_F(double z, double f);

//运动生成
NC_Prog_Block_API nc_block G31_A_F(double a, double f);

//运动生成
NC_Prog_Block_API nc_block G31_C_F(double c, double f);
#pragma endregion

#pragma region G31 三平动轴

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z(nc_block x, nc_block y, nc_block z);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z(double x, double y, double z);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z(nc_block_vec3 point);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(nc_block x, nc_block y, nc_block z, double f);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(nc_block_vec3 point, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(nc_block_vec3 point, double f);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(double x, double y, double z, double f);

//运动生成
NC_Prog_Block_API nc_block G31_X_Y_Z_F(vec3 point, double f);

#pragma endregion

#pragma region G01 基础

//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block G01_X_Y_Z_A_C(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c
);

NC_Prog_Block_API nc_block G01_X_Y_Z_A_C(
	double x,
	double y,
	double z,
	double a,
	double c
);


//基础运动生成，其他运动调用此函数
NC_Prog_Block_API nc_block G01_X_Y_Z_A_C_F(
	nc_block x,
	nc_block y,
	nc_block z,
	nc_block a,
	nc_block c,
	nc_block f
);

NC_Prog_Block_API nc_block G01_X_Y_Z_A_C_F(
	double x,
	double y,
	double z,
	double a,
	double c,
	double f
);

#pragma endregion

#pragma region G01 单轴 带F

//运动生成
NC_Prog_Block_API nc_block G01_X_F(nc_block x, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_Y_F(nc_block y, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_Z_F(nc_block z, nc_block f);
//
////运动生成
//NC_Prog_Block_API nc_block G01_A_F(nc_block& a, nc_block& f);

//运动生成
NC_Prog_Block_API nc_block G01_C_F(nc_block c, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_X_F(nc_block x, double f);

//运动生成
NC_Prog_Block_API nc_block G01_Y_F(nc_block y, double f);

//运动生成
NC_Prog_Block_API nc_block G01_Z_F(nc_block z, double f);
//
////运动生成
//NC_Prog_Block_API nc_block G01_A_F(nc_block& a, double f);

//运动生成
NC_Prog_Block_API nc_block G01_C_F(nc_block c, double f);

//运动生成
NC_Prog_Block_API nc_block G01_X_F(double x, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_Y_F(double y, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_Z_F(double z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_A_F(double a, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_C_F(double c, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_X_F(double x, double f);

//运动生成
NC_Prog_Block_API nc_block G01_Y_F(double y, double f);

//运动生成
NC_Prog_Block_API nc_block G01_Z_F(double z, double f);

//运动生成
NC_Prog_Block_API nc_block G01_A_F(double a, double f);

//运动生成
NC_Prog_Block_API nc_block G01_C_F(double c, double f);
#pragma endregion

#pragma region G01 三平动轴

//运动生成
NC_Prog_Block_API nc_block G01_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_X_Y_Z_F(nc_block_vec3 point, nc_block f);

//运动生成
NC_Prog_Block_API nc_block G01_X_Y_Z_F(nc_block_vec3 point, double f);

//运动生成
NC_Prog_Block_API nc_block G01_X_Y_Z_F(vec3 point, double f);

#pragma endregion

#pragma endregion

#pragma region 逻辑结构

NC_Prog_Block_API nc_block BREAK();

NC_Prog_Block_API nc_block WHILE_K(nc_block tiaojian, nc_block xunhuanti);

NC_Prog_Block_API nc_block IF_K(nc_block tiaojian, nc_block zhuti);

NC_Prog_Block_API nc_block IF_ELSE_K(
	nc_block tiaojian,
	nc_block zhuti1,
	nc_block zhuti2
);

NC_Prog_Block_API nc_block IF_ELSEIF_ELSE_K(
	nc_block tiaojian1, nc_block zhuti1,
	nc_block tiaojian2, nc_block zhuti2,
	nc_block zhuti3
);

NC_Prog_Block_API nc_block Process_K(int i);
#pragma endregion

#pragma region 程序块矩阵函数

//向量相加
NC_Prog_Block_API nc_block_vec3 operator+(vec3 vec, nc_block_vec3 vec1);

//向量相减
NC_Prog_Block_API nc_block_vec3 operator-(vec3 vec, nc_block_vec3 vec1);

//向量点乘
NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, nc_block_vec3 vec1);

//向量点乘
NC_Prog_Block_API nc_block dot(vec3 vec, nc_block_vec3 vec1);

//向量点乘
NC_Prog_Block_API nc_block dot(nc_block_vec3 vec, vec3 vec1);

//向量叉乘
NC_Prog_Block_API nc_block_vec3 cross(nc_block_vec3 vec, nc_block_vec3 vec1);

//向量叉乘
NC_Prog_Block_API nc_block_vec3 cross(vec3 vec, nc_block_vec3 vec1);

//向量叉乘
NC_Prog_Block_API nc_block_vec3 cross(nc_block_vec3 vec, vec3 vec1);

//矩阵乘矩阵
NC_Prog_Block_API nc_block_matrix33 operator*(mat33 mat_in, nc_block_matrix33 mat_in1);

//矩阵乘矩阵
NC_Prog_Block_API nc_block_vec3 operator*(mat33 mat_in, nc_block_vec3 vec_in);

//两向量夹角 生成code
NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, nc_block_vec3 vec2);

//两向量夹角 生成code
NC_Prog_Block_API nc_block Angle_between_2_vec(vec3 vec1, nc_block_vec3 vec2);

//两向量夹角 生成code
NC_Prog_Block_API nc_block Angle_between_2_vec(nc_block_vec3 vec1, vec3 vec2);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, nc_block_vec3 vec3, nc_block ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, vec3 vec3, nc_block ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_Block_API nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans);

#pragma endregion

#pragma region 常用特殊矩阵函数

NC_Prog_Block_API nc_block_matrix33 RotX(nc_block);

NC_Prog_Block_API nc_block_matrix33 RotY(nc_block);

NC_Prog_Block_API nc_block_matrix33 RotZ(nc_block);

NC_Prog_Block_API nc_block norm(nc_block_vec3);

NC_Prog_Block_API nc_block_vec3 normalise(nc_block_vec3);

#pragma endregion

#pragma region 文件解读函数
//NC_Prog_Block_API nc_block Recover_block();
//NC_Prog_Block_API bool reset_block();
//NC_Prog_Block_API bool Recover_nc_code();
#pragma endregion
