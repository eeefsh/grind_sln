#define Prog_Manager_EXPORTS
#include"Miller_XiDao.h"

Miller_D_ZQ::Miller_D_ZQ()
{
	tool_type = 0;
}

Miller_D_ZQ::~Miller_D_ZQ()
{
}

Miller_D_ZQ::Miller_D_ZQ(int in_name)
{
	name = in_name;
}

int Miller_D_ZQ::Save()
{
	//1、确定工序存储的位置队列
	int ls_gx_pos[100] = {};
	int ls_gx_zhixing[100] = {};
	for (int i = 0; i < v_data.size(); i++)
	{
		int cur_pos = v_data[i]->Save();
		ls_gx_pos[i] = cur_pos;
		ls_gx_zhixing[i] = v_gx_order[i];
	}
	//2、确定参数存储的位置
	int can_pos = storage_tool->write_a_row_data(1, (char*)&canshu_gg, sizeof(canshu_gg));

	//3、构造一条刀具对象数据
	//3.1 写时间和类型文件--先于对象前写入
	time_updata cur_time;
	storage_tool->write_a_row_data(16, (char*)&cur_time, sizeof(cur_time));
	storage_tool->write_a_row_data(17, (char*)&tool_type, sizeof(tool_type));

	//构造一条刀具对象数据
	tool_obj_data ls_row_data(tool_type, name, v_data.size(), ls_gx_pos, ls_gx_zhixing);
	//3.2管理写文件被打开两次，位置被后移--加判断标志位0，即加对象时更新最大存放位置
	int tool_pos = storage_tool->write_a_row_data(0, (char*)&ls_row_data, sizeof(ls_row_data));

	//4、往刀具计数文件写入一条
	storage_tool->add_tool_count(1);

	return tool_pos;
}


void Miller_D_ZQ::Load(int in_pos)
{
	//读出一条刀具对象数据
	tool_obj_data ls_row_data;
	storage_tool->read_a_row_data(0, in_pos, (char*)&ls_row_data, sizeof(ls_row_data));
	//恢复名字
	name = ls_row_data.name;

	//恢复公共参数
	//int can_pos = ls_row_data.data_pos;  //参数位置等于刀具对象位置 7.4 ???
	storage_tool->read_a_row_data(1, in_pos, (char*)&canshu_gg, sizeof(canshu_gg));
	XingCan_Tool_Base* ls_xc = new XingCan_Tool_Base(0);
	self_xingcan = ls_xc;
	set_canshu(canshu_gg);

	//2.1 当前刀的两个容器恢复
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		v_gx_pos.push_back(ls_row_data.gx_pos[i]);
		v_gx_order.push_back(ls_row_data.gx_zhixing[i]);
	}

	//恢复工序--恢复执行列表对应存储位置--10.17
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		int cur_zhixing = ls_row_data.gx_zhixing[i];
		int cur_gx_pos = ls_row_data.gx_pos[cur_zhixing];

		//读出一条gx对象数据
		gx_obj_data ls_row_data_gx;
		storage_tool->read_a_row_data(4, cur_gx_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));

		//根据工序类型new一个工序
		Miller_GX_Base* ls_gx = gen_gx(ls_row_data_gx.type);
		ls_gx->set_self_dao(this);

		XingCan_Miller_GX* ls_xc = new XingCan_Miller_GX(ls_row_data_gx.type);
		ls_gx->self_xingcan = ls_xc;
		ls_gx->Load(cur_gx_pos);

		ls_gx->slz_num = ls_row_data_gx.sl_num;
		ls_gx->in_or_out = ls_row_data_gx.in_or_out;
		ls_gx->jingeilv = ls_row_data_gx.jingeilv;

		//工序基类数据更新-选择刃和角度-11.6
		for (int i = 0; i < 6; i++)
		{
			ls_gx->A_before_ren[i] = ls_row_data_gx.A_before_ren[i];
			ls_gx->sel_A_before_ren[i] = ls_row_data_gx.sel_A_before_ren[i];
		}
		Point_by_5axis ls_anquan_p;
		storage_tool->read_a_row_data(20, cur_gx_pos, (char*)&ls_anquan_p, sizeof(ls_anquan_p));
		ls_gx->anquandian = ls_anquan_p;

		//CanShu_shalun_cal_DL ls_sl_drfl;

		//ls_gx->shalun_canshu = 

		v_data.push_back(ls_gx);
	}

}

void Miller_D_ZQ::get_renxian_of_qiu(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_qiu;
}

void Miller_D_ZQ::get_renxian_of_luo(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo;
}

void Miller_D_ZQ::get_renxian_of_qiu_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_qiu_cao;
}

void Miller_D_ZQ::get_renxian_of_luo_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo_cao;
}

int Miller_D_ZQ::get_renxian_of_qiu_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_qiu.get_p_num();
}

int Miller_D_ZQ::get_renxian_of_luo_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_luo.get_p_num();
}

void Miller_D_ZQ::get_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_1;
}

void Miller_D_ZQ::get_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_2;
}

void Miller_D_ZQ::get_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_3;
}

void Miller_D_ZQ::get_renxian_of_hdm1(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	Cal_RenXian ren_hdm1;
	get_renxian_of_qiu(in_ren_pos_num, ren_hdm1);
	Cal_RenXian ren_hdm2;
	get_renxian_of_luo(in_ren_pos_num, ren_hdm2);

	//拼接刃线的点数据，线1去除最后一个，因为两线拼接有重点
	ren_hdm1.Data_Of_Points.shed_row(ren_hdm1.Data_Of_Points.n_rows - 1);
	ren_hdm1.Data_Of_Points = join_cols(ren_hdm1.Data_Of_Points, ren_hdm2.Data_Of_Points);
	ren_hdm1.n_P = ren_hdm1.n_P + ren_hdm2.n_P;
	ren_hdm1.Max_No_P = ren_hdm1.Max_No_P + ren_hdm2.Max_No_P;

	ans_renxian = ren_hdm1;
}

void Miller_D_ZQ::get_djjx_p_sys(int in_ren_pos_num, mat& ans_p, vector<mat33>& ans_sys)
{
	//ans_p = v_base_Ren_data[in_ren_pos_num].base_p_djjx;
	//ans_sys = v_base_Ren_data[in_ren_pos_num].base_sys_djjx;
}

void Miller_D_ZQ::set_canshu_gg(CanShu_ZQ_GongGong& in_ptr)
{
	canshu_gg = in_ptr;
}


//void Miller_D_ZQ::cal_base_struct()
//{
//	cal_base_kongjianxian();
//	cal_base_renxian();
//	cal_base_hdm123();
//}

void Miller_D_ZQ::cal_base_Ren_data()
{
	v_base_Ren_data.clear();
	//生成不同的刃放到容器
	for (int i = 0; i < canshu_gg.ren_count; i++)
	{
		Ren_data_D_ZQ cur_ren_data;
#pragma region 计算刃线
		double pos_ang = canshu_gg.v_no_dengfen_angle[i];
		double pianxin = canshu_gg.v_pianxin_dis[i];
		double center_dis = canshu_gg.v_center_dis[i];

		generator_line ls_gen_line;
		ls_gen_line.set_delta_dis(delta_dis_ren);

		mat sys_rotate = tcRotZ(3, pos_ang); //旋转位置
		vec pos = { 0.0, 0.0, 0.0 };
		ls_gen_line.gen_qiutou_ren_line(canshu_gg.D_qiu / 2.0,
			canshu_gg.ang_start_zhuan, canshu_gg.ang_start_qing, canshu_gg.ang_start_luo,
			canshu_gg.ang_end_zhuan, canshu_gg.ang_end_qing, canshu_gg.ang_end_luo,
			tcRotX(3, 180), pos);

		ls_gen_line.rotate(sys_rotate);
		//球头刃线
		cur_ren_data.base_rx_qiu.ImportData_by_qiutou(ls_gen_line.ans_line);
		cur_ren_data.base_rx_qiu.set_pinxin_dis(pianxin);

		//从刃线起点逐个累积距离，统计个数所占百分比12.28
		double percent = cur_ren_data.base_rx_qiu.cal_cut_dis_percent_in_end(center_dis, cur_ren_data.base_rx_qiu.get_kongjianxian());

		//已经转tcRotX(3, 180)，表示尾在中心
		cur_ren_data.base_rx_qiu.cutting_qiutou(0, 1 - percent);//切掉中心距离
		cur_ren_data.base_rx_qiu.fanxiang();

		//test
		/*mat test_hdm = cur_ren_data.base_rx_qiu.get_kongjianxian();
		test_hdm.save(R"(test_luo-11.25.txt)", raw_ascii);*/

		//螺旋刃线
		ls_gen_line.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			canshu_gg.ang_zhui, canshu_gg.ang_luoxuan,
			canshu_gg.len_ren, 0.0,
			sys_rotate, pos);
		cur_ren_data.base_rx_luo.ImportData_by_luoxuancao(ls_gen_line.ans_line);

		//test
		/*mat test_hdm = cur_ren_data.base_rx_luo.get_kongjianxian();
		test_hdm.save(R"(test_luo-12.3.txt)", raw_ascii);*/

		//螺旋槽-空间线延长至刀尖
		generator_line ls_gen_line2;
		ls_gen_line2.set_delta_dis(delta_dis_ren);
		//0锥角反向延长-2.21
		ls_gen_line2.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			0.0, canshu_gg.ang_luoxuan,
			1.2 * canshu_gg.D_qiu / 2.0, 0.0,
			tcRotX(3, 180), pos);
		ls_gen_line2.rotate(sys_rotate);  //先转x-180换到z的副方向，在转z对应角度
		ls_gen_line2.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
		ls_gen_line2.join_a_line(ls_gen_line.ans_line);

		cur_ren_data.base_rx_luo_cao.ImportData_by_luoxuancao(ls_gen_line2.ans_line);

		//test
	/*	mat test_hdm = cur_ren_data.base_rx_luo_cao.get_kongjianxian();
		test_hdm.save(R"(test_luo-12.24.txt)", raw_ascii);*/

#pragma endregion

		//计算后刀面
		cur_ren_data.cal_base_hdm123(canshu_gg); //计算用的刃线已经在旋转后的位置

		//计算刀尖间隙
		//cur_ren_data.cal_base_djjx(canshu_gg, pos_ang);//工件坐标系中旋转对应位置

		//test
		//mat test_hdm = cur_ren_data.base_rx_djjx.get_kongjianxian();
		//test_hdm.save(R"(test_djjx-11.25.txt)", raw_ascii);

		v_base_Ren_data.push_back(cur_ren_data);
	}
}

//void Miller_D_ZQ::cal_base_kongjianxian()
//{
//	//1、用线生成器，生成锥度球头的基本空间线
//	//空间线的参考为Z指向刀具前端，X为圆周参考
//	//刀具的参考为Z指向刀具后端，X为圆周参考
//	generator_line ls_gen_line;
//	mat SYS = tcRotX(3, 0.0);  
//	vec pos = { 0.0, 0.0, 0.0 };
//	ls_gen_line.gen_qiutou_ren_line(canshu_gg.D_qiu /2.0,
//		canshu_gg.ang_start_zhuan, canshu_gg.ang_start_qing, canshu_gg.ang_start_luo,
//		canshu_gg.ang_end_zhuan, canshu_gg.ang_end_qing, canshu_gg.ang_end_luo,
//		SYS, pos);
//
//	//wen10.12
//	//vec3 point0 = ls_gen_line.ans_line.point(0);
//	//vec3 point01 = ls_gen_line.ans_line.point(ls_gen_line.ans_line.count_points()-1);
//	//vec3 point02 = ls_gen_line.ans_line.point(100);
//
//	ls_gen_line.fanxiang(); //不反向，从螺旋起点到刀尖-10.10
//	ls_gen_line.rotate(tcRotX(3, 180) * SYS);
//
//	//test 8.28 将空间线变换到与仿真显示相同 vec trans = { 90.0, 0.0, 0.0, 0.0, 100.0 - 33.838, 0.0 };
//	//ls_gen_line.rotate(tcRotX(3, 90) * SYS);
//	//ls_gen_line.trans({0.0, 100.0 - 33.838, 0.0});
//
//	base_kjx_qiu = ls_gen_line.ans_line;
//	//wen10.12
//	//vec3 point1 = base_kjx_qiu.point(0);
//	//vec3 point11 = base_kjx_qiu.point(base_kjx_qiu.count_points() - 1);
//	//vec3 point12 = base_kjx_qiu.point(100);
//
//	//螺旋空间线
//	ls_gen_line.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
//		canshu_gg.ang_zhui, canshu_gg.ang_luoxuan,
//		canshu_gg.len_ren, 0.0,
//		SYS, pos); 
//
//	base_kjx_luo = ls_gen_line.ans_line;
//
//	//螺旋槽-空间线延长至刀尖
//	generator_line ls_gen_line2;
//	ls_gen_line2.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
//		canshu_gg.ang_zhui, canshu_gg.ang_luoxuan,
//		canshu_gg.D_qiu / 2.0, 0.0,
//		SYS, pos);
//
//	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
//	ls_gen_line2.rotate(tcRotX(3, 180) * SYS);
//	ls_gen_line2.fanxiang();
//	ls_gen_line2.join_a_line(ls_gen_line.ans_line);
//
//	base_kjx_luo_cao = ls_gen_line2.ans_line;
//
//}
//
//void Miller_D_ZQ::cal_base_renxian()
//{
//	//test 不磨球头部分
//	base_rx_qiu.ImportData_by_qiutou(base_kjx_qiu);
//
//	base_rx_luo.ImportData_by_luoxuancao(base_kjx_luo);
//
//	base_rx_luo_cao.ImportData_by_luoxuancao(base_kjx_luo_cao);
//}
//
//void Miller_D_ZQ::cal_base_hdm123()
//{
//	//后刀面坐标系z轴向下
////#pragma region 后刀面1
////	   //用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X, 
////	int p_num1 = base_rx_qiu.get_p_num();
////	int p_num2 = base_rx_luo.get_p_num();
////	base_hdm_1.resize(12, 0);
////	base_hdm_1.insert_cols(0, p_num1 + p_num2);
////	//qiutou部分
////	double delta_ang_d = (canshu_gg.hdm_1_d_mid - canshu_gg.hdm_1_d_qiu) / (1.0 * p_num1); //被提到公共参数 8.12 mark
////	double delta_ang_a = (canshu_gg.hdm_1_a_mid - canshu_gg.hdm_1_a_qiu) / (1.0 * p_num1);
////	for (int i = 0; i < p_num1; i++)
////	{
////		double ls_d = canshu_gg.hdm_1_d_qiu + i * delta_ang_d; //从顶为0-10
////		double ls_a = canshu_gg.hdm_1_a_qiu + i * delta_ang_d; //从顶为3-0
////
////		mat33 test_hsys = base_rx_qiu.hSYS(i);
////
////		vec3 G_Z_HDM = normalise(-base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
////
////		vec3 dir_a_f = dot(G_Z_HDM, tcZ(3)) * sin(tcRadians(ls_a)) * tcZ(3);
////		vec3 dir_r = { -base_rx_qiu.P(i)(0), -base_rx_qiu.P(i)(1) ,0 };
////		dir_r = normalise(dir_r);
////		vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * dir_r;
////
////		vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴
////
////		vec3 G_X_HDM = normalise(-base_rx_qiu.hSYS(i).col(0));  //x轴
////
////		vec3 ls_p = base_rx_qiu.P(i);
////
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
////			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
////			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
////		base_hdm_1.col(i) = ans;
////	}
////
////
////	//点的法向：刃线横坐标系系右乘绕x旋转 后角)，取y向量
////	//螺旋部分
////	for (int i = 0; i < p_num2; i++)
////	{
////		vec3 ls_p = base_rx_luo.P(i);
////		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, canshu_gg.hdm_1_d_luo);
////		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////		   -G_SYS_HDM.col(0)(0), -G_SYS_HDM.col(0)(1), -G_SYS_HDM.col(0)(2),
////		    G_SYS_HDM.col(1)(0),  G_SYS_HDM.col(1)(1),  G_SYS_HDM.col(1)(2),
////		   -G_SYS_HDM.col(2)(0), -G_SYS_HDM.col(2)(1), -G_SYS_HDM.col(2)(2)};
////		base_hdm_1.col(i + p_num1) = ans;
////	}
////	//后刀面点计算正确，8.21检查
////	//mat test_hdm = data_lead_face.hdm_1.submat(0, 0, 2, p_num1 + p_num2 - 1);
////	//test_hdm = test_hdm.t();
////	//test_hdm.save(R"(test_hdm-8.23.txt)", raw_ascii);
////#pragma endregion
////
////#pragma region 后刀面2
////
////	base_hdm_2.resize(12, 0);
////	base_hdm_2.insert_cols(0, p_num1 + p_num2);
////	//qiutou部分
////	delta_ang_d = (canshu_gg.ang_2_d_mid - canshu_gg.ang_2_d_qiu)/ (1.0 * p_num1); //被提到公共参数 8.12 mark
////	delta_ang_a = (canshu_gg.ang_2_a_mid - canshu_gg.ang_2_a_qiu)/ (1.0 * p_num1);
////	for (int i = 0; i < p_num1; i++)
////	{
////		double ls_d = canshu_gg.ang_2_d_qiu + i * delta_ang_d; //从顶为0-10
////		double ls_a = canshu_gg.ang_2_a_qiu + i * delta_ang_d; //从顶为3-0
////
////		vec3 G_Z_HDM = normalise(base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
////
////		vec3 dir_a_f = dot(G_Z_HDM, tcZ(3)) * sin(tcRadians(ls_a)) * tcZ(3);
////		vec3 dir_r = { -base_rx_qiu.P(i)(0), -base_rx_qiu.P(i)(1) ,0 };
////		dir_r = normalise(dir_r);
////		vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * dir_r;
////
////		vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴
////
////		vec3 G_X_HDM = normalise(cross(G_Z_HDM, G_Y_HDM));
////
////		vec3 ls_p = base_rx_qiu.P(i);
////		//往y轴偏移后刀面1的宽度
////		ls_p = ls_p + canshu_gg.hdm_1_width * normalise(G_Y_HDM);
////
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
////			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
////			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
////		base_hdm_2.col(i) = ans;
////	}
////
////	//点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
////	//螺旋槽部分
////	for (int i = 0; i < p_num2; i++)
////	{
////		vec3 ls_p = base_rx_luo.P(i);
////		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, canshu_gg.ang_2_d_luo);
////		//往y轴偏移后刀面1的宽度
////		ls_p = ls_p + canshu_gg.hdm_1_width * normalise(G_SYS_HDM.col(1));
////
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////	   -G_SYS_HDM.col(0)(0), -G_SYS_HDM.col(0)(1), -G_SYS_HDM.col(0)(2),
////		G_SYS_HDM.col(1)(0),  G_SYS_HDM.col(1)(1),  G_SYS_HDM.col(1)(2),
////	   -G_SYS_HDM.col(2)(0), -G_SYS_HDM.col(2)(1), -G_SYS_HDM.col(2)(2) };
////		base_hdm_2.col(i + p_num1) = ans;
////	}
////#pragma endregion
////
////#pragma region 后刀面3
////
////	base_hdm_3.resize(12, 0);
////	base_hdm_3.insert_cols(0, p_num1 + p_num2);
////	//qiutou部分
////	delta_ang_d = (canshu_gg.ang_3_d_mid - canshu_gg.ang_3_d_qiu) / (1.0 * p_num1); //被提到公共参数 8.12 mark
////	delta_ang_a = (canshu_gg.ang_3_a_mid - canshu_gg.ang_3_a_qiu) / (1.0 * p_num1);
////	for (int i = 0; i < p_num1; i++)
////	{
////		double ls_d = canshu_gg.ang_3_d_qiu + i * delta_ang_d; //从顶为0-10
////		double ls_a = canshu_gg.ang_3_a_qiu + i * delta_ang_d; //从顶为3-0
////
////		vec3 G_Z_HDM = normalise(base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
////
////		vec3 dir_a_f = dot(G_Z_HDM, tcZ(3)) * sin(tcRadians(ls_a)) * tcZ(3);
////		vec3 dir_r = { -base_rx_qiu.P(i)(0), -base_rx_qiu.P(i)(1) ,0 };
////		dir_r = normalise(dir_r);
////		vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * dir_r;
////
////		vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴
////
////		vec3 G_X_HDM = normalise(cross(G_Z_HDM, G_Y_HDM));
////
////		vec3 ls_p = base_rx_qiu.P(i);
////		//往y轴偏移后刀面2的宽度
////		ls_p = ls_p + canshu_gg.hdm_2_width * normalise(G_Y_HDM);
////
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
////			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
////			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
////		base_hdm_3.col(i) = ans;
////	}
////
////	//点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
////	//螺旋槽部分
////	for (int i = 0; i < p_num2; i++)
////	{
////		vec3 ls_p = base_rx_luo.P(i);
////		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3,canshu_gg.ang_3_d_luo);
////		//往y轴偏移后刀面2的宽度
////		ls_p = ls_p + canshu_gg.hdm_2_width * normalise(G_SYS_HDM.col(1));
////
////		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
////		   -G_SYS_HDM.col(0)(0), -G_SYS_HDM.col(0)(1), -G_SYS_HDM.col(0)(2),
////			G_SYS_HDM.col(1)(0),  G_SYS_HDM.col(1)(1),  G_SYS_HDM.col(1)(2),
////		   -G_SYS_HDM.col(2)(0), -G_SYS_HDM.col(2)(1), -G_SYS_HDM.col(2)(2) };
////		base_hdm_3.col(i + p_num1) = ans;
////	}
////#pragma endregion
//}

bool Miller_D_ZQ::add_gx_by_end(XingCan_Miller_GX& in_ptr, int in_name)
{
	//1、根据参数类型 new一个对应工序 0-7
	//2、工序所需操作流程
	//3、放入工序列表
	int cur_type = in_ptr.get_gx_type();
	Miller_GX_Base* cur_gx = nullptr;
	switch (cur_type)
	{
	case 0:
		cur_gx = new Miller_GX_ZQ_QDM(this);
		break;
	case 1:
		cur_gx = new Miller_GX_ZQ_LXC(this);
		break;
	case 2:
		cur_gx = new Miller_GX_ZQ_HDM_1(this);
		break;
	case 3:
		cur_gx = new Miller_GX_ZQ_HDM_2(this);
		break;
	case 4:
		cur_gx = new Miller_GX_ZQ_HDM_3(this);
		break;
	case 5:
		cur_gx = new Miller_GX_ZQ_DaoTiJianXi(this);
		break;
	case 6:
		cur_gx = new Miller_GX_ZQ_DaoJianJianXi(this);
		break;
	case 7:
		cur_gx = new Miller_GX_ZQ_DaoJianJianXi(this);
		break;
	default:
		return false;
	}

	cur_gx->set_name(in_name);
	cur_gx->set_canshu(in_ptr);
	cur_gx->Save();
	v_data.push_back(cur_gx);

	//4、更新执行顺序列表
	v_gx_order.push_back(v_data.size() - 1); //0为第一执行
	return false;
}


double Miller_D_ZQ::get_gg_canshu_start_zhuan()
{
	return canshu_gg.ang_start_zhuan;
}

double Miller_D_ZQ::get_gg_canshu_start_qing()
{
	return canshu_gg.ang_start_qing;
}

double Miller_D_ZQ::get_gg_canshu_strat_luo()
{
	return canshu_gg.ang_start_luo;
}

double Miller_D_ZQ::get_gg_canshu_end_zhuan()
{
	return canshu_gg.ang_end_zhuan;
}

double Miller_D_ZQ::get_gg_canshu_end_qing()
{
	return canshu_gg.ang_end_qing;
}

double Miller_D_ZQ::get_gg_canshu_end_luo()
{
	return canshu_gg.ang_end_luo;
}

double Miller_D_ZQ::get_gg_canshu_D_qiu()
{
	return canshu_gg.D_qiu;
}

double Miller_D_ZQ::get_gg_canshu_Zhui()
{
	return canshu_gg.ang_zhui;
}

double Miller_D_ZQ::get_gg_canshu_luo()
{
	return canshu_gg.ang_luoxuan;
}

double Miller_D_ZQ::get_gg_canshu_bing()
{
	return canshu_gg.D_bing;
}

void Miller_D_ZQ::get_dengfen_ang(vector<double>& in_v_ang)
{
	for (int i = 0; i < 6; i++)
	{
		in_v_ang.push_back(canshu_gg.v_no_dengfen_angle[i]);
	}
}

double Miller_D_ZQ::get_gg_canshu_len_all()
{
	return canshu_gg.len_all;
}

double Miller_D_ZQ::get_gg_canshu_len_ren()
{
	return canshu_gg.len_ren;
}

double Miller_D_ZQ::get_gg_canshu_D_bing()
{
	return canshu_gg.D_bing;
}

double Miller_D_ZQ::get_gg_canshu_hdm_1_width()
{
	return canshu_gg.hdm_1_width;
}

double Miller_D_ZQ::get_gg_canshu_hdm_1_d_qiu()
{
	return canshu_gg.hdm_1_d_qiu;
}

double Miller_D_ZQ::get_gg_canshu_hdm_1_a_qiu()
{
	return canshu_gg.hdm_1_a_qiu;
}



double Miller_D_ZQ::get_gg_canshu_hdm_1_d_luo()
{
	return canshu_gg.hdm_1_d_luo;
}

double Miller_D_ZQ::get_gg_canshu_hdm_1_a_luo()
{
	return canshu_gg.hdm_1_a_luo;
}

double Miller_D_ZQ::get_gg_canshu_hdm_2_width()
{
	return canshu_gg.hdm_2_width;
}

double Miller_D_ZQ::get_gg_canshu_hdm_2_d_qiu()
{
	return canshu_gg.hdm_2_d_qiu;
}

double Miller_D_ZQ::get_gg_canshu_hdm_2_a_qiu()
{
	return canshu_gg.hdm_2_a_qiu;
}

double Miller_D_ZQ::get_gg_canshu_hdm_2_d_luo()
{
	return canshu_gg.hdm_2_d_luo;
}

double Miller_D_ZQ::get_gg_canshu_hdm_2_a_luo()
{
	return canshu_gg.hdm_2_a_luo;
}

double Miller_D_ZQ::get_gg_canshu_hdm_3_width()
{
	return canshu_gg.hdm_3_width;
}

double Miller_D_ZQ::get_gg_canshu_hdm_3_d_qiu()
{
	return canshu_gg.hdm_3_d_qiu;
}

double Miller_D_ZQ::get_gg_canshu_hdm_3_a_qiu()
{
	return canshu_gg.hdm_3_a_qiu;
}

double Miller_D_ZQ::get_gg_canshu_hdm_3_d_luo()
{
	return canshu_gg.hdm_3_d_luo;
}

double Miller_D_ZQ::get_gg_canshu_hdm_3_a_luo()
{
	return canshu_gg.hdm_3_d_luo;
}

void Miller_D_ZQ::get_canshu(CanShu_ZQ_GongGong& ans)
{
	ans = canshu_gg;
}

void Miller_D_ZQ::set_canshu(CanShu_ZQ_GongGong& ptr)
{
	self_xingcan->set_CanShu_ZQ_GG(ptr);
	//重新计算基本结构

}

void Miller_D_ZQ::set_canshu(XingCan_Tool_Base& ptr)
{
	canshu_gg = *(ptr.can_zq_gg); //改为public
	self_xingcan = &ptr;
}

void Miller_D_Base::get_renxian_of_qiu(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	//派生实现
}

void Miller_D_Base::get_renxian_of_luo(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_renxian_of_qiu_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_renxian_of_luo_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

int Miller_D_Base::get_renxian_of_qiu_count_p(int in_ren_pos_num)
{
	return -1;
}

int Miller_D_Base::get_renxian_of_luo_count_p(int in_ren_pos_num)
{
	return -1;
}


void Miller_D_Base::get_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_renxian_of_hdm1(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_djjx_p_sys(int in_ren_pos_num, mat& ans_p, vector<mat33>& ans_sys)
{
}

void Miller_D_Base::get_hen_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_hen_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_hen_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_luo_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_luo_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_luo_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
}

void Miller_D_Base::get_renxian_of_hen(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_renxian_of_hen_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_renxian_of_rrr(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}

void Miller_D_Base::get_qdm_of_cx(int in_ren_pos_num, mat& data_qdm)
{
}

void Miller_D_Base::get_renxian_of_cx_hdm(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
}



void Miller_D_Base::del_a_xx_by_order(int del_n_order)
{
}

void Miller_D_Base::get_self_dxf_pos(vector<int>& v_pos)
{
}

void Miller_D_Base::set_a_xx_storage_pos(int cur_tool_xx_count, int cur_stroage_pos)
{
}

int Miller_D_Base::get_gg_canshu_xingxian_count()
{
	return 0;
}

int Miller_D_Base::get_gg_canshu_houjiao_count()
{
	return 0;
}

int Miller_D_Base::get_gg_canshu_luoxuan_count()
{
	return 0.0;
}

void Miller_D_Base::set_a_ang_pos_xx(int ren_pos, int xx_oder)
{
}

void Miller_D_Base::get_cx_luoxuancanshu_by_sel(int in_sel_index, int& ans_cao_type, double& in_ang_zhuan, double& in_ang_qing, double& in_dis_pian, double& in_ang_luo, double& in_daocheng)
{
}

void Miller_D_Base::get_cx_caiyang_canshu(int& ans_cai_type, double& ans_cai_len, double& ans_cai_ang)
{
}

Miller_D_Base::Miller_D_Base()
{
	v_data.clear();
}

Miller_D_Base::~Miller_D_Base()
{
}

Miller_D_Base::Miller_D_Base(int in_name)
{
	name = in_name;
}

void Miller_D_Base::set_storage_ptr(Storage_manager* in_ptr, Storage_manager_xingxian* in_xx_ptr)
{
	storage_tool = in_ptr;
	Storage_tool_xingxian = in_xx_ptr;
}

Miller_GX_Base* Miller_D_Base::gen_gx(int tpye)
{
	//工序数量会很多，用跳表
	switch (tpye)
	{
	case 0:
		return new Miller_GX_ZQ_QDM;
	case 1:
		return new Miller_GX_ZQ_LXC;
	case 2:
		return new Miller_GX_ZQ_HDM_1;
	case 3:
		return new Miller_GX_ZQ_HDM_2;
	case 4:
		return new Miller_GX_ZQ_HDM_3;
	case 5:
		return new Miller_GX_ZQ_DaoTiJianXi;
	case 6:
		return new Miller_GX_ZQ_DaoJianJianXi;
	case 7:
		return new Miller_GX_ZQ_DaoJianFenXieCao;
		//********************************
	case 8:
		return new Miller_GX_PD_DCC;
	case 9:
		return new Miller_GX_PD_DHDM_1;
	case 10:
		return new Miller_GX_PD_DHDM_2;
	case 11:
		return new Miller_GX_PD_DHDM_3;
	case 12:
		return new Miller_GX_PD_LXC;
	case 13:
		return new Miller_GX_PD_HDM_1;
	case 14:
		return new Miller_GX_PD_HDM_2;
	case 15:
		return new Miller_GX_PD_HDM_3;
	case 16:
		return new Miller_GX_PD_DaoTiJianXi;
		//*************************************
	case 17:
		return new Miller_GX_R_QDM_R;
	case 18:
		return new Miller_GX_R_HDM_1;
	case 19:
		return new Miller_GX_R_HDM_2;
	case 20:
		return new Miller_GX_R_HDM_3;
	case 21:
		return new Miller_GX_R_LXC;
	case 22:
		return new Miller_GX_R_DaoTiJianXi;
	case 23:
		return new Miller_GX_R_DaoJianJianXi;
	case 24:
		return new Miller_GX_R_DaoJianFenXieCao;
		//*************************************
	case 25:
		return new Miller_GX_CX_KaiCao;
	case 26:
		return new Miller_GX_CX_HDM_1;
	case 27:
		return new Miller_GX_CX_HDM_2;

	default:
		return nullptr;
		break;
	}


}

int Miller_D_Base::get_canshu_gg_count()
{
	if (tool_type == 0)
	{
		return 13;
	}
	//后序根据铣刀公共参数在次加 7.4 ???
	if (tool_type == 1)
	{
		return 13;
	}
	if (tool_type == 2)
	{
		return 13;
	}
	if (tool_type == 3)
	{
		return 13;
	}
	if (tool_type == 4)
	{
		return 13;
	}

}

bool Miller_D_Base::del_gx(int gx_index)
{
	if (gx_index >= get_gx_num())
	{
		return false;
	}
	delete v_data[gx_index]; //释放内存
	v_data.erase(v_data.begin() + gx_index);
	return true;
}

void Miller_D_Base::get_gx(int gx_index, Miller_GX_Base*& ans_ptr_gx)
{
	ans_ptr_gx = v_data[gx_index];
}

void Miller_D_Base::set_gx(int gx_index, XingCan_Miller_GX& in_ptr)
{
	//1、拿出列表指定工序
	//2、修改工序-判断类型--
	//3、放回工序列表
	//6.18 zy 不新建新的工序将原工序的参数修改即可达到目的-多态

	Miller_GX_Base* cur_gx = v_data[gx_index];
	int cur_type = cur_gx->get_gx_type();
	cur_gx->set_canshu(in_ptr);
}

void Miller_D_Base::set_gx_order_up(int cur_index)
{
	if (cur_index == 0)
	{
		return;
	}
	//swap(v_gx_order.begin() + cur_index, v_gx_order.begin() + cur_index - 1);
	int temp = v_gx_order[cur_index];
	v_gx_order[cur_index] = v_gx_order[cur_index - 1];
	v_gx_order[cur_index - 1] = temp;
}

void Miller_D_Base::set_gx_order_down(int cur_index)
{
	if (cur_index == v_gx_order.size() - 1)
	{
		return;
	}
	//swap(v_gx_order.begin() + cur_index, v_gx_order.begin() + cur_index + 1);
	int temp = v_gx_order[cur_index];
	v_gx_order[cur_index] = v_gx_order[cur_index - 1];
	v_gx_order[cur_index - 1] = temp;
}

//void Miller_D_Base::set_gx_order(int index_move, int index_aim)
//{
//	/*Miller_GX_Base* cur_gx = v_data[index_move];
//	v_data.insert(v_data.begin() + index_aim, cur_gx);
//	v_data.erase(v_data.begin() + index_move + 1);*/
//
//
//}

int Miller_D_Base::get_gx_num()
{
	return v_data.size();
}

double Miller_D_Base::get_gg_canshu_start_zhuan()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_start_qing()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_strat_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_end_zhuan()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_end_qing()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_end_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_D_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_Zhui()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_bing()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_R_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_1_width()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_1_d_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_1_a_qiu()
{
	return 0.0;
}



double Miller_D_Base::get_gg_canshu_hdm_1_d_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_1_a_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_2_width()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_2_d_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_2_a_qiu()
{
	return 0.0;
}


double Miller_D_Base::get_gg_canshu_ang_2_d_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_2_a_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_hdm_3_width()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_3_d_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_3_a_qiu()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_3_d_luo()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_ang_3_a_luo()
{
	return 0.0;
}

void Miller_D_Base::get_dengfen_ang(vector<double>& in_v_ang)
{
}

double Miller_D_Base::get_gg_canshu_len_all()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_len_ren()
{
	return 0.0;
}

double Miller_D_Base::get_gg_canshu_D_bing()
{
	return 0.0;
}

void Miller_D_PD::set_canshu_gg(CanShu_PD_GongGong& in_ptr)
{
	canshu_gg = in_ptr;
}

bool Miller_D_PD::add_gx_by_end(XingCan_Miller_GX& in_ptr, int in_name)
{
	//1、根据参数类型 new一个对应工序 8-16
//2、工序所需操作流程
//3、放入工序列表
	int cur_type = in_ptr.get_gx_type();
	Miller_GX_Base* cur_gx = nullptr;
	switch (cur_type)
	{
	case 8:
		cur_gx = new Miller_GX_PD_DCC(this);
		break;
	case 9:
		cur_gx = new Miller_GX_PD_DHDM_1(this);
		break;
	case 10:
		cur_gx = new Miller_GX_PD_DHDM_2(this);
		break;
	case 11:
		cur_gx = new Miller_GX_PD_DHDM_3(this);
		break;
	case 12:
		cur_gx = new Miller_GX_PD_LXC(this);
		break;
	case 13:
		cur_gx = new Miller_GX_PD_HDM_1(this);
		break;
	case 14:
		cur_gx = new Miller_GX_PD_HDM_2(this);
		break;
	case 15:
		cur_gx = new Miller_GX_PD_HDM_3(this);
		break;
	case 16:
		cur_gx = new Miller_GX_PD_DaoTiJianXi(this);
		break;
	default:
		return false;
	}

	cur_gx->set_name(in_name);
	cur_gx->set_canshu(in_ptr);
	cur_gx->Save();
	v_data.push_back(cur_gx);

	//4、更新执行顺序列表
	v_gx_order.push_back(v_data.size() - 1); //0为第一执行
	return false;
}


void Miller_D_PD::cal_base_Ren_data()
{
	v_base_Ren_data.clear();
	//生成不同的刃放到容器
	for (int i = 0; i < canshu_gg.ren_count; i++)
	{
		Ren_data_D_PD cur_ren_data;
#pragma region 计算刃线
		double pos_ang = canshu_gg.v_no_dengfen_angle[i];
		double pianxin = canshu_gg.v_pianxin_dis[i];
		double center_dis = canshu_gg.v_center_dis[i];

		generator_line ls_gen_line;
		ls_gen_line.set_delta_dis(delta_dis_ren);

		mat sys_rotate = tcRotZ(3, pos_ang); //旋转位置
		vec pos = { 0.0, 0.0, 0.0 };
		//端刃直刃线
		ls_gen_line.gen_duan_ren_line(canshu_gg.D_qiu / 2.0,
			pianxin, canshu_gg.ang_die, 0.0,
			tcRotX(3, 180), pos);

		//切到中心距离2.17
		double cur_delta_dis = ls_gen_line.get_delta_dis();
		double len_line = cur_delta_dis * ls_gen_line.ans_line.count_points();
		double percent_cut = center_dis / len_line;
		ls_gen_line.cutting(0.0, 1.0 - percent_cut);  //指向中心，切掉结束

		ls_gen_line.rotate(sys_rotate);
		ls_gen_line.fanxiang();

		cur_ren_data.base_rx_hen.ImportData_by_hengren(ls_gen_line.ans_line);

		//test
		//mat test_hdm = cur_ren_data.base_rx_hen.get_kongjianxian();
		//test_hdm.save(R"(test_hen-2.10.txt)", raw_ascii);

		//螺旋刃线
		ls_gen_line.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			0.0, canshu_gg.ang_luo,
			canshu_gg.len_ren, 0.0,
			sys_rotate, pos);
		cur_ren_data.base_rx_luo.ImportData_by_luoxuancao(ls_gen_line.ans_line);

		//螺旋槽-空间线延长至刀尖
		generator_line ls_gen_line2;
		ls_gen_line2.set_delta_dis(delta_dis_ren);

		ls_gen_line2.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			0.0, canshu_gg.ang_luo,
			1.2 * canshu_gg.D_qiu / 2.0, 0.0,
			tcRotX(3, 180), pos);
		ls_gen_line2.rotate(sys_rotate);  //先转x-180换到z的副方向，在转z对应角度
		ls_gen_line2.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
		ls_gen_line2.join_a_line(ls_gen_line.ans_line);

		cur_ren_data.base_rx_luo_cao.ImportData_by_luoxuancao(ls_gen_line2.ans_line);

		//test
		//mat test_luo = cur_ren_data.base_rx_luo_cao.get_kongjianxian();
		//test_luo.save(R"(test_luo-12.17.txt)", raw_ascii);

#pragma endregion

		//计算后刀面
		cur_ren_data.cal_base_hdm123(canshu_gg); //计算用的刃线已经在旋转后的位置

		//计算刀尖间隙
		//cur_ren_data.cal_base_djjx(canshu_gg, pos_ang);//工件坐标系中旋转对应位置

		//计算端齿槽
		//cur_ren_data.cal_base_duan_cao(canshu_gg, i); 

		//test
		//mat test_hdm = cur_ren_data.base_rx_djjx.get_kongjianxian();
		//test_hdm.save(R"(test_djjx-11.25.txt)", raw_ascii);

		v_base_Ren_data.push_back(cur_ren_data);
	}

}

double Miller_D_PD::get_gg_canshu_len_all()
{
	return canshu_gg.len_all;
}

double Miller_D_PD::get_gg_canshu_len_ren()
{
	return canshu_gg.len_ren;
}

double Miller_D_PD::get_gg_canshu_D_bing()
{
	return canshu_gg.D_bing;
}

double Miller_D_PD::get_gg_canshu_D_qiu()
{
	return canshu_gg.D_qiu;
}

double Miller_D_PD::get_gg_canshu_ang_die()
{
	return canshu_gg.ang_die;
}

double Miller_D_PD::get_gg_canshu_Zhui()
{
	return 0.0;
}

double Miller_D_PD::get_gg_canshu_luo()
{
	return canshu_gg.ang_luo;
}


Miller_D_PD::Miller_D_PD()
{
	tool_type = 1;
}

Miller_D_PD::~Miller_D_PD()
{
}

void Miller_D_PD::get_canshu(CanShu_PD_GongGong& ans)
{
	ans = canshu_gg;
}

void Miller_D_PD::set_canshu(CanShu_PD_GongGong& ptr)
{
	XingCan_Tool_Base temp_bl;
	self_xingcan->set_Canshu_PD_GG(ptr);
}

void Miller_D_PD::set_canshu(XingCan_Tool_Base& ptr)
{
	canshu_gg = *(ptr.can_pd_gg); //改为public
	self_xingcan = &ptr;
}

Miller_D_PD::Miller_D_PD(int in_name)
{
	name = in_name;
}

int Miller_D_PD::Save()
{
	//1、确定工序存储的位置队列
	int ls_gx_pos[100] = {};
	int ls_gx_zhixing[100] = {};
	for (int i = 0; i < v_data.size(); i++)
	{
		int cur_pos = v_data[i]->Save();
		ls_gx_pos[i] = cur_pos;
		ls_gx_zhixing[i] = v_gx_order[i];
	}
	//2、确定参数存储的位置
	int can_pos = storage_tool->write_a_row_data(1, (char*)&canshu_gg, sizeof(canshu_gg));

	//3、构造一条刀具对象数据
	//3.1 写时间和类型文件--先于对象前写入
	time_updata cur_time;
	storage_tool->write_a_row_data(16, (char*)&cur_time, sizeof(cur_time));
	storage_tool->write_a_row_data(17, (char*)&tool_type, sizeof(tool_type));

	//构造一条刀具对象数据
	tool_obj_data ls_row_data(tool_type, name, v_data.size(), ls_gx_pos, ls_gx_zhixing);
	//3.2管理写文件被打开两次，位置被后移--加判断标志位0，即加对象时更新最大存放位置
	int tool_pos = storage_tool->write_a_row_data(0, (char*)&ls_row_data, sizeof(ls_row_data));

	//4、往刀具计数文件写入一条
	storage_tool->add_tool_count(1);

	return tool_pos;
}

void Miller_D_PD::Load(int in_pos)
{
	////读出一条刀具对象数据
	//tool_obj_data ls_row_data;
	//storage_tool->read_a_row_data(0, in_pos, (char*)&ls_row_data, sizeof(ls_row_data));

	////恢复公共参数
	////int can_pos = ls_row_data.data_pos;  //参数位置等于刀具对象位置 7.4 
	//storage_tool->read_a_row_data(1, in_pos, (char*)&canshu_gg, sizeof(canshu_gg));

	////2.1 当前刀的两个容器恢复
	//for (int i = 0; i < ls_row_data.gx_count; i++)
	//{
	//	v_gx_pos.push_back(ls_row_data.gx_pos[i]);
	//	v_gx_order.push_back(ls_row_data.gx_zhixing[i]);
	//}

	////恢复工序
	//for (int i = 0; i < ls_row_data.gx_count; i++)
	//{
	//	int cur_gx_pos = ls_row_data.gx_pos[i];
	//	//读出一条gx对象数据
	//	gx_obj_data ls_row_data_gx;
	//	storage_tool->read_a_row_data(4, cur_gx_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));

	//	//根据工序类型new一个工序
	//	Miller_GX_Base* ls_gx = gen_gx(ls_row_data_gx.type);
	//	ls_gx->set_self_dao(this);

	//	XingCan_Miller_GX* ls_xc = new XingCan_Miller_GX(ls_row_data_gx.type);
	//	ls_gx->self_xingcan = ls_xc;
	//	ls_gx->Load(cur_gx_pos);

	//	//工序基类数据更新-选择刃和角度-11.6
	//	for (int i = 0; i < 6; i++)
	//	{
	//		ls_gx->A_before_ren[i] = ls_row_data_gx.A_before_ren[i];
	//		ls_gx->sel_A_before_ren[i] = ls_row_data_gx.sel_A_before_ren[i];
	//	}
	//	Point_by_5axis ls_anquan_p;
	//	storage_tool->read_a_row_data(20, cur_gx_pos, (char*)&ls_anquan_p, sizeof(ls_anquan_p));
	//	ls_gx->anquandian = ls_anquan_p;

	//	v_data.push_back(ls_gx);
	//}

	////恢复名字
	//name = ls_row_data.name;
	//XingCan_Miller_D* ls_xc = new XingCan_Miller_D(1);
	//self_xingcan = ls_xc;
	//set_canshu(canshu_gg);


	//2.10
	//读出一条刀具对象数据
	tool_obj_data ls_row_data;
	storage_tool->read_a_row_data(0, in_pos, (char*)&ls_row_data, sizeof(ls_row_data));
	//恢复名字
	name = ls_row_data.name;

	//恢复公共参数
	//int can_pos = ls_row_data.data_pos;  //参数位置等于刀具对象位置 7.4 ???
	storage_tool->read_a_row_data(1, in_pos, (char*)&canshu_gg, sizeof(canshu_gg));
	XingCan_Tool_Base* ls_xc = new XingCan_Tool_Base(0);
	self_xingcan = ls_xc;
	set_canshu(canshu_gg);

	//2.1 当前刀的两个容器恢复
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		v_gx_pos.push_back(ls_row_data.gx_pos[i]);
		v_gx_order.push_back(ls_row_data.gx_zhixing[i]);
	}

	//恢复工序--恢复执行列表对应存储位置--10.17
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		int cur_zhixing = ls_row_data.gx_zhixing[i];
		int cur_gx_pos = ls_row_data.gx_pos[cur_zhixing];

		//读出一条gx对象数据
		gx_obj_data ls_row_data_gx;
		storage_tool->read_a_row_data(4, cur_gx_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));

		//根据工序类型new一个工序
		Miller_GX_Base* ls_gx = gen_gx(ls_row_data_gx.type);
		ls_gx->set_self_dao(this);

		XingCan_Miller_GX* ls_xc = new XingCan_Miller_GX(ls_row_data_gx.type);
		ls_gx->self_xingcan = ls_xc;
		ls_gx->Load(cur_gx_pos);

		ls_gx->slz_num = ls_row_data_gx.sl_num;
		ls_gx->in_or_out = ls_row_data_gx.in_or_out;
		ls_gx->jingeilv = ls_row_data_gx.jingeilv;

		//工序基类数据更新-选择刃和角度-11.6
		for (int i = 0; i < 6; i++)
		{
			ls_gx->A_before_ren[i] = ls_row_data_gx.A_before_ren[i];
			ls_gx->sel_A_before_ren[i] = ls_row_data_gx.sel_A_before_ren[i];
		}
		Point_by_5axis ls_anquan_p;
		storage_tool->read_a_row_data(20, cur_gx_pos, (char*)&ls_anquan_p, sizeof(ls_anquan_p));
		ls_gx->anquandian = ls_anquan_p;

		//CanShu_shalun_cal_DL ls_sl_drfl;

		//ls_gx->shalun_canshu = 

		v_data.push_back(ls_gx);
	}
}

void Miller_D_R::set_canshu_gg(CanShu_R_GongGong& in_ptr)
{
	canshu_gg = in_ptr;
}

bool Miller_D_R::add_gx_by_end(XingCan_Miller_GX& in_ptr, int in_name)
{
	//1、根据参数类型 new一个对应工序 17-24
//2、工序所需操作流程
//3、放入工序列表
	int cur_type = in_ptr.get_gx_type();
	Miller_GX_Base* cur_gx = nullptr;
	switch (cur_type)
	{
	case 17:
		cur_gx = new Miller_GX_R_QDM_R(this);
		break;
	case 18:
		cur_gx = new Miller_GX_R_HDM_1(this);
		break;
	case 19:
		cur_gx = new Miller_GX_R_HDM_2(this);
		break;
	case 20:
		cur_gx = new Miller_GX_R_HDM_3(this);
		break;
	case 21:
		cur_gx = new Miller_GX_R_LXC(this);
		break;
	case 22:
		cur_gx = new Miller_GX_R_DaoTiJianXi(this);
		break;
	case 23:
		cur_gx = new Miller_GX_R_DaoJianJianXi(this);
		break;
	case 24:
		cur_gx = new Miller_GX_R_DaoJianFenXieCao(this);
		break;
	default:
		return false;
	}

	cur_gx->set_name(in_name);
	cur_gx->set_canshu(in_ptr);
	cur_gx->Save();
	v_data.push_back(cur_gx);

	//4、更新执行顺序列表
	v_gx_order.push_back(v_data.size() - 1); //0为第一执行
	return false;
}



void Miller_D_R::cal_base_Ren_data()
{
	v_base_Ren_data.clear();
	//生成不同的刃放到容器
	for (int i = 0; i < canshu_gg.ren_count; i++)
	{
		Ren_data_D_R cur_ren_data;
#pragma region 计算刃线
		double pos_ang = canshu_gg.v_no_dengfen_angle[i];
		double pianxin = canshu_gg.v_pianxin_dis[i];
		double center_dis = canshu_gg.v_center_dis[i];

		generator_line ls_gen_line;
		ls_gen_line.set_delta_dis(delta_dis_ren);

		mat sys_rotate = tcRotZ(3, pos_ang); //旋转位置
		vec pos = { 0.0, 0.0, 0.0 };
		//端刃直刃线
		ls_gen_line.gen_duan_ren_line(canshu_gg.D_qiu / 2.0,
			pianxin, canshu_gg.ang_die, 0.0,
			tcRotX(3, 180), pos);

		//切到中心距离2.17
		double cur_delta_dis = ls_gen_line.get_delta_dis();
		double len_line = cur_delta_dis * ls_gen_line.ans_line.count_points();
		double percent_cut = center_dis / len_line;
		ls_gen_line.cutting(0.0, 1.0 - percent_cut);  //指向中心，切掉结束

		ls_gen_line.rotate(sys_rotate);
		ls_gen_line.fanxiang();

		cur_ren_data.base_rx_hen.ImportData_by_hengren(ls_gen_line.ans_line);

		//test
		//mat test_hdm = cur_ren_data.base_rx_hen.get_kongjianxian();
		//test_hdm.save(R"(test_hen-3.27.txt)", raw_ascii);

		//螺旋刃线
		ls_gen_line.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			0.0, canshu_gg.ang_luo,
			canshu_gg.len_ren, 0.0,
			sys_rotate, pos);
		cur_ren_data.base_rx_luo.ImportData_by_luoxuancao(ls_gen_line.ans_line);

		//螺旋槽-空间线延长至刀尖
		generator_line ls_gen_line2;
		ls_gen_line2.set_delta_dis(delta_dis_ren);

		ls_gen_line2.gen_luoxuan_ren_line(canshu_gg.D_qiu / 2.0,
			0.0, canshu_gg.ang_luo,
			1.2 * canshu_gg.D_qiu / 2.0, 0.0,
			tcRotX(3, 180), pos);
		ls_gen_line2.rotate(sys_rotate);  //先转x-180换到z的副方向，在转z对应角度
		ls_gen_line2.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
		ls_gen_line2.join_a_line(ls_gen_line.ans_line);

		cur_ren_data.base_rx_luo_cao.ImportData_by_luoxuancao(ls_gen_line2.ans_line);

		//test
		//mat test_luo = cur_ren_data.base_rx_luo_cao.get_kongjianxian();
		//test_luo.save(R"(test_luo-3.27.txt)", raw_ascii);

		//圆角刃线25.3.27
#pragma region RRR
		generator_line ls_gen_line3; 
		ls_gen_line3.set_delta_dis(delta_dis_ren);
		//准备两点及切向 3.31
		//准备三段线对应访问个数
		int count_p_hen = cur_ren_data.base_rx_hen.get_p_num();
		int count_p_luo = cur_ren_data.base_rx_luo.get_p_num();

		double p_delta_dis = cur_ren_data.base_rx_hen.Distance_of_Point;
		int count_p_cut = canshu_gg.R_qiu / p_delta_dis;
		int start_index = count_p_hen - count_p_cut;
		//切螺旋线
		p_delta_dis = cur_ren_data.base_rx_luo.Distance_of_Point;
		int count_p_cut_luo = canshu_gg.R_qiu / p_delta_dis;
		int end_index = count_p_cut_luo;

		vec3 start_p = cur_ren_data.base_rx_hen.P(start_index);
		//vec3 start_p1 = { -0.00003483449 ,4.48415627249 ,0.00005089381 };
		vec3 start_t = normalise(cur_ren_data.base_rx_hen.nX(start_index));
		vec3 end_p = cur_ren_data.base_rx_luo.P(end_index);
		//vec3 end_p1 = { -0.29353364565 ,4.99114272561 ,0.50812262860 };
		vec3 end_t = normalise(cur_ren_data.base_rx_luo.nX(end_index)); //螺旋切削向下

		ls_gen_line3.gen_rrr_by_hermite(start_p, start_t, end_p, end_t,
			100, tcRotX(3, 0.0), pos); //用刃线构造的，横刃和螺旋正确，圆角线不用旋转3.31
		//ls_gen_line3.rotate(sys_rotate);
		//ls_gen_line3.fanxiang();//柱面到端面
		cur_ren_data.base_rx_rrr.ImportData_by_qiutou(ls_gen_line3.ans_line);
#pragma endregion
	
#pragma endregion

		//计算后刀面
		cur_ren_data.cal_base_hdm123(canshu_gg); //计算用的刃线已经在旋转后的位置

		//test
		//mat test_hdm = cur_ren_data.base_rx_djjx.get_kongjianxian();
		//test_hdm.save(R"(test_djjx-11.25.txt)", raw_ascii);

		v_base_Ren_data.push_back(cur_ren_data);
	}


}

double Miller_D_R::cal_R_zhuan_ang(double in_R, double in_D, double in_luo)
{
	double zhuan_hu = in_R * tan(tcRadians(in_luo));
	double zhuan_ang = tcDegree(zhuan_hu / in_D);
	return zhuan_ang;
}

double Miller_D_R::get_gg_canshu_D_qiu()
{
	return canshu_gg.D_qiu;
}

double Miller_D_R::get_gg_canshu_luo()
{
	return canshu_gg.ang_luo;
}

double Miller_D_R::get_gg_canshu_len_ren()
{
	return canshu_gg.len_ren;
}

double Miller_D_R::get_gg_canshu_len_all()
{
	return canshu_gg.len_all;
}

double Miller_D_R::get_gg_canshu_D_bing()
{
	return canshu_gg.D_bing;
}

double Miller_D_R::get_gg_canshu_ang_die()
{
	return canshu_gg.ang_die;
}

double Miller_D_R::get_gg_canshu_Zhui()
{
	return -1.0;
}

double Miller_D_R::get_gg_canshu_R_qiu()
{
	return canshu_gg.R_qiu;
}

Miller_D_R::Miller_D_R()
{
	tool_type = 2;
}

Miller_D_R::~Miller_D_R()
{
}

void Miller_D_R::get_canshu(CanShu_R_GongGong& ans)
{
	ans = canshu_gg;
}

void Miller_D_R::set_canshu(CanShu_R_GongGong& ptr)
{
	XingCan_Tool_Base temp_bl;
	self_xingcan->set_Canshu_R_GG(ptr);
}

void Miller_D_R::set_canshu(XingCan_Tool_Base& ptr)
{
	canshu_gg = *(ptr.can_r_gg); //改为public
	self_xingcan = &ptr;
}

Miller_D_R::Miller_D_R(int in_name)
{
	name = in_name;
}

int Miller_D_R::Save()
{
	//1、确定工序存储的位置队列
	int ls_gx_pos[100] = {};
	int ls_gx_zhixing[100] = {};
	for (int i = 0; i < v_data.size(); i++)
	{
		int cur_pos = v_data[i]->Save();
		ls_gx_pos[i] = cur_pos;
		ls_gx_zhixing[i] = v_gx_order[i];
	}
	//2、确定参数存储的位置
	int can_pos = storage_tool->write_a_row_data(1, (char*)&canshu_gg, sizeof(canshu_gg));

	//3、构造一条刀具对象数据
	//3.1 写时间和类型文件--先于对象前写入
	time_updata cur_time;
	storage_tool->write_a_row_data(16, (char*)&cur_time, sizeof(cur_time));
	storage_tool->write_a_row_data(17, (char*)&tool_type, sizeof(tool_type));

	//构造一条刀具对象数据
	tool_obj_data ls_row_data(tool_type, name, v_data.size(), ls_gx_pos, ls_gx_zhixing);
	//3.2管理写文件被打开两次，位置被后移--加判断标志位0，即加对象时更新最大存放位置
	int tool_pos = storage_tool->write_a_row_data(0, (char*)&ls_row_data, sizeof(ls_row_data));

	//4、往刀具计数文件写入一条
	storage_tool->add_tool_count(1);

	return tool_pos;
}

void Miller_D_R::Load(int in_pos)
{//读出一条刀具对象数据
	tool_obj_data ls_row_data;
	storage_tool->read_a_row_data(0, in_pos, (char*)&ls_row_data, sizeof(ls_row_data));

	//恢复公共参数
	//int can_pos = ls_row_data.data_pos;  //参数位置等于刀具对象位置 7.4 
	storage_tool->read_a_row_data(1, in_pos, (char*)&canshu_gg, sizeof(canshu_gg));

	//2.1 当前刀的两个容器恢复
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		v_gx_pos.push_back(ls_row_data.gx_pos[i]);
		v_gx_order.push_back(ls_row_data.gx_zhixing[i]);
	}

	//恢复工序
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		int cur_gx_pos = ls_row_data.gx_pos[i];
		//读出一条gx对象数据
		gx_obj_data ls_row_data_gx;
		storage_tool->read_a_row_data(4, cur_gx_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));

		//根据工序类型new一个工序
		Miller_GX_Base* ls_gx = gen_gx(ls_row_data_gx.type);
		ls_gx->set_self_dao(this);

		XingCan_Miller_GX* ls_xc = new XingCan_Miller_GX(ls_row_data_gx.type);
		ls_gx->self_xingcan = ls_xc;
		ls_gx->Load(cur_gx_pos);

		//工序基类数据更新-选择刃和角度-11.6
		for (int i = 0; i < 6; i++)
		{
			ls_gx->A_before_ren[i] = ls_row_data_gx.A_before_ren[i];
			ls_gx->sel_A_before_ren[i] = ls_row_data_gx.sel_A_before_ren[i];
		}
		Point_by_5axis ls_anquan_p;
		storage_tool->read_a_row_data(20, cur_gx_pos, (char*)&ls_anquan_p, sizeof(ls_anquan_p));
		ls_gx->anquandian = ls_anquan_p;

		v_data.push_back(ls_gx);
	}

	//恢复名字
	name = ls_row_data.name;
	XingCan_Tool_Base* ls_xc = new XingCan_Tool_Base(2);
	self_xingcan = ls_xc;
	set_canshu(canshu_gg);
}

Miller_D_CX::Miller_D_CX()
{
	tool_type = 3;
}

Miller_D_CX::~Miller_D_CX()
{
}


void Miller_D_CX::del_a_xx_by_order(int del_n_order)
{
	//删除数组对应行元素，并收缩
	for (int i = del_n_order; i < 30-1; i++)
	{
		canshu_gg.v_sel_dxf_pos[i] = canshu_gg.v_sel_dxf_pos[i + 1];
	}
	canshu_gg.v_sel_dxf_pos[29] = -1;
}

void Miller_D_CX::get_self_dxf_pos(vector<int>& v_pos)
{
	v_pos.clear();
	for (int i = 0; i < 30; i++)
	{
		if (-1 < canshu_gg.v_sel_dxf_pos[i])
		{
			v_pos.push_back(canshu_gg.v_sel_dxf_pos[i]);
		}
	}
}

void Miller_D_CX::set_a_ang_pos_xx(int ren_pos, int xx_oder)
{
	//canshu_gg.v_cur_ang_pos_to_dxf_index[ren_pos] = canshu_gg.v_sel_dxf_pos[xx_oder];
}

void Miller_D_CX::set_a_xx_storage_pos(int cur_tool_xx_count, int cur_stroage_pos)
{
	canshu_gg.v_sel_dxf_pos[cur_tool_xx_count] = cur_stroage_pos;
}

int Miller_D_CX::get_gg_canshu_xingxian_count()
{
	return canshu_gg.count_dxf__xx;
}

int Miller_D_CX::get_gg_canshu_houjiao_count()
{
	return canshu_gg.count_houjiao;
}

int Miller_D_CX::get_gg_canshu_luoxuan_count()
{
	return canshu_gg.count_luoxuan;
}

void Miller_D_CX::get_cx_luoxuancanshu_by_sel(int in_sel_index, int& ans_cao_type,
	double& ans_ang_zhuan, double& ans_ang_qing, double& ans_dis_pian,
	double& ans_ang_luo, double& ans_daocheng)
{
	ans_cao_type = canshu_gg.v_type_cao[in_sel_index];
	ans_ang_zhuan = canshu_gg.v_ang_zhuan[in_sel_index];
	ans_ang_qing = canshu_gg.v_ang_qing[in_sel_index];
	ans_dis_pian = canshu_gg.v_dis_pian[in_sel_index];
	ans_ang_luo = canshu_gg.v_ang_luo[in_sel_index];
	ans_daocheng = canshu_gg.v_daocheng[in_sel_index];
}

void Miller_D_CX::get_cx_caiyang_canshu(int& ans_cai_type, double& ans_cai_len, double& ans_cai_ang)
{
	ans_cai_type = canshu_gg.cai_type;
	ans_cai_len = canshu_gg.cai_len;
	ans_cai_ang = canshu_gg.cai_ang;
}

Miller_D_CX::Miller_D_CX(int in_name)
{
	name = in_name;
}

int Miller_D_CX::Save()
{
	//1、确定工序存储的位置队列
	int ls_gx_pos[100] = {};
	int ls_gx_zhixing[100] = {};
	for (int i = 0; i < v_data.size(); i++)
	{
		int cur_pos = v_data[i]->Save();
		ls_gx_pos[i] = cur_pos;
		ls_gx_zhixing[i] = v_gx_order[i];
	}
	//2、确定参数存储的位置
	int can_pos = storage_tool->write_a_row_data(1, (char*)&canshu_gg, sizeof(canshu_gg));

	//3、构造一条刀具对象数据
	//3.1 写时间和类型文件--先于对象前写入
	time_updata cur_time;
	storage_tool->write_a_row_data(16, (char*)&cur_time, sizeof(cur_time));
	storage_tool->write_a_row_data(17, (char*)&tool_type, sizeof(tool_type));

	//构造一条刀具对象数据
	tool_obj_data ls_row_data(tool_type, name, v_data.size(), ls_gx_pos, ls_gx_zhixing);
	//3.2管理写文件被打开两次，位置被后移--加判断标志位0，即加对象时更新最大存放位置
	int tool_pos = storage_tool->write_a_row_data(0, (char*)&ls_row_data, sizeof(ls_row_data));

	//4、往刀具计数文件写入一条
	storage_tool->add_tool_count(1);

	return tool_pos;
}

void Miller_D_CX::Load(int in_pos)
{//读出一条刀具对象数据
	tool_obj_data ls_row_data;
	storage_tool->read_a_row_data(0, in_pos, (char*)&ls_row_data, sizeof(ls_row_data));
	//恢复名字
	name = ls_row_data.name;

	//恢复公共参数
	//int can_pos = ls_row_data.data_pos;  //参数位置等于刀具对象位置 7.4 ???
	storage_tool->read_a_row_data(1, in_pos, (char*)&canshu_gg, sizeof(canshu_gg));
	XingCan_Tool_Base* ls_xc = new XingCan_Tool_Base(0);
	self_xingcan = ls_xc;
	set_canshu(canshu_gg);

	//2.1 当前刀的两个容器恢复
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		v_gx_pos.push_back(ls_row_data.gx_pos[i]);
		v_gx_order.push_back(ls_row_data.gx_zhixing[i]);
	}

	//恢复工序--恢复执行列表对应存储位置--10.17
	for (int i = 0; i < ls_row_data.gx_count; i++)
	{
		int cur_zhixing = ls_row_data.gx_zhixing[i];
		int cur_gx_pos = ls_row_data.gx_pos[cur_zhixing];

		//读出一条gx对象数据
		gx_obj_data ls_row_data_gx;
		storage_tool->read_a_row_data(4, cur_gx_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));

		//根据工序类型new一个工序
		Miller_GX_Base* ls_gx = gen_gx(ls_row_data_gx.type);
		ls_gx->set_self_dao(this);

		XingCan_Miller_GX* ls_xc = new XingCan_Miller_GX(ls_row_data_gx.type);
		ls_gx->self_xingcan = ls_xc;
		ls_gx->Load(cur_gx_pos);

		ls_gx->slz_num = ls_row_data_gx.sl_num;
		ls_gx->in_or_out = ls_row_data_gx.in_or_out;
		ls_gx->jingeilv = ls_row_data_gx.jingeilv;

		//工序基类数据更新-选择刃和角度-11.6
		for (int i = 0; i < 6; i++)
		{
			ls_gx->A_before_ren[i] = ls_row_data_gx.A_before_ren[i];
			ls_gx->sel_A_before_ren[i] = ls_row_data_gx.sel_A_before_ren[i];
		}
		Point_by_5axis ls_anquan_p;
		storage_tool->read_a_row_data(20, cur_gx_pos, (char*)&ls_anquan_p, sizeof(ls_anquan_p));
		ls_gx->anquandian = ls_anquan_p;

		//CanShu_shalun_cal_DL ls_sl_drfl;

		//ls_gx->shalun_canshu = 

		v_data.push_back(ls_gx);
	}
}


void Miller_D_CX::get_dengfen_ang(vector<double>& in_v_ang)
{
	/*for (int i = 0; i < 6; i++)
	{
		in_v_ang.push_back(canshu_gg.v_no_dengfen_angle[i]);
	}*/
}

void Miller_D_CX::get_qdm_of_cx(int in_ren_pos_num, mat& data_qdm)
{
	data_qdm = v_base_Ren_data[in_ren_pos_num].base_qdm;
}

void Miller_D_CX::get_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_1;
}

void Miller_D_CX::get_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_2;
}

void Miller_D_CX::get_renxian_of_cx_hdm(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_hdm;
}

void Miller_D_CX::get_canshu(CanShu_CX_GongGong& ans)
{
	ans = canshu_gg;
}

void Miller_D_CX::set_canshu(CanShu_CX_GongGong& ptr)
{
	XingCan_Tool_Base temp_bl;
	self_xingcan->set_Canshu_CX_GG(ptr);
}

void Miller_D_CX::set_canshu(XingCan_Tool_Base& ptr)
{
	canshu_gg = *(ptr.can_cx_gg); //改为public
	self_xingcan = &ptr;
}

bool Miller_D_CX::add_gx_by_end(XingCan_Miller_GX& in_ptr, int in_name)
{
	//1、根据参数类型 new一个对应工序 25-26
//2、工序所需操作流程
//3、放入工序列表
	int cur_type = in_ptr.get_gx_type();
	Miller_GX_Base* cur_gx = nullptr;
	switch (cur_type)
	{
	case 25:
		cur_gx = new Miller_GX_CX_KaiCao(this);
		break;
	case 26:
		cur_gx = new Miller_GX_CX_HDM_1(this);
		break;
		//case 2:
		//	cur_gx = new Miller_GX_ZQ_HDM_1(this);
		//	break;
		//case 3:
		//	cur_gx = new Miller_GX_ZQ_HDM_2(this);
		//	break;

	default:
		return false;
	}

	cur_gx->set_name(in_name);
	cur_gx->set_canshu(in_ptr);
	cur_gx->Save();
	v_data.push_back(cur_gx);

	//4、更新执行顺序列表
	v_gx_order.push_back(v_data.size() - 1); //0为第一执行
	return false;
}

void Miller_D_CX::cal_base_Ren_data()
{
	//根据型线密度，计算出每个点的交点，形成刃线

	//1、准备型线、直槽面
	//2、求交得到空间线、转为刃线
	//3、放入基础数据结构

	v_base_Ren_data.clear();
	//生成不同的刃放到容器
//	for (int i = 0; i < canshu_gg.ren_count; i++)
//	{
//		Ren_data_D_CX cur_ren_data;
//		double pos_ang = canshu_gg.v_no_dengfen_angle[i];
//		//double pianxin = canshu_gg.v_pianxin_dis[i];
//		//double center_dis = canshu_gg.v_center_dis[i];
//		int dxf_file_pos = canshu_gg.v_sel_dxf_pos[i];
//
//		mat sys_rotate = tcRotZ(3, pos_ang); //旋转位置
//
////#pragma region 计算刃线
////		//1.1 根据类型初始化型线
////		Miller_XingXian ans_xingxian;
////		string tag_dxf = Storage_tool_xingxian->get_tag_pos_dxf_file_name(dxf_file_pos);
////		if (canshu_gg.cai_type == 0)
////		{
////			ans_xingxian.init_data_by_dxf_file(tag_dxf, canshu_gg.cai_len);
////		}
////		if (canshu_gg.cai_type == 1)
////		{
////			ans_xingxian.init_data_by_dxf_file(tag_dxf, canshu_gg.cai_len, canshu_gg.cai_ang);
////		}
////		cur_ren_data.base_xx = ans_xingxian;
////		cur_ren_data.base_xx.rotate(sys_rotate);
////
////		//1.2 根据槽型参数初始化槽面 --螺旋槽暂时不考虑3.10
////		Miller_CaoMian ans_caomian;
////		if (canshu_gg.type_cao == 0)
////		{
////			ans_caomian.init_data_by_zhuan_qing(canshu_gg.ang_zhuan, canshu_gg.ang_qing);
////		}
////		if (canshu_gg.type_cao == 1)
////		{
////			ans_caomian.init_data_by_pianxin_qing(canshu_gg.dis_pian, canshu_gg.ang_qing);
////		}
////		cur_ren_data.base_caomian = ans_caomian;
////		cur_ren_data.base_caomian.rotate(sys_rotate);
////
////		//1.3 计算开槽的前刀面 12*n
////		mat ang_qdm;
////		cal_caomian_to_qdm_cao(ans_caomian, ang_qdm);
////		cur_ren_data.base_qdm = ang_qdm;
////
////		//test
////		/*mat test_hdm = cur_ren_data.base_rx_qiu.get_kongjianxian();
////		test_hdm.save(R"(test_luo-11.25.txt)", raw_ascii);*/
////
////		//2 计算后刀面的刃线
////		Cal_RenXian ans_rx_hdm;
////		cal_HDM_rx_by_jiao(ans_xingxian, ans_caomian, ans_rx_hdm);
////		cur_ren_data.base_rx_hdm = ans_rx_hdm;
////
////		//test
////		/*mat test_hdm = cur_ren_data.base_rx_luo.get_kongjianxian();
////		test_hdm.save(R"(test_luo-12.3.txt)", raw_ascii);*/
////
////#pragma endregion
//
//		//计算后刀面
//		cur_ren_data.cal_base_hdm123(canshu_gg); //计算用的刃线已经在旋转后的位置
//
//		v_base_Ren_data.push_back(cur_ren_data);
//	}
}

int Miller_D_CX::solveQuadraticEquation(double a, double b, double c, double& x1, double& x2)
{
	if (abs(a) < 0.000000001)
	{
		//std::cout << "这不是一个二次方程，因为a不能为0。" << std::endl;
		return -2;
	}

	double discriminant = b * b - 4 * a * c;

	if (discriminant > 0)
	{
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		x2 = (-b - sqrt(discriminant)) / (2 * a);
		return 1;
	}
	else if (abs(discriminant) < 0.000000001)
	{
		x1 = -b / (2 * a);
		x2 = -b / (2 * a);
		return 0;
	}
	else
	{
		double realPart = -b / (2 * a);
		double imaginaryPart = sqrt(-discriminant) / (2 * a);
		return -1;
	}
	return -2;
}

void Miller_D_CX::cal_caomian_to_qdm_cao(Cal_LouXuan& in_caomian, mat& ans_cao_qdm)
{
	//槽面已有点及方向，方向等于前角线，两点构成切向，叉乘得到法向
	//条件不够，只构造前刀面坐标系，放在法坐标系上 3.10 ？
	//针对直槽，只用计算一个点位，后续相同
	int count_p = in_caomian.n_P();

	vec ls_p = in_caomian.BG_P(3, 0);
	vec ls_y = in_caomian.BG_T(3, 0);//前角线
	vec ls_p1 = in_caomian.BG_P(3, 1);
	vec ls_t = normalise(ls_p1 - ls_p);
	vec ls_n = normalise(cross(ls_t, ls_y));

	ans_cao_qdm.reset();
	for (int i = 0; i < count_p; i++)
	{
		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		 ls_t(0) ,ls_t(1) ,ls_t(2),
		 ls_y(0) ,ls_y(1) ,ls_y(2),
		 ls_n(0) ,ls_n(1) ,ls_n(2) };
		ans_cao_qdm.insert_cols(ans_cao_qdm.n_cols, ans);
	}

}

void Miller_D_CX::cal_HDM_rx_by_jiao(Cal_XingXian& in_xingxian, Cal_LouXuan& in_caomian, Cal_RenXian& ans_rx_hdm)
{
	mat ans_hdm_p;
	//逐点求交
	int count_p = in_xingxian.n_P();
	for (int i = 0; i < count_p; i++)
	{
		vec p_xing = in_xingxian.BG_hP(3, i);
		vec p_cao = in_caomian.BG_P(3, i);		//O
		vec t_cao = in_caomian.BG_T(3, i);		//T
		//构造函数的abc
		double a = t_cao(0) * t_cao(0) + t_cao(1) * t_cao(1);
		double b = 2.0 * (t_cao(0) * p_cao(0) + t_cao(1) * p_cao(1));
		double R2 = p_xing(0) * p_xing(0);
		double c = (p_cao(0) * p_cao(0) + p_cao(1) * p_cao(1)) - R2;

		double x1 = 0.0;
		double x2 = 0.0;
		int res_type = solveQuadraticEquation(a, b, c, x1, x2);

		vec3 ans_p = { 0.0,0.0,0.0 };
		if (res_type == 0)
		{
			ans_p = p_cao + x1 * t_cao;
		}
		else if (res_type == 1)
		{
			//双根取较小系数3.10
			if (x1 < x2)
			{
				ans_p = p_cao + x1 * t_cao;
			}
			else
			{
				ans_p = p_cao + x2 * t_cao;
			}

		}
		else
		{
			throw - 1;
		}
		ans_hdm_p.insert_cols(ans_hdm_p.n_cols, ans_p);
	}

	//构造刃线
	KongJianXian ls_line;
	ls_line.init_data(ans_hdm_p);
	ans_rx_hdm.ImportData_by_luoxuancao(ls_line);

}

XingCan_Tool_Base::XingCan_Tool_Base()
{
	tool_type = 0;
	can_zq_gg = nullptr;
	can_pd_gg = nullptr;
	can_r_gg = nullptr;
	can_cx_gg = nullptr;
}

XingCan_Tool_Base::~XingCan_Tool_Base()
{
}

XingCan_Tool_Base::XingCan_Tool_Base(int in_type)
{
	tool_type = in_type;
}

bool XingCan_Tool_Base::set_CanShu_ZQ_GG(CanShu_ZQ_GongGong& in_ptr)
{
	if (can_zq_gg != nullptr)
	{
		delete can_zq_gg;
	}
	can_zq_gg = new CanShu_ZQ_GongGong(in_ptr);
	tool_type = 0;
	return true;
}

bool XingCan_Tool_Base::set_Canshu_PD_GG(CanShu_PD_GongGong& in_ptr)
{
	if (can_pd_gg != nullptr)
	{
		delete can_pd_gg;
	}
	can_pd_gg = new CanShu_PD_GongGong(in_ptr);
	tool_type = 1;
	return true;
}

bool XingCan_Tool_Base::set_Canshu_R_GG(CanShu_R_GongGong& in_ptr)
{
	if (can_r_gg != nullptr)
	{
		delete can_r_gg;
	}
	can_r_gg = new CanShu_R_GongGong(in_ptr);
	tool_type = 2;
	return true;
}

bool XingCan_Tool_Base::set_Canshu_CX_GG(CanShu_CX_GongGong& in_ptr)
{
	if (can_cx_gg != nullptr)
	{
		delete can_cx_gg;
	}
	can_cx_gg = new CanShu_CX_GongGong(in_ptr);
	tool_type = 3;
	return true;
}

Ren_data_D_ZQ::Ren_data_D_ZQ()
{
}

Ren_data_D_ZQ::~Ren_data_D_ZQ()
{
}

void Ren_data_D_ZQ::cal_base_hdm123(CanShu_ZQ_GongGong& in_gg_canshu)
{
#pragma region 后刀面1
	//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X, 
	int p_num1 = base_rx_qiu.get_p_num();
	int p_num2 = base_rx_luo.get_p_num();
	base_hdm_1.resize(12, 0);
	base_hdm_1.insert_cols(0, p_num1 + p_num2);
	//qiutou部分
	double delta_ang_d = (in_gg_canshu.hdm_1_d_mid - in_gg_canshu.hdm_1_d_qiu) / (1.0 * p_num1 - 1); //被提到公共参数 8.12 mark
	double delta_ang_a = (in_gg_canshu.hdm_1_a_mid - in_gg_canshu.hdm_1_a_qiu) / (1.0 * p_num1 - 1);
	for (int i = 0; i < p_num1; i++)
	{
		double ls_d = in_gg_canshu.hdm_1_d_qiu + i * delta_ang_d; //从顶为0-10
		double ls_a = in_gg_canshu.hdm_1_a_qiu + i * delta_ang_a; //从顶为5-0

		mat33 ls_h_sys = base_rx_qiu.hSYS(i);

		//vec3 G_Z_HDM = normalise(-base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
		////轴向后角根据法向情况偏置--10.21
		//double dot_value = dot(G_Z_HDM, tcZ(3)); //变化规律cos，后续可能改为线性
		//vec3 dir_a_f;
		//if (dot_value > 0) //法向夹角小于90度、同向取负
		//{
		//	dir_a_f = dot_value * sin(tcRadians(ls_a)) * (-tcZ(3));
		//}
		//else
		//{	//球头部分轴向向量朝下，之前朝上，改 11.27
		//	dir_a_f = dot_value * sin(tcRadians(ls_a)) * (-tcZ(3));
		//}

		//vec3 dir_r = { base_rx_qiu.P(i)(0), base_rx_qiu.P(i)(1) ,0 };//朝外
		//dir_r = normalise(dir_r);
		//vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * (-dir_r);
		//dir_a_f = normalise(dir_a_f);
		//dir_d_f = normalise(dir_d_f);
		//vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴

		//G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_qiu.nX(i)));

		//vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		//三个向量叠加，后角在法向上不够，改为绕横坐标系X轴正转出后角线--1.13
		
			double ang_zhuan = ls_d + ls_a;
			vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
			vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_qiu.nX(i)));
			vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴
		


		vec3 ls_p = base_rx_qiu.P(i);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_1.col(i) = ans;
	}

	//刃线横坐标系系右乘绕x旋转 后角)，取y向量为后角线
	//螺旋部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_d_luo);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		//球头不能直接转，螺旋可以，不然会存在夹角--1.9zy
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
		vec3 G_X_HDM = -G_SYS_HDM.col(0);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hdm_1.col(i + p_num1) = ans;
	}
	//后刀面点计算正确，8.21检查
	mat test_hdm = base_hdm_1.submat(0, 0, 2, p_num1 + p_num2 - 1);
	test_hdm = test_hdm.t();
	test_hdm.save(R"(yan_hdm-11.20.txt)", raw_ascii);
#pragma endregion

#pragma region 后刀面2

	base_hdm_2.resize(12, 0);
	base_hdm_2.insert_cols(0, p_num1 + p_num2);
	//qiutou部分
	delta_ang_d = (in_gg_canshu.hdm_2_d_mid - in_gg_canshu.hdm_2_d_qiu) / (1.0 * p_num1); //被提到公共参数 8.12 mark
	delta_ang_a = (in_gg_canshu.hdm_2_a_mid - in_gg_canshu.hdm_2_a_qiu) / (1.0 * p_num1);
	for (int i = 0; i < p_num1; i++)
	{
		double ls_d = in_gg_canshu.hdm_2_d_qiu + i * delta_ang_d; //从顶为0-20
		double ls_a = in_gg_canshu.hdm_2_a_qiu + i * delta_ang_a; //从顶为3-0

		mat33 ls_h_sys = base_rx_qiu.hSYS(i);

		//vec3 G_Z_HDM = normalise(-base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
		////轴向后角根据法向情况偏置--10.21
		//double dot_value = dot(G_Z_HDM, tcZ(3)); //变化规律cos，后续可能改为线性
		//vec3 dir_a_f;
		//if (dot_value > 0) //法向夹角小于90度、同向取负
		//{
		//	dir_a_f = dot_value * sin(tcRadians(ls_a)) * (-tcZ(3));
		//}
		//else
		//{	//球头部分轴向向量朝下，之前朝上，改 11.27
		//	dir_a_f = dot_value * sin(tcRadians(ls_a)) * (-tcZ(3));
		//}

		//vec3 dir_r = { base_rx_qiu.P(i)(0), base_rx_qiu.P(i)(1) ,0 };//朝外
		//dir_r = normalise(dir_r);
		//vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * (-dir_r);
		//dir_a_f = normalise(dir_a_f);
		//dir_d_f = normalise(dir_d_f);
		//vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴

		//G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_qiu.nX(i)));

		//vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		//三个向量叠加，后角在法向上不够，改为绕横坐标系X轴正转出后角线--1.13
		
			double ang_zhuan = ls_d + ls_a;
			vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
			vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_qiu.nX(i)));
			vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴
		

		vec3 ls_p = base_rx_qiu.P(i);
		//往y轴偏移后刀面1的宽度
		vec hdm1_Y = base_hdm_1.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * normalise(hdm1_Y);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_2.col(i) = ans;
	}

	//点的法向：刃线横坐标系右乘绕x旋转 后角)，取y向量
	//螺旋槽部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_2_d_luo);
		//往后刀面1的y轴偏移后刀面1的宽度
		vec hdm1_Y = base_hdm_1.submat(6, i + p_num1, 8, i + p_num1); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;

		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
		vec3 G_X_HDM = -G_SYS_HDM.col(0);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hdm_2.col(i + p_num1) = ans;
	}

	//mat test_hdm2 = base_hdm_2.submat(0, 0, 2, p_num1 + p_num2 - 1);
	//test_hdm2 = test_hdm2.t();
	//test_hdm2.save(R"(test_hdm2-11.21.txt)", raw_ascii);
#pragma endregion

#pragma region 后刀面3

	base_hdm_3.resize(12, 0);
	base_hdm_3.insert_cols(0, p_num1 + p_num2);
	//qiutou部分
	delta_ang_d = (in_gg_canshu.hdm_3_d_mid - in_gg_canshu.hdm_3_d_qiu) / (1.0 * p_num1); //被提到公共参数 8.12 mark
	delta_ang_a = (in_gg_canshu.hdm_3_a_mid - in_gg_canshu.hdm_3_a_qiu) / (1.0 * p_num1);
	for (int i = 0; i < p_num1; i++)
	{
		double ls_d = in_gg_canshu.hdm_3_d_qiu + i * delta_ang_d; //从顶为0-10
		double ls_a = in_gg_canshu.hdm_3_a_qiu + i * delta_ang_a; //从顶为3-0

		vec3 G_Z_HDM = normalise(-base_rx_qiu.hSYS(i).col(2)); //横坐标系的z轴
		//轴向后角根据法向情况偏置--10.21
		double dot_value = dot(G_Z_HDM, tcZ(3));
		vec3 dir_a_f;
		if (dot_value > 0) //法向夹角小于90度、同向取负
		{
			dir_a_f = dot_value * sin(tcRadians(ls_a)) * (-tcZ(3));
		}
		else
		{
			dir_a_f = dot_value * sin(tcRadians(ls_a)) * tcZ(3);
		}

		vec3 dir_r = { base_rx_qiu.P(i)(0), base_rx_qiu.P(i)(1) ,0 };//朝外
		dir_r = normalise(dir_r);
		vec3 dir_d_f = dot(G_Z_HDM, dir_r) * sin(tcRadians(ls_d)) * (-dir_r);

		vec3 G_Y_HDM = normalise(dir_a_f + dir_d_f + base_rx_qiu.hSYS(i).col(1)); //y轴
		G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_qiu.nX(i)));

		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		vec3 ls_p = base_rx_qiu.P(i);
		//往y轴偏移后刀面2的宽度
		vec hdm2_Y = base_hdm_2.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_2_width * hdm2_Y;

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_3.col(i) = ans;
	}

	//点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
	//螺旋槽部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_3_d_luo);
		//往y轴偏移后刀面2的宽度
		vec hdm2_Y = base_hdm_2.submat(6, i + p_num1, 8, i + p_num1); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_2_width * hdm2_Y;

		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hdm_3.col(i + p_num1) = ans;
	}
#pragma endregion
}


Ren_data_D_PD::Ren_data_D_PD()
{
}

Ren_data_D_PD::~Ren_data_D_PD()
{
}

void Ren_data_D_PD::cal_base_hdm123(CanShu_PD_GongGong& in_gg_canshu)
{
#pragma region 后刀面1
	//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X, 
	int p_num1 = base_rx_hen.get_p_num();
	int p_num2 = base_rx_luo.get_p_num();
	base_hen_hdm_1.resize(12, 0);
	base_hen_hdm_1.insert_cols(0, p_num1);
	base_luo_hdm_1.resize(12, 0);
	base_luo_hdm_1.insert_cols(0, p_num2);
	//hengren部分
	for (int i = 0; i < p_num1; i++)
	{
		vec3 ls_p = base_rx_hen.P(i);
		mat G_SYS_HDM = base_rx_hen.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_a_hen);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_hen.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hen_hdm_1.col(i) = ans;
	}

	//刃线横坐标系系右乘绕x旋转 后角)，取y向量为后角线
	//螺旋部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_d_luo);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_luo_hdm_1.col(i) = ans;
	}
	//后刀面点计算正确，8.21检查
	//mat test_hdm = base_hdm_1.submat(0, 0, 2, p_num1 + p_num2 - 1);
	//test_hdm = test_hdm.t();
	//test_hdm.save(R"(yan_hdm-11.20.txt)", raw_ascii);
#pragma endregion

#pragma region 后刀面2

	base_hen_hdm_2.resize(12, 0);
	base_hen_hdm_2.insert_cols(0, p_num1);
	base_luo_hdm_2.resize(12, 0);
	base_luo_hdm_2.insert_cols(0, p_num2);
	//hengren部分
	for (int i = 0; i < p_num1; i++)
	{
		vec3 ls_p = base_rx_hen.P(i);
		mat G_SYS_HDM = base_rx_hen.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_2_a_hen);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_hen.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		//往y轴偏移后刀面1的宽度
		vec hdm1_Y = base_hen_hdm_1.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * normalise(hdm1_Y);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hen_hdm_2.col(i) = ans;
	}

	//点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
	//螺旋槽部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_2_d_luo);
		//往后刀面1的y轴偏移后刀面1的宽度
		vec hdm1_Y = base_luo_hdm_1.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;

		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_luo_hdm_2.col(i) = ans;
	}

	//mat test_hdm2 = base_hdm_2.submat(0, 0, 2, p_num1 + p_num2 - 1);
	//test_hdm2 = test_hdm2.t();
	//test_hdm2.save(R"(test_hdm2-11.21.txt)", raw_ascii);
#pragma endregion

#pragma region 后刀面3

	base_hen_hdm_3.resize(12, 0);
	base_hen_hdm_3.insert_cols(0, p_num1);
	base_luo_hdm_3.resize(12, 0);
	base_luo_hdm_3.insert_cols(0, p_num2);
	//hengren部分
	for (int i = 0; i < p_num1; i++)
	{
		vec3 ls_p = base_rx_hen.P(i);
		mat G_SYS_HDM = base_rx_hen.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_3_a_hen);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_hen.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		//往y轴偏移后刀面2的宽度
		vec hdm2_Y = base_hen_hdm_2.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_2_width * hdm2_Y;

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hen_hdm_3.col(i) = ans;
	}

	//点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
	//螺旋槽部分
	for (int i = 0; i < p_num2; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_3_d_luo);
		//往y轴偏移后刀面2的宽度
		vec hdm2_Y = base_luo_hdm_2.submat(6, i, 8, i); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_2_width * hdm2_Y;

		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_luo_hdm_3.col(i) = ans;
	}
#pragma endregion
}

void Ren_data_D_PD::cal_base_duan_cao(CanShu_PD_GongGong& in_gg_canshu, int in_ren_index)
{
	////计算端齿槽-单位坐标系中计算
	//double ls_R = in_gg_canshu.D_qiu;
	////两个角度决定圆弧转角
	//double ang_cao = in_gg_canshu.v_ang_duan_cao[in_ren_index];
	//double higt_cao = in_gg_canshu.v_higt_duan_cao[in_ren_index];

	//vec3 o_p = { ls_R,0.0, -higt_cao };
	//vec3 fangxiang = tcX(3) * tcRotY(3, 90 - ang_cao);
	//vec3 cal_p = o_p;
	//
	//mat ans_p; //指向刀尖
	//deque<mat33> ans_sys;

	//ans_p.insert_cols(ans_p.n_cols, cal_p);
	//while (o_p(2) < 0) //限制高度点
	//{
	//	cal_p = cal_p + fangxiang * 0.1;
	//	ans_p.insert_cols(ans_p.n_cols, cal_p);

	//	vec y_sys = { 0.0,1.0,0.0 };
	//	vec z_sys = { cal_p(0), 0.0, cal_p(2) };
	//	z_sys = normalise(z_sys);
	//	vec x_sys = normalise(tc_cross(y_sys, z_sys));

	//	mat33 cal_sys = { {x_sys(0),y_sys(0),z_sys(0)} ,
	//					 {x_sys(1),y_sys(1),z_sys(1)} ,
	//					 {x_sys(2),y_sys(2),z_sys(2)} };
	//	ans_sys.push_back(cal_sys);
	//}

	//test
	//mat test_djjx2 = ans_p.t();
	//test_djjx2.save(R"(test_djjx_2-12.3.txt)", raw_ascii);


	//test
	//mat test_djjx = base_p_djjx.t();
	//test_djjx.save(R"(test_djjx-11.27.txt)", raw_ascii);

}

void Ren_data_D_PD::cal_base_djjx(CanShu_PD_GongGong& in_gg_canshu, double in_pos_ang)
{
	//计算刀尖间隙-单位坐标系中计算
	//double ls_R = in_gg_canshu.djjx_R;
	////两个角度决定圆弧转角
	//double ang_start = in_gg_canshu.djjx_ang_down;
	//double ang_end = 90.0 - in_gg_canshu.djjx_ang_up;

	//vec3 o_p = { ls_R,0.0,0.0 };
	//vec3 cal_p = o_p;
	//double rotate_ang = ang_start;
	//mat ans_p; //指向刀尖
	//deque<mat33> ans_sys;
	//KongJianXian ans_line;



	////圆弧部分
	//while (rotate_ang < ang_end) //限制高度点
	//{
	//	cal_p = tcRotY(3, -rotate_ang) * o_p;
	//	ans_p.insert_cols(ans_p.n_cols, cal_p);

	//	vec y_sys = { 0.0,1.0,0.0 };
	//	vec z_sys = { cal_p(0), 0.0, cal_p(2) };
	//	z_sys = normalise(z_sys);
	//	vec x_sys = normalise(tc_cross(y_sys, z_sys));

	//	mat33 cal_sys = { {x_sys(0),y_sys(0),z_sys(0)} ,
	//					 {x_sys(1),y_sys(1),z_sys(1)} ,
	//					 {x_sys(2),y_sys(2),z_sys(2)} };
	//	ans_sys.push_back(cal_sys);

	//	rotate_ang = rotate_ang + 1.0;
	//}


	////下端直线
	//vec3 v_down = normalise(ans_p.col(1) - ans_p.col(0));
	//mat33 sys_down = ans_sys.at(0);
	//double delta_dis = norm(ans_p.col(1) - ans_p.col(0));
	//double dis_all = ls_R / cos(tcRadians(in_gg_canshu.djjx_ang_down));
	//int count_p = dis_all / delta_dis;

	//for (int i = 0; i < count_p; i++)
	//{
	//	cal_p = ans_p.col(0) + v_down * i * delta_dis;
	//	ans_p.insert_cols(0, cal_p);

	//	ans_sys.push_front(sys_down);
	//}

	////上端直线
	//vec3 v_up = normalise(ans_p.col(ans_p.n_cols - 2) - ans_p.col(ans_p.n_cols - 1));
	//mat33 sys_up = ans_sys.at(ans_sys.size() - 1);
	//dis_all = ls_R / cos(tcRadians(in_gg_canshu.djjx_ang_up));
	//count_p = dis_all / delta_dis;

	//for (int i = 0; i < count_p; i++)
	//{
	//	cal_p = ans_p.col(ans_p.n_cols - 1) + v_up * i * delta_dis;
	//	ans_p.insert_cols(ans_p.n_cols, cal_p);

	//	ans_sys.push_back(sys_up);
	//}

	////线旋转-绕圆弧中间点旋转，提供三个转轴,
	//vec3 p_mid = ans_p.col(ans_p.n_cols / 2); //可以提供选择参考点的接口在前端，todo：
	//mat33 sys_mid = ans_sys[ans_sys.size() / 2];//直接取中间位置的坐标系, 参考后刀面坐标系
	//mat33 sys_rotate_line = tcRotX(3, in_gg_canshu.djjx_ang_x)
	//	* tcRotY(3, in_gg_canshu.djjx_ang_y) * tcRotZ(3, in_gg_canshu.djjx_ang_z);
	//for (int i = 0; i < ans_p.n_cols; i++)
	//{
	//	//平移到原点，旋转后，复位
	//	ans_p.col(i) = sys_rotate_line * (ans_p.col(i) - p_mid) + p_mid;
	//	ans_sys[i] = sys_rotate_line * ans_sys[i];
	//}

	////test
	////mat test_djjx2 = ans_p.t();
	////test_djjx2.save(R"(test_djjx_2-12.3.txt)", raw_ascii);

	////偏移坐标系
	//mat33 sys_trans = eye(3, 3) * tcRotX(3, 180.0);

	////放到工件坐标系
	//vec pianzhi = { -in_gg_canshu.djjx_pianzhi_x, -in_gg_canshu.djjx_pianzhi_y, -in_gg_canshu.djjx_pianzhi_z };
	//for (int i = 0; i < ans_p.n_cols; i++)
	//{
	//	ans_p.col(i) = sys_trans * ans_p.col(i) + pianzhi;
	//	ans_sys[i] = sys_trans * ans_sys[i];

	//	//工件坐标系中旋转对应位置
	//	ans_p.col(i) = tcRotZ(3, in_pos_ang) * ans_p.col(i);
	//	ans_sys[i] = tcRotZ(3, in_pos_ang) * ans_sys[i];
	//}

	//base_p_djjx = ans_p;
	//for (int i = 0; i < ans_sys.size(); i++)
	//{
	//	base_sys_djjx.push_back(ans_sys[i]);
	//}


	//test
	//mat test_djjx = base_p_djjx.t();
	//test_djjx.save(R"(test_djjx-11.27.txt)", raw_ascii);
}

void Miller_D_PD::get_dengfen_ang(vector<double>& in_v_ang)
{
	for (int i = 0; i < 6; i++)
	{
		in_v_ang.push_back(canshu_gg.v_no_dengfen_angle[i]);
	}
}

void Miller_D_PD::get_renxian_of_hen(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_hen;
}

void Miller_D_PD::get_renxian_of_luo(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo;
}

void Miller_D_PD::get_renxian_of_hen_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_hen_cao;
}

void Miller_D_PD::get_renxian_of_luo_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo_cao;
}

int Miller_D_PD::get_renxian_of_hen_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_hen.get_p_num();
}

int Miller_D_PD::get_renxian_of_luo_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_luo.get_p_num();
}

void Miller_D_PD::get_hen_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hen_hdm_1;
}

void Miller_D_PD::get_hen_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hen_hdm_2;
}

void Miller_D_PD::get_hen_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hen_hdm_3;
}

void Miller_D_PD::get_luo_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_luo_hdm_1;
}

void Miller_D_PD::get_luo_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_luo_hdm_2;
}

void Miller_D_PD::get_luo_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_luo_hdm_3;
}

Ren_data_D_R::Ren_data_D_R()
{
}

Ren_data_D_R::~Ren_data_D_R()
{
}

void Ren_data_D_R::cal_base_hdm123(CanShu_R_GongGong& in_gg_canshu)
{
	//将三段刃线有序拼接成一根、25.3.27
	//横刃剪切尾部、圆角线需要反向并下降与相切横刃 --不需要3.31
	//横刃切掉后最后点高度，圆角线插值降到0，保证和螺旋线相切
	//圆角线后角，由横刃到螺旋后角插值

	//准备三段线对应访问个数
	int count_p_hen = base_rx_hen.get_p_num();
	int count_p_rrr = base_rx_rrr.get_p_num();
	int count_p_luo = base_rx_luo.get_p_num();

	double p_delta_dis = base_rx_hen.Distance_of_Point;
	int count_p_cut = in_gg_canshu.R_qiu / p_delta_dis;
	count_p_hen = count_p_hen - count_p_cut;
	//切螺旋线
	p_delta_dis = base_rx_luo.Distance_of_Point;
	int count_p_cut_luo = in_gg_canshu.R_qiu / p_delta_dis;

#pragma region 后刀面1
	//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X, 
	base_hdm_1.reset();
	//横刃部分
	for (int i = 0; i < count_p_hen; i++)
	{
		mat33 ls_h_sys = base_rx_hen.hSYS(i);

		double ang_zhuan = in_gg_canshu.hdm_1_a_hen;
		vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_hen.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		vec3 ls_p = base_rx_hen.P(i);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_1.insert_cols(base_hdm_1.n_cols, ans);
	}

	//圆角部分
	vec end_p = base_rx_hen.P(count_p_hen - 1);
	//double z_delta = abs(end_p(2)) / count_p_rrr;
	double zhuan_delta = (in_gg_canshu.hdm_1_a_hen - in_gg_canshu.hdm_1_d_luo) / count_p_rrr;
	for (int i = 0; i < count_p_rrr; i++)
	{
		mat33 ls_h_sys = base_rx_rrr.hSYS(i);

		double ang_zhuan = in_gg_canshu.hdm_1_a_hen + zhuan_delta * i;
		vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_rrr.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		vec3 ls_p = base_rx_rrr.P(i);
		//ls_p(2) = ls_p(2) - abs(end_p(2)) + i * z_delta;

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_1.insert_cols(base_hdm_1.n_cols, ans);
	}

	//螺旋部分
	for (int i = count_p_cut_luo; i < count_p_luo; i++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_d_luo);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		//球头不能直接转，螺旋可以，不然会存在夹角--1.9zy
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
		vec3 G_X_HDM = -G_SYS_HDM.col(0);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hdm_1.insert_cols(base_hdm_1.n_cols, ans);
	}
	//后刀面点计算正确，8.21检查
	mat test_hdm = base_hdm_1.submat(0, 0, 2, base_hdm_1.n_cols-1);
	test_hdm = test_hdm.t();
	test_hdm.save(R"(yan_hdm-3.27.txt)", raw_ascii);
#pragma endregion

#pragma region 后刀面2

	base_hdm_2.reset();
	int index_hdm1 = 0; //增加索引后刀面的，3.28
	//横刃部分
	for (int i = 0; i < count_p_hen; i++, index_hdm1++)
	{
		mat33 ls_h_sys = base_rx_hen.hSYS(i);

		double ang_zhuan = in_gg_canshu.hdm_2_a_hen;
		vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_hen.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		vec3 ls_p = base_rx_hen.P(i);
		vec hdm1_Y = base_hdm_1.submat(6, index_hdm1, 8, index_hdm1); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_2.insert_cols(base_hdm_2.n_cols, ans);
	}

	//圆角部分
	zhuan_delta = (in_gg_canshu.hdm_2_a_hen - in_gg_canshu.hdm_2_d_luo) / count_p_rrr;
	for (int i = 0; i < count_p_rrr; i++, index_hdm1++)
	{
		mat33 ls_h_sys = base_rx_rrr.hSYS(i);

		double ang_zhuan = in_gg_canshu.hdm_1_a_hen + zhuan_delta * i;
		vec3 G_Y_HDM = ls_h_sys * tcRotX(3, ang_zhuan) * tcY(3); //y轴
		vec3 G_Z_HDM = normalise(cross(G_Y_HDM, base_rx_rrr.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));//x轴

		vec3 ls_p = base_rx_rrr.P(i);
		vec hdm1_Y = base_hdm_1.submat(6, index_hdm1, 8, index_hdm1); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0) ,G_X_HDM(1) ,G_X_HDM(2),
			G_Y_HDM(0) ,G_Y_HDM(1) ,G_Y_HDM(2) ,
			G_Z_HDM(0) ,G_Z_HDM(1) ,G_Z_HDM(2) };
		base_hdm_2.insert_cols(base_hdm_2.n_cols, ans);
	}

	//螺旋部分
	for (int i = count_p_cut_luo; i < count_p_luo; i++, index_hdm1++)
	{
		vec3 ls_p = base_rx_luo.P(i);
		vec hdm1_Y = base_hdm_1.submat(6, index_hdm1, 8, index_hdm1); //取出Y轴
		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;

		mat G_SYS_HDM = base_rx_luo.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_d_luo);
		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
		//球头不能直接转，螺旋可以，不然会存在夹角--1.9zy
		vec3 G_Y_HDM = G_SYS_HDM.col(1);
		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
		vec3 G_X_HDM = -G_SYS_HDM.col(0);

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
		base_hdm_2.insert_cols(base_hdm_2.n_cols, ans);
	}

	//mat test_hdm2 = base_hdm_2.submat(0, 0, 2, p_num1 + p_num2 - 1);
	//test_hdm2 = test_hdm2.t();
	//test_hdm2.save(R"(test_hdm2-11.21.txt)", raw_ascii);
#pragma endregion
}

void Miller_D_R::get_renxian_of_hen(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_hen;
}

void Miller_D_R::get_renxian_of_rrr(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_rrr;
}

void Miller_D_R::get_renxian_of_luo(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo;
}

void Miller_D_R::get_renxian_of_hen_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_hen_cao;
}

void Miller_D_R::get_renxian_of_luo_cao(int in_ren_pos_num, Cal_RenXian& ans_renxian)
{
	ans_renxian = v_base_Ren_data[in_ren_pos_num].base_rx_luo_cao;
}

int Miller_D_R::get_renxian_of_hen_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_hen.get_p_num();
}

int Miller_D_R::get_renxian_of_rrr_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_rrr.get_p_num();
}

int Miller_D_R::get_renxian_of_luo_count_p(int in_ren_pos_num)
{
	return v_base_Ren_data[in_ren_pos_num].base_rx_luo.get_p_num();
}

void Miller_D_R::get_hdm_1(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_1;
}

void Miller_D_R::get_hdm_2(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_2;
}

void Miller_D_R::get_hdm_3(int in_ren_pos_num, mat& data_hdm)
{
	data_hdm = v_base_Ren_data[in_ren_pos_num].base_hdm_3;
}

Ren_data_D_CX::Ren_data_D_CX()
{
}

Ren_data_D_CX::~Ren_data_D_CX()
{
}

void Ren_data_D_CX::cal_base_hdm123(CanShu_CX_GongGong& in_gg_canshu)
{
//#pragma region 后刀面1
//	//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X, 
//	int p_num1 = base_rx_hdm.get_p_num();
//	base_hdm_1.resize(12, 0);
//	base_hdm_1.insert_cols(0, p_num1);
//
//	//刃线横坐标系系右乘绕x旋转 后角)，取y向量为后角线
//	//柱面部分
//	for (int i = 0; i < p_num1; i++)
//	{
//		vec3 ls_p = base_rx_hdm.P(i);
//		mat G_SYS_HDM = base_rx_hdm.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_1_d_luo);
//		//用横坐标系，  G_Z_HDM =  -hSYS_Z , G_Y_HDM = hSYS_Y, G_X_HDM = -hSYS_X,  ---8.30 mark
//		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
//		//球头不能直接转，螺旋可以，不然会存在夹角--1.9zy
//		vec3 G_Y_HDM = G_SYS_HDM.col(1);
//		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
//		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
//		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
//		vec3 G_X_HDM = -G_SYS_HDM.col(0);
//
//		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
//			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
//			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
//			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
//		base_hdm_1.col(i) = ans;
//	}
//	//后刀面点计算正确，8.21检查
//	//mat test_hdm = base_hdm_1.submat(0, 0, 2, p_num1 + p_num2 - 1);
//	//test_hdm = test_hdm.t();
//	//test_hdm.save(R"(yan_hdm-11.20.txt)", raw_ascii);
//#pragma endregion
//
//#pragma region 后刀面2
//
//	base_hdm_2.resize(12, 0);
//	base_hdm_2.insert_cols(0, p_num1);
//
//	//点的法向：刃线横坐标系右乘绕x旋转 后角)，取y向量
//	//螺旋槽部分
//	for (int i = 0; i < p_num1; i++)
//	{
//		vec3 ls_p = base_rx_hdm.P(i);
//		mat G_SYS_HDM = base_rx_hdm.hSYS(i) * tcRotX(3, in_gg_canshu.hdm_2_d_luo);
//		//往后刀面1的y轴偏移后刀面1的宽度
//		vec hdm1_Y = base_hdm_1.submat(6, i + p_num1, 8, i + p_num1); //取出Y轴
//		ls_p = ls_p + in_gg_canshu.hdm_1_width * hdm1_Y;
//
//		//后刀面坐标系不能直接用转过的坐标系，用Y轴算其他两个轴-10.18
//		vec3 G_Y_HDM = G_SYS_HDM.col(1);
//		/*vec3 G_Z_HDM = normalise( cross(G_Y_HDM, base_rx_luo.nX(i)));
//		vec3 G_X_HDM = normalise(cross(G_Y_HDM, G_Z_HDM));*/
//		vec3 G_Z_HDM = -G_SYS_HDM.col(2);
//		vec3 G_X_HDM = -G_SYS_HDM.col(0);
//
//		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
//			G_X_HDM(0),  G_X_HDM(1),  G_X_HDM(2),
//			G_Y_HDM(0),  G_Y_HDM(1),  G_Y_HDM(2),
//			G_Z_HDM(0),  G_Z_HDM(1),  G_Z_HDM(2) };
//		base_hdm_2.col(i) = ans;
//	}
//
//	//mat test_hdm2 = base_hdm_2.submat(0, 0, 2, p_num1 + p_num2 - 1);
//	//test_hdm2 = test_hdm2.t();
//	//test_hdm2.save(R"(test_hdm2-11.21.txt)", raw_ascii);
//#pragma endregion
}
