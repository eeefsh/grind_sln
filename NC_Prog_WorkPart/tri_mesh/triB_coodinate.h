#pragma once

#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include "triA_coordinate.h"

//×ø±êÀà
class NC_Prog_WorkPart_API triB_coor_3d
{
public:
	double _c1;
	double _c2;
	double _c3;

public:
	bool operator<(const triB_coor_3d& p) const;

public:
	triB_coor_3d();
	triB_coor_3d(double c1, double c2, double c3);
	triB_coor_3d(triA_coor_3d& coor);

	void set_value(double c1, double c2, double c3);
};

class NC_Prog_WorkPart_API triB_coor_2ptr
{
public:
	void* _p1;
	void* _p2;

public:
	bool operator<(const triB_coor_2ptr& p) const;

public:
	triB_coor_2ptr();
	triB_coor_2ptr(void* p1, void* p2);
	void set_value(void* p1, void* p2);

	triB_coor_2ptr get_oppo();

};

class NC_Prog_WorkPart_API triB_coor_3ptr_sorted
{
public:
	void* _p1;
	void* _p2;
	void* _p3;
public:
	bool operator<(const triB_coor_3ptr_sorted& p) const;

public:
	triB_coor_3ptr_sorted();
	triB_coor_3ptr_sorted(void* p1, void* p2, void* p3);
	void set_value(void* p1, void* p2, void* p3);
};