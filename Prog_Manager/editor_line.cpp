#define Prog_Manager_EXPORTS
#include"editor_line.h"

KongJianXian editor_line::fanxiang(KongJianXian* line_ptr)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	ls_data = ls_data.t(); //3*n

	ls_data = fliplr(ls_data);

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::rotate(KongJianXian* line_ptr, mat33 SYS)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	ls_data = ls_data.t();
	ls_data = SYS * ls_data;

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::trans(KongJianXian* line_ptr, vec3 O)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	ls_data = ls_data.t();
	ls_data.each_col() += O;

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::cutting(KongJianXian* line_ptr, double start, double end)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	int start_index = p_num * start;
	int end_index = p_num * end;
	//切掉两头
	ls_data.shed_rows(0, start_index);
	ls_data.shed_rows(end_index - start_index, ls_data.n_rows - 1);

	ls_data = ls_data.t();
	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::extend_end(KongJianXian* line_ptr, double add_dis)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(p_num - 1);
	vec3 pend2 = ls_data.col(p_num - 2);
	vec3 delta_qie = normalise(pend1 - pend2);

	double ls_dis = line_ptr->get_delta_dis();
	int add_num = add_dis / ls_dis;
	ls_data.insert_cols(p_num - 1, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * ls_dis * (i + 1) + pend1;
		ls_data.col(p_num + i) = ls_p;
	}

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::extend_start(KongJianXian* line_ptr, double add_dis)
{
	mat ls_data = line_ptr->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(0);
	vec3 pend2 = ls_data.col(1);
	vec3 delta_qie = normalise(pend1 - pend2);

	double ls_dis = line_ptr->get_delta_dis();
	int add_num = add_dis / ls_dis;
	ls_data.insert_cols(p_num - 1, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * ls_dis * (i + 1) + pend1;
		ls_data.col(p_num + i) = ls_p;
	}

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr->get_delta_dis());
	ls_ans.init_data(ls_data);
	return ls_ans;
}

KongJianXian editor_line::joint_two_line(KongJianXian* line_ptr1, KongJianXian* line_ptr2)
{
	mat ls_data1 = line_ptr1->get_all_p(); //n*3
	mat ls_data2 = line_ptr2->get_all_p(); //n*3
	ls_data1 = ls_data1.t();
	ls_data2 = ls_data2.t();

	int index1 = line_ptr1->count_points();
	int index2 = line_ptr2->count_points();
	vec3 p1 = ls_data1.col(index1 - 1);
	vec3 p2 = ls_data2.col(0);

	mat ans_data(3, index1 + index2, fill::zeros);
	double dis_pp = tcDistance(p1, p2);
	if (dis_pp < line_ptr1->get_delta_dis() * 10)
	{
		//ans_line.data = join_rows(line_ptr1->data, line_ptr2->data);
		//ls_data1.reset();
		ans_data.insert_cols(0, ls_data1);
		ans_data.insert_cols(ans_data.n_cols, ls_data2);
	}
	else
	{
		//throw - 1;
	}

	KongJianXian ls_ans;
	ls_ans.set_delta_dis(line_ptr1->get_delta_dis());
	ls_ans.init_data(ans_data);
	return ls_ans;
}

//Cal_RenXian editor_line::fanxiang(Cal_RenXian* line_ptr)
//{
//	mat ls_data = line_ptr->get_kongjianxian(); //n*3
//	ls_data = ls_data.t(); //3*n
//
//	ls_data = fliplr(ls_data);
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	Cal_RenXian ls_ren;
//	ls_ren.ImportData(ls_line);
//	return ls_ren;
//}

Cal_RenXian editor_line::rotate(Cal_RenXian* line_ptr, mat33 SYS)
{
	mat ls_data = line_ptr->get_kongjianxian(); //n*3
	ls_data = ls_data.t(); //3*n

	ls_data = SYS * ls_data;

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::trans(Cal_RenXian* line_ptr, vec3 O)
{
	mat ls_data = line_ptr->get_kongjianxian(); //n*3
	ls_data = ls_data.t(); //3*n

	ls_data.each_col() += O;

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::cutting(Cal_RenXian* line_ptr, double start, double end)
{
	mat ls_data = line_ptr->get_kongjianxian(); //n*3

	int p_num = ls_data.n_rows;
	int start_index = p_num * start;
	int end_index = p_num * end;
	//切掉两头
	ls_data.shed_rows(0, start_index);
	ls_data.shed_rows(end_index - start_index, ls_data.n_rows - 1);
	ls_data = ls_data.t();

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::extend_end(Cal_RenXian* line_ptr, double add_dis)
{
	mat ls_data = line_ptr->get_kongjianxian(); //n*3

	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(p_num - 1);
	vec3 pend2 = ls_data.col(p_num - 2);
	vec3 delta_qie = normalise(pend1 - pend2);

	double delta_dis = tcDistance(pend1, pend2);
	int add_num = add_dis / delta_dis;
	ls_data.insert_cols(p_num - 1, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
		ls_data.col(p_num + i) = ls_p;
	}

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::extend_start(Cal_RenXian* line_ptr, double add_dis)
{
	mat ls_data = line_ptr->get_kongjianxian(); //n*3

	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(0);
	vec3 pend2 = ls_data.col(1);
	vec3 delta_qie = normalise(pend1 - pend2);

	double delta_dis = tcDistance(pend1, pend2);
	int add_num = add_dis / delta_dis;
	ls_data.insert_cols(p_num - 1, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
		ls_data.col(p_num + i) = ls_p;
	}

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::joint_two_line(Cal_RenXian* line_ptr1, Cal_RenXian* line_ptr2)
{
	mat ls_data1 = line_ptr1->get_kongjianxian(); //n*3
	mat ls_data2 = line_ptr2->get_kongjianxian(); //n*3
	ls_data1 = ls_data1.t();
	ls_data2 = ls_data2.t();

	int index1 = ls_data1.n_cols;
	int index2 = ls_data2.n_cols;
	vec3 p1 = ls_data1.col(index1 - 1);
	vec3 p2 = ls_data2.col(0);


	mat ans_data(3, index1 + index2, fill::zeros);
	double dis_pp = tcDistance(p1, p2);
	double delta_dis = tcDistance(ls_data2.col(0), ls_data2.col(1));

	if (dis_pp < delta_dis * 10)
	{
		ans_data.insert_cols(0, ls_data1);
		ans_data.insert_cols(ans_data.n_cols, ls_data2);
	}
	else
	{
		//throw - 1;
	}

	KongJianXian ls_line;
	ls_line.init_data(ans_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}

Cal_RenXian editor_line::set_pinxin_dis(Cal_RenXian* line_ptr, double in_dis)
{
	//1、根据偏心距计算出，偏置长度的范围，此时球头已经拼接上螺旋线
	mat ls_data = line_ptr->get_kongjianxian(); //n*3
	ls_data = ls_data.t(); //3*n

	double delta_dis = tcDistance(ls_data.col(0), ls_data.col(1));
	int pian_num = delta_dis / in_dis;
	pian_num = pian_num * 5;

	double delta_pain = in_dis / pian_num;

	for (int i = 0; i < pian_num; i++)
	{
		vec3 p = line_ptr->P(i);
		vec3 n_pian = line_ptr->hY(i);
		n_pian = normalise(-n_pian);
		p = p + n_pian * (in_dis - i * delta_pain);
		ls_data.col(i) = p;
	}

	KongJianXian ls_line;
	ls_line.init_data(ls_data);
	Cal_RenXian ls_ren;
	ls_ren.ImportData_by_luoxuancao(ls_line);
	return ls_ren;
}


