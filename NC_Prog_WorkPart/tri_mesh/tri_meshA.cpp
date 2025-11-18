#include"../pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "tri_meshA.h"
#include "manager_h\MA_020101_File_STL.h"

bool tri_meshA::init(string dir)
{
	xt_STL_Data data;
	count = 0;

	if (!data.read_file(dir))
	{
		return false;
	}

	for (int i = 0; i < data.Facet_count(); i++)
	{
		//遍历每一个读入的三角形
		if (
			create_a_face(
			data.p(i, 0),
			data.p(i, 1),
			data.p(i, 2)
			)
			)
		{
			count++;
		}
	}
}

bool tri_meshA::init(xt_STL_Data data)
{
	count = 0;

	for (int i = 0; i < data.Facet_count(); i++)
	{
		//遍历每一个读入的三角形
		if (
			create_a_face(
				data.p(i, 0),
				data.p(i, 1),
				data.p(i, 2)
			)
			)
		{
			count++;
		}
	}
	return true;
}

int tri_meshA::get_count()
{
	return count;
}

bool tri_meshA::get_a_unvisited_face(int visit, tri_meshA_F*& ans)
{
	for (auto it = manager_f.begin(); it != manager_f.end(); it++)
	{
		if (it->second->has_visited(visit))
		{

		}
		else
		{
			ans = it->second;
			return true;
		}
	}
	return false;
}

bool tri_meshA::create_a_face(fvec3 p1, fvec3 p2, fvec3 p3)
{
	bool ok_p1 = 0;
	bool ok_p2 = 0;
	bool ok_p3 = 0;
	bool ok_f = 0;
	tri_meshA_V* new_p1 = 0;
	tri_meshA_V* new_p2 = 0;
	tri_meshA_V* new_p3 = 0;
	tri_meshA_F* new_f = 0;
	ok_p1 = insert_a_vertex(p1(0), p1(1), p1(2),new_p1);
	ok_p2 = insert_a_vertex(p2(0), p2(1), p2(2),new_p2);
	ok_p3 = insert_a_vertex(p3(0), p3(1), p3(2),new_p3);
	ok_f = insert_a_face(new_p1, new_p2, new_p3, new_f);
	if (ok_f)
	{
		triA_ralation_av2af* p1tof = new triA_ralation_av2af(
			new_p1,
			new_f->ral.get_new_ralation_num(),
			new_f,
			new_p1->ral.get_new_ralation_num()
		);
		new_p1->ral.add_ralation(p1tof, true);
		new_f->ral.add_ralation(p1tof, false);

		triA_ralation_av2af* p2tof = new triA_ralation_av2af(
			new_p2,
			new_f->ral.get_new_ralation_num(),
			new_f,
			new_p2->ral.get_new_ralation_num()
		);
		new_p2->ral.add_ralation(p2tof, true);
		new_f->ral.add_ralation(p2tof, false);

		triA_ralation_av2af* p3tof = new triA_ralation_av2af(
			new_p3,
			new_f->ral.get_new_ralation_num(),
			new_f,
			new_p3->ral.get_new_ralation_num()
		);		
		new_p3->ral.add_ralation(p3tof, true);
		new_f->ral.add_ralation(p3tof, false);
	}
	return ok_f;
}

bool tri_meshA::insert_a_vertex(double p1, double p2, double p3, tri_meshA_V*& ans)
{
	tri_meshA_V* ls_ans=0;
	if (has_this_3d(p1, p2, p3, ls_ans))
	{
		ans = ls_ans;
		return false;
	}
	else
	{
		tri_meshA_V* ls_f = new tri_meshA_V(p1, p2, p3);
		auto it = manager_v.insert(
			pair<triA_coor_3d, tri_meshA_V*>
			(triA_coor_3d(p1, p2, p3), ls_f)
		);
		ans = it.first->second;
		return true;
	}
}

bool tri_meshA::insert_a_face(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3, tri_meshA_F*& ans)
{
	tri_meshA_F* ls_ans = 0;
	if (has_this_3ptr(p1, p2, p3, ls_ans))
	{
		ans = ls_ans;
		return false;
	}
	else
	{
		tri_meshA_F* ls_f = new tri_meshA_F(p1, p2, p3);
		auto it=manager_f.insert(
			pair<triA_coor_3ptr, tri_meshA_F*>
			(triA_coor_3ptr(p1, p2, p3), ls_f)
		);
		ans = it.first->second;
		return true;
	}
}

bool tri_meshA::has_this_3d(double p1, double p2, double p3, tri_meshA_V*& ans)
{
	triA_coor_3d ls_3d(p1, p2, p3);
	map<triA_coor_3d, tri_meshA_V*>::iterator it = manager_v.find(ls_3d);
	if (it != manager_v.end())
	{
		ans = it->second;
		return true;
	}
	else
	{
		ans = 0;
		return false;
	}
}

bool tri_meshA::has_this_3ptr(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3, tri_meshA_F*& ans)
{
	triA_coor_3ptr ls_3ptr((void*)p1, (void*)p2, (void*)p3);
	map<triA_coor_3ptr, tri_meshA_F*>::iterator it = manager_f.find(ls_3ptr);
	if (it != manager_f.end())
	{
		ans = it->second;
		return true;
	}
	else
	{
		ans = 0;
		return false;
	}
}

int tri_meshA::reset_allface_visited()
{
	for (auto it = manager_f.begin(); it != manager_f.end(); it++)
	{
		it->second->reset_visited();
	}
	return 0;
}

tri_meshA_V::tri_meshA_V()
{
}

tri_meshA_V::tri_meshA_V(double p1, double p2, double p3)
{
	coor._c1 = p1;
	coor._c2 = p2;
	coor._c3 = p3;
}

int tri_meshA_V::count_nerb_face()
{
	return ral.count;
}

bool tri_meshA_V::get_nerb_face(int i, tri_meshA_F*& nerb_face)
{
	if (i < ral.rals.size())
	{
		nerb_face = ral.rals[i]->getF();
		if (nerb_face != nullptr)
		{
			return true;
		}
	}
	return false;
}

int tri_meshA_V::get_pos_count()
{
	return ral.rals.size();
}

bool tri_meshA_V::has_this_face(tri_meshA_F*& face_ral)
{
	for (int i = 0; i < ral.rals.size(); i++)
	{
		if (ral.rals[i]->getF() == face_ral)
		{
			return true;
		}
	}
	return false;
}

triA_coor_3d tri_meshA_V::get_coor()
{
	return coor;
}

void tri_meshA_F::reset_visited()
{
	has_been_visited = -1;
}

bool tri_meshA_F::has_visited(int i)
{
	return !(has_been_visited < i);
}

void tri_meshA_F::visit(int i)
{
	has_been_visited = i;
}

triA_coor_3ptr tri_meshA_F::get_coor()
{
	return coor;
}

tri_meshA_F::tri_meshA_F()
{
	
}

tri_meshA_F::tri_meshA_F(tri_meshA_V* p1, tri_meshA_V* p2, tri_meshA_V* p3)
{
	coor._p1 = p1;
	coor._p2 = p2;
	coor._p3 = p3;
}

bool tri_meshA_F::get_nerb_face(int i, tri_meshA_F*& nerb_face, tri_meshA_V*& p1, tri_meshA_V*& p2)
{
	//面中只有3个点面关系
	tri_meshA_V* ls_p1 = 0;
	tri_meshA_V* ls_p2 = 0;

	//1 获得公共点
	if (i == 2)
	{
		ls_p1 = ral.rals[i]->getV();
		ls_p2 = ral.rals[0]->getV();
	}
	else
	{
		ls_p1 = ral.rals[i]->getV();
		ls_p2 = ral.rals[i + 1]->getV();
	}

	tri_meshA_F* ls_f = 0;
	for (int i = 0; i < ls_p1->ral.rals.size(); i++)
	{
		if (ls_p1->get_nerb_face(i, ls_f))
		{
			if (ls_p2->has_this_face(ls_f))
			{
				if (ls_f != this)
				{
					//找到了要求的相邻面
					nerb_face = ls_f;
					if (p1 != nullptr)
					{
						p1 = ls_p1;
					}
					if (p2 != nullptr)
					{
						p2 = ls_p2;
					}
					return true;
				}
			}
		}
	}
	p1 = nullptr;
	p2 = nullptr;
	nerb_face = nullptr;
	return false;
}

tri_meshA_V* tri_meshA_F::get_the_other_v_of_f(tri_meshA_V*& p1, tri_meshA_V*& p2)
{
	for (int i = 0; i < ral.rals.size(); i++)
	{
		tri_meshA_V* ls_v = ral.rals[i]->getV();
		if (ls_v != nullptr)
		{
			if (ls_v != p1 && ls_v != p2)
			{
				return ls_v;
			}
		}
	}
	return nullptr;
}

tri_meshA_V* tri_meshA_F::get_a_vertex_of_f(int m)
{
	int n = 0;
	for (int i = 0; i < ral.rals.size(); i++)
	{
		tri_meshA_V* ls_v = ral.rals[i]->getV();
		if (ls_v != nullptr)
		{
			if (n==m)
			{
				return ls_v;
			}
			n++;
		}
	}
	return nullptr;
}
