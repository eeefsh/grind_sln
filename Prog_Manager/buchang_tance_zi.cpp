#include"pch.h"
#define Prog_Manager_EXPORTS

#include"buchang_tance_zi.h"
//#include <Cal_ZuoBiaoBianHuan/include/Cal_ZuoBiaoBianHuan.h>
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"


F_zi_tance_3_axis::F_zi_tance_3_axis(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_zi(father, nc_var_type)
{
	//01 程序变量
	name = 6492;
	//02 输入参数 分配变量
	tc_G5X_in.replace(new_BL_Block());
	tc_back_safe_global_in.replace(new_BL_Block());
	tc_safe_G5X_in.replace(new_BL_Block());
	tc_back_safe_local_in.replace(new_BL_Block());
	tc_need_cu_in.replace(new_BL_Block());

	tc_targ_point_in.replace(new_BL_Vec());
	tc_A_in.replace(new_BL_Block());
	tc_C_in.replace(new_BL_Block());
	tc_targ_N_in.replace(new_BL_Vec());

	tc_dis_safe_in.replace(new_BL_Block());
	tc_dis_start_in.replace(new_BL_Block());
	tc_dis_more_in.replace(new_BL_Block());

	//03 输出参数 分配变量
	tc_ans_point_out.replace(new_BL_Vec());
}

void F_zi_tance_3_axis::prog_main()
{
	// 开始
	nc_code >>  choose_G5X(tc_G5X_in);
	nc_code >>  G90();
	nc_block probe_R(new_BL_Block());
	nc_code >>  (probe_R = 1.50);
	nc_block f_fast(new_BL_Block());
	nc_code >>  (f_fast = 4000.0);
	nc_block f_middle(new_BL_Block());
	nc_code >>  (f_middle = 300.0);
	nc_block f_slow(new_BL_Block());
	nc_code >>  (f_slow = 60.0);

	//旋转A/C轴
	nc_code >>  G01_A_F(tc_A_in, f_fast);
	nc_code >>  G01_C_F(tc_C_in, f_fast);

	//判断是否先到局部安全位置
	//nc_block need_back_safe_local((tc_back_safe_local_in > 0.9));
	nc_block back_safe_local_first(Process_K(0));
	nc_block_vec3 ans_xyz_1(new_BL_Vec());
	back_safe_local_first << (ans_xyz_1 = tc_targ_point_in + (tc_dis_start_in + tc_dis_safe_in + probe_R) * tc_targ_N_in);
	back_safe_local_first << G01_X_F(ans_xyz_1(0), f_fast);
	back_safe_local_first << G01_Z_F(ans_xyz_1(2), f_fast);
	back_safe_local_first << G01_Y_F(ans_xyz_1(1), f_fast);
	nc_code >>  IF_K(tc_back_safe_local_in > 0.9, back_safe_local_first);

	//仅精探分支
	nc_block no_need_cu(abs(tc_need_cu_in) < 0.1);
	nc_block only_jing(Process_K(0));
	nc_block_vec3 ans_xyz_jing_2(new_BL_Vec());
	only_jing << (ans_xyz_jing_2 = tc_targ_point_in + (1.0 + probe_R) * tc_targ_N_in);
	only_jing << G01_X_Y_Z_F(ans_xyz_jing_2(0), ans_xyz_jing_2(1), ans_xyz_jing_2(2), f_fast);
	only_jing << xiaoxi();
	nc_block_vec3 ans_xyz_jing_3(new_BL_Vec());
	only_jing << (ans_xyz_jing_3 = tc_targ_point_in - (tc_dis_more_in)*tc_targ_N_in + probe_R * tc_targ_N_in);
	only_jing << G31_X_Y_Z_F(ans_xyz_jing_3(0), ans_xyz_jing_3(1), ans_xyz_jing_3(2), f_slow);
	only_jing << WAIT();
	only_jing << G01_X_Y_Z_F(ans_xyz_jing_2(0), ans_xyz_jing_2(1), ans_xyz_jing_2(2), f_fast);
	nc_code >>  IF_K(no_need_cu, only_jing);

	//完整探测分支
	//计算粗探开始点并到达
	nc_block need_cu((abs(tc_need_cu_in) > 0.9));
	nc_block complete_tance(Process_K(0));
	nc_block_vec3 ans_xyz_2(new_BL_Vec());//粗探开始位置
	complete_tance << (ans_xyz_2 = tc_targ_point_in + (tc_dis_start_in + probe_R) * tc_targ_N_in);
	complete_tance << G01_X_Y_Z_F(ans_xyz_2(0), ans_xyz_2(1), ans_xyz_2(2), f_fast);
	complete_tance << WAIT();

	//消隙
	complete_tance << xiaoxi();

	//计算探测目标点并粗探
	nc_block_vec3 ans_xyz_3(new_BL_Vec());//探测位置
	complete_tance << (ans_xyz_3 = tc_targ_point_in - (tc_dis_more_in)*tc_targ_N_in + probe_R * tc_targ_N_in);
	complete_tance << G31_X_Y_Z_F(ans_xyz_3(0), ans_xyz_3(1), ans_xyz_3(2), f_middle);
	complete_tance << WAIT();

	//粗探探到了？精探
	nc_block jingtan(Process_K(0));
	nc_block_vec3 ans_xyz_4(new_BL_Vec());//精探开始位置
	jingtan << (ans_xyz_4 = 1.0 * tc_targ_N_in);
	jingtan << G91();
	jingtan << G01_X_Y_Z_F(ans_xyz_4(0), ans_xyz_4(1), ans_xyz_4(2), f_middle);
	jingtan << WAIT();
	jingtan << G90();
	jingtan << G31_X_Y_Z_F(ans_xyz_3(0), ans_xyz_3(1), ans_xyz_3(2), f_slow);
	jingtan << WAIT();
	jingtan << G01_X_Y_Z_F(ans_xyz_2(0), ans_xyz_2(1), ans_xyz_2(2), f_fast);
	complete_tance << IF_K(tc_tance_done() > 0.99, jingtan);
	nc_code >>  IF_K(need_cu, complete_tance);

	//判断是否返回局部安全位置
	nc_block back_safe_local_last(Process_K(0));
	nc_block_vec3 ans_xyz_5(new_BL_Vec());//安全位置
	back_safe_local_last << (ans_xyz_5 = tc_targ_point_in + (tc_dis_start_in + tc_dis_safe_in + probe_R) * tc_targ_N_in);
	back_safe_local_last << G01_X_Y_Z_F(ans_xyz_5(0), ans_xyz_5(1), ans_xyz_5(2), f_fast);;
	back_safe_local_last << WAIT();
	nc_code >>  IF_K(tc_back_safe_local_in > 0.9, back_safe_local_last);

	//补偿误差,-两段4次曲线拟合，平均拟合
	nc_block_vec3 JC_X(new_BL_Vec());
	nc_code >>  (JC_X = tcX(3));
	nc_block_vec3 JC_Y(new_BL_Vec());
	nc_code >>  (JC_Y = tcY(3));
	nc_block theta(new_BL_Block());
	nc_code >>  Angle_from_a_to_b_around_c(tc_targ_N_in, JC_X, JC_Y, theta);
	nc_block is_neg_180_degree(theta < -179.9);
	nc_code >>  IF_K(is_neg_180_degree, theta = 180.0);
	nc_block error_probe(new_BL_Block());

	double bl_100000 = 100000;
	nc_block bl_100000_block(new_BL_Block());
	nc_code >>  (bl_100000_block = 100000.0);
	nc_block under112d((theta < 112.0));
	nc_block nihe_under_112d(Process_K(0));
	{
		nihe_under_112d << (error_probe = ((0.0000000056686422 * bl_100000 / bl_100000_block) * theta * theta * theta * theta)
			- ((0.0000012781477506 * bl_100000 / bl_100000_block) * theta * theta * theta)
			+ ((0.0001080047947901 * bl_100000 / bl_100000_block) * theta * theta)
			- ((0.0033368371263922 * bl_100000 / bl_100000_block) * theta)
			+ (0.3047719181653080 * bl_100000 / bl_100000_block));
	}
	nc_code >>  IF_K(under112d, nihe_under_112d);

	nc_block over112d((theta >= 112.0));
	nc_block nihe_over_112d(Process_K(0));
	{
		nihe_over_112d << (error_probe = ((0.0000000143437121 * bl_100000 / bl_100000_block) * theta * theta * theta * theta)
			- ((0.0000091440616700 * bl_100000 / bl_100000_block) * theta * theta * theta)
			+ ((0.0021979956572704 * bl_100000 / bl_100000_block) * theta * theta)
			- ((0.2391499988183020 * bl_100000 / bl_100000_block) * theta)
			+ (10.1950370354937000 * bl_100000 / bl_100000_block));
	}
	nc_code >>  IF_K(over112d, nihe_over_112d);

	//输出结果
	nc_code >>  (tc_ans_point_out(0) = tc_inner_X_coorAbs() + error_probe * tc_targ_N_in(0) - tc_targ_N_in(0) * probe_R);
	nc_code >>  (tc_ans_point_out(1) = tc_inner_Y_coorAbs() + error_probe * tc_targ_N_in(1) - tc_targ_N_in(1) * probe_R);
	nc_code >>  (tc_ans_point_out(2) = tc_inner_Z_coorAbs() + error_probe * tc_targ_N_in(2) - tc_targ_N_in(2) * probe_R);

	//要回安全位置？回安全位置
	nc_block back_anquan(Process_K(0));
	nc_block x_ls(new_BL_Block());
	back_anquan << (x_ls = -65.0);
	nc_block y_ls(new_BL_Block());
	back_anquan << (y_ls = -150.0);
	nc_block z_ls(new_BL_Block());
	back_anquan << (z_ls = 0.0);
	back_anquan << choose_G5X(tc_safe_G5X_in);
	back_anquan << G01_Y_F(y_ls, f_fast);
	back_anquan << G01_X_Y_Z_F(x_ls, y_ls, z_ls, f_fast);
	back_anquan << choose_G5X(tc_G5X_in);
	nc_code >>  IF_K(tc_back_safe_global_in > 0.99, back_anquan);

	//结束
	nc_code >>  M99();
}

nc_block F_zi_tance_3_axis::diaoyong(
	nc_block& tc_G5X, nc_block& tc_back_safe_global, nc_block& tc_safe_G5X, nc_block& tc_back_safe_local, nc_block& tc_need_cu,
	nc_block_vec3& tc_targ_point, nc_block& tc_A, nc_block& tc_C, nc_block_vec3& tc_targ_N,
	nc_block& tc_dis_safe, nc_block& tc_dis_start, nc_block& tc_dis_more,
	nc_block_vec3& tc_ans_point
)
{
	nc_block ans_block(Process_K(0));
	{
		//1 分配内存
	// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_apply.diaoyong(count_all);
		//取分配结果
		//2 传参
		ans_block << (tc_G5X_in = diaoyong_BL_bianhuan(tc_G5X));
		ans_block << (tc_back_safe_global_in = diaoyong_BL_bianhuan(tc_back_safe_global));
		ans_block << (tc_safe_G5X_in = diaoyong_BL_bianhuan(tc_safe_G5X));
		ans_block << (tc_back_safe_local_in = diaoyong_BL_bianhuan(tc_back_safe_local));
		ans_block << (tc_need_cu_in = diaoyong_BL_bianhuan(tc_need_cu));
		ans_block << (tc_targ_point_in = diaoyong_BL_bianhuan(tc_targ_point));
		ans_block << (tc_A_in = diaoyong_BL_bianhuan(tc_A));
		ans_block << (tc_C_in = diaoyong_BL_bianhuan(tc_C));
		ans_block << (tc_targ_N_in = diaoyong_BL_bianhuan(tc_targ_N));
		ans_block << (tc_dis_safe_in = diaoyong_BL_bianhuan(tc_dis_safe));
		ans_block << (tc_dis_start_in = diaoyong_BL_bianhuan(tc_dis_start));
		ans_block << (tc_dis_more_in = diaoyong_BL_bianhuan(tc_dis_more));

		//3 转跳
		ans_block << M98(entrance, name);
		//4 传参
		ans_block << (diaoyong_BL_bianhuan(tc_ans_point) = tc_ans_point_out);
		//5 回收
		// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_release.diaoyong(count_all, n_of_a_range, this_prog_start_pos);
	}
	return ans_block;
}

nc_block F_zi_tance_3_axis::choose_G5X(nc_block& G5X)
{
	nc_block entr(Process_K(0));
	nc_block is_G54((G5X < 0.1));
	entr << IF_K(is_G54, G54());
	nc_block is_G55(((G5X >= 0.1) && (G5X < 1.1)));
	entr << IF_K(is_G55, G55());
	nc_block is_G56(((G5X >= 1.1) && (G5X < 2.1)));
	entr << IF_K(is_G56, G56());
	nc_block is_G57(((G5X >= 2.1) && (G5X < 3.1)));
	entr << IF_K(is_G57, G57());
	nc_block is_G58(((G5X >= 3.1) && (G5X < 4.1)));
	entr << IF_K(is_G58, G58());
	nc_block is_G59(((G5X >= 4.1) && (G5X < 5.1)));
	entr << IF_K(is_G59, G59());
	return entr;
}

nc_block F_zi_tance_3_axis::xiaoxi()
{
	nc_block entr(Process_K(0));
	double speed_pingdong = 500.0;
	double speed_zhuandong = 200.0;
	entr << G91();
	entr << (G01_X_F(0.01, speed_pingdong));
	entr << (G01_X_F(-0.01, speed_pingdong));
	entr << (G01_Y_F(0.01, speed_pingdong));
	entr << (G01_Y_F(-0.01, speed_pingdong));
	entr << (G01_Z_F(0.01, speed_pingdong));
	entr << (G01_Z_F(-0.01, speed_pingdong));
	entr << (G01_A_F(0.001, speed_pingdong));
	entr << (G01_A_F(-0.001, speed_pingdong));
	entr << (G01_C_F(0.001, speed_pingdong));
	entr << (G01_C_F(-0.001, speed_pingdong));
	entr << G90();
	return entr;
}

nc_block F_zi_tance_3_axis::goto_anquan_pos_by_Y_XYZ()
{
	nc_block entr(Process_K(0));
	nc_block x_ls(new_BL_Block());
	nc_block y_ls(new_BL_Block());
	nc_block z_ls(new_BL_Block());
	nc_block a_ls(new_BL_Block());
	nc_block c_ls(new_BL_Block());
	nc_block f_ls(new_BL_Block());
	entr << WAIT();
	entr << (x_ls = 100.0);
	entr << (y_ls = 50.0);
	entr << (z_ls = 50.0);
	entr << (a_ls = 0.0);
	entr << (c_ls = -90.0);
	entr << (f_ls = 1000.0);
	entr << (G90());
	entr << G01_Y_F(y_ls, f_ls);
	entr << G01_X_Y_Z_F(x_ls, y_ls, z_ls, f_ls);
	return entr;
}

nc_block F_zi_tance_3_axis::tc_inner_X_coorMac()
{
	return BL_Block(1, 1441);
}

nc_block F_zi_tance_3_axis::tc_inner_Y_coorMac()
{
	return BL_Block(1, 1442);
}

nc_block F_zi_tance_3_axis::tc_inner_Z_coorMac()
{
	return BL_Block(1, 1443);
}

nc_block F_zi_tance_3_axis::tc_inner_A_coorMac()
{
	return BL_Block(1, 1444);
}

nc_block F_zi_tance_3_axis::tc_inner_C_coorMac()
{
	return BL_Block(1, 1445);
}

nc_block F_zi_tance_3_axis::tc_inner_X_coorAbs()
{
	return BL_Block(1, 1361);
}

nc_block F_zi_tance_3_axis::tc_inner_Y_coorAbs()
{
	return BL_Block(1, 1362);
}

nc_block F_zi_tance_3_axis::tc_inner_Z_coorAbs()
{
	return BL_Block(1, 1363);
}

nc_block F_zi_tance_3_axis::tc_inner_A_coorAbs()
{
	return BL_Block(1, 1364);
}

nc_block F_zi_tance_3_axis::tc_inner_C_coorAbs()
{
	return BL_Block(1, 1365);
}

nc_block F_zi_tance_3_axis::tc_tance_done()
{
	return BL_Block(1, 1608);
}
