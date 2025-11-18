#pragma once
#include"manager_h/xt_armadillo_settings.h"
#include "manager_h\MA_031001_NC_Prog_nb_NC_Block.h"


#ifdef NC_Prog_nb_NC_Block_matrix_EXPORTS
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllimport)
#endif

class nb_NC_block_vec3;

//程序块矩阵3*3
class NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33
{
public:
	nb_NC_block* data[9];
	//$$$只有变量矩阵不是临时矩阵$$$
	//目的：计算时析构常量的矩阵，因为常量矩阵不需要记录，只是用于本次计算
	//变量矩阵以后还要用，所以需要保留
	//在计算输入时，可能是变量矩阵，也可能是常量矩阵，因此需要增加此变量用于动态判断
	//要注意：默认构造函数生成临时矩阵，  带有type参数的构造函数生成非临时矩阵
	bool is_temp_mat;
	bool is_BL_now = false;
	bool need_release = false;

public:
	//生成一个空的程序块矩阵
	nb_NC_block_matrix33();

	//若type==BH_BL_A或BH_BL_JIN则是新建变量矩阵
	nb_NC_block_matrix33(int type);

	nb_NC_block_matrix33(nb_NC_block_matrix33& A);

	~nb_NC_block_matrix33();

//20231206-ZYW
public:
	nb_NC_block_matrix33* new_copy();
public:
	bool isTemp();

	//访问元素
	nb_NC_block& operator()(int i, int j);
	//访问列
	nb_NC_block_vec3& col(int i);
	//设置元素程序块，将输入程序块挂在矩阵指定位置上
	void set_NC_Block(int i, int j, nb_NC_block& block_in);

	nb_NC_block& operator=(nb_NC_block_matrix33& mat);

	nb_NC_block& operator=(mat33 mat_in2);

public:
	friend NC_Prog_nb_NC_Block_matrix_API void nb_set_mat_father(nb_NC_block_matrix33* p_mat, nb_NC_block& father);
	friend NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(double& db, nb_NC_block_matrix33& cvec);
	friend NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(nb_NC_block& bl, nb_NC_block_matrix33& cvec);
};
