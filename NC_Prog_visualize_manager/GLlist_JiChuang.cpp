#include "pch.h"
#define NC_Prog_visualize_manager_EXPORTS
#include "GLlist_Color.h"
#include "GLlist_Pbody.h"
#include"manager_h/MA_010101_NC_wheel_data.h"
#include"manager_h/MA_010101_NC_RotateShow.h"
#include "GLlist_JiChuang.h"

GLlist_JiChuang::GLlist_JiChuang()
{
	range_xyz.resize(3, 2);
	range_xyz.col(0).fill(-1.0);
	range_xyz.col(1).fill(1.0);
	Part = nullptr;
	//Tool = nullptr;

	v_hide.resize(4);
}

GLlist_JiChuang::~GLlist_JiChuang()
{
	for (auto i : Zaxis)
	{
		delete i;
	}

	for (auto i : Aaxis)
	{
		delete i;
	}

	for (auto i : Xaxis)
	{
		delete i;
	}
	for (auto i : Yaxis)
	{
		delete i;
	}
	for (auto i : Zaxis)
	{
		delete i;
	}
	for (auto i : base)
	{
		delete i;
	}

	//if (Tool != nullptr)
	//{
	//	delete Tool;
	//	Tool = nullptr;
	//}
	if (!Tool.empty())
	{
		for (size_t i = 0; i < Tool.size(); i++)
		{
			delete Tool[i];
		}
	}

	if (Part != nullptr)
	{
		delete Part;
		Part = nullptr;
	}
}

bool GLlist_JiChuang::init()
{
	//使用GLAD来加载OpenGL
	::gladLoadGL();
	int n = 0;
	gyGLColor colorpad;
	n = 0;

	GLlist_Pbody* A_zhou = new GLlist_Pbody;
	colorpad.color_product(2);	//0-13
	A_zhou->set_color(colorpad);
	if (!A_zhou->read_stl("STL\\A_zhou.stl"))
	{
		return false;
	}
	n++;


	GLlist_Pbody* C_gan = new GLlist_Pbody;
	colorpad.color_product(n);
	C_gan->set_color(colorpad);
	if (!C_gan->read_stl("STL\\C_gan.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* C_tanzhen = new GLlist_Pbody;
	colorpad.color_product(0);
	C_tanzhen->set_color(colorpad);
	if (!C_tanzhen->read_stl("STL\\C_tanzhen.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* C_zhou = new GLlist_Pbody;
	colorpad.color_product(11);
	C_zhou->set_color(colorpad);
	if (!C_zhou->read_stl("STL\\C_zhou.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* X_huakuai = new GLlist_Pbody;
	colorpad.color_product(n);
	X_huakuai->set_color(colorpad);
	if (!X_huakuai->read_stl("STL\\X_huakuai.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* XY_daogui = new GLlist_Pbody;
	colorpad.color_product(11);
	XY_daogui->set_color(colorpad);
	if (!XY_daogui->read_stl("STL\\XY_daogui.stl"))  
	{
		return false;
	}
	n++;

	GLlist_Pbody* Z_daogui = new GLlist_Pbody;
	colorpad.color_product(n);
	Z_daogui->set_color(colorpad);
	if (!Z_daogui->read_stl("STL\\Z_daogui.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* Z_guandao = new GLlist_Pbody;
	colorpad.color_product(n);
	Z_guandao->set_color(colorpad);
	if (!Z_guandao->read_stl("STL\\Z_guandao.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* Z_huakuai = new GLlist_Pbody;
	colorpad.color_product(n);
	Z_huakuai->set_color(colorpad);
	if (!Z_huakuai->read_stl("STL\\Z_huakuai.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* Z_tanzhen = new GLlist_Pbody;
	colorpad.color_product(0);
	Z_tanzhen->set_color(colorpad);
	if (!Z_tanzhen->read_stl("STL\\Z_tanzhen.stl"))
	{
		return false;
	}
	n++;

	GLlist_Pbody* Z_zhuzhou = new GLlist_Pbody;
	colorpad.color_product(n);
	Z_zhuzhou->set_color(colorpad);
	if (!Z_zhuzhou->read_stl("STL\\Z_zhuzhou.stl"))
	{
		return false;
	}
	n++;

	//GLlist_Pbody* Z_box = new GLlist_Pbody;
	//colorpad.color_product(n);
	//Z_zhuzhou->set_color(colorpad);
	//if (!Z_zhuzhou->read_stl("STL\\z_box2.stl"))
	//{
	//	return false;
	//}

	Caxis.push_back(C_gan);
	Caxis.push_back(C_tanzhen);
	Caxis.push_back(C_zhou);

	Xaxis.push_back(X_huakuai);

	Yaxis.push_back(Z_daogui);

	Zaxis.push_back(Z_guandao);
	Zaxis.push_back(Z_tanzhen);
	Zaxis.push_back(Z_zhuzhou);
	Zaxis.push_back(Z_huakuai);

	//Zaxis.push_back(Z_box);

	Aaxis.push_back(A_zhou);
	
	base.push_back(XY_daogui);
	
	

	for (auto i : Zaxis)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}
	for (auto i : Xaxis)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}
	for (auto i : Yaxis)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}
	for (auto i : Aaxis)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}
	for (auto i : Caxis)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}
	for (auto i : base)
	{
		if (i->get_max_x() > get_max_x())
		{
			range_xyz(0, 1) = i->get_max_x();
		}
		if (i->get_max_y() > get_max_y())
		{
			range_xyz(1, 1) = i->get_max_y();
		}
		if (i->get_max_z() > get_max_z())
		{
			range_xyz(2, 1) = i->get_max_z();
		}
		if (i->get_min_x() < get_min_x())
		{
			range_xyz(0, 0) = i->get_min_x();
		}
		if (i->get_min_y() < get_min_y())
		{
			range_xyz(1, 0) = i->get_min_y();
		}
		if (i->get_min_z() < get_min_z())
		{
			range_xyz(2, 0) = i->get_min_z();
		}
	}


	return true;
}

bool GLlist_JiChuang::init_part_by_stl(string dir)
{
	gyGLColor colorpad;
	Part = new GLlist_Pbody;
	colorpad.color_product(0);
	Part->set_color(colorpad);
	if (!Part->read_stl(dir))
	{
		return false;
	}
	Aaxis.push_back(Part);
	return true;
}

bool GLlist_JiChuang::init_tool(vector<mat>& _point)
{
	RotateShow* temp = nullptr;
	for (size_t i = 0; i < _point.size(); i++)
	{
		temp = new RotateShow(_point[i]);
		temp->set_color(200, 10, 10);
		temp->init_show3D();
		Tool.push_back(temp);
	}
	return true;
}

bool GLlist_JiChuang::unload_tool()
{
	if (!Tool.empty())
	{
		for (size_t i = 0; i < Tool.size(); i++)
		{
			delete Tool[i];
		}
	}
	Tool.clear();
	return true;
}

void GLlist_JiChuang::show(
	mat44& base_in,
	double x,
	double y,
	double z,
	double a,
	double c
)
{
	mat44 matX_in = base_in * tcTranslate(-x, 0.0, 0.0);
	mat44 matY_in = base_in * tcTranslate(0.0, y, 0.0);
	mat44 matC_in = matX_in * tcRotZ(4, c);
	mat44 matZ_in = matY_in * tcTranslate(0.0, 0.0, z);
	mat44 matA_in = matC_in * tcTranslate(0.0, 0.0, 30) * tcRotY(4, a) * tcTranslate(0.0, 0.0, -30);

#pragma region 是否显示部件控制 2024.8.29 zy
	if (v_hide[0])
	{
		for (auto i : base)
		{
			i->show(base_in);
		}
	}
	if (v_hide[1])
	{
		for (auto i : Xaxis)
		{
			i->show(matX_in);
		}
	}
	if (v_hide[2])
	{
		for (auto i : Yaxis)
		{
			i->show(matY_in);
		}
	}
	if (v_hide[3])
	{
		for (auto i : Zaxis)
		{
			i->show(matZ_in);
		}
	}

	for (auto i : Aaxis)
	{
		i->show(matA_in);
	}
	for (auto i : Caxis)
	{
		i->show(matC_in);
	}
#pragma endregion

	if (!Tool.empty())
	{
		//调整砂轮位置 3.14
		mat temp = matZ_in * tcTranslate(219.832, 350.927, 179.5) * tcRotZ(4, -90.0); 
		//test 1.2
		//mat temp = matZ_in ;
		//mat temp = tcTranslate(-100, -200, 0) * matZ_in  * tcRotZ(4, -90.0);
		//GLfloat ambient[] = { 0.0, 0.6, 1.0, 1.0 };
		//GLfloat diffuse[] = { 0.7, 0.0, 0.0, 1.0 };
		//GLfloat specular[] = { 0.3, 0.0, 0.0, 1.0 };
		//GLfloat shininess[] = { 0 };
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		for (size_t i = 0; i < Tool.size(); i++)
		{
			Tool[i]->loop_show(temp);
		}
	}
}

double GLlist_JiChuang::get_max_x()
{
	return range_xyz(0, 1);
}
double GLlist_JiChuang::get_max_y()
{
	return range_xyz(1, 1);
}
double GLlist_JiChuang::get_max_z()
{
	return range_xyz(2, 1);
}
double GLlist_JiChuang::get_min_x()
{
	return range_xyz(0, 0);
}
double GLlist_JiChuang::get_min_y()
{
	return range_xyz(1, 0);
}
double GLlist_JiChuang::get_min_z()
{
	return range_xyz(2, 0);
}