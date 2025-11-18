#pragma once
#ifdef NC_Prog_nb_NC_Block_matrix_EXPORTS
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllimport)
#endif
#include"manager_h/xt_armadillo_settings.h"
#include "manager_h\MA_031001_NC_Prog_nb_NC_Block.h"


//程序块向量3*1
class NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3
{
public:
	nb_NC_block* data[3];
	//$$$只有变量矩阵不是临时矩阵$$$
	//目的：计算时析构常量的矩阵，因为常量矩阵不需要记录，只是用于本次计算
	//变量矩阵以后还要用，所以需要保留
	//在计算输入时，可能是变量矩阵，也可能是常量矩阵，因此需要增加此变量用于动态判断
	//要注意：默认构造函数生成临时矩阵，  带有type参数的构造函数生成非临时矩阵
	bool is_temp_mat;
	bool is_BL_now = false;
	bool need_release = false;

public:
	//生成一个空的程序块向量
	nb_NC_block_vec3();
	//若type==BH_BL_A或BH_BL_JIN则是新建变量矩阵
	nb_NC_block_vec3(int type);

	nb_NC_block_vec3(nb_NC_block_vec3& vec);

	~nb_NC_block_vec3();

	//设置元素程序块，将输入程序块挂在矩阵指定位置上
	void set_NC_Block(int i,nb_NC_block& block_in);
//20231206-ZYW
public:
	nb_NC_block_vec3* new_copy();
public:
	bool isTemp();
	//访问元素
	nb_NC_block& operator() (int i);

	nb_NC_block& operator=(nb_NC_block_vec3& vec);

	nb_NC_block& operator=(vec3 vec);

public:
	friend NC_Prog_nb_NC_Block_matrix_API void nb_set_vec_father(nb_NC_block_vec3* p_vec, nb_NC_block& father);
	friend NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(double& db, nb_NC_block_vec3& cvec);
	friend NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(nb_NC_block& bl, nb_NC_block_vec3& cvec);

}; 