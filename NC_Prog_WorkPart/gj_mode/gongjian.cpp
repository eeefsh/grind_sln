#pragma once

#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include"gongjian.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include<set>





//工件位置变换

 double gongjian_init::get_acc()
{
	return acc_d;
}

void gongjian_init::init_gj_by_stl(string file_dir, vec trans, double acc_in)
{
	read_stl(file_dir);

	//11.30 给参数赋值 装成函数 ???
	acc_d = acc_in;
	manager_cells.set_acc(acc_d);
	set_show(10, acc_d);

	int3v P_MAX, P_MIN;
	P_MAX.x = INT_MIN;
	P_MAX.y = INT_MIN;
	P_MAX.z = INT_MIN;
	P_MIN.x = INT_MAX;
	P_MIN.y = INT_MAX;
	P_MIN.z = INT_MAX;
	

	//2 从三角网格中读取到所有顶点及法向 后进行加密
	vector<double3v> ans_points;
	vector<double3v> ans_normals;
	lisan_by_stl(mesh_gj, trans, ans_points, ans_normals, P_MAX, P_MIN);
	//离散完一个三角形 就放入map 11.28

	//3 创建阵列点盒，建立空间层级+坐标位置索引
	
	//create_cells_and_boxes(ans_points, ans_normals, P_MAX, P_MIN);

	//4 初始化树 map里面cell的面状态
	init_tree(P_MAX, P_MIN, acc_d);

	//
	set_group_last_n();
}

void gongjian_init::init_gj_by_col(double D_in, double len_in, double acc_in)
{
	acc_d = acc_in;
	manager_cells.set_acc(acc_d);
	set_show(10, acc_d);

	set_col_var(D_in, len_in);

	int3v P_MAX, P_MIN;
	P_MAX.x = INT_MIN;
	P_MAX.y = INT_MIN;
	P_MAX.z = INT_MIN;
	P_MIN.x = INT_MAX;
	P_MIN.y = INT_MAX;
	P_MIN.z = INT_MAX;

	//1 根据参数 生成顶点及法向 
	vector<double3v> tri_points;  // 0 1 2 为一个三角形 3 4 5另一个
	vector<double3v> tri_normals;
	get_col_tri_nor(tri_points, tri_normals, acc_d);

	//2 从三角中读取到所有顶点及法向 后进行加密
	vector<double3v> ans_points;
	vector<double3v> ans_normals;
	lisan_by_col_and_rot(tri_points, tri_normals, ans_points, ans_normals, P_MAX, P_MIN);
	//离散完一个三角形 就放入map 11.28

	//3 创建阵列点盒，建立空间层级+坐标位置索引

	//create_cells_and_boxes(ans_points, ans_normals, P_MAX, P_MIN);

	//4 初始化树 map里面cell的面状态
	init_tree(P_MAX, P_MIN, acc_d);

	//5
	set_group_last_n();
}

void gongjian_init::init_gj_by_rot(mat& gj_outline, double acc_in)
{
	acc_d = acc_in;
	manager_cells.set_acc(acc_d);
	set_show(10, acc_d);

	set_rot_var(gj_outline);

	int3v P_MAX, P_MIN;
	P_MAX.x = INT_MIN;
	P_MAX.y = INT_MIN;
	P_MAX.z = INT_MIN;
	P_MIN.x = INT_MAX;
	P_MIN.y = INT_MAX;
	P_MIN.z = INT_MAX;

	//1 根据参数 生成与精度相关的三角点 及法向 
	vector<double3v> tri_points;  // 0 1 2 为一个三角形 3 4 5另一个
	vector<double3v> tri_normals;
	//端面用三角离散，侧面直接离散
	get_rot_tri_nor(tri_points, tri_normals, acc_in);

	vector<double3v> ans_points;
	vector<double3v> ans_normals;
	lisan_by_col_and_rot(tri_points, tri_normals, ans_points, ans_normals, P_MAX, P_MIN);

	//3 创建阵列点盒，建立空间层级+坐标位置索引
	//create_cells_and_boxes(ans_points, ans_normals, P_MAX, P_MIN);

	//4 初始化树 map里面cell的面状态
	init_tree(P_MAX, P_MIN, acc_d);

	//
	set_group_last_n();
}



void gongjian_init::send_init_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num)
{
	queue<octree*>  qt;
	octree* cur = &manager_cells.oc_tree;

	//分组越多更新越慢
	int aim_deptn = group_last_n;
	qt.push(cur);
	while (cur->get_depth() > aim_deptn)
	{
		cur->get_child_octree(qt);
		qt.pop();
		cur = qt.front();
	}

	vector<mesh_cutted> temp;
	mesh_cutted tri_nor;

	//更新显示内容
	while (!qt.empty())
	{

		queue<obj_cell*> voc;
		qt.front()->get_all_obj(voc);

		while (!voc.empty())
		{
			//显示一个点* 
			obj_cell* op = voc.front();
			voc.pop();
			double3v ap = op->cal_normal();


			//将一个点按照法向 分解为四个点
			vec3 ls_p = { op->get_double3v(acc_d).x, op->get_double3v(acc_d).y , op->get_double3v(acc_d).z };
			vec3 ls_nor = { ap.x, ap.y, ap.z };
			//生成一个不平行法向的向量
			vec3 pnor_temp;
			if (ls_nor(1) > -0.00005 && ls_nor(1) < 0.00005
				&& ls_nor(2) > -0.00005 && ls_nor(2) < 0.00005)
			{
				pnor_temp = { ls_nor(0), ls_nor(1) + 1.0, ls_nor(2) };
			}
			else
			{
				pnor_temp = { ls_nor(0) + 1.0, ls_nor(1) , ls_nor(2) };
			}
			pnor_temp = normalise(pnor_temp);

			vec3 ls_a = normalise(cross(ls_nor, pnor_temp));
			vec3 ls_b = normalise(cross(ls_nor, ls_a));
			mat33 ls_SYS = { {ls_a(0),ls_b(0),ls_nor(0)},
							{ls_a(1),ls_b(1),ls_nor(1)},
							{ls_a(2),ls_b(2),ls_nor(2)} };

			vec3 ls_R = { acc_d , 0.0 ,0.0 };
			vec3 ansp1 = ls_SYS * ls_R + ls_p;
			vec3 ansp2 = ls_SYS * tcRotZ(3, 60.0) * ls_R + ls_p;
			vec3 ansp3 = ls_SYS * tcRotZ(3, 120.0) * ls_R + ls_p;
			vec3 ansp4 = ls_SYS * tcRotZ(3, 180.0) * ls_R + ls_p;

			vector<double3v> v_seg;  //生成点顺序 是相对180度，存放改变 3.15
			v_seg.emplace_back(ansp1);
			v_seg.emplace_back(ansp2);
			v_seg.emplace_back(ansp3);
			v_seg.emplace_back(ansp4);
			v_seg.emplace_back(ansp1);

			for (int i = 0; i < v_seg.size() - 1; i++)
			{
				tri_nor.p1 = op->get_double3v(acc_d);
				tri_nor.p2 = v_seg[i];
				tri_nor.p3 = v_seg[i + 1];
				tri_nor.p4 = ap;
				temp.emplace_back(tri_nor);
			}
		}

		//计算对应列表号
		int list_index = cal_list_num(manager_cells.oc_tree, *qt.front());
		renew_list_num.push_back(list_index);

		qt.pop();
		show_data.emplace_back(temp);
		temp.clear();
	}
}

//1.1 包含表面索引初始化

void gongjian_init::lisan_by_stl(const tri_meshB& mesh, vec trans, vector<double3v>& ans_points, vector<double3v>& ans_normals, int3v& P_MAX, int3v& P_MIN)
{
	//2 从三角网格中读取到所有顶点及法向
	vector<double3v> mesh_gj_p;
	vector<double3v> normals;
	get_points_and_normals(mesh, trans, mesh_gj_p, normals);

	//3 对三角面片加密点
	tri_lisan_vec_triangles(mesh_gj_p, normals, ans_points, ans_normals , P_MAX, P_MIN);
}

void gongjian_init::lisan_by_col_and_rot(vector<double3v>& in_points, vector<double3v>& in_normals, vector<double3v>& ans_points, vector<double3v>& ans_normals, int3v& P_MAX, int3v& P_MIN)
{
	tri_lisan_vec_triangles(in_points, in_normals, ans_points, ans_normals, P_MAX, P_MIN);
}

//1.1.1 从三角网格中读取到所有顶点及法向

void gongjian_init::get_points_and_normals(const tri_meshB& mesh_gj, vec trans, vector<double3v>& ans_point_vec, vector<double3v>& ans_normal_vec)
{
	mat SYS_trans =  tcRotY(3, -trans(2)) * tcRotZ(3, trans(1)) * tcRotX(3, trans(0))  * tcRotX(3, 90);
	
	vec vec_trans = { trans(3), -trans(5), trans(4) };

	auto itend = mesh_gj.all_face.end();
	for (auto it = mesh_gj.all_face.begin(); it != itend; it++)
	{
		vec3 p;
		p = SYS_trans * it->second->get_double3v(0)->get_vec3() + vec_trans;
		ans_point_vec.emplace_back(p);
		p = SYS_trans * it->second->get_normal() ;
		ans_normal_vec.emplace_back(p);

		p = SYS_trans * it->second->get_double3v(1)->get_vec3() + vec_trans;
		ans_point_vec.emplace_back(p);
		p = SYS_trans * it->second->get_normal() ;
		ans_normal_vec.emplace_back(p);

		p = SYS_trans * it->second->get_double3v(2)->get_vec3() + vec_trans;
		ans_point_vec.emplace_back(p);
		p = SYS_trans * it->second->get_normal() ;
		ans_normal_vec.emplace_back(p);
	}
}

//1.1.2

void gongjian_init::tri_lisan_vec_triangles(const vector<double3v>& points_in, const vector<double3v>& normals_in, 
	vector<double3v>& ans_points, vector<double3v>& ans_normals, int3v& P_MAX, int3v& P_MIN)
{
	int len = points_in.size();
	for (int i = 0; i < len;)
	{
		tri_lisan_a_triangle(
			points_in[i], points_in[i + 1], points_in[i + 2],
			normals_in[i], ans_points, ans_normals);
		i = i + 3;

		//离散完一个三角形 就放入map 11.28
		create_cells_and_boxes(ans_points, ans_normals, P_MAX, P_MIN);
		ans_points.clear();
		ans_normals.clear();
	}

	//检查一个cell为内部点 但有一个外面(有问题) 将cell删除 2024.9.5
	auto it = manager_cells.map_pos.begin();
	for (; it != manager_cells.map_pos.end(); it++)
	{
		obj_cell* cur_cell = it->second;
		//找到点的面状态为外：1 的位置：0-5
		vector<int> save_out;
		cur_cell->get_all_face_dir_out(save_out);

		if (save_out.size() > 1)
		{
			int i = -1;
		}

		for (int i = 0; i < save_out.size(); i++)
		{
			int out_now = save_out[i];
			//计算指定外方向相邻的坐标
			int3v coor_the_out = cur_cell->cal_side_p_int(out_now, acc_d);

			//如果位置存在cell 将cell删除
			if (manager_cells.is_the_point_exist(coor_the_out))
			{
				manager_cells.map_pos.erase(it);
				it--;
				break;
			}
			
		}
	}

	//初始化所有表面点  11.15 改所有面为内的cell删除
	manager_cells.init_all_cells_face_num(acc_d);
}

//1.1.2.1 三角形按照精度加密得到一堆点

void gongjian_init::tri_lisan_a_triangle(double3v p1, double3v p2, double3v p3, const double3v& normal, vector<double3v>& san_p_all, vector<double3v>& res_nor)
{
	{
		double3v b_point;
		double3v long_line_p;
		double3v short_line_p;
		vector<double3v> san_p1, san_p2;

		//找公共点，最长边的点，次长边的点
		find_bp(p1, p2, p3, b_point, long_line_p, short_line_p);

		int p_mun = c_p_mun(b_point, long_line_p);	//插值个数
		//最长边加密
		cai_point_1(b_point, long_line_p, p_mun, san_p1);
		//次长边加密
		cai_point_1(b_point, short_line_p, p_mun, san_p2);

		int len = san_p1.size();
		for (int i = 0; i < len; i++)
		{
			cai_point_2(san_p1[i], san_p2[i], acc_d, normal, san_p_all, res_nor);
		}
	}
	
}

//1.1.2.1.1

void gongjian_init::find_bp(double3v& p1, double3v& p2, double3v& p3, double3v& b_point, double3v& long_p, double3v& short_p)
{
	//计算三边
	double line1 = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
	double line2 = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y) + (p3.z - p2.z) * (p3.z - p2.z));
	double line3 = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y) + (p1.z - p3.z) * (p1.z - p3.z));
	vector<double> vb{ line1, line2, line3 };
	sort(vb.begin(), vb.end(), greater<double>());

	b_point = p1;
	double3v ls_P = p2;
	if (abs(line1 - vb[0]) < 0.0005)
	{
		if (abs(line2 - vb[1]) < 0.0005)
		{
			b_point = p2;
			long_p = p1;
			short_p = p3;
		}
		else
		{
			b_point = p1;
			long_p = p2;
			short_p = p3;
		}
	}
	else if (abs(line2 - vb[0]) < 0.0005)
	{
		if (abs(line1 - vb[1]) < 0.0005)
		{
			b_point = p2;
			long_p = p3;
			short_p = p1;
		}
		else
		{
			b_point = p3;
			long_p = p2;
			short_p = p1;
		}
	}
	else
	{
		if (abs(line1 - vb[1]) < 0.0005)
		{
			b_point = p1;
			long_p = p3;
			short_p = p2;
		}
		else
		{
			b_point = p3;
			long_p = p1;
			short_p = p2;
		}
	}
}

//1.1.2.1.2

void gongjian_init::cai_point_1(double3v bp, double3v p2, int n, vector<double3v>& vp1)
{
	if (n == 0)
	{
		vp1.emplace_back(bp);
		vp1.emplace_back(p2);
		return;
	}
	//vp1.emplace_back(bp);
	for (int i = 0; i < n; i++)
	{
		double3v p;
		p.x = bp.x + (p2.x - bp.x) / double(n + 1) * double(i+ 1);
		p.y = bp.y + (p2.y - bp.y) / double(n + 1) * double(i+ 1);
		p.z = bp.z + (p2.z - bp.z) / double(n + 1) * double(i+ 1);
		vp1.emplace_back(p);
	}
	vp1.emplace_back(p2);
}

//1.1.2.1.3

void gongjian_init::cai_point_2(double3v bp, double3v p2, double d, const double3v& normal, vector<double3v>& vp1, vector<double3v>& res_nor)
{
	//离散间距小于cell宽度
	double acc_dis = acc_d / 5;
	double line1 = sqrt((p2.x - bp.x) * (p2.x - bp.x) + (p2.y - bp.y) * (p2.y - bp.y) + (p2.z - bp.z) * (p2.z - bp.z));
	int n = int(line1 / acc_dis);
	/*if (abs(line1 - n * acc_dis) < acc_dis * 0.2)
	{
		n--;
	}*/

	if (n == 0)
	{
		vp1.emplace_back(bp);
		res_nor.emplace_back(normal);
		vp1.emplace_back(p2);
		res_nor.emplace_back(normal);
		return;
	}
	vp1.emplace_back(bp);
	res_nor.emplace_back(normal);
	for (int i = 0; i < n; i++)
	{
		double3v p;		//总差 / 个数+1 = 步长
		p.x = bp.x + (p2.x - bp.x) / double(n + 1) * double(i + 1);
		p.y = bp.y + (p2.y - bp.y) / double(n + 1) * double(i + 1);
		p.z = bp.z + (p2.z - bp.z) / double(n + 1) * double(i + 1);
		vp1.emplace_back(p);
		res_nor.emplace_back(normal);
	}
	vp1.emplace_back(p2);
	res_nor.emplace_back(normal);
}

//1.1.2.1.4

int gongjian_init::c_p_mun(double3v bp, double3v p2)
{
	double acc_dis = acc_d / 5 ;
	double line1 = sqrt((p2.x - bp.x) * (p2.x - bp.x) + (p2.y - bp.y) * (p2.y - bp.y) + (p2.z - bp.z) * (p2.z - bp.z));
	//int n = static_cast<int> (line1 / 2*acc_d );
	int n = int (line1 / acc_dis);
	if (abs(line1 - n * acc_dis) < acc_dis * 0.2)
	{
		n--;
	}
	return n;
}

//1.2 创建阵列点盒，建立坐标位置索引 + 记录空间大小最值

void gongjian_init::create_cells_and_boxes(const vector<double3v>& points, const vector<double3v>& normals, int3v& P_MAX, int3v& P_MIN)
{

	int ls_size = points.size();
	for (int i = 0; i < ls_size; i++)
	{
		//计算点盒坐标----可以放入点盒的初始化
		obj_cell* cp = new obj_cell(acc_d , points[i], normals[i]);
		double3v it = cp->get_double3v(acc_d );
		{
			//double dis = sqrt((points[i].x - it.x) * (points[i].x - it.x) + (points[i].y - it.y) * (points[i].y - it.y) + (points[i].z - it.z) * (points[i].z - it.z));
			//if (dis < acc_d  + acc_d / 5)
			//{
			//	int3v tp = cp->get_int3v();
			//	if (manager_cells.map_pos.find(tp) != manager_cells.map_pos.end())
			//	{
			//		delete cp;  //存在索引中
			//	}
			//	else
			//	{
			//		manager_cells.add_cell_to_map(cp);
			//		find_max_min_p(P_MAX, P_MIN, cp->get_int3v());
			//	}
			//}
		}
		int3v tp = cp->get_int3v();
		if (manager_cells.map_pos.find(tp) != manager_cells.map_pos.end())
		{
			delete cp;  //存在索引中
		}
		else
		{
			manager_cells.add_cell_to_map(cp);
			find_max_min_p(P_MAX, P_MIN, cp->get_int3v());
		}
		
	}

}

//1.2.1

void gongjian_init::find_max_min_p(int3v& P_MAX, int3v& P_MIN, int3v p)
{
	if (p.x > P_MAX.x)
	{
		P_MAX.x = p.x;
	}
	if (p.x < P_MIN.x)
	{
		P_MIN.x = p.x;
	}
	if (p.y > P_MAX.y)
	{
		P_MAX.y = p.y;
	}
	if (p.y < P_MIN.y)
	{
		P_MIN.y = p.y;
	}
	if (p.z > P_MAX.z)
	{
		P_MAX.z = p.z;
	}
	if (p.z < P_MIN.z)
	{
		P_MIN.z = p.z;
	}
}

//1.3

void gongjian_init::init_tree(const int3v& P_MAX, const int3v& P_MIN, const double d)
{
	//初始化树
	cube_box box(acc_d);
	box.set_max_xyz(P_MAX);
	box.set_min_xyz(P_MIN);
	box.init_box();
	manager_cells.oc_tree.init_tree(box);



	//将初始化完成的cell，挂到树上
	auto itend = manager_cells.map_pos.end();
	for (auto it = manager_cells.map_pos.begin(); it != itend; it++)
	{
		manager_cells.oc_tree.add_obj(it->second);
	}
}

//1.3.1 树的层级确定后 确定分组

void gongjian_init::set_group_last_n()
{
	group_last_n = manager_cells.oc_tree.get_depth() / 2 + 1 ;
	//group_last_n = 6;
}

//1.4 根据倒数第几层(树的底层为1) 计算分组个数 并genlist

//void gongjian_init::gen_list()
//{
//	//根据树的层数，确定分组个数
//	list_num = manager_cells.oc_tree.get_nodes2last(group_last_n);
//
//	//::gladLoadGL();
//	// 创建显示列表
//	list_start_num = glGenLists(list_num);
//}

//1.5 初始化每个列表的内容

//void gongjian_init::init_list()
//{
//	//遍历完树的分组层级，将指针放入待更新组
//	queue<octree*>  qt;
//	octree* cur = &manager_cells.oc_tree;
//
//	//分组越多更新越慢
//	int aim_deptn = group_last_n;
//	qt.push(&manager_cells.oc_tree);
//	while (cur->get_depth() > aim_deptn)
//	{
//		cur->get_child_octree(qt);
//		qt.pop();
//		cur = qt.front();
//	}
//
//	//更新显示内容
//	while (!qt.empty())
//	{
//		//计算对应列表号--树返回结果
//		int list_index = cal_list_num(manager_cells.oc_tree, *qt.front());
//		//到对应号的显示列表，将分组下的点画上
//		display_fresh_a_list(qt.front(), list_index + list_start_num);
//		qt.pop();
//	}
//}

//1.5.1计算当前组 所对应显示列表号

int gongjian_init::cal_list_num(octree& root, octree& group)
{
	//一行分组节点个数 
	int N = root.get_L() / group.get_L();	//树的包围盒边长/分组包围盒边长 = 一行分组节点个数
	int xp, yp, zp;
	//树包围盒中心 到 坐标值最小分组盒 中心 的 轴向距离大小
	int temp = (N / 2) * group.get_L() - group.get_L() / 2;//N  * group.get_L()/2 - group.get_L() / 2; (N-1) *group.get_L()/2

	//坐标值最小分组包围盒 中心
	xp = root.get_c_point().x - temp;
	yp = root.get_c_point().y - temp;
	zp = root.get_c_point().z - temp;

	//任意分组 所在 位置
	int X = (group.get_c_point().x - xp) / group.get_L();
	int Y = (group.get_c_point().y - yp) / group.get_L();
	int Z = (group.get_c_point().z - zp) / group.get_L();

	return Z * N * N + Y * N + X;
}






mat44 gongjian_init::construct_sys(mat33 SYS, vec3 O)
{
	mat m4(4, 4, fill::zeros);
	m4.submat(0, 0, 2, 2) = SYS;
	m4.submat(0, 3, 2, 3) = O;
	m4(3, 3) = 1.0;
	mat44 ans = m4;
	return ans;
}

//设置点画圆的分割边数 与 半径

void gongjian_init::set_show(int seg, double rad)
{
	draw_point_seg = seg;
	draw_point_r = rad;
}

//显示磨削过程中离散模型的变化

//void gongjian_init::show_cutting()
//{
//	::gladLoadGL();
//	if (is_show)
//	{
//		for (int i = 0 + list_start_num; i < list_num + list_start_num; i++)
//		{
//			glCallList(i);
//		}
//	}
//}

//2：切除

gongjian_cutoff::gongjian_cutoff()
{
}

int test_p = 0;
void gongjian_cutoff::cut_off(shalun* sl, unsigned char color, unsigned char count_cut)
{
	test_p++;
	queue<obj_cell*> peng_p;
	//根据工件砂轮位置检测碰撞 得到碰撞的cells
	check_allcells_peng(sl, peng_p);
	if (peng_p.empty())
	{
		return;
	}

	//根据碰撞的cells 计算变形结果 并记录变形过程中产生变化的组
	change_point(peng_p, sl, color, count_cut);
	//更新变化组所对应显示事列表的内容
	//renew_list();
}

void gongjian_cutoff::send_cut_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num)
{
	//记录被删除的组号，后清空显示列表
	set<int>::iterator it_num = groups_clear.begin();
	auto it_num_end = groups_clear.end();
	for (; it_num != it_num_end; it_num++)
	{
		del_list_num.push_back(*it_num);
	}
	groups_clear.clear();

	vector<mesh_cutted> temp;
	mesh_cutted tri_nor;

	set<octree*>::iterator it = groups_changed.begin();
	auto it_end = groups_changed.end();
	for (; it != it_end; it++)
	{
		queue<obj_cell*> voc;
		(*it)->get_all_obj(voc);

		while (!voc.empty())
		{
			//显示一个点* 
			obj_cell* op = voc.front();
			voc.pop();
			double3v ap = op->cal_normal();

			
			//将一个点按照法向 分解为四个点
			vec3 ls_p = { op->get_double3v(acc_d).x, op->get_double3v(acc_d).y , op->get_double3v(acc_d).z };
			vec3 ls_nor = { ap.x, ap.y, ap.z };
			//生成一个不平行法向的向量
			vec3 pnor_temp;
			if (ls_nor(1) > -0.00005 && ls_nor(1) < 0.00005
				&& ls_nor(2) > -0.00005 && ls_nor(2) < 0.00005)
			{
				pnor_temp = { ls_nor(0), ls_nor(1) + 1.0, ls_nor(2) };
			}
			else
			{
				pnor_temp = { ls_nor(0) + 1.0, ls_nor(1) , ls_nor(2) };
			}
			pnor_temp = normalise(pnor_temp);

			vec3 ls_a = normalise(cross(ls_nor, pnor_temp));
			vec3 ls_b = normalise(cross(ls_nor, ls_a));
			mat33 ls_SYS = {{ls_a(0),ls_b(0),ls_nor(0)},
							{ls_a(1),ls_b(1),ls_nor(1)},
							{ls_a(2),ls_b(2),ls_nor(2)} };

			vec3 ls_R = { acc_d , 0.0 ,0.0 };
			vec3 ansp1 = ls_SYS * ls_R + ls_p;
			vec3 ansp2 = ls_SYS * tcRotZ(3, 60.0) * ls_R + ls_p;
			vec3 ansp3 = ls_SYS * tcRotZ(3, 120.0) * ls_R + ls_p;
			vec3 ansp4 = ls_SYS * tcRotZ(3, 180.0) * ls_R + ls_p;

			vector<double3v> v_seg;  //生成点顺序 是相对180度，存放改变 3.15
			v_seg.emplace_back(ansp1);
			v_seg.emplace_back(ansp2);
			v_seg.emplace_back(ansp3);
			v_seg.emplace_back(ansp4);
			v_seg.emplace_back(ansp1);

			for (int i = 0; i < v_seg.size() - 1; i++)
			{
				tri_nor.p1 = op->get_double3v(acc_d);
				tri_nor.p2 = v_seg[i];
				tri_nor.p3 = v_seg[i + 1];
				tri_nor.p4 = ap;
				temp.emplace_back(tri_nor);
			}
			
		}

		//计算对应列表号
		int list_index = cal_list_num(manager_cells.oc_tree, *(*it));
		renew_list_num.push_back(list_index);

		show_data.emplace_back(temp);
		temp.clear();
	}
	groups_changed.clear();


}


//2.1  根据工件砂轮位置检测碰撞 得到碰撞的cells
int test_top1 = 0;
int test_top2 = 0;
int test_top3 = 0;
void gongjian_cutoff::check_allcells_peng(shalun* sl, queue<obj_cell*>& ans_cells_peng)
{
	//第一级搜索盒放入待检查队列
	queue<octree*> boxes_uncheck;
	int i = manager_cells.oc_tree.get_depth();
	boxes_uncheck.push(&manager_cells.oc_tree);
	while (!boxes_uncheck.empty())
	{
		//取首个，碰撞计算
		octree* cur_box = boxes_uncheck.front();
		boxes_uncheck.pop();
		if (is_peng_box_and_sl(sl, cur_box))
		{
			test_top1++;
			//判断是否末级树
			if (cur_box->is_bottom())
			{
				//下一级点盒放入碰撞点队列
				queue<obj_cell*> cells_temp;
				cur_box->get_child_obj(cells_temp);
				while (!cells_temp.empty())
				{
					if (is_peng_cell_and_sl(sl, cells_temp.front()))
					{
						test_top2++;
						//轮廓碰撞计算
						if (is_peng_cell_and_ls_outline(sl, cells_temp.front()))
						{
							test_top3++;
							ans_cells_peng.push(cells_temp.front());
						}
					}
					cells_temp.pop();
				}
			}
			else
			{
				//下一级树放入待检查队列
				cur_box->get_child_octree(boxes_uncheck);
			}
		}
	}
}

//2.1.1 

bool gongjian_cutoff::is_peng_box_and_sl(shalun* sl, octree* cur_box)
{
	return	is_peng(sl, cur_box->get_double3v(acc_d), cur_box->get_r(acc_d));

}

//2.1.2

bool gongjian_cutoff::is_peng_cell_and_sl(shalun* sl, obj_cell* cur_cell)
{
	return	is_peng(sl, cur_cell->get_double3v(acc_d), acc_d * sqrt(3.0) / 2.0);
}

bool gongjian_cutoff::is_peng(shalun* sl, double3v& temp_p, double R)
{
	vec GJ_box_point(3);
	GJ_box_point(0) = temp_p.x;
	GJ_box_point(1) = temp_p.y;
	GJ_box_point(2) = temp_p.z;

	double box_R = R;
	vec GJ_O_SL = sl->GJ_O_SL;
	mat GJ_SYS_SL = sl->GJ_SYS_SL;
	//vec3 GJ_O_SL ;
	//mat33 GJ_SYS_SL ;
	//cal_SL_to_GJ(sl, GJ_O_SL, GJ_SYS_SL);	//12.1 gai
	
	//1判断外侧
	double lenth_ls =
		dot(
			GJ_box_point - (GJ_O_SL + GJ_SYS_SL.col(2) * sl->out_length),
			GJ_SYS_SL.col(2)
		);
	if (lenth_ls - box_R > 0.0)	//表示未碰撞
	{
		return false;
	}

	//3判断内侧
	//判断条件有问题
	double lenth_lsnei =
		dot(
			GJ_box_point - (GJ_O_SL + GJ_SYS_SL.col(2) * sl->in_length),
			-GJ_SYS_SL.col(2)
		);
	if (lenth_lsnei - box_R > 0.0)	//表示未碰撞
	{
		return false;
	}

	//2判断直径
	double r_temp =
		norm(
			GJ_box_point - GJ_O_SL
			-
			dot(GJ_box_point - GJ_O_SL, GJ_SYS_SL.col(2)) * GJ_SYS_SL.col(2)
		);
	if (r_temp - box_R > sl->cover_d / 2.0)
	{
		return false;
	}

	return true;
}

//2.1.3 //轮廓碰撞计算

bool gongjian_cutoff::is_peng_cell_and_ls_outline(shalun* sl, obj_cell* cur_he)
{
	double3v temp_p = cur_he->get_double3v(acc_d);
	vec GJ_box_point(3);
	GJ_box_point(0) = temp_p.x;
	GJ_box_point(1) = temp_p.y;
	GJ_box_point(2) = temp_p.z;

	vec GJ_O_SL = sl->GJ_O_SL;
	mat GJ_SYS_SL = sl->GJ_SYS_SL;
	 
	double lenth_ls =
		dot(
			GJ_box_point - (GJ_O_SL + GJ_SYS_SL.col(2) * sl->out_length),
			GJ_SYS_SL.col(2)
		);
	//lenth_ls 为负数说明在外端面内侧
	double cur_len = sl->out_length + lenth_ls; //len大于in_length
	double ls_r1 = 0;	double ls_len1 = 0;
	double ls_r2 = 0;	double ls_len2 = 0;

	//12.14 用lower_bound 
	auto it = sl->outline_len_r.lower_bound(cur_len);
	ls_r1 = it->second;
	ls_len1 = it->first;
	it++;
	ls_r2 = it->second;
	ls_len2 = it->first;
	/*for (auto it = sl->outline_len_r.begin(); it != sl->outline_len_r.end(); it++)
	{
		
		if (cur_len > it->first - 0.005)
		{
			ls_r1 = it->second;
			ls_len1 = it->first;
		}
		else
		{
			ls_r2 = it->second;
			ls_len2 = it->first;
		}
	}*/
	//double box_R = (ls_r1 + ls_r2) / 2.0 ;	//轮廓之间半径 应根据距离对r插值 ???
	double box_R = ls_r1 + (cur_len - ls_len1) * (ls_r2 - ls_r1) / (ls_len2 - ls_len1);

	double r_temp =
		norm(
			GJ_box_point - GJ_O_SL
			-
			dot(GJ_box_point - GJ_O_SL, GJ_SYS_SL.col(2)) * GJ_SYS_SL.col(2)
		);

	//2判断直径
	if (r_temp > box_R)
	{
		return false;
	}
	return true;

}

//2.2 根据碰撞的cells 计算变形结果

void gongjian_cutoff::change_point(queue<obj_cell*>& cells_peng, shalun* sl, unsigned char color, unsigned char count_cut)
{
	while (!cells_peng.empty())
	{
 		obj_cell* cur_p = cells_peng.front();
		cells_peng.pop();
		//碰撞点所在分组节点，放入带更新的组
		octree* temp_ot = cur_p->get_up_octree(group_last_n);
		groups_changed.insert(temp_ot);
		int cur_list_index = cal_list_num(manager_cells.oc_tree, *temp_ot);

		//计算该点会产生的新边界点
		vector<int> v_in;//方向标志
		cur_p->get_all_face_dir_in(v_in);

		for (int i = 0; i < v_in.size(); i++)//遍历所有朝向内的面
		{
			int3v op = cur_p->cal_side_p_int(v_in[i],acc_d);  //计算旁边点的坐标
			obj_cell* cur_cell = nullptr;
			if (manager_cells.is_the_point_exist(op))//这个坐标的点存在
			{
				//修改存在点的对应面状态
				cur_cell = manager_cells.map_pos.find(op)->second;
				cur_cell->set_face_out(cal_duimian_num(v_in[i]));
			}
			else
			{
				cur_cell = manager_cells.new_a_cutted_cell(op, v_in[i]);

				manager_cells.add_cell_to_map(cur_cell);
				manager_cells.add_cell_to_tree(cur_cell);
				if (is_peng_cell_and_sl(sl, cur_cell))
				{
					//轮廓碰撞计算
					if (is_peng_cell_and_ls_outline(sl, cur_cell))
					{
						cells_peng.push(cur_cell);
					}
				}
				else
				{
				}
			}
			//已存在的cell也要改变刀序颜色
			//cur_cell->set_count_cut(count_cut);
			cur_cell->set_color(color);

			octree* temp_ot2 = cur_cell->get_up_octree(group_last_n);
			groups_changed.insert(temp_ot2);
		}
		//删除
		octree* ptr_zu = nullptr;
		manager_cells.del_cell(cur_p, ptr_zu, group_last_n);
		if (ptr_zu != nullptr)
		{
			if (groups_changed.find(ptr_zu) != groups_changed.end())
			{
				groups_changed.erase(ptr_zu);
			}
			//刷新cur_list
			/*::gladLoadGL();
			glNewList(cur_list_index + list_start_num, GL_COMPILE);
			glEndList();*/

			//12.6增加 记录被删除的组号，后清空显示列表
			int clear_num = cal_list_num(manager_cells.oc_tree, *ptr_zu);
			groups_clear.insert(clear_num);
		}
	}
}

//2.2.2 计算一个面的向对面的号

int gongjian_cutoff::cal_duimian_num(int face_now)
{
	if (face_now % 2 == 0)
	{
		face_now++;
	}
	else
	{
		face_now--;
	}
	return face_now;
}

//2.3 更新变化组所对应显示事列表的内容

//void gongjian_cutoff::renew_list()
//{
//	set<octree*>::iterator it = groups_changed.begin();
//	auto it_end = groups_changed.end();
//	for (; it != it_end; it++)
//	{
//		int list_index = cal_list_num(manager_cells.oc_tree, *(*it));
//
//		display_fresh_a_list(*it, list_index + list_start_num);
//	}
//	groups_changed.clear();
//}

gongjian_cutted::gongjian_cutted()
{
}

gongjian_cutted::~gongjian_cutted()
{
}

void gongjian_cutted::create_face_mesh()
{
	/*list_num_cutted = glGenLists(1);*/
	gj_acc = get_acc();
	smooth_w = 2;	//平滑范围

	color_list_size = 10;
	color_list_start = glGenLists(color_list_size);
	set_color_list();

	//1.产生变形的区域进行平滑》》可以得到不规整cell的点
	//1.1变形的点会有标记 按照工序计数 ++

	//map存的int3v 改变值后索引不到 需要个容器存放改变值后的cell
	map<int3v, int> all_change_cells;
	vector<double3v> change_cells_new;	//先存上原来的值
	get_all_change_cells(all_change_cells, change_cells_new);	//记录最大的刀序  
	//

	//要求1： 未变形的点也平滑  》》只改循环的对象
	//2: 同一刀序 产生的变形点 一起平滑  》》已添加 

	//11.29 平滑计算存在问题 16：53
	//smooth_all_cells( all_change_cells, change_cells_new);	
	//点平滑后 通过 all_change_cells 可索引到新的坐标值 在change_cells_new
	// 即 可在工件map中构建三角  网格 顶点值由 change_cells_new 更新

	create_mesh_finish(all_change_cells, change_cells_new);

	//未变形的点 + 变形结束平滑后的点显示
	//show_all_cells();
}

void gongjian_cutted::send_mesh_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num)
{
	vector<mesh_cutted> temp;
	mesh_cutted tri_nor;

	int len_tri = mesh_finish_tri.size();
	for (int i = 0; i < len_tri; i++)	
	{ 
		double3v p1 = mesh_finish_tri[i].p1;
		double3v p2 = mesh_finish_tri[i].p2;
		double3v p3 = mesh_finish_tri[i].p3;

		vec3 v1 = { p1.x, p1.y, p1.z };
		vec3 v2 = { p2.x, p2.y, p2.z };
		vec3 v3 = { p3.x, p3.y, p3.z };
		vec3 nor1 = cross((v2 - v1), (v3 - v2));

		tri_nor.p1 = p1;
		tri_nor.p2 = p2;
		tri_nor.p3 = p3;
		tri_nor.p4 = nor1;

		temp.emplace_back(tri_nor);
	}
	show_data.emplace_back(temp);
}

void gongjian_cutted::send_cutted_data(vector<vector<mesh_cutted>>& show_data, vector<int>& zu_color)
{
	auto itb = manager_cells.map_pos.begin();
	auto itend = manager_cells.map_pos.begin();  //int3v, obj_cell*
	//颜色分组
	multimap<int, obj_cell*> map_color;
	for (; itb != itend; itb++)
	{
		map_color.insert({ itb->second->color_num, itb->second });
	}

	vector<mesh_cutted>  temp_mesh;
	auto itb2 = map_color.begin();
	auto itend2 = map_color.end();
	int before_color = -2;
	for (; itb2 != itend2; )
	{
		int cur_color = itb2->first;
		if (before_color != cur_color) //一个组完成
		{
			show_data.push_back(temp_mesh); //会推一个空组进去
			zu_color.push_back(before_color);
			before_color = cur_color;
			temp_mesh.clear();
		}
		else
		{
			mesh_cutted tri_nor;

			//显示一个点* 
			obj_cell* op = itb2->second;
			double3v ap = op->cal_normal();

			//将一个点按照法向 分解为四个点 
			vec3 ls_p = { op->get_double3v(acc_d).x, op->get_double3v(acc_d).y , op->get_double3v(acc_d).z };
			vec3 ls_nor = { ap.x, ap.y, ap.z };
			//生成一个不平行法向的向量
			vec3 pnor_temp;
			if (ls_nor(1) > -0.00005 && ls_nor(1) < 0.00005
				&& ls_nor(2) > -0.00005 && ls_nor(2) < 0.00005)
			{
				pnor_temp = { ls_nor(0), ls_nor(1) + 1.0, ls_nor(2) };
			}
			else
			{
				pnor_temp = { ls_nor(0) + 1.0, ls_nor(1) , ls_nor(2) };
			}
			vec3 ls_a = cross(ls_nor, pnor_temp);
			vec3 ls_b = cross(ls_nor, ls_a);
			mat33 ls_SYS = { {ls_a(0),ls_b(0),ls_nor(0)},
							{ls_a(1),ls_b(1),ls_nor(1)},
							{ls_a(2),ls_b(2),ls_nor(2)} };

			vec3 ls_R = { acc_d * 1.5, 0.0 ,0.0 };
			//画6边形
			vector<double3v> v_seg;
			for (int i = 0; i < 6; i++)
			{
				vec3 ansp = ls_SYS * tcRotZ(3, i * 60) * ls_R + ls_p;
				v_seg.emplace_back(ansp);
			}
			vec3 ansp = ls_SYS * tcRotZ(3, 0) * ls_R + ls_p;
			v_seg.emplace_back(ansp);
			{
				//vec3 ansp1 = ls_SYS * ls_R + ls_p;
				//vec3 ansp2 = ls_SYS * tcRotZ(3, 90.0) * ls_R + ls_p;
				//vec3 ansp3 = ls_SYS * tcRotZ(3, 180.0) * ls_R + ls_p;
				//vec3 ansp4 = ls_SYS * tcRotZ(3, 270.0) * ls_R + ls_p;

				//生成点顺序 是相对180度，存放改变 3.15
				//v_seg.emplace_back(ansp1);
				//v_seg.emplace_back(ansp2);
				//v_seg.emplace_back(ansp3);
				//v_seg.emplace_back(ansp4);
				//v_seg.emplace_back(ansp1);
			}

			for (int i = 0; i < v_seg.size() - 1; i++)
			{
				tri_nor.p1 = op->get_double3v(acc_d);
				tri_nor.p2 = v_seg[i];
				tri_nor.p3 = v_seg[i + 1];
				tri_nor.p4 = ap;
				temp_mesh.emplace_back(tri_nor);
			}

			itb2++;
		}
	}
}

//void gongjian_cutted::show_cutted_mesh()
//{
//	glCallList(list_num_cutted);
//}

void gongjian_cutted::get_all_change_cells(map<int3v, int>& all_cells, vector<double3v>& all_cell_dou3v)
{
	int count_cell = 0;
	auto itend = manager_cells.map_pos.end();
	for (auto it = manager_cells.map_pos.begin(); it != itend; it++)
	{
		//11.27 16:53 增加 cell有5个外删除 
		vector<int> v_out;
		it->second->get_all_face_dir_out(v_out);
		if (v_out.size() > 4)
		{
			it = manager_cells.map_pos.erase(it);
			it--;
		}
		else
		{
			if (it->second->count_cut > 0)
			{
				//拿出面状态
				all_cells.insert({ it->first, count_cell });
				all_cell_dou3v.emplace_back(it->second->get_double3v(gj_acc));
				count_cell++;
			}
		}

	}
}

void gongjian_cutted::smooth_all_cells(map<int3v, int>& change_cells, vector<double3v>& change_cells_new)
{
	auto itend = change_cells.end();
	for (auto it = change_cells.begin(); it != itend; it++)
	{
		//根据周围 （n阶）cell的坐标值改变自身坐标值
		smooth_a_cell(it->first, it->second, change_cells, change_cells_new);
	}
	//未变形点
	/*auto gj_itend = manager_cells.map_pos.end();
	for (auto it = manager_cells.map_pos.begin(); it != gj_itend; it++)
	{
		smooth_a_cell( it->first, 0, change_cells, change_cells_new);
	}*/
}

void gongjian_cutted::smooth_a_cell(int3v cell_p, int change_index, map<int3v, int>& change_cells, vector<double3v>& change_cells_new)
{
	if (change_cells.size() == 0)
	{
		return;
	}
	//change_cells.insert({ cell_p, count}); // 记录改变值后的cell 原始状态
	set<int3v> side_cells;
	int cur_cut = manager_cells.map_pos.find(cell_p)->second->count_cut;
	//计算（一阶）周围cell 记录存在位置
	get_n_side_cells(cell_p, cur_cut, smooth_w, side_cells);	//加上刀序 找周围 

	//根据存在的cell 计算新的坐标值

	cal_smooth_new_cell(side_cells, cell_p, change_index, change_cells, change_cells_new);

}

//void gongjian_cutted::show_all_cells()
//{
//	::gladLoadGL();
//	glNewList(list_num_cutted, GL_COMPILE); // 开始记录绘制命令
//	glMatrixMode(GL_MODELVIEW);
//
//	int len_tri = mesh_finish_tri.size();
//	for (int i = 0; i < len_tri; i++)	//测试 显示网格构建三角的顺序 20
//	{
//		//显示一个tri_mesh 
//		double3v p1 = mesh_finish_tri[i].p1;
//		double3v p2 = mesh_finish_tri[i].p2;
//		double3v p3 = mesh_finish_tri[i].p3;
//
//		vec3 v1 = { p1.x, p1.y, p1.z };
//		vec3 v2 = { p2.x, p2.y, p2.z };
//		vec3 v3 = { p3.x, p3.y, p3.z };
//		vec3 nor1 = cross((v2 - v1), (v3 - v2));
//		//通过刀序设置颜色;
//		int cur_color = mesh_finish_tri[i].color;
//		glCallList(color_list_start + cur_color);
//		glPushMatrix();
//		{
//			//glMultMatrixd(m4.memptr());   //调用
//			glNormal3f(nor1(0), nor1(1), nor1(2));//改变 显示两个三角的顺序 123 << 124
//			glBegin(GL_TRIANGLES);
//			{
//				glVertex3d(v1(0), v1(1), v1(2));
//				glVertex3d(v2(0), v2(1), v2(2));
//				glVertex3d(v3(0), v3(1), v3(2));
//			}
//			glEnd();
//		}
//		glPopMatrix();
//	}
//
//
//	glEndList(); // 结束记录
//}

void gongjian_cutted::get_n_side_cells(int3v& cell_p, int count_cut, int smooth_size, set<int3v>& side_cell)
{
	vector<int3v> v_cells;
	v_cells.emplace_back(cell_p);
	int3v cur_cell = cell_p;
	int3v left_cell = cell_p;
	int3v right_cell = cell_p;
	for (int i = 0; i < smooth_size; i++)
	{
		cur_cell = left_cell;
		//left_cell会更新
		if (find_cell_u_left(cur_cell, left_cell))//左
		{
			if (manager_cells.map_pos.find(left_cell)->second->count_cut == count_cut)//加上刀序 相同
			{
				v_cells.emplace_back(left_cell);
			}
		}
		else
		{
			int i = 0;
		}
		cur_cell = right_cell;
		if (find_cell_u_right(cur_cell, right_cell))//右  没找到但是改变了值
		{
			if (manager_cells.map_pos.find(right_cell)->second->count_cut == count_cut)
			{
				v_cells.emplace_back(right_cell);
			}
		}
		else
		{
			int i = 0;
		}
	}
	int3v front_cell;
	int3v back_cell;
	for (int i = 0; i < v_cells.size(); i++)
	{
		front_cell = v_cells[i];
		back_cell = v_cells[i];
		side_cell.insert(v_cells[i]);
		for (int j = 0; j < smooth_size; j++)
		{
			cur_cell = front_cell;
			if (find_cell_v_front(cell_p, front_cell))//前 一定存在
			{
				if (manager_cells.map_pos.find(front_cell)->second->count_cut == count_cut)
				{
					side_cell.insert(front_cell);
				}
			}
			else
			{
				int i = 0;
			}
			cur_cell = back_cell;
			if (find_cell_v_back(cell_p, back_cell))//后 可能不存在
			{
				if (manager_cells.map_pos.find(back_cell)->second->count_cut == count_cut)
				{
					side_cell.insert(back_cell);
				}
			}
			else
			{
				int i = 0;
			}
		}
	}
}

bool gongjian_cutted::find_cell_v_front(int3v& cur_cell, int3v& aim_cell)
{
	aim_cell = cur_cell;
	//v方向 对应四个面
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_cell);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (is_pos_out(5, cur_out)) //上面为外
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 0);
		cal_cell_int3v_side(aim_cell, 3, 1);
		//aim_cell.x = aim_cell.x - 2;
		//aim_cell.z = aim_cell.z + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 0);
			//aim_cell.z = aim_cell.z - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 0);
				//aim_cell.z = aim_cell.z - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(4, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 1);
		cal_cell_int3v_side(aim_cell, 3, 0);
		//aim_cell.x = aim_cell.x + 2;
		//aim_cell.z = aim_cell.z - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 1);
			//aim_cell.z = aim_cell.z + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 1);
				//aim_cell.z = aim_cell.z + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(3, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 0);
		cal_cell_int3v_side(aim_cell, 2, 0);
		//aim_cell.x = aim_cell.x - 2;
		//aim_cell.y = aim_cell.y - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 1);
			//aim_cell.y = aim_cell.y + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 1);
				//aim_cell.y = aim_cell.y + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(2, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 0);
		cal_cell_int3v_side(aim_cell, 2, 1);
		//aim_cell.x = aim_cell.x - 2;
		//aim_cell.y = aim_cell.y + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 0);
			//aim_cell.y = aim_cell.y - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 0);
				//aim_cell.y = aim_cell.y - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(1, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 1);
		cal_cell_int3v_side(aim_cell, 1, 1);
		//aim_cell.z = aim_cell.z + 2;
		//aim_cell.x = aim_cell.x + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 0);
			//aim_cell.x = aim_cell.x - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 0);
				//aim_cell.x = aim_cell.x - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(0, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 0);
		cal_cell_int3v_side(aim_cell, 1, 0);
		//aim_cell.z = aim_cell.z - 2;
		//aim_cell.x = aim_cell.x - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 1);
			//aim_cell.x = aim_cell.x + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 1);
				//aim_cell.x = aim_cell.x + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	aim_cell = cur_cell;
	return 0;
}

bool gongjian_cutted::find_cell_v_back(int3v& cur_cell, int3v& aim_cell)
{
	aim_cell = cur_cell;
	//v方向 对应四个面
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_cell);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (is_pos_out(5, cur_out)) //上面为外
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 1);
		cal_cell_int3v_side(aim_cell, 3, 1);
		//aim_cell.x = aim_cell.x + 2;
		//aim_cell.z = aim_cell.z + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 0);
			//aim_cell.z = aim_cell.z - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 0);
				//aim_cell.z = aim_cell.z - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(4, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 0);
		cal_cell_int3v_side(aim_cell, 3, 0);
		//aim_cell.x = aim_cell.x - 2;
		//aim_cell.z = aim_cell.z - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 1);
			//aim_cell.z = aim_cell.z + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 1);
				//aim_cell.z = aim_cell.z + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(3, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 1);
		cal_cell_int3v_side(aim_cell, 2, 0);
		//aim_cell.x = aim_cell.x + 2;
		//aim_cell.y = aim_cell.y - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 1);
			//aim_cell.y = aim_cell.y + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 1);
				//aim_cell.y = aim_cell.y + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(2, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 1, 1);
		cal_cell_int3v_side(aim_cell, 2, 1);
		//aim_cell.x = aim_cell.x + 2;
		//aim_cell.y = aim_cell.y + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 0);
			//aim_cell.y = aim_cell.y - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 0);
				//aim_cell.y = aim_cell.y - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(1, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 0);
		cal_cell_int3v_side(aim_cell, 1, 1);
		//aim_cell.z = aim_cell.z - 2;
		//aim_cell.x = aim_cell.x + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 0);
			//aim_cell.x = aim_cell.x - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 0);
				//aim_cell.x = aim_cell.x - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(0, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 1);
		cal_cell_int3v_side(aim_cell, 1, 0);
		//aim_cell.z = aim_cell.z + 2;
		//aim_cell.x = aim_cell.x - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 1);
			//aim_cell.x = aim_cell.x + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 1);
				//aim_cell.x = aim_cell.x + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	aim_cell = cur_cell;
	return 0;
}

bool gongjian_cutted::is_pos_out(int pos, vector<int>& cur_out)
{
	for (int i = 0; i < cur_out.size(); i++)
	{
		if (pos == cur_out[i])
		{
			return true;
		}
	}
	return false;
}

void gongjian_cutted::cal_smooth_new_cell(set<int3v>& side_cells, int3v& cell_p, int change_index, map<int3v, int>& change_cells, vector<double3v>& change_cells_new)
{
	//平均法向  
	vec3 move_nor;
	acl_move_nor(side_cells, cell_p, move_nor);
	if (side_cells.size() == 1)
	{
		return;
	}
	side_cells.erase(cell_p);

	//计算移动距离
	vec3 v_old;
	vec3 move_dis;
	if (change_cells.find(cell_p) != change_cells.end())
	{
		double3v new_ed = change_cells_new[change_cells.find(cell_p)->second];
		v_old = { new_ed.x , new_ed.y ,new_ed.z };
	}
	else
	{
		double3v ls = cell_p.turn_point_double(gj_acc);
		v_old = { ls.x , ls.y, ls.z };
	}

	auto itend = side_cells.end();
	for (auto it = side_cells.begin(); it != itend; it++)
	{
		int3v temp = *it;
		vec3 v_temp;
		if (change_cells.find(temp) != change_cells.end())	//存在已经平滑后的点
		{
			double3v new_ed = change_cells_new[change_cells.find(temp)->second];
			v_temp = { new_ed.x , new_ed.y ,new_ed.z };
		}
		else
		{
			double3v ls = temp.turn_point_double(gj_acc);
			v_temp = { ls.x , ls.y, ls.z };
		}
		v_temp = normalise(v_temp - v_old);
		//一个点影响距离
		vec3 move_temp;
		move_temp = dot(v_temp, move_nor) * move_nor;
		move_dis = move_dis + move_temp;
	}
	double p_num = side_cells.size();
	change_cells_new[change_index].x = v_old(0) + move_dis(0) / p_num;
	change_cells_new[change_index].y = v_old(1) + move_dis(1) / p_num;
	change_cells_new[change_index].z = v_old(2) + move_dis(2) / p_num;
}

void gongjian_cutted::acl_move_nor(set<int3v>& side_cells, int3v& cell_p, vec3& move_nor)
{
	move_nor = { 0.0, 0.0, 0.0 };
	auto itend = side_cells.end();
	for (auto it = side_cells.begin(); it != itend; it++)
	{
		double3v cur_nor = manager_cells.map_pos.find(*it)->second->cal_normal();
		move_nor(0) = move_nor(0) + cur_nor.x;
		move_nor(1) = move_nor(1) + cur_nor.y;
		move_nor(2) = move_nor(2) + cur_nor.z;
	}
	int size_p = side_cells.size();
	move_nor = move_nor / size_p;
}

bool gongjian_cutted::find_cell_u_left(int3v& cur_cell, int3v& aim_cell)
{
	aim_cell = cur_cell;
	//u方向 对应四个面
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_cell);
	if (itout == manager_cells.map_pos.end())
	{
		return 1;
	}
	itout->second->get_all_face_dir_out(cur_out);


	auto itend = manager_cells.map_pos.end();
	if (is_pos_out(5, cur_out)) //上面为外
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 0);
		cal_cell_int3v_side(aim_cell, 3, 1);
		//aim_cell.y = aim_cell.y - gj_acc * 1000 * 2;
		//aim_cell.z = aim_cell.z + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 0);
			//aim_cell.z = aim_cell.z - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 0);
				//aim_cell.z = aim_cell.z - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;	//不能返回false ，必定存在 ，面转向11.25 ???
				}
			}
		}
	}
	if (is_pos_out(4, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 0);
		cal_cell_int3v_side(aim_cell, 3, 0);
		//aim_cell.y = aim_cell.y - 2;
		//aim_cell.z = aim_cell.z - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 1);
			//aim_cell.z = aim_cell.z + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 1);
				//aim_cell.z = aim_cell.z + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(3, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 0);
		cal_cell_int3v_side(aim_cell, 2, 0);
		//aim_cell.z = aim_cell.z - 2;
		//aim_cell.y = aim_cell.y - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 1);
			//aim_cell.y = aim_cell.y + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 1);
				//aim_cell.y = aim_cell.y + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(2, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 1);
		cal_cell_int3v_side(aim_cell, 2, 1);
		//aim_cell.z = aim_cell.z + 2;
		//aim_cell.y = aim_cell.y + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 0);
			//aim_cell.y = aim_cell.y - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 0);
				//aim_cell.y = aim_cell.y - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(1, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 0);
		cal_cell_int3v_side(aim_cell, 1, 1);
		//aim_cell.y = aim_cell.y - 2;
		//aim_cell.x = aim_cell.x + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 0);
			//aim_cell.x = aim_cell.x - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 0);
				//aim_cell.x = aim_cell.x - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(0, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 0);
		cal_cell_int3v_side(aim_cell, 1, 0);
		//aim_cell.y = aim_cell.y - 2;
		//aim_cell.x = aim_cell.x - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 1);
			//aim_cell.x = aim_cell.x + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 1);
				//aim_cell.x = aim_cell.x + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	aim_cell = cur_cell;
	return 0;
}

bool gongjian_cutted::find_cell_u_right(int3v& cur_cell, int3v& aim_cell)
{

	//u方向 对应四个面
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_cell);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (is_pos_out(5, cur_out)) //上面为外
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 1);
		cal_cell_int3v_side(aim_cell, 3, 1);
		//aim_cell.y = aim_cell.y +  2;
		//aim_cell.z = aim_cell.z +  2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 0);
			//aim_cell.z = aim_cell.z - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 0);
				//aim_cell.z = aim_cell.z - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(4, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 1);
		cal_cell_int3v_side(aim_cell, 3, 0);
		//aim_cell.y = aim_cell.y + 2;
		//aim_cell.z = aim_cell.z - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 3, 1);
			//aim_cell.z = aim_cell.z + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 3, 1);
				//aim_cell.z = aim_cell.z + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(3, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 1);
		cal_cell_int3v_side(aim_cell, 2, 0);
		//aim_cell.z = aim_cell.z + 2;
		//aim_cell.y = aim_cell.y - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 1);
			//aim_cell.y = aim_cell.y + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 1);
				//aim_cell.y = aim_cell.y + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(2, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 3, 0);
		cal_cell_int3v_side(aim_cell, 2, 1);
		//aim_cell.z = aim_cell.z - 2;
		//aim_cell.y = aim_cell.y + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 2, 0);
			//aim_cell.y = aim_cell.y - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 2, 0);
				//aim_cell.y = aim_cell.y - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(1, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 1);
		cal_cell_int3v_side(aim_cell, 1, 1);
		//aim_cell.y = aim_cell.y + 2;
		//aim_cell.x = aim_cell.x + 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 0);
			//aim_cell.x = aim_cell.x - 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 0);
				//aim_cell.x = aim_cell.x - 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	if (is_pos_out(0, cur_out))
	{
		aim_cell = cur_cell;
		cal_cell_int3v_side(aim_cell, 2, 1);
		cal_cell_int3v_side(aim_cell, 1, 0);
		//aim_cell.y = aim_cell.y + 2;
		//aim_cell.x = aim_cell.x - 2;
		auto it = manager_cells.map_pos.find(aim_cell);
		if (it != itend)
		{
			return true;
		}
		else
		{
			cal_cell_int3v_side(aim_cell, 1, 1);
			//aim_cell.x = aim_cell.x + 2;
			it = manager_cells.map_pos.find(aim_cell);
			if (it != itend)
			{
				return true;
			}
			else
			{
				cal_cell_int3v_side(aim_cell, 1, 1);
				//aim_cell.x = aim_cell.x + 2;
				it = manager_cells.map_pos.find(aim_cell);
				if (it != itend)
				{
					return true;
				}
				else
				{
					//return false;
				}
			}
		}
	}
	aim_cell = cur_cell;
	return 0;
}

void gongjian_cutted::create_mesh_finish(map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new)
{
	//测试 只显示变形
	//int count_num = 0;
	//auto itend = all_change_cells.end();
	//for (auto it = all_change_cells.begin(); it != itend; it++)
	//{
	//	int3v cur_p = it->first;
	////	//count_num++;
	////	//if (count_num == 2)
	////	//{
	////	//	return;
	////	//}

	int test_num = 1;
	auto itend = manager_cells.map_pos.end();
	for (auto it = manager_cells.map_pos.begin(); it != itend; it++)
	{
		if (test_num == 35)
		{
			int i = 0;
		}
		test_num++;
		//每个点按照统一方式  构建四边形 法向右手定则
		int3v cur_p = it->second->get_int3v();
		double3v cur_temp = cur_p.turn_point_double(gj_acc);

		vector<int3v> polygons;	// 自 前x-  自左y- 前左x-y- 
		//find_cell_polygon_4( cur_p, polygons);		//一个点会产生多个面片 解决 为3的倍数

		find_cell_polygon_4or3(cur_p, all_change_cells, change_cells_new, polygons);	//一个cell会判断多个面 size > 2三角形在里面构建


		if (polygons.size() % 3 == 0 && polygons.size() > 2)
		{
			create_a_mesh(cur_p, all_change_cells, change_cells_new, polygons);
		}
		//11.20 按照size 的个数 决定 构建网格的方式
		//if (polygons.size() == 3)
		//{
		//	create_a_mesh( cur_p, all_change_cells, change_cells_new, polygons);
		//}
		//else if (polygons.size() == 6)
		//{
		//	//有问题 ??? 11.20  16:42
		//	create_few_tri_mesh( cur_p, all_change_cells, change_cells_new, polygons);
		//}


		//测试
		int len = mesh_finish_tri.size();
	}

	//处理不封闭的边  删除边有问题??? 1108
	deal_mesh_line(all_change_cells, change_cells_new);
}

void gongjian_cutted::find_cell_polygon_4(int3v& cur_p, vector<int3v>& polygons)
{
	auto it = manager_cells.map_pos.find(cur_p);
	int fa = it->second->get_num();

	//拿到当前cell所有的外
	vector<int> cur_out;
	it->second->get_all_face_dir_out(cur_out);
	for (int i = 0; i < cur_out.size(); i++)
	{
		int out_pos = cur_out[i];
		//前x-
		int3v front_cell;
		if (find_polygon_front(cur_p, out_pos, front_cell))
		{
			int3v left_cell;
			if (find_polygon_left(cur_p, out_pos, left_cell))
			{
				int3v left_front_cell;
				if (find_polygon_left_and_front(cur_p, out_pos, left_front_cell))//outpos 也要改变 解决
				{
					polygons.push_back(front_cell);
					polygons.push_back(left_cell);
					polygons.push_back(left_front_cell);
				}
			}
		}
	}
}

bool gongjian_cutted::find_polygon_front(int3v& cur_p, int out_pos, int3v& front_p)
{
	front_p = cur_p;
	int cell_w = int(gj_acc * 2 * 1000);
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_p);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (out_pos == 5) //上面为外
	{
		front_p.x = front_p.x - cell_w;
		front_p.z = front_p.z + cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.z = front_p.z - cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.z = front_p.z - cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 4)//下面为外
	{
		front_p.x = front_p.x + cell_w;
		front_p.z = front_p.z - cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.z = front_p.z + cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.z = front_p.z + cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 3)//左面为外
	{
		front_p.x = front_p.x - cell_w;
		front_p.y = front_p.y - cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.y = front_p.y + cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.y = front_p.y + cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 2)	//右
	{
		front_p.x = front_p.x - cell_w;
		front_p.y = front_p.y + cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.y = front_p.y - cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.y = front_p.y - cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 1)	//前
	{
		front_p.z = front_p.z + cell_w;
		front_p.x = front_p.x + cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.x = front_p.x - cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.x = front_p.x - cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 0)	//后
	{
		front_p.z = front_p.z - cell_w;
		front_p.x = front_p.x - cell_w;
		auto it = manager_cells.map_pos.find(front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			front_p.x = front_p.x + cell_w;
			it = manager_cells.map_pos.find(front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				front_p.x = front_p.x + cell_w;
				it = manager_cells.map_pos.find(front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}

bool gongjian_cutted::find_polygon_left(int3v& cur_p, int out_pos, int3v& left_p)
{
	left_p = cur_p;
	int cell_w = int(gj_acc * 2 * 1000);
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_p);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (out_pos == 5) //上面为外
	{
		left_p.y = left_p.y - cell_w;
		left_p.z = left_p.z + cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.z = left_p.z - cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.z = left_p.z - cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 4)//下面为外
	{
		left_p.y = left_p.y - cell_w;
		left_p.z = left_p.z - cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.z = left_p.z + cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.z = left_p.z + cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 3)//左面为外
	{
		left_p.z = left_p.z - cell_w;
		left_p.y = left_p.y - cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.y = left_p.y + cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.y = left_p.y + cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 2)	//右
	{
		left_p.z = left_p.z + cell_w;
		left_p.y = left_p.y + cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.y = left_p.y - cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.y = left_p.y - cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 1)	//前
	{
		left_p.y = left_p.y - cell_w;
		left_p.x = left_p.x + cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.x = left_p.x - cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.x = left_p.x - cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 0)	//后
	{
		left_p.y = left_p.y - cell_w;
		left_p.x = left_p.x - cell_w;
		auto it = manager_cells.map_pos.find(left_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_p.x = left_p.x + cell_w;
			it = manager_cells.map_pos.find(left_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_p.x = left_p.x + cell_w;
				it = manager_cells.map_pos.find(left_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}

bool gongjian_cutted::find_polygon_left_and_front(int3v& cur_p, int out_pos, int3v& left_front_p)
{
	left_front_p = cur_p;
	int cell_w = int(gj_acc * 2 * 1000);
	vector<int> cur_out;
	auto itout = manager_cells.map_pos.find(cur_p);
	itout->second->get_all_face_dir_out(cur_out);

	auto itend = manager_cells.map_pos.end();
	if (out_pos == 5) //上面为外
	{
		left_front_p.y = left_front_p.y - cell_w;
		left_front_p.x = left_front_p.x - cell_w;
		left_front_p.z = left_front_p.z + cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.z = left_front_p.z - cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.z = left_front_p.z - cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 4)//下面为外
	{
		left_front_p.y = left_front_p.y - cell_w;
		left_front_p.x = left_front_p.x + cell_w;
		left_front_p.z = left_front_p.z - cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.z = left_front_p.z + cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.z = left_front_p.z + cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 3)//左面为外
	{
		left_front_p.z = left_front_p.z - cell_w;
		left_front_p.x = left_front_p.x - cell_w;
		left_front_p.y = left_front_p.y - cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.y = left_front_p.y + cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.y = left_front_p.y + cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 2)	//右
	{
		left_front_p.z = left_front_p.z + cell_w;
		left_front_p.x = left_front_p.x - cell_w;
		left_front_p.y = left_front_p.y + cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.y = left_front_p.y - cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.y = left_front_p.y - cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 1)	//前
	{
		left_front_p.y = left_front_p.y - cell_w;
		left_front_p.z = left_front_p.z + cell_w;
		left_front_p.x = left_front_p.x + cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.x = left_front_p.x - cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.x = left_front_p.x - cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (out_pos == 0)	//后
	{
		left_front_p.y = left_front_p.y - cell_w;
		left_front_p.z = left_front_p.z - cell_w;
		left_front_p.x = left_front_p.x - cell_w;
		auto it = manager_cells.map_pos.find(left_front_p);
		if (it != itend)
		{
			return true;
		}
		else
		{
			left_front_p.x = left_front_p.x + cell_w;
			it = manager_cells.map_pos.find(left_front_p);
			if (it != itend)
			{
				return true;
			}
			else
			{
				left_front_p.x = left_front_p.x + cell_w;
				it = manager_cells.map_pos.find(left_front_p);
				if (it != itend)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}

void gongjian_cutted::find_cell_polygon_4or3(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons)
{
	auto it = manager_cells.map_pos.find(cur_p);
	int fa = it->second->get_num();

	//拿到当前cell所有的外
	vector<int> cur_out;
	it->second->get_all_face_dir_out(cur_out);

	//11.21 改
	//一个cell  1、有两个外面 选择一个最终的外  
	// 2、三个外面 有两个最终外 或  一个
	//deal_cell_finish_out(cur_out);	//??? 去重有效就不用判断面的转向 11.23

	//前 左 固定  左前按照面位置找
	//前左判断重合情况

	set<int3v> set_cells;
	for (int i = 0; i < cur_out.size(); i++)
	{
		int out_pos = cur_out[i];
		if (out_pos == -1)
		{
			continue;
		}
		//前x-
		int3v front_cell;
		if (find_polygon_front(cur_p, out_pos, front_cell))
		{
			int3v left_cell;
			if (find_polygon_left(cur_p, out_pos, left_cell))
			{
				int3v left_front_cell;
				if (find_polygon_left_and_front(cur_p, out_pos, left_front_cell))
				{
					set<int3v> set_cells_left;
					find_polygon_front_and_left(front_cell, set_cells_left);
					if (set_cells_left.find(left_cell) != set_cells_left.end())	//点重合 为三角  
					{
						create_tri_mesh(cur_p, front_cell, left_cell, all_change_cells, change_cells_new);
					}
					else
					{
						polygons.push_back(front_cell);		//三个方向同时存在
						polygons.push_back(left_cell);
						polygons.push_back(left_front_cell);
					}
				}
				else
				{
					if (set_cells.find(front_cell) != set_cells.end() && set_cells.find(left_cell) != set_cells.end())
					{
					}
					else
					{
						create_tri_mesh(cur_p, front_cell, left_cell, all_change_cells, change_cells_new);	//前 左 0
					}
				}
			}
			else
			{
				int3v left_front_cell;
				if (find_polygon_left_and_front(cur_p, out_pos, left_front_cell))
				{
					if (set_cells.find(front_cell) != set_cells.end() && set_cells.find(left_front_cell) != set_cells.end())
					{
					}
					else
					{
						create_tri_mesh(cur_p, front_cell, left_front_cell, all_change_cells, change_cells_new);// 前 0 斜
					}

				}
			}
		}
		else
		{
			int3v left_cell;
			if (find_polygon_left(cur_p, out_pos, left_cell))
			{
				int3v left_front_cell;
				if (find_polygon_left_and_front(cur_p, out_pos, left_front_cell))
				{
					//三角在四边形中已经包含 解决
					if (set_cells.find(left_cell) != set_cells.end() && set_cells.find(left_front_cell) != set_cells.end())
					{
					}
					else
					{	//逆时针构建 11.15
						create_tri_mesh(cur_p, left_front_cell, left_cell, all_change_cells, change_cells_new);	// 0 左 斜
					}
				}
			}
		}
	}
}

void gongjian_cutted::deal_cell_finish_out(vector<int>& cur_out)
{

	int len = cur_out.size();
	if (len == 1)
	{
		return;
	}
	if (len == 2)
	{
		if (cur_out[0] == 0)	//bcak
		{
			switch (cur_out[1])
			{
			case 5:
				cur_out.pop_back();	//up
				break;
			case 4:
				cur_out.erase(cur_out.begin());
				break;
			case 3:
				cur_out.pop_back();
				break;
			case 2:
				cur_out.pop_back();
				break;
			default:
				break;
			}
			return;
		}
		if (cur_out[0] == 1)	//front
		{
			switch (cur_out[1])
			{
			case 5:
				cur_out.erase(cur_out.begin());	//up
				break;
			case 4:
				cur_out.pop_back();
				break;
			case 3:
				cur_out.erase(cur_out.begin());
				break;
			case 2:
				//cur_out.erase(cur_out.begin());
				break;
			default:
				break;
			}
			return;
		}
		if (cur_out[0] == 2)	//right
		{
			switch (cur_out[1])
			{
			case 5:
				cur_out.erase(cur_out.begin());
				break;
			default:
				break;
			}
			return;
		}
		if (cur_out[0] == 3)	//left
		{
			cur_out.pop_back();
		}
		return;
	}

	//if (len == 3)	//三个外也可能相对
	//{
	//	{
	//		bool is_op = false;
	//		for (int i = 0; i <= cur_out.size() - 1; i++)
	//		{
	//			int cur = cur_out[i];
	//			if (cur % 2 == 0 && cur == cur_out[i + 1] - 1)
	//			{
	//				cur_out[i] = -1;	//前面的删除也可替换为-1 ???
	//				i++;
	//				cur_out[i] = -1;
	//				is_op = true;
	//			}
	//		}
	//		if (is_op)
	//		{
	//			return;
	//		}
	//	}
	//	if (cur_out[0] == 0)	//bcak
	//	{
	//		if (cur_out[1] == 2)
	//		{
	//			if (cur_out[2] == 5)	//最终一个外  >>保留两个  11.23
	//			{
	//				auto it = cur_out.begin(); it++;
	//				cur_out.erase(it);
	//				cur_out.pop_back();
	//			}
	//			if (cur_out[2] == 4)	//save down
	//			{
	//				cur_out.erase(cur_out.begin());
	//				cur_out.erase(cur_out.begin());
	//			}
	//		}
	//		if (cur_out[1] == 3)
	//		{
	//			if (cur_out[2] == 5)	//后左上 save left
	//			{
	//				cur_out.pop_back();
	//				
	//			}
	//			if (cur_out[2] == 4)	//save down
	//			{
	//				cur_out.erase(cur_out.begin());
	//				cur_out.erase(cur_out.begin());
	//			}
	//		}
	//	}
	//	if (cur_out[0] == 1)	//front
	//	{
	//		if (cur_out[1] == 2)
	//		{
	//			if (cur_out[2] == 5)	//save up
	//			{
	//				cur_out.erase(cur_out.begin());
	//				cur_out.erase(cur_out.begin());
	//			}
	//			else
	//			{
	//				cur_out.pop_back();
	//			}
	//		}
	//		if (cur_out[1] == 3)	 
	//		{
	//			if (cur_out[2] == 5)	//save left
	//			{
	//				cur_out.pop_back();
	//				cur_out.erase(cur_out.begin());
	//			}
	//			if (cur_out[2] == 4)	//save down
	//			{
	//				cur_out.erase(cur_out.begin());
	//				cur_out.erase(cur_out.begin());
	//			}
	//		}
	//	}
	//	return;
	//}
	//把相对的外面都删除 
	{
		for (int i = 0; i <= cur_out.size() - 1; i++)
		{
			int cur = cur_out[i];
			if (cur % 2 == 0 && cur == cur_out[i + 1] - 1)
			{
				cur_out[i] = -1;	//前面的删除也可替换为-1 ???
				i++;
				cur_out[i] = -1;
			}
		}
	}
}

void gongjian_cutted::create_tri_mesh(int3v& cur_p, int3v& p1, int3v& p2, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new)
{
	int cur_color = 0;
	{
		int temp_color = 0;
		temp_color = manager_cells.map_pos.find(cur_p)->second->count_cut;
		cur_color = temp_color > cur_color ? temp_color : cur_color;
		temp_color = manager_cells.map_pos.find(p1)->second->count_cut;
		cur_color = temp_color > cur_color ? temp_color : cur_color;
		temp_color = manager_cells.map_pos.find(p2)->second->count_cut;
		cur_color = temp_color > cur_color ? temp_color : cur_color;
	}
	mesh_tri temp_tri;
	temp_tri.color = cur_color;
	auto itp1 = all_change_cells.find(cur_p);
	if (itp1 != all_change_cells.end())	//初始点就是变形平滑后的要更新  之前会出现四边形不封闭
	{
		temp_tri.p1 = change_cells_new[itp1->second];
	}
	else
	{
		temp_tri.p1 = cur_p.turn_point_double(gj_acc);
	}

	itp1 = all_change_cells.find(p1);
	if (itp1 != all_change_cells.end())
	{
		temp_tri.p2 = change_cells_new[itp1->second];
	}
	else
	{
		temp_tri.p2 = p1.turn_point_double(gj_acc);
	}
	itp1 = all_change_cells.find(p2);
	if (itp1 != all_change_cells.end())
	{
		temp_tri.p3 = change_cells_new[itp1->second];
	}
	else
	{
		temp_tri.p3 = p2.turn_point_double(gj_acc);
	}
	//放入网格容器
	if (!is_tri_mesh_eixst(temp_tri))
	{
		if (is_line_eixst(temp_tri))
		{
			mesh_finish_tri.emplace_back(temp_tri);
			insert_line(temp_tri);
		}
	}
}

void gongjian_cutted::set_color_list()
{
	for (int i = 0; i < color_list_size; i++)
	{
		::gladLoadGL();
		glNewList(color_list_start + i, GL_COMPILE); // 开始记录绘制命令

		{
			//设置OpenGL材料  10.23   作用于后面glPushMatrix(); 11.3
			GLfloat ambient[] = { i / 10.0, i / 10.0, i / 10.0, 1.0 };
			GLfloat diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
			GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat shininess[] = { 0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		}

		glEndList(); // 结束记录
	}
}

void gongjian_cutted::create_a_mesh(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons)
{
	mesh_cutted mesh_temp;
	char cur_color = 0;	//边界过度颜色控制 可以判别修改 11.27 ???
	auto itp1 = all_change_cells.find(cur_p);
	char temp_color = manager_cells.map_pos.find(cur_p)->second->count_cut;
	cur_color = cur_color < temp_color ? temp_color : cur_color;
	if (itp1 != all_change_cells.end())	//初始点就是变形平滑后的要更新  之前会出现四边形不封闭
	{
		mesh_temp.p1 = change_cells_new[itp1->second];
	}
	else
	{
		mesh_temp.p1 = cur_p.turn_point_double(gj_acc);
	}
	for (int i = 0; i < polygons.size(); i = i + 3)
	{
		auto ittemp = all_change_cells.find(polygons[i]);
		temp_color = manager_cells.map_pos.find(polygons[i])->second->count_cut;
		cur_color = cur_color < temp_color ? temp_color : cur_color;

		if (ittemp != all_change_cells.end())
		{
			mesh_temp.p2 = change_cells_new[ittemp->second];
		}
		else
		{
			mesh_temp.p2 = polygons[i].turn_point_double(gj_acc);
		}
		ittemp = all_change_cells.find(polygons[i + 1]);
		temp_color = manager_cells.map_pos.find(polygons[i + 1])->second->count_cut;
		cur_color = cur_color < temp_color ? temp_color : cur_color;
		if (ittemp != all_change_cells.end())
		{
			mesh_temp.p3 = change_cells_new[ittemp->second];
		}
		else
		{
			mesh_temp.p3 = polygons[i + 1].turn_point_double(gj_acc);
		}
		ittemp = all_change_cells.find(polygons[i + 2]);
		temp_color = manager_cells.map_pos.find(polygons[i + 2])->second->count_cut;
		cur_color = cur_color < temp_color ? temp_color : cur_color;
		if (ittemp != all_change_cells.end())
		{
			mesh_temp.p4 = change_cells_new[ittemp->second];
		}
		else
		{
			mesh_temp.p4 = polygons[i + 2].turn_point_double(gj_acc);
		}
		//放入网格容器  换为往三角形网格容器里放 11.07
		//mesh_temp.color = cur_color;
		//mesh_finish.emplace_back(mesh_temp);


		//对四边形去重 解决  》》 
		//四边形 分解两种三角，三角去重产生三角时覆盖11.14
		//四边形分解两个三角形时，加约束  11.14

		discolse_4_to_3(mesh_temp, cur_color);		//最开始没有
		//不能直接放  分解优先级 11.22 两个没有可以放，如果一个有 一个没有 ：优先

		{

			mesh_tri tri_temp;
			tri_temp.p1 = mesh_temp.p1;
			tri_temp.p2 = mesh_temp.p2;
			tri_temp.p3 = mesh_temp.p3;
			//is_mesh_eixst(tri_temp);
			push_tri_to_check(tri_temp);
			//push_tri_to_container(mesh_temp.p1, mesh_temp.p2, mesh_temp.p3, cur_color);

			tri_temp.p1 = mesh_temp.p2;
			tri_temp.p2 = mesh_temp.p4;
			tri_temp.p3 = mesh_temp.p3;
			//is_mesh_eixst(tri_temp);
			push_tri_to_check(tri_temp);
			//push_tri_to_container(mesh_temp.p2, mesh_temp.p4, mesh_temp.p3, cur_color);

			tri_temp.p1 = mesh_temp.p1;
			tri_temp.p2 = mesh_temp.p2;
			tri_temp.p3 = mesh_temp.p4;
			//is_mesh_eixst(tri_temp);
			push_tri_to_check(tri_temp);
			//push_tri_to_container(mesh_temp.p1, mesh_temp.p2, mesh_temp.p4, cur_color);

			tri_temp.p1 = mesh_temp.p1;
			tri_temp.p2 = mesh_temp.p4;
			tri_temp.p3 = mesh_temp.p3;
			//is_mesh_eixst(tri_temp);
			push_tri_to_check(tri_temp);
			//push_tri_to_container(mesh_temp.p1, mesh_temp.p4, mesh_temp.p3, cur_color);
		}
		if (polygons.size() == 9)	//三个外面都要产生网格必定重复遮挡 11.16
		{
			return;
		}
	}
}

//void gongjian_cutted::mesh_sub_loop_of_cut()
//{
//	//取出没变形的三角网格
//	for (int i = 0; i < mesh_finish_tri.size(); i++ )
//	{
//		if (mesh_finish_tri[i].color == 0)
//		{
//			mesh_tri temp;
//			temp.p1 = mesh_finish_tri[i].p1;
//			temp.p2 = mesh_finish_tri[i].p2;
//			temp.p3 = mesh_finish_tri[i].p3;
//			mesh_finish_tri.emplace_back(temp);
//			//mesh_finish.erase(it);
//		}
//		else
//		{
//			//可以优化容器大小  ???
//		}
//	}
//
//	//同刀序 loop一次 先取出
//	for (int i = 0 + 1; i < color_list_size; i++)
//	{
//		vector<tri_loop> a_cut_mesh;
//		for (int j = 0; j <  mesh_finish_tri.size(); j++)
//		{
//			if (mesh_finish_tri[j].color == i)
//			{
//				tri_loop temp;
//				temp.color = i;
//				temp.p1 = mesh_finish_tri[j].p1;
//				temp.p2 = mesh_finish_tri[j].p2;
//				temp.p3 = mesh_finish_tri[j].p3;
//				a_cut_mesh.emplace_back(temp);
//				//mesh_finish.erase(it);
//			}
//			else
//			{
//				//it++;
//			}
//		}
//		//构建相邻关系 确定边的对点
//		/*create_relation(a_cut_mesh);
//		loop_vec_tri(a_cut_mesh);*/
//		/*mesh_sub_loop cur_sub(a_cut_mesh);
//		cur_sub.create_relation();
//		cur_sub.loop_vec_tri();*/
//	}
//}

void gongjian_cutted::cal_cell_int3v_side(int3v& aim_cell, int XYZ, bool ADD)
{
	if (XYZ == 1)
	{
		if (ADD)
		{
			aim_cell.x = aim_cell.x + gj_acc * 1000 * 2;
		}
		else
		{
			aim_cell.x = aim_cell.x - gj_acc * 1000 * 2;
		}
		return;
	}
	if (XYZ == 2)
	{
		if (ADD)
		{
			aim_cell.y = aim_cell.y + gj_acc * 1000 * 2;
		}
		else
		{
			aim_cell.y = aim_cell.y - gj_acc * 1000 * 2;
		}
		return;
	}
	if (XYZ == 3)
	{
		if (ADD)
		{
			aim_cell.z = aim_cell.z + gj_acc * 1000 * 2;
		}
		else
		{
			aim_cell.z = aim_cell.z - gj_acc * 1000 * 2;
		}
		return;
	}
}

void gongjian_cutted::insert_line(mesh_tri& tri_temp)
{
	int3v start = tri_temp.p1.turn_point_int(gj_acc);
	int3v end = tri_temp.p2.turn_point_int(gj_acc);
	int3v line_temp;
	line_temp.x = (start.x + end.x) / 2;
	line_temp.y = (start.y + end.y) / 2;
	line_temp.z = (start.z + end.z) / 2;

	pair<int3v, int3v> pair_temp = { start, end };
	if (mesh_line.find(line_temp) != mesh_line.end())	//存在
	{
		mesh_line.erase(line_temp);
	}
	else
	{
		mesh_line.insert({ line_temp, pair_temp });
		test_line.push_back({ start,end });
	}

	start = tri_temp.p2.turn_point_int(gj_acc);
	end = tri_temp.p3.turn_point_int(gj_acc);
	line_temp.x = (start.x + end.x) / 2;
	line_temp.y = (start.y + end.y) / 2;
	line_temp.z = (start.z + end.z) / 2;
	pair_temp = { start, end };
	if (mesh_line.find(line_temp) != mesh_line.end())	//存在
	{
		mesh_line.erase(line_temp);
	}
	else
	{
		mesh_line.insert({ line_temp, pair_temp });
		test_line.push_back({ start,end });
	}

	start = tri_temp.p3.turn_point_int(gj_acc);
	end = tri_temp.p1.turn_point_int(gj_acc);
	line_temp.x = (start.x + end.x) / 2;
	line_temp.y = (start.y + end.y) / 2;
	line_temp.z = (start.z + end.z) / 2;
	pair_temp = { start, end };
	if (mesh_line.find(line_temp) != mesh_line.end())	//存在
	{
		mesh_line.erase(line_temp);
	}
	else
	{
		mesh_line.insert({ line_temp, pair_temp });
		test_line.push_back({ start,end });
	}
}

void gongjian_cutted::deal_mesh_line(map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new)
{
	//最后剩余边不一定会首位顺序相连  》》创建单个三角顺序没有逆时针??? 11.15
	multimap<int3v, int3v> temp_line;
	for (auto it = mesh_line.begin(); it != mesh_line.end(); it++)
	{
		temp_line.insert({ it->second.first, it->second.second });
	}
	//mesh_line.clear();
	//存在一个起点 不同终点的情况
	int cur_color = 0;
	int temp_color = 0;
	while (!temp_line.empty())
	{
		auto it = temp_line.begin();
		int3v start = it->first;
		int3v end = it->second;
		/*{
			temp_color = manager_cells.map_pos.find(start)->second->count_cut;
			cur_color = temp_color > cur_color ? temp_color : cur_color;
		}*/

		int num1 = temp_line.count(end);
		auto it_l2_start = temp_line.find(end);
		for (int i = 0; i < num1; i++)
		{
			if (it_l2_start != temp_line.end())
			{
				int3v l2_start = it_l2_start->first;
				int3v l2_end = it_l2_start->second;
				/*{
					temp_color = manager_cells.map_pos.find(start)->second->count_cut;
					cur_color = temp_color > cur_color ? temp_color : cur_color;
				}*/
				int num2 = temp_line.count(l2_end);
				auto it_l3_start = temp_line.find(l2_end);	//会有两个
				for (int j = 0; j < num2; j++)
				{
					int3v l3_start = it_l3_start->first;
					int3v l3_end = it_l3_start->second;
					/*{
						temp_color = manager_cells.map_pos.find(start)->second->count_cut;
						cur_color = temp_color > cur_color ? temp_color : cur_color;
					}*/
					if (temp_line.find(l3_end) == temp_line.begin())	//l3的end 等于start
					{
						//构建一个三角 删除三边 
						//用改变后的数据
						mesh_tri mesh_temp;
						cur_color = 0;
						auto itp1 = all_change_cells.find(start);
						if (itp1 != all_change_cells.end())
						{
							mesh_temp.p1 = change_cells_new[itp1->second];
							mesh_temp.color = manager_cells.map_pos.find(itp1->first)->second->count_cut;
						}
						else
						{
							mesh_temp.p1 = start.turn_point_double(gj_acc);
						}
						//temp_color = manager_cells.map_pos.find(itp1->first)->second->count_cut;
						//cur_color = temp_color > cur_color ? temp_color : cur_color;
						auto itp2 = all_change_cells.find(end);
						if (itp2 != all_change_cells.end())
						{
							mesh_temp.p2 = change_cells_new[itp2->second];
							mesh_temp.color = manager_cells.map_pos.find(itp2->first)->second->count_cut;
						}
						else
						{
							mesh_temp.p2 = end.turn_point_double(gj_acc);
						}
						//temp_color = manager_cells.map_pos.find(itp2->first)->second->count_cut;
						//cur_color = temp_color > cur_color ? temp_color : cur_color;
						auto itp3 = all_change_cells.find(l2_end);
						if (itp3 != all_change_cells.end())
						{
							mesh_temp.p3 = change_cells_new[itp3->second];
							mesh_temp.color = manager_cells.map_pos.find(itp3->first)->second->count_cut;
						}
						else
						{
							mesh_temp.p3 = l2_end.turn_point_double(gj_acc);
						}
						//temp_color = manager_cells.map_pos.find(itp3->first)->second->count_cut;
						//cur_color = temp_color > cur_color ? temp_color : cur_color;
						//mesh_temp.color = cur_color;
						mesh_finish_tri.emplace_back(mesh_temp);
					}
					it_l3_start++;
				}
			}
			it_l2_start++;
		}
		temp_line.erase(it);
	}
}

bool gongjian_cutted::is_tri_mesh_eixst(mesh_tri& mesh_temp)
{
	int3v center;
	int3v p1 = mesh_temp.p1.turn_point_int(gj_acc);
	int3v p2 = mesh_temp.p2.turn_point_int(gj_acc);
	int3v p3 = mesh_temp.p3.turn_point_int(gj_acc);
	center.x = (p1.x + p2.x + p3.x) / 3;
	center.y = (p1.y + p2.y + p3.y) / 3;
	center.z = (p1.z + p2.z + p3.z) / 3;
	if (mesh_three.find(center) != mesh_three.end())
	{
		if (is_nor_equal(mesh_temp, center))	//重心可能会重合 重合在加判断 ???  11.22 15:54	
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//mesh_three.insert(center); //只判断 不放入 11.21
		return false;
	}
}

bool gongjian_cutted::is_nor_equal(mesh_tri& mesh_temp, int3v& tri_center)
{
	auto it = mesh_three.find(tri_center);
	mesh_tri tri_old = it->second;
	vec3 v_new1 = { mesh_temp.p1.x, mesh_temp.p1.y, mesh_temp.p1.z };
	vec3 v_new2 = { mesh_temp.p2.x, mesh_temp.p2.y, mesh_temp.p2.z };
	vec3 v_new3 = { mesh_temp.p3.x, mesh_temp.p3.y, mesh_temp.p3.z };

	vec3 v_old1 = { tri_old.p1.x, tri_old.p1.y, tri_old.p1.z };
	vec3 v_old2 = { tri_old.p2.x, tri_old.p2.y, tri_old.p2.z };
	vec3 v_old3 = { tri_old.p3.x, tri_old.p3.y, tri_old.p3.z };

	vec3 nor_new = cross(v_new2 - v_new1, v_new3 - v_new1);
	vec3 nor_old = cross(v_old2 - v_old1, v_old3 - v_old1);

	if (norm(nor_new - nor_old) < 0.01)	//表示法向相同
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool gongjian_cutted::is_line_eixst(mesh_tri& temp_tri)
{
	int3v p1 = temp_tri.p1.turn_point_int(gj_acc);
	int3v p2 = temp_tri.p2.turn_point_int(gj_acc);
	int3v p3 = temp_tri.p3.turn_point_int(gj_acc);
	int3v line1;
	line1.x = (p1.x + p2.x) / 2;
	line1.y = (p1.y + p2.y) / 2;
	line1.z = (p1.z + p2.z) / 2;
	auto it = all_line.find(line1);
	if (it != all_line.end())
	{
		if (it->second == 1)
		{
			it->second++;
		}
		else
		{
			return false;
		}
	}
	int3v line2;
	line2.x = (p2.x + p3.x) / 2;
	line2.y = (p2.y + p3.y) / 2;
	line2.z = (p2.z + p3.z) / 2;
	it = all_line.find(line2);
	if (it != all_line.end())
	{
		if (it->second == 1)
		{
			it->second++;
		}
		else
		{
			return false;
		}
	}
	int3v line3;
	line3.x = (p3.x + p1.x) / 2;
	line3.y = (p3.y + p1.y) / 2;
	line3.z = (p3.z + p1.z) / 2;
	it = all_line.find(line3);
	if (it != all_line.end())
	{
		if (it->second == 1)
		{
			it->second++;
		}
		else
		{
			return false;
		}
	}
	//all_line.insert({ line1, 1 });
	//all_line.insert({ line2, 1 });
	//all_line.insert({ line3, 1 });
	return true;
}

void gongjian_cutted::discolse_4_to_3(mesh_cutted& mesh_temp, char cur_color)
{
	//两个没有可以放，如果一个有 一个没有 ：优先
	bool is_push = 0;
	mesh_tri tri_temp1;
	tri_temp1.color = cur_color;
	tri_temp1.p1 = mesh_temp.p1;
	tri_temp1.p2 = mesh_temp.p2;
	tri_temp1.p3 = mesh_temp.p3;

	mesh_tri tri_temp2;
	tri_temp2.color = cur_color;
	tri_temp2.p1 = mesh_temp.p2;
	tri_temp2.p2 = mesh_temp.p4;
	tri_temp2.p3 = mesh_temp.p3;
	if (!is_tri_mesh_eixst(tri_temp1) && !is_tri_mesh_eixst(tri_temp2))	//不会两个都存在
	{
		is_push = 1;
	}
	if ((!is_tri_mesh_eixst(tri_temp1) && is_tri_mesh_eixst(tri_temp2))
		|| (is_tri_mesh_eixst(tri_temp1) && !is_tri_mesh_eixst(tri_temp2))) //只一个存在
	{
		push_tri_to_container(mesh_temp.p1, mesh_temp.p2, mesh_temp.p3, cur_color);
		push_tri_to_container(mesh_temp.p2, mesh_temp.p4, mesh_temp.p3, cur_color);
		push_tri_to_check(tri_temp1);
		push_tri_to_check(tri_temp2);
		return;
	}

	tri_temp1.color = cur_color;
	tri_temp1.p1 = mesh_temp.p1;
	tri_temp1.p2 = mesh_temp.p2;
	tri_temp1.p3 = mesh_temp.p4;

	tri_temp2.color = cur_color;
	tri_temp2.p1 = mesh_temp.p1;
	tri_temp2.p2 = mesh_temp.p4;
	tri_temp2.p3 = mesh_temp.p3;
	if ((!is_tri_mesh_eixst(tri_temp1) && is_tri_mesh_eixst(tri_temp2))
		|| (is_tri_mesh_eixst(tri_temp1) && !is_tri_mesh_eixst(tri_temp2)))
	{
		push_tri_to_container(mesh_temp.p1, mesh_temp.p2, mesh_temp.p4, cur_color);
		push_tri_to_container(mesh_temp.p1, mesh_temp.p4, mesh_temp.p3, cur_color);
		push_tri_to_check(tri_temp1);
		push_tri_to_check(tri_temp2);
		return;
	}

	if (is_push)
	{
		push_tri_to_container(mesh_temp.p1, mesh_temp.p2, mesh_temp.p3, cur_color);
		push_tri_to_container(mesh_temp.p2, mesh_temp.p4, mesh_temp.p3, cur_color);
		return;
	}
}

void gongjian_cutted::push_tri_to_container(double3v& p1, double3v& p2, double3v& p3, char cur_color)
{
	mesh_tri tri_temp;
	tri_temp.color = cur_color;
	tri_temp.p1 = p1;
	tri_temp.p2 = p2;
	tri_temp.p3 = p3;

	if (!is_tri_mesh_eixst(tri_temp))
	{
		if (is_line_eixst(tri_temp))	//边去重 放多了???  只判断 不存放
		{
			mesh_finish_tri.emplace_back(tri_temp);
			//mesh_three.insert(center);
			insert_line(tri_temp);
		}
	}
}

void gongjian_cutted::push_tri_to_check(mesh_tri& tri_temp)
{
	int3v center;
	int3v c1 = tri_temp.p1.turn_point_int(gj_acc);
	int3v c2 = tri_temp.p2.turn_point_int(gj_acc);
	int3v c3 = tri_temp.p3.turn_point_int(gj_acc);
	center.x = (c1.x + c2.x + c3.x) / 3;
	center.y = (c1.y + c2.y + c3.y) / 3;
	center.z = (c1.z + c2.z + c3.z) / 3;

	if (!is_tri_mesh_eixst(tri_temp))
	{
		mesh_three.insert({ center, tri_temp });
	}
}

void gongjian_cutted::find_polygon_front_and_left(int3v& front_cell, set<int3v>& set_cells)
{
	//拿到当前cell所有的外
	auto it = manager_cells.map_pos.find(front_cell);
	vector<int> cur_out;
	it->second->get_all_face_dir_out(cur_out);	//当有三个外 有两个左重复 删除
	for (int i = 0; i < cur_out.size(); i++)
	{
		int out_pos = cur_out[i];
		int3v left_cell;
		if (find_polygon_left(front_cell, out_pos, left_cell))
		{
			if (set_cells.find(left_cell) != set_cells.end())	//???
			{
				set_cells.erase(left_cell);
			}
			else
			{
				set_cells.insert(left_cell);
			}
		}
	}
}

void gongjian_cutted::create_few_tri_mesh(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons)
{
	//对构成网格的点去重 6个点 两个四边形 三角有重复 才正确>> 三个三角 
	//unordered_set  需要自定义比较

	mesh_tri mesh_temp;
	double3v p1, p2, p3, p4;
	char cur_color = 0;
	get_a_cell_real_value(cur_p, all_change_cells, change_cells_new, p1, cur_color);
	get_a_cell_real_value(polygons[0], all_change_cells, change_cells_new, p2, cur_color);
	get_a_cell_real_value(polygons[1], all_change_cells, change_cells_new, p3, cur_color);
	get_a_cell_real_value(polygons[2], all_change_cells, change_cells_new, p4, cur_color);

	push_tri_to_container(p1, p2, p3, cur_color);
	push_tri_to_container(p2, p4, p3, cur_color);

	//处理第二个四边形  
	get_a_cell_real_value(polygons[3], all_change_cells, change_cells_new, p2, cur_color);
	get_a_cell_real_value(polygons[4], all_change_cells, change_cells_new, p3, cur_color);
	get_a_cell_real_value(polygons[5], all_change_cells, change_cells_new, p4, cur_color);

	mesh_tri tri_temp1;
	tri_temp1.color = cur_color;
	tri_temp1.p1 = p1;
	tri_temp1.p2 = p2;
	tri_temp1.p3 = p3;

	mesh_tri tri_temp2;
	tri_temp2.color = cur_color;
	tri_temp2.p1 = p2;
	tri_temp2.p2 = p4;
	tri_temp2.p3 = p3;
	if (is_tri_mesh_eixst(tri_temp1) || is_tri_mesh_eixst(tri_temp2))	//分解只有两种情况
	{
		push_tri_to_container(p1, p2, p3, cur_color);
		push_tri_to_container(p2, p4, p3, cur_color);
		return;
	}

	tri_temp1.color = cur_color;
	tri_temp1.p1 = p1;
	tri_temp1.p2 = p2;
	tri_temp1.p3 = p4;

	tri_temp2.color = cur_color;
	tri_temp2.p1 = p1;
	tri_temp2.p2 = p4;
	tri_temp2.p3 = p3;
	if (is_tri_mesh_eixst(tri_temp1) || is_tri_mesh_eixst(tri_temp2))	//分解只有两种情况
	{
		push_tri_to_container(p1, p2, p4, cur_color);
		push_tri_to_container(p1, p4, p3, cur_color);
		return;
	}
}

void gongjian_cutted::get_a_cell_real_value(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, double3v& cur_cell, char cur_color)
{
	auto itp1 = all_change_cells.find(cur_p);
	char temp_color = manager_cells.map_pos.find(cur_p)->second->count_cut;
	cur_color = cur_color < temp_color ? temp_color : cur_color;
	if (itp1 != all_change_cells.end())
	{
		cur_cell = change_cells_new[itp1->second];
	}
	else
	{
		cur_cell = cur_p.turn_point_double(gj_acc);
	}
}



gongjian::gongjian()
{

}


gongjian::~gongjian()
{
}

//工件位置变换

void gongjian::set_position(vec3& p, mat& mat3)
{
	JC_O_GJ = p;
	JC_SYS_GJ = mat3;
}


//获取工件位置

vec3 gongjian::get_O()
{
	return JC_O_GJ;
}

//获取工件姿态

mat33 gongjian::get_SYS()
{
	return JC_SYS_GJ;
}

gongjian::gongjian(string& file, vec trans, double acc)
{
	vec3 v3_o = { 0,0,0 };
	mat33 m3_sys(fill::eye);
	set_position(v3_o, m3_sys);
	init_gj_by_stl(file, trans, acc);
}

gongjian::gongjian(double D, double len, double acc_d)
{
	vec3 v3_o = { 10,20,30 };
	mat33 m3_sys(fill::eye);
	m3_sys = -m3_sys;
	set_position(v3_o, m3_sys);
	init_gj_by_col(D, len, acc_d);
}

gongjian::gongjian(mat& gj_outline, double acc_d)
{
	vec3 v3_o = { 0,0,0 };
	mat33 m3_sys(fill::eye);
	set_position(v3_o, m3_sys);
	init_gj_by_rot(gj_outline, acc_d);
}

gongjian_col::gongjian_col()
{
}

gongjian_col::~gongjian_col()
{
}

void gongjian_col::set_col_var(double D, double len)
{
	col_D = D;
	col_len = len;
}

void gongjian_col::get_col_tri_nor(vector<double3v>& ans_points, vector<double3v>& ans_normals, double acc_in)
{
	//1、生成底面三角形，及圆周法向
	//2、生成顶面三角形
	vector<vec3> dwon_point;
	vector<vec3> dwon_nor;
	vector<vec3> up_point;
	gen_down_point(dwon_point, dwon_nor, up_point, acc_in);
	
	//3、构造三角形，及法向
	int count = dwon_point.size() - 1;
	vec3 p1_dwon = { 0.0, 0.0, 0.0 };	//原点  
	vec3 nor1_dwon = { 0.0, 0.0, -1.0 }; //底面法向
	vec3 p1_up = { 0.0, 0.0, col_len }; //上顶面中心
	vec3 nor1_up = { 0.0, 0.0, 1.0 };   //  
	for (int i = 0; i < count; i++) //三角顺序 不影响后续加密 一次循环更好
	{
		//底面三角
		double3v p2_dwon = dwon_point[i];
		double3v p3_dwon = dwon_point[i + 1];
		ans_points.emplace_back(p1_dwon);
		ans_points.emplace_back(p2_dwon);
		ans_points.emplace_back(p3_dwon);
		ans_normals.emplace_back(nor1_dwon);
		ans_normals.emplace_back(nor1_dwon);
		ans_normals.emplace_back(nor1_dwon);
		//顶面三角
		double3v p2_up = up_point[i];
		double3v p3_up = up_point[i + 1];
		ans_points.emplace_back(p1_up);
		ans_points.emplace_back(p2_up);
		ans_points.emplace_back(p3_up);
		ans_normals.emplace_back(nor1_up);
		ans_normals.emplace_back(nor1_up);
		ans_normals.emplace_back(nor1_up);
		//ce面  上下四个点 两个三角
		double3v nor_c = dwon_nor[i];
		ans_points.emplace_back(p2_dwon);
		ans_points.emplace_back(p3_dwon);
		ans_points.emplace_back(p2_up);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);

		ans_points.emplace_back(p2_up);
		ans_points.emplace_back(p3_up);
		ans_points.emplace_back(p3_dwon);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
	}
	//4、收尾 循环差一个
	{
		ans_points.emplace_back(p1_dwon);
		ans_points.emplace_back(dwon_point.front());
		ans_points.emplace_back(dwon_point.back());
		ans_normals.emplace_back(nor1_dwon);
		ans_normals.emplace_back(nor1_dwon);
		ans_normals.emplace_back(nor1_dwon);

		ans_points.emplace_back(p1_up);
		ans_points.emplace_back(up_point.front());
		ans_points.emplace_back(up_point.back());
		ans_normals.emplace_back(nor1_up);
		ans_normals.emplace_back(nor1_up);
		ans_normals.emplace_back(nor1_up);

		double3v nor_c = dwon_nor.back();
		ans_points.emplace_back(dwon_point.front());
		ans_points.emplace_back(dwon_point.back());
		ans_points.emplace_back(up_point.back());
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);

		ans_points.emplace_back(up_point.front());
		ans_points.emplace_back(up_point.back());
		ans_points.emplace_back(dwon_point.front());
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
		ans_normals.emplace_back(nor_c);
	}
}

void gongjian_col::gen_down_point(vector<vec3>& down_point, vector<vec3>& normol, vector<vec3>& up_point, double acc_in)
{
	//按照精度，圆周上采点--10.14
	int num_max = ceil(col_D * arma::datum::pi / acc_in);
	double deta_ang = 360.0 / num_max;

	mat33 ls_SYS(fill::eye);
	//vec3 ls_R = { col_D / 2.0 , 0.0 ,0.0 };
	
	for (int i = 0; i < num_max; i++)
	{
		//vec3 ans_p = ls_SYS * tcRotZ(3, i * deta_ang)* ls_R ;
		//vec3 ans_n = normalise(ans_p);
		//vec3 ans_up = { ans_p(0), ans_p(1), ans_p(2) + col_len };

		vec3 ans_n = ls_SYS * tcRotZ(3, i * deta_ang) * tcX(3);
		vec3 ans_down = ans_n * col_D / 2.0;
		vec3 ans_up = ans_down + ls_SYS * tcZ(3) * col_len;
		
		normol.emplace_back(ans_n);
		down_point.emplace_back(ans_down);
		up_point.emplace_back(ans_up);
	}
}

gongjian_rot::gongjian_rot()
{
}

gongjian_rot::~gongjian_rot()
{
}

void gongjian_rot::set_rot_var(mat& gj_outline)
{
	for (int i = 0; i < gj_outline.n_cols; i++)	////3*n  定义为沿x为内端面
	{
		rot_len.push_back(gj_outline.col(i)[0]);
		rot_r.push_back(gj_outline.col(i)[1]);
		outline_len_r.insert({ gj_outline.col(i)[0] ,gj_outline.col(i)[1] });
	}
}

void gongjian_rot::get_rot_tri_nor(vector<double3v>& ans_points, vector<double3v>& ans_normals, double acc_in)
{
	{
		////不同长度，对应半径不同，要根据长度与精度，计算在轮廓上的采样
		//// 快捷统一：以最大半径为基准，按照col离散端面方式，获得侧面法向 ??? 可以
		//double max_rot_R = 0.0;
		//for (int i = 0; i < rot_r.size(); i++)
		//{
		//	if (max_rot_R < rot_r[i])
		//	{
		//		max_rot_R = rot_r[i];
		//	}
		//}
		//double dwon_R = rot_r.front();
		//double up_R = rot_r.back();
		//double rot_z_len = rot_len.back() - rot_len.front();
		//int num_max = 2 * max_rot_R * 3.1415 / acc_in; //最大半径的分割数
		//double deta_ang = 360.0 / num_max;	

		//// 1、先处理两个端面
		////按照精度，圆周上采点
		//vector<vec3> dwon_point;
		//vector<vec3> dwon_nor;
		//vector<vec3> up_point;
		//mat33 ls_SYS(fill::eye);
		//vec3 ls_dwon_R = { dwon_R , 0.0 ,0.0 };
		//vec3 ls_up_R = { up_R , 0.0 ,0.0 };
		//for (int i = 0; i < num_max; i++)
		//{
		//	vec3 ans_p = ls_SYS * tcRotZ(3, i * deta_ang) * ls_dwon_R;
		//	vec3 ans_n = normalise(ans_p);
		//	vec3 ans_up = ls_SYS * tcRotZ(3, i * deta_ang) * ls_up_R;

		//	dwon_point.emplace_back(ans_p);
		//	dwon_nor.emplace_back(ans_n);
		//	up_point.emplace_back(ans_up);
		//}
		//
		//{
		//	//端面离散  
		//	int num_r = dwon_R / acc_in; // 离散圈数
		//	vec3 ls_acc_R = { acc_in , 0.0 ,0.0 };
		//	//下端面 
		//	vec3 dwon_p = { 0.0, 0.0, 0.0 };
		//	vec3 dwon_nor = { 0.0, 0.0, -1.0 };
		//	ans_points.emplace_back(dwon_p);
		//	ans_normals.emplace_back(dwon_nor); //放入中心点
		//	for (int i = 0; i < num_r; i++)
		//	{
		//		for (int j = 0; j < num_max; j++)
		//		{
		//			vec3 ans_p = ls_SYS * tcRotZ(3, j * deta_ang) * ls_acc_R * i;

		//			ans_points.emplace_back(ans_p);
		//			ans_normals.emplace_back(dwon_nor);
		//		}
		//	}
		//	//上端面 
		//	num_r = up_R / acc_in;
		//	vec3 up_p = { 0.0, 0.0, rot_len.back() }; //不等于位置高差。rot_z_len 等于绝对高度
		//	vec3 up_nor = { 0.0, 0.0, 1.0 };
		//	ans_points.emplace_back(up_p);
		//	ans_normals.emplace_back(up_nor); //放入中心点
		//	for (int i = 0; i < num_r; i++)
		//	{
		//		for (int j = 0; j < num_max; j++)
		//		{
		//			vec3 ans_p = ls_SYS * tcRotZ(3, j * deta_ang) * ls_acc_R * i;

		//			ans_points.emplace_back(ans_p);
		//			ans_normals.emplace_back(up_nor);
		//		}
		//	}
		//}
		//
		/////2、侧面
		//int num_len = rot_z_len / acc_in; //可能不够密 ??? 3.20

		//for (int i = 1; i < num_len; i++)
		//{
		//	double cur_len = rot_len.front() + i * acc_in;
		//	//获得对应半径
		//	double len_to_R = get_curlen_R(cur_len);
		//	vec3 ls_R = { len_to_R , 0.0 ,0.0 };
		//	for (int  j = 0; j < num_max; j++)
		//	{
		//		vec3 ans_p = ls_SYS * tcRotZ(3, i * deta_ang) * ls_R;

		//		ans_points.emplace_back(ans_p);
		//		ans_normals.emplace_back(dwon_nor[j]);
		//	}
		//}
	}
	double max_rot_R = 0.0;
	for (int i = 0; i < rot_r.size(); i++)
	{
		if (max_rot_R < rot_r[i])
		{
			max_rot_R = rot_r[i];
		}
	}
	int num_max = 2 * max_rot_R * 3.1415 / acc_in; //最大半径的分割数
	double deta_ang = 360.0 / num_max;

	//得到圆周离散点 + 法向
	//遍历长度 像上逐圈生成三角
	mat33 ls_SYS(fill::eye);
	int len = rot_len.size() - 1;
	for (int i = 0; i < len; i++)
	{
		vec3 cur_P = { 0.0, 0.0, rot_len[i] };	//回转中心点  
		vec3 cur_R = { rot_r[i], 0.0, 0.0 };   //半径

		vec3 cur_P2 = { 0.0, 0.0, rot_len[i + 1] };	//回转中心点  上一层的点
		vec3 cur_R2 = { rot_r[i + 1], 0.0, 0.0 };   //半径

		for (int j = 0; j < num_max; j++)
		{
			vec3 ans_p1 = ls_SYS * tcRotZ(3, j * deta_ang) * cur_R + cur_P;
			vec3 ans_p2 = ls_SYS * tcRotZ(3, (j + 1) * deta_ang) * cur_R + cur_P;
		
			vec3 ans_p3 = ls_SYS * tcRotZ(3, j  * deta_ang) * cur_R2 + cur_P2;
			vec3 ans_p4 = ls_SYS * tcRotZ(3, (j + 1) * deta_ang) * cur_R2 + cur_P2;

			vec3 ans_nor = normalise(ans_p1);
			//上下四点 组成两个三角
			ans_points.emplace_back(ans_p1);
			ans_points.emplace_back(ans_p2);
			ans_points.emplace_back(ans_p3);
			ans_normals.emplace_back(ans_nor);
			ans_normals.emplace_back(ans_nor);
			ans_normals.emplace_back(ans_nor);

			ans_points.emplace_back(ans_p2);
			ans_points.emplace_back(ans_p4);
			ans_points.emplace_back(ans_p3);
			ans_normals.emplace_back(ans_nor);
			ans_normals.emplace_back(ans_nor);
			ans_normals.emplace_back(ans_nor);
		}

	}

	vec3 dwon_P = { 0.0, 0.0, rot_len.front()};	
	vec3 dwon_R = { rot_r.front(), 0.0, 0.0};
	vec3 dwon_nor = {0.0, 0.0, -1.0 };
	vec3 up_P = { 0.0, 0.0, rot_len.back() };
	vec3 up_R = { rot_r.back(), 0.0, 0.0};   
	vec3 up_nor = { 1.0, 0.0, 0.0 };
	for (int i = 0; i < num_max; i++)
	{
		vec3 dwon_p1 = ls_SYS * tcRotZ(3, i * deta_ang) * dwon_R + dwon_P;
		vec3 dwon_p2 = ls_SYS * tcRotZ(3, (i + 1) * deta_ang) * dwon_R + dwon_P;

		ans_points.emplace_back(dwon_P);
		ans_points.emplace_back(dwon_p1);
		ans_points.emplace_back(dwon_p2);
		ans_normals.emplace_back(dwon_nor);
		ans_normals.emplace_back(dwon_nor);
		ans_normals.emplace_back(dwon_nor);

		vec3 up_p1 = ls_SYS * tcRotZ(3, i * deta_ang) * up_R + up_P;
		vec3 up_p2 = ls_SYS * tcRotZ(3, (i + 1) * deta_ang) * up_R + up_P;

		ans_points.emplace_back(up_P);
		ans_points.emplace_back(up_p1);
		ans_points.emplace_back(up_p2);
		ans_normals.emplace_back(up_nor);
		ans_normals.emplace_back(up_nor);
		ans_normals.emplace_back(up_nor);
	}
}


