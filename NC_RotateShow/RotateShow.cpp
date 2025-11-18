#include "pch.h"
#define NC_RotateShow_EXPORTS
#include "manager_h/xt_glfw_setting.h"
#include "manager_h/MA_040101_GL_MatrixCtrl.h"
#include "RotateShow.h"



RotateShow::RotateShow(mat _data):
	my_list(0),
	show_data(_data),
	max_y(0.0),
	colour{ 1,0,0 }
{
	::gladLoadGL();
	my_list = glGenLists(1);
	find_max_y();
}



RotateShow::~RotateShow()
{
	glDeleteLists(my_list, 1);
}

void RotateShow::find_max_y()
{
	for (size_t i = 0; i < show_data.n_cols; i++)
	{
		if (show_data.col(i)[1] > max_y)
		{
			max_y = show_data.col(i)[1];
		}
	}
}

vec RotateShow::rot_angle(double err, double r_l, double start, double end)
{
	double d = 2.0 * acos((r_l - err) / r_l) * (180.0 / datum::pi);
	vec temp = linspace(start, end, ceil(360.0 / d) + 1);
	return temp;
}

void RotateShow::init_show3D()
{
	glNewList(my_list, GL_COMPILE);
	//颜色设置
#pragma region 颜色设置
	GLfloat mat_ambient[] = { colour[0] / 255.0,colour[1] / 255.0, colour[2] / 255.0, 1.0 };  // 环境光
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };     // 漫反射
	GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };  // 镜面反射
	GLfloat mat_shininess[] = { 76.8 };  // 高光指数

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
#pragma endregion

		
	
	vec angle = rot_angle(0.001, max_y, 0.0, 360.0);
	mat temp1(show_data);
	mat temp2(tcRotX(3, angle[1]) * (show_data));
	
	for (size_t i = 1; i < angle.size(); i++)
	{
		draw3D(temp1, temp2);
		temp1 = temp2;
		temp2 = tcRotX(3, angle[1]) * temp2;
	}
	
	glEndList();
}

void RotateShow::init_show2D()
{
	glNewList(my_list, GL_COMPILE);
	draw2D();
	glEndList();
}

void RotateShow::draw3D(mat& temp0, mat& temp1)
{
	vec normal_temp;
	
	glBegin(GL_QUAD_STRIP);
	for (size_t i = 0; i < temp0.n_cols - 1; i++)
	{
		if (norm(temp0.col(i + 1) - temp1.col(i + 1)) < 1.0e-10)
		{
			normal_temp = normalise(cross(temp1.col(i) - temp0.col(i), temp0.col(i + 1) - temp0.col(i)));
		}
		else
		{
			normal_temp = normalise(cross(temp1.col(i + 1) - temp0.col(i), temp0.col(i + 1) - temp0.col(i)));
		}

		glNormal3d(normal_temp(0), normal_temp(1), normal_temp(2));
		glVertex3d(temp0.col(i)(0), temp0.col(i)(1), temp0.col(i)(2));
		glVertex3d(temp1.col(i)(0), temp1.col(i)(1), temp1.col(i)(2));
		glVertex3d(temp0.col(i + 1)(0), temp0.col(i + 1)(1), temp0.col(i + 1)(2));
		glVertex3d(temp1.col(i + 1)(0), temp1.col(i + 1)(1), temp1.col(i + 1)(2));
	}
	glEnd();
	
}

void RotateShow::draw2D()
{
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glNormal3d(0.0, 0.0, 1.0);
	for (size_t i = 0; i < show_data.n_cols; i++)
	{
		glVertex3d(show_data.col(i)[0], show_data.col(i)[1], show_data.col(i)[2]);
	}
	glEnd();
}

void RotateShow::loop_show(mat& t_Matrix)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(t_Matrix.memptr());
	/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialSHIN);*/
	glCallList(my_list);
}

void RotateShow::loop_show()
{
	glCallList(my_list);
}

void RotateShow::set_color(int r, int g, int b)
{
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;

}
