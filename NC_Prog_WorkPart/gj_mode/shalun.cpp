#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include"shalun.h"
#include"manager_h/xt_glfw_setting.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"


//包含OpenGL的文件

void shalun::set_JC_O_SL(vec3& in_JC_O_SL)
{
	JC_O_SL = in_JC_O_SL;
}

void shalun::set_JC_SYS_SL(mat33& in_JC_SYS_SL)
{
	JC_SYS_SL = in_JC_SYS_SL;
	//JC_SYS_SL = in_JC_SYS_SL * tcRotX(3,180.0);
}

shalun::shalun()
{
}

shalun::shalun(vec3 &p, mat33 &mat3)
{
	JC_O_SL = p;
	JC_SYS_SL = mat3;
}

shalun::~shalun()
{
}

void shalun::init_shape(double in, double out, double c_d, std::vector<double>& v_lens, std::vector<double>& v_rs)
{
	::gladLoadGL();
	in_length = in;
	out_length = out;
	cover_d = c_d;

	set_outline(v_lens, v_rs);

	{
		//gl_list_sl = glGenLists(1);
		//glNewList(gl_list_sl, GL_COMPILE);
		//{
		//	//设置OpenGL材料  10.23
		//	GLfloat ambient[] = { 0.0, 0.2, 0.2, 1.0 };
		//	GLfloat diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
		//	GLfloat specular[] = { 0.0, 1.0, 1.0, 1.0 };
		//	GLfloat shininess[] = { 0 };
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		//	//20231020 改了out_length-in_length 
		//	//for (size_t i = 0; i < 72; i++)
		//	//{
		//	//	glBegin(GL_POLYGON);
		//	//	vec normal = tcRotZ(3, 10.0 * double(i)) * tcX(3);
		//	//	//glColor3d(1.0, 0.0, 0.0);
		//	//	glNormal3d(normal(0), normal(1), normal(2));
		//	//	vec p1 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cover_d / 2.0 + tcZ(3) * (in_length);
		//	//	vec p2 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cover_d / 2.0 + tcZ(3) * (in_length);
		//	//	vec p3 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cover_d / 2.0 + tcZ(3) * (out_length);
		//	//	vec p4 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cover_d / 2.0 + tcZ(3) * (out_length);
		//	//	glVertex3d(p1(0), p1(1), p1(2));
		//	//	glVertex3d(p2(0), p2(1), p2(2));
		//	//	glVertex3d(p3(0), p3(1), p3(2));
		//	//	glVertex3d(p4(0), p4(1), p4(2));
		//	//	glEnd();
		//	//}
		//	for (auto it = outline_len_r.begin(); it != outline_len_r.end(); )
		//	{
		//		double cur_len = it->first;
		//		double cur_r = it->second;
		//		it++;
		//		if (it == outline_len_r.end())
		//		{
		//			break;
		//		}
		//		double cur_len2 = it->first;
		//		double cur_r2 = it->second;
		//		for (size_t i = 0; i < 72; i++)//画侧面四边形
		//		{
		//			glBegin(GL_POLYGON);
		//			vec normal = tcRotZ(3, 10.0 * double(i)) * tcX(3);
		//			//glColor3d(1.0, 0.0, 0.0);
		//			glNormal3d(normal(0), normal(1), normal(2));
		//			vec p1 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r +  tcZ(3) * (cur_len);
		//			vec p2 = tcRotZ(3, 10.0 * double(i))     * tcX(3) * cur_r +  tcZ(3) * (cur_len);
		//			vec p3 = tcRotZ(3, 10.0 * double(i))     * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);
		//			vec p4 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);
		//			glVertex3d(p1(0), p1(1), p1(2));
		//			glVertex3d(p2(0), p2(1), p2(2));
		//			glVertex3d(p3(0), p3(1), p3(2));
		//			glVertex3d(p4(0), p4(1), p4(2));
		//			glEnd();
		//		}
		//	}
		//	
		//	double in_r = outline_len_r.begin()->second;
		//	//画两个端面
		//	{
		//		glNormal3d(0.0, 0.0, -1.0);
		//		glBegin(GL_POLYGON);
		//		vec p1;
		//		for (size_t i = 0; i < 36; i++)
		//		{
		//			p1 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * in_r + tcZ(3) * (in_length);
		//			glVertex3d(p1(0), p1(1), p1(2));
		//		}
		//		glEnd();
		//	}
		//	auto it = outline_len_r.end();
		//	it--;
		//	double out_r = it->second;
		//	{
		//		glNormal3d(0.0, 0.0, 1.0);
		//		glBegin(GL_POLYGON);
		//		vec p1;
		//		for (size_t i = 0; i < 36; i++)
		//		{
		//			p1 = tcRotZ(3, -10.0 * double(i)) * tcX(3) * out_r + tcZ(3) * (out_length);
		//			glVertex3d(p1(0), p1(1), p1(2));
		//		}
		//		glEnd();
		//	}

		//	{
		//		//设置OpenGL材料  10.23   改变点的颜色
		//		GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		//		GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
		//		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		//		GLfloat shininess[] = { 0 };
		//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		//		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		//	}
		//}
		//glEndList();
	}
}

void shalun::reset_data()
{
	in_length = -1.0;
	out_length = -1.0;
	cover_d = -1.0;

	//JC_O_SL.clear();
	//JC_SYS_SL.clear();
	//GJ_O_SL.clear();
	//GJ_SYS_SL.clear();

	outline_len_r.clear();
}

void shalun::send_shalun_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num)
{
	vector<mesh_cutted> temp;
	mesh_cutted tri_nor;

	for (auto it = outline_len_r.begin(); it != outline_len_r.end(); )
	{
		double cur_len = it->first;
		double cur_r = it->second;
		it++;
		if (it == outline_len_r.end())
		{
			break;
		}
		double cur_len2 = it->first;
		double cur_r2 = it->second;
		for (int i = 0; i < 36; i++)//画侧面四边形
		{
			vec3 normal = tcRotZ(3, 10.0 * double(i)) * tcX(3);
			tri_nor.p4 = normal;

			vec3 p1 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r + tcZ(3) * (cur_len);
			vec3 p2 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cur_r + tcZ(3) * (cur_len);
			vec3 p3 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);
			vec3 p4 = tcRotZ(3, 10.0 * double(i + 1)) * tcX(3) * cur_r2 + tcZ(3) * (cur_len2);

			tri_nor.p1 = p1;
			tri_nor.p2 = p2;
			tri_nor.p3 = p3;
			temp.emplace_back(tri_nor);

			tri_nor.p1 = p1;
			tri_nor.p2 = p3;
			tri_nor.p3 = p4;
			temp.emplace_back(tri_nor);
		}
	}
	
	//画两个端面
	double in_r = outline_len_r.begin()->second;
	
	vector<double3v> v_seg;
	vec3 p1;
	vec3 op = tcZ(3) * (in_length);
	v_seg.emplace_back(p1);
	for (int i = 0; i < 36; i++)
	{
		p1 = tcRotZ(3, 10.0 * double(i)) * tcX(3) * in_r + tcZ(3) * (in_length);
		v_seg.emplace_back(p1);
	}
	p1 = tcRotZ(3, 10.0 * double(0)) * tcX(3) * in_r + tcZ(3) * (in_length);
	v_seg.emplace_back(p1);

	double3v ptemp = { 0, 0, -1 };
	tri_nor.p4 = ptemp;
	for (int i = 0; i < v_seg.size() - 1; i++)
	{
		tri_nor.p1 = op;
		tri_nor.p2 = v_seg[i];
		tri_nor.p3 = v_seg[i + 1];
		temp.emplace_back(tri_nor);
	}
	v_seg.clear();

	//画两个端面
	auto it = outline_len_r.end();
	it--;
	double out_r = it->second;
	op = tcZ(3) * (out_length);
	v_seg.emplace_back(p1);
	for (size_t i = 0; i < 36; i++)
	{
		p1 = tcRotZ(3, -10.0 * double(i)) * tcX(3) * out_r + tcZ(3) * (out_length);
		v_seg.emplace_back(p1);
	}
	p1 = tcRotZ(3, -10.0 * double(0)) * tcX(3) * out_r + tcZ(3) * (out_length);
	v_seg.emplace_back(p1);

	tri_nor.p4 = { 0, 0, 1 };
	for (int i = 0; i < v_seg.size() - 1; i++)
	{
		tri_nor.p1 = op;
		tri_nor.p2 = v_seg[i];
		tri_nor.p3 = v_seg[i + 1];
		temp.emplace_back(tri_nor);
	}

	show_data.emplace_back(temp);
}

void shalun::set_outline(std::vector<double>& v_lens, std::vector<double>& v_rs)
{
	int len = v_lens.size();
	for (int i = 0; i < len; i++)
	{
		outline_len_r.insert({ v_lens[i],v_rs[i] });
	}
}




//void shalun::show(mat33& A)
//{
//	::gladLoadGL();
//	vec p = tcX(3);
//	glPushMatrix();
//	mat m4(4, 4, fill::zeros);
//	m4.submat(0, 0, 2, 2) = JC_SYS_SL;
//	m4.submat(0, 3, 2, 3) = JC_O_SL;
//	m4(3, 3) = 1.0;
//	glMultMatrixd(m4.memptr());
//	glCallList(gl_list_sl);
//	glPopMatrix();
//}

void shalun::cal_SL_to_GJ(vec3& JC_O_GJ, mat33& JC_SYS_GJ)
{
	GJ_O_SL = JC_SYS_GJ.i()*(JC_O_SL - JC_O_GJ);
	//GJ_O_SL = (JC_O_SL - JC_O_GJ);  //9.5
	GJ_SYS_SL = JC_SYS_GJ.i() * JC_SYS_SL;
}

tanzhen_Z::tanzhen_Z()
{
	JC_O_TZ = { 0.0, 0.0, 0.0 };
	JC_SYS_TZ = eye(3, 3);
}

tanzhen_Z::~tanzhen_Z()
{
}

void tanzhen_Z::cal_self_pos(mat44& mat_z)
{
	JC_SYS_TZ = mat_z.submat(0, 0, 2, 2);
	vec3 ls_shalun = mat_z.submat(0, 3, 2, 3);
	
	JC_O_TZ = { ls_shalun(0) - 79.471, 
				ls_shalun(1) + 10.578,
				ls_shalun(2) - 85.01 };
	
	//up_lien = { JC_O_TZ(0) , JC_O_TZ(1) + 4.814, JC_O_TZ(2) };
	//mid_face = { JC_O_TZ(0), JC_O_TZ(1) + 4.814 + 1, JC_O_TZ(2) - 4.814 };
	//dwon_point = { JC_O_TZ(0), JC_O_TZ(1), JC_O_TZ(2) - 9.628 }; 
	//dwon_lien = { JC_O_TZ(0), JC_O_TZ(1) + 4.814, JC_O_TZ(2) - 9.628 };

	//cal_peng_points.emplace_back(JC_O_TZ);
	//cal_peng_points.emplace_back(up_lien);
	//cal_peng_points.emplace_back(mid_face);
	//cal_peng_points.emplace_back(dwon_point);
	//cal_peng_points.emplace_back(dwon_lien );
}


