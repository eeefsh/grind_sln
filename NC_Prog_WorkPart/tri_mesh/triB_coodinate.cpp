#include"../pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "triB_coodinate.h"

//判断点是同一个点的最小距离
const double err = 0.0001;

bool triB_coor_3d::operator<(const triB_coor_3d& p) const
{
	if (_c1 < p._c1 - err)
	{
		return true;
	}
	else if (p._c1 + err < _c1)
	{
		return false;
	}
	else
	{
		if (_c2 < p._c2 - err)
		{
			return true;
		}
		else if (p._c2 + err < _c2)
		{
			return false;
		}
		else
		{
			if (_c3 < p._c3 - err)
			{
				return true;
			}
			else if (p._c3 + err < _c3)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}

}

triB_coor_3d::triB_coor_3d()
{
	_c1 = 0.0;
	_c2 = 0.0;
	_c3 = 0.0;
}

triB_coor_3d::triB_coor_3d(double c1, double c2, double c3)
{
	_c1 = c1;
	_c2 = c2;
	_c3 = c3;
}

triB_coor_3d::triB_coor_3d(triA_coor_3d& coor)
{
	_c1 = coor._c1;
	_c2 = coor._c2;
	_c3 = coor._c3;
}

void triB_coor_3d::set_value(double c1, double c2, double c3)
{
	_c1 = c1;
	_c2 = c2;
	_c3 = c3;
}

bool triB_coor_3ptr_sorted::operator<(const triB_coor_3ptr_sorted& p) const
{
	if (_p1 < p._p1)
	{
		return true;
	}
	else if (p._p1 < _p1)
	{
		return false;
	}
	else
	{
		if (_p2 < p._p2)
		{
			return true;
		}
		else if (p._p2 < _p2)
		{
			return false;
		}
		else
		{
			if (_p3 < p._p3)
			{
				return true;
			}
			else if (p._p3 < _p3)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}

triB_coor_3ptr_sorted::triB_coor_3ptr_sorted()
{
	_p1 = 0;
	_p2 = 0;
	_p3 = 0;
}

triB_coor_3ptr_sorted::triB_coor_3ptr_sorted(void* p1, void* p2, void* p3)
{
	set_value(p1, p2, p3);
}

void triB_coor_3ptr_sorted::set_value(void* p1, void* p2, void* p3)
{
	bool b12 = p1 < p2;
	bool b13 = p1 < p3;
	bool b23 = p2 < p3;

	if (b12)
	{
		if (b23)
		{
			_p1 = p1;
			_p2 = p2;
			_p3 = p3;
		}
		else
		{
			if (b13)
			{
				_p1 = p1;
				_p2 = p3;
				_p3 = p2;
			}
			else
			{
				_p1 = p3;
				_p2 = p1;
				_p3 = p2;
			}

		}
	}
	else
	{
		if (b13)
		{
			_p1 = p2;
			_p2 = p1;
			_p3 = p3;
		}
		else
		{
			if (b23)
			{
				_p1 = p2;
				_p2 = p3;
				_p3 = p1;
			}
			else
			{
				_p1 = p3;
				_p2 = p2;
				_p3 = p1;
			}
		}
	}
}

bool triB_coor_2ptr::operator<(const triB_coor_2ptr& p) const
{

	if (_p1 < p._p1)
	{
		return true;
	}
	else if (p._p1 < _p1)
	{
		return false;
	}
	else
	{
		if (_p2 < p._p2)
		{
			return true;
		}
		else if (p._p2 < _p2)
		{
			return false;
		}
		else
		{
			return false;
		}
	}
}

triB_coor_2ptr::triB_coor_2ptr()
{
	set_value(0, 0);
}

triB_coor_2ptr::triB_coor_2ptr(void* p1, void* p2)
{
	set_value(p1, p2);
}

void triB_coor_2ptr::set_value(void* p1, void* p2)
{
	_p1 = p1;
	_p2 = p2;
}

triB_coor_2ptr triB_coor_2ptr::get_oppo()
{
	triB_coor_2ptr ls_coor;
	auto temp = ls_coor._p1;
	ls_coor._p1 = _p2;
	ls_coor._p2 = temp;
	return ls_coor;
}
