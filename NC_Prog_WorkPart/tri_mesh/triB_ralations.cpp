#include"../pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "triB_ralations.h"
#include "tri_meshB.h"

triB_ralation_bv2be::triB_ralation_bv2be(tri_meshB_V* v_in, tri_meshB_E* e_in, int in_v)
{
	v = v_in;
	e = e_in;
	e_num_in_v = in_v;
}

tri_meshB_V* triB_ralation_bv2be::getV()
{
	return v;
}

tri_meshB_E* triB_ralation_bv2be::getE()
{
	return e;
}

int triB_ralation_bv2be::get_num_e_in_v()
{
	return e_num_in_v;
}

triB_ralation_bv2be::~triB_ralation_bv2be()
{
	int i = 0;
}

void triB_ralation_manager_bv2be::add_ralation(triB_ralation_bv2be* ral, bool im_first)
{
	if (empty_num_in_vec.empty())
	{
		is_first.push_back(im_first);
		rals.push_back(ral);
	}
	else
	{
		is_first[empty_num_in_vec.front()] = im_first;
		rals[empty_num_in_vec.front()] = ral;
		empty_num_in_vec.pop();
	}
	count++;
}

void triB_ralation_manager_bv2be::delete_ralation(int i)
{
	if (rals[i] != nullptr)
	{
		rals[i] = nullptr;
		empty_num_in_vec.push(i);
	}
	else
	{

	}
	count--;
}

int triB_ralation_manager_bv2be::get_new_ralation_num()
{
	if (!empty_num_in_vec.empty())
	{
		return empty_num_in_vec.front();
	}
	else
	{
		return count;
	}
}

triB_ralation_manager_bv2be::triB_ralation_manager_bv2be()
{
	count = 0;
	is_first.clear();
	rals.clear();
	while (!empty_num_in_vec.empty())
	{
		empty_num_in_vec.pop();
	}
}

triB_ralation_manager_bv2be::~triB_ralation_manager_bv2be()
{

}

triB_ralation_be2bf::triB_ralation_be2bf(tri_meshB_E* e_in, tri_meshB_F* f_in, int e_in_f)
{
	e = e_in;
	f = f_in;
	e_num_in_f = e_in_f;
}

tri_meshB_E* triB_ralation_be2bf::getE()
{
	return e;
}

tri_meshB_F* triB_ralation_be2bf::getF()
{
	return f;
}

int triB_ralation_be2bf::get_num_e_in_v()
{
	return e_num_in_f;
}

void triB_ralation_manager_be2bf::add_ralation(triB_ralation_be2bf* ral, bool im_first)
{
	if (empty_num_in_vec.empty())
	{
		is_first.push_back(im_first);
		rals.push_back(ral);
	}
	else
	{
		is_first[empty_num_in_vec.front()] = im_first;
		rals[empty_num_in_vec.front()] = ral;
		empty_num_in_vec.pop();
	}
	count++;
}

void triB_ralation_manager_be2bf::delete_ralation(int i)
{
	if (rals[i] != nullptr)
	{
		rals[i] = nullptr;
		empty_num_in_vec.push(i);
	}
	else
	{

	}
	count--;
}

int triB_ralation_manager_be2bf::get_new_ralation_num()
{
	if (!empty_num_in_vec.empty())
	{
		return empty_num_in_vec.front();
	}
	else
	{
		return count;
	}
}

triB_ralation_manager_be2bf::triB_ralation_manager_be2bf()
{
	count = 0;
	is_first.clear();
	rals.clear();
	while (!empty_num_in_vec.empty())
	{
		empty_num_in_vec.pop();
	}
}

triB_ralation_manager_be2bf::~triB_ralation_manager_be2bf()
{
}
