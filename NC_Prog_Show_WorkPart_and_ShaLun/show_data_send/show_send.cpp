#include "../pch.h"
#define NC_Prog_Show_WorkPart_and_ShaLun_EXPORTS
#include "show_send.h"
#include"manager_h/MA_010101_NC_Prog_WorkPart.h"

void show_send::load_stl_data(gongjian* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> renew_list_num;
	vector<int> del_list_num;
	//ptr_data->send_data(show_data, renew_list_num, del_list_num);
	ptr->send_stl_data(show_data, renew_list_num, del_list_num);

	if (in_list_to_start.empty())
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int cur_list_num = glGenLists(1);
			in_list_to_start.insert({ 0, cur_list_num });
			//all_list_start.push_back(cur_list_num);
			glNewList(cur_list_num, GL_COMPILE);

			int len_in = show_data[i].size();
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
	}
	else
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int in_cur_list = renew_list_num[i];
			int cur_renew = in_list_to_start.find(in_cur_list)->second;
			glNewList(cur_renew, GL_COMPILE);
			int len_in = show_data[i].size();
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
		for (int i = 0; i < del_list_num.size(); i++)
		{
			int in_cur_list = del_list_num[i];
			int cur_renew = in_list_to_start.find(in_cur_list)->second;

			glNewList(cur_renew, GL_COMPILE);
			glEndList();
		}
	}
}

void show_send::load_init_data(gongjian* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> renew_list_num;
	vector<int> del_list_num;
	//ptr_data->send_data(show_data, renew_list_num, del_list_num);
	ptr->send_init_data(show_data, renew_list_num, del_list_num);

	if (in_list_to_start.empty())
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int cur_list_num = glGenLists(1);
			in_list_to_start.insert({ renew_list_num[i], cur_list_num });
			//all_list_start.push_back(cur_list_num);
			glNewList(cur_list_num, GL_COMPILE);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			int len_in = show_data[i].size();
			
			glBegin(GL_TRIANGLES);
			glColor3d(0.2,0.2, 1.0);  // 3.28 test
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
	}
	else
	{
		
	}
}

void show_send::load_cut_data(gongjian* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> renew_list_num;
	vector<int> del_list_num;
	//ptr_data->send_data(show_data, renew_list_num, del_list_num);
	ptr->send_cut_data(show_data, renew_list_num, del_list_num);
	if (in_list_to_start.empty())		//test 1.2 能清空所有列表
	{
		//一定不为空
		for (auto& it : in_list_to_start)
		{
			int cur_renew = it.second;
			glNewList(cur_renew, GL_COMPILE);
			glEndList();
		}
	}
	else
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int in_cur_list = renew_list_num[i];	//显示列表清空动作为完成，可能列表计算错误 ??? 12.29
			//当前更新组，没有对应list，应新建
			if (in_list_to_start.find(in_cur_list) == in_list_to_start.end())
			{
				int cur_list_num = glGenLists(1);
				in_list_to_start.insert({ renew_list_num[i], cur_list_num });
				//all_list_start.push_back(cur_list_num);
				glNewList(cur_list_num, GL_COMPILE);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glFrontFace(GL_CCW);

				//test
				{
					glEnable(GL_CULL_FACE);
					glFrontFace(GL_CCW);
					GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
					GLfloat diffuse[] = { 0.7, 0.0, 0.0, 1.0 };
					GLfloat specular[] = { 0.3, 0.0, 0.0, 1.0 };
					GLfloat shininess[] = { 0 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				}

				int len_in = show_data[i].size();
				//glBegin(GL_TRIANGLES);
				//glColor3d(1.0, 0.0, 0.0);
				//for (int j = 0; j < len_in; j++)
				//{
				//	glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				//	glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				//	glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				//	glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
				//}
				//glEnd();
				glEndList();
			}
			else
			{
				int cur_renew = in_list_to_start.find(in_cur_list)->second;
				glNewList(cur_renew, GL_COMPILE);

				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glFrontFace(GL_CCW);

				{
					glEnable(GL_CULL_FACE);
					glFrontFace(GL_CCW);
					GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
					GLfloat diffuse[] = { 0.7, 0.0, 0.0, 1.0 };
					GLfloat specular[] = { 0.3, 0.0, 0.0, 1.0 };
					GLfloat shininess[] = { 0 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				}

				glBegin(GL_TRIANGLES);
				int len_in = show_data[i].size();
				{
					for (int j = 0; j < len_in; j++)
					{
						glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
						glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
						glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
						glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
					}
					glEnd();
				}

				glEndList();
			}
			
		}
		for (int i = 0; i < del_list_num.size(); i++)
		{
			int in_cur_list = del_list_num[i];
			int cur_renew = in_list_to_start.find(in_cur_list)->second;

			glNewList(cur_renew, GL_COMPILE);
			glEndList();
		}
	}
}

void show_send::load_mesh_data(gongjian* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> renew_list_num;
	vector<int> del_list_num;
	//send_mesh_data 没有操作其他两个容器
	ptr->send_mesh_data(show_data, renew_list_num, del_list_num);

	if (in_list_to_start.empty())
	{
		//一定不为空
		int list_num = show_data.size();
		for (int i = 0; i < list_num; i++)
		{

		}
		int cur_list_num = glGenLists(1);
		in_list_to_start.insert({ -1, cur_list_num });
		for (int j = 0; j < list_num; j++)
		{
			//all_list_start.push_back(cur_list_num);
			glNewList(cur_list_num, GL_COMPILE);
			
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < list_num; j++)
			{
				glNormal3d(show_data[0][j].p4.x, show_data[0][j].p4.y, show_data[0][j].p4.z);
				glVertex3d(show_data[0][j].p1.x, show_data[0][j].p1.y, show_data[0][j].p1.z);
				glVertex3d(show_data[0][j].p2.x, show_data[0][j].p2.y, show_data[0][j].p2.z);
				glVertex3d(show_data[0][j].p3.x, show_data[0][j].p3.y, show_data[0][j].p3.z);
			}
			glEnd();
			glEndList();
		}
	}
	else
	{

	}
}

void show_send::load_cutted_data(gongjian* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> zu_color; 
	ptr->send_cutted_data(show_data, zu_color);

	if (in_list_to_start.empty())		//test 1.2 能清空所有列表
	{
		//一定为空
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int cur_list_num = glGenLists(1);
			in_list_to_start.insert({ 0, cur_list_num });
			
			glNewList(cur_list_num, GL_COMPILE);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);

			//需要传出颜色组信息
			int cur_color = zu_color[i];
			if (cur_color < 0)
			{
				cur_color = 0;
			}
			{
				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				
				GLfloat ambient[] = { cur_color / 10.0, cur_color / 10.0, cur_color / 10.0, 1.0 };
				GLfloat diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
				GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat shininess[] = { 0 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			}
			int len_in = show_data[i].size();
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
	}
	else
	{

	}
}

void show_send::load_shalun_data(shalun* ptr)
{
	vector<vector<mesh_cutted>> show_data;
	vector<int> renew_list_num;
	vector<int> del_list_num;
	ptr->send_shalun_data(show_data, renew_list_num, del_list_num);

	if (in_list_to_start.empty())
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int cur_list_num = glGenLists(1);
			in_list_to_start.insert({ 0, cur_list_num });
			//all_list_start.push_back(cur_list_num);
			glNewList(cur_list_num, GL_COMPILE);

			int len_in = show_data[i].size();
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
	}
	else
	{
		int len = show_data.size();
		for (int i = 0; i < len; i++)
		{
			int in_cur_list = renew_list_num[i];
			int cur_renew = in_list_to_start.find(in_cur_list)->second;
			glNewList(cur_renew, GL_COMPILE);
			int len_in = show_data[i].size();
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < len_in; j++)
			{
				glNormal3d(show_data[i][j].p4.x, show_data[i][j].p4.y, show_data[i][j].p4.z);
				glVertex3d(show_data[i][j].p1.x, show_data[i][j].p1.y, show_data[i][j].p1.z);
				glVertex3d(show_data[i][j].p2.x, show_data[i][j].p2.y, show_data[i][j].p2.z);
				glVertex3d(show_data[i][j].p3.x, show_data[i][j].p3.y, show_data[i][j].p3.z);
			}
			glEnd();
			glEndList();
		}
		for (int i = 0; i < del_list_num.size(); i++)
		{
			int in_cur_list = del_list_num[i];
			int cur_renew = in_list_to_start.find(in_cur_list)->second;

			glNewList(cur_renew, GL_COMPILE);
			glEndList();
		}
	}
}


void show_send::show(mat44& A)
{
	if (is_show)
	{
		////加颜色 ???
		//glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW);
		//GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
		//GLfloat diffuse[] = { 0.7, 0.0, 0.0, 1.0 };
		//GLfloat specular[] = { 0.3, 0.0, 0.0, 1.0 };
		//GLfloat shininess[] = { 0 };
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		for (auto it : in_list_to_start)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixd(A.memptr()); 
			glCallList(it.second);
		}
	}
}

show_send::show_send()
{
	::gladLoadGL();
}

show_send::~show_send()
{
}
