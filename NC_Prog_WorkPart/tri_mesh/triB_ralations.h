#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include <queue>
#include <vector>
using namespace std;
class tri_meshB_V;
class tri_meshB_E;
class tri_meshB_F;
class tri_meshB;

//n to 1 ¹ØÏµ
class NC_Prog_WorkPart_API triB_ralation_bv2be
{
public:
	tri_meshB_V* v;
	tri_meshB_E* e;
	int e_num_in_v;
public:
	triB_ralation_bv2be(tri_meshB_V* v_in, tri_meshB_E* e_in, int in_v);

public:
	tri_meshB_V* getV();
	tri_meshB_E* getE();
	int get_num_e_in_v();

	~triB_ralation_bv2be();
};

class NC_Prog_WorkPart_API triB_ralation_be2bf
{
public:
	tri_meshB_E* e;
	tri_meshB_F* f;
	int e_num_in_f;
public:
	triB_ralation_be2bf(tri_meshB_E* e_in, tri_meshB_F* f_in, int e_in_f);

public:
	tri_meshB_E* getE();
	tri_meshB_F* getF();
	int get_num_e_in_v();
};

class NC_Prog_WorkPart_API triB_ralation_manager_bv2be
{
public:
	int count;
	vector<bool> is_first;
	vector<triB_ralation_bv2be*> rals;
	queue<int> empty_num_in_vec;

public:
	void add_ralation(triB_ralation_bv2be* ral, bool im_first);
	void delete_ralation(int i);
	int get_new_ralation_num();

public:
	triB_ralation_manager_bv2be();
	~triB_ralation_manager_bv2be();
};

class NC_Prog_WorkPart_API triB_ralation_manager_be2bf
{
public:
	int count;
	vector<bool> is_first;
	vector<triB_ralation_be2bf*> rals;
	queue<int> empty_num_in_vec;

public:
	void add_ralation(triB_ralation_be2bf* ral, bool im_first);
	void delete_ralation(int i);
	int get_new_ralation_num();

public:
	triB_ralation_manager_be2bf();
	~triB_ralation_manager_be2bf();
};