#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "triA_ralations.h"
#include "Tri_meshA.h"

triA_ralation_av2af::triA_ralation_av2af(tri_meshA_V* v_in, int in_f, tri_meshA_F* f_in, int in_v)
{
	v = v_in;
	v_num_in_f = in_f;
	f = f_in;
	f_num_in_v = in_v;
}

tri_meshA_V* triA_ralation_av2af::getV()
{
	return v;
}

tri_meshA_F* triA_ralation_av2af::getF()
{
	return f;
}

int triA_ralation_av2af::get_num_v_in_f()
{
	return v_num_in_f;
}

int triA_ralation_av2af::get_num_f_in_v()
{
	return f_num_in_v;
}

void triA_ralation_manager_av2af::add_ralation(triA_ralation_av2af* ral, bool im_first)
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

void triA_ralation_manager_av2af::delete_ralation(int i)
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

int triA_ralation_manager_av2af::get_new_ralation_num()
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



triA_ralation_manager_av2af::triA_ralation_manager_av2af()
{
	count = 0;
	is_first.clear();
	rals.clear();
	while (!empty_num_in_vec.empty())
	{
		empty_num_in_vec.pop();
	}
}

triA_ralation_manager_av2af::~triA_ralation_manager_av2af()
{

}
