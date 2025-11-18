#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS

#include "Miller_GX_Base.h"
#include "Miller_GX_CanShu.h"



//计算基本刀路


//生成工序副程序--工序重写

void Miller_Mo_QDM::set_base_data(CanShu_XinHouMian& in_data)
{
	obj_xinhou.set_base_data(in_data);
	obj_xinhou.init_data();
}

void Miller_Mo_QDM::init()
{
	init_shalun();

	if (error_message_global != 0)
	{
		return;
	}

	init_DL_base();

	if (error_message_global != 0)
	{
		return;
	}

	init_DL_end();

	init_prog_of_gx();
	is_lastest = 1;
}



void Miller_Mo_QDM::init_shalun()
{
	//根据砂轮id，磨削内外侧获取：xt_gx_shalun

}

void Miller_Mo_QDM::init_duixiang()
{
	obj_mian.init_data();
	if (error_message_global != 0)
	{
		return ;
	}
	obj_mian_end = obj_mian.copy_main_data();
}


void Miller_Mo_QDM::init_DL_base()
{
	////范围
	//double start = base_data.range.start;
	//double end = base_data.range.end;
	//obj_mian.Range(start, end);

	////抽样
	//double len = 0.1;
	//double ang = 0.1;
	//if (flag_cal_prog == 0)
	//{
	//	len = base_data.sample.Sample_lenth;
	//	ang = base_data.sample.Sample_angle;
	//}
	//if (flag_cal_prog == 1)
	//{
	//	len = base_data.sample.Sample_lenth_2D;
	//	ang = base_data.sample.Sample_angle_2D;
	//}
	//if (flag_cal_prog == 2)
	//{
	//	len = base_data.sample.Sample_lenth_3D;
	//	ang = base_data.sample.Sample_angle_3D;
	//}
	//obj_mian.Sample(len, ang);

	//计算刀路
	int no_success = cal_DL_by_qx_xh();
	if (no_success == 1)
	{
		return ;
	}
	
	//变化
	DL_base = XiDao_HDM_MoXue_BianHuan(DL_base, base_data.bianhuan);
}

void Miller_Mo_QDM::init_DL_end()
{
	DL_end = XiDao_JinTuiDao(0, DL_base, base_data.jintuidao);

	//增加循环和阵列后形成副程序- 6.14
	//XiDao_HDM_MoXue_XunHuan(DL_end,mo_canshu.xunhuan);

	//XiDao_HDM_MoXue_ZhenLie(DL_end, mo_canshu.zhenlie);
}

void Miller_Mo_QDM::init_prog_of_gx()
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(ptr_tool->prog_zhu, 0);
	//设置速度
	prog_of_gx->set_jingeilv(base_data.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	//prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);

	//需要将机床砂轮库封装一个类，提供交互操作，输入砂轮id返回位置-25.5.21

	vector<double> ls_fd = ptr_lx->ptr_fd->v_fendu;
	//传指针
	prog_of_gx->set_gx_DL(Miller_GX_Base::base_data.type_gx, &DL_end, Miller_GX_Base::base_data.sl_pos_in_JC, Miller_GX_Base::base_data.sl_pos_in_slz,
		sl, ls_fd);

	for (int i = 0; i < 6; i++)
	{
		prog_of_gx->selected_ren[i] = selected_ren[i];
	}

	//设置安全点
	prog_of_gx->gx_safe_point = ptr_tool->get_gx_safe_p();
	prog_of_gx->sl_safe_point = ptr_tool->get_sl_safe_p();
}

void Miller_Mo_QDM::cal_DL()
{

}

void Miller_Mo_QDM::init_data()
{
	//派生类填所需参数
	init_mo_data();

	if (error_message_global != 0)
	{
		return;
	}

	//计算流程
	init();
}


int Miller_Mo_QDM::cal_DL_by_qx_xh()
{
	DL_base.reset();

	//确定点数量
	int count = obj_mian.n_P();
	double ang_qx = base_data.fangfa.ang_qiexue;
	int mo_in_or_out = base_data.fangfa.in_or_out;
	double A_before = base_data.A_before;
	double C_before = 0.0;
	vector<Gpoint> all_Gp, ans;//前刀面数据
	
	Gpoint Gp;
	for (int i = 0; i < count; i++)
	{
		vec p_data = obj_mian.BG_P(i);
		vec t_data = obj_mian.BG_X(i);
		vec n_data = obj_mian.BG_Z(i);
		Gp.set_xyz(p_data(0), p_data(1), p_data(2));
		Gp.set_Qie(t_data(0), t_data(1), t_data(2));
		Gp.set_N(n_data(0), n_data(1), n_data(2));
		all_Gp.push_back(Gp);
	}

	QuMian_Grovving Grovving;
	Grovving.Set_XHM(&obj_xinhou.obj_qm);
	Grovving.Set_QDM(all_Gp);
	//Grovving.Set_SL_data(sl.r, sl.Ry / 2.0, ang_qx, mo_in_or_out);//函数默认外侧磨
	Grovving.Set_SL_data(sl.r, sl.Ry, ang_qx, mo_in_or_out);//函数默认外侧磨

	//8.16
	Grovving.Grinding_route(Reverse_flag);
	
	//test导出前刀面点数据
	{
		std::ofstream outFile1("points_qdm.txt");
		if (!outFile1.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		for (int i = 0; i < all_Gp.size(); i++)
		{
			// 获取当前 (u, v) 对应的点坐标（arma::vec3）
			arma::vec3 point = all_Gp[i].get_xyz_vec3();

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();
	}

	if (Grovving.Get_SL_WZ(ans))
	{
		//throw 99; //后期封装成全局报错机制 8.12 >> 封装到p_manager 9.12
		error_message_global = -2;
		return 1;
	}

	//test导出砂轮位姿点数据
	{
		mat44 accc = ans.back().get_WZ_mat44();
		mat coordinates;
		for (size_t i = 0; i < ans.size(); i++)
		{
			accc = ans[i].get_WZ_mat44();
			for (size_t i = 0; i < 360; i=i+4)
			{
				coordinates.insert_rows(coordinates.n_rows, Grovving.SL_Dong_point_out(accc, i).t());
			}
		}
		coordinates.save(R"(point.txt)", arma::raw_ascii);
	}


	for (size_t i = 0; i < ans.size(); i++)
	{
		mat44 ls_WZ = ans[i].get_WZ_mat44();
		mat33 G_SYS_SL = ls_WZ.submat(0, 0, 2, 2);

		DL_P ans_DL_P;
		ans_DL_P.G_P = obj_mian.BG_P(i);
		ans_DL_P.G_SYS_HDM = obj_mian.BG_SYS(i);
		ans_DL_P.G_SYS_SL = G_SYS_SL;

		//工件坐标系定义(X为回转轴)调整放到后处理坐标系, 绕Y转180。
		mat33 trans_mat = tcRotY(3, 180.0);
		ans_DL_P.G_P = trans_mat * ans_DL_P.G_P;
		ans_DL_P.G_SYS_HDM = trans_mat * ans_DL_P.G_SYS_HDM;
		ans_DL_P.G_SYS_SL  = trans_mat * ans_DL_P.G_SYS_SL ;

		//计算一个刀路点，类似于单点的后处理6.6
		cal_DL_P_by_G_SYS_SL(ans_DL_P, A_before, C_before); 
		A_before = ans_DL_P.theta_nz;
		C_before = ans_DL_P.theta_bd;

		DL_base.Data.push_back(ans_DL_P);
	}
	
}

void Miller_Mo_QDM::cal_DL_P_by_G_SYS_SL(DL_P& ans_DL_P, double& A_before,double& C_before)
{
	//3、 一些准备工作
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;

	mat33 GC_SYS_D = ans_DL_P.G_SYS_SL;
	vec3 GC_Z_D = ans_DL_P.G_SYS_SL.col(2);
	vec3 GC_O_D = ans_DL_P.G_P;
	vec3 GC_N = ans_DL_P.G_SYS_HDM.col(2);

	//4、 计算An
	double An = 0.0;
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}

	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}

	//5、 计算Cn
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);

	//6、 计算JC_SYS_HDM，JC_SYS_SL，JC_P
	ans_DL_P.JC_SYS_HDM = tcRotZ(3, -Cn) * tcRotX(3, -An) * ans_DL_P.G_SYS_HDM;
	ans_DL_P.JC_SYS_SL = tcRotZ(3, -Cn) * tcRotX(3, -An) * ans_DL_P.G_SYS_SL;
	ans_DL_P.JC_P = tcRotZ(3, -Cn) * JC_Y * ptr_tool->w_c2g + tcRotZ(3, -Cn) * tcRotX(3, -An) * ans_DL_P.G_P;

	//7、 计算theta_nz，theta_bd，theta_fx，theta_xq
	ans_DL_P.theta_nz = An;
	ans_DL_P.theta_bd = Cn;
	ans_DL_P.theta_fx = deltaRotAngle(tcX(3), ans_DL_P.JC_SYS_SL.col(0), ans_DL_P.JC_SYS_SL.col(2));
	ans_DL_P.theta_xq = deltaRotAngle(ans_DL_P.JC_SYS_SL.col(0), -ans_DL_P.JC_SYS_HDM.col(2), ans_DL_P.JC_SYS_SL.col(1));
}

void Miller_Mo_QDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
	base_data.A_before = in_mo.A_before;
	base_data.range = in_mo.range;
	base_data.sample = in_mo.sample;
	base_data.jintuidao = in_mo.jintuidao;
	base_data.bianhuan = in_mo.bianhuan;
	base_data.fangfa = in_mo.fangfa;
	base_data.sudu = in_mo.sudu;
}

int Miller_Mo_QDM::save(int pos)
{
	Miller_GX_Base::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_Mo_QDM::load(int pos)
{
	Miller_GX_Base::load(pos);
	base_data.load(pos);
}

//inline void Miller_QDM::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
//{
//	//需要一个主程序指针
//	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
//	//设置速度
//	prog_of_gx->set_jingeilv(Mo_Canshu.sudu.MoXueJinGei, Mo_Canshu.sudu);
//	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
//	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);
//
//}


void Miller_Mo_HDM::init()
{
	init_shalun();
	if (error_message_global != 0)
	{
		return;
	}

	init_DL_base();

	if (error_message_global != 0)
	{
		return;
	}
	init_DL_end();


	init_prog_of_gx();
	is_lastest = 1;
}

void Miller_Mo_HDM::init_shalun()
{
}

void Miller_Mo_HDM::init_duixiang()
{
	//20250603
	//if (ptr_mian == nullptr)
	//{
	//	ptr_mian = new Cal_HDM(lx_id, hj_id, ptr_tool);
	//}
	//else
	//{
	//	ptr_mian->set_luoxuan_id(lx_id);
	//	ptr_mian->set_houjiao_id(hj_id);
	//}

	//派生类产生后刀面对象时，已经计算完成 不需要再次计算 8.4
	//obj_mian.init_data();
	obj_mian_end = obj_mian.copy_main_data();
}

void Miller_Mo_HDM::init_DL_base()
{
	////范围
	//double start = base_data.range.start;
	//double end = base_data.range.end;
	//obj_mian.Range(start, end);

	////抽样
	//double len = 0.1;
	//double ang = 0.1;
	//if (flag_cal_prog == 0)
	//{
	//	len = base_data.sample.Sample_lenth;
	//	ang = base_data.sample.Sample_angle;
	//}
	//if (flag_cal_prog == 1)
	//{
	//	len = base_data.sample.Sample_lenth_2D;
	//	ang = base_data.sample.Sample_angle_2D;
	//}
	//if (flag_cal_prog == 2)
	//{
	//	len = base_data.sample.Sample_lenth_3D;
	//	ang = base_data.sample.Sample_angle_3D;
	//}
	//obj_mian.Sample(len, ang);

	//计算刀路
	//旋转角度+位移角度
	if (base_data.fangfa.type == 0)
	{
		//确定点数量
		int count = obj_mian.n_P();
		double xxlenth = obj_mian.Lenth_At_Point(count - 1);
		//确定旋转角度
		vec v_xz(count);
		if (base_data.fangfa.qx_wy.QX_isbian == false)
		{
			v_xz.fill(base_data.fangfa.qx_wy.QX);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_xz(i) = base_data.fangfa.qx_wy.QX_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}
		//确定位移角度
		vec v_wy(count);
		if (base_data.fangfa.qx_wy.WY_isbian == false)
		{
			v_wy.fill(base_data.fangfa.qx_wy.WY);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_wy(i) = base_data.fangfa.qx_wy.WY_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}
		//计算刀路
		cal_DL_by_xz_wy(v_xz, v_wy, &obj_mian, sel_hdm_id,0);

	}
	//摆动角度+位移角度
	else if (base_data.fangfa.type == 1)
	{
		//确定点数量
		int count = obj_mian.n_P();
		double xxlenth = obj_mian.Lenth_At_Point(count - 1);
		//确定摆动角度
		vec v_bd(count);
		if (base_data.fangfa.qx_wy.QX_isbian == false)
		{
			v_bd.fill(base_data.fangfa.qx_wy.QX);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_bd(i) = base_data.fangfa.qx_wy.QX_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}
		//确定位移角度
		vec v_wy(count);
		if (base_data.fangfa.qx_wy.WY_isbian == false)
		{
			v_wy.fill(base_data.fangfa.qx_wy.WY);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_wy(i) = base_data.fangfa.qx_wy.WY_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}

		//计算刀路
		cal_DL_by_bd_wy(v_bd, v_wy, &obj_mian, sel_hdm_id);
	}
	//切削角度+位移角度
	else if (base_data.fangfa.type == 2)
	{
		//确定点数量
		int count = obj_mian.n_P();
		double xxlenth = obj_mian.Lenth_At_Point(count - 1);
		//确定摆动角度
		vec v_qx(count);
		if (base_data.fangfa.qx_wy.QX_isbian == false)
		{
			v_qx.fill(base_data.fangfa.qx_wy.QX);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_qx(i) = base_data.fangfa.qx_wy.QX_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}
		//确定位移角度
		vec v_wy(count);
		if (base_data.fangfa.qx_wy.WY_isbian == false)
		{
			v_wy.fill(base_data.fangfa.qx_wy.WY);
		}
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				v_wy(i) = base_data.fangfa.qx_wy.WY_bian.get(obj_mian.Lenth_At_Point(i) / xxlenth);
			}
		}

		//计算刀路
		cal_DL_by_qx_wy(v_qx, v_wy, &obj_mian, sel_hdm_id, base_data.A_before);
	}
	else
	{
		throw - 1;
	}

	//变化
	DL_base = XiDao_HDM_MoXue_BianHuan(DL_base, base_data.bianhuan);
}

void Miller_Mo_HDM::init_DL_end()
{
	DL_end = XiDao_JinTuiDao(1, DL_base, base_data.jintuidao);

	//增加循环和阵列后形成副程序- 6.14
	//XiDao_HDM_MoXue_XunHuan(DL_end, mo_canshu.xunhuan);

	//XiDao_HDM_MoXue_ZhenLie(DL_end, mo_canshu.zhenlie);
}

void Miller_Mo_HDM::init_prog_of_gx()
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(ptr_tool->prog_zhu, 0);
	//设置速度
	prog_of_gx->set_jingeilv(base_data.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	//prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);

	
	vector<double> ls_fd = ptr_lx->ptr_fd->v_fendu;

	//传指针
	prog_of_gx->set_gx_DL(Miller_GX_Base::base_data.type_gx, &DL_end, Miller_GX_Base::base_data.sl_pos_in_JC, Miller_GX_Base::base_data.sl_pos_in_slz,
		sl, ls_fd);
	for (int i = 0; i < 6; i++)
	{
		prog_of_gx->selected_ren[i] = selected_ren[i];
	}

	//设置安全点
	prog_of_gx->gx_safe_point = ptr_tool->get_gx_safe_p();
	prog_of_gx->sl_safe_point = ptr_tool->get_sl_safe_p();
}

void Miller_Mo_HDM::cal_DL()
{

}

void Miller_Mo_HDM::init_data()
{
	//派生类填所需参数
	init_mo_data();

	if (error_message_global != 0)
	{
		return;
	}
	
	//计算流程
	init();
}



void Miller_Mo_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	base_data.A_before = in_mo.A_before;
	base_data.range = in_mo.range;
	base_data.sample = in_mo.sample;
	base_data.jintuidao = in_mo.jintuidao;
	base_data.bianhuan = in_mo.bianhuan;
	base_data.fangfa = in_mo.fangfa;
	base_data.sudu = in_mo.sudu;
}

void Miller_Mo_HDM::cal_DL_by_xz_wy(vec xz_v, vec wy_v, Cal_HDM* hdm, int hdm_sel, bool in_other)
{

	DL_base.reset();
	int count = hdm->n_P();
	double bd_before = -90.0;

	for (int i = 0; i < count; i++)
	{
		//
		DL_P ls_dlp;
		//1、 计算G_P和G_SYS_HDM
		if (hdm_sel == 0)
		{
			ls_dlp.G_P =  hdm->HJ1_P(i);
			ls_dlp.G_SYS_HDM = hdm->HJ1_SYS(i);
		}
		else if (hdm_sel == 1)
		{
			ls_dlp.G_P = hdm->HJ2_P(i);
			ls_dlp.G_SYS_HDM = hdm->HJ2_SYS(i);
		}
		else if (hdm_sel == 2)
		{
			ls_dlp.G_P = hdm->HJ3_P(i);
			ls_dlp.G_SYS_HDM = hdm->HJ3_SYS(i);
		}

		//工件坐标系定义(X为回转轴)调整放到后处理坐标系, 绕Y转180。
		mat33 trans_mat = tcRotY(3, 180.0);
		ls_dlp.G_P = trans_mat * ls_dlp.G_P;
		ls_dlp.G_SYS_HDM = trans_mat * ls_dlp.G_SYS_HDM;
		ls_dlp.G_SYS_SL = trans_mat * ls_dlp.G_SYS_SL;

		//2、 相位角计算
		mat ls_sys = eye(3, 3);
		vec ls_vec = ls_dlp.G_P;
		ls_vec(0) = 0.0;
		ls_vec = normalise(ls_vec);
		double xiangwei = deltaRotAngle(tcY(3), ls_vec, tcX(3));

		//3、计算G_Y_SL
		//0相位时的后刀面坐标系  
		ls_sys = tcRotX(3, -xiangwei) * ls_dlp.G_SYS_HDM;

		//0相位时的工件坐标系下砂轮Y轴
		ls_sys = ls_sys * tcRotZ(3, wy_v(i));//砂轮Y轴与后角线方向相同
		vec3 G_Y_SL = ls_sys.col(1);
		vec3 ls_y = tcRotX(3, -xz_v(i)) * G_Y_SL;
	
		//tcRotZ(-bd)* tcRotX(3, -xz_v(i))* G_Y_SL* tcY(3) = 0;
		//tcRotZ(-bd)* ls_y* tcY(3) = 0;
		//sin(-bd)* ls_y(0) + cos(-bd) * ls_y(1) = 0;
		//tan(-bd) = -ls_y(1) / ls_y(0);

		////4、 确定bd
		double bd = 0.0;
		//bd = tcDegree(atan(
		//	(cos(tcRadians(xz_v(i))) * G_Y_SL(1) + sin(tcRadians(xz_v(i))) * G_Y_SL(2))
		//	/ G_Y_SL(0)
		//));
		bd = -tcDegree(atan(-ls_y(1) / ls_y(0)));

		if (dot(tcRotZ(3, -bd) * tcX(3), tcY(3)) > 0)
		{
		}
		else
		{
			if (bd > 0.0)
			{
				bd = bd - 180.0;
			}
			else
			{
				bd = bd + 180.0;
			}
		}

		//bd = bd - 90.0;
		//atan周期为180度
		if (i == 0)
		{
			//加选择解的参数，改变初始点的bd 8.25
			//if (in_other == 1)
			//{
			//	//保证砂轮轴与刀尖方向一致
			//	if (bd > 0.0)
			//	{
			//		bd = bd - 180.0;
			//	}
			//	else
			//	{
			//		bd = bd + 180.0;
			//	}
			//}
		}
		else
		{
			//保证刀路连续
			//if (bd_before)
			{
				double panduan = bd - bd_before;
				if (abs(panduan) < 70.0)
				{

				}
				else
				{
					bd = bd - 180.0 * panduan / abs(panduan);//上面的条件决定了panduan不等于0
				}
			}
		}
		bd_before = bd;

		//5、 0相位时，由JC_Z_SL 求G_Z_SL和G_X_SL
		vec3 G_Z_SL = tcRotX(3, xz_v(i)) * tcRotZ(3, bd) * tcY(3);
		vec3 G_X_SL = cross(G_Y_SL, G_Z_SL);

		//6、计算0相位时，G_SYS_SL
		ls_dlp.G_SYS_SL.col(0) = G_X_SL;
		ls_dlp.G_SYS_SL.col(1) = G_Y_SL;
		ls_dlp.G_SYS_SL.col(2) = G_Z_SL;

		//还原相位角 计算得G_SYS_SL
		ls_dlp.G_SYS_SL = tcRotX(3, xiangwei) * ls_dlp.G_SYS_SL;

		//7、计算JC_SYS_SL
		ls_dlp.JC_SYS_SL = trans_G_to_JC_in_BiaoZhun(ls_dlp.G_SYS_SL, xiangwei + xz_v(i), bd);

		//8、计算JC_SYS_HDM
		ls_dlp.JC_SYS_HDM = trans_G_to_JC_in_BiaoZhun( ls_dlp.G_SYS_HDM, xiangwei + xz_v(i), bd);

		//9、计算JC_P
		ls_dlp.JC_P = trans_G_to_JC_in_BiaoZhun(ls_dlp.G_P, xiangwei + xz_v(i),bd);

		//10、 计算theta_nz，theta_bd，theta_fx，theta_xq
		ls_dlp.theta_nz = xiangwei + xz_v(i);//相位的定义和扭转的定义相反
		ls_dlp.theta_bd = bd;
		ls_dlp.theta_fx = deltaRotAngle(tcX(3), ls_dlp.JC_SYS_SL.col(0), ls_dlp.JC_SYS_SL.col(2));
		ls_dlp.theta_xq = deltaRotAngle(ls_dlp.JC_SYS_SL.col(0), -ls_dlp.JC_SYS_HDM.col(2), ls_dlp.JC_SYS_SL.col(1));

		//插入刀路点
		DL_base.Data.push_back(ls_dlp);
	}
}

void Miller_Mo_HDM::cal_DL_by_qx_wy(vec qx_v, vec wy_v, Cal_HDM* hdm, int hdm_sel, double A_before_in)
{
	DL_base.reset();
	int count = hdm->n_P();
	double A_before = A_before_in;
	for (size_t i = 0; i < count; i++)
	{
		//
		DL_P ls_dlp;

		//1、 计算G_P和G_SYS_HDM
		if (hdm_sel == 0)
		{
			ls_dlp.G_P =  hdm->HJ1_P(i);
			ls_dlp.G_SYS_HDM = hdm->HJ1_SYS(i);
		}
		else if (hdm_sel == 1)
		{
			ls_dlp.G_P =  hdm->HJ2_P(i);
			ls_dlp.G_SYS_HDM =  hdm->HJ2_SYS(i);
		}
		else if (hdm_sel == 2)
		{
			ls_dlp.G_P =  hdm->HJ3_P(i);
			ls_dlp.G_SYS_HDM =  hdm->HJ3_SYS(i);
		}

		//2、 计算G_SYS_SL
		double test_wy = wy_v(i);
		double test_qx = qx_v(i);
		//后刀面逆路径转负的切削角 8.21
		if (Reverse_flag == 0)
		{
			ls_dlp.G_SYS_SL = ls_dlp.G_SYS_HDM * tcRotZ(3, 180.0) * tcRotZ(3, wy_v(i)) * tcRotY(3, qx_v(i));
		}
		else
		{
			ls_dlp.G_SYS_SL = ls_dlp.G_SYS_HDM * tcRotZ(3, 180.0) * tcRotZ(3, wy_v(i)) * tcRotY(3, -qx_v(i));
		}

		//工件坐标系定义(X为回转轴)调整放到后处理坐标系, 绕Y转180
		mat33 trans_mat = tcRotY(3, 180.0);
		ls_dlp.G_P = trans_mat * ls_dlp.G_P;
		ls_dlp.G_SYS_HDM = trans_mat * ls_dlp.G_SYS_HDM;
		ls_dlp.G_SYS_SL = trans_mat * ls_dlp.G_SYS_SL;


		//3、 一些准备工作
		const double  DEG_90 = 90.0;
		const double  DEG_180 = 180.0;
		const double  DIF_E = 0.000001;

		mat33 GC_SYS_D = ls_dlp.G_SYS_SL;
		vec3 GC_Z_D = ls_dlp.G_SYS_SL.col(2);
		vec3 GC_O_D = ls_dlp.G_P;
		vec3 GC_N = ls_dlp.G_SYS_HDM.col(2);

		//4、 计算An
		double An = 0.0;
		if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
		{
			An = DEG_90;
		}
		else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
		{
			std::cout << "主轴与A轴平行" << endl;
			An = A_before;
		}
		else if (abs(GC_Z_D(1)) >= DIF_E)
		{
			An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
		}
		while (An - A_before > DEG_90)
		{
			An = An - DEG_180;
		}
		while (An - A_before < -DEG_90)
		{
			An = An + DEG_180;
		}

		//5、 计算Cn
		vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
		vec3 JC_Y = tcY(3);
		vec3 JC_Z = tcZ(3);
		double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);

		//6、 计算JC_SYS_HDM，JC_SYS_SL，JC_P
		ls_dlp.JC_SYS_HDM = tcRotZ(3, -Cn) * tcRotX(3, -An) * ls_dlp.G_SYS_HDM;
		ls_dlp.JC_SYS_SL = tcRotZ(3, -Cn) * tcRotX(3, -An) * ls_dlp.G_SYS_SL;
		ls_dlp.JC_P = tcRotZ(3, -Cn) * JC_Y * ptr_tool->w_c2g + tcRotZ(3, -Cn) * tcRotX(3, -An) * ls_dlp.G_P;

		//7、 计算theta_nz，theta_bd，theta_fx，theta_xq
		ls_dlp.theta_nz = An;
		ls_dlp.theta_bd = Cn;
		ls_dlp.theta_fx = deltaRotAngle(tcX(3), ls_dlp.JC_SYS_SL.col(0), ls_dlp.JC_SYS_SL.col(2));
		ls_dlp.theta_xq = deltaRotAngle(ls_dlp.JC_SYS_SL.col(0), -ls_dlp.JC_SYS_HDM.col(2), ls_dlp.JC_SYS_SL.col(1));

		//插入刀路点
		DL_base.Data.push_back(ls_dlp);
	}

	//以上计算按照标准机床和标准示意图完成，没有进行戴杰机床的适配
}

int Miller_Mo_HDM::save(int pos)
{
	Miller_GX_Base::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_Mo_HDM::load(int pos)
{
	Miller_GX_Base::load(pos);
	base_data.load(pos);
}

void Miller_Mo_HDM::cal_DL_by_bd_wy(vec bd_v, vec wy_v, Cal_HDM* hdm, int hdm_sel)
{
}

//保留安全包围盒接近原理方式，计算还是采用空间点
//前后刀面坐标系定义不同，可用一个函数加类型判断统一实现 6.6 

Miller_GX_Base::Miller_GX_Base()
{

}

Miller_GX_Base::~Miller_GX_Base()
{

}


void Miller_GX_Base::speak_father_del_guanxi()
{

}

void Miller_GX_Base::init_guanxi()
{

}

string Miller_GX_Base::get_name()
{
	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致 
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };

	string ans_name;
	//if (storage_lib.Storage_base::read_a_row_data(9, pos, name_buffer, NAME_BUFFER_SIZE))
	//{
	//	ans_name.assign(name_buffer);
	//	// 如果存储时有填充空字符，会自动截断
	//}
	//else
	//{
	//	ans_name = "Unknown";
	//}
	return ans_name;
}

string Miller_GX_Base::get_type_of_string()
{
	string ans_name;
	switch (base_data.type_gx)
	{
	case 0:
		ans_name = "开槽";
		break;
	case 1:
		ans_name = "螺旋槽";
		break;
	case 2:
		ans_name = "端齿槽-球头";
		break;
	case 3:
		ans_name = "端齿槽-直线";
		break;
	case 4:
		ans_name = "圆角前刀面";
		break;
	case 5:
		ans_name = "后刀面";
		break;
	case 6:
		ans_name = "后刀面all-锥球刀";
		break;
	case 7:
		ans_name = "端后刀面-直线";
		break;
	case 8:
		ans_name = "柱后刀面-平底刀";
		break;
	case 9:
		ans_name = "后刀面all-圆角刀";
		break;
	case 10:
		ans_name = "刀尖间隙";
		break;
	

	default:
		break;
	}
	return ans_name;
}

int Miller_GX_Base::get_sl_id()
{
	return base_data.shalun_id;
}

double Miller_GX_Base::get_jingeilv()
{
	return 0.0;
}

int Miller_GX_Base::get_hj_id()
{
	return -1;
}

int Miller_GX_Base::get_lx_id()
{
	return -1;
}

void Miller_GX_Base::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{

}

void Miller_GX_Base::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{

}

vec3 Miller_GX_Base::tcCartesian_to_Polar(vec3 cart_P, int i)
{
	vec ans(3, fill::zeros);
	if (i == 0)
	{
		//步骤1
		ans(0) = cart_P(0);
		//步骤2
		ans(1) = sqrt(cart_P(1) * cart_P(1) + cart_P(2) * cart_P(2));
		//步骤3
		vec3 temp = cart_P;
		temp(0) = 0.0;
		temp = normalise(temp);
		ans(2) = deltaRotAngle(tcY(3), temp, tcX(3));
	}
	else if (i == 1)
	{
		//步骤1
		ans(0) = cart_P(1);
		//步骤2
		ans(1) = sqrt(cart_P(0) * cart_P(0) + cart_P(2) * cart_P(2));
		//步骤3
		vec3 temp = cart_P;
		temp(1) = 0.0;
		temp = normalise(temp);
		ans(2) = deltaRotAngle(tcZ(3), temp, tcY(3));
	}
	else if (i == 2)
	{
		//步骤1
		ans(0) = cart_P(2);
		//步骤2
		ans(1) = sqrt(cart_P(0) * cart_P(0) + cart_P(1) * cart_P(1));
		//步骤3
		vec3 temp = cart_P;
		temp(2) = 0.0;
		temp = normalise(temp);
		ans(2) = deltaRotAngle(tcX(3), temp, tcZ(3));
	}
	return ans;
}


vec3 Miller_GX_Base::tcPolar_to_Cartesian(vec3 polar_P, int i)
{
	vec ans(3, fill::zeros);
	if (i == 0)
	{
		//步骤1
		ans(0) = polar_P(0);
		//步骤2
		ans(1) = polar_P(1) * cos(tcRadians(polar_P(2)));
		//步骤3
		ans(2) = polar_P(1) * sin(tcRadians(polar_P(2)));
	}
	else if (i == 1)
	{
		//步骤1
		ans(1) = polar_P(0);
		//步骤2
		ans(2) = polar_P(1) * cos(tcRadians(polar_P(2)));
		//步骤3
		ans(0) = polar_P(1) * sin(tcRadians(polar_P(2)));
	}
	else if (i == 2)
	{
		//步骤1
		ans(2) = polar_P(0);
		//步骤2
		ans(0) = polar_P(1) * cos(tcRadians(polar_P(2)));
		//步骤3
		ans(1) = polar_P(1) * sin(tcRadians(polar_P(2)));
	}
	return ans;
}

//当前G_P在标准SYS, 转极坐标系要考虑相位的轴 9.9
DL Miller_GX_Base::XiDao_JinTuiDao(int mo_type, DL& in_DaoLu, xt_CanShu_JinTuiDao in_JinTuiDaoCanShu)
{
	vec G_JinDaoDian, JC_JinDaoDian;
	vec G_TuiDaoDian, JC_TuiDaoDian;
	vec G_JieJinDian, JC_JieJinDian;
	vec G_YuanLiDian, JC_YuanLiDian;
	vec G_AnQuanDianStart, JC_AnQuanDianStart;
	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
	vec Start_QieXiang;
	vec End_QieXiang;

	//0 准备要用到数据 
	int count_p = in_DaoLu.Data.size();
	double A_start = in_DaoLu.Data.at(0).theta_nz;
	double C_start = in_DaoLu.Data.at(0).theta_bd;
	double A_end = in_DaoLu.Data.at(count_p - 1).theta_nz;
	double C_end = in_DaoLu.Data.at(count_p - 1).theta_bd;
	vec G_P_start = in_DaoLu.Data.at(0).G_P;
	vec G_P_end = in_DaoLu.Data.at(count_p - 1).G_P;
	vec G_P_start_pol = tcCartesian_to_Polar(in_DaoLu.Data.at(0).G_P, 0); //X是回转轴 刀尖指刀柄
	vec G_P_end_pol = tcCartesian_to_Polar(in_DaoLu.Data.at(count_p - 1).G_P, 0);
	mat G_SYS_HDM_start = in_DaoLu.Data.at(0).G_SYS_HDM;
	mat G_SYS_SL_start = in_DaoLu.Data.at(0).G_SYS_SL;
	mat G_SYS_HDM_end = in_DaoLu.Data.at(count_p - 1).G_SYS_HDM;
	mat G_SYS_SL_end = in_DaoLu.Data.at(count_p - 1).G_SYS_SL;


	//计算进刀点
	//计算进刀方向向量- 

	//构建一个进刀坐标系，X轴沿刀路切向，Z轴沿面法向
	vec G_P_start_2 = in_DaoLu.Data.at(1).G_P;
	mat jindao_sys(3, 3, fill::zeros);
	jindao_sys.col(0) = normalise(G_P_start_2 - G_P_start);
	jindao_sys.col(2) = G_SYS_HDM_start.col(2);
	jindao_sys.col(1) = tc_cross(jindao_sys.col(2), jindao_sys.col(0));

	//计算进刀方向
	if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
	{
		Start_QieXiang = -jindao_sys.col(0);
	}
	else
	{
		Start_QieXiang = jindao_sys * tcRotY(3, in_JinTuiDaoCanShu.JinDaoJiaoDu) * (-tcX(3)); //进退刀方向水平
	}

	//第一个磨削点+进刀距离*进刀方向
	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + G_P_start;
	vec G_jd_pol = tcCartesian_to_Polar(G_JinDaoDian, 0);
	JC_JinDaoDian = trans_G_to_JC_in_BiaoZhun(G_JinDaoDian, A_start, C_start);


	//计算退刀点

	//构建一个退刀坐标系，X轴沿刀路切向，Z轴沿面法向
	vec G_P_end_2 = in_DaoLu.Data.at(count_p - 2).G_P;
	mat tuidao_sys(3, 3, fill::zeros);
	tuidao_sys.col(0) = normalise(G_P_end - G_P_end_2);
	tuidao_sys.col(2) = G_SYS_HDM_end.col(2);
	tuidao_sys.col(1) = tc_cross(tuidao_sys.col(2), tuidao_sys.col(0));

	//计算退刀方向
	if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
	{
		End_QieXiang = tuidao_sys.col(0);
	}
	else
	{
		End_QieXiang = tuidao_sys * tcRotY(3, -in_JinTuiDaoCanShu.TuiDaoJiaoDu) * (tcX(3)); //进退刀方向水平
	}

	//第一个磨削点+进刀距离*进刀方向
	G_TuiDaoDian = End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + G_P_end;
	vec G_td_pol = tcCartesian_to_Polar(G_TuiDaoDian, 0);
	JC_TuiDaoDian = trans_G_to_JC_in_BiaoZhun(G_TuiDaoDian, A_end, C_end);



	//计算安全点 : 
	double AnQuanR = in_DaoLu.maxR() + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
	double AnQuanX = in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi;
	//当前G_P在标准SYS
	vec anquan_start_pol = { AnQuanX , AnQuanR , G_jd_pol(2) };//wen  保证一致
	vec anquan_end_pol = { AnQuanX , AnQuanR , G_td_pol(2) };
	G_AnQuanDianStart = tcPolar_to_Cartesian(anquan_start_pol, 0);
	G_AnQuanDianEnd = tcPolar_to_Cartesian(anquan_end_pol, 0);

	JC_AnQuanDianStart = trans_G_to_JC_in_BiaoZhun(G_AnQuanDianStart, A_start, C_start);
	JC_AnQuanDianEnd = trans_G_to_JC_in_BiaoZhun(G_AnQuanDianEnd, A_end, C_end);

	//计算接近点
	{
		vec LSvec1, LSvec2;
		//指向安全点的方向向量
		LSvec1 = normalise(anquan_start_pol - G_jd_pol);//相位差为0
		//指向接近点方向的方向向量
		LSvec2 = normalise(tcRotZ(3, in_JinTuiDaoCanShu.JieJinJiaoDu) * (tcX(3)));
		vec G_jj_pol = zeros(3);

		double juli = 0.0;
		if (LSvec2(0) > LSvec1(0))
		{
			//说明先到达轴向安全距离位置
			juli = abs(AnQuanX - G_jd_pol(0)) / cos(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu));
		}
		else
		{
			//说明先到达径向安全距离位置
			juli = abs(AnQuanR - G_jd_pol(1)) / sin(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu));
		}
		G_jj_pol = G_jd_pol + juli * LSvec2;
		G_JieJinDian = tcPolar_to_Cartesian(G_jj_pol, 0);
		JC_JieJinDian = trans_G_to_JC_in_BiaoZhun(G_JieJinDian, A_start, C_start);
	}

	//计算远离点
	{
		vec LSvec1, LSvec2;
		//指向安全点的方向向量
		LSvec1 = normalise(anquan_end_pol - G_td_pol);//相位差为0
		//指向接近点方向的方向向量
		LSvec2 = tcRotZ(3, -in_JinTuiDaoCanShu.YuanLiJiaoDu) * (-tcX(3));

		vec G_jj_pol = zeros(3);
		double juli = 0.0;
		if (LSvec2(0) > LSvec1(0))
		{
			//说明先到达轴向安全距离位置
			juli = abs(AnQuanX - G_td_pol(0)) / cos(tcRadians(in_JinTuiDaoCanShu.YuanLiJiaoDu));
		}
		else
		{
			//说明先到达径向安全距离位置
			juli = abs(AnQuanR - G_td_pol(1)) / sin(tcRadians(in_JinTuiDaoCanShu.YuanLiJiaoDu));
		}

		vec dir(3, fill::zeros);
		if (mo_type == 0)//前刀面 = 0
		{
			dir = tcRotX(3, G_td_pol(2)) * LSvec2;
			dir = normalise(tc_vec_prj_to_plane(dir, G_SYS_SL_end.col(2)));
		}
		else
		{
			dir = tcRotX(3, G_td_pol(2)) * LSvec2;
		}

		G_YuanLiDian = dir * juli + G_TuiDaoDian;
		JC_YuanLiDian = trans_G_to_JC_in_BiaoZhun(G_YuanLiDian, A_end, C_end);
	}

#pragma region 将结果插入队列

	//将结果插入队列
	//在前后各复制三个元素
	DL_P ls_start_p = in_DaoLu.Data.at(0);
	DL_P ls_end_p = in_DaoLu.Data.at(count_p - 1);


	//进退刀增加刀路点时插值10个 25.10.31
	int num_cha = 11;
	DL_P ans_cha_p;

	//进刀点
	{
		vec G_cha_start_p = in_DaoLu.Data.at(0).G_P;
		vec G_pp_t = normalise(G_JinDaoDian - G_cha_start_p);
		double G_pp_dis = tcDistance(G_JinDaoDian, G_cha_start_p);
		double G_delta_dis = G_pp_dis / (1.0 * (num_cha - 1));

		vec JC_cha_start_p = in_DaoLu.Data.at(0).JC_P;
		vec JC_pp_t = normalise(JC_JinDaoDian - JC_cha_start_p);
		double JC_pp_dis = tcDistance(JC_JinDaoDian, JC_cha_start_p);
		double JC_delta_dis = JC_pp_dis / (1.0 * (num_cha - 1));
		for (int i = 1; i < num_cha; i++)
		{
			vec G_ls_p = G_cha_start_p + G_pp_t * i * G_delta_dis;
			vec JC_ls_p = JC_cha_start_p + JC_pp_t * i * JC_delta_dis;

			ans_cha_p.G_P = G_ls_p;
			ans_cha_p.G_SYS_HDM = ls_start_p.G_SYS_HDM;
			ans_cha_p.G_SYS_SL = ls_start_p.G_SYS_SL;
			ans_cha_p.JC_P = JC_ls_p;
			ans_cha_p.JC_SYS_HDM = ls_start_p.JC_SYS_HDM;
			ans_cha_p.JC_SYS_SL = ls_start_p.JC_SYS_SL;
			ans_cha_p.theta_nz = ls_start_p.theta_nz;
			ans_cha_p.theta_bd = ls_start_p.theta_bd;
			ans_cha_p.theta_fx = ls_start_p.theta_fx;
			ans_cha_p.theta_xq = ls_start_p.theta_xq;
			ans_cha_p.point_type = 1;

			in_DaoLu.Data.insert(in_DaoLu.Data.begin(), ans_cha_p);
		}
	}

	//接近点
	{
		vec G_cha_start_p = in_DaoLu.Data.at(0).G_P;
		vec G_pp_t = normalise(G_JieJinDian - G_cha_start_p);
		double G_pp_dis = tcDistance(G_JieJinDian, G_cha_start_p);
		double G_delta_dis = G_pp_dis / (1.0 * (num_cha - 1));

		vec JC_cha_start_p = in_DaoLu.Data.at(0).JC_P;
		vec JC_pp_t = normalise(JC_JieJinDian - JC_cha_start_p);
		double JC_pp_dis = tcDistance(JC_JieJinDian, JC_cha_start_p);
		double JC_delta_dis = JC_pp_dis / (1.0 * (num_cha - 1));

		for (int i = 1; i < num_cha; i++)
		{
			vec G_ls_p = G_cha_start_p + G_pp_t * i * G_delta_dis;
			vec JC_ls_p = JC_cha_start_p + JC_pp_t * i * JC_delta_dis;

			ans_cha_p.G_P = G_ls_p;
			ans_cha_p.G_SYS_HDM = ls_start_p.G_SYS_HDM;
			ans_cha_p.G_SYS_SL = ls_start_p.G_SYS_SL;
			ans_cha_p.JC_P = JC_ls_p;
			ans_cha_p.JC_SYS_HDM = ls_start_p.JC_SYS_HDM;
			ans_cha_p.JC_SYS_SL = ls_start_p.JC_SYS_SL;
			ans_cha_p.theta_nz = ls_start_p.theta_nz;
			ans_cha_p.theta_bd = ls_start_p.theta_bd;
			ans_cha_p.theta_fx = ls_start_p.theta_fx;
			ans_cha_p.theta_xq = ls_start_p.theta_xq;
			ans_cha_p.point_type = 3;

			in_DaoLu.Data.insert(in_DaoLu.Data.begin(), ans_cha_p);
		}
	}

	//接近点2
	{
		vec cal_p = G_JieJinDian;
		cal_p(0) = 0;
		double R = norm(cal_p);

		vec ans_G_p2 = G_JieJinDian;
		//说明先到达径向安全距离位置
		if ( abs(R - AnQuanR) < 0.001  )
		{
			ans_G_p2(0) = AnQuanX;
		}
		else
		{
			ans_G_p2(2) = AnQuanR;
		}
		vec ans_JC_p2 = trans_G_to_JC_in_BiaoZhun(ans_G_p2, A_start, C_start);

		ans_cha_p.G_P = ans_G_p2;
		ans_cha_p.G_SYS_HDM = ls_start_p.G_SYS_HDM;
		ans_cha_p.G_SYS_SL = ls_start_p.G_SYS_SL;
		ans_cha_p.JC_P = ans_JC_p2;
		ans_cha_p.JC_SYS_HDM = ls_start_p.JC_SYS_HDM;
		ans_cha_p.JC_SYS_SL = ls_start_p.JC_SYS_SL;
		ans_cha_p.theta_nz = ls_start_p.theta_nz;
		ans_cha_p.theta_bd = ls_start_p.theta_bd;
		ans_cha_p.theta_fx = ls_start_p.theta_fx;
		ans_cha_p.theta_xq = ls_start_p.theta_xq;
		ans_cha_p.point_type = 3;

		in_DaoLu.Data.insert(in_DaoLu.Data.begin(), ans_cha_p);
	}

	//起始安全点 不插值
	{
		ans_cha_p.G_P = G_AnQuanDianStart;
		ans_cha_p.G_SYS_HDM = ls_start_p.G_SYS_HDM;
		ans_cha_p.G_SYS_SL = ls_start_p.G_SYS_SL;
		ans_cha_p.JC_P = JC_AnQuanDianStart;
		ans_cha_p.JC_SYS_HDM = ls_start_p.JC_SYS_HDM;
		ans_cha_p.JC_SYS_SL = ls_start_p.JC_SYS_SL;
		ans_cha_p.theta_nz = ls_start_p.theta_nz;
		ans_cha_p.theta_bd = ls_start_p.theta_bd;
		ans_cha_p.theta_fx = ls_start_p.theta_fx;
		ans_cha_p.theta_xq = ls_start_p.theta_xq;
		ans_cha_p.point_type = 5;

		in_DaoLu.Data.insert(in_DaoLu.Data.begin(), ans_cha_p);
	}

	//退刀点
	{
		vec G_cha_start_p = in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P;
		vec G_pp_t = normalise(G_TuiDaoDian - G_cha_start_p);
		double G_pp_dis = tcDistance(G_TuiDaoDian, G_cha_start_p);
		double G_delta_dis = G_pp_dis / (1.0 * (num_cha - 1));

		vec JC_cha_start_p = in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P;
		vec JC_pp_t = normalise(JC_TuiDaoDian - JC_cha_start_p);
		double JC_pp_dis = tcDistance(JC_TuiDaoDian, JC_cha_start_p);
		double JC_delta_dis = JC_pp_dis / (1.0 * (num_cha - 1));

		for (int i = 1; i < num_cha; i++)
		{
			vec G_ls_p = G_cha_start_p + G_pp_t * i * G_delta_dis;
			vec JC_ls_p = JC_cha_start_p + JC_pp_t * i * JC_delta_dis;

			ans_cha_p.G_P = G_ls_p;
			ans_cha_p.G_SYS_HDM = ls_end_p.G_SYS_HDM;
			ans_cha_p.G_SYS_SL = ls_end_p.G_SYS_SL;
			ans_cha_p.JC_P = JC_ls_p;
			ans_cha_p.JC_SYS_HDM = ls_end_p.JC_SYS_HDM;
			ans_cha_p.JC_SYS_SL = ls_end_p.JC_SYS_SL;
			ans_cha_p.theta_nz = ls_end_p.theta_nz;
			ans_cha_p.theta_bd = ls_end_p.theta_bd;
			ans_cha_p.theta_fx = ls_end_p.theta_fx;
			ans_cha_p.theta_xq = ls_end_p.theta_xq;
			ans_cha_p.point_type = 2;

			in_DaoLu.Data.insert(in_DaoLu.Data.end(), ans_cha_p);
		}
	}

	//远离点
	{
		vec G_cha_start_p = in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P;
		vec G_pp_t = normalise(G_YuanLiDian - G_cha_start_p);
		double G_pp_dis = tcDistance(G_YuanLiDian, G_cha_start_p);
		double G_delta_dis = G_pp_dis / (1.0 * (num_cha - 1));

		vec JC_cha_start_p = in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P;
		vec JC_pp_t = normalise(JC_YuanLiDian - JC_cha_start_p);
		double JC_pp_dis = tcDistance(JC_YuanLiDian, JC_cha_start_p);
		double JC_delta_dis = JC_pp_dis / (1.0 * (num_cha - 1));

		for (int i = 1; i < num_cha; i++)
		{
			vec G_ls_p = G_cha_start_p + G_pp_t * i * G_delta_dis;
			vec JC_ls_p = JC_cha_start_p + JC_pp_t * i * JC_delta_dis;

			ans_cha_p.G_P = G_ls_p;
			ans_cha_p.G_SYS_HDM = ls_end_p.G_SYS_HDM;
			ans_cha_p.G_SYS_SL = ls_end_p.G_SYS_SL;
			ans_cha_p.JC_P = JC_ls_p;
			ans_cha_p.JC_SYS_HDM = ls_end_p.JC_SYS_HDM;
			ans_cha_p.JC_SYS_SL = ls_end_p.JC_SYS_SL;
			ans_cha_p.theta_nz = ls_end_p.theta_nz;
			ans_cha_p.theta_bd = ls_end_p.theta_bd;
			ans_cha_p.theta_fx = ls_end_p.theta_fx;
			ans_cha_p.theta_xq = ls_end_p.theta_xq;
			ans_cha_p.point_type = 4;

			in_DaoLu.Data.insert(in_DaoLu.Data.end(), ans_cha_p);
		}
	}

	//远离点2
	{
		vec cal_p = G_YuanLiDian;
		cal_p(0) = 0;
		double R = norm(cal_p);

		vec ans_G_p2 = G_YuanLiDian;
		//一定是先到达径向安全距离位置
		if (abs(R - AnQuanR) < 0.001)
		{
			ans_G_p2(0) = AnQuanX;
		}

		vec ans_JC_p2 = trans_G_to_JC_in_BiaoZhun(ans_G_p2, A_end, C_end);

		ans_cha_p.G_P = ans_G_p2;
		ans_cha_p.G_SYS_HDM = ls_end_p.G_SYS_HDM;
		ans_cha_p.G_SYS_SL = ls_end_p.G_SYS_SL;
		ans_cha_p.JC_P = ans_JC_p2;
		ans_cha_p.JC_SYS_HDM = ls_end_p.JC_SYS_HDM;
		ans_cha_p.JC_SYS_SL = ls_end_p.JC_SYS_SL;
		ans_cha_p.theta_nz = ls_end_p.theta_nz;
		ans_cha_p.theta_bd = ls_end_p.theta_bd;
		ans_cha_p.theta_fx = ls_end_p.theta_fx;
		ans_cha_p.theta_xq = ls_end_p.theta_xq;
		ans_cha_p.point_type = 4;

		in_DaoLu.Data.insert(in_DaoLu.Data.end(), ans_cha_p);
	}

	//结束安全点 不插值
	{
		ans_cha_p.G_P = G_AnQuanDianEnd;
		ans_cha_p.G_SYS_HDM = ls_end_p.G_SYS_HDM;
		ans_cha_p.G_SYS_SL = ls_end_p.G_SYS_SL;
		ans_cha_p.JC_P = JC_AnQuanDianEnd;
		ans_cha_p.JC_SYS_HDM = ls_end_p.JC_SYS_HDM;
		ans_cha_p.JC_SYS_SL = ls_end_p.JC_SYS_SL;
		ans_cha_p.theta_nz = ls_end_p.theta_nz;
		ans_cha_p.theta_bd = ls_end_p.theta_bd;
		ans_cha_p.theta_fx = ls_end_p.theta_fx;
		ans_cha_p.theta_xq = ls_end_p.theta_xq;
		ans_cha_p.point_type = 6;

		in_DaoLu.Data.insert(in_DaoLu.Data.end(), ans_cha_p);
	}

#pragma endregion

	return in_DaoLu;
}

//DL Miller_GX_Base::XiDao_JinTuiDao(int mo_type, DL in_DaoLu, xt_CanShu_JinTuiDao in_JinTuiDaoCanShu)
//{
//	vec G_JinDaoDian, JC_JinDaoDian;
//	vec G_TuiDaoDian, JC_TuiDaoDian;
//	vec G_JieJinDian, JC_JieJinDian;
//	vec G_YuanLiDian, JC_YuanLiDian;
//	vec G_AnQuanDianStart, JC_AnQuanDianStart;
//	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
//	vec Start_QieXiang;
//	vec End_QieXiang;
//
//	//计算进刀点
//	//计算进刀方向向量-
//	if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
//	{
//		Start_QieXiang = normalise(in_DaoLu.Data.at(0).G_P - in_DaoLu.Data.at(1).G_P);
//	}
//	else
//	{
//		Start_QieXiang = -tcRotZ(3, -in_JinTuiDaoCanShu.JinDaoJiaoDu) * tcX(3);
//	}
//	//第一个磨削点+进刀距离*进刀方向
//	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + in_DaoLu.Data.at(0).G_P;
//	JC_JinDaoDian = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz) * G_JinDaoDian;
//
//	//计算退刀点
//	//计算退刀方向向量+
//	if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
//	{
//		End_QieXiang = normalise(in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P - in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P);
//	}
//	else
//	{
//		End_QieXiang = -tcRotZ(3, -in_JinTuiDaoCanShu.TuiDaoJiaoDu) * tcX(3);
//	}
//	//最后磨削点+退刀距离*退刀方向
//	G_TuiDaoDian = (End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + in_DaoLu.Data.at(0).G_P);
//	JC_TuiDaoDian = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz) * G_TuiDaoDian;
//
//
//	//计算安全点
//	double AnQuanR = 0.0;
//	double AnQuanX = 0.0;
//	AnQuanR = in_DaoLu.maxR() + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
//	AnQuanX = in_DaoLu.minX() - in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi;
//	G_AnQuanDianStart = { AnQuanX ,AnQuanR ,0.0 };
//	G_AnQuanDianEnd = { AnQuanX ,AnQuanR ,0.0 };
//	JC_AnQuanDianStart = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz) * G_AnQuanDianStart;
//	JC_AnQuanDianEnd = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz) * G_AnQuanDianEnd;
//
//	//计算接近点
//	vec LSvec1, LSvec2;
//	//指向安全点的方向向量
//	LSvec1 = normalise(G_AnQuanDianStart - G_JinDaoDian);
//	//指向接近点方向的方向向量
//	LSvec2 = normalise(-tcRotZ(3, -in_JinTuiDaoCanShu.JieJinJiaoDu) * tcX(3));
//	if (LSvec2(1) <= LSvec1(1))
//	{
//		//说明先到达纵向安全距离位置
//		G_JieJinDian = G_JinDaoDian + (G_JinDaoDian(0) - AnQuanX) / cos(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu)) * LSvec2;
//	}
//	else
//	{
//		//说明先到达径向安全距离位置
//		G_JieJinDian = G_JinDaoDian + (AnQuanR - G_JinDaoDian(1)) / sin(tcRadians(in_JinTuiDaoCanShu.JieJinJiaoDu)) * LSvec2;
//	}
//	JC_JieJinDian = tcRotX(3, -in_DaoLu.Data.at(0).theta_nz) * G_JieJinDian;
//
//	//计算远离点
//	vec LSvec3;
//	LSvec3 = normalise(-tcRotZ(3, -in_JinTuiDaoCanShu.YuanLiJiaoDu) * tcX(3));
//	G_YuanLiDian = G_TuiDaoDian + (AnQuanR - G_TuiDaoDian(1)) * LSvec3;
//	JC_YuanLiDian = tcRotX(3, -in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).theta_nz) * G_YuanLiDian;
//
//	//将结果插入队列
//	//在前后各复制三个元素
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(in_DaoLu.Data.size() - 1));
//
//	//起始安全点
//	in_DaoLu.Data.at(0).G_P = G_AnQuanDianStart;
//	in_DaoLu.Data.at(0).JC_P = JC_AnQuanDianStart;
//	in_DaoLu.Data.at(0).point_type = 5;
//	//接近点
//	in_DaoLu.Data.at(1).G_P = G_JieJinDian;
//	in_DaoLu.Data.at(1).JC_P = JC_JieJinDian;
//	in_DaoLu.Data.at(1).point_type = 3;
//	//进刀点
//	in_DaoLu.Data.at(2).G_P = G_JinDaoDian;
//	in_DaoLu.Data.at(2).JC_P = JC_JinDaoDian;
//	in_DaoLu.Data.at(2).point_type = 1;
//	//结束安全点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P = G_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P = JC_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).point_type = 6;
//	//远离点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_P = G_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).JC_P = JC_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).point_type = 4;
//	//退刀点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_P = G_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).JC_P = JC_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).point_type = 2;
//
//	return in_DaoLu;
//}


//DL Miller_GX_Base::XiDao_QDM_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu)
//{
//
//#pragma region 变量声明
//	vec G_JinDaoDian, JC_JinDaoDian;
//	vec G_TuiDaoDian, JC_TuiDaoDian;
//	vec G_JieJinDian, JC_JieJinDian;
//	vec G_YuanLiDian, JC_YuanLiDian;
//	vec G_AnQuanDianStart, JC_AnQuanDianStart;
//	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
//	vec Start_QieXiang;
//	vec End_QieXiang;
//
//	int feibiao_xishu = -1;
//
//#pragma endregion
//
//	int index_start = 0;
//	int index_end = in_DaoLu.Data.size() - 1;
//
//	//12.26 修改为沿砂轮-x进退，前端输入没用
//#pragma region 计算进刀点
//	//计算进刀方向向量
//	//if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
//	//{
//	//	//后刀面坐标系X轴,方向
//	//	Start_QieXiang = in_DaoLu.Data.at(0).G_SYS_SL * (-tcX(3));
//	//}
//	//else
//	//{
//	//	//X轴绕Z旋转进刀角度--坐标自身的Y轴旋转-角度，背离材料，取x轴
//	//	mat ls_sys = in_DaoLu.Data.at(0).G_SYS_HDM * tcRotY(3, -in_JinTuiDaoCanShu.JinDaoJiaoDu);
//	//	Start_QieXiang = ls_sys * (tcX(3));
//	//}
//	//第一个磨削点+进刀距离*进刀方向
//	Start_QieXiang = in_DaoLu.Data.at(0).G_SYS_SL * (-tcX(3));
//	vec test_mo_p = in_DaoLu.Data.at(0).G_P;
//	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + in_DaoLu.Data.at(0).G_P;
//#pragma endregion
//
//#pragma region 计算退刀点
//	//计算退刀方向向量+  
//	//if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
//	//{
//	//	//后刀面坐标系X轴-切向
//	//	End_QieXiang = in_DaoLu.Data.at(index_end).G_SYS_HDM * (-tcX(3));
//	//}
//	//else
//	//{
//	//	//X轴绕Z轴旋转退刀角度
//	//	mat ls_sys = in_DaoLu.Data.at(index_end).G_SYS_HDM * tcRotY(3, in_JinTuiDaoCanShu.JinDaoJiaoDu);
//	//	End_QieXiang = ls_sys * (-tcX(3));
//	//}
//	//最后磨削点+退刀距离*退刀方向
//	End_QieXiang = in_DaoLu.Data.at(index_end).G_SYS_SL * (-tcX(3));
//	G_TuiDaoDian = End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + in_DaoLu.Data.at(index_end).G_P;
//#pragma endregion
//
//#pragma region 计算接近点
//	vec LSvec1, LSvec2;
//	//指向安全点的方向向量
//	//LSvec1 = normalise(G_AnQuanDianStart - G_JinDaoDian);
//
//	//指向接近点方向的方向向量
//	vec mo_p = in_DaoLu.Data.at(0).G_P;
//	double delta_dis = in_JinTuiDaoCanShu.JinDaoJuLi;
//	LSvec2 = in_DaoLu.Data.at(0).G_SYS_SL * (-tcX(3));
//
//	G_JieJinDian = G_JinDaoDian + normalise(LSvec2) * delta_dis;
//#pragma endregion
//
//#pragma region 计算安全点
//	//安全点转到进刀点与Z轴所在平面
//	double AnQuanR = 0.0;
//	double AnQuanZ = 0.0;
//	AnQuanR = in_DaoLu.anquandian.X + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
//	AnQuanZ = in_DaoLu.anquandian.Z - in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi; //工件坐标中参考，刀尖前
//	G_AnQuanDianStart = { AnQuanR , 0.0 ,AnQuanZ }; //11.25 ???
//
//	vec mo_p0 = in_DaoLu.Data.at(0).G_P;
//	mo_p0(2) = 0;
//	double delta_dis0 = in_JinTuiDaoCanShu.JinDaoJuLi;
//	vec LSvec30 = in_DaoLu.Data.at(0).G_SYS_SL * (-tcX(3));
//
//	double safe_dis = in_JinTuiDaoCanShu.JingXiangAnQuanJuLi; //删除 - norm(mo_p0)1.18 
//	G_AnQuanDianStart = G_JieJinDian + normalise(LSvec30) * safe_dis;
//
//#pragma endregion
//
//#pragma region 计算远离点
//	vec LSvec3;
//	//指向远离点方向的方向向量
//	mo_p = in_DaoLu.Data.at(index_end).G_P;
//	mo_p(2) = 0;
//	delta_dis = in_JinTuiDaoCanShu.TuiDaoJuLi;
//	LSvec3 = in_DaoLu.Data.at(index_end).G_SYS_SL * (-tcX(3));
//
//	G_YuanLiDian = G_TuiDaoDian + normalise(LSvec3) * delta_dis;
//
//	double safe_dis0 = in_JinTuiDaoCanShu.JingXiangAnQuanJuLi; //- norm(mo_p0)
//	//结束安全点
//	G_AnQuanDianEnd = G_YuanLiDian + (normalise(LSvec3) * safe_dis0);
//#pragma endregion
//	//记录进退刀的后刀面坐标系及砂轮坐标系-11.1
//	mat sys_qdm_start = in_DaoLu.Data.at(0).G_SYS_HDM;
//	mat sys_sl_start = in_DaoLu.Data.at(0).G_SYS_SL;
//	mat sys_qdm_end = in_DaoLu.Data.at(index_end).G_SYS_HDM;
//	mat sys_sl_end = in_DaoLu.Data.at(index_end).G_SYS_SL;
//
//#pragma region 将结果插入队列
//	//在前后各复制三个元素
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//
//	//起始安全点
//	in_DaoLu.Data.at(0).G_P = G_AnQuanDianStart;
//	in_DaoLu.Data.at(0).JC_P = JC_AnQuanDianStart;
//	in_DaoLu.Data.at(0).point_type = 5;
//	in_DaoLu.Data.at(0).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(0).G_SYS_SL = sys_sl_start;
//	//接近点
//	in_DaoLu.Data.at(1).G_P = G_JieJinDian;
//	in_DaoLu.Data.at(1).JC_P = JC_JieJinDian;
//	in_DaoLu.Data.at(1).point_type = 3;
//	in_DaoLu.Data.at(1).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(1).G_SYS_SL = sys_sl_start;
//	//进刀点
//	in_DaoLu.Data.at(2).G_P = G_JinDaoDian;
//	in_DaoLu.Data.at(2).JC_P = JC_JinDaoDian;
//	in_DaoLu.Data.at(2).point_type = 1;
//	in_DaoLu.Data.at(2).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(2).G_SYS_SL = sys_sl_start;
//	//结束安全点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P = G_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P = JC_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).point_type = 6;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_SL = sys_sl_end;
//	//远离点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_P = G_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).JC_P = JC_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).point_type = 4;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_SL = sys_sl_end;
//	//退刀点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_P = G_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).JC_P = JC_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).point_type = 2;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_SL = sys_sl_end;
//#pragma endregion
//
//	return in_DaoLu;
//}
//
////前刀面进退刀
//DL Miller_GX_Base::XiDao_LXC_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu)
//{
//#pragma region 变量声明
//	vec G_JinDaoDian, JC_JinDaoDian;
//	vec G_TuiDaoDian, JC_TuiDaoDian;
//	vec G_JieJinDian, JC_JieJinDian;
//	vec G_YuanLiDian, JC_YuanLiDian;
//	vec G_AnQuanDianStart, JC_AnQuanDianStart;
//	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
//	vec Start_QieXiang;
//	vec End_QieXiang;
//
//	int feibiao_xishu = -1;
//
//#pragma endregion
//
//	int index_start = 0;
//	int index_end = in_DaoLu.Data.size() - 1;
//
//#pragma region 计算进刀点
//	//计算进刀方向向量
//	if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴,方向
//		Start_QieXiang = in_DaoLu.Data.at(0).G_SYS_HDM * (-tcX(3));
//	}
//	else
//	{
//		//X轴绕Z旋转进刀角度--坐标自身的Y轴旋转-角度，背离材料，取x轴
//		mat ls_sys = in_DaoLu.Data.at(0).G_SYS_HDM * tcRotY(3, in_JinTuiDaoCanShu.JinDaoJiaoDu);
//		Start_QieXiang = ls_sys * (-tcX(3));
//	}
//	//第一个磨削点+进刀距离*进刀方向
//	vec test_mo_p = in_DaoLu.Data.at(0).G_P;
//	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + in_DaoLu.Data.at(0).G_P;
//#pragma endregion
//
//#pragma region 计算退刀点
//	//计算退刀方向向量+  
//	if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴-切向
//		End_QieXiang = in_DaoLu.Data.at(index_end).G_SYS_HDM * (tcX(3));
//	}
//	else
//	{
//		//X轴绕Z轴旋转退刀角度
//		mat ls_sys = in_DaoLu.Data.at(index_end).G_SYS_HDM * tcRotY(3, -in_JinTuiDaoCanShu.JinDaoJiaoDu);
//		End_QieXiang = ls_sys * (tcX(3));
//	}
//	//最后磨削点+退刀距离*退刀方向
//	G_TuiDaoDian = End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + in_DaoLu.Data.at(index_end).G_P;
//#pragma endregion
//
//#pragma region 计算安全点
//	//安全点转到进刀点与Z轴所在平面
//	double AnQuanR = 0.0;
//	double AnQuanZ = 0.0;
//	AnQuanR = in_DaoLu.anquandian.X + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
//	AnQuanZ = in_DaoLu.anquandian.Z - in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi; //工件坐标中参考，刀尖前
//	G_AnQuanDianStart = { AnQuanR , 0.0 ,AnQuanZ }; //11.25 ???
//
//
//	double ang_zhuan = tcDegree(atan(abs(G_JinDaoDian(1)) / abs(G_JinDaoDian(0)))); //x+为基准
//	//判定象限
//	if (G_JinDaoDian(1) > 0.0 && G_JinDaoDian(0) > 0.0)
//	{
//		ang_zhuan = ang_zhuan;
//	}
//	if (G_JinDaoDian(1) > 0.0 && G_JinDaoDian(0) < 0.0)
//	{
//		ang_zhuan = 180.0 - ang_zhuan;
//	}
//	if (G_JinDaoDian(1) < 0.0 && G_JinDaoDian(0) < 0.0)
//	{
//		ang_zhuan = 180.0 + ang_zhuan;
//	}
//	if (G_JinDaoDian(1) < 0.0 && G_JinDaoDian(0) > 0.0)
//	{
//		ang_zhuan = -ang_zhuan;
//	}
//	G_AnQuanDianStart = tcRotZ(3, ang_zhuan) * G_AnQuanDianStart;
//#pragma endregion
//
//#pragma region 计算接近点
//	vec LSvec1, LSvec2;
//	//指向安全点的方向向量
//	LSvec1 = normalise(G_AnQuanDianStart - G_JinDaoDian);
//
//	//指向接近点方向的方向向量
//	vec mo_p = in_DaoLu.Data.at(0).G_P;
//	vec sl_x = in_DaoLu.Data.at(0).G_SYS_SL.col(0);
//	vec sl_z = in_DaoLu.Data.at(0).G_SYS_SL.col(2);
//	vec jia_p = mo_p + (-sl_x * 150);
//	vec jia_R = { jia_p(0), jia_p(1), 0.0 }; //假想点半径方向
//
//	vec cal_t = normalise(jia_R - dot(jia_R, sl_z) * sl_z);
//	vec down_p = jia_p + (-cal_t * 150);
//	double down_R = sqrt(down_p(0) * down_p(0) + down_p(1) * down_p(1)); //低点半径
//
//	double delta_R = 0.0;
//	if (AnQuanR > down_R)
//	{
//		delta_R = AnQuanR - down_R;
//	}
//	else
//	{
//		delta_R = AnQuanR;
//	}
//
//	//进刀点加上半径方向偏置，保证芯厚出径向安全距离
//	G_JieJinDian = G_JinDaoDian + (normalise(cal_t) * abs(delta_R));  //11.26加绝对值
//
//	G_AnQuanDianStart = G_JieJinDian + (normalise(cal_t) * abs(delta_R));
//#pragma endregion
//
//#pragma region 计算远离点
//	vec LSvec3;
//	//指向远离点方向的方向向量
//	mo_p = in_DaoLu.Data.at(index_end).G_P;
//	sl_x = in_DaoLu.Data.at(index_end).G_SYS_SL.col(0);
//	sl_z = in_DaoLu.Data.at(index_end).G_SYS_SL.col(2);
//	jia_p = mo_p + (-sl_x * 150);
//	jia_R = { jia_p(0), jia_p(1), 0.0 }; //假想点半径方向
//
//	cal_t = normalise(jia_R - dot(jia_R, sl_z) * sl_z);
//	down_p = jia_p + (-cal_t * 150);
//	down_R = sqrt(down_p(0) * down_p(0) + down_p(1) * down_p(1)); //低点半径
//
//	//delta_R = AnQuanR - down_R; //后刀面计算时，半径差值为负值，说明，最低点过了安全半径，偏移取绝对值11.14
//	if (AnQuanR > down_R)
//	{
//		delta_R = AnQuanR - down_R;
//	}
//	else
//	{
//		delta_R = AnQuanR;
//	}
//
//	G_YuanLiDian = G_TuiDaoDian + (normalise(cal_t) * abs(delta_R)); //退刀点加上半径方向偏置，保证芯厚出径向安全距离
//	//结束安全点
//
//	G_AnQuanDianEnd = G_YuanLiDian + (normalise(cal_t) * abs(delta_R));
//#pragma endregion
//	//记录进退刀的后刀面坐标系及砂轮坐标系-11.1
//	mat sys_qdm_start = in_DaoLu.Data.at(0).G_SYS_HDM;
//	mat sys_sl_start = in_DaoLu.Data.at(0).G_SYS_SL;
//	mat sys_qdm_end = in_DaoLu.Data.at(index_end).G_SYS_HDM;
//	mat sys_sl_end = in_DaoLu.Data.at(index_end).G_SYS_SL;
//
//
//
//#pragma region 将结果插入队列
//	//在前后各复制三个元素
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//
//	//起始安全点
//	in_DaoLu.Data.at(0).G_P = G_AnQuanDianStart;
//	in_DaoLu.Data.at(0).JC_P = JC_AnQuanDianStart;
//	in_DaoLu.Data.at(0).point_type = 5;
//	in_DaoLu.Data.at(0).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(0).G_SYS_SL = sys_sl_start;
//	//接近点
//	in_DaoLu.Data.at(1).G_P = G_JieJinDian;
//	in_DaoLu.Data.at(1).JC_P = JC_JieJinDian;
//	in_DaoLu.Data.at(1).point_type = 3;
//	in_DaoLu.Data.at(1).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(1).G_SYS_SL = sys_sl_start;
//	//进刀点
//	in_DaoLu.Data.at(2).G_P = G_JinDaoDian;
//	in_DaoLu.Data.at(2).JC_P = JC_JinDaoDian;
//	in_DaoLu.Data.at(2).point_type = 1;
//	in_DaoLu.Data.at(2).G_SYS_HDM = sys_qdm_start;
//	in_DaoLu.Data.at(2).G_SYS_SL = sys_sl_start;
//	//结束安全点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P = G_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P = JC_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).point_type = 6;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_SL = sys_sl_end;
//	//远离点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_P = G_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).JC_P = JC_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).point_type = 4;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_SL = sys_sl_end;
//	//退刀点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_P = G_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).JC_P = JC_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).point_type = 2;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_HDM = sys_qdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_SL = sys_sl_end;
//#pragma endregion
//
//	return in_DaoLu;
//}
//
////后刀面进退刀
//DL Miller_GX_Base::XiDao_HDM_JinTuiDao(DL& in_DaoLu, xt_CanShu_JinTuiDao& in_JinTuiDaoCanShu)
//{
//#pragma region 变量声明
//	vec G_JinDaoDian, JC_JinDaoDian;
//	vec G_TuiDaoDian, JC_TuiDaoDian;
//	vec G_JieJinDian, JC_JieJinDian;
//	vec G_YuanLiDian, JC_YuanLiDian;
//	vec G_AnQuanDianStart, JC_AnQuanDianStart;
//	vec G_AnQuanDianEnd, JC_AnQuanDianEnd;
//	vec Start_QieXiang;
//	vec End_QieXiang;
//
//	int feibiao_xishu = -1;
//
//#pragma endregion
//
//	int index_start = 0;
//	int index_end = in_DaoLu.Data.size() - 1;
//
//#pragma region 计算进刀点
//	//计算进刀方向向量
//	if (in_JinTuiDaoCanShu.JinDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴,方向
//		Start_QieXiang = in_DaoLu.Data.at(0).G_SYS_HDM * tcX(3);
//	}
//	else
//	{
//		//X轴绕Z旋转进刀角度--坐标自身的Y轴旋转-角度，背离材料，取x轴
//		mat ls_sys = in_DaoLu.Data.at(0).G_SYS_HDM * tcRotY(3, -in_JinTuiDaoCanShu.JinDaoJiaoDu);
//		Start_QieXiang = ls_sys * tcX(3);
//	}
//	//第一个磨削点+进刀距离*进刀方向
//	vec test_mo_p = in_DaoLu.Data.at(0).G_P;
//	G_JinDaoDian = Start_QieXiang * in_JinTuiDaoCanShu.JinDaoJuLi + in_DaoLu.Data.at(0).G_P;
//#pragma endregion
//
//#pragma region 计算退刀点
//	//计算退刀方向向量+  
//	if (in_JinTuiDaoCanShu.TuiDaoXiangQie == 1)
//	{
//		//后刀面坐标系X轴-切向
//		End_QieXiang = in_DaoLu.Data.at(index_end).G_SYS_HDM * (-tcX(3));
//	}
//	else
//	{
//		//X轴绕Z轴旋转退刀角度
//		mat ls_sys = in_DaoLu.Data.at(index_end).G_SYS_HDM * tcRotY(3, in_JinTuiDaoCanShu.JinDaoJiaoDu);
//		End_QieXiang = ls_sys * (-tcX(3));
//	}
//	//最后磨削点+退刀距离*退刀方向
//	G_TuiDaoDian = End_QieXiang * in_JinTuiDaoCanShu.TuiDaoJuLi + in_DaoLu.Data.at(index_end).G_P;
//	//G_TuiDaoDian = in_DaoLu.Data.at(index_end).G_P;
//#pragma endregion
//
//#pragma region 计算安全点
//	//安全点转到进刀点与Z轴所在平面
//	double AnQuanR = 0.0;
//	double AnQuanZ = 0.0;
//	AnQuanR = in_DaoLu.anquandian.X + in_JinTuiDaoCanShu.JingXiangAnQuanJuLi;
//	AnQuanZ = in_DaoLu.anquandian.Z - in_JinTuiDaoCanShu.ZhouXiangAnQuanJuLi; //工件坐标中参考，刀尖前
//	G_AnQuanDianStart = { AnQuanR , 0.0 ,AnQuanZ }; //11.25 ???
//
//
//	double ang_zhuan = tcDegree(atan(abs(G_JinDaoDian(1)) / abs(G_JinDaoDian(0)))); //x+为基准
//	//判定象限
//	if (G_JinDaoDian(1) > 0.0 && G_JinDaoDian(0) > 0.0)
//	{
//		ang_zhuan = ang_zhuan;
//	}
//	if (G_JinDaoDian(1) > 0.0 && G_JinDaoDian(0) < 0.0)
//	{
//		ang_zhuan = 180.0 - ang_zhuan;
//	}
//	if (G_JinDaoDian(1) < 0.0 && G_JinDaoDian(0) < 0.0)
//	{
//		ang_zhuan = 180.0 + ang_zhuan;
//	}
//	if (G_JinDaoDian(1) < 0.0 && G_JinDaoDian(0) > 0.0)
//	{
//		ang_zhuan = -ang_zhuan;
//	}
//	//G_AnQuanDianStart = tcRotZ(3, ang_zhuan) * G_AnQuanDianStart;
//	//改为接近点工件轴向偏置 -1.10 
//
//#pragma endregion
//
//#pragma region 计算接近点
//	vec LSvec1, LSvec2;
//	//指向安全点的方向向量
//	LSvec1 = normalise(G_AnQuanDianStart - G_JinDaoDian);
//
//	//指向接近点方向的方向向量
//	vec mo_p = in_DaoLu.Data.at(0).G_P;
//	vec sl_x = in_DaoLu.Data.at(0).G_SYS_SL.col(0);
//	vec sl_z = in_DaoLu.Data.at(0).G_SYS_SL.col(2);
//	vec jia_p = mo_p + (-sl_x * 150);
//	vec jia_R = { jia_p(0), jia_p(1), 0.0 }; //假想点半径方向
//
//	vec cal_t = normalise(jia_R - dot(jia_R, sl_z) * sl_z);
//	vec down_p = jia_p + (-cal_t * 150);
//	double down_R = sqrt(down_p(0) * down_p(0) + down_p(1) * down_p(1)); //低点半径
//
//	double delta_R = AnQuanR - down_R;
//	if (AnQuanR > down_R)
//	{
//		delta_R = AnQuanR - down_R;
//	}
//	else
//	{
//		delta_R = AnQuanR;
//	}
//	LSvec2 = { G_JinDaoDian(0), G_JinDaoDian(1), 0.0 }; //进刀点半径方向
//	//进刀点加上半径方向偏置，保证芯厚出径向安全距离
//	//G_JieJinDian = G_JinDaoDian + (normalise(cal_t) * abs(delta_R));  //11.26加绝对值
//
//	//砂轮法向偏置-1.10
//	G_JieJinDian = G_JinDaoDian + (normalise(sl_z) * abs(in_JinTuiDaoCanShu.JinDaoJuLi));
//	//改为接近点工件轴向偏置 -1.10 
//	G_AnQuanDianStart = G_JieJinDian + (normalise(-tcZ(3)) * abs(AnQuanZ));
//
//#pragma endregion
//
//#pragma region 计算远离点
//	vec LSvec3;
//	//指向远离点方向的方向向量
//	mo_p = in_DaoLu.Data.at(index_end).G_P;
//	sl_x = in_DaoLu.Data.at(index_end).G_SYS_SL.col(0);
//	sl_z = in_DaoLu.Data.at(index_end).G_SYS_SL.col(2);
//	jia_p = mo_p + (-sl_x * 150);
//	jia_R = { jia_p(0), jia_p(1), 0.0 }; //假想点半径方向
//
//	cal_t = normalise(jia_R - dot(jia_R, sl_z) * sl_z);
//	down_p = jia_p + (-cal_t * 150);
//	down_R = sqrt(down_p(0) * down_p(0) + down_p(1) * down_p(1)); //低点半径
//
//	delta_R = AnQuanR - down_R; //后刀面计算时，半径差值为负值，说明，最低点过了安全半径，偏移取绝对值11.14
//	if (AnQuanR > down_R)
//	{
//		delta_R = AnQuanR - down_R;
//	}
//	else
//	{
//		delta_R = AnQuanR;
//	}
//	LSvec3 = { G_TuiDaoDian(0), G_TuiDaoDian(1), 0.0 }; //退刀点半径方向
//
//	//G_YuanLiDian = G_TuiDaoDian + (normalise(cal_t) * abs(delta_R)); //退刀点加上半径方向偏置，保证芯厚出径向安全距离
//	////结束安全点
//	//G_AnQuanDianEnd = G_YuanLiDian + (normalise(cal_t) * abs(delta_R));
//
//	G_YuanLiDian = G_TuiDaoDian + (normalise(sl_z) * abs(in_JinTuiDaoCanShu.JinDaoJuLi)); //退刀点加上半径方向偏置，保证芯厚出径向安全距离
//	//结束安全点
//	G_AnQuanDianEnd = G_YuanLiDian + (normalise(sl_z) * abs(in_JinTuiDaoCanShu.JinDaoJuLi));
//#pragma endregion
//	//记录进退刀的后刀面坐标系及砂轮坐标系-11.1
//	mat sys_hdm_start = in_DaoLu.Data.at(0).G_SYS_HDM;
//	mat sys_sl_start = in_DaoLu.Data.at(0).G_SYS_SL;
//	mat sys_hdm_end = in_DaoLu.Data.at(index_end).G_SYS_HDM;
//	mat sys_sl_end = in_DaoLu.Data.at(index_end).G_SYS_SL;
//
//
//
//#pragma region 将结果插入队列
//	//在前后各复制三个元素
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.begin(), in_DaoLu.Data.at(0));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//	in_DaoLu.Data.insert(in_DaoLu.Data.end(), in_DaoLu.Data.at(index_end));
//
//	//起始安全点
//	in_DaoLu.Data.at(0).G_P = G_AnQuanDianStart;
//	in_DaoLu.Data.at(0).JC_P = JC_AnQuanDianStart;
//	in_DaoLu.Data.at(0).point_type = 5;
//	in_DaoLu.Data.at(0).G_SYS_HDM = sys_hdm_start;
//	in_DaoLu.Data.at(0).G_SYS_SL = sys_sl_start;
//	//接近点
//	in_DaoLu.Data.at(1).G_P = G_JieJinDian;
//	in_DaoLu.Data.at(1).JC_P = JC_JieJinDian;
//	in_DaoLu.Data.at(1).point_type = 3;
//	in_DaoLu.Data.at(1).G_SYS_HDM = sys_hdm_start;
//	in_DaoLu.Data.at(1).G_SYS_SL = sys_sl_start;
//	//进刀点
//	in_DaoLu.Data.at(2).G_P = G_JinDaoDian;
//	in_DaoLu.Data.at(2).JC_P = JC_JinDaoDian;
//	in_DaoLu.Data.at(2).point_type = 1;
//	in_DaoLu.Data.at(2).G_SYS_HDM = sys_hdm_start;
//	in_DaoLu.Data.at(2).G_SYS_SL = sys_sl_start;
//	//结束安全点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_P = G_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).JC_P = JC_AnQuanDianEnd;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).point_type = 6;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_HDM = sys_hdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 1).G_SYS_SL = sys_sl_end;
//	//远离点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_P = G_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).JC_P = JC_YuanLiDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).point_type = 4;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_HDM = sys_hdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 2).G_SYS_SL = sys_sl_end;
//	//退刀点
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_P = G_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).JC_P = JC_TuiDaoDian;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).point_type = 2;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_HDM = sys_hdm_end;
//	in_DaoLu.Data.at(in_DaoLu.Data.size() - 3).G_SYS_SL = sys_sl_end;
//#pragma endregion
//
//	return in_DaoLu;
//}


DL Miller_GX_Base::XiDao_HDM_MoXue_BianHuan(DL& in_DaoLu, xt_CanShu_MoXue_BianHuan& in_BianHuan)
{
	//变量声明
	vec changdu, banjing, faxiang;
	double niuzhuan;
	//长度变换向量
	changdu = { in_BianHuan.ChangDuPianZhi,0,0 };
	//径向变换向量
	banjing = { 0,in_BianHuan.JingXiangPianZhi,0 };
	//扭转变换角
	niuzhuan = in_BianHuan.XuanZhuanPianZhi;
	mat G_SYS_HDM;
	for (vector<DL_P>::iterator it = in_DaoLu.Data.begin(); it != in_DaoLu.Data.end(); it++)
	{
		G_SYS_HDM = (*it).G_SYS_HDM;
		faxiang = G_SYS_HDM.col(2) * in_BianHuan.FaXiangPianZhi;
		(*it).G_P = (*it).G_P + faxiang + banjing + changdu;
		//(*it).JC_P = tcRotX(3, -(*it).beta_xz) * (*it).G_P;
		//--不变换：JC点坐标及坐标系6.6
		//(*it).JC_P = tcRotZ(3, -(*it).theta_bd) * tcY(3) * ptr_tool->w_c2g
		//	+tcRotZ(3, -(*it).theta_bd)*tcRotX(3, -(*it).theta_nz) * (*it).G_P; //8.14 mark
		(*it).theta_nz = (*it).theta_nz + niuzhuan;

		//更新其他
		(*it).G_SYS_HDM = tcRotX(3, niuzhuan) * (*it).G_SYS_HDM;
		(*it).G_SYS_SL	= tcRotX(3, niuzhuan) * (*it).G_SYS_SL;
							   
		(*it).JC_P		= tcRotX(3, niuzhuan) * (*it).JC_P;
		(*it).JC_SYS_HDM= tcRotX(3, niuzhuan) * (*it).JC_SYS_HDM;
		(*it).JC_SYS_SL	= tcRotX(3, niuzhuan) * (*it).JC_SYS_SL;

	}
	return in_DaoLu;
}

DL Miller_GX_Base::XiDao_HDM_MoXue_XunHuan(DL& in_DaoLu, xt_CanShu_MoXue_XunHuan& in_XunHuan)
{
	if (in_XunHuan.CanShu.size() == 0)
	{
		return in_DaoLu;
	}
	else
	{
		DL LS_DaoLu;
		DL LS_JieGuo;
		//基本刀路
		LS_DaoLu.Data.assign(in_DaoLu.Data.begin(), in_DaoLu.Data.end());

		for (vector<xt_CanShu_HDM_MoXue_d_XunHuan>::iterator it = in_XunHuan.CanShu.begin();
			it != in_XunHuan.CanShu.end();
			it++)
		{
			switch ((*it).LeiXing)
			{
			case 0://沿砂轮半径方向循环
				//遍历所有循环
				for (int i = 0; i < (*it).CiShu; i++)
				{
					// 插入刀路
					LS_JieGuo.Data.insert(LS_JieGuo.Data.begin(), LS_DaoLu.Data.begin(), LS_DaoLu.Data.end());
					//计算下一个刀路位置
					for (vector<DL_P>::iterator it2 = LS_DaoLu.Data.begin(); it2 != LS_DaoLu.Data.end(); it2++)
					{
						(*it2).JC_P = (*it2).JC_P - (*it2).JC_SYS_SL.col(0) * (*it).YuLiang / ((double)(*it).CiShu);
						//(*it2).G_P = tcRotX(3, (*it2).beta_xz) * (*it2).JC_P;
						(*it2).G_P = tcRotX(3, (*it2).theta_nz) * (*it2).JC_P;
					}
				}
				break;

			default:
				break;
			}
		}
		return LS_JieGuo;
	}
}

DL Miller_GX_Base::XiDao_HDM_MoXue_ZhenLie(DL& in_DaoLu, xt_CanShu_MoXue_ZhenLie& in_ZhenLie)
{
	double dengfenjiao = 0.0;
	DL ZL_DL;
	//结果中插入第一行
	ZL_DL.Data.insert(ZL_DL.Data.end(), in_DaoLu.Data.begin(), in_DaoLu.Data.end());
	if (in_ZhenLie.DengFen == 0)
	{
		dengfenjiao = 360.0 / ((double)in_ZhenLie.RenShu);
		//阵列
		for (int i = 1; i < in_ZhenLie.RenShu; i++)
		{
			//对每一个点计算阵列后的相位角
			for (vector<DL_P>::iterator it = in_DaoLu.Data.begin(); it != in_DaoLu.Data.end(); it++)
			{
				(*it).theta_nz = (*it).theta_nz + dengfenjiao;
			}
			//将阵列结果插到队尾
			ZL_DL.Data.insert(ZL_DL.Data.end(), in_DaoLu.Data.begin(), in_DaoLu.Data.end());
		}
	}
	else
	{
		for (int i = 1; i < in_ZhenLie.BDF_RenShu; i++)
		{
			//阵列
			dengfenjiao = in_ZhenLie.WeiZhi.at(i, 0) - in_ZhenLie.WeiZhi.at(i - 1, 0);
			//对每一个点计算阵列后的相位角
			for (vector<DL_P>::iterator it = in_DaoLu.Data.begin(); it != in_DaoLu.Data.end(); it++)
			{
				(*it).theta_nz = (*it).theta_nz + dengfenjiao;
			}
			//将阵列结果插到队尾
			ZL_DL.Data.insert(ZL_DL.Data.end(), in_DaoLu.Data.begin(), in_DaoLu.Data.end());
		}
	}
	return ZL_DL;
}

vec Miller_GX_Base::trans_G_to_JC_in_BiaoZhun(vec& G_P, double a, double c)
{
	vec JC_P = tcRotZ(3, -c)* tcY(3)* ptr_tool->w_c2g
		+ tcRotZ(3, -c) * tcRotX(3, -a) * G_P;
	return JC_P;
}

mat Miller_GX_Base::trans_G_to_JC_in_BiaoZhun(mat& G_SYS, double a, double c)
{
	mat JC_SYS = tcRotZ(3, -c) * tcRotX(3, -a) * G_SYS;
	return JC_SYS;
}

vec Miller_GX_Base::trans_G_to_JC_in_DaiJie(vec& G_P, double a, double c)
{
	vec JC_P = tcRotZ(3, c) * tcRotY(3, a) * G_P;
	return JC_P;
}

mat Miller_GX_Base::trans_G_to_JC_in_DaiJie(mat& G_SYS, double a, double c)
{
	mat JC_SYS = tcRotZ(3, c) * tcRotY(3, a) * G_SYS;
	return JC_SYS;
}

vec Miller_GX_Base::trans_G_to_JC_in_ABS(vec& G_P, double a, double c)
{
	vec JC_P = tcRotZ(3, c) * tcRotY(3, a) * (tcRotZ(3, -90.0) * G_P);
	return JC_P;
}


int Miller_GX_Base::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(
		storage_lib.file_dir_gx_base_canshu, pos, (char*)&base_data, sizeof(base_data)
	);
	return pos;
}

void Miller_GX_Base::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_gx_base_canshu, pos, (char*)&base_data, sizeof(base_data)
	);
}










