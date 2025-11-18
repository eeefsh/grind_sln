#include "pch.h"
#define NC_Prog_nb_NC_Block_matrix_EXPORTS
#include "nb_NC_block_matrix33.h"
#include "nb_block_functions_2.h"

nb_NC_block_matrix33::nb_NC_block_matrix33()
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = 0;
	}
	is_temp_mat = true;
}

nb_NC_block_matrix33::nb_NC_block_matrix33(int type)
{
	if (type == BH_BL_A || type == BH_BL_JIN)
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = &(nb_new_BL_Block());
			data[i]->set_father(nb_NC_block::father_block);
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = 0;
		}
	}
	is_temp_mat = false;
}

nb_NC_block_matrix33::nb_NC_block_matrix33(nb_NC_block_matrix33& A)
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = A.data[i];
	}
	is_temp_mat = true;
}

nb_NC_block_matrix33::~nb_NC_block_matrix33()
{
	for (int i = 0; i < 9; i++)
	{
		delete data[i];
	}
}
//20231206-ZYW
nb_NC_block_matrix33* nb_NC_block_matrix33::new_copy()
{
	nb_NC_block_matrix33* ans_ptr = new nb_NC_block_matrix33;
	for (size_t i = 0; i < 9; i++)
	{
		ans_ptr->data[i] = this->data[i]->new_copy();
		ans_ptr->data[i]->set_father(nb_NC_block::father_block);
	}
	ans_ptr->is_temp_mat = true;
	return ans_ptr;
}

bool nb_NC_block_matrix33::isTemp()
{
	return is_temp_mat;
}

nb_NC_block& nb_NC_block_matrix33::operator()(int i, int j)
{
	return *data[3 * i + j];
}

nb_NC_block_vec3& nb_NC_block_matrix33::col(int i)
{
	nb_NC_block_vec3* ptr = new nb_NC_block_vec3;
	for (int j = 0; j < 3; j++)
	{
		ptr->data[j] = &((*this)(j, i));
	}
	nb_set_vec_father(ptr, nb_NC_block::father_block);
	delete_Temp_mat(*this);
	return *ptr;
}

void nb_NC_block_matrix33::set_NC_Block(int i, int j, nb_NC_block& block_in)
{
	data[3 * i + j] = &block_in;
	data[3 * i + j]->set_father(nb_NC_block::father_block);
}

nb_NC_block& nb_NC_block_matrix33::operator=(nb_NC_block_matrix33& mat)
{
	nb_NC_block* ptr = &nb_Process_K(0);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*ptr <<((*this)(i, j) = mat(i, j));
		}
	}
	delete_Temp_mat(*this);
	delete_Temp_mat(mat);
	return *ptr;
}

nb_NC_block& nb_NC_block_matrix33::operator=(mat33 mat_in2)
{
	nb_NC_block* ptr = &nb_Process_K(0);

	for (int i = 0; i < 3; i++)
	{
		rowvec3 ls = mat_in2.row(i);
		for (int j = 0; j < 3; j++)
		{
			double temp = ls(j);
			//double temp = mat_in2[i, j];
			//*ptr << ((*this)(i, j) = mat_in2.at(i, j));
			*ptr << ((*this)(i, j) = ls(j));
		}
	}
	delete_Temp_mat(*this);
	return *ptr;
}

