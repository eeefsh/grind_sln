#include "pch.h"
#define NC_Prog_nb_NC_Block_matrix_EXPORTS
#include "nb_block_functions_2.h"

nb_NC_block_matrix33& operator*(mat33& mat_in, nb_NC_block_matrix33& mat_in1)
{
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					mat_in(i, 0) * mat_in1(0, j)
					+ mat_in(i, 1) * mat_in1(1, j)
					+ mat_in(i, 2) * mat_in1(2, j)
					);
		}
	}
	delete_Temp_mat(mat_in1);
	return *ptr;
}

nb_NC_block_vec3& operator*(mat33& mat_in, nb_NC_block_vec3& vec_in)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &(mat_in(0, 0) * vec_in(0) + mat_in(0, 1) * vec_in(1) + mat_in(0, 2) * vec_in(2));
	ptr->data[1] = &(mat_in(1, 0) * vec_in(0) + mat_in(1, 1) * vec_in(1) + mat_in(1, 2) * vec_in(2));
	ptr->data[2] = &(mat_in(2, 0) * vec_in(0) + mat_in(2, 1) * vec_in(1) + mat_in(2, 2) * vec_in(2));
	delete_Temp_mat(vec_in);
	return *ptr;
}

nb_NC_block& nb_Angle_between_2_vec(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2)
{
	nb_NC_block& a = nb_acos(nb_dot(vec1, vec2));
	delete_Temp_mat(vec1);
	delete_Temp_mat(vec2);
	return a;
}

nb_NC_block& nb_Angle_between_2_vec(vec3& vec1, nb_NC_block_vec3& vec2)
{
	nb_NC_block& a = nb_acos(nb_dot(vec1, vec2));
	delete_Temp_mat(vec2);
	return a;
}

nb_NC_block& nb_Angle_between_2_vec(nb_NC_block_vec3& vec1, vec3& vec2)
{
	nb_NC_block& a = nb_acos(nb_dot(vec1, vec2));
	delete_Temp_mat(vec1);
	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假 
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);
	delete_Temp_mat(vec1);
	delete_Temp_mat(vec2);
	delete_Temp_mat(vec3);
	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(vec3& vec1, nb_NC_block_vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);

	delete_Temp_mat(vec2);
	delete_Temp_mat(vec3);
	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, vec3& vec2, nb_NC_block_vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);
	delete_Temp_mat(vec1);
	delete_Temp_mat(vec3);
	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, nb_NC_block_vec3& vec2, vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);
	delete_Temp_mat(vec1);
	delete_Temp_mat(vec2);

	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(nb_NC_block_vec3& vec1, vec3& vec2, vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);
	delete_Temp_mat(vec1);

	return a;
}

nb_NC_block& nb_Angle_from_a_to_b_around_c(vec3& vec1, nb_NC_block_vec3& vec2, vec3& vec3, nb_NC_block& ans)
{
	nb_NC_block& a =
		nb_IF_ELSE_K
		(
			//条件
			nb_dot(nb_cross(vec1, vec2), vec3) > 0.0,
			//真
			ans = nb_Angle_between_2_vec(vec1, vec2),
			//假
			ans = -nb_Angle_between_2_vec(vec1, vec2)
		);
	delete_Temp_mat(vec2);
	return a;
}

nb_NC_block_matrix33& nb_RotX(nb_NC_block& block_in)
{
	nb_NC_block_matrix33* ls_mat = new nb_NC_block_matrix33;
	//row1
	ls_mat->data[0] = &nb_ChangShu(1.0);
	ls_mat->data[1] = &nb_ChangShu(0.0);
	ls_mat->data[2] = &nb_ChangShu(0.0);

	//row2
	ls_mat->data[3] = &nb_ChangShu(0.0);
	ls_mat->data[4] = &nb_cos(block_in);
	ls_mat->data[5] = &(-nb_sin(block_in));

	//row3
	ls_mat->data[6] = &nb_ChangShu(0.0);
	ls_mat->data[7] = &nb_sin(block_in);
	ls_mat->data[8] = &nb_cos(block_in);

	nb_set_mat_father(ls_mat, nb_NC_block::father_block);

	return *ls_mat;
}

nb_NC_block_matrix33& nb_RotY(nb_NC_block& block_in)
{
	nb_NC_block_matrix33* ls_mat = new nb_NC_block_matrix33;
	//row1
	ls_mat->data[0] = &nb_cos(block_in);
	ls_mat->data[1] = &nb_ChangShu(0.0);
	ls_mat->data[2] = &nb_sin(block_in);

	//row2
	ls_mat->data[3] = &nb_ChangShu(0.0);
	ls_mat->data[4] = &nb_ChangShu(1.0);
	ls_mat->data[5] = &nb_ChangShu(0.0);

	//row3
	ls_mat->data[6] = &(-nb_sin(block_in));
	ls_mat->data[7] = &nb_ChangShu(0.0);
	ls_mat->data[8] = &nb_cos(block_in);

	nb_set_mat_father(ls_mat, nb_NC_block::father_block);

	return *ls_mat;
}

nb_NC_block_matrix33& nb_RotZ(nb_NC_block& block_in)
{
	nb_NC_block_matrix33* ls_mat = new nb_NC_block_matrix33;
	//row1
	ls_mat->data[0] = &nb_cos(block_in);
	ls_mat->data[1] = &(-nb_sin(block_in));
	ls_mat->data[2] = &nb_ChangShu(0.0);

	//row2
	ls_mat->data[3] = &nb_sin(block_in);
	ls_mat->data[4] = &nb_cos(block_in);
	ls_mat->data[5] = &nb_ChangShu(0.0);

	//row3
	ls_mat->data[6] = &nb_ChangShu(0.0);
	ls_mat->data[7] = &nb_ChangShu(0.0);
	ls_mat->data[8] = &nb_ChangShu(1.0);

	nb_set_mat_father(ls_mat, nb_NC_block::father_block);

	return *ls_mat;
}

nb_NC_block& nb_norm(nb_NC_block_vec3& vec_in)
{
	nb_NC_block& a = nb_sqrt(
		vec_in(0) * vec_in(0)
		+ vec_in(1) * vec_in(1)
		+ vec_in(2) * vec_in(2)
	);
	delete_Temp_mat(vec_in);
	return a;
}

nb_NC_block_vec3& nb_normalise(nb_NC_block_vec3& vec_in)
{
	nb_NC_block_vec3* ls_vec = new nb_NC_block_vec3;
	(*ls_vec)(0) = vec_in(0) / nb_norm(vec_in);
	(*ls_vec)(1) = vec_in(1) / nb_norm(vec_in);
	(*ls_vec)(2) = vec_in(2) / nb_norm(vec_in);

	nb_set_vec_father(ls_vec, nb_NC_block::father_block);
	delete_Temp_mat(vec_in);
	return *ls_vec;
}

void nb_set_vec_father(nb_NC_block_vec3* p_vec, nb_NC_block& father)
{
	for (int i = 0; i < 3; i++)
	{
		p_vec->data[i]->set_father(father);
	}
}

nb_NC_block_vec3& operator*(double& db, nb_NC_block_vec3& cvec)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((cvec)(i)*db);
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(cvec);
	return *ptr;
}

nb_NC_block_vec3& operator*(nb_NC_block& bl, nb_NC_block_vec3& cvec)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((cvec)(i)*bl);
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(cvec);
	return *ptr;
}

void nb_set_mat_father(nb_NC_block_matrix33* p_mat, nb_NC_block& father)
{
	for (int i = 0; i < 9; i++)
	{
		p_mat->data[i]->set_father(father);
	}
}

nb_NC_block_matrix33& operator*(double& db, nb_NC_block_matrix33& cmat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(cmat)(i, j) * db
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(cmat);
	return *ptr;

}

nb_NC_block_matrix33& operator*(nb_NC_block& bl, nb_NC_block_matrix33& cmat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(cmat)(i, j) * bl
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(cmat);
	return *ptr;
}

void delete_Temp_mat(nb_NC_block_matrix33& p_mat)
{
	if (p_mat.isTemp())
	{
		delete& p_mat;
	}
}

void delete_Temp_mat(nb_NC_block_vec3& p_vec)
{
	if (p_vec.isTemp())
	{
		delete& p_vec;
	}
}

nb_NC_block_vec3& nb_new_BL_Vec()
{
	nb_NC_block_vec3* a = new nb_NC_block_vec3(BH_BL_A);
	a->is_BL_now = true;
	return *a;
}

nb_NC_block_vec3& nb_new_uninit_BL_Vec()
{
	return *(new nb_NC_block_vec3(0));
}

nb_NC_block_matrix33& nb_new_uninit_BL_Mat()
{
	return *(new nb_NC_block_matrix33(0));
}

nb_NC_block_matrix33& nb_new_BL_Mat()
{
	nb_NC_block_matrix33* a = new nb_NC_block_matrix33(BH_BL_A);
	a->is_BL_now = true;
	return *a;
}

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator+(nb_NC_block_matrix33& block_in, nb_NC_block_matrix33&ls_mat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] = &((block_in)(i, j) + (ls_mat(i, j)));
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	delete_Temp_mat(ls_mat);
	return *ptr;
}

NC_Prog_nb_NC_Block_matrix_API nb_NC_block_matrix33& operator+(nb_NC_block_matrix33& block_in, mat33& ls_mat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] = &((block_in)(i, j) + (ls_mat(i, j)));
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator*(nb_NC_block_matrix33& block_in, nb_NC_block_vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &((block_in)(0, 0) * ls_vec(0) + (block_in)(0, 1) * ls_vec(1) + (block_in)(0, 2) * ls_vec(2));
	ptr->data[1] = &((block_in)(1, 0) * ls_vec(0) + (block_in)(1, 1) * ls_vec(1) + (block_in)(1, 2) * ls_vec(2));
	ptr->data[2] = &((block_in)(2, 0) * ls_vec(0) + (block_in)(2, 1) * ls_vec(1) + (block_in)(2, 2) * ls_vec(2));
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(ls_vec);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator*(nb_NC_block_matrix33& block_in, vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &((block_in)(0, 0) * ls_vec(0) + (block_in)(0, 1) * ls_vec(1) + (block_in)(0, 2) * ls_vec(2));
	ptr->data[1] = &((block_in)(1, 0) * ls_vec(0) + (block_in)(1, 1) * ls_vec(1) + (block_in)(1, 2) * ls_vec(2));
	ptr->data[2] = &((block_in)(2, 0) * ls_vec(0) + (block_in)(2, 1) * ls_vec(1) + (block_in)(2, 2) * ls_vec(2));
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_matrix33& operator*(nb_NC_block_matrix33& block_in, nb_NC_block_matrix33& ls_mat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(block_in)(i, 0) * ls_mat(0, j)
					+ (block_in)(i, 1) * ls_mat(1, j)
					+ (block_in)(i, 2) * ls_mat(2, j)
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(ls_mat);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_matrix33& operator*(nb_NC_block_matrix33& block_in, mat33& ls_mat)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(block_in)(i, 0) * ls_mat(0, j)
					+ (block_in)(i, 1) * ls_mat(1, j)
					+ (block_in)(i, 2) * ls_mat(2, j)
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_matrix33& operator*(nb_NC_block_matrix33& block_in, nb_NC_block& bl)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(block_in)(i, j) * bl
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_matrix33& operator*(nb_NC_block_matrix33& block_in, double& dou)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_matrix33* ptr = new nb_NC_block_matrix33;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ptr->data[i * 3 + j] =
				&(
					(block_in)(i, j) * dou
					);
		}
	}
	nb_set_mat_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator+(nb_NC_block_vec3& block_in, nb_NC_block_vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)+(ls_vec(i)));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	delete_Temp_mat(ls_vec);
	return *ptr;
}

nb_NC_block_vec3& operator+(nb_NC_block_vec3& block_in, vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)+ls_vec(i));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);

	return *ptr;
}

nb_NC_block_vec3& operator-(nb_NC_block_vec3& block_in, nb_NC_block_vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)-(ls_vec(i)));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	delete_Temp_mat(ls_vec);
	return *ptr;
}

nb_NC_block_vec3& operator-(nb_NC_block_vec3& block_in, vec3& ls_vec)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)-ls_vec(i));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator*(nb_NC_block_vec3& block_in, nb_NC_block& bl)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)*bl);
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator*(nb_NC_block_vec3& block_in, double& dou)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &((block_in)(i)*dou);
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(block_in);
	return *ptr;
}

nb_NC_block_vec3& operator+(vec3& vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &(vec(i) + vec1(i));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block_vec3& operator-(vec3& vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int i = 0; i < 3; i++)
	{
		ptr->data[i] = &(vec(i) - vec1(i));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block& nb_dot(nb_NC_block_vec3& vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block* ptr = new nb_NC_block;
	ptr = &(
		vec(0) * vec1(0)
		+ vec(1) * vec1(1)
		+ vec(2) * vec1(2)
		);
	delete_Temp_mat(vec);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block& nb_dot(vec3 vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block* ptr = new nb_NC_block;
	ptr = &(
		vec(0) * vec1(0)
		+ vec(1) * vec1(1)
		+ vec(2) * vec1(2)
		);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block& nb_dot(nb_NC_block_vec3& vec, vec3 vec1)
{
	nb_NC_block* ptr = new nb_NC_block;
	ptr = &(
		vec(0) * vec1(0)
		+ vec(1) * vec1(1)
		+ vec(2) * vec1(2)
		);
	delete_Temp_mat(vec);
	return *ptr;
}

nb_NC_block_vec3& nb_cross(nb_NC_block_vec3& vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &(vec(1) * vec1(2) - vec(2) * vec1(1));
	ptr->data[1] = &(vec(2) * vec1(0) - vec(0) * vec1(2));
	ptr->data[2] = &(vec(0) * vec1(1) - vec(1) * vec1(0));
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(vec);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block_vec3& nb_cross(vec3 vec, nb_NC_block_vec3& vec1)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &(vec(1) * vec1(2) - vec(2) * vec1(1));
	ptr->data[1] = &(vec(2) * vec1(0) - vec(0) * vec1(2));
	ptr->data[2] = &(vec(0) * vec1(1) - vec(1) * vec1(0));
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(vec1);
	return *ptr;
}

nb_NC_block_vec3& nb_cross(nb_NC_block_vec3& vec, vec3 vec1)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	ptr->data[0] = &(vec(1) * vec1(2) - vec(2) * vec1(1));
	ptr->data[1] = &(vec(2) * vec1(0) - vec(0) * vec1(2));
	ptr->data[2] = &(vec(0) * vec1(1) - vec(1) * vec1(0));
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(vec);
	return *ptr;
}