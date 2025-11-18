#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif


//×ø±êÀà
class NC_Prog_WorkPart_API triA_coor_3d
{
public:
	double _c1;
	double _c2;
	double _c3;

public:
	bool operator<(const triA_coor_3d& p) const;

public:
	triA_coor_3d();
	triA_coor_3d(double c1, double c2, double c3);
	void set_value(double c1, double c2, double c3);
};

class NC_Prog_WorkPart_API triA_coor_3ptr
{
public:
	void* _p1;
	void* _p2;
	void* _p3;
public:
	bool operator<(const triA_coor_3ptr& p) const;

public:
	triA_coor_3ptr();
	triA_coor_3ptr(void* p1, void* p2, void* p3);
	void set_value(void* p1, void* p2, void* p3);
};


