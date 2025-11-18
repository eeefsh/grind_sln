#pragma once
#ifdef NC_Prog_nb_NC_Block_matrix_EXPORTS
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_matrix_API __declspec(dllimport)
#endif

#include "manager_h\MA_031001_NC_Prog_nb_NC_Block.h"

#include "nb_NC_block_matrix33.h"
#include "nb_NC_block_vec3.h"

#pragma once
//大部分需要做接口
#pragma region 程序块生成函数声明

#pragma region 变量生成

//申请变量函数-向量程序块
//向变量管理器申请变量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_new_BL_Vec();

//申请变量函数-向量程序块
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_new_uninit_BL_Vec();

//申请变量函数-向量程序块
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& nb_new_uninit_BL_Mat();

//申请变量函数-矩阵程序块
//向变量管理器申请变量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& nb_new_BL_Mat();


#pragma endregion

#pragma region 程序块矩阵函数
//ZYW-240110
//矩阵加矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator+(nb_NC_block_matrix33&, nb_NC_block_matrix33&);
//矩阵加矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator+(nb_NC_block_matrix33&, mat33&);

//矩阵乘向量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(nb_NC_block_matrix33&, nb_NC_block_vec3&);

//矩阵乘向量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(nb_NC_block_matrix33&, vec3&);

// 矩阵乘矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(nb_NC_block_matrix33&, nb_NC_block_matrix33&);

//矩阵乘矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(nb_NC_block_matrix33&, mat33&);

//矩阵乘变量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(nb_NC_block_matrix33&, nb_NC_block&);

//矩阵乘数
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(nb_NC_block_matrix33&, double&);

//向量相加
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator+(nb_NC_block_vec3&, nb_NC_block_vec3&);

//向量相加
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator+(nb_NC_block_vec3&, vec3&);

//向量相减
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator-(nb_NC_block_vec3&, nb_NC_block_vec3&);

//向量相减
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator-(nb_NC_block_vec3&, vec3&);

//向量乘变量
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(nb_NC_block_vec3&, nb_NC_block&);

//向量乘以数
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(nb_NC_block_vec3&, double&);

//向量相加
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator+(vec3& vec, nb_NC_block_vec3& vec1);

//向量相减
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator-(vec3& vec, nb_NC_block_vec3& vec1);

//向量点乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_dot(nb_NC_block_vec3& vec, nb_NC_block_vec3& vec1);

//向量点乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_dot(vec3 vec, nb_NC_block_vec3& vec1);

//向量点乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_dot(nb_NC_block_vec3& vec, vec3 vec1);

//向量叉乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_cross(nb_NC_block_vec3& vec, nb_NC_block_vec3& vec1);

//向量叉乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_cross(vec3 vec, nb_NC_block_vec3& vec1);

//向量叉乘
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_cross(nb_NC_block_vec3& vec, vec3 vec1);

//矩阵乘矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator*(mat33& mat_in, nb_NC_block_matrix33& mat_in1);

//矩阵乘矩阵
NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& operator*(mat33& mat_in, nb_NC_block_vec3& vec_in);

//两向量夹角 生成code
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_between_2_vec(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2);

//两向量夹角 生成code
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_between_2_vec(vec3& vec1, nb_NC_block_vec3& vec2);

//两向量夹角 生成code
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_between_2_vec(nb_NC_block_vec3& vec1, vec3& vec2);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(vec3& vec1, nb_NC_block_vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2, vec3& vec3, nb_NC_block& ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, vec3& vec2, vec3& vec3, nb_NC_block& ans);

//a到b绕c的转角，c需要垂直于a，b
NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_Angle_from_a_to_b_around_c(vec3& vec1, nb_NC_block_vec3& vec2, vec3& vec3, nb_NC_block& ans);

#pragma endregion

#pragma region 常用特殊矩阵函数

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& nb_RotX(nb_NC_block&);

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& nb_RotY(nb_NC_block&);

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& nb_RotZ(nb_NC_block&);

NC_Prog_nb_NC_Block_matrix_API nb_NC_block& nb_norm(nb_NC_block_vec3&);

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_vec3& nb_normalise(nb_NC_block_vec3&);

#pragma endregion

NC_Prog_nb_NC_Block_matrix_API void nb_set_vec_father(nb_NC_block_vec3* p_vec, nb_NC_block& father);

NC_Prog_nb_NC_Block_matrix_API void nb_set_mat_father(nb_NC_block_matrix33* p_mat, nb_NC_block& father);

NC_Prog_nb_NC_Block_matrix_API void delete_Temp_mat(nb_NC_block_matrix33& p_mat);

NC_Prog_nb_NC_Block_matrix_API void delete_Temp_mat(nb_NC_block_vec3& p_vec);

#pragma endregion

