#include"pch.h"
#define Prog_Manager_EXPORTS
#include "KongJianXian.h"

KongJianXian::KongJianXian()
{
	count_p = 0;
	delta_dis = 0.0;
}

KongJianXian::~KongJianXian()
{
}

void KongJianXian::set_delta_dis(double in_dis)
{
	delta_dis = in_dis;
}

double KongJianXian::get_delta_dis()
{
	return delta_dis;
}


int KongJianXian::count_points()
{
	return count_p;
}

vec3 KongJianXian::point(int i)
{
	return data.submat(i, 0, i, 2).t();
}

vec3 KongJianXian::T(int i)
{
	return data.submat(i, 3, i, 5).t();
}

mat KongJianXian::get_all_p()
{
	return data.submat(0, 0, count_p - 1, 2);
}

mat KongJianXian::get_all_T()
{
	return data.submat(0, 3, count_p - 1, 5);
}

double KongJianXian::get_lenth(int i)
{
	return data.row(i)(6);
}

void KongJianXian::fanxiang()
{
	mat ls_data = this->get_all_p(); //n*3

	ls_data = ls_data.t(); //3*n
	ls_data = fliplr(ls_data);

	this->init_data(ls_data);

	//ls_data = ls_data.t();
	//ls_data.save(R"(fanxiang_5.31.txt)", raw_ascii);
}

void KongJianXian::rotate(mat33 SYS)
{
	mat ls_data = this->get_all_p(); //n*3
	ls_data = ls_data.t();
	ls_data = SYS * ls_data;

	this->init_data(ls_data);
}

void KongJianXian::trans(vec3 O)
{
	mat ls_data = this->get_all_p(); //n*3
	ls_data = ls_data.t();
	ls_data.each_col() += O;

	this->init_data(ls_data);
}

void KongJianXian::cutting(double start, double end)
{
	mat ls_data = this->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	int start_index = p_num * start;
	int end_index = p_num * end;
	//切掉两头
	ls_data.shed_rows(0, start_index);
	ls_data.shed_rows(end_index - start_index, ls_data.n_rows - 1);

	ls_data = ls_data.t();
	this->init_data(ls_data);
}

void KongJianXian::extend_end(double add_dis)
{
	mat ls_data = this->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(p_num - 1);
	vec3 pend2 = ls_data.col(p_num - 2);
	vec3 delta_qie = normalise(pend1 - pend2);

	int add_num = add_dis / delta_dis;
	//wld250603
	//ls_data.insert_cols(p_num - 1, add_num);
	ls_data.insert_cols(p_num, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
		ls_data.col(p_num + i) = ls_p;
	}

	this->init_data(ls_data);
}

void KongJianXian::extend_start(double add_dis)
{
	mat ls_data = this->get_all_p(); //n*3
	int p_num = ls_data.n_rows;
	ls_data = ls_data.t();
	vec3 pend1 = ls_data.col(0);
	vec3 pend2 = ls_data.col(1);

	vec3 delta_qie = normalise(pend1 - pend2);

	int add_num = add_dis / delta_dis;
	//wld250603	
	//ls_data.insert_cols(p_num - 1, add_num);
	ls_data.insert_cols(0, add_num);
	for (int i = 0; i < add_num; i++)
	{
		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
		//wld250603	
		//ls_data.col(p_num + i) = ls_p;
		ls_data.col(add_num - 1 - i) = ls_p;
	}

	this->init_data(ls_data);
}

void KongJianXian::join_a_line(KongJianXian& in_line2)
{
	mat line1_data = get_all_p(); //n*3
	mat line2_data = in_line2.get_all_p();

	line1_data.shed_row(line1_data.n_rows - 1);
	//join_cols() and join_vert(): vertical concatenation
	mat ls_data = join_cols(line1_data, line2_data);

	//test
	//mat ans_p = ls_data;
	//ans_p.save(R"(test_qdm_10.21.1_join.txt)", raw_ascii);

	ls_data = ls_data.t();
	init_data(ls_data);
}

void KongJianXian::init_data(mat& in_points)
{
	count_p = in_points.n_cols;
	data.reset();
	data.resize(7, 0);
	data.insert_cols(0, count_p);

	for (int i = 0; i < count_p - 1; i++)
	{
		vec3 ls_p = in_points.col(i);
		vec3 ls_t = normalise(in_points.col(i + 1) - in_points.col(i));
		vec ls_ans = { ls_p(0),ls_p(1),ls_p(2),
						ls_t(0),ls_t(1),ls_t(2),
						ls_p(2) };
		data.col(i) = ls_ans;
	}
	//最后一点切向等于前一点 ：点的个数必须大于2
	vec3 ls_p = in_points.col(count_p - 1);
	vec3 ls_t = data.submat(3, count_p - 1, 5, count_p - 1);
	vec ls_ans = { ls_p(0),ls_p(1),ls_p(2),
					ls_t(0),ls_t(1),ls_t(2),
					ls_p(2) };
	data.col(count_p - 1) = ls_ans;

	//计算间距
	//data.submat(0, 0, 2, 0).print();

	double delta_dis = tcDistance(data.submat(0, 0, 2, 0), data.submat(0, 1, 2, 1));
	this->set_delta_dis(delta_dis);

	data = data.t(); //转置为n*7
}
