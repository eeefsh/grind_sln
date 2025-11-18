#include "pch.h"
#define NC_Prog_nb_NC_Block_matrix_EXPORTS
#include "nb_NC_block_vec3.h"
#include "nb_block_functions_2.h"

nb_NC_block_vec3::nb_NC_block_vec3()
{
	for (int i = 0; i < 3; i++)
	{
		data[i] = 0;
	}
	is_temp_mat = true;
}

nb_NC_block_vec3::nb_NC_block_vec3(int type)
{
	if (type == BH_BL_A || type == BH_BL_JIN)
	{
		for (int i = 0; i < 3; i++)
		{
			data[i] = &(nb_new_BL_Block());
			data[i]->set_father(nb_NC_block::father_block);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			data[i] = 0;
		}
	}
	is_temp_mat = false;
}

nb_NC_block_vec3::nb_NC_block_vec3(nb_NC_block_vec3& vec)
{
	for (int i = 0; i < 3; i++)
	{
		data[i] = vec.data[i];
	}
	is_temp_mat = true;
}

nb_NC_block_vec3::~nb_NC_block_vec3()
{
	for (int i = 0; i < 3; i++)
	{
		delete data[i];
	}
}

void nb_NC_block_vec3::set_NC_Block(int i, nb_NC_block& block_in)
{
	data[i] = &block_in;
	data[i]->set_father(nb_NC_block::father_block);
}
//20231206-ZYW
nb_NC_block_vec3* nb_NC_block_vec3::new_copy()
{
	nb_NC_block_vec3* ans_ptr = new nb_NC_block_vec3;
	for (size_t i = 0; i < 3; i++)
	{
		ans_ptr->data[i] = this->data[i]->new_copy();
		ans_ptr->data[i]->set_father(nb_NC_block::father_block);
	}
	ans_ptr->is_temp_mat = true;
	return ans_ptr;
}

bool nb_NC_block_vec3::isTemp()
{
	return is_temp_mat;
}

nb_NC_block& nb_NC_block_vec3::operator()(int i)
{
	return *data[i];
}


nb_NC_block& nb_NC_block_vec3::operator=(nb_NC_block_vec3& vec)
{
	nb_NC_block* ptr = &nb_Process_K(0);
	for (int i = 0; i < 3; i++)
	{
		*ptr << ((*this)(i) = vec(i));
	}
	delete_Temp_mat(*this);
	delete_Temp_mat(vec);
	return *ptr;
}

nb_NC_block& nb_NC_block_vec3::operator=(vec3 vec)
{
	nb_NC_block* ptr = &nb_Process_K(0);
	for (int i = 0; i < 3; i++)
	{
		*ptr << ((*this)(i) = vec[i]);
	}
	delete_Temp_mat(*this);
	return *ptr;
}



