#include"pch.h"
#define Prog_Manager_EXPORTS

#include "buchang_tance_fu.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"

buchang_tance_fu::buchang_tance_fu(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_fu(father, nc_var_type), zi_obj(father, nc_var_type)
{
	name = 2301 + name_fu_i;
	name_fu_i++;

	dis_safe_in = 1.0;
	dis_start_in = 10.0;
	dis_more_in = 5.0;
}

void buchang_tance_fu::prog_main()
{
	nc_code >>  M05(); //主轴停转
	nc_code >>  M09(); //冷却液关

	//nc_code >>  G01_A_F(0, 1000);
	//nc_code >>  G01_C_F(0, 1000); //计算探测的初始状态

	//准备探测运动模式
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


	nc_block tc_dis_safe_in(new_BL_Block());
	nc_block tc_dis_start_in(new_BL_Block());
	nc_block tc_dis_more_in(new_BL_Block());
	nc_code >>  (tc_dis_safe_in = dis_safe_in);
	nc_code >>  (tc_dis_start_in = dis_start_in);
	nc_code >>  (tc_dis_more_in = dis_more_in);

	//输出
	nc_block_vec3 tc_ans_point_out(new_BL_Vec());


	nc_block ans_bu(new_BL_Block());
	nc_block_vec3 tance_t(new_BL_Vec());
	nc_block dis_pan(new_BL_Block());

	nc_block_matrix33 trans_block(new_BL_Mat());
	nc_block_vec3 temp_targ_point(new_BL_Vec());
	nc_block_vec3 temp_targ_nor(new_BL_Vec());

	//根据探测点数量循环调用
	int cur_gx_type = gx_type_in;
	int count_p = v_points_in.size();
	for (int i = 0; i < count_p; i++)
	{
		//准备单个点的输入
		vec3 cur_p = v_points_in[i];
		vec3 cur_nor = v_nors_in[i];  
		double cur_A = v_A_in[i];
		double cur_C = v_C_in[i];

		nc_code >>  (tc_targ_point_in = cur_p);
		nc_code >>  (tc_targ_N_in = cur_nor);
		nc_code >>  (tc_A_in = cur_A + 90.0);
		nc_code >>  (tc_C_in = cur_C);

		nc_code >>  (trans_block = tcRotX(3, 90.0));
		nc_code >>  (temp_targ_point = trans_block * tc_targ_point_in); //临时变量中转
		nc_code >>  (temp_targ_nor = trans_block * tc_targ_N_in);

		nc_code >>  (tc_targ_point_in = temp_targ_point);
		nc_code >>  (tc_targ_N_in = temp_targ_nor);
		nc_code >>  (tc_targ_point_in(1) = tc_targ_point_in(1) + BL(1800)); //磨削原点
		//nc_code >>  (trans_block = tcRotZ(3, cur_C) * tcTranslate(, 0.0, 0.0) * tcRotY(3, cur_A + 90.0) * tcRotX(3, 90));

		nc_code >>  (trans_block = tcRotY(3, cur_A + 90.0));
		nc_code >>  (temp_targ_point = trans_block * tc_targ_point_in);
		nc_code >>  (temp_targ_nor = trans_block * tc_targ_N_in);

		nc_code >>  (tc_targ_point_in = temp_targ_point);
		nc_code >>  (tc_targ_N_in = temp_targ_nor);
		nc_code >>  (tc_targ_point_in(0) = tc_targ_point_in(0) - 0.01699);

		nc_code >>  (trans_block = tcRotZ(3, cur_C));
		nc_code >>  (temp_targ_point = trans_block * tc_targ_point_in);
		nc_code >>  (temp_targ_nor = trans_block * tc_targ_N_in);

		nc_code >>  (tc_targ_point_in = temp_targ_point); 
		nc_code >>  (tc_targ_N_in = temp_targ_nor); 

		//nc_code >>  (tc_targ_point_in(0) = tc_targ_point_in(0) + BL(1800)); 

		cur_p = tcRotX(3, 90.0) * cur_p;
		cur_nor = tcRotX(3, 90.0) * cur_nor;
		cur_p(1) = cur_p(1) + 16.0;
		cur_p = tcRotY(3, cur_A + 90.0) * cur_p;
		cur_nor = tcRotY(3, cur_A + 90.0) * cur_nor;
		cur_p(0) = cur_p(0) - 0.01699;
		cur_p = tcRotZ(3, cur_C) * cur_p;
		cur_nor = tcRotZ(3, cur_C) * cur_nor;
		

		nc_code >>  ((F_zi_tance_3_axis*)(zi_obj.target_prog))->diaoyong(
			tc_G5X_in, tc_back_safe_global_in, tc_safe_G5X_in, tc_back_safe_local_in, tc_need_cu_in,
			tc_targ_point_in, tc_A_in, tc_C_in, tc_targ_N_in,
			tc_dis_safe_in, tc_dis_start_in, tc_dis_more_in,
			tc_ans_point_out);


		//探测结果计算出补偿值
		/*
		double ans_bu = 10.0;  //初值很大，结果大说明探测有误
		vec3 tance_p = { zi_obj.tc_ans_point_out(0).block->ans_value,
						zi_obj.tc_ans_point_out(1).block->ans_value,
						zi_obj.tc_ans_point_out(2).block->ans_value,};
		vec3 tance_t = tance_p - cur_p;
				double dis_pan = dot(tance_t, cur_nor);
		if (dis_pan < 0)
		{
			ans_bu = -norm(tance_t);
		}
		else
		{
			ans_bu = norm(tance_t);
		}
		*/

		
		nc_code >>  (tance_t = tc_ans_point_out - tc_targ_point_in);
		
		nc_code >>  (dis_pan = dot(tance_t, tc_targ_N_in));

		nc_block pan_low_0(dis_pan < 0.0);
		nc_block zhuti1(Process_K(0));
		zhuti1 << (ans_bu = norm(tance_t));
		nc_block zhuti2(Process_K(0));
		zhuti2 << (ans_bu = -norm(tance_t));
		nc_code >>  IF_ELSE_K(pan_low_0, zhuti1, zhuti2);


		//写到机床对应变量
		int num_BL_pos = 0; 
		num_BL_pos = find_num_BL_pos(cur_gx_type, i);
		nc_code >>  (BL(num_BL_pos) = ans_bu);
	}
	

	nc_code >>  M99();
}

nc_block buchang_tance_fu::diaoyong()
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

void buchang_tance_fu::set_tance_dis(double in_safe, double in_start, double in_more)
{
	dis_safe_in = in_safe;
	dis_start_in = in_start;
	dis_more_in = in_more;
}

int buchang_tance_fu::find_num_BL_pos(int in_gx_type, int in_p_pos)
{
	int ans_num = 0;
	int num_start = 1950; //后续好设置--更改需要同步 find_num_BL_pos
	switch (in_gx_type)
	{
	case 0:
		ans_num = num_start + 0 + in_p_pos;
		break;
	case 1:
		ans_num = num_start + 1 + in_p_pos;
		break;
	case 2:
		ans_num = num_start + 2 + in_p_pos;
		break;

		//大多数工序不用探测补偿

	case 8:
		ans_num = num_start + 6 + in_p_pos;
		break;
	case 9:
		ans_num = num_start + 7 + in_p_pos;
		break;
	case 12:
		ans_num = num_start + 8 + in_p_pos;
		break;
	case 13:
		ans_num = num_start + 9 + in_p_pos;
		break;

	case 17:
		ans_num = num_start + 10 + in_p_pos;
		break;

	default:
		break;
	}
	return ans_num;
}


