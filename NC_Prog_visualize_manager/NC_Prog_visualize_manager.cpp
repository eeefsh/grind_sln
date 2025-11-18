#include"pch.h"
#define NC_Prog_visualize_manager_EXPORTS
#include"NC_Prog_visualize_manager.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include"manager_h/MA_010601_Cal_JiHe_PointSort.h"

#include"GLlist_Pbody.h"


void visualize_manager::set_hide_parts(vector<bool>& v_hide)
{
	jichuang_gl_ptr->v_hide = v_hide;
}

visualize_manager::visualize_manager()
{
	jichuang_gl_ptr = new GLlist_JiChuang;
	jichuang_gl_ptr->init();

	//sl_group = new wheel_group;
	sl_data_ptr = new shalun;

	tanzhen_Z_ptr = new tanzhen_Z;
	vir_mac_ptr = new virtual_machine;

	//显示相关指针
	gj_gl_stl = new show_send();
	gj_gl_cut = new show_send();
	//gj_gl_mesh = new show_send();

	gj_gl_cutted = new show_send();
	//sl_group = new wheel_group;
}

visualize_manager::~visualize_manager()
{
}

void visualize_manager::init_gj_by_stl(string file, vec trans, double acc_d)
{
	gj_data_ptr = new gongjian(file, trans, acc_d);

	//gj_gl_stl->load_stl_data(gj_data_ptr);
	gj_gl_cut->load_init_data(gj_data_ptr);
}

void visualize_manager::init_gj_by_col(double D, double len, double acc_d)
{
	//gj_data_ptr = new gongjian(file, acc_d);
	gj_data_ptr = new gongjian(D, len, acc_d);	//调用圆柱形的构造


	//gj_gl_stl->load_stl_data(gj_data_ptr);
	gj_gl_cut->load_init_data(gj_data_ptr);
}

void visualize_manager::init_gj_by_dxf(string file, double acc_d)
{
	//wheel_dxf sl_dxf;  //用于dxf工件初始化
	//sl_dxf.set_wheel(file, acc_d);

	//wheel_group sl_zu;
	//sl_zu.set_wheel_pole(70, 40, 25, 10, 120, 20);
	//sl_zu.set_nut(15, 50);
	////sl_zu.add_wheel(sl_dxf, 1, 1, 0); -8.13 mark

	//mat gj_outline;
	//sl_zu.get_wheel_outline(gj_outline);
	//init_gj_by_rot(gj_outline, acc_d);
}

void visualize_manager::init_gj_by_rot(mat& gj_outline, double acc_d)
{
	gj_data_ptr = new gongjian(gj_outline, acc_d);	//调用回转形的构造

	gj_gl_cut->load_init_data(gj_data_ptr);
}

void visualize_manager::load_shalun(int slz_id,int sl_id)
{
	//加载碰撞砂轮
	init_wheel_group_peng_data(sl_id);

	//加载显示砂轮
	vector<mat> temp_mat;
	sl_manager->get_group_show_outline(slz_id,temp_mat);  //用于显示的数据，包括杆
	jichuang_gl_ptr->unload_tool();
	jichuang_gl_ptr->init_tool(temp_mat);
}

void visualize_manager::unload_shalun()
{
	jichuang_gl_ptr->unload_tool();
	//vis的可视化砂轮没有加载数据的
	//sl_group 在初始化数据的时候会 指向新的砂轮组
	sl_data_ptr->reset_data();
}

void visualize_manager::init_wheel_group_peng_data(int sl_id)
{
	//给计算碰撞的砂轮加载数据
	sl_gl_ptr = new show_send();
	// 默认砂轮组上只有一个砂轮，拿sl_id获取碰撞数据 25.6.20 zy
	//vector<int> v_sl_id;
	//sl_manager->get_a_group_all_wheel_key(slz_id, v_sl_id);
	//int sl_id = -1;
	//for (int i = 0; i < v_sl_id.size(); i++)
	//{
	//	if (v_sl_id[i] > 0) 
	//	{
	//		sl_id = v_sl_id[i];
	//		break;
	//	}
	//}

	mat temp_mat;
	sl_manager->get_2D_wheel_outline(sl_id, temp_mat);	//3*n  定义为沿x为内端面

	vector<double> v_lens;
	vector<double> v_rs;
	double cover_box = DBL_MIN;
	for (size_t i = 0; i < temp_mat.n_cols; i++)
	{
		v_lens.push_back(temp_mat.col(i)[0]);	//砂轮定义内外端面在z轴方向上 因此转换
		v_rs.push_back(temp_mat.col(i)[1]);	//等价于取的y值
		if (cover_box < temp_mat.col(i)[1])
		{
			cover_box = temp_mat.col(i)[1];
		}
	}
	sl_data_ptr->init_shape(v_lens.front() , v_lens.back(),  2 * cover_box, v_lens, v_rs);
}

void visualize_manager::init_mat_ctrl(tcGLMatrixCtrl* ptr)
{
	mat_ctrl = ptr;
	vec3 ls_scale;
	vec3 p;

	cal_scale(ls_scale, p);

	mat_ctrl->reset_view_scale(2.0 / ls_scale(0));
	mat_ctrl->reset_view_point(p);
}

void visualize_manager::set_view_mat(mat44& view)
{
	view = tcScale(800 / 1290.0, 1, 1) * mat_ctrl->to_mirror_Z() * mat_ctrl->get_mat_now();
}

void visualize_manager::set_base_mat(mat44& base)
{
	base ;
}

void visualize_manager::cal_gj_clamp_mat(mat44& matA, double out_len)
{
	//matA = matA * tcRotX(4, 90) * tcTranslate(0.0, 30.0, 33 - out_len); //会装轴长度偏心距 约33
	//test 1.2
	//matA = matA * tcTranslate(0.0, -33 + out_len, 30) * tcRotX(4, -90);
	matA = matA * tcTranslate(-3.054, -33.838 + out_len, 30) * tcRotX(4, -90);
}

void visualize_manager::cal_sl_clamp_mat(mat44& matZ, double out_len)
{
	//matZ = matZ  * tcTranslate(220.0, 160.0, -360 - out_len) * tcRotX(4, -90);
	//matZ = matZ * tcTranslate(219.832, 350.927, 179.5) * tcRotZ(4, -90.0);
	//砂轮内外端面 在Y轴上  》》 转到z轴
	matZ = matZ * tcTranslate(219.832, 350.927, 179.5) * tcRotZ(4, 90.0);
}


bool visualize_manager::show_now_state(vec5& ls_mac_sys, vec5& ls_abs_sys, int color, mat44& base, mat44& view)
{
	mat44 z_mat;
	mat44 a_mat;
	//绝对坐标计算碰撞
	cal_gongjian_abs_mat(ls_abs_sys, base, a_mat);
	cal_shalun_abs_mat(ls_abs_sys, base, z_mat);

	//检查部件间的碰撞 不包括工件与砂轮
	//if (check_all_prat_peng())
	{
		//return true;
	}
	is_tance = false;
	//检查探针与工件  A探针与砂轮
	if (is_tance)
	{
		vec5 ls_abs = {0.0,0.0,0.0,0.0,0.0};
		//碰到后动作 抓取当前机床位置坐标  ??? 需要界面显示 
		if (check_peng_Ztanzhen_and_gj(a_mat, z_mat))
		{
			//return false; //抓取当前机床位置坐标 需要继承NC块
			
			tc_inner_ABS(ls_abs);
		}
		
	}

	//计算去除变形运动  3.25 ??? 是否增加开关 ，只仿真运动
	//cal_cut_sport(a_mat, z_mat, color);  //能碰 检查显示 12.27  (变形应该没问题)

	mat44 ls = view * base;
	glLoadMatrixd(ls.memptr());

	//工件固定视口控制-前端按键改变--2024.11.19
	mat44 mat_lookat_gongjian = eye(4, 4);
	if (is_lookat_gongjian)
	{
		mat_lookat_gongjian =  tcRotZ(4, -ls_mac_sys(4)) * tcTranslate(ls_mac_sys(0), 0.0, 0.0);
	}
	else
	{
		mat_lookat_gongjian = eye(4, 4);
	}
	ls = view * mat_lookat_gongjian * base;
	
	//显示   -- 用机械坐标
	show_parts(ls_mac_sys, ls_abs_sys, ls);
	return true;
}

bool visualize_manager::show_end_state(vec5& ls_mac_sys, vec5& ls_abs_sys, int color, mat44& base, mat44& view)
{
	mat44 ls = view * base;
	glLoadMatrixd(ls.memptr());

	//显示   -- 用机械坐标
	jichuang_gl_ptr->show(base,
		ls_mac_sys(0),
		ls_mac_sys(1),
		ls_mac_sys(2),
		ls_mac_sys(3),
		ls_mac_sys(4));

	mat44 matA;
	//matA.eye();
	cal_gongjian_mac_mat(ls_mac_sys, base, matA); // 正确 3.13

	gj_gl_cutted->load_cutted_data(gj_data_ptr);
	gj_gl_cutted->show(matA);
	return true;
}

void visualize_manager::cal_scale(vec3& ls_scale, vec3& p)
{
	ls_scale(0) = jichuang_gl_ptr->get_max_x() - jichuang_gl_ptr->get_min_x();
	ls_scale(1) = jichuang_gl_ptr->get_max_y() - jichuang_gl_ptr->get_min_y();
	ls_scale(2) = jichuang_gl_ptr->get_max_z() - jichuang_gl_ptr->get_min_z();

	p(0) = (jichuang_gl_ptr->get_max_x() + jichuang_gl_ptr->get_min_x()) / 2.0 / ls_scale(0) * 2.0;
	p(1) = (jichuang_gl_ptr->get_max_y() + jichuang_gl_ptr->get_min_y()) / 2.0 / ls_scale(1) * 3.0;
	p(2) = (jichuang_gl_ptr->get_max_z() + jichuang_gl_ptr->get_min_z()) / 2.0 / ls_scale(2) * 2.0;
}

void visualize_manager::cal_axis_pos_mat(vec5& ls_mac_sys, mat44& base, mat44& matX, mat44& matY, mat44& matZ, mat44& matA, mat44& matC)
{
	double zb_x = ls_mac_sys(0);
	double zb_y = ls_mac_sys(1);
	double zb_z = ls_mac_sys(2);
	double zb_a = -ls_mac_sys(3);
	double zb_c = -90.0 - ls_mac_sys(4);

	mat44 x_move = tcTranslate(-zb_x, 0, 0);
	mat44 y_move = tcTranslate(0, -zb_y, 0);
	mat44 z_move = tcTranslate(0, 0, zb_z);

	mat44 a_move = tcRotX(4, -zb_a);
	mat44 c_move = tcRotZ(4, -zb_c);

	mat44 base_mat = base;// 机床位置

	mat44 x_mat = base_mat * x_move;
	mat44 y_mat = x_mat * y_move;
	mat44 c_mat = y_mat * c_move;
	mat44 z_mat = base_mat * z_move;
	mat44 a_mat = c_mat * a_move;
}

void visualize_manager::cal_gongjian_abs_mat(vec5& ls_abs_sys, mat44& base_in, mat44& gongjian_mat)
{
	//mat44 matX_in = base_in * tcTranslate(-ls_abs_sys(0), 0.0, 0.0);
	//mat44 matC_in = matX_in * tcRotZ(4, ls_abs_sys(4));
	//gongjian_mat = matC_in * tcTranslate(0.0, 0.0, 30) * tcRotY(4, ls_abs_sys(3)) * tcTranslate(0.0, 0.0, -30);

	//base_in = tcTranslate(0.0, 0.0, 30) * tcRotX(4, -90);
	//gongjian_mat = tcTranslate(-ls_abs_sys(0), 0.0, 0.0) * tcRotY(4, ls_abs_sys(3)) * tcRotZ(4, ls_abs_sys(4)) * base_in;
	
	mat trans = tcTranslate(pos_gj_trans(0), pos_gj_trans(1), pos_gj_trans(2));

	gongjian_mat =  tcTranslate(-ls_abs_sys(0), 0.0, 0.0) * tcRotZ(4, ls_abs_sys(4)) * tcRotY(4, ls_abs_sys(3))
		* tcTranslate(0.0, 0.0, 0.0) * (tcRotX(4, 90) * trans);//矩阵*对象
}

void visualize_manager::cal_shalun_abs_mat(vec5& ls_abs_sys, mat44& base_in, mat44& shalun_mat)
{
	/*mat44 matY_in = base_in * tcTranslate(0.0, ls_abs_sys(1), 0.0);
	shalun_mat = matY_in * tcTranslate(0.0, 0.0, ls_abs_sys(2));*/

	//base_in = tcTranslate(0.0, 0.0, 30) * tcRotX(4, 90);
	//base_in = tcTranslate(0.0, 0.0, 0.0) * tcRotX(4, 90);
	shalun_mat = tcTranslate(0.0, ls_abs_sys(1), 0.0) * tcTranslate(0.0, 0.0, ls_abs_sys(2))
		* tcTranslate(0.0, 0.0, 0.0) * tcRotX(4, 90);
}

void visualize_manager::cal_gongjian_mac_mat(vec5& ls_mac_sys, mat44& base_in, mat44& gongjian_mat)
{//3D仿真显示

	mat trans = tcTranslate(pos_gj_trans(0), pos_gj_trans(1), pos_gj_trans(2));
	mat44 matX_in = tcTranslate(-ls_mac_sys(0), 0.0, 0.0);
	mat44 matC_in = matX_in * tcRotZ(4, ls_mac_sys(4));
	gongjian_mat = matC_in * tcTranslate(0.0, 0.0, 30) * tcRotY(4, ls_mac_sys(3)) ;

	//3.15 13:38 装夹长度还是需要 * tcTranslate(0.0, 0.0, -30) 平移影响显示结果与计算对不上
	gongjian_mat = base_in * gongjian_mat * (tcRotX(4, 90.0) *  trans);
}

void visualize_manager::cal_shalun_mac_mat(vec5& ls_mac_sys, mat44& base_in, mat44& shalun_mat)
{
	mat44 matY_in = base_in * tcTranslate(0.0, ls_mac_sys(1), 0.0);
	shalun_mat = matY_in * tcTranslate(0.0, 0.0, ls_mac_sys(2));
}


void visualize_manager::cal_cut_sport(mat44& A_axis_ABS_mat,  mat44& Z_axis_ABS_mat,int color)
{

	//改变工件，砂轮位置，计算数据，发送数据
	//转到主轴向外定义的计算碰撞坐标系 --9.2
	vec3 ABS_O_SL = Z_axis_ABS_mat.submat(0, 3, 2, 3);
	mat33 ABS_SYS_SL = Z_axis_ABS_mat.submat(0, 0, 2, 2);  //此处计算的砂轮Z轴就是主轴向外 9.3 mark

	sl_data_ptr->set_JC_O_SL(ABS_O_SL);
	sl_data_ptr->set_JC_SYS_SL(ABS_SYS_SL);

	gj_data_ptr->JC_SYS_GJ = A_axis_ABS_mat.submat(0, 0, 2, 2);
	gj_data_ptr->JC_O_GJ = A_axis_ABS_mat.submat(0, 3, 2, 3);

	sl_data_ptr->cal_SL_to_GJ(gj_data_ptr->get_O(), gj_data_ptr->get_SYS());
	gj_data_ptr->cut_off(sl_data_ptr, color, 1);

	gj_gl_cut->load_cut_data(gj_data_ptr);
	
}

bool visualize_manager::check_all_prat_peng()
{
	//同一轴上的部件 不进行检测
	//基座 （工件 + 砂轮）
	vector<vector<GLlist_Pbody*>> all_axis_part;
	all_axis_part.push_back(jichuang_gl_ptr->Xaxis);
	all_axis_part.push_back(jichuang_gl_ptr->Yaxis);
	all_axis_part.push_back(jichuang_gl_ptr->Zaxis);
	all_axis_part.push_back(jichuang_gl_ptr->Aaxis);
	all_axis_part.push_back(jichuang_gl_ptr->Caxis);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < all_axis_part[i].size(); j++)
		{
			mat A_box;
			//A_box = all_axis_part[i][j]->get_box();
			GLlist_Pbody* gp = all_axis_part[i][j];
			A_box = gp->get_box();
			//gp->get_box(A_box);
			//下一轴上部件
			for (int k = i + 1; k < 5; k++)
			{
				for (int p = 0; p < all_axis_part[k].size(); p++)
				{
					//获取两个部件的box
					mat B_box = all_axis_part[k][p]->get_box();
					if (check_two_prat_AABB_peng(A_box, B_box))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool visualize_manager::check_two_prat_AABB_peng(mat& A_box, mat& B_box)
{
	vec3 A_min = A_box.col(0);
	vec3 A_max = A_box.col(1);
	vec3 B_min = B_box.col(0);
	vec3 B_max = B_box.col(1);
	{
		// 检查X轴上的投影是否相交
		if (A_max(0) < B_min(0) || A_min(0) > B_max(0)) {
			return false;
		}
		// 检查Y轴上的投影是否相交
		if (A_max(1) < B_min(1) || A_min(1) > B_max(1)) {
			return false;
		}
		// 检查Z轴上的投影是否相交
		if (A_max(2) < B_min(2) || A_min(2) > B_max(2)) {
			return false;
		}
	}
	// 如果在所有轴上的投影都相交，则认为两个包围盒相交
	return true;
}

void visualize_manager::show_parts(vec5& ls_mac_sys, vec5& ls_abs_sys, mat44& base)
{
	jichuang_gl_ptr->show(base,
		ls_mac_sys(0),
		ls_mac_sys(1),
		ls_mac_sys(2),
		ls_mac_sys(3),
		ls_mac_sys(4));

	mat44 matA;
	//matA.eye();
	mat44 matZ;
	//matZ.eye();
	cal_gongjian_mac_mat(ls_mac_sys, base, matA); // 正确 3.13
	//cal_shalun_mac_mat(ls_mac_sys, base, matZ);
	/*cal_gongjian_abs_mat(ls_abs_sys, base, matA);
	cal_shalun_abs_mat(ls_abs_sys, base, matZ);*/

	//gj_gl_stl->show(matZ);
	//cal_gj_clamp_mat(matA, 0);//通过改变矩阵，改变显示状态，
	//没有改变工件在机床坐标系下的状态
	



	gj_gl_cut->show(matA);

	
	//gj_gl_stl->show(matA);
	//gj_gl_cut->show(matA);
	//gj_gl_mesh->show(matA);

	//sl_gl_ptr->show(matZ);
}


bool visualize_manager::check_peng_Ztanzhen_and_gj(mat44 mat_a, mat44 mat_z)
{
	tanzhen_Z_ptr->cal_self_pos(mat_z);
	{
		//tz_point在绝对坐标系中 要转到工件坐标系
		tanzhen_Z_ptr->GJ_O_TZ = gj_data_ptr->get_SYS().i() * (tanzhen_Z_ptr->JC_O_TZ - gj_data_ptr->get_O());
		//tanzhen_Z_ptr->GJ_SYS_TZ = gj_data_ptr->get_SYS().i() * tanzhen_Z_ptr->JC_SYS_TZ;
		vec3 cur_p = tanzhen_Z_ptr->GJ_O_TZ;
		
		queue<octree*> boxes_uncheck;
		boxes_uncheck.push(&gj_data_ptr->manager_cells.oc_tree);
		while (!boxes_uncheck.empty())
		{
			//取首个，碰撞计算
			octree* cur_box = boxes_uncheck.front();
			boxes_uncheck.pop();
			int cur_depth = cur_box->get_depth();
			if (check_peng_point_and_box(cur_p, mat_a, cur_box))
			{
				// 队列的数据结构与算法可以加快碰撞检测 2024.3.25 zy ???!!!
				// 单点碰撞只能是树一个分支
				
				//没有清空函数，遍历出栈
				while (!boxes_uncheck.empty())
				{
					boxes_uncheck.pop();
				}
				
				//判断是否到倒数第二层
				if (cur_depth > 2.1)
				{
					//下一级点盒放入碰撞点队列  
					cur_box->get_child_octree(boxes_uncheck);
				}
				else
				{
					//倒数第二层碰撞计算
					if (check_peng_point_and_box(cur_p, mat_a, cur_box)) //重复计算了 但是计算只有一次，忽略不及
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool visualize_manager::check_peng_point_and_box(vec3 tz_point, mat44 mat_a, octree* cur_box)
{
	double cur_R = cur_box->get_r(gj_data_ptr->acc_d);		

	double3v box_p = cur_box->get_double3v(gj_data_ptr->acc_d);	//在工件坐标系中

	vec3 box_v3 = { box_p.x, box_p.y, box_p.z };

	if ((box_p.y + cur_R) > tz_point(1) && (box_p.y - cur_R) < (tz_point(1) + tanzhen_Z_ptr->length))
	{
		if (box_p.z + cur_R > (tz_point(2) - tanzhen_Z_ptr->height) && box_p.z - cur_R < tz_point(2))
		{
			if (box_p.x + cur_R > tz_point(0) && (box_p.x - cur_R) < (tz_point(0) + tanzhen_Z_ptr->width))
			{
				return true; //工件点 + 半径 与探针包围盒相交  半径过大有问题 ？？？
			}
		}
	}
	else
	{
		return false;
	}
}

void visualize_manager::tc_inner_ABS(vec5& abs_coor)
{
	//vir_mac_ptr->BL_S_read(1361, abs_coor(0));
	//vir_mac_ptr->BL_S_read(1362, abs_coor(1));
	//vir_mac_ptr->BL_S_read(1363, abs_coor(2));
	//vir_mac_ptr->BL_S_read(1364, abs_coor(3));
	//vir_mac_ptr->BL_S_read(1365, abs_coor(4));
}

void visualize_manager::tc_inner_MCA(vec5& mac_coor)
{
	//vir_mac_ptr->BL_S_read(1441, mac_coor(0));
	//vir_mac_ptr->BL_S_read(1442, mac_coor(1));
	//vir_mac_ptr->BL_S_read(1443, mac_coor(2));
	//vir_mac_ptr->BL_S_read(1444, mac_coor(3));
	//vir_mac_ptr->BL_S_read(1445, mac_coor(4));

}


