#include "pch.h"
#define jiemian_show_EXPORTS
#include "manager_h/xt_glfw_setting.h"
#include "jiemian_show.h"

jiemian_show::jiemian_show()
{
	view = eye(4, 4);

	::gladLoadGL();
	
	list_start = glGenLists(1);
	gj = glGenLists(1);
	list_line = glGenLists(1);
}

jiemian_show::~jiemian_show()
{
	glDeleteLists(list_start, 1);
	glDeleteLists(gj, 1);
}

void jiemian_show::set_2D_OpenGl_show()
{
	{
		// 在开始2D绘制之前禁用光照
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		// 确保使用纯颜色绘制，不受光照影响
		glColor3f(1.0f, 1.0f, 1.0f); // 设置绘制颜色为白色
	
		// 4. 重置矩阵状态
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, -1, 1); // 修正近远平面为常规顺序

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		// 5. 启用2D所需功能
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//6. 保持你的2D设置
	glEnable(GL_RESCALE_NORMAL);
	// 设置平滑着色模式，保证颜色插值平滑
	glShadeModel(GL_SMOOTH);
	// 设置投影矩阵为正交投影
	glMatrixMode(GL_PROJECTION);  // 切换到投影矩阵模式
	glLoadIdentity();             // 将投影矩阵重置为单位矩阵
	glOrtho(-1, 1, -1, 1, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glfwSwapInterval(1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void jiemian_show::draw_gj_2D(mat& val)
{
	{
		glDeleteLists(gj, 1);
		glNewList(gj, GL_COMPILE);
		glBegin(GL_LINE_LOOP);
		for (size_t i = 0; i < val.n_cols; i++)
		{
			//double testx = val.col(i)[0];
			//double testy = val.col(i)[1];
			glVertex2d(val.col(i)[0], val.col(i)[1]);
		}
		glEnd();
		glEndList();
	}
}

void jiemian_show::draw_line(std::vector<mat>& val)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);

	if (val.size() == 0)
	{
		return;
	}
	glNewList(list_start, GL_COMPILE);
	for (size_t i = 0; i < val.size(); i++)
	{
		glBegin(GL_LINE_LOOP);
		for (size_t j = 0; j < val[i].n_cols; j++)
		{
			glVertex2d(val[i].col(j)(0), val[i].col(j)(1));
		}
		glEnd();
	}
	glEndList();

}
void jiemian_show::draw_line(mat& val)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);

	if (val.size() == 0)
	{
		return;
	}
	glNewList(list_start, GL_COMPILE);

	glBegin(GL_LINE_LOOP);
	for (size_t j = 0; j < val.n_cols; j++)
	{
		glVertex2d(val.col(j)(0), val.col(j)(1));
	}
	glEnd();

	glEndList();

}

void jiemian_show::redraw()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glNewList(list_start, GL_COMPILE);
	glEndList();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void jiemian_show::set_L_H(double _L, double _H, double init_xs)
{
	L = _L;
	H = _H;
	view = eye(4, 4);
	view(0, 0) = (H / L) * init_xs;
	view(1, 1) = init_xs;
	init = init_xs;
}

mat44 jiemian_show::get_Ctrl_view(vec2 point_1, vec2 point_2, double& ans_d_fangda_xishu)
{
	mat44 ls = eye(4, 4);

	mat44 move = eye(4, 4);

	//缩放系数
	double xishu = 1;

	vec2 dt = point_1 - point_2;
	if (abs(dt(0)) > abs(dt(1)))
	{
		xishu = L / abs(dt(0));
	}
	else
	{
		xishu = H / abs(dt(1));
	}
	ls(0, 0) = xishu;
	ls(1, 1) = xishu;

	ans_d_fangda_xishu = xishu;

	vec2 zhongdian = (point_1 + point_2) / 2;
	//(2 / H)的2与glOrtho(-1, 1, -1, 1, 100, -100);有关
	move(0, 3) = -zhongdian(0) * (H / L) * (2 / H);
	move(1, 3) = -zhongdian(1) * (2 / H);

	view = ls * move * view;
	return view;
}


//mat44 jiemian_show::get_Ctrl_view(vec2 point, double xishu)
//{
//	mat44 ls = eye(4, 4);
//
//	ls(0, 0) = xishu;
//	ls(1, 1) = xishu;
//
//	ls(0, 3) = (1 - xishu) * point(0);
//	ls(1, 3) = (1 - xishu) * point(1);
//
//	return ls;
//}

mat44 jiemian_show::reset_view()
{
	// 计算视口矩阵的逆矩阵来复位视图
	
	view = eye(4, 4);
	view(0, 0) = (H / L) * init;
	view(1, 1) = init;
	scale_mat_before = view;
	return view;
}

void jiemian_show::Calls()
{
	glCallList(list_start);
	glCallList(gj);
	glCallList(list_line);
}


