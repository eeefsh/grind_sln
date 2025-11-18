#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include"obj_cell.h"
//#include"octree.h"
//#include"oc_point.h"
#undef max


obj_cell::obj_cell()
{
	father = nullptr;
	place_flag = 0;

	num = 0;
}

obj_cell::obj_cell(int3v op)
{
	c_point = op;
	father = nullptr;
	place_flag = 0;
	num = 0;
}

obj_cell::obj_cell(double acc, double3v &op)
{
	c_point = op.turn_point_int(acc);
	father = nullptr;
	place_flag = 0;

	num = 0;
}
//改输入
obj_cell::obj_cell(double acc, double3v op, double3v fa)
{

	father = nullptr;
	place_flag = 0;
	c_point = op.turn_point_int(acc);
	num = 0;

	//11.16 保留三个法向分量
	{
		/*if (fa.x > 0)
		{
			num = 1 << 1;
		}
		else if (fa.x < 0)
		{
			num = 1;
		}
		if (fa.y > 0)
		{
			num = num | (1 << 2);
		}
		else if (fa.y < 0)
		{
			num = num | (1 << 3);
		}
		if (fa.z > 0)
		{
			num = num | (1 << 5);
		}
		else if (fa.z < 0)
		{
			num = num | (1 << 4);
		}*/
	}
	//找法向分量最大绝对值
	{
		int max_index = 0;
		double dmax = abs(fa.x);
		if (dmax < abs(fa.y))
		{
			dmax = abs(fa.y);
			max_index = 1;
		}
		else if (dmax < abs(fa.z))
		{
			max_index = 2;
		}
		//给分量最大面状态设置为外 ： 1
		if (max_index == 0)
		{
			if (fa.x > 0)
			{
				num = 1 << 1;
			}
			else
			{
				num = 1;
			}
		}
		else if (max_index == 1)
		{
			if (fa.y > 0)
			{
				num = 1 << 2;
			}
			else
			{
				num = 1 << 3;
			}
		}
		else
		{
			if (fa.z > 0)
			{
				num = 1 << 5;
			}
			else
			{
				num = 1 << 4;
			}
		}
	}
}

obj_cell::~obj_cell()
{
	int i = 0;
}

double3v obj_cell::get_double3v(double acc)
{
	return c_point.turn_point_double(acc);
}

int3v obj_cell::get_int3v()
{
	return c_point;
}

octree* obj_cell::get_father_octree()
{
	return father;
}

octree* obj_cell::get_up_octree(int n)
{
	/*if (this != nullptr)
	{
		if (n > 0)
		{
			return get_up_octree(n - 1);
		}
	}
	else
	{
		int i = 0;
	}*/
	
	if (n <= 0)
	{
		return nullptr;
	}
	octree* p = this->father;
	for (int i = 0; i < n - 1; i++)
	{
		p = p->get_father_octree();
	}

	return p;
}


int obj_cell::get_a_wai()
{
	for (size_t i = 0; i < 6; i++)
	{
		if (num & (1 << i))
		{
			return i;
		}
	}
	//没有找到外返回-1
	return -1;
}

void obj_cell::get_wai_side(int index, vector<int>& v_side)
{
	if (index % 2 == 1)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (i == index || i == index - 1)
			{
				continue;
			}
			v_side.push_back(i);
		}
	}
	else
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (i == index || i == index + 1)
			{
				continue;
			}
			v_side.push_back(i);
		}
	}

}


int obj_cell::cal_duimian_num(int wai)
{
	if (wai % 2 == 1)
	{
		return wai - 1;
	}
	else
	{
		return wai + 1;
	}
}

void obj_cell::set_face_out(int v_in)
{
	num |= (1 << v_in);
}

void obj_cell::set_face_in(int v_in)
{
	num = num & (~(1 << v_in));
}

void obj_cell::set_color(unsigned char c_num)
{
	color_num = c_num;
}

void obj_cell::set_count_cut(unsigned char cut_num)
{
	count_cut = cut_num;
}

void obj_cell::get_all_face_dir_in(vector<int>& v_in)
{
	for (size_t i = 0; i < 6; i++)
	{
		if (!((num >> i) & 1))
		{
			v_in.push_back(i);
		}
	}
}

void obj_cell::get_all_face_dir_out(vector<int>& v_out)
{
	for (size_t i = 0; i < 6; i++)
	{
		if (((num >> i) & 1))
		{
			v_out.push_back(i);
		}
	}
}

int3v obj_cell::cal_side_p_int(int pos, double w)
{
	int3v p = c_point;
	int a = static_cast<int> (w * 2.0 * 1000.0);
	switch (pos)
	{
		case 0: 
			p.x -= a;
			break;
		case 1: 
			p.x += a;
			break;
		case 2: 
			p.y += a;
			break;
		case 3: 
			p.y -= a;
			break;
		case 4: 
			p.z -= a;
			break;
		case 5: 
			p.z += a;
			break;
		default:
			break;
	}
	return p;
}

int3v obj_cell::cal_xie_side(int out, int pos, double w)
{
	int3v p = cal_side_p_int(pos, w);
	int a = static_cast<int>(w * 2.0 * 1000.0);
	switch (out)
	{
		case 0: 
			p.x -= a;
			break;
		case 1: 
			p.x += a;
			break;
		case 2: 
			p.y += a;
			break;
		case 3: 
			p.y -= a;
			break;
		case 4: 
			p.z -= a;
			break;
		case 5: 
			p.z += a;
			break;
		default:
			break;
	}
	return p;
}

bool obj_cell::is_the_side_out(int pos)
{
	if ((num & (1 << pos)))
	{
		return true;
	}
	return false;
}

unsigned char obj_cell::get_num()
{
	return num;
}


double3v obj_cell::cal_normal()
{
	int dd = 1;
	int3v op;
	//-x方向
	if (num & 1)
	{
		//op.x = op.x - dd;
		op.x--;
	}
	//+x方向
	if (num & (1 << 1))
	{
		//op.x = op.x + dd;
		op.x++;
	}
	//+y方向
	if (num & (1 << 2))
	{
		op.y++;
	}
	//-y方向
	if (num & (1 << 3))
	{
		op.y--;
	}
	//-z方向
	if (num & (1 << 4))
	{
		op.z--;
	}
	//+z方向
	if (num & (1 << 5))
	{
		op.z++;
	}
	double3v ans(op.x, op.y, op.z);	
	return ans;
}



void obj_cell::cal_o_sys(double xfa, double yfa, double zfa, double err,vec3& O, mat33& SYS )
{
	O(0) =  c_point.turn_point_double(err).x;
	O(1) =  c_point.turn_point_double(err).y;
	O(2) =  c_point.turn_point_double(err).z;

	vec3 vz = { xfa ,yfa,zfa };
	vec3 vx = { xfa ,yfa,zfa };
	if (abs(vx(0)) > 0.998)
	{
		vx(1) = vx(1) + 1.0;
	}
	else
	{
		vx(0) = vx(0) + 1.0;
	}
	
	SYS.col(0) = normalise(cross(vz, vx));
	SYS.col(2) = normalise(vz);
	SYS.col(1) = cross(SYS.col(0), SYS.col(2));
}




