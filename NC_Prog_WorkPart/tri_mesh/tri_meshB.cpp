
#include"../pch.h"
#define NC_Prog_WorkPart_EXPORTS
using namespace std;
#include "tri_meshB.h"

//#include"../graph_mygl.h"  12.5


extern int temp;

int tri_meshB::reset_allface_visited()
{
	for (auto it = all_face.begin(); it != all_face.end(); it++)
	{
		it->second->reset_visited();
	}
	return 0;
}

bool tri_meshB::get_a_unvisited_face(int visit, tri_meshB_F*& ans)
{
	for (auto it = all_face.begin(); it != all_face.end(); it++)
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

bool tri_meshB::init(string dir)
{
	tri_meshA meshA;
	meshA.init(dir);

	//读一个种子面
	int visit = meshA.reset_allface_visited();
	tri_meshA_F* ls_f = 0;
	if (!meshA.get_a_unvisited_face(visit, ls_f))
	{
		return false;
	}
	queue< tri_meshA_F*> neb_face;
	neb_face.push(ls_f);


	
	{
		vec3 ls_v;
		ls_v(0) = ls_f->get_a_vertex_of_f(0)->get_coor()._c1;
		ls_v(1) = ls_f->get_a_vertex_of_f(0)->get_coor()._c2;
		ls_v(2) = ls_f->get_a_vertex_of_f(0)->get_coor()._c3;
		int  i = 1;
	}
	

	//读一个连通域
	ls_f->visit(visit);
	//一个联通的面列队，按此顺序保证每个面均与已有的面相邻
	vector<tri_meshA_F*> vec_face;

	tri_meshA_F* face_now = 0;
	tri_meshA_F* ls_face1 = 0;
	tri_meshA_V* ls_vertex1 = 0;
	while (!neb_face.empty())
	{
		//对邻面列队的第一个面
		face_now = neb_face.front();
		for (int i = 0; i < 3; i++)
		{
			//找一个邻面
			face_now->get_nerb_face(i, ls_face1, ls_vertex1, ls_vertex1);
			if (ls_face1 != nullptr)
			{
				//如果这个面还没有访问
				if (!ls_face1->has_visited(visit))
				{
					//加入邻面列队
					neb_face.push(ls_face1);
				}
				//设置这个面为已访问
				ls_face1->visit(visit);
			}
		}
		//对第一个面加入相邻队列
		vec_face.push_back(face_now);
		neb_face.pop();	
	}
	tri_meshB_F* ans_new_face = 0;

	//处理的面有可能已经被访问
	//处理的面，除了第一个面，一定有已存在的邻面
	//创建面

	for (int i = 0; i < vec_face.size(); i++)
	{
		//按相邻关系遍历，保证每个新面都与已有面相邻
		if (create_a_face(vec_face[i], ans_new_face))
		{
			count++;
		}
		//更新新建面的相邻关系
		construct_nerb_ralation(ans_new_face);

	}




	//计算法向
	for (auto it = all_face.begin(); it != all_face.end(); it++)
	{
		it->second->cal_normal();
	}

	return true;
}

bool tri_meshB::init(xt_STL_Data data)
{
	tri_meshA meshA;
	meshA.init(data);

	//读一个种子面
	int visit = meshA.reset_allface_visited();
	tri_meshA_F* ls_f = 0;
	if (!meshA.get_a_unvisited_face(visit, ls_f))
	{
		return false;
	}
	queue< tri_meshA_F*> neb_face;
	neb_face.push(ls_f);



	{
		vec3 ls_v;
		ls_v(0) = ls_f->get_a_vertex_of_f(0)->get_coor()._c1;
		ls_v(1) = ls_f->get_a_vertex_of_f(0)->get_coor()._c2;
		ls_v(2) = ls_f->get_a_vertex_of_f(0)->get_coor()._c3;
		int  i = 1;
	}


	//读一个连通域
	ls_f->visit(visit);
	//一个联通的面列队，按此顺序保证每个面均与已有的面相邻
	vector<tri_meshA_F*> vec_face;

	tri_meshA_F* face_now = 0;
	tri_meshA_F* ls_face1 = 0;
	tri_meshA_V* ls_vertex1 = 0;
	while (!neb_face.empty())
	{
		//对邻面列队的第一个面
		face_now = neb_face.front();
		for (int i = 0; i < 3; i++)
		{
			//找一个邻面
			face_now->get_nerb_face(i, ls_face1, ls_vertex1, ls_vertex1);
			if (ls_face1 != nullptr)
			{
				//如果这个面还没有访问
				if (!ls_face1->has_visited(visit))
				{
					//加入邻面列队
					neb_face.push(ls_face1);
				}
				//设置这个面为已访问
				ls_face1->visit(visit);
			}
		}
		//对第一个面加入相邻队列
		vec_face.push_back(face_now);
		neb_face.pop();
	}
	tri_meshB_F* ans_new_face = 0;

	//处理的面有可能已经被访问
	//处理的面，除了第一个面，一定有已存在的邻面
	//创建面

	for (int i = 0; i < vec_face.size(); i++)
	{
		//按相邻关系遍历，保证每个新面都与已有面相邻
		if (create_a_face(vec_face[i], ans_new_face))
		{
			count++;
		}
		//更新新建面的相邻关系
		construct_nerb_ralation(ans_new_face);

	}


	//计算法向
	for (auto it = all_face.begin(); it != all_face.end(); it++)
	{
		it->second->cal_normal();
	}

	return true;
}

bool tri_meshB::create_a_face(tri_meshA_F* fa, tri_meshB_F*& ans)
{
	tri_meshA_V* p1 = 0;
	tri_meshA_V* p2 = 0;
	tri_meshA_V* p3 = 0;

	p1 = fa->get_a_vertex_of_f(0);
	p2 = fa->get_a_vertex_of_f(1);
	p3 = fa->get_a_vertex_of_f(2);

	tri_meshB_V* ls_pbv1 = 0;
	tri_meshB_V* ls_pbv2 = 0;
	tri_meshB_V* ls_pbv3 = 0;
	tri_meshB_E* ls_pbe1 = 0;
	tri_meshB_E* ls_pbe2 = 0;
	tri_meshB_E* ls_pbe3 = 0;
	tri_meshB_F* ls_pbf = 0;

	bool has_v1 = true;
	bool has_v2 = true;
	bool has_v3 = true;

	if (!find_v(triB_coor_3d(p1->get_coor()), ls_pbv1))
	{
		has_v1 = false;
		ls_pbv1 = new tri_meshB_V(triB_coor_3d(p1->get_coor()));
		insert_v(ls_pbv1->coor, ls_pbv1);
	}
	if (!find_v(triB_coor_3d(p2->get_coor()), ls_pbv2))
	{
		has_v2 = false;
		ls_pbv2 = new tri_meshB_V(triB_coor_3d(p2->get_coor()));
		insert_v(ls_pbv2->coor, ls_pbv2);
	}
	if (!find_v(triB_coor_3d(p3->get_coor()), ls_pbv3))
	{
		has_v3 = false;
		ls_pbv3 = new tri_meshB_V(triB_coor_3d(p3->get_coor()));
		insert_v(ls_pbv3->coor, ls_pbv3);
	}

	auto it1 = all_edge.find(triB_coor_2ptr(ls_pbv1, ls_pbv2));
	auto it2 = all_edge.find(triB_coor_2ptr(ls_pbv2, ls_pbv3));
	auto it3 = all_edge.find(triB_coor_2ptr(ls_pbv3, ls_pbv1));


	bool is_123 = false;

	if (it1 != all_edge.end() || it2 != all_edge.end() || it3 != all_edge.end())
	{
		//有棱已经存在，看反向是否也存在
		auto it1 = all_edge.find(triB_coor_2ptr(ls_pbv2, ls_pbv1));
		auto it2 = all_edge.find(triB_coor_2ptr(ls_pbv3, ls_pbv2));
		auto it3 = all_edge.find(triB_coor_2ptr(ls_pbv1, ls_pbv3));
		if (it1 != all_edge.end() || it2 != all_edge.end() || it3 != all_edge.end())
		{
			//有棱已经存在 重置 
			if (!has_v1)
			{
				delete_v(ls_pbv1->coor);
				delete ls_pbv1;
			}

			if (!has_v2)
			{
				delete_v(ls_pbv2->coor);
				delete ls_pbv2;
			}

			if (!has_v3)
			{
				delete_v(ls_pbv3->coor);
				delete ls_pbv3;
			}
			return false;
		}
		else
		{
			//都没有找到

			ls_pbe1 = new tri_meshB_E(triB_coor_2ptr(ls_pbv2, ls_pbv1));

			triB_ralation_bv2be* ral_1ve = new triB_ralation_bv2be(ls_pbv2, ls_pbe1, ls_pbv2->out.get_new_ralation_num());
			ls_pbv2->out.add_ralation(ral_1ve, true);
			ls_pbe1->start = ral_1ve;

			triB_ralation_bv2be* ral_2ve = new triB_ralation_bv2be(ls_pbv1, ls_pbe1, ls_pbv1->in.get_new_ralation_num());
			ls_pbv1->in.add_ralation(ral_2ve, true);
			ls_pbe1->end = ral_2ve;

			ls_pbe2 = new tri_meshB_E(triB_coor_2ptr(ls_pbv3, ls_pbv2));
			triB_ralation_bv2be* ral_3ve = new triB_ralation_bv2be(ls_pbv3, ls_pbe2, ls_pbv3->out.get_new_ralation_num());
			ls_pbv3->out.add_ralation(ral_3ve, true);
			ls_pbe1->start = ral_3ve;

			triB_ralation_bv2be* ral_4ve = new triB_ralation_bv2be(ls_pbv2, ls_pbe2, ls_pbv2->in.get_new_ralation_num());
			ls_pbv2->in.add_ralation(ral_4ve, true);
			ls_pbe2->end = ral_4ve;

			ls_pbe3 = new tri_meshB_E(triB_coor_2ptr(ls_pbv1, ls_pbv3));
			triB_ralation_bv2be* ral_5ve = new triB_ralation_bv2be(ls_pbv1, ls_pbe3, ls_pbv1->out.get_new_ralation_num());
			ls_pbv1->out.add_ralation(ral_5ve, true);
			ls_pbe3->start = ral_5ve;

			triB_ralation_bv2be* ral_6ve = new triB_ralation_bv2be(ls_pbv3, ls_pbe3, ls_pbv3->in.get_new_ralation_num());
			ls_pbv3->in.add_ralation(ral_6ve, true);
			ls_pbe3->end = ral_6ve;

		}
	}
	else
	{
		//都没有找到
		ls_pbe1 = new tri_meshB_E(triB_coor_2ptr(ls_pbv1, ls_pbv2));
		triB_ralation_bv2be* ral_1ve = new triB_ralation_bv2be(ls_pbv1, ls_pbe1, ls_pbv1->out.get_new_ralation_num());
		ls_pbv1->out.add_ralation(ral_1ve, true);
		ls_pbe1->start = ral_1ve;

		triB_ralation_bv2be* ral_2ve = new triB_ralation_bv2be(ls_pbv2, ls_pbe1, ls_pbv2->in.get_new_ralation_num());
		ls_pbv2->in.add_ralation(ral_2ve, true);
		ls_pbe1->end = ral_2ve;


		ls_pbe2 = new tri_meshB_E(triB_coor_2ptr(ls_pbv2, ls_pbv3));
		triB_ralation_bv2be* ral_3ve = new triB_ralation_bv2be(ls_pbv2, ls_pbe2, ls_pbv2->out.get_new_ralation_num());
		ls_pbv2->out.add_ralation(ral_3ve, true);
		ls_pbe2->start = ral_3ve;

		triB_ralation_bv2be* ral_4ve = new triB_ralation_bv2be(ls_pbv3, ls_pbe2, ls_pbv3->in.get_new_ralation_num());
		ls_pbv3->in.add_ralation(ral_4ve, true);
		ls_pbe2->end = ral_4ve;


		ls_pbe3 = new tri_meshB_E(triB_coor_2ptr(ls_pbv3, ls_pbv1));
		triB_ralation_bv2be* ral_5ve = new triB_ralation_bv2be(ls_pbv3, ls_pbe3, ls_pbv3->out.get_new_ralation_num());
		ls_pbv3->out.add_ralation(ral_5ve, true);
		ls_pbe3->start = ral_5ve;

		triB_ralation_bv2be* ral_6ve = new triB_ralation_bv2be(ls_pbv1, ls_pbe3, ls_pbv1->in.get_new_ralation_num());
		ls_pbv1->in.add_ralation(ral_6ve, true);
		ls_pbe3->end = ral_6ve;
	}

	insert_e(ls_pbe1->coor, ls_pbe1);
	insert_e(ls_pbe2->coor, ls_pbe2);
	insert_e(ls_pbe3->coor, ls_pbe3);

	ls_pbf = new tri_meshB_F(triB_coor_3ptr_sorted(ls_pbe1, ls_pbe2, ls_pbe3));
	insert_f(ls_pbf->coor, ls_pbf);

	ans = ls_pbf;

	//3个面棱关系
	triB_ralation_be2bf* ral_e2f1 = new triB_ralation_be2bf(ls_pbe1, ls_pbf, ls_pbf->edges.get_new_ralation_num());
	ls_pbf->edges.add_ralation(ral_e2f1, false);
	ls_pbe1->face_ral = ral_e2f1;

	triB_ralation_be2bf* ral_e2f2 = new triB_ralation_be2bf(ls_pbe2, ls_pbf, ls_pbf->edges.get_new_ralation_num());
	ls_pbf->edges.add_ralation(ral_e2f2, false);
	ls_pbe2->face_ral = ral_e2f2;

	triB_ralation_be2bf* ral_e2f3 = new triB_ralation_be2bf(ls_pbe3, ls_pbf, ls_pbf->edges.get_new_ralation_num());
	ls_pbf->edges.add_ralation(ral_e2f3, false);
	ls_pbe3->face_ral = ral_e2f3;

	//棱棱关系

	ls_pbe1->next = ls_pbe2;
	ls_pbe1->before = ls_pbe3;

	ls_pbe2->next = ls_pbe3;
	ls_pbe2->before = ls_pbe1;

	ls_pbe3->next = ls_pbe1;
	ls_pbe3->before = ls_pbe2;


	

	return true;
}

bool tri_meshB::construct_nerb_ralation(tri_meshB_F* face_in)
{

	tri_meshB_E* ls_e = 0;
	tri_meshB_F* ans_face = 0;
	tri_meshB_E* v_delete_e[3] = {};
	ans_face = face_in;
	
	//检查对棱关系，并建立对棱关系
	for (int i = 0; i < 3; i++)
	{
		ls_e = ans_face->get_edge(i);
		auto it = all_edge.find(ls_e->coor.get_oppo());
		//如果存在对棱
		if (it != all_edge.end())
		{
			//就建立此棱和对棱的关系
			make_pair(ls_e, it->second);
		}
	}

	return true;
}

bool tri_meshB::find_v(triB_coor_3d& coor, tri_meshB_V*& ans)
{
	auto f_ans = all_vertex.find(coor);
	if (f_ans != all_vertex.end())
	{
		ans = f_ans->second;
		return true;
	}
	ans = nullptr;
	return false;
}

bool tri_meshB::find_e(triB_coor_2ptr& coor, tri_meshB_E*& ans)
{
	auto f_ans = all_edge.find(coor);
	if (f_ans != all_edge.end())
	{
		ans = f_ans->second;
		return true;
	}
	ans = nullptr;
	return false;
}

bool tri_meshB::find_f(triB_coor_3ptr_sorted& coor, tri_meshB_F*& ans)
{
	auto f_ans = all_face.find(coor);
	if (f_ans != all_face.end())
	{
		ans = f_ans->second;
		return true;
	}
	ans = nullptr;
	return false;
}

bool tri_meshB::insert_v(triB_coor_3d& coor, tri_meshB_V* v_in)
{
	tri_meshB_V* ls = 0;
	//auto it = all_vertex.find(coor, ls);
	auto it = all_vertex.find(coor);
	if (it != all_vertex.end())
	{
		return false;
	}
	else
	{
		all_vertex.insert(pair<triB_coor_3d, tri_meshB_V*>(coor, v_in));
		return true;
	}
}

bool tri_meshB::insert_e(triB_coor_2ptr& coor, tri_meshB_E* e_in)
{
	tri_meshB_E* ls = 0;
	//auto it = all_vertex.find(coor, ls);
	auto it = all_edge.find(coor);
	if (it != all_edge.end())
	{
		return false;
	}
	else
	{
		all_edge.insert(pair<triB_coor_2ptr, tri_meshB_E*>(coor, e_in));
		return true;
	}
}

bool tri_meshB::insert_f(triB_coor_3ptr_sorted& coor, tri_meshB_F* f_in)
{
	tri_meshB_F* ls = 0;
	//auto it = all_vertex.find(coor, ls);
	auto it = all_face.find(coor);
	if (it != all_face.end())
	{
		return false;
	}
	else
	{
		all_face.insert(pair<triB_coor_3ptr_sorted, tri_meshB_F*>(coor, f_in));
		return true;
	}
}

bool tri_meshB::delete_v(triB_coor_3d& coor)
{
	if (all_vertex.erase(coor) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tri_meshB::delete_e(triB_coor_2ptr& coor)
{
	if (all_edge.erase(coor) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tri_meshB::delete_f(triB_coor_3ptr_sorted& coor)
{
	if (all_face.erase(coor) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tri_meshB::is_normal_out()
{
	//遍历所有面，找到重心最高的面，判断法向是否向上
	int len = all_face.size();
	double max_z = -10000.0;
	map<triB_coor_3ptr_sorted, tri_meshB_F*>::iterator it_max
		= all_face.begin();
	for (auto it= all_face.begin(); it != all_face.end(); it++)
	{
		//面计算重心函数
		vec3 zhong = it->second->cal_zhongxin();
		if (zhong.at(2) > max_z)
		{
			max_z = zhong(2);
			it_max = it;
		}
	}
	//面计算法向
	vec3 nor = it_max->second->cal_normal();

	if (nor(2) > 0.0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void tri_meshB::change_normal_out()
{
	if (is_normal_out())
	{

		int i = 0;
	}
	else
	{
		int i = 0;
		//清空边
		all_edge.clear();
		//改变起点终点-关系
		for (auto it = all_face.begin(); it != all_face.end(); it++)
		{
			//面反向
			it->second->change_normal();
			//棱注册
			for (size_t j = 0; j < 3; j++)
			{
				tri_meshB_E* ls_e = it->second->get_edge(j);
				insert_e(ls_e->coor, ls_e);
			}
		}
	}
}

tri_meshB_V::tri_meshB_V(triB_coor_3d coor_in)
{
	coor._c1 = coor_in._c1;
	coor._c2 = coor_in._c2;
	coor._c3 = coor_in._c3;
}

tri_meshB_V::~tri_meshB_V()
{

}

vec3 tri_meshB_V::get_vec3()
{
	vec3 v = { coor._c1, coor._c2, coor._c3};
	return v;
}

tri_meshB_F::tri_meshB_F(triB_coor_3ptr_sorted& coor_in)
{
	coor._p1 = coor_in._p1;
	coor._p2 = coor_in._p2;
	coor._p3 = coor_in._p3;
}

tri_meshB_E* tri_meshB_F::get_edge(int i)
{
	return edges.rals[i]->getE();
}

tri_meshB_V* tri_meshB_F::get_double3v(int i)
{
	tri_meshB_E* ls_e1 = get_edge(0);
	if (i == 0)
	{
		return ls_e1->get_start_p();
	}
	else if (i == 1)
	{
		return ls_e1->get_end_p();
	}
	else
	{
		return ls_e1->next->get_end_p();
	}
}

tri_meshB_F* tri_meshB_F::create_a_oppo_face()
{
	tri_meshB_E* ls_e[3] = {};
	tri_meshB_E* ls_e_new[3] = {};
	tri_meshB_F* ans_f = 0;
	for (int i = 0; i < 3; i++)
	{
		ls_e[i] = get_edge(i);
		ls_e_new[i] = ls_e[i]->create_oppo_edge();
	}

	ans_f = new tri_meshB_F(triB_coor_3ptr_sorted(ls_e_new[0], ls_e_new[1], ls_e_new[2]));

	//3个面棱关系
	for (int i = 0; i < 3; i++)
	{
		triB_ralation_be2bf* ral_e2f = new triB_ralation_be2bf(ls_e_new[i], ans_f, ans_f->edges.get_new_ralation_num());
		ans_f->edges.add_ralation(ral_e2f, false);
		ls_e_new[i]->face_ral = ral_e2f;
	}

	//建立相邻棱关系
	if (ls_e_new[0]->end->getV() == ls_e_new[1]->start->getV())
	{
		//棱棱关系
		ls_e_new[0]->next = ls_e_new[1];
		ls_e_new[0]->before = ls_e_new[2];

		ls_e_new[1]->next = ls_e_new[2];
		ls_e_new[1]->before = ls_e_new[0];

		ls_e_new[2]->next = ls_e_new[0];
		ls_e_new[2]->before = ls_e_new[1];
	}
	else if(ls_e_new[0]->end->getV() == ls_e_new[2]->start->getV())
	{
		//棱棱关系
		ls_e_new[0]->next = ls_e_new[2];
		ls_e_new[0]->before = ls_e_new[1];

		ls_e_new[1]->next = ls_e_new[0];
		ls_e_new[1]->before = ls_e_new[2];

		ls_e_new[2]->next = ls_e_new[1];
		ls_e_new[2]->before = ls_e_new[0];
	}
	return ans_f;
}

vec3 tri_meshB_F::cal_zhongxin()
{
	vec3 zhong =
		(
			get_edge(0)->get_start_p()->get_vec3()
			+ get_edge(1)->get_start_p()->get_vec3()
			+ get_edge(2)->get_start_p()->get_vec3()
			)
		/ 3.0;
	return zhong;
}

vec3 tri_meshB_F::cal_normal()
{
	vec3 v1 = get_edge(0)->get_vec3();
	vec3 v2 = -get_edge(0)->before->get_vec3();
	vec3 nor = normalise(cross(v1, v2));
	normal = nor;
	return nor;
}

vec3 tri_meshB_F::get_normal()
{
	return normal;
}

void tri_meshB_F::change_normal()
{

	tri_meshB_E* l1 = get_edge(0);
	tri_meshB_E* l2 = get_edge(1);
	tri_meshB_E* l3 = get_edge(2);
	l1->swap_start_end();
	l2->swap_start_end();
	l3->swap_start_end();

	tri_meshB_E* temp = 0;
	temp = l1->next;
	l1->next = l1->before;
	l1->before = temp;

	temp = l2->next;
	l2->next = l2->before;
	l2->before = temp;

	temp = l3->next;
	l3->next = l3->before;
	l3->before = temp;


	cal_normal();
}

void tri_meshB_F::reset_visited()
{
	has_been_visited = -1;
}

bool tri_meshB_F::has_visited(int i)
{
	return !(has_been_visited < i);
}

void tri_meshB_F::visit(int i)
{
	has_been_visited = i;
}

tri_meshB_F::~tri_meshB_F()
{
	tri_meshB_E* ls_e[3] = {0};
	for (int i = 0; i < edges.rals.size(); i++)
	{
		if (edges.rals[i] != nullptr)
		{
			ls_e[i] = edges.rals[i]->getE();
			delete edges.rals[i];
			ls_e[i]->face_ral = nullptr;
		}
	}
}

tri_meshB_E::tri_meshB_E(triB_coor_2ptr& coor_in)
{
	coor._p1 = coor_in._p1;
	coor._p2 = coor_in._p2;
}

tri_meshB_E::~tri_meshB_E()
{
	if (face_ral != nullptr)
	{
		delete face_ral;
	}
	start->getV()->out.delete_ralation(start->e_num_in_v);
	delete start;
	end->getV()->in.delete_ralation(end->e_num_in_v);
	delete end;
}

tri_meshB_E* tri_meshB_E::create_oppo_edge()
{
	tri_meshB_E* ans = new tri_meshB_E(coor.get_oppo());
	tri_meshB_V* ls_end = start->getV();
	tri_meshB_V* ls_start = end->getV();
	ans->start = new triB_ralation_bv2be(ls_start, ans, ls_start->out.get_new_ralation_num());
	ans->end = new triB_ralation_bv2be(ls_end, ans, ls_start->out.get_new_ralation_num());
	return ans;
}

tri_meshB_V* tri_meshB_E::get_start_p()
{
	return start->getV();
}

tri_meshB_V* tri_meshB_E::get_end_p()
{
	return end->getV();
}

vec3 tri_meshB_E::get_vec3()
{
	return normalise(
		get_end_p()->get_vec3()
		-get_start_p()->get_vec3()
	);
}

void tri_meshB_E::swap_start_end()
{
	tri_meshB_V* end_p = get_start_p();
	tri_meshB_V* start_p = get_end_p();

	end_p->out.delete_ralation(start->e_num_in_v);
	start_p->in.delete_ralation(end->e_num_in_v);

	triB_ralation_bv2be* ls = end;
	end = start;
	start = ls;

	end_p->in.add_ralation(end, true);
	start_p->out.add_ralation(start, true);

	coor = coor.get_oppo();
}

void make_pair(tri_meshB_E* e1, tri_meshB_E* e2)
{
	e1->oppo = e2;
	e2->oppo = e1;
}
