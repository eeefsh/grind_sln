#include"pch.h"
#define Prog_Manager_EXPORTS
#include "length_tance_fu.h"

length_tance_fu::length_tance_fu(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_fu(father, nc_var_type), zi_obj(father, nc_var_type)
{
	name = 2201 + name_fu_i;
	name_fu_i++;

	dis_safe_in = 1.0;
	dis_start_in = 10.0;
	dis_more_in = 5.0;
}

void length_tance_fu::prog_main()
{
	//准备探测运动模式
	//给子程序的输入直接赋值
	//初始探测增加安全判断，没探到就中断M30
	nc_code >> (BL(1800) = 999.0);

	//补偿值变量赋初值12.25
	{
		//nc_code >>  (BL(1950) = 0.0);
		//nc_code >>  (BL(1951) = 0.0);
		//nc_code >>  (BL(1952) = 0.0);
		//nc_code >>  (BL(1953) = 0.0);
		//nc_code >>  (BL(1954) = 0.0);
		//nc_code >>  (BL(1955) = 0.0);
		//nc_code >>  (BL(1956) = 0.0);
		//nc_code >>  (BL(1957) = 0.0);
		//nc_code >>  (BL(1958) = 0.0);
		//nc_code >>  (BL(1959) = 0.0);
		//nc_code >>  (BL(1960) = 0.0);
	}

	//虚拟机检查变量值，机床实际探测该变量值小，仿真跳过探测程序
	nc_block is_fangzhen(BL(1999) > 900.0);
	nc_block no_tan(Process_K(0));
	no_tan << M99();
	nc_code >>  IF_K(is_fangzhen, no_tan);


	nc_block tc_G5X_in(new_BL_Block());
	nc_block tc_back_safe_global_in(new_BL_Block());
	nc_block tc_safe_G5X_in(new_BL_Block());
	nc_block tc_back_safe_local_in(new_BL_Block());
	nc_block tc_need_cu_in(new_BL_Block());
	nc_code >>  (tc_G5X_in = 2.0);
	nc_code >>  (tc_back_safe_global_in = 1.0);
	nc_code >>  (tc_safe_G5X_in = 3.0);
	nc_code >>  (tc_back_safe_local_in = 1.0);
	nc_code >>  (tc_need_cu_in = 1.0);

	nc_block_vec3 tc_targ_point_in(new_BL_Vec());
	nc_block tc_A_in(new_BL_Block());
	nc_block tc_C_in(new_BL_Block());
	nc_block_vec3 tc_targ_N_in(new_BL_Vec());
	nc_code >>  (tc_targ_point_in = v_points_in);
	nc_code >>  (tc_A_in = v_A_in);
	nc_code >>  (tc_C_in = v_C_in);
	nc_code >>  (tc_targ_N_in = v_nors_in);

	nc_block tc_dis_safe_in(new_BL_Block());
	nc_block tc_dis_start_in(new_BL_Block());
	nc_block tc_dis_more_in(new_BL_Block());
	nc_code >>  (tc_dis_safe_in = dis_safe_in);
	nc_code >>  (tc_dis_start_in = dis_start_in);
	nc_code >>  (tc_dis_more_in = dis_more_in);

	//输出
	nc_block_vec3 tc_ans_point_out(new_BL_Vec());


	nc_code >>  ((F_zi_tance_3_axis*)(zi_obj.target_prog))->diaoyong(
		tc_G5X_in, tc_back_safe_global_in, tc_safe_G5X_in, tc_back_safe_local_in, tc_need_cu_in,
		tc_targ_point_in, tc_A_in, tc_C_in, tc_targ_N_in,
		tc_dis_safe_in, tc_dis_start_in, tc_dis_more_in,
		tc_ans_point_out);

	//探测结果计算出补偿值
 
	//检查探测值误差值过大，不执行加工
	
	//nc_block_vec3 tance_delta(new_BL_Vec());
	//nc_code >>  (tance_delta = tc_ans_point_out - tc_targ_point_in);

	//nc_block pan_dis(abs(tance_delta(0)) > 5.0); //该条件会进？取消判断12.19
	//nc_block zhuti1(Process_K(0));
	//zhuti1 << M30();
	//zhuti1 << M00();
	//zhuti1 << WAIT();

	//nc_block zhuti2(Process_K(0));
	//zhuti2 << (BL(1800) = tc_ans_point_out(0) - v_dis_jiagong_in);//写到机床对应变量
	//zhuti2 << M00();
	//zhuti2 << WAIT();
	//nc_code >>  IF_ELSE_K(pan_dis, zhuti1, zhuti2);

	nc_code >>  (BL(1801) = tc_ans_point_out(0)); //原始探测长度值，保存，补偿探测需要12.30
	nc_code >>  (BL(1800) = tc_ans_point_out(0) - v_dis_jiagong_in);//写到机床对应变量

	//检查是否探到
	nc_block pan_tan(BL(1800) > 900.0);
	nc_block tan1(Process_K(0));
	tan1 << M00();
	tan1 << WAIT();
	tan1 << M30();
	nc_block tan2(Process_K(0));
	tan2 << (BL(1800) = tc_ans_point_out(0) - v_dis_jiagong_in);
	tan2 << M00();
	tan2 << WAIT();
	nc_code >>  IF_ELSE_K(pan_tan, tan1, tan2);

	nc_code >>  M99();
}

nc_block length_tance_fu::diaoyong()
{
	nc_block ans_block(Process_K(0));
	{
		//1 分配内存
	// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_apply.diaoyong(count_all);
		//取分配结果

		//2 传参

		//3 转跳
		ans_block << M98(entrance, name);

		//4 传参
		//不传出，所以不写

		//5 回收
		// 内存管理器为静态内存所以不写
		ans_block << manager->zi_var_manager_release.diaoyong(count_all, n_of_a_range, this_prog_start_pos);
	}
	return ans_block;
}

void length_tance_fu::set_tance_dis(double in_safe, double in_start, double in_more)
{
	dis_safe_in = in_safe;
	dis_start_in = in_start;
	dis_more_in = in_more;
}
