#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include"gx_fu.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include"manager_h/MA_010501_Cal_LeiXingZhuanHuan.h"
#include"manager_h/MA_010601_Cal_JiHe_PointSort.h"

Miller_DL_fu_prog::Miller_DL_fu_prog(nc_program_zi_fangzhichongfu* father, int nc_var_type)
	:nc_program_fu(father, nc_var_type)
{
	name = 2101 + name_fu_i;
	name_fu_i++;
}

void Miller_DL_fu_prog::prog_main()
{
	nc_code >> G90();
	nc_code >> G54();

	trans_sl_to_M06();

	//主轴正转
	nc_code >> M03();
	nc_code >> S_speed(SL_zhuansu);

	//冷却液
	nc_code >> M08();

	trans_DL_to_G01();

	//nc_code >> ((void_zi*)(zi_obj.target_prog))->diaoyong();
	nc_code >> M99();
}

void Miller_DL_fu_prog::set_gx_DL(int in_gx_type, DL* in_DL, int in_sl_pos_JC_lib, int in_sl_pos_slz,
	xt_gx_shalun& in_sl, vector<double>& in_v_fd)
{
	gx_type = in_gx_type;
	//计算砂轮转速
	double sudu_w = (1000.0 * sudu_lilun.SL_XianSuDu) / (2* in_sl.Ry + 2*in_sl.r) / datum::pi;
	SL_zhuansu = sudu_w * 60.0; 

	ptr_DL = in_DL;

	sl_pos_in_JC_lib = in_sl_pos_JC_lib;
	sl_pos_in_slz = in_sl_pos_slz;

	sl_canshul = in_sl;
	v_fd = in_v_fd;
}

void Miller_DL_fu_prog::trans_sl_to_M06()
{
	nc_code >> G01_Z_F(sl_safe_point.Z, sudu_lilun.KuaiSu);
	nc_code >> G01_X_F(sl_safe_point.X, sudu_lilun.KuaiSu);
	nc_code >> G01_Y_F(sl_safe_point.Y, sudu_lilun.KuaiSu);
	nc_code >> G01_A_F(sl_safe_point.A, sudu_lilun.KuaiSu);
	nc_code >> G01_C_F(sl_safe_point.C, sudu_lilun.KuaiSu);

	nc_code >> M06(sl_pos_in_JC_lib, sl_pos_in_slz);  //输入
}

void Miller_DL_fu_prog::trans_DL_to_G01()
{
	//double cur_sudu = jingeilv_lilun;
	double cur_sudu = sudu_lilun.MoXueJinGei;
	double cal_sudu = sudu_lilun.KuaiSu;
	
	{
		//nc_code >> G01_X_Y_Z_A_C_F(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		//nc_code >> G01_X_Y_Z_A_C_F(0.0, 0.0, 0.0, 360.0, 90.0, 0.0);
		//nc_code >> G01_X_Y_Z_A_C_F(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		//nc_code >> G01_X_Y_Z_A_C_F(0.0, 0.0, 0.0, 180.0, 90.0, 0.0);
	}

	//G54状态下的安全位置
	nc_code >> G01_A_F(gx_safe_point.A, cal_sudu);
	nc_code >> G01_C_F(gx_safe_point.C, cal_sudu);
	nc_code >> G01_Z_F(gx_safe_point.Z, cal_sudu);
	nc_code >> G01_X_F(gx_safe_point.X, cal_sudu);
	nc_code >> G01_Y_F(gx_safe_point.Y, cal_sudu);


	//写文本的参数全转为块12.5 需要指定静态变量
	nc_block X_b(BL(1901));
	nc_block Y_b(BL(1902));
	nc_block Z_b(BL(1903));

	nc_block cal_bu_b(BL(1904));
	//对于不补偿的工序，对应变量号为1949 = 0.0, 12.13
	nc_code >> (BL(1949) = 0.0);

	//只遍历刀路点
	int count_p = ptr_DL->Data.size();

	//阵列等于多调用几次单刀路循环 6.20
	for (int j = 0; j < 6; j++)
	{
		double cur_ang_pos = 0.0;
		int is_sel = selected_ren[j];
		if (is_sel == 1)
		{
			cur_ang_pos = v_fd[j];
		}
		else
		{
			continue;
		}
		for (int i = 0; i < count_p; i++)
		{
			DL_P ls_dl_p = ptr_DL->Data[i];

			//解算出砂轮的参考点
			vec JC_P = ptr_DL->Data[i].JC_P;
			mat JC_SYS_SL = ptr_DL->Data[i].JC_SYS_SL;
			mat JC_SYS_HDM = ptr_DL->Data[i].JC_SYS_HDM;  //只一个法向，vec3 12.5
			double cur_a = ptr_DL->Data[i].theta_nz;
			double cur_c = ptr_DL->Data[i].theta_bd;
			int type_p = ptr_DL->Data[i].point_type;

			//将标准机的AC，转为戴杰AC。9.9 此处转换可增加不同机床类型
			cur_a = -cur_a;
			cur_c = -90.0 - cur_c;

			//阵列在机床坐标系中等于改变A值
			cur_a = cur_a + cur_ang_pos;

			//从机床点偏移对应三次方向到机床主轴点 6.20
			vec3 cur_p = JC_P + JC_SYS_HDM.col(2) * sl_canshul.r
				- JC_SYS_SL.col(0) * sl_canshul.Ry + JC_SYS_SL.col(2) * sl_canshul.L;

#pragma region 计算补偿
			//0、刀路数据增加工序类型信息
			//1、根据i计算出对应补偿模型的位置，球头
			//1.1、计算出的位置能判断出是否在球头
			//2、插值公式

			int is_ball = is_has_qiu_car_gx(gx_type);

			//对应机床变量,工序指定，输入给探测程序，变量序号设置写为函数
			//一个工序最多四个
			int num_1_in_JC_BL = 0;
			int num_2_in_JC_BL = 0;
			int num_3_in_JC_BL = 0;
			int num_4_in_JC_BL = 0;

			set_num_in_JC_BL(gx_type, num_1_in_JC_BL, num_2_in_JC_BL, num_3_in_JC_BL, num_4_in_JC_BL);

			nc_block a1 = BL(num_1_in_JC_BL);
			nc_block a2 = BL(num_2_in_JC_BL);
			nc_block a3 = BL(num_3_in_JC_BL);
			nc_block a4 = BL(num_4_in_JC_BL);

			if (is_ball && type_p == 0) //点类型为0
			{
				double  cur_p_bu_pos = 0.1;
				//根据i计算出对应补偿模型的位置
				cur_p_bu_pos = cal_p_in_bu_mode_pos(ptr_DL->Data[i].G_P);

				if (cur_p_bu_pos < 0.5)
				{
					nc_code >> (cal_bu_b = (1 - cur_p_bu_pos) * a1 + cur_p_bu_pos * a2);
				}
				else if (cur_p_bu_pos < 1.0)
				{
					nc_code >> (cal_bu_b = (1 - cur_p_bu_pos) * a2 + cur_p_bu_pos * a3);
				}
				else
				{
					nc_code >> (cal_bu_b = a4);
				}
			}
			else
			{
				nc_code >> (cal_bu_b = a1);
			}
#pragma endregion

#pragma region 计算速度
			//只有点类型为0即磨削点，才计算速度,其他类型直接赋值-11.4
			if (type_p == 0)
			{
				//计算实际两点间的速度11.1
				vec3 ls_cur_p = ptr_DL->Data[i].G_P;
				vec3 ls_next_p = ptr_DL->Data[i + 1].G_P; //最后一个磨削点下一个为退刀点，用退刀速度
				double next_a = ptr_DL->Data[i + 1].theta_nz;
				double next_c = ptr_DL->Data[i + 1].theta_bd;

				//需要计算主轴点 6.18 ???
				vec3 ls_cur_jc_p = ptr_DL->Data[i].JC_P;
				vec3 ls_next_jc_p = ptr_DL->Data[i + 1].JC_P;

				//磨削点的路程 / 进给速度 = 理论时间
				double time_lilun = tcDistance(ls_cur_p, ls_next_p) / cur_sudu;
				//修改进退刀距离为0计算出时间为0，不往后走 12.20
				if (time_lilun < 0.0000000001)
				{
					cal_sudu = cal_sudu;
				}
				else
				{
					//计算时间 / 理论时间 = 倍率
					double x_move = abs(ls_next_jc_p(0) - ls_cur_jc_p(0));
					double y_move = abs(ls_next_jc_p(1) - ls_cur_jc_p(1));
					double z_move = abs(ls_next_jc_p(2) - ls_cur_jc_p(2));
					double a_move = abs(next_a - cur_a);
					double c_move = abs(next_c - cur_c);
					double total_move = sqrt(x_move * x_move + y_move * y_move + z_move * z_move
						+ a_move * a_move + c_move * c_move);

					//主轴在XOZ平面走圆弧，参考点位移放大半径系数，距离很大，加以限制 12.24
					double x_sudu = x_move / time_lilun;
					double y_sudu = y_move / time_lilun;
					double z_sudu = z_move / time_lilun;
					double a_sudu = a_move / time_lilun;
					double c_sudu = c_move / time_lilun;
					double total_sudu = total_move / time_lilun;
					//单独设置每个轴速度上限，可提到前端
					vec max_sudu = { 1000,1000,1000,1000,360 };

					double x_time = x_move / max_sudu(0);
					double y_time = y_move / max_sudu(1);
					double z_time = z_move / max_sudu(2);
					double a_time = a_move / max_sudu(3);
					double c_time = c_move / max_sudu(4);

					double time_max = 0.0;
					vec v_time = { time_lilun, x_time, y_time, z_time,a_time,c_time };
					time_max = arma::max(v_time);
					int max_index = v_time.index_max();
					if (max_index > 0)
					{
						time_max = arma::max(v_time);
					}

					cal_sudu = total_move / time_max;
				}

			}
			else
			{
				switch (type_p)
				{
				case 1:
					cal_sudu = sudu_lilun.JinDao;
					break;
				case 2:
					cal_sudu = sudu_lilun.TuiDao;
					break;
				case 3:
					cal_sudu = sudu_lilun.JieJin;
					break;
				case 4:
					cal_sudu = sudu_lilun.YuanLi;
					break;
				case 5:
					cal_sudu = sudu_lilun.KuaiSu;
					break;
				case 6:
					cal_sudu = sudu_lilun.KuaiSu;
					break;
				default:
					cal_sudu = 0.0;
					break;
				}
			}
#pragma endregion

			//点所在法向
			vec3 cur_nor = JC_SYS_HDM.col(0);
			vec3 lenth_vec = tcRotZ(3, cur_c) * tcY(3);

			//块赋值
			{
				nc_code >> (X_b = cur_p(0) + lenth_vec(0) * BL(1800) + cur_nor(0) * cal_bu_b); //原始+偏置+补偿
				nc_code >> (Y_b = cur_p(1) + lenth_vec(1) * BL(1800) + cur_nor(1) * cal_bu_b);
				nc_code >> (Z_b = cur_p(2) + cur_nor(2) * cal_bu_b);
			}

			//在点类型为5时，增加几个走位点11.11
			if (type_p == 5)
			{
				nc_code >> G01_A_F(cur_a, cal_sudu);
				nc_code >> G01_C_F(cur_c, cal_sudu);
				nc_code >> G01_X_F(X_b, ChangShu(cal_sudu));
				nc_code >> G01_Y_F(Y_b, ChangShu(cal_sudu));
				nc_code >> G01_Z_F(Z_b, ChangShu(cal_sudu));
			}
			else if (type_p == 6)
			{
				nc_code >> G01_X_Y_Z_A_C_F(X_b, Y_b, Z_b, ChangShu(cur_a), ChangShu(cur_c), ChangShu(cal_sudu));
				//nc_code >> G01_Z_F(safe_point.Z, cal_sudu); 退刀点插值后，删除副程序的Z抬升 25.11.10 
				//nc_code >> G01_X_F(200.0, cal_sudu);
				//nc_code >> G01_Y_F(200.0, cal_sudu);
			}
			else
			{
				nc_code >> G01_X_Y_Z_A_C_F(X_b, Y_b, Z_b, ChangShu(cur_a), ChangShu(cur_c), ChangShu(cal_sudu));
			}

		}
	}


	//G54状态下的安全位置 一个工序结束要回 25.11.13
	nc_code >> G01_Z_F(gx_safe_point.Z, cal_sudu);
	nc_code >> G01_X_F(gx_safe_point.X, cal_sudu);
	nc_code >> G01_Y_F(gx_safe_point.Y, cal_sudu);
	nc_code >> G01_A_F(gx_safe_point.A, cal_sudu);
	nc_code >> G01_C_F(gx_safe_point.C, cal_sudu);
}

inline void Miller_DL_fu_prog::set_jingeilv(CanShu_SuDu in_sudu)
{
	sudu_lilun = in_sudu;
}

nc_block Miller_DL_fu_prog::diaoyong()
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

int Miller_DL_fu_prog::is_has_qiu_car_gx(int in_gx_type)
{
	int ans = 0;
	switch (in_gx_type)
	{
	case 0:
		ans = 0;
		break;
	case 2:
		ans = 1;
		break;
	case 3:
		ans = 0; //后刀面2不补12.30
		break;

	default:
		ans = 0;
		break;
	}
	return ans;
}

void Miller_DL_fu_prog::set_num_in_JC_BL(int in_gx_type, int& num1, int& num2, int& num3, int& num4)
{
	int num_start = 1950; //后续好设置--更改需要同步 find_num_BL_pos
	switch (in_gx_type)
	{
	case 0:
		num1 = num_start + 0;  //前刀面只探一个点
		break;
	case 1:
		num1 = num_start + 1;
		break;
	case 2:
		num1 = num_start + 2; 
		num2 = num_start + 3; 
		num3 = num_start + 4; 
		num4 = num_start + 5;
		break;

	//大多数工序不用探测补偿

	case 8:
		num1 = num_start + 6;
		break;
	case 9:
		num1 = num_start + 7;
		break;
	case 12:
		num1 = num_start + 8;
		break;
	case 13:
		num1 = num_start + 9;
		break;

	case 17:
		num1 = num_start + 10;
		break;

	default:
		num1 = num_start - 1; //大多数工序不用探测补偿,将 1949设置为0.0
		break;
	}
}

double Miller_DL_fu_prog::cal_p_in_bu_mode_pos(vec3 in_p)
{
	//进入此函数，一定有球部分，输入点为工件坐标系
	if (in_p(2) > 0.001) //点在柱面
	{
		return 1.0;
	}
	else
	{
		//计算与-Z轴夹角12.13
		double ang = tcDegree(acos(dot(normalise(in_p), -tcZ(3))));

		return ang / 90.0;
	}
	return 0.0;
}

