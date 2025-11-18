#include "pch.h"
//#define NC_wheel_data_EXPORTS

#include "line_manager.h"


#undef max
#undef min
using namespace std;

line_manager::line_manager(const std::string& filename)
{
	min_xyz.set_c(0) = DBL_MAX;
	min_xyz.set_c(1) = DBL_MAX;
	min_xyz.set_c(2) = DBL_MAX;
	read_dxf file(filename);
	file.get_all_arc(all_arc);
	file.get_all_line(all_line);
	take_all_points();
	//move_to_origin();
	add_to_datamat();
	sort();
}

void line_manager::get_all_line(vector<dxf_line*>& all_line_in)
{
	all_line_in = all_line;
}

void line_manager::get_all_arc(vector<dxf_arc*>& all_arc_in)
{
	all_arc_in = all_arc;
}


void line_manager::get_discrete_point(double d, vector<vec>& points)
{
	double flag = 0.0;
	double offset = 0.0;
	vec temp;

	for (size_t i = 0; i < show_data.n_cols; i++)
	{
		temp = show_data.col(i);
		flag = temp(0);
		if (flag == DXF_LINE)
		{
			offset = discrete_line2(temp, d, offset, points);

		}
		else
		{
			offset = discrete_arc2(temp, d, offset, points);
		}
	}
	//补充最后一个点，出线段的点
	{
		vec t = { points.back()[0],points.back()[1], points.back()[2] };
		vec temp = { points.back()[3],points.back()[4], points.back()[5] };
		temp = temp + (d * t);
		vec point = { t[0],t[1],t[2], temp[0],temp[1],temp[2] };
		points.push_back(point);
	}
}

void line_manager::get_integral_point(double L, double angle, vector<vec>& points)
{
	vector<vec> points_temp;
	double L_count = 0.0;
	double angle_count = 0.0;

	get_discrete_point(0.0001, points_temp);
	points.push_back(points_temp[0]);
	for (size_t i = 0; i < points_temp.size() - 1; i++)
	{
		vec p0 = { points_temp[i][3], points_temp[i][4], points_temp[i][5] };
		vec p1 = { points_temp[i + 1][3], points_temp[i + 1][4], points_temp[i + 1][5] };
		vec t0 = { points_temp[i][0], points_temp[i][1], points_temp[i][2] };
		vec t1 = { points_temp[i + 1][0], points_temp[i + 1][1], points_temp[i + 1][2] };
		L_count = L_count + norm(p0 - p1);
		angle_count = angle_count + (180.0 * acos(dot(t0, t1) / (norm(t0) * norm(t1))) / datum::pi);
		//积分距离
		if (L_count > L)
		{
			points.push_back(points_temp[i + 1]);
			L_count = 0.0;
			angle_count = 0.0;
		}
		//积分角度
		else if (angle_count > angle)
		{
			points.push_back(points_temp[i + 1]);
			L_count = 0.0;
			angle_count = 0.0;
		}
	}
	points.push_back(points_temp.back());

}

//void line_manager::show_point(double L, double angle)
//{
//	vector<vec> point_all;
//	get_integral_point(L, angle, point_all);
//	GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
//	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
//	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat mat_shininess[] = { 50.0 };
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//	glBegin(GL_LINES);
//	for (size_t i = 0; i < point_all.size(); i++)
//	{
//		double x = point_all[i](3);
//		double y = point_all[i](4);
//		double z = point_all[i](5);
//
//		vec normal = { point_all[i](0), point_all[i](1), point_all[i](2) };
//		normal = tcRotZ(3, 90) * normal;
//		vec temp = { x,y,z };
//		temp = temp + normal * 2.0;
//
//		glVertex3d(x, y, z);
//		glVertex3d(temp[0], temp[1], temp[2]);
//
//	}
//	glEnd();
//}

void line_manager::get_curvature_point(double e, mat& points)
{
	double flag = 0;
	double d = 0.0;
	vec temp;


	for (size_t i = 0; i < show_data.n_cols; i++)
	{
		temp = show_data.col(i);
		flag = temp(0);
		if (flag == DXF_LINE)
		{
			//计算直线长度
			double L = line_L(temp);

			discrete_line(temp, L / 2.0, points);
		}
		else
		{
			//计算圆弧总角度
			double L = arc_L(temp);
			double r_l = temp(4);
			double d = 2.0 * acos((r_l - e) / r_l) * (180.0 / datum::pi);
			discrete_arc_angle(temp, L / ceil(L / d), points);
		}
	}
}

//void line_manager::show()
//{
//	_show_arc();
//	_show_line();
//}


//void line_manager::show_point(double d)
//{
//	vector<vec> point_all;
//	get_discrete_point(d, point_all);
//	GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
//	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
//	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat mat_shininess[] = { 50.0 };
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//	glBegin(GL_LINES);
//	for (size_t i = 0; i < point_all.size(); i++)
//	{
//		double x = point_all[i](3);
//		double y = point_all[i](4);
//		double z = point_all[i](5);
//
//		vec normal = { point_all[i](0), point_all[i](1), point_all[i](2) };
//		normal = tcRotZ(3, 90) * normal;
//		vec temp = { x,y,z };
//		temp = temp + normal * 2.0;
//
//		glVertex3d(x, y, z);
//		glVertex3d(temp[0], temp[1], temp[2]);
//
//	}
//	glEnd();
//}

//void line_manager::show_point_e(double e)
//{
//	//用于存储点集，单列为一个点vec(6)
//	mat points;
//	double d = 1.0;
//	get_curvature_point(e, points);
//	glBegin(GL_POINTS);
//	for (size_t i = 0; i < points.n_cols; i++)
//	{
//		double x = points.col(i)(3);
//		double y = points.col(i)(4);
//		double z = points.col(i)(5);
//		vec size_n = { points.col(i)(0),points.col(i)(1),points.col(i)(2) };
//		vec temp = { x, y, z };
//		glVertex3d(x, y, z);
//	}
//	glEnd();
//
//	for (size_t i = 0; i < points.n_cols; i++)
//	{
//		double x = points.col(i)(3);
//		double y = points.col(i)(4);
//		double z = points.col(i)(5);
//		vec normal = { points.col(i)(0),points.col(i)(1),points.col(i)(2) };
//		vec temp = { x,y,z };
//		//
//		vec temp1 = temp + normal * d * 0.7;
//		mat rot0 = { {-0.866,-0.5,0}, {0.5,-0.866,0}, {0.0,0.0,1.0} };
//		mat rot1 = { {-0.866,0.5,0}, {-0.5,-0.866,0}, {0.0,0.0,1.0} };
//		glBegin(GL_LINE_STRIP);
//		{
//			glVertex3d(x, y, z);
//			x = temp1(0);
//			y = temp1(1);
//			z = temp1(2);
//			glVertex3d(x, y, z);
//
//			/*	temp1 = temp1 + rot0 * (normal * d * 0.4);
//				x = temp1(0);
//				y = temp1(1);
//				z = temp1(2);
//				glVertex3d(x, y, z);*/
//		}
//		glEnd();
//		/*temp1 = temp + normal * d * 0.7;
//		glBegin(GL_LINE_STRIP);
//		{
//			x = temp1(0);
//			y = temp1(1);
//			z = temp1(2);
//			glVertex3d(x, y, z);
//
//			temp1 = temp1 + rot1 * (normal * d * 0.4);
//			x = temp1(0);
//			y = temp1(1);
//			z = temp1(2);
//			glVertex3d(x, y, z);
//		}
//		glEnd();*/
//	}
//
//
//}

void line_manager::take_all_points()
{
	double* temp_c = nullptr;

	for (size_t i = 0; i < all_line.size(); i++)
	{
		temp_c = all_line[i]->get_start()->get_c_ptr();
		find_min_xyz(temp_c[0], temp_c[1], temp_c[2]);
		temp_c = all_line[i]->get_end()->get_c_ptr();
		find_min_xyz(temp_c[0], temp_c[1], temp_c[2]);
	}
	for (size_t i = 0; i < all_arc.size(); i++)
	{
		temp_c = all_arc[i]->get_center()->get_c_ptr();
		find_min_xyz(temp_c[0] - all_arc[i]->get_r(), temp_c[1] - all_arc[i]->get_r(), temp_c[2]);
	}
}

void line_manager::move_to_origin()
{
	double* temp_c = nullptr;
	double* temp_min = min_xyz.get_c_ptr();

	for (size_t i = 0; i < all_line.size(); i++)
	{
		temp_c = all_line[i]->get_start()->get_c_ptr();
		temp_c[0] -= temp_min[0];
		temp_c[1] -= temp_min[1];
		temp_c[2] -= temp_min[2];
		temp_c = all_line[i]->get_end()->get_c_ptr();
		temp_c[0] -= temp_min[0];
		temp_c[1] -= temp_min[1];
		temp_c[2] -= temp_min[2];
	}
	for (size_t i = 0; i < all_arc.size(); i++)
	{
		temp_c = all_arc[i]->get_center()->get_c_ptr();
		temp_c[0] -= temp_min[0];
		temp_c[1] -= temp_min[1];
		temp_c[2] -= temp_min[2];
	}
}

bool line_manager::line_line_round_OK(vec& first, vec& second, double r_l)
{
	vec start0, end0;
	vec start1, end1;
	get_line_data(first, start0, end0);
	get_line_data(second, start1, end1);

	double L0 = line_L(first);
	double L1 = line_L(second);
	vec temp_L = { std::min(L0, L1), 0, 0 };
	//计算夹角
	double angleDeg = acos(dot(start0 - end0, end1 - start1) / (L0 * L1)) * 180.0 / datum::pi;
	vec temp_r = { r_l, 0, 0 };
	//判断r满足倒角条件
	if (norm(tcRotZ(3, angleDeg) * temp_L - temp_L) > norm(tcRotZ(3, 180.0 - angleDeg) * temp_r - temp_r))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




void line_manager::set_round(double r_l)
{
	vec ans0;
	vec ans1;
	if (show_data.n_cols < 2)
	{
		return;
	}
	for (size_t i = 0; i < show_data.n_cols; i++)
	{
		int flag = read_data(i, ans0);
		//当前为直线的情况
		if (flag == DXF_LINE)
		{
			//判断下一条为直线
			if (read_data(i + 1, ans1) == DXF_LINE)
			{
				vec start0, end0;
				vec start1, end1;
				get_line_data(ans0, start0, end0);
				get_line_data(ans1, start1, end1);
				//两直线平行
				if (norm(cross((start0 - end0), (start1 - end1))) < 1.0e-10)
				{
					continue;
				}
				else if (line_line_round_OK(ans0, ans1, r_l))
				{

				}
			}
			else
			{

			}
		}



	}

}



//void line_manager::_show_arc()
//{
//	for (size_t i = 0; i < all_arc.size(); i++)
//	{
//		auto temp_start = all_arc[i]->get_start();
//		auto temp_end = all_arc[i]->get_end();
//		double size_n = 0.0;
//		glBegin(GL_LINE_STRIP);
//
//
//		if (temp_start > temp_end)
//		{
//			size_n = 360.0 + temp_end - temp_start;
//		}
//		else
//		{
//			size_n = temp_end - temp_start;
//		}
//		double j = all_arc[i]->get_start();
//		for (double k = 0.0; k < size_n; j += 0.1, k += 0.1)
//		{
//			if (j >= 360.0)
//			{
//				j -= 360.0;
//			}
//			auto temp = all_arc[i]->get_center()->get_c_ptr();
//			auto r_l = all_arc[i]->get_r();
//			double x = temp[0] + r_l * cos(j * datum::pi / 180.0);
//			double y = temp[1] + r_l * sin(j * datum::pi / 180.0);
//			glVertex3d(x, y, 0);
//		}
//		glEnd();
//	}
//}
//
//void line_manager::_show_line()
//{
//	double* temp = nullptr;
//	glBegin(GL_LINES);
//	for (size_t i = 0; i < all_line.size(); i++)
//	{
//		temp = all_line[i]->get_start()->get_c_ptr();
//		glVertex3d(temp[0], temp[1], temp[2]);
//		temp = all_line[i]->get_end()->get_c_ptr();
//		glVertex3d(temp[0], temp[1], temp[2]);
//	}
//	glEnd();
//}

void line_manager::sort()
{

	mat temp_data;
	//放入第一个列到临时矩阵
	temp_data.insert_cols(0, show_data.col(0));
	//从data中删除已经被放入临时矩阵的列
	show_data.shed_col(0);
	int size_n = show_data.n_cols;
	int i = 0;
	//在data中找临时矩阵最后一列相邻的线段
	while (!show_data.empty() && i < show_data.n_cols)
	{
		//临时矩阵最后列 起点 终点
		auto v0 = get_extreme(temp_data.n_cols - 1, temp_data);
		//data第i列 起点 终点
		auto v1 = get_extreme(i, show_data);
		//是相邻的
		if (is_in_domain(v0, v1))
		{
			vec v_temp;
			double flag1 = 0;
			double flag2 = 0;
			switch (is_in_domain(v0, v1))
			{
			case 1:
				//把相邻的线段插入到临时矩阵最后
				temp_data.insert_cols(temp_data.n_cols, show_data.col(i));
				//从data中删除已经被放入临时矩阵的列
				show_data.shed_col(i);
				i = -1;
				break;
			case 4:
				v_temp = show_data.col(i);
				show_data.shed_col(i);
				flag1 = v_temp(0);
				//判断是直线
				if (flag1 == DXF_LINE)
				{
					change_line(v_temp);
					temp_data.insert_cols(temp_data.n_cols, v_temp);
				}
				else
				{
					change_arc(v_temp);
					temp_data.insert_cols(temp_data.n_cols, v_temp);
				}
				i = -1;
				break;

			case 3:
				flag1 = temp_data.col(temp_data.n_cols - 1)(0);
				flag2 = show_data.col(i)(0);
				if (flag1 == flag2)
				{
					if (flag1 == DXF_LINE)
					{
						//两个直线首尾相连
						show_data.shed_col(i);
					}
					else
					{
						//两个圆弧首尾相连
						show_data.shed_col(i);
					}
				}
				i = -1;
				break;
			case 12:
				flag1 = temp_data.col(temp_data.n_cols - 1)(0);
				flag2 = show_data.col(i)(0);
				if (flag1 == flag2)
				{
					if (flag1 == DXF_LINE)
					{
						//两个直线首首相连,尾尾相连
						show_data.shed_col(i);
					}
					else
					{
						//两个圆弧首首相连,尾尾相连
						show_data.shed_col(i);
					}
				}
				i = -1;
				break;
			default:
				break;
			}
		}
		i++;
	}
	i = 0;
	//在data中找临时矩阵第0列相邻的线段
	while (!show_data.empty() && i < show_data.n_cols)
	{
		auto v0 = get_extreme(0, temp_data);
		auto v1 = get_extreme(i, show_data);
		if (is_in_domain(v0, v1))
		{
			vec v_temp;
			double flag1 = 0;
			double flag2 = 0;
			switch (is_in_domain(v0, v1))
			{
			case 2:
				temp_data.insert_cols(0, show_data.col(i));
				show_data.shed_col(i);
				i = -1;
				break;
			case 8:
				v_temp = show_data.col(i);
				show_data.shed_col(i);
				flag1 = v_temp(0);
				if (flag1 == DXF_LINE)
				{
					change_line(v_temp);
					temp_data.insert_cols(0, v_temp);
				}
				else
				{
					change_arc(v_temp);
					temp_data.insert_cols(0, v_temp);
				}
				i = -1;
				break;
			case 3:
				flag1 = temp_data.col(0)(0);
				flag2 = show_data.col(i)(0);
				if (flag1 == flag2)
				{
					if (flag1 == DXF_LINE)
					{
						//两个直线首尾相连
						show_data.shed_col(i);
					}
					else
					{
						//两个圆弧首尾相连
						show_data.shed_col(i);
					}
				}
				i = -1;
				break;
			case 12:
				flag1 = temp_data.col(0)(0);
				flag2 = show_data.col(i)(0);
				if (flag1 == flag2)
				{
					if (flag1 == DXF_LINE)
					{
						//两个直线首首相连,尾尾相连
						show_data.shed_col(i);
					}
					else
					{
						//两个圆弧首首相连,尾尾相连
						show_data.shed_col(i);
					}
				}
				i = -1;
				break;
			default:
				break;
			}
		}
		i++;
	}
	//存在不相连的图形
	if (!show_data.empty())
	{
		show_data.clear();
		shapes = 1;
	}
	show_data = temp_data;
}

void line_manager::join_line(dxf_line* line, vec& v)
{
	double* p = nullptr;

	v(0) = DXF_LINE;
	p = line->get_start()->get_c_ptr();
	for (size_t i = 0; i < 3; i++)
	{
		v(i + 1) = p[i];
	}
	p = line->get_end()->get_c_ptr();
	for (size_t i = 0; i < 3; i++)
	{
		v(i + 4) = p[i];
	}
}

void line_manager::join_arc(dxf_arc* arc, vec& v)
{
	double* p = nullptr;
	v(0) = DXF_ARC;
	p = arc->get_center()->get_c_ptr();
	for (size_t i = 0; i < 3; i++)
	{
		v(i + 1) = p[i];
	}
	v(4) = arc->get_r();
	v(5) = arc->get_start();
	v(6) = arc->get_end();
}

void line_manager::add_to_datamat()
{
	vec temp(7, fill::zeros);
	for (dxf_line* i : all_line)
	{
		join_line(i, temp);
		if (!line_is_point(temp))
		{
			show_data.insert_cols(show_data.n_cols, temp);
		}
	}
	for (dxf_arc* i : all_arc)
	{
		join_arc(i, temp);
		if (!arc_is_point(temp))
		{
			show_data.insert_cols(show_data.n_cols, temp);
		}
	}
}

vec line_manager::get_extreme(int i, mat data_in)
{
	vec temp = data_in.col(i);
	vec ans(6);
	//直线
	double temp0 = temp(0);
	if (temp0 == DXF_LINE)
	{
		for (size_t i = 0; i < 6; i++)
		{
			ans(i) = temp(i + 1);
		}
		return ans;
	}
	//圆弧
	else if (temp0 == DXF_ARC)
	{
		ans(0) = temp(1) + temp(4) * cos(temp(5) * datum::pi / 180.0);
		ans(1) = temp(2) + temp(4) * sin(temp(5) * datum::pi / 180.0);
		ans(2) = 0.0;

		ans(3) = temp(1) + temp(4) * cos(temp(6) * datum::pi / 180.0);
		ans(4) = temp(2) + temp(4) * sin(temp(6) * datum::pi / 180.0);
		ans(5) = 0.0;
		return ans;
	}
}

int line_manager::is_in_domain(vec& domain, vec& value)
{
	int temp = 0;
	vec start0 = { domain(0), domain(1), domain(2) };
	vec end0 = { domain(3), domain(4), domain(5) };
	vec start1 = { value(0), value(1), value(2) };
	vec end1 = { value(3), value(4), value(5) };
	if (norm(end0 - start1) < 0.000001)
	{
		temp |= 1;
	}
	if (norm(end1 - start0) < 0.000001)
	{
		temp |= 2;
	}
	if (norm(end0 - end1) < 0.000001)
	{
		temp |= 4;
	}
	if (norm(start0 - start1) < 0.000001)
	{
		temp |= 8;
	}
	return temp;
}

void line_manager::change_line(vec& line)
{
	double x = line(1);
	double y = line(2);
	double z = line(3);
	line(1) = line(4);
	line(2) = line(5);
	line(3) = line(6);
	line(4) = x;
	line(5) = y;
	line(6) = z;
}

void line_manager::change_arc(vec& arc)
{
	double start = arc(5);
	double end = arc(6);
	if (start > 0 || end > 0)
	{
		arc(5) = end - 360.0;
		arc(6) = start - 360.0;
	}
	else
	{
		arc(5) = end + 360.0;
		arc(6) = start + 360.0;
	}
}

void line_manager::discrete_line(vec line_in, double d, mat& mat_in)
{

	vec start = { line_in(1), line_in(2), line_in(3) };
	vec end = { line_in(4), line_in(5), line_in(6) };
	//逆时针
	mat rot_0 = { {0, -1, 0},{1, 0, 0},{0, 0, 1} };
	vec normal = rot_0 * normalise(end - start);
	int size_n = static_cast<int>(std::round(norm(end - start) / d)) + 1;
	double s = start(0);
	double e = end(0);
	vec temp_x = linspace(s, e, size_n);
	s = start(1);
	e = end(1);
	vec temp_y = linspace(s, e, size_n);
	vec point(6, fill::zeros);
	for (size_t i = 0; i < 3; i++)
	{
		point(i) = normal(i);
	}
	//去除连接处重复的端点，去除上一段的最后一个点
	if (!mat_in.empty())
	{
		vec temp_p = mat_in.col(mat_in.n_cols - 1);
		vec p0 = { temp_x(0) ,temp_y(0) ,0.0 };
		vec p1 = { temp_p(3),temp_p(4) ,temp_p(5) };
		if (norm(p0 - p1) < 0.000001)
		{
			mat_in.shed_col(mat_in.n_cols - 1);
		}
	}
	for (size_t i = 0; i < size_n; i++)
	{
		point(3) = temp_x(i);
		point(4) = temp_y(i);
		point(5) = 0.0;
		mat_in.insert_cols(mat_in.n_cols, point);
	}
}

void line_manager::discrete_arc(vec arc_in, double d, mat& mat_in)
{
	vec c = { arc_in(1), arc_in(2), arc_in(3) };
	vec temp_point(3, fill::zeros);
	double start = arc_in(5);
	double end = arc_in(6);
	double r_l = arc_in(4);
	double angle = (d * 180.0) / (datum::pi * r_l);
	double angle_all = 0.0;
	int size_n = 0;
	vec temp_angle;
	//跨x轴判断
	if (start < 0 || end < 0)
	{
		if (start > end)
		{
			angle_all = abs(end - start);
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start, end, size_n);
		}
		else
		{
			angle_all = abs(end - 360 - start);
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start + 360.0, end, size_n);
		}

	}
	else
	{
		if (start > end)
		{
			angle_all = end + 360 - start;
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start - 360.0, end, size_n);
		}
		else
		{
			angle_all = end - start;
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start, end, size_n);
		}
	}


	vec normal(3, fill::zeros);
	vec point(6, fill::zeros);
	//逆时针
	mat rot_0 = { {0, -1, 0},{1, 0, 0},{0, 0, 1} };
	//顺时针
	mat rot_1 = { {0, 1, 0},{-1, 0, 0},{0, 0, 1} };
	//去除连接处重复的端点，去除上一段的最后一个点
	if (!mat_in.empty())
	{
		vec temp_p = mat_in.col(mat_in.n_cols - 1);
		temp_point(0) = c(0) + r_l * cos(temp_angle(0) * datum::pi / 180.0);
		temp_point(1) = c(1) + r_l * sin(temp_angle(0) * datum::pi / 180.0);
		temp_point(2) = 0;
		vec p1 = { temp_p(3),temp_p(4) ,temp_p(5) };
		if (norm(temp_point - p1) < 0.000001)
		{
			mat_in.shed_col(mat_in.n_cols - 1);
		}
	}
	for (size_t i = 0; i < size_n; i++)
	{
		temp_point(0) = c(0) + r_l * cos(temp_angle(i) * datum::pi / 180.0);
		temp_point(1) = c(1) + r_l * sin(temp_angle(i) * datum::pi / 180.0);
		temp_point(2) = 0.0;
		if (start < 0 || end < 0)
		{
			normal = normalise(rot_1 * rot_0 * (temp_point - c));
		}
		else
		{
			normal = normalise(rot_0 * rot_0 * (temp_point - c));
		}
		for (size_t i = 0; i < 3; i++)
		{
			point(i) = normal(i);
		}
		for (size_t i = 0; i < 3; i++)
		{
			point(i + 3) = temp_point(i);
		}
		mat_in.insert_cols(mat_in.n_cols, point);
	}
}

void line_manager::discrete_arc_angle(vec arc_in, double angle, mat& mat_in)
{
	vec c = { arc_in(1), arc_in(2), arc_in(3) };
	vec temp_point(3, fill::zeros);
	double start = arc_in(5);
	double end = arc_in(6);
	double r_l = arc_in(4);
	double angle_all = 0.0;
	int size_n = 0;
	vec temp_angle;
	//跨x轴判断
	if (start < 0 || end < 0)
	{
		if (start > end)
		{
			angle_all = abs(end - start);
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start, end, size_n);
		}
		else
		{
			angle_all = abs(end - 360 - start);
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start + 360.0, end, size_n);
		}

	}
	else
	{
		if (start > end)
		{
			angle_all = end + 360 - start;
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start - 360.0, end, size_n);
		}
		else
		{
			angle_all = end - start;
			size_n = static_cast<int>(std::round(angle_all / angle)) + 1;
			temp_angle = linspace(start, end, size_n);
		}
	}


	vec normal(3, fill::zeros);
	vec point(6, fill::zeros);
	//逆时针
	mat rot_0 = { {0, -1, 0},{1, 0, 0},{0, 0, 1} };
	//顺时针
	mat rot_1 = { {0, 1, 0},{-1, 0, 0},{0, 0, 1} };
	//去除连接处重复的端点，去除上一段的最后一个点
	if (!mat_in.empty())
	{
		vec temp_p = mat_in.col(mat_in.n_cols - 1);
		temp_point(0) = c(0) + r_l * cos(temp_angle(0) * datum::pi / 180.0);
		temp_point(1) = c(1) + r_l * sin(temp_angle(0) * datum::pi / 180.0);
		temp_point(2) = 0;
		vec p1 = { temp_p(3),temp_p(4) ,temp_p(5) };
		if (norm(temp_point - p1) < 0.000001)
		{
			mat_in.shed_col(mat_in.n_cols - 1);
		}
	}
	for (size_t i = 0; i < size_n; i++)
	{
		temp_point(0) = c(0) + r_l * cos(temp_angle(i) * datum::pi / 180.0);
		temp_point(1) = c(1) + r_l * sin(temp_angle(i) * datum::pi / 180.0);
		temp_point(2) = 0.0;
		if (start < 0 || end < 0)
		{
			normal = normalise(rot_1 * rot_0 * (temp_point - c));
		}
		else
		{
			normal = normalise(rot_0 * rot_0 * (temp_point - c));
		}
		for (size_t i = 0; i < 3; i++)
		{
			point(i) = normal(i);
		}
		for (size_t i = 0; i < 3; i++)
		{
			point(i + 3) = temp_point(i);
		}
		mat_in.insert_cols(mat_in.n_cols, point);
	}
}

bool line_manager::line_is_point(vec& line)
{
	vec start = { line(1),line(2),line(3) };
	vec end = { line(4),line(5),line(6) };
	if (norm(start - end) < 0.0000000000001)
	{
		return true;
	}
	return false;
}

bool line_manager::arc_is_point(vec& arc)
{
	double start = arc(5);
	double end = arc(6);
	if (abs(start - end) < 0.0000000000001 || abs(abs(start - end) - 360.0) < 0.0000000000001)
	{
		return true;
	}
	return false;
}

double line_manager::line_L(vec& line)
{
	vec start = { line(1), line(2), line(3) };
	vec end = { line(4), line(5), line(6) };
	return norm(start - end);
}

double line_manager::arc_L(const vec& arc)
{
	double start = arc(5);
	double end = arc(6);
	if (start < 0 || end < 0)
	{
		if (start > end)
		{
			return start - end;
		}
		else
		{
			return start - (end - 360.0);
		}
	}
	else
	{
		if (start < end)
		{
			return end - start;
		}
		else
		{
			return end + 360.0 - start;
		}
	}
}

double line_manager::discrete_line2(const vec& line_in, const double& d, const double& offset, vector<vec>& point_in)
{
	vec start;
	vec end;
	get_line_data(line_in, start, end);
	double L_temp = norm(start - end) - offset;
	if (L_temp <= 0.0)
	{
		return -L_temp;
	}
	//分段数
	int size_n = int(L_temp / d);

	vec point(6);
	//切向
	vec t = normalise(end - start);
	vec normal = tcRotZ(3, 90) * t;
	//偏置起点
	{
		start = start + (offset * t);
		point = { t[0],t[1],t[2], start[0],start[1],start[2] };
		point_in.push_back(point);
	}

	for (size_t i = 1; i <= size_n; i++)
	{
		vec temp = start + ((d * i) * t);
		point = { t[0],t[1],t[2], temp[0],temp[1],temp[2] };
		point_in.push_back(point);
	}

	return (1.0 - (L_temp / d - size_n)) * d;
}

double line_manager::discrete_arc2(const vec& line_in, const double& d, const double& offset, vector<vec>& point_in)
{
	vec c;
	double start;
	double end;
	double r_l;
	double angle_all = arc_L(line_in);
	get_arc_data(line_in, c, r_l, start, end);
	vec r_vec = { r_l, 0.0, 0.0 };
	double angle_temp = (offset / r_l) * 180.0 / datum::pi;
	double L_temp = datum::pi * r_l * angle_all / 180.0 - offset;
	//切向
	vec t(3);
	vec point(6);
	//偏置起点
	{
		vec temp;
		if (start > 0 || end > 0)
		{
			start = start + angle_temp;
			temp = c + tcRotZ(3, start) * r_vec;
			t = tcRotZ(3, 90.0) * normalise(temp - c);
		}
		else
		{
			start = start - angle_temp;
			temp = c + tcRotZ(3, start) * r_vec;
			t = tcRotZ(3, -90.0) * normalise(temp - c);
		}



		point = { t[0],t[1],t[2], temp[0],temp[1],temp[2] };
		point_in.push_back(point);
	}
	//角度增量
	angle_temp = (d / r_l) * 180.0 / datum::pi;

	//分段数
	int size_n = int(L_temp / d);

	for (size_t i = 1; i <= size_n; i++)
	{
		vec temp(3);
		if (start > 0 || end > 0)
		{
			temp = c + tcRotZ(3, start + i * angle_temp) * r_vec;
			t = tcRotZ(3, 90.0) * normalise(temp - c);
		}
		else
		{
			temp = c + tcRotZ(3, start - i * angle_temp) * r_vec;
			t = tcRotZ(3, -90.0) * normalise(temp - c);
		}

		point = { t[0],t[1],t[2], temp[0],temp[1],temp[2] };
		point_in.push_back(point);
	}

	return (1.0 - (L_temp / d - size_n)) * d;
}

bool line_manager::is_closed_shape()
{
	//判断排序好的先第一个和最后一个是否首尾相连
	vec v0 = get_extreme(0, show_data);
	vec vn = get_extreme(show_data.n_cols - 1, show_data);
	vec start = { v0(0), v0(1) ,v0(2) };
	vec end = { vn(3), vn(4) ,vn(5) };
	if (norm(start - end) < 0.000001)
	{
		return true;
	}
	return false;
}

bool line_manager::is_multiple_shapes()
{
	return shapes;
}

void line_manager::reverse_start_end()
{
	mat temp;
	vec v_temp;
	double flag = 0;
	while (!show_data.empty())
	{
		v_temp = show_data.col(0);
		show_data.shed_col(0);
		flag = v_temp(0);
		if (flag == DXF_LINE)
		{
			change_line(v_temp);
		}
		else
		{
			change_arc(v_temp);
		}
		temp.insert_cols(0, v_temp);
	}
	show_data = temp;
}

void line_manager::find_min_xyz(double x, double y, double z)
{
	double* c = min_xyz.get_c_ptr();
	if (x < c[0])
	{
		c[0] = x;
	}
	if (y < c[1])
	{
		c[1] = y;
	}
	if (z < c[2])
	{
		c[2] = z;
	}
}

int line_data::read_data(size_t col, vec& ans)
{
	ans = show_data.col(col);
	int temp = static_cast<int>(show_data.col(col)[0]);
	return temp;
}

bool line_data::get_arc_data(const vec& in, vec& c, double& r_l, double& start, double& end)
{
	int flag = static_cast<int>(in[0]);
	if (flag == DXF_ARC)
	{
		c = { in[1], in[2], in[3] };
		r_l = in[4];
		start = in[5];
		end = in[6];
		return true;
	}
	return false;
}

bool line_data::get_line_data(const vec& in, vec& start, vec& end)
{
	int flag = static_cast<int>(in[0]);
	if (flag == DXF_LINE)
	{
		start = { in[1], in[2], in[3] };
		end = { in[4], in[5], in[6] };
		return true;
	}
	return false;
}




