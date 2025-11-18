#include "pch.h"
#define NC_Prog_visualize_manager_EXPORTS
#include "GLlist_Color.h"
#include "GLlist_Pbody.h"

GLlist_Pbody::GLlist_Pbody()
{
	//使用GLAD来加载OpenGL
	::gladLoadGL();
	body_glList = glGenLists(1);
	materialAmb[0] = 0.5;
	materialAmb[1] = 0.5;
	materialAmb[2] = 0.5;
	materialAmb[3] = 1.0;

	materialDiff[0] = 0.5;
	materialDiff[1] = 0.5;
	materialDiff[2] = 0.5;
	materialDiff[3] = 1.0;

	materialSpec[0] = 0.5;
	materialSpec[1] = 0.5;
	materialSpec[2] = 0.5;
	materialSpec[3] = 1.0;

	materialSHIN = 1.0;
	range_xyz.resize(3, 2);
	range_xyz.col(0).fill(-1.0);
	range_xyz.col(1).fill(1.0);

	is_show = true;
	x_offset = 0.0;
	y_offset = 0.0;
	z_offset = 0.0;
}

GLlist_Pbody::~GLlist_Pbody()
{
	glDeleteLists(body_glList, 1);
}

bool GLlist_Pbody::read_stl(std::string dir)
{
	if (stl_reader.read_file(dir))
	{
		range_xyz(0, 0) = stl_reader.min_x();
		range_xyz(1, 0) = stl_reader.min_y();
		range_xyz(2, 0) = stl_reader.min_z();
		range_xyz(0, 1) = stl_reader.max_x();
		range_xyz(1, 1) = stl_reader.max_y();
		range_xyz(2, 1) = stl_reader.max_z();
		draw();
		return true;
	}
	else
	{
		return false;
	}
}

void GLlist_Pbody::draw()
{
	glNewList(body_glList, GL_COMPILE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialSHIN);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < stl_reader.Facet_count(); i++)
	{
		glNormal3d(stl_reader.n(i)[0], stl_reader.n(i)[1], stl_reader.n(i)[2]);
		glVertex3d(stl_reader.x(i, 0) + x_offset, stl_reader.y(i, 0) + y_offset, stl_reader.z(i, 0) + z_offset);
		glVertex3d(stl_reader.x(i, 1) + x_offset, stl_reader.y(i, 1) + y_offset, stl_reader.z(i, 1) + z_offset);
		glVertex3d(stl_reader.x(i, 2) + x_offset, stl_reader.y(i, 2) + y_offset, stl_reader.z(i, 2) + z_offset);
	}
	glEnd();
	glEndList();
}

bool GLlist_Pbody::set_color(fvec4 amb, fvec4 diff, fvec4 spec, float shin)
{
	materialAmb[0] = amb[0];
	materialAmb[1] = amb[1];
	materialAmb[2] = amb[2];
	materialAmb[3] = amb[3];

	materialDiff[0] = diff[0];
	materialDiff[1] = diff[1];
	materialDiff[2] = diff[2];
	materialDiff[3] = diff[3];

	materialSpec[0] = spec[0];
	materialSpec[1] = spec[1];
	materialSpec[2] = spec[2];
	materialSpec[3] = spec[3];

	materialSHIN = shin;
	return false;
}

bool GLlist_Pbody::set_color(gyGLColor& color)
{
	materialAmb[0] = color.color_amb[0];
	materialAmb[1] = color.color_amb[1];
	materialAmb[2] = color.color_amb[2];
	materialAmb[3] = color.color_amb[3];

	materialDiff[0] = color.color_diff[0];
	materialDiff[1] = color.color_diff[1];
	materialDiff[2] = color.color_diff[2];
	materialDiff[3] = color.color_diff[3];

	materialSpec[0] = color.color_spec[0];
	materialSpec[1] = color.color_spec[1];
	materialSpec[2] = color.color_spec[2];
	materialSpec[3] = color.color_spec[3];

	materialSHIN = color.shin;
	return true;
}

void GLlist_Pbody::set_offset(double x, double y, double z)
{
	x_offset = x;
	y_offset = y;
	z_offset = z;
	range_xyz(0, 0) = range_xyz(0, 0) + x_offset;
	range_xyz(1, 0) = range_xyz(1, 0) + y_offset;
	range_xyz(2, 0) = range_xyz(2, 0) + z_offset;
	range_xyz(0, 1) = range_xyz(0, 1) + x_offset;
	range_xyz(1, 1) = range_xyz(1, 1) + y_offset;
	range_xyz(2, 1) = range_xyz(2, 1) + z_offset;
	draw();
}

void GLlist_Pbody::show(mat44& A)
{
	if (is_show)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(A.memptr());
		/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialSHIN);*/
		glCallList(body_glList);
	}
}

void GLlist_Pbody::turnOn()
{
	is_show = true;
}

void GLlist_Pbody::turnOff()
{
	is_show = false;
}

double GLlist_Pbody::get_max_x()
{
	return range_xyz(0, 1);
}
double GLlist_Pbody::get_max_y()
{
	return range_xyz(1, 1);
}
double GLlist_Pbody::get_max_z()
{
	return range_xyz(2, 1);
}
double GLlist_Pbody::get_min_x()
{
	return range_xyz(0, 0);
}
double GLlist_Pbody::get_min_y()
{
	return range_xyz(1, 0);
}
double GLlist_Pbody::get_min_z()
{
	return range_xyz(2, 0);
}

mat GLlist_Pbody::get_box()
{
	return range_xyz;
}
