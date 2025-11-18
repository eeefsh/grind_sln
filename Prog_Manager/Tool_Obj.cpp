#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Tool_Obj.h"
#include "generator_line.h"


void cal_xx_lx_by_kjx(KongJianXian& in_kjx, Cal_XingXian* ans_xx, Cal_LouXuan* ans_lx)
{
		int count_p = in_kjx.count_points();
		//取所有坐标
		mat all_p = in_kjx.get_all_p().t();
		mat points = all_p;

		//点转到平面计算不对， 8.11 zy
		//求所有的半径
		//all_p.row(0).fill(0.0);
		for (size_t i = 0; i < count_p; i++)
		{
			vec ls_p = all_p.col(i);
			ls_p(0) = 0.0;
			double r = norm(ls_p);
			points.col(i)(1) = r;
			points.col(i)(2) = 0.0;
		}
		//所有Z坐标等于0
		//points.row(2).fill(0.0);

		ans_xx->init_data(points);

		for (int i = 0; i < count_p ; i++)
		{
#pragma region 型线

#pragma endregion

#pragma region 螺旋
			//螺旋-直角坐标点
			vec3 p_lx = in_kjx.point(i);

			//半径方向-向外>>轴向向外 8.11
			vec3 cal_tr_p = p_lx;
			cal_tr_p(0) = 0.0;
			vec t_R = normalise(cal_tr_p);
			//相位角
			double XW = deltaRotAngle(tcY(3), t_R, tcX(3));
			//螺旋-柱坐标点
			double ls_R = norm(p_lx); //y = 半径
			vec3 p_lx_zhu = { p_lx(0), ls_R, XW };

			//柱坐标系
			vec zhu_X = ans_xx->BG_T(i); //X轴：相位0截形的切向
			vec zhu_Y = tcZ(3); //Z轴：	同刀具Z轴
			vec zhu_Z = cross(zhu_X, zhu_Y); //Y轴：

			//法0后面坐标系
			vec ls_T;
			if (i == count_p - 1)
			{
				//vec ls_next = in_vp.col(i + 1);
				ls_T =  -ans_lx->BG_nX(i - 1);
			}
			else
			{
				vec ls_p2 = in_kjx.point(i + 1);
				ls_T = normalise(ls_p2 - p_lx);
			}
			vec fa_X = -ls_T;//X轴：	刃线反切向
			vec fa_Z = normalise(cross(fa_X, normalise(cross(tcX(3), t_R))));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
			vec fa_Y = cross(fa_Z, fa_X);//Z轴：	后角线方向（Z轴×X轴）

			//只有立铣刀会用此函数，直纹方向默认前角为0, 9.19
			vec ls_zhiwen = tcRotX(3, 0.0) * (-tcY(3));

			vec ans_p2 = { p_lx_zhu(0), p_lx_zhu(1), p_lx_zhu(2),
					p_lx(0), p_lx(1), p_lx(2),
					t_R(0), t_R(1), t_R(2),
					zhu_X(0), zhu_X(1), zhu_X(2),
					zhu_Y(0), zhu_Y(1), zhu_Y(2),
					zhu_Z(0), zhu_Z(1), zhu_Z(2),
					fa_X(0), fa_X(1), fa_X(2),
					fa_Y(0), fa_Y(1), fa_Y(2),
					fa_Z(0), fa_Z(1), fa_Z(2),
					ans_xx->Lenth_At_Point(i),
					ls_zhiwen(0),ls_zhiwen(1),ls_zhiwen(2)
			};

			ans_lx->Data_Of_Points.insert_cols(ans_lx->Data_Of_Points.n_cols, ans_p2);

#pragma endregion
		}

		//最后一个点
		{
			//vec3 p_xx = ans_xx->BG_P(ans_xx->n_P() - 1);
			//vec3 next_p = in_kjx.point(count_p - 1);
			//next_p(2) = 0.0;
			//double next_R = norm(next_p); //y = 半径
			//vec3 next_xx = { next_p(0),next_R, 0.0 };

			//vec3 X_xx = normalise(next_xx - p_xx);
			//vec3 Y_xx = tcRotZ(3, 90.0) * X_xx;
			//vec3 Z_xx = cross(X_xx, Y_xx);

			//double len_xx = tcDistance(next_xx, p_xx);

			//vec ans_p = { p_xx(0), p_xx(1), p_xx(2),
			//		X_xx(0), X_xx(1), X_xx(2),
			//		Y_xx(0), Y_xx(1), Y_xx(2),
			//		Z_xx(0), Z_xx(1), Z_xx(2),
			//		len_xx };

			//ans_xx->Data_Of_Points.insert_cols(ans_xx->Data_Of_Points.n_cols, ans_p);


			////螺旋-直角坐标点
			//vec3 p_lx = in_kjx.point(count_p - 1);
			//vec3 ls_p = p_lx;
			//ls_p(2) = 0.0;
			//double ls_R = norm(ls_p); //y = 半径
			//p_xx = { ls_p(0),ls_R, 0.0 };
			////相位角
			//double XW = deltaRotAngle(tcY(3), ls_p, tcX(3));
			////螺旋-柱坐标点
			//vec3 p_lx_zhu = { p_xx(0),p_xx(1),XW };
			////半径方向-向外
			//vec t_R = normalise(ls_p);

			////柱坐标系
			//vec zhu_X = X_xx; //X轴：相位0截形的切向
			//vec zhu_Y = tcZ(3); //Z轴：	同刀具Z轴
			//vec zhu_Z = cross(zhu_X, zhu_Y); //Y轴：

			////法0后面坐标系
			//vec ls_T = ans_lx->BG_nX(count_p - 2);

			//vec fa_X = -ls_T;//X轴：	刃线切向
			//vec fa_Z = normalise(cross(fa_X, normalise(cross(tcX(3), t_R))));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
			//vec fa_Y = cross(fa_Z, fa_X);//Z轴：	后角线方向（Z轴×X轴）

			//vec ans_p2 = { p_lx_zhu(0), p_lx_zhu(1), p_lx_zhu(2),
			//		p_lx(0), p_lx(1), p_lx(2),
			//		t_R(0), t_R(1), t_R(2),
			//		zhu_X(0), zhu_X(1), zhu_X(2),
			//		zhu_Y(0), zhu_Y(1), zhu_Y(2),
			//		zhu_Z(0), zhu_Z(1), zhu_Z(2),
			//		fa_X(0), fa_X(1), fa_X(2),
			//		fa_Y(0), fa_Y(1), fa_Y(2),
			//		fa_Z(0), fa_Z(1), fa_Z(2),
			//		len_xx };

			//ans_lx->Data_Of_Points.insert_cols(ans_lx->Data_Of_Points.n_cols, ans_p2);
		}

		//螺旋相位角在柱面起点处为0
		//增加螺旋指定长度相位为0，以此基础改变所有点
		//前面部分封装为函数，输入空间线，得到对应型线及螺旋
}

void Tool_ZQ::set_base_data(CanShu_Geo_ZQ& in_data)
{
	data_base = in_data;
}

void Tool_ZQ::init()
{
	init_self_list();

	ptr_list_xx->cal_self();
	ptr_list_hj->cal_self();
	ptr_list_fd->cal_self();
	ptr_list_lx->cal_self();

	ptr_list_gx->cal_self();
}

void Tool_ZQ::init_self_list()
{
	cal_kjx();

	//三条型线、一组后角、3组螺旋、一组分度
	Cal_XingXian* xx_qiu = new Cal_XingXian;
	Cal_XingXian* xx_luo = new Cal_XingXian;
	Cal_XingXian* xx_all = new Cal_XingXian;
	Cal_LouXuan* lx_qiu = new Cal_LouXuan;
	Cal_LouXuan* lx_luo = new Cal_LouXuan;
	Cal_LouXuan* lx_all = new Cal_LouXuan;
	//list元素的刀指针赋值 8.7 new全局变量  修改计算完成标志 8.8
	xx_qiu->ptr_tool = this; xx_qiu->is_lastest = 1;
	xx_luo->ptr_tool = this; xx_luo->is_lastest = 1;
	xx_all->ptr_tool = this; xx_all->is_lastest = 1;
	lx_qiu->ptr_tool = this; lx_qiu->is_lastest = 1;
	lx_luo->ptr_tool = this; lx_luo->is_lastest = 1;
	lx_all->ptr_tool = this; lx_all->is_lastest = 1;

	cal_xx_lx_by_kjx(kjx_qiu, xx_qiu, lx_qiu);
	cal_xx_lx_by_kjx(kjx_luo, xx_luo, lx_luo);
	cal_xx_lx_by_kjx(kjx_all, xx_all, lx_all);

	xx_qiu->is_lastest = 1;

	ptr_list_xx->v_obj_ptr.push_back(xx_all);
	ptr_list_xx->v_obj_ptr.push_back(xx_qiu);//列表存储顺序
	ptr_list_xx->v_obj_ptr.push_back(xx_luo);

	ptr_list_lx->v_obj_ptr.push_back(lx_all);
	ptr_list_lx->v_obj_ptr.push_back(lx_qiu);
	ptr_list_lx->v_obj_ptr.push_back(lx_luo);

	//
	Cal_HouJiao* hj_all = new Cal_HouJiao;
	hj_all->ptr_tool = this; hj_all->is_lastest = 1;
	cal_hj_of_all(hj_all);
	ptr_list_hj->v_obj_ptr.push_back(hj_all);
}

void Tool_PD::set_base_data(CanShu_Geo_PD& in_data)
{
	data_base = in_data;
}

void Tool_PD::init()
{	
	init_self_list();

	ptr_list_xx->cal_self();
	ptr_list_hj->cal_self();
	ptr_list_fd->cal_self();
	ptr_list_lx->cal_self();

	ptr_list_gx->cal_self();
}

void Tool_PD::init_self_list()
{
	cal_kjx();

	//3条型线、两组后角、两组螺旋、一组分度
	Cal_XingXian* xx_all = new Cal_XingXian;
	Cal_XingXian* xx_duan = new Cal_XingXian;
	Cal_XingXian* xx_luo = new Cal_XingXian;
	Cal_LouXuan* lx_all = new Cal_LouXuan;
	Cal_LouXuan* lx_duan = new Cal_LouXuan;
	Cal_LouXuan* lx_luo = new Cal_LouXuan;
	xx_all->ptr_tool = this; xx_all->is_lastest = 1;
	xx_duan->ptr_tool = this; xx_duan->is_lastest = 1;
	xx_luo->ptr_tool = this;  xx_luo->is_lastest = 1;
	lx_all->ptr_tool = this; lx_all->is_lastest = 1;
	lx_duan->ptr_tool = this; lx_duan->is_lastest = 1;
	lx_luo->ptr_tool = this;  lx_luo->is_lastest = 1;

	cal_xx_lx_by_kjx(kjx_all, xx_all, lx_all);
	cal_xx_lx_by_kjx(kjx_duan, xx_duan, lx_duan);
	cal_xx_lx_by_kjx(kjx_luo, xx_luo, lx_luo);

	ptr_list_xx->v_obj_ptr.push_back(xx_all);	//列表存储顺序
	ptr_list_xx->v_obj_ptr.push_back(xx_duan);	//列表存储顺序
	ptr_list_xx->v_obj_ptr.push_back(xx_luo);
	ptr_list_lx->v_obj_ptr.push_back(lx_all);
	ptr_list_lx->v_obj_ptr.push_back(lx_duan);
	ptr_list_lx->v_obj_ptr.push_back(lx_luo);

	Cal_HouJiao* hj_duan = new Cal_HouJiao;
	hj_duan->ptr_tool = this; hj_duan->is_lastest = 1;
	cal_hj_of_duan(hj_duan);
	Cal_HouJiao* hj_luo = new Cal_HouJiao;
	hj_luo->ptr_tool = this; hj_luo->is_lastest = 1;
	cal_hj_of_luo(hj_luo);

	ptr_list_hj->v_obj_ptr.push_back(hj_duan);
	ptr_list_hj->v_obj_ptr.push_back(hj_luo);
}

void Tool_R::set_base_data(CanShu_Geo_R& in_data)
{
	data_base = in_data;
}

void Tool_R::init()
{
	init_self_list();

	ptr_list_xx->cal_self();
	ptr_list_hj->cal_self();
	ptr_list_fd->cal_self();
	ptr_list_lx->cal_self();

	ptr_list_gx->cal_self();
}

void Tool_R::init_self_list()
{
	cal_kjx();

	//4条型线、1组后角、4组螺旋、一组分度
	Cal_XingXian* xx_duan = new Cal_XingXian;
	Cal_XingXian* xx_rrr = new Cal_XingXian;
	Cal_XingXian* xx_luo = new Cal_XingXian;
	Cal_XingXian* xx_all = new Cal_XingXian;
	Cal_LouXuan* lx_duan = new Cal_LouXuan;
	Cal_LouXuan* lx_rrr = new Cal_LouXuan;
	Cal_LouXuan* lx_luo = new Cal_LouXuan;
	Cal_LouXuan* lx_all = new Cal_LouXuan;
	xx_duan->ptr_tool = this; xx_duan->is_lastest = 1;
	xx_rrr->ptr_tool = this; xx_rrr->is_lastest = 1;
	xx_luo->ptr_tool = this; xx_luo->is_lastest = 1;
	xx_all->ptr_tool = this; xx_all->is_lastest = 1;
	lx_duan->ptr_tool = this; lx_duan->is_lastest = 1;
	lx_rrr->ptr_tool = this; lx_rrr->is_lastest = 1;
	lx_luo->ptr_tool = this; lx_luo->is_lastest = 1;
	lx_all->ptr_tool = this; lx_all->is_lastest = 1;

	cal_xx_lx_by_kjx(kjx_all, xx_all, lx_all);
	cal_xx_lx_by_kjx(kjx_duan, xx_duan, lx_duan);
	cal_xx_lx_by_kjx(kjx_rrr, xx_rrr, lx_rrr);
	cal_xx_lx_by_kjx(kjx_luo, xx_luo, lx_luo);

	ptr_list_xx->v_obj_ptr.push_back(xx_all);
	ptr_list_xx->v_obj_ptr.push_back(xx_duan);	//列表存储顺序
	ptr_list_xx->v_obj_ptr.push_back(xx_rrr);
	ptr_list_xx->v_obj_ptr.push_back(xx_luo);
	ptr_list_lx->v_obj_ptr.push_back(lx_all);
	ptr_list_lx->v_obj_ptr.push_back(lx_duan);
	ptr_list_lx->v_obj_ptr.push_back(lx_rrr);
	ptr_list_lx->v_obj_ptr.push_back(lx_luo);

	//
	Cal_HouJiao* hj_all = new Cal_HouJiao;
	hj_all->ptr_tool = this; hj_all->is_lastest = 1;
	cal_hj_of_all(hj_all);
	ptr_list_hj->v_obj_ptr.push_back(hj_all);
}

void Tool_ZQ::cal_fd_of_all(Cal_FenDu& ans_fd)
{
	for (int i = 0; i < 6; i++)
	{
		ans_fd.v_fendu[i] = data_base.v_no_dengfen_angle[i];
	}
}

int Tool_ZQ::save()
{
	Tool_Base::save();

	//2、刀具参数存储的位置 = 刀位置
	//storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Tool_ZQ::load()
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	Tool_Base::load();
}

void Tool_PD::cal_fd_of_all(Cal_FenDu& ans_fd)
{
	for (int i = 0; i < 6; i++)
	{
		ans_fd.v_fendu[i] = data_base.v_no_dengfen_angle[i];
	}
}

int Tool_PD::save()
{
	//Tool_Base::save();
	////2、刀具参数存储的位置 = 刀位置
	//storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Tool_PD::load()
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	Tool_Base::load();
}

void Tool_R::cal_fd_of_all(Cal_FenDu& ans_fd)
{
	for (int i = 0; i < 6; i++)
	{
		ans_fd.v_fendu[i] = data_base.v_no_dengfen_angle[i];
	}
}

int Tool_R::save()
{
	//Tool_Base::save();
	////2、刀具参数存储的位置 = 刀位置
	//storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Tool_R::load()
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	Tool_Base::load();
}

Tool_ZQ::Tool_ZQ()
{
	type_tool = 0;
	v_new_gx_type.push_back(1);
	v_new_gx_type.push_back(2);
	v_new_gx_type.push_back(6);
	v_new_gx_type.push_back(10);
}

Tool_ZQ::~Tool_ZQ()
{
}

int Tool_ZQ::get_luoxuancao_lx_id()
{
	return 2;
}

int Tool_ZQ::get_duanchicao_lx_id()
{
	return 1;
}

int Tool_ZQ::get_yuanjiaocao_lx_id()
{
	return -1;
}

int Tool_ZQ::get_hdm_lx_id()
{
	return 0;
}

int Tool_ZQ::get_hdm_pd_duan_lx_id()
{
	return 0;
}

int Tool_ZQ::get_hdm_pd_zhu_lx_id()
{
	return 0;
}

int Tool_ZQ::get_hdm_hj_id()
{
	return 0;
}

int Tool_ZQ::get_hdm_pd_duan_hj_id()
{
	return 0;
}

int Tool_ZQ::get_hdm_pd_zhu_hj_id()
{
	return 0;
}

void Tool_ZQ::get_cur_tool_canshu(CanShu_Geo_ZQ& ans_can)
{
	ans_can = data_base;
}

void Tool_ZQ::set_cur_tool_canshu(CanShu_Geo_ZQ& ans_can)
{
	data_base = ans_can;
}

double Tool_ZQ::get_D()
{
	return data_base.D;
}

double Tool_ZQ::get_renlen()
{
	return data_base.len_ren;
}

double Tool_ZQ::get_alllen()
{
	return data_base.len_all;
}

void Tool_ZQ::cal_kjx()
{
	double delta_dis_ren = canshu_gg.delta_dis_ren; //关联上前端 8.20
	double R_qiu = data_base.D / 2.0;


	//旋转位置：空间线坐标系转到刀具坐标系，先转y-90，后转x-90
	mat sys_rotate = tcRotX(3, -90.0) * tcRotY(3, -90.0);
	//平移半径
	vec3 move_R = { R_qiu,0.0,0.0 };

	//wld250603
	//球头空间线
	generator_line ls_gen_line;
	ls_gen_line.set_delta_dis(delta_dis_ren);

	vec pos = { 0.0, 0.0, 0.0 };
	ls_gen_line.gen_qiutou_ren_line(R_qiu,1.0, data_base.ang_zhui,
		data_base.ang_end_luo, 
		tcRotX(3, 0.0), pos);

	kjx_qiu = ls_gen_line.ans_line;

	kjx_qiu.fanxiang();
	kjx_qiu.rotate(sys_rotate);
	kjx_qiu.trans(move_R);

	{
		std::ofstream outFile1("points_kjx_qiu.txt");
		if (!outFile1.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		int count_p = kjx_qiu.count_points();
		for (int i = 0; i < count_p; i++)
		{
			vec3 point = kjx_qiu.point(i);

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();
	}


	//螺旋空间线
	//wld250603
	//20250811 zy 螺旋空间线的拼接顺序修改
	//螺旋槽-空间线延长至刀尖
	generator_line ls_gen_yan;
	ls_gen_yan.set_delta_dis(delta_dis_ren);
	//0锥角反向延长-2.21
	ls_gen_yan.gen_luoxuan_ren_line(R_qiu,
		-data_base.ang_zhui, data_base.ang_luoxuan,
		R_qiu, 0.0,
		tcRotX(3, 0.0), pos);
	kjx_luo = ls_gen_yan.ans_line;

	kjx_luo.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
	kjx_luo.rotate(sys_rotate);
	kjx_luo.trans(move_R);

	//原始螺旋线
	ls_gen_line.gen_luoxuan_ren_line(R_qiu,
		data_base.ang_zhui, data_base.ang_luoxuan,
		data_base.len_ren - R_qiu, 0.0,
		tcRotX(3, 180.0), pos); 

	KongJianXian ls_kjx_cal = ls_gen_line.ans_line;

	ls_kjx_cal.rotate(sys_rotate);
	ls_kjx_cal.trans(move_R);


	{
		//std::ofstream outFile1("points_ls_kjx_yan.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = ls_kjx_yan.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = ls_kjx_yan.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}

	//组合
	kjx_qiu.fanxiang();
	kjx_all = kjx_qiu; //接没反向之前的数据 8.15
	kjx_all.join_a_line(ls_kjx_cal);

	{
		//std::ofstream outFile1("points_kjx_all.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = kjx_all.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = kjx_all.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}

	kjx_luo.join_a_line(ls_kjx_cal);

	{
		//std::ofstream outFile1("points_kjx_luo.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = kjx_luo.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = kjx_luo.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}
}


void Tool_ZQ::cal_hj_of_all(Cal_HouJiao* ans_hj)
{	
	Cal_XingXian* ls_xx_all = ptr_list_xx->get_obj(0);
	Cal_XingXian* ls_xx_qiu = ptr_list_xx->get_obj(1);

	double lenth_all = ls_xx_all->Lenth();
	double lenth_qiu = ls_xx_qiu->Lenth();

	//记录要插值的后角长度:百分比
	double len_qiu = 0.0;
	double len_mid = lenth_qiu / 2.0 / lenth_all;
	double len_luo = lenth_qiu / lenth_all;
	double len_end = 1.0;

	ans_hj->data_base.guanlian_xx_id = 0; //默认选择全型线
	ans_hj->ptr_xx = ls_xx_all; //8.13

	ans_hj->data_base.type = 1;

	//vec v_qiu = {data_base.hdm_1_d_qiu, data_base.hdm_1_a_qiu, data_base.hdm_1_width };
	//vec v_mid = {data_base.hdm_1_d_mid, data_base.hdm_1_a_mid, data_base.hdm_1_width };
	//vec v_luo = {data_base.hdm_1_d_luo, data_base.hdm_1_a_luo, data_base.hdm_1_width };
	//vec v_end = {data_base.hdm_1_d_luo, data_base.hdm_1_a_luo, data_base.hdm_1_width };
	vec v_qiu = {len_qiu, data_base.hdm_1_d_qiu, data_base.hdm_1_a_qiu, data_base.hdm_1_width };
	vec v_mid = {len_mid, data_base.hdm_1_d_mid, data_base.hdm_1_a_mid, data_base.hdm_1_width };
	vec v_luo = {len_luo, data_base.hdm_1_d_luo, data_base.hdm_1_a_luo, data_base.hdm_1_width };
	vec v_end = {len_end, data_base.hdm_1_d_luo, data_base.hdm_1_a_luo, data_base.hdm_1_width };
	//插入前清空，不用封装类的插入 8.16
	//ans_hj->data_base.B_ang_a_r_1.insert_element(len_qiu, v_qiu);
	//ans_hj->data_base.B_ang_a_r_1.insert_element(len_mid, v_mid);
	//ans_hj->data_base.B_ang_a_r_1.insert_element(len_luo, v_luo);
	//ans_hj->data_base.B_ang_a_r_1.insert_element(len_end, v_end);
	ans_hj->data_base.B_ang_a_r_1.canshu.reset();
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_qiu);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_mid);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_luo);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_end);


	v_qiu = {len_qiu, data_base.hdm_2_d_qiu, data_base.hdm_2_a_qiu, data_base.hdm_2_width };
	v_mid = {len_mid, data_base.hdm_2_d_mid, data_base.hdm_2_a_mid, data_base.hdm_2_width };
	v_luo = {len_luo, data_base.hdm_2_d_luo, data_base.hdm_2_a_luo, data_base.hdm_2_width };
	v_end = {len_end, data_base.hdm_2_d_luo, data_base.hdm_2_a_luo, data_base.hdm_2_width };
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_qiu);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_mid);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_luo);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_end);

	v_qiu = {len_qiu, data_base.hdm_3_d_qiu, data_base.hdm_3_a_qiu, data_base.hdm_3_width };
	v_mid = {len_mid, data_base.hdm_3_d_mid, data_base.hdm_3_a_mid, data_base.hdm_3_width };
	v_luo = {len_luo, data_base.hdm_3_d_luo, data_base.hdm_3_a_luo, data_base.hdm_3_width };
	v_end = {len_end, data_base.hdm_3_d_luo, data_base.hdm_3_a_luo, data_base.hdm_3_width };
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_qiu);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_mid);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_luo);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_end);

	ans_hj->init_data();
}


Tool_PD::Tool_PD()
{
	type_tool = 1;
	v_new_gx_type.push_back(1);
	v_new_gx_type.push_back(3);
	v_new_gx_type.push_back(7);
	v_new_gx_type.push_back(8);
	v_new_gx_type.push_back(10);
}

void Tool_PD::cal_hj_of_duan(Cal_HouJiao* ans_hj)
{
	//记录要插值的后角长度:百分比
	double len_start = 0.0;
	double len_end = 1.0;

	ans_hj->data_base.guanlian_xx_id = 1; //默认选择型线
	Cal_XingXian* ls_xx_all = ptr_list_xx->get_obj(1);
	ans_hj->ptr_xx = ls_xx_all; //8.13

	ans_hj->data_base.type = 1;

	vec v_start = { len_start, 0.0, data_base.hdm_1_a_hen, data_base.hdm_1_width };
	vec v_end = { len_end, 0.0, data_base.hdm_1_a_hen, data_base.hdm_1_width };
	ans_hj->data_base.B_ang_a_r_1.canshu.reset();
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_end);

	v_start = { len_start, 0.0, data_base.hdm_2_a_hen, data_base.hdm_2_width };
	v_end = { len_end, 0.0, data_base.hdm_2_a_hen, data_base.hdm_2_width };
	ans_hj->data_base.B_ang_a_r_2.canshu.reset();
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_end);

	v_start = { len_start, 0.0, data_base.hdm_3_a_hen, data_base.hdm_3_width };
	v_end = { len_end, 0.0, data_base.hdm_3_a_hen, data_base.hdm_3_width };
	ans_hj->data_base.B_ang_a_r_3.canshu.reset();
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_end);

	ans_hj->init_data();
}

void Tool_PD::cal_hj_of_luo(Cal_HouJiao* ans_hj)
{
	//记录要插值的后角长度
	double len_start = 0.0;
	double len_end = 1.0;

	ans_hj->data_base.guanlian_xx_id = 2; //默认选择型线
	Cal_XingXian* ls_xx_all = ptr_list_xx->get_obj(2);
	ans_hj->ptr_xx = ls_xx_all; //8.13

	ans_hj->data_base.type = 1;

	vec v_start = { len_start, data_base.hdm_1_d_luo, 0.0, data_base.hdm_1_width };
	vec v_end = { len_end, data_base.hdm_1_d_luo, 0.0, data_base.hdm_1_width };
	ans_hj->data_base.B_ang_a_r_1.canshu.reset();
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_end);

	v_start = { len_start, data_base.hdm_2_d_luo, 0.0, data_base.hdm_2_width };
	v_end = { len_end,  data_base.hdm_2_d_luo, 0.0, data_base.hdm_2_width };
	ans_hj->data_base.B_ang_a_r_2.canshu.reset();
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_end);

	v_start = { len_start, data_base.hdm_3_d_luo, 0.0, data_base.hdm_3_width };
	v_end = { len_end,  data_base.hdm_3_d_luo, 0.0, data_base.hdm_3_width };
	ans_hj->data_base.B_ang_a_r_3.canshu.reset();
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_end);

	ans_hj->init_data();
}

Tool_PD::~Tool_PD()
{
}

int Tool_PD::get_luoxuancao_lx_id()
{
	return 2;
}

int Tool_PD::get_duanchicao_lx_id()
{
	return 1;
}

int Tool_PD::get_yuanjiaocao_lx_id()
{
	return -1;
}

int Tool_PD::get_hdm_lx_id()
{
	return 2;
}

int Tool_PD::get_hdm_pd_duan_lx_id()
{
	return 1;
}

int Tool_PD::get_hdm_pd_zhu_lx_id()
{
	return 2;
}

int Tool_PD::get_hdm_hj_id()
{
	return 0;
}

int Tool_PD::get_hdm_pd_duan_hj_id()
{
	return 0;
}

int Tool_PD::get_hdm_pd_zhu_hj_id()
{
	return 1;
}

void Tool_PD::get_cur_tool_canshu(CanShu_Geo_PD& ans_can)
{
	ans_can = data_base;
}

void Tool_PD::set_cur_tool_canshu(CanShu_Geo_PD& ans_can)
{
	data_base = ans_can;
}

double Tool_PD::get_D()
{
	return data_base.D;
}

double Tool_PD::get_renlen()
{
	return data_base.len_ren;
}

double Tool_PD::get_alllen()
{
	return data_base.len_all;
}

void Tool_PD::cal_kjx()
{
	double delta_dis_ren = canshu_gg.delta_dis_ren;
	double R_qiu = data_base.D / 2.0;

	//旋转位置：空间线坐标系转到刀具坐标系，先转y-90，后转x-90
	mat sys_rotate = tcRotX(3, -90.0) * tcRotY(3, -90.0);

	//横端刃空间线
	generator_line ls_gen_line;
	ls_gen_line.set_delta_dis(delta_dis_ren);

	vec pos = { 0.0, 0.0, 0.0 };
	ls_gen_line.gen_duan_ren_line(R_qiu, 0.0, data_base.ang_die,
		tcRotX(3, 0.0), pos);

	kjx_duan = ls_gen_line.ans_line;

	kjx_duan.fanxiang();
	kjx_duan.rotate(sys_rotate); //中心指向半径

	{
		//std::ofstream outFile1("points_kjx_duan.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = kjx_duan.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = kjx_duan.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}

	//螺旋槽-空间线延长至刀尖
	ls_gen_line.gen_luoxuan_ren_line(R_qiu,
		0.0, data_base.ang_luo,
		R_qiu, 0.0,
		tcRotX(3, 0.0), pos);

	kjx_luo = ls_gen_line.ans_line;

	kjx_luo.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
	kjx_luo.rotate(sys_rotate);

	//原始螺旋空间线
	ls_gen_line.gen_luoxuan_ren_line(R_qiu,
		0.0, data_base.ang_luo,
		data_base.len_ren, 0.0,
		tcRotX(3, 180.0), pos);

	KongJianXian ls_kjx_cal = ls_gen_line.ans_line;

	ls_kjx_cal.rotate(sys_rotate);

	//组合
	kjx_luo.join_a_line(ls_kjx_cal);

	kjx_all = kjx_duan; //刀尖指刀柄
	kjx_all.join_a_line(ls_kjx_cal);

	{
		//std::ofstream outFile1("9.9_PD_kjx_all.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = kjx_all.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = kjx_all.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}
}

Tool_R::Tool_R()
{
	type_tool = 2;
	v_new_gx_type.push_back(1);
	v_new_gx_type.push_back(4);
	v_new_gx_type.push_back(9);
	v_new_gx_type.push_back(10);
}

Tool_R::~Tool_R()
{
}

int Tool_R::get_luoxuancao_lx_id()
{
	return 3;
}

int Tool_R::get_duanchicao_lx_id()
{
	return 1;
}

int Tool_R::get_yuanjiaocao_lx_id()
{
	return 2;
}

int Tool_R::get_hdm_lx_id()
{
	return 3;
}

int Tool_R::get_hdm_pd_duan_lx_id()
{
	return 1;
}

int Tool_R::get_hdm_pd_zhu_lx_id()
{
	return 0;
}

int Tool_R::get_hdm_hj_id()
{
	return 0;
}

int Tool_R::get_hdm_pd_duan_hj_id()
{
	return 0;
}

int Tool_R::get_hdm_pd_zhu_hj_id()
{
	return 0;
}

void Tool_R::get_cur_tool_canshu(CanShu_Geo_R& ans_can)
{
	ans_can = data_base;
}

void Tool_R::set_cur_tool_canshu(CanShu_Geo_R& ans_can)
{
	data_base = ans_can;
}

double Tool_R::get_D()
{
	return data_base.D;
}

double Tool_R::get_renlen()
{
	return data_base.len_ren;
}

double Tool_R::get_alllen()
{
	return data_base.len_all;
}

double Tool_R::get_rrr()
{
	return data_base.R_qiu;
}

void Tool_R::cal_kjx()
{
	double delta_dis_ren = canshu_gg.delta_dis_ren;
	double R_qiu = data_base.D / 2.0;

	//旋转位置：空间线坐标系转到刀具坐标系，先转y-90，后转x-90
	mat sys_rotate = tcRotX(3, -90.0) * tcRotY(3, -90.0);

	//横端刃空间线
	generator_line ls_gen_line;
	ls_gen_line.set_delta_dis(delta_dis_ren);

	vec pos = { 0.0, 0.0, 0.0 };
	ls_gen_line.gen_duan_ren_line_R(R_qiu, data_base.R_qiu,
		0.0,data_base.ang_die, 
		tcRotX(3, 0.0), pos);

	kjx_duan = ls_gen_line.ans_line;

	kjx_duan.fanxiang();
	kjx_duan.rotate(sys_rotate);

	{
		std::ofstream outFile1("points_kjx_duan.txt");
		if (!outFile1.is_open()) {
			std::cerr << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		int count_p = kjx_duan.count_points();
		for (int i = 0; i < count_p; i++)
		{
			vec3 point = kjx_duan.point(i);

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();
	}

	//圆角空间线
	ls_gen_line.gen_R_ren_line(R_qiu, data_base.R_qiu,
		0.0, data_base.ang_die, data_base.ang_luo,
		tcRotX(3, 0.0), pos);

	kjx_rrr = ls_gen_line.ans_line;

	kjx_rrr.rotate(sys_rotate);

	{
		std::ofstream outFile1("points_kjx_rrr.txt");
		if (!outFile1.is_open())
		{
			std::cout << "无法打开文件！" << std::endl;
		}

		// 设置输出格式（6位小数，科学计数法）
		outFile1 << std::scientific << std::setprecision(6);

		int count_p = kjx_rrr.count_points();
		for (int i = 0; i < count_p; i++)
		{
			vec3 point = kjx_rrr.point(i);

			// 写入文件：x y z（每行一个点）
			outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		}
		outFile1.close();
	}

	//螺旋槽-空间线延长至刀尖
	ls_gen_line.gen_luoxuan_ren_line(R_qiu,
		0.0, data_base.ang_luo,
		R_qiu, 0.0,
		tcRotX(3, 0.0), pos);

	kjx_luo = ls_gen_line.ans_line;

	kjx_luo.fanxiang();	//平移后空间线不过原起点，用反向短线拼接-长度为球头半径
	kjx_luo.rotate(sys_rotate);

	//螺旋空间线
	ls_gen_line.gen_luoxuan_ren_line(R_qiu,
		0.0, data_base.ang_luo,
		data_base.len_ren, 0.0,
		tcRotX(3, 180.0), pos);

	KongJianXian ls_kjx_cal = ls_gen_line.ans_line;

	ls_kjx_cal.rotate(sys_rotate);

	//组合
	kjx_all = kjx_duan;
	kjx_all.join_a_line(kjx_rrr);
	kjx_all.join_a_line(ls_kjx_cal);
	
	{
		//std::ofstream outFile1("points_kjx_all.txt");
		//if (!outFile1.is_open()) {
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);

		//int count_p = kjx_all.count_points();
		//for (int i = 0; i < count_p; i++)
		//{
		//	vec3 point = kjx_all.point(i);

		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";
		//}
		//outFile1.close();
	}
}

void Tool_R::cal_hj_of_all(Cal_HouJiao* ans_hj)
{
	Cal_XingXian* ls_xx_duan = ptr_list_xx->get_obj(1);
	Cal_XingXian* ls_xx_rrr = ptr_list_xx->get_obj(2);
	Cal_XingXian* ls_xx_all = ptr_list_xx->get_obj(0);
	
	double len_duan = ls_xx_duan->Lenth();
	double len_rrr = ls_xx_rrr->Lenth();
	double len_all = ls_xx_all->Lenth();

	//记录要插值的后角长度:百分比
	double len_start = 0.0;
	double len_start_r = len_duan /len_all;
	double len_end_r = (len_duan + len_rrr) / len_all;
	double len_end = 1.0;

	ans_hj->data_base.guanlian_xx_id = 0; //默认选择型线x
	ans_hj->ptr_xx = ls_xx_all; //8.13

	ans_hj->data_base.type = 1;

	vec v_start = { len_start, 0.0, data_base.hdm_1_a_hen, data_base.hdm_1_width };
	vec v_start_r = { len_start_r, 0.0, data_base.hdm_1_a_hen, data_base.hdm_1_width };
	vec v_end_r = { len_end_r, data_base.hdm_1_d_rrr, 0.0 , data_base.hdm_1_width };
	vec v_end = { len_end, data_base.hdm_1_d_luo, 0.0 , data_base.hdm_1_width };
	ans_hj->data_base.B_ang_a_r_1.canshu.reset();
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_start );
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_start_r);
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_end_r );
	ans_hj->data_base.B_ang_a_r_1.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_1.canshu.n_cols, v_end );

	v_start = { len_start, 0.0, data_base.hdm_2_a_hen, data_base.hdm_2_width };
	v_start_r = { len_start_r, 0.0, data_base.hdm_2_a_hen, data_base.hdm_2_width };
	v_end_r = { len_end_r, data_base.hdm_2_d_rrr, 0.0 , data_base.hdm_2_width };
	v_end = { len_end, data_base.hdm_2_d_luo, 0.0 , data_base.hdm_2_width };
	ans_hj->data_base.B_ang_a_r_2.canshu.reset();
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_start_r);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_end_r);
	ans_hj->data_base.B_ang_a_r_2.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_2.canshu.n_cols, v_end);

	v_start = { len_start,0.0, data_base.hdm_3_a_hen, data_base.hdm_3_width };
	v_start_r = { len_start_r,0.0, data_base.hdm_3_a_hen, data_base.hdm_3_width };
	v_end_r = { len_end_r, data_base.hdm_3_d_rrr, 0.0 , data_base.hdm_3_width };
	v_end = { len_end, data_base.hdm_3_d_luo, 0.0 , data_base.hdm_3_width };
	ans_hj->data_base.B_ang_a_r_3.canshu.reset();
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_start);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_start_r);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_end_r);
	ans_hj->data_base.B_ang_a_r_3.canshu.insert_cols(ans_hj->data_base.B_ang_a_r_3.canshu.n_cols, v_end);
	
	ans_hj->init_data();
}

void Tool_CX::set_base_data(CanShu_Geo_CX& in_data)
{
	data_base = in_data;
}

void Tool_CX::init()
{
	ptr_list_xx->cal_self();
	ptr_list_hj->cal_self();
	ptr_list_fd->cal_self();
	ptr_list_lx->cal_self();

	ptr_list_gx->cal_self();
}

Tool_CX::Tool_CX()
{
	type_tool = 3;
	v_new_gx_type.push_back(0);
	v_new_gx_type.push_back(5);
	v_new_gx_type.push_back(10);
	v_new_gx_type.push_back(11);
}

Tool_CX::~Tool_CX()
{
}

int Tool_CX::get_luoxuancao_lx_id()
{
	return 0;
}

int Tool_CX::get_duanchicao_lx_id()
{
	return 0;
}

int Tool_CX::get_yuanjiaocao_lx_id()
{
	return 0;
}

int Tool_CX::get_hdm_lx_id()
{
	return 0;
}

int Tool_CX::get_hdm_pd_duan_lx_id()
{
	return 0;
}

int Tool_CX::get_hdm_pd_zhu_lx_id()
{
	return 0;
}

int Tool_CX::get_hdm_hj_id()
{
	return 0;
}

int Tool_CX::get_hdm_pd_duan_hj_id()
{
	return 0;
}

int Tool_CX::get_hdm_pd_zhu_hj_id()
{
	return 0;
}

void Tool_CX::get_cur_tool_canshu(CanShu_Geo_CX& ans_can)
{
	ans_can = data_base;
}

void Tool_CX::set_cur_tool_canshu(CanShu_Geo_CX& ans_can)
{
	data_base = ans_can;
}

double Tool_CX::get_D()
{
	return data_base.cx_D;
}

double Tool_CX::get_renlen()
{
	return data_base.cx_len;
}

double Tool_CX::get_alllen()
{
	return data_base.cx_len;
}


int Tool_CX::save()
{
	//Tool_Base::save();
	////2、刀具参数存储的位置 = 刀位置
	//storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Tool_CX::load()
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_data, pos, (char*)&data_base, sizeof(data_base));
	Tool_Base::load();
}
