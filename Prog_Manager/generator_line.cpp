#include"pch.h"
#define Prog_Manager_EXPORTS
#include "generator_line.h"
//引导线的生成保存了副本，5.9-15：33
 
#pragma region 计算空间线
void cal_lead_line_duan(double R, double pianxin, double die_ang,
	double start_ang,
	mat33 SYS, vec3 O,
	double delta_dis,
	mat& ans_p)
{
	//1、计算起点
	vec3 start_p = { R, 0.0, 0.0 };
	start_p = SYS * tcRotZ(3, start_ang) * start_p;

	//2、xy平面上偏心圆上切点
	double pianxin_ang = tcDegree(asin(pianxin / R));
	vec3 ls_p_xy = { pianxin, 0.0, 0.0 };
	double ls_deta_ang = 90 - pianxin_ang + start_ang;
	ls_p_xy = tcRotZ(3, ls_deta_ang) * ls_p_xy;
	//过切点与起点垂直于xy的平面法向
	vec3 n_of_plane = ls_p_xy;

	//3、形成蝶形角短向量上的点
	vec3 die_p = tcRotY(3, -die_ang) * -tcX(3) / 1000 + start_p;
	//投影到平面
	die_p = tc_point_prj_to_plane(die_p, start_p, n_of_plane);
	//蝶形角方向
	vec3 v_die = die_p;

	//4、计算终点
	//xy平面上偏心圆上切点、平行z方向向下与端刃线方向交点
	vec3 qie_p = start_p - ls_p_xy;
	double cos_ang = dot(qie_p, v_die) / (norm(qie_p) * norm(v_die));
	double jia_ang = tcDegree(acos(cos_ang));

	double dis_pp = tcDistance(start_p, ls_p_xy);
	double deta_z = dis_pp * tan(tcRadians(jia_ang));

	vec3 end_p = ls_p_xy;
	end_p(2) = -deta_z;


	//5、直线插值
	int p_num = norm(qie_p) / delta_dis;
	int count_p = 0;
	ans_p.reset();
	ans_p.resize(3, 0);
	ans_p.insert_cols(0, p_num);

	vec3 deta = (end_p - start_p) / p_num;

	for (int i = 0; i < p_num; i++)
	{
		vec3 scale_and_trans_mat = start_p + i * deta;
		ans_p.col(i) = scale_and_trans_mat;
		count_p++;
	}
	ans_p.each_col() += O;

	//转置为n*3
	ans_p = ans_p.t();
	//ans_p.swap_cols(0, 2);	//在定义的坐标系下，不转换
}

//生成基本等角锥螺旋线，锥度为0的时候为圆柱螺旋线
//输入：1、形状：半径、锥度角、螺旋角、z轴上螺旋线长度
//输入：2、起点位置：转角：在x轴上的半径长度、相对x轴的旋转角度
//输入：3、放置位置：坐标系 + 位置
//输出：n*3
void cal_lead_line_luoxuan(double R, double zhui_ang, double luo_ang, double z_lenth,
	double start_ang,
	mat33 SYS, vec3 O,
	double delta_dis,
	mat& ans_p)
{
	double A = tan(tcRadians(zhui_ang));
	double B = tan(tcRadians(luo_ang));

	double cur_ang = 0.0;

	vec3 qie0 = {
		A * cos(tcRadians(cur_ang)) - B * sin(tcRadians(cur_ang)),
		A * sin(tcRadians(cur_ang)) + B * cos(tcRadians(cur_ang)),
		1 };

	vec3 p0 = { R, 0.0, 0.0 };
	p0 = tcRotZ(3, start_ang) * p0;
	vec3 p1 = normalise(qie0) * delta_dis + p0;


	int count_p = 0;
	ans_p.reset();
	ans_p.resize(3, 0);
	ans_p.insert_cols(0, 1000);
	ans_p.col(count_p) = p0;
	count_p++;
	ans_p.col(count_p) = p1;
	count_p++;


	while (1)
	{
		if (count_p == ans_p.n_cols)
		{
			ans_p.insert_cols(count_p, 1000);
		}

		vec3 ls_p = p1;
		ls_p(2) = 0.0;
		cur_ang = deltaRotAngle(tcX(3), normalise(ls_p), tcZ(3));

		vec3 cur_qie = { A * cos(tcRadians(cur_ang)) - B * sin(tcRadians(cur_ang)),
						 A * sin(tcRadians(cur_ang)) + B * cos(tcRadians(cur_ang)),
						 1 };

		p0 = p1;
		p1 = normalise(cur_qie) * delta_dis + p0;

		ans_p.col(count_p) = p0;
		count_p++;
		ans_p.col(count_p) = p1;
		count_p++;

		if (p1(2) > z_lenth)
		{
			break;
		}
	}

	ans_p.shed_cols(count_p, ans_p.n_cols - 1);

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//转置为n*3
	ans_p = ans_p.t();
	//ans_p.swap_cols(0, 2);

	//mat anse = ans_p.t();
	//ans_p.save(R"(luoxuanxian_4.30.txt)", raw_ascii);
}

//生成三次基本球头刃线
//输入：1、形状：球头半径长度
//输入：2、起点：相对x轴的旋转角度、水平倾角、螺旋角
//输入：3、终点：相对x轴的旋转角度、水平倾角、螺旋角
//输入：4、放置位置：坐标系 + 位置
//输出：n*3
void cal_lead_line_qiutou(double R,
	double start_alpha, double start_beta, double start_luo,
	double end_alpha, double end_beta, double end_luo,
	mat33 SYS, vec3 O,
	double delta_dis,
	mat& ans_p)
{
	int count = 1 / delta_dis;
	double deta_a = (end_alpha - start_alpha) / count;

	double cur_a = start_alpha;
	double cur_b = start_beta;

	double lsls = pow(5, 0);
	//1、方程系数矩阵
	mat mat_xishu = {
		{pow(start_alpha,3)		 , pow(start_alpha,2)	 , pow(start_alpha,1),		1 },
		{pow(end_alpha,3)		 , pow(end_alpha,2)		 , pow(end_alpha,1)  ,		1 },
		{3 * pow(start_alpha,2)  , 2 * pow(start_alpha,1),  1 ,0 },
		{3 * pow(end_alpha,2)    , 2 * pow(end_alpha,1)  ,  1 ,0 } };


	vec vec_xishu = { start_beta , end_beta ,1.0 / tan(tcRadians(start_luo)), 1.0 / tan(tcRadians(end_luo)) };
	//vec vec_xishu = { start_beta , end_beta , tan(90 - start_luo), tan(90 - end_luo) };

	//2、矩阵逆左乘常数向量得到四个方程系数
	mat ls_ni = mat_xishu.i();
	vec vec_var = ls_ni * vec_xishu;

	//double cal_a = 6 * vec_var(0)* end_alpha + 2* vec_var(1);
	//double cal_a1 = 6 * vec_var(0) * start_alpha + 2 * vec_var(1);

	//3、计算起点
	vec3 p0 = { R, 0.0, 0.0 };
	p0 = tcRotZ(3, start_alpha) * p0;
	vec3 start_p = p0;

	int count_p = 0;
	ans_p.reset();
	ans_p.resize(3, 0);
	ans_p.insert_cols(0, count);
	ans_p.col(count_p) = p0;
	count_p++;

	//5、计算后续点
	while (count_p < count)
	{
		cur_a = cur_a + deta_a;
		cur_b = vec_var(0) * pow(cur_a, 3)
			+ vec_var(1) * pow(cur_a, 2)
			+ vec_var(2) * pow(cur_a, 1)
			+ vec_var(3) * pow(cur_a, 0);

		vec3 p1 = tcRotZ(3, cur_a) * tcRotY(3, -cur_b) * start_p;

		//p0 = p1;

		ans_p.col(count_p) = p1;
		count_p++;

		/*if (count_p * deta_a > end_alpha)
		{
			break;
		}*/
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//转置为n*3
	ans_p = ans_p.t();
	//ans_p.swap_cols(0, 2);

	//mat anse = ans_p.t();
	//ans_p.save(R"(ball_xian_4.30.txt)", raw_ascii);
}

//生成圆角刃线
//输入：1、形状：半径、圆角半径
//输入：2、起点：相对x轴的旋转角度、水平倾角、螺旋角
//输入：3、终点：相对x轴的旋转角度、水平倾角、螺旋角
//输入：4、放置位置：坐标系 + 位置
//输出：n*3
void cal_lead_line_R(double R, double ren_R,
	double start_alpha, double start_beta, double start_luo,
	double end_alpha, double end_beta, double end_luo,
	mat33 SYS, vec3 O,
	double delta_dis,
	mat& ans_p)
{
	int count = 1 / delta_dis;
	mat33 ls_sys = SYS;
	vec3 base_vp = { ren_R, 0.0, 0.0 };
	vec3 base_len_p = { R - ren_R, 0.0, 0.0 };

	//1、求转过角度微分量
	double deta_a = (end_alpha - start_alpha) / count;
	double deta_theta = (end_luo - start_luo) / count;
	double deta_b = deta_a / tan(tcRadians(start_luo));

	//1、方程系数矩阵
	mat mat_xishu = {
		{pow(start_alpha,3)		 , pow(start_alpha,2)	 , pow(start_alpha,1),		1 },
		{pow(end_alpha,3)		 , pow(end_alpha,2)		 , pow(end_alpha,1)  ,		1 },
		{3 * pow(start_alpha,2)  , 2 * pow(start_alpha,1),  1 ,0 },
		{3 * pow(end_alpha,2)    , 2 * pow(end_alpha,1)  ,  1 ,0 } };

	vec vec_xishu = { start_beta , end_beta ,1.0 / tan(tcRadians(start_luo)), 1.0 / tan(tcRadians(end_luo)) };
	//vec vec_xishu = { start_beta , end_beta , tan(90 - start_luo), tan(90 - end_luo) };

	//2、矩阵逆左乘常数向量得到四个方程系数
	mat ls_ni = mat_xishu.i();
	vec vec_var = ls_ni * vec_xishu;


	double cur_a = start_alpha;
	double cur_b = start_beta;

	//2、计算起点
	vec3 p0 = { R, 0.0, 0.0 };
	p0 = tcRotZ(3, start_alpha) * tcRotY(3, -cur_b) * p0;

	int count_p = 0;
	ans_p.reset();
	ans_p.resize(3, 0);
	ans_p.insert_cols(0, count);
	ans_p.col(count_p) = p0;
	count_p++;

	while (count_p < count)
	{
		cur_a = cur_a + deta_a;
		cur_b = vec_var(0) * pow(cur_a, 3)
			+ vec_var(1) * pow(cur_a, 2)
			+ vec_var(2) * pow(cur_a, 1)
			+ vec_var(3) * pow(cur_a, 0);

		//原点刃R球面位置
		vec3 v_p1 = tcRotZ(3, cur_a) * tcRotY(3, -cur_b) * base_vp;
		vec3 ls_len_p = tcRotZ(3, cur_a) * base_len_p;

		vec3 p1 = v_p1 + ls_len_p;

		ans_p.col(count_p) = p1;
		count_p++;
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;
	//转置为n*3
	ans_p = ans_p.t();
	//ans_p.swap_cols(0, 2);

	//mat anse = ans_p.t();
	//ans_p.save(R"(R_xian_4.30.txt)", raw_ascii);
}
#pragma endregion

generator_line::generator_line()
{
	delta_dis = 0.04;
}

generator_line::~generator_line()
{
}

void generator_line::set_delta_dis(double in_dis)
{
	if (in_dis >  0)
	{
		delta_dis = in_dis;
		ans_line.set_delta_dis(in_dis);
	}
	else
	{
		throw - 1;
	}
}

double generator_line::get_delta_dis()
{
	return delta_dis;
}

void generator_line::gen_duan_ren_line(double R, double pianxin, double die_ang, mat33 SYS, vec3 O)
{
	//计算端刃线的空间线
	//1、计算起点
	vec3 start_p = { R, 0.0, 0.0 };

	//2、xy平面上偏心圆上切点
	double pianxin_ang = tcDegree(asin(pianxin / R));
	vec3 ls_p_xy = { pianxin, 0.0, 0.0 };
	double ls_deta_ang = 90 - pianxin_ang;
	ls_p_xy = tcRotZ(3, ls_deta_ang) * ls_p_xy;
	//过切点与起点垂直于xy的平面法向
	vec3 n_of_plane = tcRotZ(3, -ls_deta_ang) * tcX(3);

	//3、形成蝶形角短向量上的点
	vec3 die_p = tcRotY(3, -die_ang) * (- tcX(3) / 100.0) + start_p;
	//投影到平面
	die_p = tc_point_prj_to_plane(die_p, start_p, n_of_plane);
	//蝶形角方向
	vec3 v_die = tcRotY(3, -die_ang) * (-tcX(3));

	//4、计算终点
	//xy平面上偏心圆上切点、平行z方向向下与端刃线方向交点
	vec3 qie_p = normalise( ls_p_xy - start_p) ;
	double cos_ang = dot(qie_p, v_die) / (norm(qie_p) * norm(v_die));
	double jia_ang = tcDegree(acos(cos_ang));
	//偏心距大于固定蝶形角计算得出夹角增大不合理，改为固定值-2.14
	jia_ang = die_ang;

	double dis_pp = tcDistance(start_p, ls_p_xy);
	double deta_z = dis_pp * tan(tcRadians(jia_ang));

	vec3 end_p = ls_p_xy;
	end_p(2) = -deta_z;


	//5、直线插值
	vec3 qie_end = end_p - start_p;
	int p_num = norm(qie_end) / delta_dis;
	
	//6、存放计算点结果
	mat ans_p(3, 0, fill::zeros); //3*n
	

	vec3 deta = qie_end / p_num;

	for (int i = 0; i < p_num; i++)
	{
		vec ls_p = start_p + i * deta;
		ans_p.insert_cols(ans_p.n_cols, ls_p);
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	//ans_p.shed_col(ans_p.n_cols - 1);

	//7、计算结果构造空间线
	ans_line.init_data(ans_p);

	//test
	ans_p = ans_p.t();
	ans_p.save(R"(test_duan-12.8.txt)", raw_ascii);
}

void generator_line::gen_duan_ren_line_R(double R, double ren_R, double pianxin,
	double die_ang, 
	mat33 SYS, vec3 O)
{	//计算端刃线的空间线
	//1、计算起点
	vec3 start_p = { 0.0, 0.0, ren_R };
	vec3 move_t = { R - ren_R, 0.0, -ren_R };
	start_p = tcRotY(3, -die_ang) * start_p + move_t;

	//2、xy平面上偏心圆上切点
	double pianxin_ang = tcDegree(asin(pianxin / R));
	vec3 ls_p_xy = { pianxin, 0.0, 0.0 };
	double ls_deta_ang = 90 - pianxin_ang ;
	ls_p_xy = tcRotZ(3, ls_deta_ang) * ls_p_xy;
	//过切点与起点垂直于xy的平面法向
	vec3 n_of_plane = ls_p_xy;

	//3、形成蝶形角短向量上的点
	vec3 die_p = tcRotY(3, -die_ang) * -tcX(3) / 1000 + start_p;
	//投影到平面
	die_p = tc_point_prj_to_plane(die_p, start_p, n_of_plane);
	//蝶形角方向
	vec3 v_die = die_p;

	//4、计算终点
	//xy平面上偏心圆上切点、平行z方向向下与端刃线方向交点
	vec3 qie_p = start_p - ls_p_xy;
	double cos_ang = dot(qie_p, v_die) / (norm(qie_p) * norm(v_die));
	double jia_ang = tcDegree(acos(cos_ang));

	double dis_pp = tcDistance(start_p, ls_p_xy);
	double deta_z = dis_pp * tan(tcRadians(jia_ang));

	vec3 end_p = ls_p_xy;
	end_p(2) = -deta_z;


	//5、直线插值
	vec3 qie_end = end_p - start_p;
	int p_num = norm(qie_end) / delta_dis;

	//6、存放计算点结果
	mat ans_p(3, p_num, fill::zeros); //3*n

	vec3 deta = qie_end / p_num;

	for (int i = 0; i < p_num; i++)
	{
		ans_p.col(i) = start_p + i * deta;
	}

	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	ans_p.shed_row(ans_p.n_cols - 1);

	//7、计算结果构造空间线
	ans_line.init_data(ans_p);
}

void generator_line::gen_luoxuan_ren_line(double R, double zhui_ang, double luo_ang, double z_lenth, double start_ang, mat33 SYS, vec3 O)
{

	////版本2：不用切向表达式
	//// 锥螺旋增量关系
	////以长度为增量 z+ 

	double A = tan(tcRadians(zhui_ang));
	double B = tan(tcRadians(luo_ang));
	double C = cos(tcRadians(zhui_ang));

	double delta_z = delta_dis ;
	double delta_r = A * delta_z;
	double delta_l =  delta_z / C;  //母线长度增量
	double delta_w = B * delta_l;
	//double delta_w = B * delta_z;	//螺旋角与轴线夹角 8.8 mark

	double cur_R = R;
	double cur_ang = start_ang;
	double cur_len = 0.0;

	vec3 start_p = { R, 0.0, 0.0 };
	double cur_a = 0.0; //初始转角
	double cur_b = zhui_ang;
	start_p = tcRotY(3, -cur_b) * start_p;

	vec3 p_pre = start_p;

	//计算结果存放
	int count_p = 0;
	mat ans_p(3, 0, fill::zeros); //3*n
	ans_p.insert_cols(ans_p.n_cols, p_pre);
	count_p++;

	while (1)
	{
		double ls_R = cur_R + delta_r;
		double delta_ang = tcDegree(atan(delta_w / ls_R)) ; //旋转需要角度值
		//double delta_ang = tcDegree(delta_w / ls_R);
		//double delta_ang = tcDegree(delta_w / ls_R);
		double ls_ang = cur_ang + delta_ang;
		double ls_len = cur_len + delta_z;

		vec3 p_ls = { ls_R ,0.0, ls_len };
		vec3 ls_ans = tcRotZ(3, ls_ang) * p_ls;

		//修整到空间弧长相等 6.12zeng
		double dis_temp = tcDistance(p_pre, ls_ans);
		double ans_xishu = delta_dis * 1.0 / dis_temp;
		//double ans_xishu = 1.0 ; //不修整
		double ans_delta_z = ans_xishu * delta_z;
		double ans_delta_r = ans_xishu * delta_r;
		double ans_delta_ang = ans_xishu * delta_ang;

		cur_R = cur_R + ans_delta_r;
		cur_ang = cur_ang + ans_delta_ang;
		cur_len = cur_len + ans_delta_z;

		vec3 p_ans = { cur_R ,0.0, cur_len };
		p_ans = tcRotZ(3, cur_ang) * p_ans;
		p_pre = p_ans;	//记录上一点

		ans_p.insert_cols(ans_p.n_cols, p_pre);
		count_p++;

		if (ls_ans(2) > z_lenth)
		{
			break;
		}
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	ans_p.shed_cols(count_p - 1,ans_p.n_cols - 1);
	//ans_p.shed_col(count_p - 1);
	//7、计算结果构造空间线
	ans_line.init_data(ans_p);

	//test
	//ans_p = ans_p.t();
	//ans_p.save(R"(new_luoxuan_8.7-0.1.txt)", raw_ascii);
}

void generator_line::gen_luoxuan_ren_line_R(double R, double ren_R, double zhui_ang, double luo_ang, double z_lenth, double start_ang, mat33 SYS, vec3 O)
{
	double A = tan(tcRadians(zhui_ang));
	double B = tan(tcRadians(luo_ang));
	double C = cos(tcRadians(zhui_ang));

	double delta_z = delta_dis;
	double delta_r = A * delta_z;
	double delta_l = delta_z / C;  //母线长度增量
	double delta_w = B * delta_l;
	//double delta_w = B * delta_z;	//螺旋角与轴线夹角 8.8 mark

	double cur_R = R;
	double cur_ang = start_ang;
	double cur_len = 0.0;

	vec3 start_p = { R, 0.0, 0.0 };
	double cur_a = 0.0; //初始转角
	double cur_b = zhui_ang;
	start_p = tcRotY(3, -cur_b) * start_p;

	vec3 p_pre = start_p;

	//计算结果存放
	int count_p = 0;
	mat ans_p(3, 0, fill::zeros); //3*n
	ans_p.insert_cols(ans_p.n_cols, p_pre);
	count_p++;

	while (1)
	{
		double ls_R = cur_R + delta_r;
		double delta_ang = tcDegree(atan(delta_w / ls_R)); //旋转需要角度值
		double ls_ang = cur_ang + delta_ang;
		double ls_len = cur_len + delta_z;

		if (ls_len < ren_R)
		{
			continue;
		}

		vec3 p_ls = { ls_R ,0.0, ls_len };
		vec3 ls_ans = tcRotZ(3, ls_ang) * p_ls;

		//修整到空间弧长相等 6.12zeng
		double dis_temp = tcDistance(p_pre, ls_ans);
		double ans_xishu = delta_dis * 1.0 / dis_temp;
		//double ans_xishu = 1.0 ; //不修整
		double ans_delta_z = ans_xishu * delta_z;
		double ans_delta_r = ans_xishu * delta_r;
		double ans_delta_ang = ans_xishu * delta_ang;

		cur_R = cur_R + ans_delta_r;
		cur_ang = cur_ang + ans_delta_ang;
		cur_len = cur_len + ans_delta_z;

		vec3 p_ans = { cur_R ,0.0, cur_len };
		p_ans = tcRotZ(3, cur_ang) * p_ans;
		p_pre = p_ans;	//记录上一点

		ans_p.insert_cols(ans_p.n_cols, p_pre);
		count_p++;

		if (ls_ans(2) > z_lenth)
		{
			break;
		}
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	ans_p.shed_cols(count_p - 1, ans_p.n_cols - 1);
	//ans_p.shed_col(count_p - 1);
	//7、计算结果构造空间线
	ans_line.init_data(ans_p);
}

void generator_line::gen_qiutou_ren_line(double R,
	double xishu_aotu, double ang_zhui, double end_luo,
	mat33 SYS, vec3 O)
{
//1、倾角一定是从0-90，根据精度确定点的个数
//2、输入的螺旋角结束是0，根据起始螺旋角，设计函数关系得到合理的转角--一定90过顶点
//3、根据点个数将转角微分，转角为自变量，求得倾角，可能不过顶点
// 3.1、转角等增到90，倾角到不了90，可以加一个大于一的系数（也可以直接规整）
//4、螺旋角小于18.5，线会越过顶点

//方案二 //没采用
//最后是求得转角与倾角，根据输入解方程组得到，其关系
//以倾角为自变量，求得转角，可保证刚好到顶点，（转角一定为正值）
//卡尔丹公式或数值方法（牛顿迭代），有重根，迭代不收敛

	//0、计算球头刃线的空间线

	//限定一些角度的输入值
	double start_alpha = 0.0;
	double start_beta = ang_zhui;
	double end_alpha = xishu_aotu * tan(tcRadians(end_luo)) * 90.0 / 2.0;
	//end_alpha = 45.0; //螺旋角线性变化到0，积分出转角，用户输入标准的系数
	double end_beta = 90.0; double ding_luo = 0.001;//结束螺旋角为90才是正确

	double delta_b = 0.1; //角度步长
	double delta_a = delta_b * tan(tcRadians(end_luo));
	int count = 90.0 / delta_b;


	//1、方程系数矩阵
	mat mat_xishu = {
		{pow(start_alpha,3)		 , pow(start_alpha,2)	 , pow(start_alpha,1),		1 },
		{pow(end_alpha,3)		 , pow(end_alpha,2)		 , pow(end_alpha,1)  ,		1 },
		{3 * pow(start_alpha,2)  , 2 * pow(start_alpha,1),  1 ,0 },
		{3 * pow(end_alpha,2)    , 2 * pow(end_alpha,1)  ,  1 ,0 } };
	//螺旋角以母线参考 
	//vec vec_xishu = { start_beta , end_beta ,1.0 / tan(tcRadians(start_luo)), 1.0 / tan(tcRadians(end_luo)) };
	vec vec_xishu = { start_beta , end_beta ,1.0 / tan(tcRadians(end_luo)), ding_luo };

	//2、矩阵逆左乘常数向量得到四个方程系数
	mat ls_ni(4, 4, fill::zeros);
	ls_ni = mat_xishu.i();
	vec vec_var = ls_ni * vec_xishu;

	//3、计算起点
	//double cur_a = start_beta * tan(tcRadians(end_luo)); //初始转角
	double cur_a = 0.0; //初始转角
	double cur_b = ang_zhui;
	double pre_a = cur_a;
	double pre_b = cur_b;

	vec3 start_p = { R, 0.0, 0.0 };
	start_p = tcRotY(3, -cur_b) * start_p;


	//计算结果存放
	int count_p = 0;
	//mat ans_p(3, count + 1, fill::zeros); //3*n
	mat ans_p(3, 0, fill::zeros); //3*n
	ans_p.insert_cols(ans_p.n_cols, start_p);
	count_p++;

	//5、计算后续点
	while (1)
	{
		double cal_cur_a = pre_a + delta_a; //计算转角
		double cal_cur_b = vec_var(0) * pow(cal_cur_a, 3)
			+ vec_var(1) * pow(cal_cur_a, 2)
			+ vec_var(2) * pow(cal_cur_a, 1)
			+ vec_var(3) * pow(cal_cur_a, 0); //理论倾角

		{
			//if (start_luo < 18.5) //修正:等价于插值 --9.8 正确
		//{
		//	double deta_b = (cal_cur_b - pre_b); //倾角增量
		//	int insert_p = (deta_b / delta_a);

		//	double new_deta_a = delta_a / insert_p;
		//	double new_deta_b = deta_b / insert_p;
		//	for (int i = 1; i < insert_p; i++)
		//	{
		//		if (count_p == ans_p.n_cols)
		//		{
		//			ans_p.insert_cols(count_p, 100);
		//		}
		//		double ls_cur_a = pre_a + i * new_deta_a;
		//		double ls_cur_b = pre_b + i * new_deta_b;

		//		if (ls_cur_b > 89.9)
		//		{
		//			break;
		//		}

		//		vec3 p1 = tcRotZ(3, ls_cur_a) * tcRotY(3, -ls_cur_b) * start_p;
		//		ans_p.col(count_p) = p1;
		//		count_p++;
		//	}
		//}
		//else
		//{
		//}
		}
		

		//计算值等于实际值
		cur_a = cal_cur_a;
		cur_b = cal_cur_b;

		if (cur_b > 89.99)
		{
			break;
		}
		vec3 p1 = tcRotZ(3, cur_a) * tcRotY(3, -cur_b) * start_p;

		ans_p.insert_cols(ans_p.n_cols, p1);
		count_p++;

		pre_a = cur_a;
		pre_b = cur_b;
	}

	//6、增加中心点-保证有相位角
	vec3 last_p = ans_p.col(ans_p.n_cols - 1);
	last_p(2) = 0.0;
	last_p = 0.01 * last_p;
	vec3 p0 = { 0.0, 0.0, R };
	p0 = p0 + last_p;
	ans_p.insert_cols(ans_p.n_cols, p0);

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	//ans_p.shed_col(count_p - 1);
	//wen10.12
	//ans_p.shed_cols(count_p - 2, ans_p.n_cols-1);

	//7、计算结果构造空间线
	ans_line.init_data(ans_p);
	//生成的线结果正确没有少点 24.11.20 zy
	//生成时从柱面到球顶，输出球顶到柱面 6.3
	ans_line.fanxiang();

	//test
	//ans_p = ans_p.t();
	//ans_p.save(R"(test_qiu-12.10.txt)", raw_ascii);
}

void generator_line::gen_R_ren_line(double R, double ren_R, 
	double pianxin, double die_ang, double end_luo,
	mat33 SYS, vec3 O)
{
//#pragma region MyRegion
//	//计算圆角刃线的空间线
//	mat33 ls_sys = SYS;
//	vec3 base_vp = { ren_R, 0.0, 0.0 };
//	vec3 base_len_p = { R - ren_R, 0.0, 0.0 };
//
//	//0、求转过角度微分量
//	/*double deta_a = (end_alpha - start_alpha) / count;
//	double deta_theta = (end_luo - start_luo) / count;
//	double deta_b = deta_a / tan(tcRadians(start_luo));*/
//	double deta_a = atan(tcDegree(delta_dis / R));
//	deta_a = 0.05;//3.28 圆角转角很小，计算点过少不能初始化
//	int count = (end_alpha - start_alpha) / deta_a;
//
//	//1、方程系数矩阵
//	mat mat_xishu = {
//		{pow(start_alpha,3)		 , pow(start_alpha,2)	 , pow(start_alpha,1),		1 },
//		{pow(end_alpha,3)		 , pow(end_alpha,2)		 , pow(end_alpha,1)  ,		1 },
//		{3 * pow(start_alpha,2)  , 2 * pow(start_alpha,1),  1 ,0 },
//		{3 * pow(end_alpha,2)    , 2 * pow(end_alpha,1)  ,  1 ,0 } };
//
//	vec vec_xishu = { start_beta , end_beta ,1.0 / tan(tcRadians(start_luo)), 0.001 };
//
//	//2、矩阵逆左乘常数向量得到四个方程系数
//	mat ls_ni = mat_xishu.i();
//	vec vec_var = ls_ni * vec_xishu;
//
//	double cur_a = start_alpha;
//	double cur_b = start_beta;
//
//	//2、计算起点
//	vec3 p0 = { R, 0.0, 0.0 };
//	p0 = tcRotZ(3, start_alpha) * tcRotY(3, -cur_b) * p0;
//
//	//计算结果存放
//	int count_p = 0;
//	mat ans_p(3, 1000, fill::zeros); //3*n
//	ans_p.col(count_p) = p0;
//	count_p++;
//
//	while (count_p < count)
//	{
//		cur_a = cur_a + deta_a;
//		cur_b = vec_var(0) * pow(cur_a, 3)
//			+ vec_var(1) * pow(cur_a, 2)
//			+ vec_var(2) * pow(cur_a, 1)
//			+ vec_var(3) * pow(cur_a, 0);
//
//		//原点刃R球面位置
//		vec3 v_p1 = tcRotZ(3, cur_a) * tcRotY(3, -cur_b) * base_vp;
//		vec3 ls_len_p = tcRotZ(3, cur_a) * base_len_p;
//
//		vec3 p1 = v_p1 + ls_len_p;
//
//		ans_p.col(count_p) = p1;
//		count_p++;
//	}
//
//	ans_p = SYS * ans_p;
//	ans_p.each_col() += O;
//
//	//最后一个点为原点 删除 5.23
//	ans_p.shed_cols(count_p - 1, ans_p.n_cols - 1);
//
//	//7、计算结果构造空间线
//	ans_line.init_data(ans_p);
//#pragma endregion

	//构造gen_rrr_by_hermite所需的输入
	//1、计算起点
	vec3 start_p = { 0.0, 0.0, ren_R };
	vec3 move_t = { R - ren_R, 0.0, -ren_R };
	start_p = tcRotY(3, -die_ang) * start_p + move_t;

	vec3 start_t = tcRotY(3, -die_ang) * tcX(3);

	//2、计算终点
	vec3 end_p = { R, 0.0, -ren_R };
	double ang_zhuan = tcDegree((ren_R * tan(tcRadians(end_luo))) / R);
	end_p = tcRotZ(3, -ang_zhuan) * end_p;
	vec3 end_t = tcRotX(3, -end_luo) * (-tcZ(3));
	
	//
	int num_p = (90.0 + die_ang) / 0.1;
	gen_rrr_by_hermite(start_p, start_t,end_p,end_t,num_p,
		SYS, O);
}

void generator_line::gen_rrr_by_hermite(vec3 start_p, vec3 start_t, vec3 end_p, vec3 end_t, int num_p, mat33 SYS, vec3 O)
{
	mat ans_p(3, num_p, fill::zeros); //3*n

	for (int i = 0; i < num_p; ++i) {
		double t = static_cast<double>(i) / (num_p - 1); // t ∈ [0, 1]
		double t2 = t * t;
		double t3 = t2 * t;

		// Hermite 基函数
		double h00 = 2 * t3 - 3 * t2 + 1;
		double h10 = t3 - 2 * t2 + t;
		double h01 = -2 * t3 + 3 * t2;
		double h11 = t3 - t2;

		// 计算插值点
		vec3 ls_ans_p;
		ls_ans_p(0) = h00 * start_p(0) + h10 * start_t(0) + h01 * end_p(0) + h11 * end_t(0);
		ls_ans_p(1) = h00 * start_p(1) + h10 * start_t(1) + h01 * end_p(1) + h11 * end_t(1);
		ls_ans_p(2) = h00 * start_p(2) + h10 * start_t(2) + h01 * end_p(2) + h11 * end_t(2);

		ans_p.col(i) = ls_ans_p;
	}

	ans_p = SYS * ans_p;
	ans_p.each_col() += O;

	//最后一个点为原点 删除 5.23
	ans_p.shed_cols(num_p - 1, ans_p.n_cols - 1);

	//7、计算结果构造空间线
	ans_line.init_data(ans_p);

	//test
	ans_p = ans_p.t();
	ans_p.save(R"(test_rrr_hermite-3.31.txt)", raw_ascii);
}

void generator_line::correct_qiutouren(mat& ans_ren)
{
	delta_dis;

}

