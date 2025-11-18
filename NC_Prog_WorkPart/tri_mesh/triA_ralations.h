#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
class tri_meshA_V;
class tri_meshA_F;

#include <queue>
#include <vector>
using namespace std;
class triA_ralation_av2af;

class NC_Prog_WorkPart_API triA_ralation_manager_av2af
{
public:
	int count;
	vector<bool> is_first;
	vector<triA_ralation_av2af*> rals;
	queue<int> empty_num_in_vec;

public:
	void add_ralation(triA_ralation_av2af* ral, bool im_first);
	void delete_ralation(int i);
	int get_new_ralation_num();

public:
	triA_ralation_manager_av2af();	
	~triA_ralation_manager_av2af();
};


class NC_Prog_WorkPart_API triA_ralation_av2af
{
public:
	tri_meshA_V* v;
	int v_num_in_f;

	tri_meshA_F* f;
	int f_num_in_v;
public:
	triA_ralation_av2af(tri_meshA_V* v_in, int in_f, tri_meshA_F* f_in, int in_v);

public:
	tri_meshA_V* getV();
	tri_meshA_F* getF();
	int get_num_v_in_f();
	int get_num_f_in_v();
};
