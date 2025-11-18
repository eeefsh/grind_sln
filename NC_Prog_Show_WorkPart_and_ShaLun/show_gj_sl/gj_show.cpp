#include "../pch.h"
#define NC_Prog_Show_WorkPart_and_ShaLun_EXPORTS
#include "gj_show.h"
#include"manager_h/xt_glfw_setting.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"


show_gj_sl::show_gj_sl()
{

}

show_gj_sl::~show_gj_sl()
{

}

void show_gj_sl::show(mat44& A)
{
	for (int i = 0; i < all_part.size(); i++)
	{
		all_part[i]->show(A);
	}
}

//void show_gj_sl::show_shalun()
//{
//	::gladLoadGL();
//	vec p = tcX(3);
//	glPushMatrix();
//	mat m4(4, 4, fill::zeros);
//	m4.submat(0, 0, 2, 2) = sl_show_ptr->JC_SYS_SL;
//	m4.submat(0, 3, 2, 3) = sl_show_ptr->JC_O_SL;
//	m4(3, 3) = 1.0;
//	glMultMatrixd(m4.memptr());
//	glCallList(list_sl);
//	glPopMatrix();
//}
//
//void show_gj_sl::init_sl_list()
//{
//	list_sl = glGenLists(1);
//	glNewList(list_sl, GL_COMPILE);
//	{
//		//设置OpenGL材料  10.23
//		GLfloat ambient[] = { 0.0, 0.2, 0.2, 1.0 };
//		GLfloat diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
//		GLfloat specular[] = { 0.0, 1.0, 1.0, 1.0 };
//		GLfloat shininess[] = { 0 };
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//
//		for (auto it = sl_show_ptr->outline_len_r.begin(); it != sl_show_ptr->outline_len_r.end(); )
//		{
//			float cur_len = it->first;
//			float cur_r = it->second;
//			it++;
//			if (it == sl_show_ptr->outline_len_r.end())
//			{
//				break;
//			}
//			float cur_len2 = it->first;
//			float cur_r2 = it->second;
//			for (size_t i = 0; i < 72; i++)//画侧面四边形
//			{
//				glBegin(GL_POLYGON);
//				vec normal = tcRotZ(3, 10.0 * double(i)) * tcX(3);
//				//glColor3d(1.0, 0.0, 0.0);
//				glNormal3d(normal(0), normal(1), normal(2));
//				vec p1 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r + tcZ(3) * (cur_len);
//				vec p2 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cur_r + tcZ(3) * (cur_len);
//				vec p3 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);
//				vec p4 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);
//				glVertex3d(p1(0), p1(1), p1(2));
//				glVertex3d(p2(0), p2(1), p2(2));
//				glVertex3d(p3(0), p3(1), p3(2));
//				glVertex3d(p4(0), p4(1), p4(2));
//				glEnd();
//			}
//		}
//
//		float in_r = sl_show_ptr->outline_len_r.begin()->second;
//		//画两个端面
//		{
//			glNormal3d(0.0, 0.0, -1.0);
//			glBegin(GL_POLYGON);
//			vec p1;
//			for (size_t i = 0; i < 36; i++)
//			{
//				p1 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * in_r + tcZ(3) * (sl_show_ptr->in_length);
//				glVertex3d(p1(0), p1(1), p1(2));
//			}
//			glEnd();
//		}
//		auto it = sl_show_ptr->outline_len_r.end();
//		it--;
//		float out_r = it->second;
//		{
//			glNormal3d(0.0, 0.0, 1.0);
//			glBegin(GL_POLYGON);
//			vec p1;
//			for (size_t i = 0; i < 36; i++)
//			{
//				p1 = tcRotZ(3, -10.0 * double(i)) * tcX(3) * out_r + tcZ(3) * (sl_show_ptr->out_length);
//				glVertex3d(p1(0), p1(1), p1(2));
//			}
//			glEnd();
//		}
//
//		{
//			//设置OpenGL材料  10.23   改变点的颜色
//			GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
//			GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
//			GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
//			GLfloat shininess[] = { 0 };
//			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//		}
//	}
//	glEndList();
//}
//
//void show_gj_sl::show_stl()
//{
//	glCallList(list_gj_stl);	
//}
//
//void show_gj_sl::show_cutting()
//{
//	renew_cutting_list();
//	for (int i = 0 + list_gj_start; i < list_gj_size + list_gj_start; i++)
//	{
//		glCallList(i);
//	}
//}
//
//void show_gj_sl::show_mesh()
//{
//	init_mesh_list();
//	glCallList(list_gj_mesh);
//}
//
//void show_gj_sl::init_stl_list()
//{
//	list_gj_stl = glGenLists(1);
//
//	glNewList(list_gj_stl, GL_COMPILE); // 开始记录绘制命令
//	glMatrixMode(GL_MODELVIEW);
//	auto itend = gj_show_ptr->mesh_gj.all_face.end();
//	for (auto it = gj_show_ptr->mesh_gj.all_face.begin(); it != itend; it++)
//	{
//		double3v p1 = it->second->get_double3v(0)->get_vec3();
//		double3v p2 = it->second->get_double3v(1)->get_vec3();
//		double3v p3 = it->second->get_double3v(2)->get_vec3();
//		double3v nor = it->second->get_normal();
//
//		//将表面点转到工件坐标系中
//		glPushMatrix();
//		{
//			//glMultMatrixd(m4.memptr());   //调用
//			//通过点的颜色设置-- unsigned char color;
//			//glNormal3f(nor.x, nor.y, nor.z);
//			glNormal3d(nor.x, nor.y, nor.z);
//			glBegin(GL_POLYGON);
//			{
//				glVertex3d(p1.x, p1.y, p1.z);
//				glVertex3d(p2.x, p2.y, p2.z);
//				glVertex3d(p3.x, p3.y, p3.z);
//			}
//			glEnd();
//		}
//		glPopMatrix();
//	}
//	glEndList(); // 结束记录
//}
//
//void show_gj_sl::init_cutting_list()
//{
//	//根据树的层数，确定分组个数
//	list_gj_size = gj_show_ptr->manager_cells.oc_tree.get_nodes2last(gj_show_ptr->group_last_n);
//
//	//::gladLoadGL();
//	// 创建显示列表
//	list_gj_start = glGenLists(list_gj_size);
//
//	//遍历完树的分组层级，将指针放入待更新组
//	queue<octree*>  qt;
//	octree* cur = &gj_show_ptr->manager_cells.oc_tree;
//
//	//分组越多更新越慢
//	int aim_deptn = gj_show_ptr->group_last_n;
//	qt.push(&gj_show_ptr->manager_cells.oc_tree);
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
//		int list_index = gj_show_ptr->cal_list_num(gj_show_ptr->manager_cells.oc_tree, *qt.front());
//		//到对应号的显示列表，将分组下的点画上
//		display_fresh_a_list(qt.front(), list_index + list_gj_start);
//		qt.pop();
//	}
//}
//
//void show_gj_sl::renew_cutting_list()
//{
//	//12.6增加 记录被删除的组号，后清空显示列表
//	set<int>::iterator it_num = gj_show_ptr->groups_clear.begin();
//	auto it_num_end = gj_show_ptr->groups_clear.end();
//	for (; it_num != it_num_end ; it_num++)
//	{
//		glNewList(*it_num + list_gj_start, GL_COMPILE);
//		glEndList(); 
//	}
//	gj_show_ptr->groups_clear.clear();
//
//	set<octree*>::iterator it = gj_show_ptr->groups_changed.begin();
//	auto it_end = gj_show_ptr->groups_changed.end();
//	for (; it != it_end; it++)
//	{
//		int list_index = gj_show_ptr->cal_list_num(gj_show_ptr->manager_cells.oc_tree, *(*it));
//		display_fresh_a_list(*it, list_index + list_gj_start);
//	}
//	gj_show_ptr->groups_changed.clear();
//}
//
//void show_gj_sl::display_fresh_a_list(octree* cur_zu, int list_index)
//{
//	::gladLoadGL();
//	//按组画点
//	queue<obj_cell*> voc;
//	cur_zu->get_all_obj(voc);
//	
//	GLint temp = list_index;
//	glNewList(temp, GL_COMPILE); // 开始记录绘制命令
//	glMatrixMode(GL_MODELVIEW);
//	
//	while (!voc.empty())
//	{
//		//显示一个点* 
//		obj_cell* op = voc.front();
//		voc.pop();
//		double3v ap = op->cal_normal();
//	
//		//将表面点转到工件坐标系中
//		vec3 cell_O(fill::zeros);
//		mat33 cell_SYS(fill::zeros);
//		op->cal_o_sys(ap.x, ap.y, ap.z, gj_show_ptr->acc_d, cell_O, cell_SYS);
//		mat44 m4 = gj_show_ptr->construct_sys(cell_SYS, cell_O);
//	
//		glPushMatrix();
//		{
//			glMultMatrixd(m4.memptr());   //调用
//			//通过点的颜色设置-- unsigned char color;
//			//vec3 vec3_color = op->get_color();
//			//set_color(vec3_color);
//			::gladLoadGL();
//			glNormal3f(ap.x, ap.y, ap.z);
//			glBegin(GL_POLYGON);
//			{
//				vec3 ls_v = { 0.0,0.0,0.0 };
//				vec3 ls_l = { gj_show_ptr->draw_point_r,0.0,0.0 };
//				double det_ang = 360.0 / gj_show_ptr->draw_point_seg;
//				for (size_t i = 0; i <= gj_show_ptr->draw_point_seg; i++)
//				{
//					ls_v = tcRotZ(3, det_ang * i) * ls_l;
//					glVertex3f(ls_v(0), ls_v(1), ls_v(2));
//				}
//			}
//			glEnd();
//		}
//		glPopMatrix();
//	}
//	glEndList(); // 结束记录
//}
//
//void show_gj_sl::init_mesh_list()
//{
//	::gladLoadGL();
//	list_gj_mesh = glGenLists(1);
//	glNewList(list_gj_mesh, GL_COMPILE); // 开始记录绘制命令
//	glMatrixMode(GL_MODELVIEW);
//
//	int len_tri = gj_show_ptr->mesh_finish_tri.size();
//	for (int i = 0; i < len_tri; i++)	//测试 显示网格构建三角的顺序 20
//	{
//		//显示一个tri_mesh 
//		double3v p1 = gj_show_ptr->mesh_finish_tri[i].p1;
//		double3v p2 = gj_show_ptr->mesh_finish_tri[i].p2;
//		double3v p3 = gj_show_ptr->mesh_finish_tri[i].p3;
//
//		vec3 v1 = { p1.x, p1.y, p1.z };
//		vec3 v2 = { p2.x, p2.y, p2.z };
//		vec3 v3 = { p3.x, p3.y, p3.z };
//		vec3 nor1 = cross((v2 - v1), (v3 - v2));
//		//通过刀序设置颜色;
//		int cur_color = gj_show_ptr->mesh_finish_tri[i].color;
//		glCallList(gj_show_ptr->color_list_start + cur_color);
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
//	glEndList(); // 结束记录
//}


