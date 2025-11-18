
#define Prog_Manager_EXPORTS
#include "zi_JC_P_tance_3_axis.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

zi_JC_P_tance_3_axis::zi_JC_P_tance_3_axis(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_zi(father, nc_var_type)
{
	//01 程序变量
	name = 6492;
	//02 输入参数 分配变量
	tc_JC_P_in.replace(new_BL_Vec());
	tc_JC_N_in.replace(new_BL_Vec());
	tc_A_in.replace(new_BL_Block());
	tc_C_in.replace(new_BL_Block());
	tc_safe_plane_in.replace(new_BL_Block());

	//03 输出参数 分配变量
	tc_JC_P_out.replace(new_BL_Vec());
}

void zi_JC_P_tance_3_axis::prog_main()
{
	detectP(tc_JC_P_in, tc_JC_N_in, tc_A_in, tc_C_in, tc_safe_plane_in,
		tc_JC_P_out);
}

nc_block configure_the_craft()
{
	nc_block entr(Process_K(0));
	//配置工艺全局安全点
	entr << set_safe_x_abs(100.0);
	entr << set_safe_y_abs(80.0);
	entr << set_safe_z_abs(60.0);
	//配置探测局部安全平面
	entr << set_safe_plane_x(50.0);
	entr << set_safe_plane_y(50.0);
	entr << set_safe_plane_z(50.0);
	return entr;
}


//探测程序需要的变量******************************************************//
nc_block tan_probe_r;
nc_block tan_f_fast;
nc_block tan_f_middle;
nc_block tan_f_slow;
nc_block tan_dis_start;
nc_block tan_dis_more;
nc_block_vec3 tan_targ_P;
nc_block_vec3 tan_ans_xyz_ready;//到达粗探开始位置
nc_block_vec3 tan_ans_xyz_target;
nc_block_vec3 tan_ans_xyz_precise;
nc_block tan_error_probe;
nc_block tan_an;
nc_block tan_cn;
nc_block_vec3 dir_Y;
nc_block_vec3 dir_X;
nc_block_vec3 dir_Z;

nc_block zi_JC_P_tance_3_axis::diaoyong(nc_block_vec3& tc_JC_P, nc_block_vec3& tc_JC_N, nc_block& tc_A, nc_block& tc_C, nc_block& tc_safe_plane, nc_block_vec3& ans_tc_JC_P)
{
	nc_block ans_block(Process_K(0));
	{
		//1 分配内存
		// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_apply.diaoyong(count_all);
		//取分配结果
		//2 传参
		ans_block << (tc_JC_P_in = diaoyong_BL_bianhuan(tc_JC_P));
		ans_block << (tc_JC_N_in = diaoyong_BL_bianhuan(tc_JC_N));
		ans_block << (tc_A_in = diaoyong_BL_bianhuan(tc_A));
		ans_block << (tc_C_in = diaoyong_BL_bianhuan(tc_C));
		ans_block << (tc_safe_plane_in = diaoyong_BL_bianhuan(tc_safe_plane));

		//3 转跳
		ans_block << M98(entrance, name);
		//4 传参
		ans_block << (diaoyong_BL_bianhuan(ans_tc_JC_P) = tc_JC_P_out);
		//5 回收
		// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_release.diaoyong(count_all, n_of_a_range, this_prog_start_pos);
	}
	return ans_block;
}

nc_block zi_JC_P_tance_3_axis::detectP(nc_block_vec3 p, nc_block_vec3 n, nc_block an, nc_block cn, nc_block safe_plane, nc_block_vec3 ans_p)
{
	nc_block entr(Process_K(0));
	// 开始
	entr << G56();
	entr << G90();
	//设定内部变量
	entr << (tan_probe_r = get_probe_r());
	entr << (tan_f_fast = 6000.0);
	entr << (tan_f_middle = 200.0);
	entr << (tan_f_slow = 60.0);
	entr << (tan_dis_start = 5.0);
	entr << (tan_dis_more = 5.0);
	//旋转A/C轴
	entr << G01_A_F(an, tan_f_fast);
	entr << G01_C_F(cn, tan_f_fast);

	//移动到局部安全位置
	entr << (tan_targ_P = p);
	entr << detectArriveLocalSafe(tan_targ_P, safe_plane);

	//探测
	entr << (tan_ans_xyz_ready = (tan_targ_P + (tan_dis_start + tan_probe_r) * n));
	entr << G01_X_Y_Z_F(tan_ans_xyz_ready(0), tan_ans_xyz_ready(1), tan_ans_xyz_ready(2), tan_f_fast);
	entr << WAIT();
	entr << detectShake();//消隙
	entr << (tan_ans_xyz_target = tan_targ_P - (tan_dis_more)*n + tan_probe_r * n);
	entr << G31_X_Y_Z_F(tan_ans_xyz_target(0), tan_ans_xyz_target(1), tan_ans_xyz_target(2), tan_f_middle);//粗探
	entr << WAIT();
	entr << (tan_ans_xyz_precise = 1.0 * n);
	nc_block process_jingtan(Process_K(0));
	process_jingtan << G91();
	process_jingtan << G01_X_Y_Z_F(tan_ans_xyz_precise(0), tan_ans_xyz_precise(1), tan_ans_xyz_precise(2), tan_f_slow);
	process_jingtan << WAIT();
	process_jingtan << G90();
	process_jingtan << G31_X_Y_Z_F(tan_ans_xyz_target(0), tan_ans_xyz_target(1), tan_ans_xyz_target(2), tan_f_slow);
	process_jingtan << WAIT();
	process_jingtan << G01_X_Y_Z_F(tan_ans_xyz_ready(0), tan_ans_xyz_ready(1), tan_ans_xyz_ready(2), tan_f_fast);
	nc_block process_zhongduan(Process_K(0));
	process_zhongduan << M00();
	process_zhongduan << WAIT();
	//process_zhongduan << comment("探测异常！粗探未探到。");
	entr << IF_ELSE_K(tance_done() > 0.99, process_jingtan, process_zhongduan);

	//返回安全平面
	entr << detectBackLocalSafe(safe_plane);

	//补偿误差
	entr << detectCompensateError(n, tan_error_probe);

	//输出结果
	entr << (ans_p(0) = inner_X_coorAbs() + tan_error_probe * n(0) - tan_probe_r * n(0));
	entr << (ans_p(1) = inner_Y_coorAbs() + tan_error_probe * n(1) - tan_probe_r * n(1));
	entr << (ans_p(2) = inner_Z_coorAbs() + tan_error_probe * n(2) - tan_probe_r * n(2));

	return entr;
}

inline nc_block zi_JC_P_tance_3_axis::detectShake()
{
	nc_block entr(Process_K(0));
	double speed_pingdong = 500.0;
	double speed_zhuandong = 200.0;
	entr << G91();
	entr << (G01_X_F(0.05, speed_pingdong));
	entr << (G01_X_F(-0.05, speed_pingdong));
	entr << (G01_Y_F(0.05, speed_pingdong));
	entr << (G01_Y_F(-0.05, speed_pingdong));
	entr << (G01_Z_F(0.05, speed_pingdong));
	entr << (G01_Z_F(-0.05, speed_pingdong));
	entr << (G01_A_F(0.1, speed_zhuandong));
	entr << (G01_A_F(-0.1, speed_zhuandong));
	entr << (G01_C_F(0.05, speed_zhuandong));
	entr << (G01_C_F(-0.05, speed_zhuandong));
	entr << G90();
	return entr;
}

inline nc_block zi_JC_P_tance_3_axis::detectCompensateError(nc_block_vec3 targ_n, nc_block error_probe)
{
	nc_block entr(Process_K(0));
	entr << (dir_X = tcX(3));
	entr << (dir_Y = tcY(3));
	entr << (dir_Z = tcZ(3));
	entr << IF_K(dot(targ_n, dir_X) > 0.99, error_probe = 0.175);
	entr << IF_K(dot(targ_n, dir_Y) > 0.99, error_probe = -0.008);
	entr << IF_K(dot(targ_n, dir_Z) > 0.99, error_probe = 0.122);
	entr << (error_probe = 0.0);
	return entr;
}

inline nc_block zi_JC_P_tance_3_axis::detectArriveLocalSafe(nc_block_vec3 p, nc_block safe_plane)
{
	nc_block entr(Process_K(0));
	//安全状态监测
	//合格检测
	entr << IF_K((((inner_X_current() - get_M_O_A_X()) < (get_safe_plane_x() - 0.5))) && ((inner_Y_current() - get_M_O_A_Y()) < ((get_safe_plane_y() - 0.5))) && ((inner_Z_current() - get_M_O_A_Z()) < ((get_safe_plane_z() - 0.5))), M00());
	//如果开始位于X安全平面
	nc_block move_from_x_plane(Process_K(0));
	nc_block x_to_x(Process_K(0));
	x_to_x << G01_Y_F(p(1), 6000.0);
	x_to_x << G01_Z_F(p(2), 6000.0);
	nc_block x_to_y(Process_K(0));
	x_to_y << G01_Y_F(get_safe_plane_y(), 6000.0);
	x_to_y << G01_X_F(p(0), 6000.0);
	x_to_y << G01_Z_F(p(2), 6000.0);
	nc_block x_to_z(Process_K(0));
	x_to_z << G01_Z_F(get_safe_plane_z(), 6000.0);
	x_to_z << G01_X_F(p(0), 6000.0);
	x_to_z << G01_Y_F(p(1), 6000.0);
	move_from_x_plane << IF_K(safe_plane < 0.5, x_to_x);
	move_from_x_plane << IF_K((safe_plane > 0.5) && (safe_plane < 1.5), x_to_y);
	move_from_x_plane << IF_K((safe_plane > 1.5) && (safe_plane < 2.5), x_to_z);
	entr << IF_K((inner_X_current() - get_M_O_A_X()) >(get_safe_plane_x() - 0.5), move_from_x_plane);
	//如果开始位于Y安全平面
	nc_block move_from_y_plane(Process_K(0));
	nc_block y_to_x(Process_K(0));
	y_to_x << G01_X_F(get_safe_plane_x(), 6000.0);
	y_to_x << G01_Y_F(p(1), 6000.0);
	y_to_x << G01_Z_F(p(2), 6000.0);
	nc_block y_to_y(Process_K(0));
	y_to_y << G01_X_F(p(0), 6000.0);
	y_to_y << G01_Z_F(p(2), 6000.0);
	nc_block y_to_z(Process_K(0));
	y_to_z << G01_Z_F(get_safe_plane_z(), 6000.0);
	y_to_z << G01_X_F(p(0), 6000.0);
	y_to_z << G01_Y_F(p(1), 6000.0);
	move_from_y_plane << IF_K(safe_plane < 0.5, y_to_x);
	move_from_y_plane << IF_K((safe_plane > 0.5) && (safe_plane < 1.5), y_to_y);
	move_from_y_plane << IF_K((safe_plane > 1.5) && (safe_plane < 2.5), y_to_z);
	entr << IF_K((inner_Y_current() - get_M_O_A_Y()) >(get_safe_plane_y() - 0.5), move_from_y_plane);
	//如果开始位于Z安全平面
	nc_block move_from_z_plane(Process_K(0));
	nc_block z_to_x(Process_K(0));
	z_to_x << G01_X_F(get_safe_plane_x(), 6000.0);
	z_to_x << G01_Y_F(p(1), 6000.0);
	z_to_x << G01_Z_F(p(2), 6000.0);
	nc_block z_to_y(Process_K(0));
	z_to_y << G01_Y_F(get_safe_plane_y(), 6000.0);
	z_to_y << G01_X_F(p(0), 6000.0);
	z_to_y << G01_Z_F(p(2), 6000.0);
	nc_block z_to_z(Process_K(0));
	z_to_z << G01_X_F(p(0), 6000.0);
	z_to_z << G01_Y_F(p(1), 6000.0);
	move_from_z_plane << IF_K(safe_plane < 0.5, z_to_x);
	move_from_z_plane << IF_K((safe_plane > 0.5) && (safe_plane < 1.5), z_to_y);
	move_from_z_plane << IF_K((safe_plane > 1.5) && (safe_plane < 2.5), z_to_z);
	entr << IF_K((inner_Z_current() - get_M_O_A_Z()) >(get_safe_plane_z() - 0.5), move_from_z_plane);
	return entr;
}

inline nc_block zi_JC_P_tance_3_axis::detectBackLocalSafe(nc_block safe_plane)
{
	nc_block entr(Process_K(0));
	entr << IF_K(safe_plane < 0.5, G01_X_F(get_safe_plane_x(), 4000.0));
	entr << IF_K((safe_plane > 0.5) && (safe_plane < 1.5), G01_Y_F(get_safe_plane_y(), 6000.0));
	entr << IF_K((safe_plane > 1.5) && (safe_plane < 2.5), G01_Z_F(get_safe_plane_z(), 6000.0));
	return entr;
}
