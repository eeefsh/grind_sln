//计算

void Miller_GX_Base::cal_base_DL()
{
}

int Miller_GX_Base::get_gx_type()
{
	return gx_type;
}

void Miller_GX_Base::set_self_dao(Tool_Base* in_ptr)
{
	ptr_tool = in_ptr;
}



Miller_GX_Base::Miller_GX_Base()
{
	gx_type = 0;
	name = -1;

	A_before = 0.0;

}

Miller_GX_Base::~Miller_GX_Base()
{
}

void Miller_GX_Base::set_name(int in_name)
{
	name = in_name;
}

int Miller_GX_Base::Save()
{
	return 0;
}

void Miller_GX_Base::Load(int in_pos)
{
}

void Miller_GX_Base::set_self_dao(Miller_D_Base* in_ptr)
{
}




XingCan_Miller_GX::XingCan_Miller_GX()
{
	gx_type = 0;
	can_zq_qdm = nullptr;
	can_zq_lxc = nullptr;
	can_zq_hdm_1 = nullptr;
	can_zq_hdm_2 = nullptr;
	can_zq_hdm_3 = nullptr;
	can_zq_dt_jx = nullptr;
	can_zq_dj_jx = nullptr;
	can_zq_dj_fxc = nullptr;

	can_pd_dcc = nullptr;
	can_pd_dhdm_1 = nullptr;
	can_pd_dhdm_2 = nullptr;
	can_pd_dhdm_3 = nullptr;
	can_pd_lxc = nullptr;
	can_pd_hdm_1 = nullptr;
	can_pd_hdm_2 = nullptr;
	can_pd_hdm_3 = nullptr;
	can_pd_dt_jx = nullptr;

	can_r_qdm = nullptr;
	can_r_hdm_1 = nullptr;
	can_r_hdm_2 = nullptr;
	can_r_hdm_3 = nullptr;
	can_r_lxc = nullptr;
	can_r_dt_jx = nullptr;
	can_r_dj_jx = nullptr;
	can_r_dj_fxc = nullptr;

	can_cx_kaicao = nullptr;
	can_cx_hdm_1 = nullptr;
	can_cx_hdm_2 = nullptr;
}

//后续加成员，要在内部初始化指针 ???

XingCan_Miller_GX::~XingCan_Miller_GX()
{
	/*delete can_zq_qdm;
	delete can_zq_lxc;
	delete can_zq_hdm_1;
	delete can_zq_hdm_2;
	delete can_zq_hdm_3;
	delete can_zq_dt_jx;
	delete can_zq_dj_jx;
	delete can_zq_dj_fxc;

	delete can_pd_dcc;
	delete can_pd_dhdm_1;
	delete can_pd_dhdm_2;
	delete can_pd_dhdm_3;
	delete can_pd_lxc;
	delete can_pd_hdm_1;
	delete can_pd_hdm_2;
	delete can_pd_hdm_3;
	delete can_pd_dt_jx;

	delete can_r_qdm;
	delete can_r_hdm_1;
	delete can_r_hdm_2;
	delete can_r_hdm_3;
	delete can_r_lxc;
	delete can_r_dt_jx;
	delete can_r_dj_jx;
	delete can_r_dj_fxc;*/
}

XingCan_Miller_GX::XingCan_Miller_GX(int in_type)
{
	gx_type = in_type;
}

bool XingCan_Miller_GX::set_CanShu_ZQ_QDM(CanShu_ZQ_QDM& in_ptr)
{
	if (can_zq_qdm != nullptr)
	{
		delete can_zq_qdm;
	}
	can_zq_qdm = new CanShu_ZQ_QDM(in_ptr);
	gx_type = 0;
	return true;
}

bool XingCan_Miller_GX::set_Canshu_ZQ_LXC(Canshu_ZQ_LXC& in_ptr)
{
	if (can_zq_lxc != nullptr)
	{
		delete can_zq_lxc;
	}
	can_zq_lxc = new Canshu_ZQ_LXC(in_ptr);
	gx_type = 1;
	return true;
}

bool XingCan_Miller_GX::set_Canshu_ZQ_HDM_1(Canshu_ZQ_HDM_1& in_ptr)
{
	if (can_zq_hdm_1 != nullptr)
	{
		delete can_zq_hdm_1;
	}
	can_zq_hdm_1 = new Canshu_ZQ_HDM_1(in_ptr);
	gx_type = 2;
	return true;
}

bool XingCan_Miller_GX::set_Canshu_ZQ_HDM_2(Canshu_ZQ_HDM_2& in_ptr)
{
	if (can_zq_hdm_2 != nullptr)
	{
		delete can_zq_hdm_2;
	}
	can_zq_hdm_2 = new Canshu_ZQ_HDM_2(in_ptr);
	gx_type = 3;
	return true;
}

bool XingCan_Miller_GX::set_Canshu_ZQ_HDM_3(Canshu_ZQ_HDM_3& in_ptr)
{
	if (can_zq_hdm_3 != nullptr)
	{
		delete can_zq_hdm_3;
	}
	can_zq_hdm_3 = new Canshu_ZQ_HDM_3(in_ptr);
	gx_type = 4;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_ZQ_DaoTiJianXi(CanShu_ZQ_DaoTiJianXi& in_ptr)
{
	if (can_zq_dt_jx != nullptr)
	{
		delete can_zq_dt_jx;
	}
	can_zq_dt_jx = new CanShu_ZQ_DaoTiJianXi(in_ptr);
	gx_type = 5;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_ZQ_DaoJianJianXi(CanShu_ZQ_DaoJianJianXi& in_ptr)
{
	if (can_zq_dj_jx != nullptr)
	{
		delete can_zq_dj_jx;
	}
	can_zq_dj_jx = new CanShu_ZQ_DaoJianJianXi(in_ptr);
	gx_type = 6;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_ZQ_DaoJianFenXieCao(CanShu_ZQ_DaoJianFenXieCao& in_ptr)
{
	if (can_zq_dj_fxc != nullptr)
	{
		delete can_zq_dj_fxc;
	}
	can_zq_dj_fxc = new CanShu_ZQ_DaoJianFenXieCao(in_ptr);
	gx_type = 7;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_DCC(CanShu_PD_DCC& in_ptr)
{
	if (can_pd_dcc != nullptr)
	{
		delete can_pd_dcc;
	}
	can_pd_dcc = new CanShu_PD_DCC(in_ptr);
	gx_type = 8;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_DHDM_1(CanShu_PD_DHDM_1& in_ptr)
{
	if (can_pd_dhdm_1 != nullptr)
	{
		delete can_pd_dhdm_1;
	}
	can_pd_dhdm_1 = new CanShu_PD_DHDM_1(in_ptr);
	gx_type = 9;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_DHDM_2(CanShu_PD_DHDM_2& in_ptr)
{
	if (can_pd_dhdm_2 != nullptr)
	{
		delete can_pd_dhdm_2;
	}
	can_pd_dhdm_2 = new CanShu_PD_DHDM_2(in_ptr);
	gx_type = 10;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_DHDM_3(CanShu_PD_DHDM_3& in_ptr)
{
	if (can_pd_dhdm_3 != nullptr)
	{
		delete can_pd_dhdm_3;
	}
	can_pd_dhdm_3 = new CanShu_PD_DHDM_3(in_ptr);
	gx_type = 11;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_LXC(CanShu_PD_LXC& in_ptr)
{
	if (can_pd_lxc != nullptr)
	{
		delete can_pd_lxc;
	}
	can_pd_lxc = new CanShu_PD_LXC(in_ptr);
	gx_type = 12;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_HDM_1(CanShu_PD_HDM_1& in_ptr)
{
	if (can_pd_hdm_1 != nullptr)
	{
		delete can_pd_hdm_1;
	}
	can_pd_hdm_1 = new CanShu_PD_HDM_1(in_ptr);
	gx_type = 13;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_HDM_2(CanShu_PD_HDM_2& in_ptr)
{
	if (can_pd_hdm_2 != nullptr)
	{
		delete can_pd_hdm_2;
	}
	can_pd_hdm_2 = new CanShu_PD_HDM_2(in_ptr);
	gx_type = 14;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_HDM_3(CanShu_PD_HDM_3& in_ptr)
{
	if (can_pd_hdm_3 != nullptr)
	{
		delete can_pd_hdm_3;
	}
	can_pd_hdm_3 = new CanShu_PD_HDM_3(in_ptr);
	gx_type = 15;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_PD_DaoTiJianXi(CanShu_PD_DaoTiJianXi& in_ptr)
{
	if (can_pd_dt_jx != nullptr)
	{
		delete can_pd_dt_jx;
	}
	can_pd_dt_jx = new CanShu_PD_DaoTiJianXi(in_ptr);
	gx_type = 16;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_QDM_R(CanShu_R_QDM_R& in_ptr)
{
	if (can_r_qdm != nullptr)
	{
		delete can_r_qdm;
	}
	can_r_qdm = new CanShu_R_QDM_R(in_ptr);
	gx_type = 17;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_HDM_1(CanShu_R_HDM_1& in_ptr)
{
	if (can_r_hdm_1 != nullptr)
	{
		delete can_r_hdm_1;
	}
	can_r_hdm_1 = new CanShu_R_HDM_1(in_ptr);
	gx_type = 18;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_HDM_2(CanShu_R_HDM_2& in_ptr)
{
	if (can_r_hdm_2 != nullptr)
	{
		delete can_r_hdm_2;
	}
	can_r_hdm_2 = new CanShu_R_HDM_2(in_ptr);
	gx_type = 19;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_HDM_3(CanShu_R_HDM_3& in_ptr)
{
	if (can_r_hdm_3 != nullptr)
	{
		delete can_r_hdm_3;
	}
	can_r_hdm_3 = new CanShu_R_HDM_3(in_ptr);
	gx_type = 20;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_LXC(CanShu_R_LXC& in_ptr)
{
	if (can_r_lxc != nullptr)
	{
		delete can_r_lxc;
	}
	can_r_lxc = new CanShu_R_LXC(in_ptr);
	gx_type = 21;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_DaoTiJianXi(CanShu_R_DaoTiJianXi& in_ptr)
{
	if (can_r_dt_jx != nullptr)
	{
		delete can_r_dt_jx;
	}
	can_r_dt_jx = new CanShu_R_DaoTiJianXi(in_ptr);
	gx_type = 22;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_DaoJianJianXi(CanShu_R_DaoJianJianXi& in_ptr)
{
	if (can_r_dj_jx != nullptr)
	{
		delete can_r_dj_jx;
	}
	can_r_dj_jx = new CanShu_R_DaoJianJianXi(in_ptr);
	gx_type = 23;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_R_DaoJianFenXieCao(CanShu_R_DaoJianFenXieCao& in_ptr)
{
	if (can_r_dj_fxc != nullptr)
	{
		delete can_r_dj_fxc;
	}
	can_r_dj_fxc = new CanShu_R_DaoJianFenXieCao(in_ptr);
	gx_type = 24;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_GX_CX_KaiCao(CanShu_GX_CX_KaiCao& in_ptr)
{
	if (can_cx_kaicao != nullptr)
	{
		delete can_cx_kaicao;
	}
	can_cx_kaicao = new CanShu_GX_CX_KaiCao(in_ptr);
	gx_type = 25;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_GX_CX_HDM_1(CanShu_GX_CX_HDM_1& in_ptr)
{
	if (can_cx_hdm_1 != nullptr)
	{
		delete can_cx_hdm_1;
	}
	can_cx_hdm_1 = new CanShu_GX_CX_HDM_1(in_ptr);
	gx_type = 26;
	return true;
}

bool XingCan_Miller_GX::set_CanShu_GX_CX_HDM_2(CanShu_GX_CX_HDM_2& in_ptr)
{
	if (can_cx_hdm_2 != nullptr)
	{
		delete can_cx_hdm_2;
	}
	can_cx_hdm_2 = new CanShu_GX_CX_HDM_2(in_ptr);
	gx_type = 27;
	return true;
}

int XingCan_Miller_GX::get_gx_type()
{
	return gx_type;
}



void Miller_GX_ZQ_QDM::get_canshu(CanShu_ZQ_QDM& ans)
{
	ans = data_canshu;
}

//A设置球头容屑槽参数

void Miller_GX_ZQ_QDM::set_canshu(CanShu_ZQ_QDM& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_ZQ_QDM(ptr);
}

//A.1设置球头容屑槽参数

void Miller_GX_ZQ_QDM::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_qdm); //改为public
	self_xingcan = &ptr;
	/*cal_renxian(Cal_RenXian& ans_rx);
	cal_leadface(Cal_RenXian& ans_rx);*/
}

void Miller_GX_ZQ_QDM::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	prog_of_gx->set_jingeilv(jingeilv, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);

}

//计算基本刀路

void Miller_GX_ZQ_QDM::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;
			//当前刃的位置角度
			double angle_zhuan = self_Dao->self_xingcan->can_zq_gg->v_no_dengfen_angle[i];

			//1、从铣刀获取基本球头刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			//只有铣刀基类指针，基类里提供获取刃线的函数，具体工序类调用对应刀的 8.24 
			self_Dao->get_renxian_of_qiu(ls_ren_pos, get_renxian);
			//引用传递会修改原始刃线，get引用后复制出一份给后续计算10.30
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//1.5 修改编辑--
			cal_new_renxian(data_canshu.ang_to_end, ls_renxian); //剪切掉角度所占%
			//修剪到中心距离
			//double len_ren = ls_renxian.Lenth_of_RenXian();
			//double R_qiu = self_Dao->self_xingcan->can_zq_gg->D_qiu;
			//double per_center = data_canshu.dis_to_center / (arma::datum::pi * R_qiu / 4);
			//ls_renxian.cutting_qiutou(per_center, 1.0);


			//2、生成前刀面数据--
			mat data_qdm;
			cal_leadface(ls_renxian, data_qdm); //刀尖指向刀柄

			//3、以球头槽方式计算圆弧部分
#pragma region 球头槽
			int p_count = data_qdm.n_cols;
			double var2_t_w = 0.0;
			//3、准备计算砂轮位姿的数据
			mat p_data(3, p_count, fill::zeros);
			mat n_data(3, p_count, fill::zeros);
			mat t_data(3, p_count, fill::zeros);
			p_data = data_qdm.submat(0, 0, 2, p_count - 1);		//前刀面点
			n_data = data_qdm.submat(9, 0, 11, p_count - 1);		//法向 = z轴
			t_data = data_qdm.submat(3, 0, 5, p_count - 1);		//切向 = x轴

			mat33 sys_xh = eye(3, 3);
			vec3 p_xh = { 0.0, 0.0, 0.0 };
			double cur_R = self_Dao->self_xingcan->can_zq_gg->D_qiu / 2.0;
			//3.1、芯厚面数据--加上转角10.30--只需要圆弧部分
			mat xinhou_data; //3*n 
			double R_xin = data_canshu.jin_percent_r * cur_R;
			//cal_xinhoumian(p_data.col(0),data_canshu.angle_up, R_xin, data_canshu.angle_jin,
			//shalun_canshu.D / 2.0 + shalun_canshu.R, angle_zhuan, xinhou_data);

			vec3 ls_qdm_p = { 0.0, 0.0, -cur_R };
			xt_QT_XHM cal_xinhou;
			cal_xinhou.Set_QDM(ls_qdm_p, n_data.col(0), t_data.col(0));
			cal_xinhou.Set_SL_Cutting(shalun_canshu.D / 2.0, shalun_canshu.R, data_canshu.angle_qiexue);
			cal_xinhou.Set_XHM(R_xin, data_canshu.angle_up, 90 - data_canshu.angle_jin);//芯厚固定为90
			bool is_input0 = cal_xinhou.Check_Input();
			if (is_input0 == 0)
			{
				return; //输入有误--可以将返回值在对话框弹出计算失败11.6
			}
			xinhou_data = cal_xinhou.Get_XHM(10000); //1.16芯厚密度不够,有些点解不出来
			//xinhou_data = tcRotZ(3, angle_zhuan) * xinhou_data; //1.16 不能打开，

			vec last_xinhou_p = xinhou_data.col(xinhou_data.n_cols - 1);

			mat test_p = xinhou_data.t();
			test_p.save(R"(test_xinhou_12.3.txt)", raw_ascii);
			mat test_p2 = p_data.t();
			test_p2.save(R"(test_qdm_12.10.txt)", raw_ascii);

			vec3 qiuxin_p;
			cal_xinhou.Get_XHM_Point(qiuxin_p);

			xt_XiDao_QT cal_qiutoucao;
			cal_qiutoucao.Set_QDM(p_data, n_data, t_data);
			cal_qiutoucao.Set_SL_Cutting(shalun_canshu.D / 2.0, shalun_canshu.R, data_canshu.angle_qiexue);
			cal_qiutoucao.Set_XHM(xinhou_data, qiuxin_p, 90 - data_canshu.angle_jin);

			bool is_input = cal_qiutoucao.Check_Input();
			if (is_input == 0)
			{
				//return; //输入有误
			}


			//4、砂轮结果获取 = 工件坐标系下的刀路点
			vec3 ls_p = { 0.0,0.0,0.0 };
			mat33 ls_sys = eye(3, 3);
			bool has_jie = cal_qiutoucao.Get_WZ_First(ls_p, ls_sys);
			int index_cir_end = 0;
			vec last_qiedian = { 0.0,0.0,0.0 };
			for (int i = 1; i < p_count - 1; i++)
			{
				cal_qiutoucao.Get_WZ_Next(ls_p, ls_sys);
				//计算的结果为，抽象的回转面与圆角的回转轴中心，通过砂轮安装状态才能确定出位姿
				//根据砂轮的内外磨，确定z轴是否反向

				//Z轴：砂轮轴朝向磨削面法向
				//X轴：砂轮轴心指向磨削点
				//右手系
				//ls_sys = ls_sys * tcRotZ(3, 180.0);

				//切换砂轮内外侧磨削 8.7 mark 默认内侧 9.9 
				if (in_or_out == 1)
				{
					ls_sys = ls_sys * tcRotX(3, 180.0);
				}
				else
				{
					ls_sys = ls_sys * tcRotX(3, 0.0);//前刀面就是外侧磨
				}

				mat33 G_SYS_SL = eye(3, 3);
				G_SYS_SL.col(0) = ls_sys.col(0);
				G_SYS_SL.col(1) = ls_sys.col(1);
				G_SYS_SL.col(2) = ls_sys.col(2);

				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
						{ls_sub(0),  ls_sub(3), ls_sub(6)},
						{ls_sub(1),  ls_sub(4), ls_sub(7)},
						{ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_data.col(i);
				ans_DL_P.G_SYS_HDM = G_SYS_QDM; //法向为z轴
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);

				{
					//判断当前砂轮与芯厚的交点，判断z值是否与芯厚面线圆弧部分最后一点高度相同
					//vec ls_qiedian = cal_qiutoucao.Get_QieDian();

					////vec3 qiuxin_p;
					////cal_xinhou.Get_XHM_Point(qiuxin_p);
					////vec begin_p = xinhou_data.col(0);
					////last_xinhou_p;
					//// vec3 qi_t = begin_p - qiuxin_p;
					//// vec3 end_t = last_xinhou_p - qiuxin_p;
					//// vec3 pan_t = ls_qiedian - qiuxin_p;
					//// bool is_out_range = { dot(cross(normalise(pan_t),normalise(qi_t)),
					////  cross(normalise(pan_t),normalise(end_t))) > 0.0 };//是则超出
					//// if (is_out_range)
					//// {
					   ////  index_cir_end = i;
					   ////  last_qiedian = ls_qiedian;
					   ////  var2_t_w = cal_qiutoucao.Get_Ans_tw();
					   ////  break;
					//// }

					//if (ls_qiedian(2) > last_xinhou_p(2)) 
					//{//记录当前刃线点位置
					   // index_cir_end = i;

					   // var2_t_w = cal_qiutoucao.Get_Ans_tw();
					   // break;
					//}
				}
			}

#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始砂轮切向延长指定距离-11.19 当前刃线刀尖指向刀柄
			{
				//球头第24刃线不横向退刀  12.12---12.28改为可以横向90度
				double ang_hen_tui = data_canshu.angle_hen_tui;
				/*if (ls_ren_pos == 1 || ls_ren_pos == 3)
				{
					ang_hen_tui = 0.0;
				}*/

				double dis_extend = data_canshu.dis_end_extend;  //需要加密延长点12.2
				vec end_v = ls_renxian.nX(ls_renxian.n_P - 1);
				vec end_y = ls_renxian.nY(ls_renxian.n_P - 1);
				vec end_z = ls_renxian.nZ(ls_renxian.n_P - 1);

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_SL_start = DL_part.Data[0].G_SYS_SL;
				mat33 ls_sys_sl = DL_part.Data[0].G_SYS_HDM * tcRotY(3, ang_hen_tui); //横向退刀
				vec start_v = ls_sys_sl * (-tcX(3));

				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_SL_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;


				//延长过中心距离1.20
				{
					vec start_v_yan = DL_part.Data[0].G_SYS_HDM * (-tcX(3)); //切向过中心

					double dis_start_extend = data_canshu.dis_start_extend;
					double dis_p_start = 0.04;
					int start_yan = dis_start_extend / dis_p_start;

					for (int i = 1; i <= start_yan; i++)
					{
						DL_P ans_start;
						ans_start.G_P = p_dl_start + (start_v_yan)*i * dis_p_start;
						ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
						ans_start.G_SYS_SL = G_SYS_SL_start;
						ans_start.point_type = 2;

						DL_part.Data.insert(DL_part.Data.begin(), ans_start);
					}
				}
				p_dl_start = DL_part.Data[0].G_P;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用起始
				dis_p = 0.04;
				int count_yan = dis_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + (start_v)*i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = G_SYS_SL_start;
					ans_start.point_type = 2;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);

					DL_P ans_end;
					ans_end.G_P = p_dl_end + (end_v)*i * dis_p; //终点刃线切向 11.28
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = G_SYS_SL_end;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//4.6、刀路点反向，只改点的顺序
			reverse(DL_part.Data.begin(), DL_part.Data.end());

			//5、单刃进退刀 --点顺序反向后，进退刀不对，先加进退刀，后反向12.20
			XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}


}

void Miller_GX_ZQ_QDM::cal_new_renxian(double per_start, Cal_RenXian& in_rx)
{
	//反向
	//in_rx.fanxiang();
	double ls_per = per_start / 90;
	in_rx.cutting_qiutou(0, 1.0 - ls_per);
}

//计算引导面

void Miller_GX_ZQ_QDM::cal_leadface(Cal_RenXian& in_rx, mat& data_qdm)
{
	//球头前刀面：刃线法坐标系绕x转 90-前角
	int p_num = in_rx.get_p_num();

	//前角线性插值11.26
	vector<double> v_ang;
	{
		int p_num_mid = p_num / 2;
		double delta_ang = (data_canshu.ang_n2 - data_canshu.ang_n1) / p_num_mid;
		for (int i = 0; i < p_num_mid; i++)
		{
			double cal_ang = data_canshu.ang_n1 + delta_ang * i;
			v_ang.push_back(cal_ang);
		}
		delta_ang = (data_canshu.ang_n3 - data_canshu.ang_n2) / (p_num - p_num_mid);
		for (int i = 0; i < p_num - p_num_mid; i++)
		{
			double cal_ang = data_canshu.ang_n2 + delta_ang * i;
			v_ang.push_back(cal_ang);
		}
	}

	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat test_sys = in_rx.nSYS(i);
		double cur_ang = v_ang[i];
		mat ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - cur_ang));
		//vec3 ls_n = -ls_sys.col(1);
		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}

}

void Miller_GX_ZQ_QDM::cal_xinhou_hz(double D_sl, double R_xh, double in_ang_in, mat& px, mat& nx)
{
	vec v_fangxiang = normalise(tcRotY(3, in_ang_in) * tcZ(3)); //芯厚线方向
	vec v_t = normalise(tcRotY(3, in_ang_in) * tcX(3));//芯厚线法向
	vec ls_p = { R_xh ,0.0,0.0 };
	vec p_start = tcRotY(3, in_ang_in) * ls_p + 5 * (-v_fangxiang);
	int p_count = D_sl / 0.1;
	int cur_p_index = 0;
	//for (int i = p_count - 1; i > 0; i--)
	//{
	   // vec3 ans_p = p_start + i * 0.1 * (-v_fangxiang);
	   // px.col(cur_p_index) = ans_p;

	   // nx.col(cur_p_index) = v_t;
	   // cur_p_index++;
	//}

	for (int i = 0; i < p_count; i++)
	{
		vec3 ans_p = p_start + i * 0.1 * v_fangxiang;
		px.col(cur_p_index) = ans_p;

		nx.col(cur_p_index) = v_t;
		cur_p_index++;
	}
}

void Miller_GX_ZQ_QDM::cal_xinhoumian(vec3 qdm_p, double ang_up, double R_xin, double ang_out, double R_sl, double ang_zhuan, mat& px)
{
	//1、根据点+顶角，算出芯厚圆的高度
	//2、高度确定芯厚圆轮廓、根据砂轮半径+点算出切点
	//3、切点切向延长得到第一段直线
	//4、计算出线切点

	vec3 ls_p = -qdm_p;  //在正半轴计算
	ls_p(0) = 0.0; ls_p(1) = 0.0; //近似处理
	double h = cal_Offset_Height(ls_p(2), R_xin, ang_up);//圆心偏移高度

	double ox = 0.0;
	double oz = 0.0;
	findCircle2Center(h, R_xin, ls_p(2), R_sl, ox, oz); //砂轮圆心

	vec3 o1 = { 0.0,0.0,h };
	vec3 o2 = { ox,0.0,oz };
	vec3 o1_to_o2 = o2 - o1;
	double xishu = R_xin / R_sl;
	vec3 tp = xishu * o1_to_o2 + o1; //切点坐标
	double ang_tp = tcDegree(atan((tp(2) - h) / tp(0))); //切点转角

	vec3 tv = normalise(tcRotY(3, -90) * tp);

	vector<vec3> line1; //切点指向Z轴交点
	vec3 ans_p = tp;
	//while (ans_p(0) > 0)
	//{
	   // line1.push_back(ans_p);
	   // ans_p = ans_p + 0.1 * tv;
	//}

	vec3 right_x0 = { R_xin,0.0,0.0 }; //右边水平半径长度点
	vec3 dis_up = { 0.0,0.0,h };
	vec3 tp_out = tcRotY(3, -ang_out) * right_x0 + dis_up; //出线切点

	//圆弧部分--改为直线测试10.30
	vector<vec3> line2; //出线切点指向圆切点
	ans_p = tp_out;
	double cur_ang = ang_out;
	while (cur_ang < ang_tp)
	{
		line2.push_back(ans_p);
		cur_ang = cur_ang + 1; //角度细分量
		ans_p = tcRotY(3, -cur_ang) * right_x0 + dis_up;
	}

	//vector<vec3> line2; //出线切点指向圆切点
	//vec3 tv1 = normalise(tp - tp_out);
	//ans_p = tp_out + 0.1 * tv1;
	//while (ans_p(2) < tp(2))
	//{
	   // line2.push_back(ans_p);
	   // ans_p = ans_p + 0.1 * tv1;
	//}

	vec3 tp_v = tp_out - o1; //出线切点向量
	vec3 tv2 = normalise(tcRotY(3, 90) * tp_v);

	vector<vec3> line3; //出线切点指向X轴
	ans_p = tp_out;
	//while (ans_p(2) > -10)
	//{
	   // line3.push_back(ans_p);
	   // ans_p = ans_p + 0.1 * tv2;
	//}

	//三线和一
	int count1 = line1.size(), count2 = line2.size(), count3 = line3.size();
	px.reset();
	px.resize(3, 0);
	px.insert_cols(0, count1 + count2 + count3);
	int index = 0;
	for (int i = count1 - 1; i > 0; i--) //倒放
	{
		px.col(index) = line1[i];
		index++;
	}
	for (int i = count2 - 1; i > 0; i--)//倒放
	{
		px.col(index) = line2[i];
		index++;
	}
	for (int i = 0; i < count3; i++)
	{
		px.col(index) = line3[i];
		index++;
	}
	//px = fliplr(px);
	px = tcRotX(3, 180) * px;

	px = tcRotZ(3, ang_zhuan) * px;
	mat test_p = px.t();
	test_p.save(R"(test_xinhou_10.29.txt)", raw_ascii);
}

double Miller_GX_ZQ_QDM::cal_Offset_Height(double z_p, double r, double angleDegrees) {
	// 将角度转换为弧度
	double angleRadians = angleDegrees * arma::datum::pi / 180.0;

	// 计算 sec(theta)
	double secTheta = 1.0 / std::cos(angleRadians);

	// 计算偏置的高度
	double z = z_p - r * secTheta;

	return z;
}

void Miller_GX_ZQ_QDM::findCircle2Center(double h1, double r, double h2, double R2, double& ans_x, double& ans_y)
{
	double len1 = R2;
	double len2 = r + R2;

	double y1 = ((len2 * len2 - len1 * len1) + (h2 * h2 - h1 * h1))
		/ (2 * (h2 - h1));

	ans_x = sqrt(len1 * len1 - (y1 - h2) * (y1 - h2));
	ans_y = y1;
}

void Miller_GX_ZQ_QDM::cal_xinhoumian(mat& px, mat& nx, double sl_D)
{
	{
		// //备注：前刀面的芯厚线，不用延长 8.13 mark
	 ////切入深度A与结束处半径比值B，可在平面上确定两点，构造出椭圆曲线
	 ////在曲线上采样，保证在回转轴上的间隔相等
	 ////两个角度值，三角tan，得到切向单位化，逐个插点
	 //// Z为水平轴，X为垂直轴
	 ////曲线表达式：Z = （A/B^2）* X^2 - A
		// double A = self_Dao->get_gg_canshu_D_qiu() - data_canshu.deep_qie;
		// double B = self_Dao->get_gg_canshu_D_qiu() * data_canshu.end_percent_r;

		// int p_count = data_lead_face.hdm_1.n_cols;
		// double delta_dis = abs(A / (1.0 * p_count));

		// //顶部进入延长段
		// vec3 p_A = { 0.0, 0.0, -A };
		// vec3 p_qie = { -1.0, 0.0, -A - tan(tcRadians(data_canshu.angle_up)) };
		// vec3 p_v = normalise(p_qie - p_A);
		// //int extend_count = sl_D / delta_dis;
		// //芯厚线要与磨削面同向 8.13 mark
		// //p_count = p_count - 2;
		// px.resize(3, p_count);
		// nx.resize(3, p_count);
		// //for (int i = 0; i < extend_count; i++)
		// //{
		//	// vec3 ans_p = p_A + i * delta_dis * p_v;
		//	// px.col(i) = ans_p;

		//	// //切向转90度
		//	// if (i == 0)
		//	// {
		//	// }
		//	// else
		//	// {
		//	//	 vec3 ans_ls = ans_p - px.col(i - 1);
		//	//	 vec3 ans_n = tcRotY(3, 90) * ans_ls;
		//	//	 nx.col(i) = normalise(ans_n);
		//	// }
		// //}
		// //nx.col(0) = nx.col(1);

		// //曲线段
		// for (int i = 0; i < p_count; i++)
		// {
		//	 /* if (i == 316)
		//	  {
		//		  int a = 0;
		//	  }*/
		//	 double z = -A + (i + 1) * delta_dis;
		//	 double x = sqrt((z + A) / (A / (B * B)));
		//	 double y = 0.0;
		//	 vec3 ans_p = { x, y, z };
		//	 px.col(i) = ans_p;

		//	 //切向转90度
		//	 if (i == 0)
		//	 {
		//	 }
		//	 else
		//	 {
		//		 vec3 ans_ls = ans_p - px.col(i - 1);
		//		 vec3 ans_n = tcRotY(3, 90) * ans_ls;
		//		 nx.col(i) = normalise(ans_n);
		//	 }
		// }
		// nx.col(0) = nx.col(1);

		// //芯厚线要与磨削面同向 8.13 mark
		// mat ls_p = px;
		// mat ls_n = nx;
		// for (int i = 0; i < p_count; i++)
		// {
		//	 px.col(i) = ls_p.col(p_count - 1 - i);
		//	 nx.col(i) = ls_n.col(p_count - 1 - i);
		// }
		// px = tcRotX(3, 180) * px;
		// nx = tcRotX(3, 180) * nx;

		// mat test_p = px.t();
		// test_p.save(R"(test_xinhou_8.13.txt)", raw_ascii);

		// //出线延长段
		// //vec3 p_B = { B, 0.0, 0.0 };
		// //vec3 p_qie2 = { A + tan(tcRadians(data_canshu.angle_end)), 0.0, 1.0 };
		// //vec3 p_v2 = normalise(p_qie2 - p_B);
		// //for (int i = 0; i < extend_count; i++)
		// //{
		//	// vec3 ans_p = p_B + i * delta_dis * p_v2;
		//	// px.col(i + extend_count+ p_count) = ans_p;

		//	// //切向转90度
		//	// if (i == 0)
		//	// {
		//	// }
		//	// else
		//	// {
		//	//	 vec3 ans_ls = ans_p - px.col(i - 1);
		//	//	 vec3 ans_n = tcRotY(3, 90) * ans_ls;
		//	//	 nx.col(i + extend_count + p_count) = normalise(ans_n);
		//	// }
		// //}
		// //nx.col(extend_count + p_count - 1) = nx.col(extend_count + p_count);
	}

	//球头面芯厚计算版本2 zy 8.13 
	//要求相对球心点在xoz平面内，两点夹角相等
	int p_count = px.n_cols;
	double A = self_Dao->get_gg_canshu_D_qiu() / 2.0 - data_canshu.deep_qie;
	double B = self_Dao->get_gg_canshu_D_qiu() / 2.0 * data_canshu.jin_percent_r;

	double delta_r = (A - B) / (1.0 * p_count);
	double delta_ang = 90.0 / (1.0 * p_count);
	//曲线段
	for (int i = 0; i < p_count; i++)
	{
		vec3 start_p = { 0.0, 0.0 , -(A - i * delta_r) };
		vec3 ans_p = tcRotY(3, -(i * delta_ang)) * start_p;
		px.col(i) = ans_p;

		//切向转90度
		if (i == 0)
		{
		}
		else
		{
			vec3 ans_ls = ans_p - px.col(i - 1);
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = normalise(ans_n);
		}
	}
	nx.col(0) = nx.col(1);

	// mat test_p = px.t();
	//test_p.save(R"(test_xinhou_9.24-deng.txt)", raw_ascii);
}

void Miller_GX_ZQ_QDM::cal_xinhoumian(Cal_RenXian& ans_rx, mat& px, mat& nx)
{

}

Miller_GX_ZQ_QDM::Miller_GX_ZQ_QDM()
{
	gx_type = 0;
}

Miller_GX_ZQ_QDM::~Miller_GX_ZQ_QDM()
{
}

//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数

Miller_GX_ZQ_QDM::Miller_GX_ZQ_QDM(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_QDM::Miller_GX_ZQ_QDM(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_QDM::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_QDM::Load(int in_pos)
{
	//恢复参数
	CanShu_ZQ_QDM  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_QDM::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

//将参数读到对话框



void Miller_GX_ZQ_LXC::get_canshu(Canshu_ZQ_LXC& ans)
{
	ans = data_canshu;
}

//A设置设置周刃螺旋槽参数

void Miller_GX_ZQ_LXC::set_canshu(Canshu_ZQ_LXC& ptr)
{
	data_canshu = ptr;
	data_canshu = ptr;
	self_xingcan->set_Canshu_ZQ_LXC(ptr);
}

//A.1设置周刃螺旋槽参数

void Miller_GX_ZQ_LXC::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_lxc); //改为public
	self_xingcan = &ptr;
	/*cal_renxian(Cal_RenXian& ans_rx);
	cal_leadface(Cal_RenXian& ans_rx);*/
}


//计算基本刀路

void Miller_GX_ZQ_LXC::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	prog_of_gx->set_jingeilv(jingeilv, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);
}

void Miller_GX_ZQ_LXC::cal_base_DL()
{

	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			self_Dao->get_renxian_of_luo_cao(ls_ren_pos, get_renxian);
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//2、生成前刀面数据
			mat data_qdm;
			cal_leadface(ls_renxian, data_canshu.type, data_qdm);

			int p_count = data_qdm.n_cols;

			{
				////3、准备计算砂轮位姿的数据
				//mat p_data(3, p_count, fill::zeros);
				//mat n_data(3, p_count, fill::zeros);
				//mat t_data(3, p_count, fill::zeros);
				//p_data = data_qdm.submat(0, 0, 2, p_count - 1);
				//n_data = data_qdm.submat(9, 0, 11, p_count - 1);
				//t_data = data_qdm.submat(3, 0, 5, p_count - 1);
				////3.1、芯厚面数据
				//int p_count2 = p_count + (4 * shalun_canshu.D) / 0.1;
				//mat px_data(3, p_count2, fill::zeros);
				//mat nx_data(3, p_count2, fill::zeros);
				//cal_xinhoumian(px_data, nx_data, shalun_canshu.D);

				//mat33 sys_xh = eye(3, 3);
				//vec3 p_xh = { 0.0,0.0, 0.0 };

				////test
				//mat ans_p = p_data.t();
				//ans_p.save(R"(test_luo-11.13.txt)", raw_ascii);
				//mat ans_p2 = px_data.t();
				//ans_p2.save(R"(test_luoxinhou-11.13.txt)", raw_ascii);

				//xt_XiDao_HZ ls_cal_dl;
				//ls_cal_dl.Set_QDM(p_data, n_data, t_data); //++切向
				//ls_cal_dl.Set_XHM(px_data, nx_data);
				//ls_cal_dl.Set_SYS_XH(p_xh, sys_xh);
				//ls_cal_dl.Set_SL_Cutting(shalun_canshu.D / 2.0, shalun_canshu.R, data_canshu.angle_qiexue);

				//bool is_input = ls_cal_dl.Check_Input();

				////4、砂轮结果获取 = 工件坐标系下的刀路点
				//vec3 ls_p = { 0.0,0.0,0.0 };
				//mat33 ls_sys = eye(3, 3);
				//bool has_jie = ls_cal_dl.Get_First(ls_p, ls_sys);
				//if (has_jie)
				//{
				   // for (int i = 1; i < p_count - 1; i++)
				   // {
				   //	 ls_cal_dl.Get_Next(ls_p, ls_sys);
				   //	 //计算的结果为，抽象的回转面与圆角的回转轴中心，通过砂轮安装状态才能确定出位姿
				   //	 //根据砂轮的内外磨，确定z轴是否反向

				   //	 //Z轴：砂轮轴朝向磨削面法向
				   //	 //X轴：轴心指向磨削点进行修改-不旋转z 9.13
				   //	 //右手系
				   //	 //ls_sys = ls_sys * tcRotZ(3, 180.0);

				   //	 //切换砂轮内外侧磨削 8.7 mark 默认内侧 9.9 
				   //	 if (in_or_out == 1)
				   //	 {
				   //		 ls_sys = ls_sys * tcRotX(3, 180.0);
				   //	 }
				   //	 else
				   //	 {
				   //		 ls_sys = ls_sys * tcRotX(3, 0.0);
				   //	 }

				   //	 mat33 G_SYS_SL = eye(3, 3);
				   //	 G_SYS_SL.col(0) = ls_sys.col(0);
				   //	 G_SYS_SL.col(1) = ls_sys.col(1);
				   //	 G_SYS_SL.col(2) = ls_sys.col(2);

				   //	 vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1
				   //	 //转为后刀面坐标系的定义，不完全准确，用于进退刀方向的计算-11.12
				   //	 // X_HDM = -X_QDM, Y_HDM = -Y_QDM, Z_HDM = Z_QDM,

				   //	 mat33 G_SYS_QDM = {
				   //		 {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   //		 {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   //		 {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				   //	 //不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				   //	 DL_P ans_DL_P;
				   //	 ans_DL_P.G_P = p_data.col(i);
				   //	 ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				   //	 ans_DL_P.G_SYS_SL = G_SYS_SL;

				   //	 DL_part.Data.push_back(ans_DL_P);
				   // }
				//}
				//else
				//{
				   // return;
				//}
			}

			//计算刀路点 3.25
#pragma region MyRegion
			vec3 start_qdm_p = data_qdm.submat(0, 0, 2, 0);
			vec start_sub = data_qdm.submat(3, 0, 11, 0); //取出为9*1
			mat33 G_SYS_QDM = {
				{start_sub(0),  start_sub(3), start_sub(6)},
				{start_sub(1),  start_sub(4), start_sub(7)},
				{start_sub(2),  start_sub(5), start_sub(8)}, };
			//初始砂轮位姿
			mat33 G_SYS_SL = G_SYS_QDM;
			G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度

			double xinhou_R = self_Dao->get_gg_canshu_D_qiu() * data_canshu.percent_r;
			double ans_zhuan = Cal_LXC_SL_SYS_by_XH(start_qdm_p, G_SYS_SL, shalun_canshu.D / 2.0, xinhou_R);

			G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_qdm_p = data_qdm.submat(0, i, 2, i);
				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
				   {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_QDM;
				G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

				//切换砂轮内外侧磨削 
				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				//不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_qdm_p;
				ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}
#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				double dis_start_extend = data_canshu.dis_start_extend;

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_QDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_QDM_start * (-tcX(3)) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.dis_end_extend;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_QDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_QDM_start * (tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}

			}

			//5、螺旋槽单刃进退刀--11.4
			XiDao_LXC_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_ZQ_LXC::cal_new_renxian(Cal_RenXian& in_rx)
{
	//1、旋转
	//mat rotate_mat = tcRotZ(3, ls_ren_pos);

	//mat ls_data = in_rx.get_kongjianxian(); //n*3
	//ls_data = ls_data.t(); //3*n
	//ls_data = rotate_mat * ls_data;

	//KongJianXian ls_kjx;
	//ls_kjx.init_data(ls_data);
	//in_rx.ImportData_by_luoxuancao(ls_kjx);
}

//计算引导面

void Miller_GX_ZQ_LXC::cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm)
{
	//螺旋槽前刀面：刃线法坐标系绕x转 90-前角
	//根据前角类型：旋转不同的刃线坐标系--11.7
	int p_num = in_rx.get_p_num();
	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat ls_sys = eye(3, 3);
		if (ang_type == 0)
		{
			ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_n1));
		}
		else
		{
			//test
			mat test_mat = in_rx.hSYS(i);
			//ls_sys = in_rx.hSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_d)) * tcRotY(3, self_Dao->get_gg_canshu_luo());
			//先Z转螺旋角，在X转修正后的前角2.20
			double ls_ang_luo = self_Dao->get_gg_canshu_luo();
			double cal_ang_qian = data_canshu.ang_d / cos(tcRadians(ls_ang_luo));
			ls_sys = in_rx.hSYS(i) * tcRotZ(3, ls_ang_luo) * tcRotX(3, (90.0 - data_canshu.ang_d));
		}

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}


void Miller_GX_ZQ_LXC::cal_xinhoumian(mat& px, mat& nx, double sl_D)
{
	int p_count = px.n_cols;
	vec3 start_p = { self_Dao->get_gg_canshu_D_qiu() / 2.0, 0.0, 0.0 };
	// vec3 start_end = { self_Dao->get_gg_canshu_D_bing()  , 0.0, self_Dao->get_gg_canshu_len_ren() };
	double ls_hight = self_Dao->get_gg_canshu_len_ren() * tan(tcRadians(self_Dao->get_gg_canshu_Zhui()));
	vec3 start_end = { start_p(0) + ls_hight, 0.0,  self_Dao->get_gg_canshu_len_ren() };
	start_p(0) = start_p(0) * data_canshu.percent_r;
	start_end(0) = start_end(0) * data_canshu.percent_r;

	//double delta = 1.0 / (p_count * 1.0);
	double delta = 0.1;
	vec3 vt_start_end = normalise(start_end - start_p);

	vec3 start_p_front = start_p + (-vt_start_end * sl_D);
	//start_p_front(2) = start_p_front(2) -  sl_D;

	vec3 start_p_back = start_p + (vt_start_end * sl_D);
	//start_p_back(2) = start_p_back(2) +  sl_D;

	//3段线组成
	int count1 = (sl_D) / delta;
	int count2 = count1 + p_count + (sl_D) / delta;
	px.resize(3, 0);
	px.insert_cols(0, count2);
	nx.resize(3, 0);
	nx.insert_cols(0, count2);
	//前延长
	vec3 v_p_end = vt_start_end;
	for (int i = 0; i < count1; i++)
	{
		vec3 ans_p = start_p_front + i * delta * v_p_end;
		px.col(i) = ans_p;
		//切向转90度
		if (i == 0)
		{
		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(0) = nx.col(1);

	//中间
	v_p_end = vt_start_end;
	int index = 0;
	for (int i = count1; i < count1 + p_count; i++)
	{
		vec3 ans_p = start_p + index * delta * v_p_end;
		index++;
		px.col(i) = ans_p;
		//切向转90度
		if (i == count1)
		{

		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(count1) = nx.col(count1 + 1);
	//后延长
	//v_p_end = normalise(start_p_back - start_end);
	//int index2 = 0;
	//for (int i = count1 + p_count ; i < count2 ; i++)
	//{
	   // vec3 ans_p = start_end + index2 * delta * v_p_end;
	   // index2++;
	   // px.col(i) = ans_p;
	   // //切向转90度
	   // if (i == count1 + p_count)
	   // {

	   // }
	   // else
	   // {
	   //	 vec3 ans_ls = normalise(ans_p - px.col(i - 1));
	   //	 vec3 ans_n = tcRotY(3, 90) * ans_ls;
	   //	 nx.col(i) = ans_n;
	   // }
	//}
	//nx.col(count1 + p_count) = nx.col(count1 + p_count + 1);

	//test
	//ans_p = px.t();
	//ans_p.save(R"(test_芯厚-9.9.txt)", raw_ascii);
}

Miller_GX_ZQ_LXC::Miller_GX_ZQ_LXC()
{
	gx_type = 1;
}

Miller_GX_ZQ_LXC::~Miller_GX_ZQ_LXC()
{
}

Miller_GX_ZQ_LXC::Miller_GX_ZQ_LXC(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

// 通过 Miller_GX_Base 继承

void Miller_GX_ZQ_LXC::set_shalun_set()
{
}

void Miller_GX_ZQ_LXC::set_sudu_set()
{
}

Miller_GX_ZQ_LXC::Miller_GX_ZQ_LXC(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_LXC::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_LXC::Load(int in_pos)
{
	//恢复参数
	Canshu_ZQ_LXC  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_LXC::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_ZQ_HDM_1::get_canshu(Canshu_ZQ_HDM_1& ans)
{
	ans = data_canshu;
}

//A设置设置后刀面参数

void Miller_GX_ZQ_HDM_1::set_canshu(Canshu_ZQ_HDM_1& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_Canshu_ZQ_HDM_1(ptr);

}

//A.1设置后刀面参数

void Miller_GX_ZQ_HDM_1::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_hdm_1); //改为public
	self_xingcan = &ptr;
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
}



//计算基本刀路

void Miller_GX_ZQ_HDM_1::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	prog_of_gx->set_jingeilv(jingeilv, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);	 //

}

void Miller_GX_ZQ_HDM_1::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本球头刃线和螺旋线的点数量
			int p_count_qiu = self_Dao->get_renxian_of_qiu_count_p(ls_ren_pos);
			int p_count_luo = self_Dao->get_renxian_of_luo_count_p(ls_ren_pos);

			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_1(ls_ren_pos, data_hdm);

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_qiu(ls_ren_pos, ren_hdm1);
			Cal_RenXian ren_hdm2;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_hdm2);

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(p_count_qiu, p_count_luo, ls_qie, ls_wy);

			int p_all_count = p_count_qiu + p_count_luo;
			for (int i = 0; i < p_all_count; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;
				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				//只修球头
				{
					vec3 ren_n, ren_t;
					double theta = 0.0;
					double ang_xiu = 0.0;
					if (i < p_count_qiu)
					{
						ren_n = ren_hdm1.hY(i); //平面法向
						ren_t = ren_hdm1.hX(i);
					}
					else
					{
						ren_n = ren_hdm2.hY(i - p_count_qiu);
						ren_t = ren_hdm2.hX(i - p_count_qiu);
					}
					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					//vec3 ls_x = normalise( dot(ren_t, G_SYS_SL.col(0)) * G_SYS_SL.col(0));
					theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					ang_xiu = tcDegree(acos(theta));
					if (abs(theta) > 1.0) //2025.3.26 zy 柱面后刀面修正时，角度nan
					{
						ang_xiu = 0.0;
					}
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			//角度延长过中刀路点
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				//dis_start_extend = 0.1; //X指向回转轴且偏下-1.13,转30度
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;
				vec3 t_yan = G_SYS_HDM_start * tcRotZ(3, 0.0) * tcX(3); //转角大不能形成交线//1.16
				t_yan(2) = -t_yan(2);
				t_yan = normalise(t_yan);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + t_yan * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //横刃砂轮以0度后角延长1.16-后角5°横刃在球面上0.00098
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.dis_end_extend;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_ZQ_HDM_1::cal_new_hdm(mat& in_mat)
{
	//1、旋转
	mat rotate_mat = tcRotZ(3, 0.0);

	int count_p = in_mat.n_cols;
	for (int i = 0; i < count_p; i++)
	{
		vec ls_col = in_mat.submat(0, i, 11, i);//一行数据

		vec cur_p = { ls_col(0),ls_col(1),ls_col(2) };
		mat33 cur_sys = { {ls_col(3),ls_col(6),ls_col(9)  },
						   {ls_col(4),ls_col(7),ls_col(10) },
						   {ls_col(5),ls_col(8),ls_col(11) } };

		cur_p = rotate_mat * cur_p;
		cur_sys = rotate_mat * cur_sys;

		vec ans_col = { cur_p(0),cur_p(1),cur_p(2),
			cur_sys.col(0)(0),cur_sys.col(0)(1),cur_sys.col(0)(2),
			cur_sys.col(1)(0),cur_sys.col(1)(1),cur_sys.col(1)(2),
			cur_sys.col(2)(0),cur_sys.col(2)(1),cur_sys.col(2)(2), };
		in_mat.col(i) = ans_col;
	}
}


void Miller_GX_ZQ_HDM_1::cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy)
{
	int p_num1 = p_count_qiu * data_canshu.pos_percent;
	double delta_ang_qie = (data_canshu.angle_qiexue_qiu2 - data_canshu.angle_qiexue_qiu) / p_num1;
	double delta_ang_wy = (data_canshu.angle_wy_qiu2 - data_canshu.angle_wy_qiu) / p_num1;
	for (int i = 0; i < p_num1; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num2 = p_count_qiu - p_num1;
	delta_ang_qie = (data_canshu.angle_qiexue_luo - data_canshu.angle_qiexue_qiu2) / p_num2;
	delta_ang_wy = (data_canshu.angle_wy_luo - data_canshu.angle_wy_qiu2) / p_num2;

	for (int i = 0; i < p_num2; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu2 + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu2 + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num3 = p_count_luo;
	delta_ang_qie = data_canshu.angle_qiexue_luo;
	delta_ang_wy = data_canshu.angle_wy_luo;
	for (int i = 0; i < p_num3; i++)
	{
		double cur_qie = delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}
}


//根据引导刃线生成引导面

void Miller_GX_ZQ_HDM_1::gen_leadface_by_ren(Cal_RenXian& in_line)
{
	// //点的法向：刃线法坐标系右乘绕x旋转 后角)，取y向量
	//int p_num = in_line.get_p_num();
	//data_lead_face.hdm_1.insert_cols(0, p_num);
	////螺旋槽部分
	//for (int i = 0; i < p_num; i++)
	//{
	//	vec3 ls_p = in_line.P(i);
	//	mat ls_sys = in_line.nSYS(i) * tcRotX(3, data_canshu.ang_n1_luo);
	//	vec3 ls_n = ls_sys.col(1);
	//	vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,ls_n(0) ,ls_n(1) ,ls_n(2) };
	//	data_lead_face.hdm_1.col(i) = ans;
	//}
}

void Miller_GX_ZQ_HDM_1::cal_xinhoumian(mat& px, mat& nx, double sl_D)
{
}

Miller_GX_ZQ_HDM_1::Miller_GX_ZQ_HDM_1()
{
	gx_type = 2;
}

Miller_GX_ZQ_HDM_1::~Miller_GX_ZQ_HDM_1()
{
}

Miller_GX_ZQ_HDM_1::Miller_GX_ZQ_HDM_1(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_ZQ_HDM_1::set_shalun_set()
{
}

void Miller_GX_ZQ_HDM_1::set_sudu_set()
{
}

Miller_GX_ZQ_HDM_1::Miller_GX_ZQ_HDM_1(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_HDM_1::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_HDM_1::Load(int in_pos)
{		//恢复参数
	Canshu_ZQ_HDM_1  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_HDM_1::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_ZQ_HDM_2::get_canshu(Canshu_ZQ_HDM_2& ans)
{
	ans = data_canshu;
}

//A设置设置后刀面参数

void Miller_GX_ZQ_HDM_2::set_canshu(Canshu_ZQ_HDM_2& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_Canshu_ZQ_HDM_2(ptr);

}

//A.1设置后刀面参数

void Miller_GX_ZQ_HDM_2::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_hdm_2); //改为public
	self_xingcan = &ptr;
	//cal_renxian(Cal_RenXian& ans_rx);
	//cal_leadface(Cal_RenXian& ans_rx);
}

//计算基本刀路

void Miller_GX_ZQ_HDM_2::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{ //需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	prog_of_gx->set_jingeilv(jingeilv, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);	 //
}

void Miller_GX_ZQ_HDM_2::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;
			//1、从铣刀获取基本球头刃线和螺旋线的点数量
			int p_count_qiu = self_Dao->get_renxian_of_qiu_count_p(ls_ren_pos);
			int p_count_luo = self_Dao->get_renxian_of_luo_count_p(ls_ren_pos);

			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_2(ls_ren_pos, data_hdm);

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_qiu(ls_ren_pos, ren_hdm1);
			Cal_RenXian ren_hdm2;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_hdm2);

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(p_count_qiu, p_count_luo, ls_qie, ls_wy);

			int p_all_count = p_count_qiu + p_count_luo;
			for (int i = 0; i < p_all_count; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_HDM;
				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				{
					vec3 ren_n, ren_t;
					if (i < p_count_qiu)
					{
						ren_n = ren_hdm1.hY(i); //平面法向
						ren_t = ren_hdm1.hX(i);
					}
					else
					{
						ren_n = ren_hdm2.hY(i - p_count_qiu);
						ren_t = ren_hdm2.hX(i - p_count_qiu);
					}
					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					//vec3 ls_x = normalise( dot(ren_t, G_SYS_SL.col(0)) * G_SYS_SL.col(0));
					double theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					double ang_xiu = tcDegree(acos(theta));
					if (abs(theta) > 1.0) //2025.3.26 zy 柱面后刀面修正时，角度nan
					{
						ang_xiu = 0.0;
					}
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}
				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_HDM_start * tcX(3) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.dis_end_extend;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}


}


void Miller_GX_ZQ_HDM_2::cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy)
{
	int p_num1 = p_count_qiu * data_canshu.pos_percent;
	double delta_ang_qie = (data_canshu.angle_qiexue_qiu2 - data_canshu.angle_qiexue_qiu) / p_num1;
	double delta_ang_wy = (data_canshu.angle_wy_qiu2 - data_canshu.angle_wy_qiu) / p_num1;
	for (int i = 0; i < p_num1; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num2 = p_count_qiu - p_num1;
	delta_ang_qie = (data_canshu.angle_qiexue_luo - data_canshu.angle_qiexue_qiu2) / p_num2;
	delta_ang_wy = (data_canshu.angle_wy_luo - data_canshu.angle_wy_qiu2) / p_num2;

	for (int i = 0; i < p_num2; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu2 + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu2 + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num3 = p_count_luo;
	delta_ang_qie = data_canshu.angle_qiexue_luo;
	delta_ang_wy = data_canshu.angle_wy_luo;
	for (int i = 0; i < p_num3; i++)
	{
		double cur_qie = delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}
}


Miller_GX_ZQ_HDM_2::Miller_GX_ZQ_HDM_2()
{
	gx_type = 3;
}

Miller_GX_ZQ_HDM_2::~Miller_GX_ZQ_HDM_2()
{
}

Miller_GX_ZQ_HDM_2::Miller_GX_ZQ_HDM_2(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_HDM_2::Miller_GX_ZQ_HDM_2(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_HDM_2::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;

}

void Miller_GX_ZQ_HDM_2::Load(int in_pos)
{	//恢复参数
	Canshu_ZQ_HDM_2  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_HDM_2::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_ZQ_HDM_3::get_canshu(Canshu_ZQ_HDM_3& ans)
{
	ans = data_canshu;
}

//A设置设置后刀面参数

void Miller_GX_ZQ_HDM_3::set_canshu(Canshu_ZQ_HDM_3& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_Canshu_ZQ_HDM_3(ptr);

}

//A.1设置后刀面参数

void Miller_GX_ZQ_HDM_3::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_hdm_3); //改为public
	self_xingcan = &ptr;
	//cal_renxian(Cal_RenXian& ans_rx);
	//cal_leadface(Cal_RenXian& ans_rx);
}

void Miller_GX_ZQ_HDM_3::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
}

//计算基本刀路

void Miller_GX_ZQ_HDM_3::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;
			//1、从铣刀获取基本球头刃线和螺旋线的点数量
			int p_count_qiu = self_Dao->get_renxian_of_qiu_count_p(ls_ren_pos);
			int p_count_luo = self_Dao->get_renxian_of_luo_count_p(ls_ren_pos);

			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_3(ls_ren_pos, data_hdm);
			//砂轮位姿与后刀面关系
			//X_sl = -X_hdm, Y_sl = -Y_hdm,  Z_sl = G_Z_HDM;

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(p_count_qiu, p_count_luo, ls_qie, ls_wy);

			int p_all_count = p_count_qiu + p_count_luo;
			for (int i = 0; i < p_all_count; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度,(-qie。9.6)
				mat33 ls_G_SYS_SL = G_SYS_HDM * tcRotZ(3, cur_wy) * tcRotY(3, -cur_qie);  //砂轮坐标系右乘

				vec3 G_X_SL = -ls_G_SYS_SL.col(0); //9.21
				vec3 G_Y_SL = -ls_G_SYS_SL.col(1);
				vec3 G_Z_SL = ls_G_SYS_SL.col(2);
				//vec3 G_X_SL = normalise(cross(G_Y_SL, G_Z_SL));

				mat33 G_SYS_SL = {
					{G_X_SL(0),G_Y_SL(0), G_Z_SL(0)},
					{G_X_SL(1),G_Y_SL(1), G_Z_SL(1)},
					{G_X_SL(2),G_Y_SL(2), G_Z_SL(2)}, };

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//5、单刃进退刀
			XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}


}

void Miller_GX_ZQ_HDM_3::cal_cha_ang(int p_count_qiu, int p_count_luo, vector<double>& ans_qie, vector<double>& ans_wy)
{
	int p_num1 = p_count_qiu * data_canshu.pos_percent;
	double delta_ang_qie = (data_canshu.angle_qiexue_qiu2 - data_canshu.angle_qiexue_qiu) / p_num1;
	double delta_ang_wy = (data_canshu.angle_wy_qiu2 - data_canshu.angle_wy_qiu) / p_num1;
	for (int i = 0; i < p_num1; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num2 = p_count_qiu - p_num1;
	delta_ang_qie = (data_canshu.angle_qiexue_luo - data_canshu.angle_qiexue_qiu2) / p_num2;
	delta_ang_wy = (data_canshu.angle_wy_luo - data_canshu.angle_wy_qiu2) / p_num2;

	for (int i = 0; i < p_num2; i++)
	{
		double cur_qie = data_canshu.angle_qiexue_qiu2 + i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_qiu2 + i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	int p_num3 = p_count_luo;
	delta_ang_qie = data_canshu.angle_qiexue_luo;
	delta_ang_wy = data_canshu.angle_wy_luo;
	for (int i = 0; i < p_num3; i++)
	{
		double cur_qie = delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}
}

Miller_GX_ZQ_HDM_3::Miller_GX_ZQ_HDM_3()
{
	gx_type = 4;
}

Miller_GX_ZQ_HDM_3::~Miller_GX_ZQ_HDM_3()
{
}

Miller_GX_ZQ_HDM_3::Miller_GX_ZQ_HDM_3(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_HDM_3::Miller_GX_ZQ_HDM_3(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_HDM_3::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_HDM_3::Load(int in_pos)
{	//恢复参数
	Canshu_ZQ_HDM_3  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_HDM_3::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_ZQ_DaoTiJianXi::get_canshu(CanShu_ZQ_DaoTiJianXi& ans)
{
	ans = data_canshu;
}

//A设置设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoTiJianXi::set_canshu(CanShu_ZQ_DaoTiJianXi& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_ZQ_DaoTiJianXi(ptr);

}

//A.1设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoTiJianXi::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_dt_jx); //改为public
	self_xingcan = &ptr;
}

//计算

void Miller_GX_ZQ_DaoTiJianXi::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_ZQ_DaoTiJianXi::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		//if (data_canshu.selected_ren[i] == 1)
		//{
		   // int ls_ren_pos = i;
		   // double cur_pos = data_canshu.
		   // //2、获取刀面数据
		   //// mat data_hdm;
		   //// self_Dao->get_hdm_1(ls_ren_pos, data_hdm);

		   //// //2.5 直接旋转后刀面数据
		   ////// cal_new_hdm(data_hdm);

		   //// //插值出每个点的切削，位移角度
		   //// vector<double> ls_qie;
		   //// vector<double> ls_wy;

		   //int p_all_count = p_count_qiu + p_count_luo;
		   // for (int i = 0; i < p_all_count; i++)
		   // {
		   //	 double cur_qie = ls_qie[i];
		   //	 double cur_wy = ls_wy[i];

		   //	 vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

		   //	 //矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
		   //	 mat33 G_SYS_HDM = {
		   //		 {ls_sub(0),ls_sub(3), ls_sub(6)},
		   //		 {ls_sub(1),ls_sub(4), ls_sub(7)},
		   //		 {ls_sub(2),ls_sub(5), ls_sub(8)}, };

		   //	 //饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度,(-qie。9.6)
		   //	 mat33 G_SYS_SL = G_SYS_HDM * tcRotZ(3, 180.0);
		   //	 G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

		   //	 vec3 p_sl = data_hdm.submat(0, i, 2, i);

		   //	 DL_P ans_DL_P;
		   //	 ans_DL_P.G_P = p_sl;
		   //	 ans_DL_P.G_SYS_HDM = G_SYS_HDM;
		   //	 //ans_DL_P.G_SYS_SL = G_SYS_SL;

		   //	 //DL_part.Data.push_back(ans_DL_P);
		   // }

		   // //5、单刃进退刀
		   // XiDao_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

		   // //6、组合完整刀路
		   // for (int i = 0; i < DL_part.Data.size(); i++)
		   // {
		   //	 DL_base.Data.push_back(DL_part.Data[i]);
		   // }
		//}
	}
}

Miller_GX_ZQ_DaoTiJianXi::Miller_GX_ZQ_DaoTiJianXi()
{
	gx_type = 5;
}

Miller_GX_ZQ_DaoTiJianXi::~Miller_GX_ZQ_DaoTiJianXi()
{
}

Miller_GX_ZQ_DaoTiJianXi::Miller_GX_ZQ_DaoTiJianXi(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_DaoTiJianXi::Miller_GX_ZQ_DaoTiJianXi(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_DaoTiJianXi::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_DaoTiJianXi::Load(int in_pos)
{	//恢复参数
	CanShu_ZQ_DaoTiJianXi  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_DaoTiJianXi::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

//将参数读到对话框

void Miller_GX_ZQ_DaoJianJianXi::get_canshu(CanShu_ZQ_DaoJianJianXi& ans)
{
	ans = data_canshu;
}

//A设置设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoJianJianXi::set_canshu(CanShu_ZQ_DaoJianJianXi& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_ZQ_DaoJianJianXi(ptr);

}

//A.1设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoJianJianXi::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_dj_jx); //改为public
	self_xingcan = &ptr;
}


void Miller_GX_ZQ_DaoJianJianXi::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	prog_of_gx->set_jingeilv(jingeilv, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);	 //

}

void Miller_GX_ZQ_DaoJianJianXi::cal_base_DL()
{
	vector<double> v_dengfen_ang;
	self_Dao->get_dengfen_ang(v_dengfen_ang);
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			double cur_dengfen_ang = v_dengfen_ang[i];

			//1、从铣刀获取刀尖间隙数据
			mat djjx_p;
			vector<mat33> djjx_sys;
			//self_Dao->get_djjx_p_sys(ls_ren_pos, djjx_p, djjx_sys);
			   //mat base_p_djjx;//指向刀尖 3*n
			   //vector<mat33> base_sys_djjx;  //X切向、Z法向
			cal_leadline(cur_dengfen_ang, djjx_p, djjx_sys); //相对于标准后刀面tcRotZ（180）

			//test
			mat ans_p = djjx_p.t();
			ans_p.save(R"(test_djjx-12.24.txt)", raw_ascii);
			/*mat ans_p2 = px_data.t();
			ans_p2.save(R"(test_luoxinhou-11.18.txt)", raw_ascii);*/

			//2、

			//3、取法坐标系转位移角度
			int p_count = djjx_p.n_cols;
			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_p = djjx_p.col(i);
				mat33 ls_hdm_sys = djjx_sys[i];

				//矩阵按照列构造，
				// sl_sys_z = ls_sys_z, hdm_x = ls_sys_x, hdm_y = ls_sys_y
				mat33 G_SYS_SL = ls_hdm_sys;

				//饶后自身坐标系转90位移角度，90切削角度，砂轮立起来
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90) * tcRotY(3, 90);

				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_p;
				ans_DL_P.G_SYS_HDM = ls_hdm_sys;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
		   //用刀路点的起始砂轮切向延长指定距离 当前刃线刀柄指向刀间,
			{
				//double dis_extend = data_canshu.dis_end_extend;  //需要加密延长点12.2
				//vec end_v = ls_renxian.nX(ls_renxian.n_P - 1);
				//vec end_y = ls_renxian.nY(ls_renxian.n_P - 1);
				//vec end_z = ls_renxian.nZ(ls_renxian.n_P - 1);

				//vec3 p_dl_start = DL_part.Data[0].G_P;
				//mat33 G_SYS_SL_start = DL_part.Data[0].G_SYS_SL;
				//mat33 ls_sys_sl = G_SYS_SL_start * tcRotX(3, ang_hen_tui); //横向退刀
				//vec start_v = -ls_sys_sl.col(1); //起点砂轮y负切向延长,旋转后

				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_SL_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				//double dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//int count_yan = dis_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_start;
				   // ans_start.G_P = p_dl_start + (start_v)*i * dis_p;
				   // ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_start.G_SYS_SL = G_SYS_SL_start;
				   // ans_start.point_type = 2;

				   // DL_P ans_end;
				   // ans_end.G_P = p_dl_end + (end_v)*i * dis_p; //终点刃线切向 11.28
				   // ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
				   // ans_end.G_SYS_SL = G_SYS_SL_end;
				   // ans_end.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				   // DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//5、单刃进退刀--
			XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao); //后刀面模式

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_ZQ_DaoJianJianXi::cal_leadline(double in_pos_ang, mat& base_p_djjx, vector<mat33>& base_sys_djjx)
{
	// void Ren_data_D_ZQ::cal_base_djjx(CanShu_ZQ_GongGong& in_gg_canshu, double in_pos_ang)

	//计算刀尖间隙-单位坐标系中计算
	double ls_R = data_canshu.djjx_R;
	//两个角度决定圆弧转角
	double ang_start = data_canshu.djjx_ang_down;
	double ang_end = 90.0 - data_canshu.djjx_ang_up;

	vec3 o_p = { ls_R,0.0,0.0 };
	vec3 cal_p = o_p;
	double rotate_ang = ang_start;
	mat ans_p; //指向刀尖
	deque<mat33> ans_sys;
	KongJianXian ans_line;

	//圆弧部分
	while (rotate_ang < ang_end) //限制高度点
	{
		cal_p = tcRotY(3, -rotate_ang) * o_p;
		ans_p.insert_cols(ans_p.n_cols, cal_p);

		vec y_sys = { 0.0,1.0,0.0 };
		vec z_sys = { cal_p(0), 0.0, cal_p(2) };
		z_sys = normalise(z_sys);
		vec x_sys = normalise(tc_cross(y_sys, z_sys));

		mat33 cal_sys = { {x_sys(0),y_sys(0),z_sys(0)} ,
						 {x_sys(1),y_sys(1),z_sys(1)} ,
						 {x_sys(2),y_sys(2),z_sys(2)} };
		ans_sys.push_back(cal_sys);

		rotate_ang = rotate_ang + 1.0;
	}

	//下端直线
	vec3 v_down = normalise(ans_p.col(0) - ans_p.col(1));
	mat33 sys_down = ans_sys.at(0);
	double delta_dis = norm(ans_p.col(1) - ans_p.col(0));
	double dis_all = ls_R / cos(tcRadians(data_canshu.djjx_ang_down));
	int count_p = dis_all / delta_dis;

	for (int i = 0; i < count_p; i++)
	{
		cal_p = ans_p.col(0) + v_down * delta_dis;
		ans_p.insert_cols(0, cal_p);

		ans_sys.push_front(sys_down);
	}


	//上端直线
	vec3 v_up = normalise(ans_p.col(ans_p.n_cols - 1) - ans_p.col(ans_p.n_cols - 2));
	mat33 sys_up = ans_sys.at(ans_sys.size() - 1);
	dis_all = ls_R / cos(tcRadians(data_canshu.djjx_ang_up));
	count_p = dis_all / delta_dis;

	for (int i = 0; i < count_p; i++)
	{
		cal_p = ans_p.col(ans_p.n_cols - 1) + v_up * delta_dis;
		ans_p.insert_cols(ans_p.n_cols, cal_p);

		ans_sys.push_back(sys_up);
	}

	//线旋转-绕圆弧中间点旋转，提供三个转轴,
	vec3 p_mid = ans_p.col(ans_p.n_cols / 2); //可以提供选择参考点的接口在前端，todo：
	mat33 sys_mid = ans_sys[ans_sys.size() / 2];//直接取中间位置的坐标系, 参考后刀面坐标系
	mat33 sys_rotate_line = tcRotX(3, data_canshu.djjx_ang_x)
		* tcRotY(3, data_canshu.djjx_ang_y) * tcRotZ(3, data_canshu.djjx_ang_z);
	for (int i = 0; i < ans_p.n_cols; i++)
	{
		//平移到原点，旋转后，复位
		ans_p.col(i) = sys_rotate_line * (ans_p.col(i) - p_mid) + p_mid;
		ans_sys[i] = sys_rotate_line * ans_sys[i];
	}

	//test
	//mat test_djjx2 = ans_p.t();
	//test_djjx2.save(R"(test_djjx_2-12.3.txt)", raw_ascii);

	//偏移坐标系
	mat33 sys_trans = eye(3, 3) * tcRotX(3, 180.0);

	//放到工件坐标系
	vec pianzhi = { -data_canshu.djjx_pianzhi_x, -data_canshu.djjx_pianzhi_y, -data_canshu.djjx_pianzhi_z };
	for (int i = 0; i < ans_p.n_cols; i++)
	{
		ans_p.col(i) = sys_trans * ans_p.col(i) + pianzhi;
		ans_sys[i] = sys_trans * ans_sys[i];

		//工件坐标系中旋转对应位置
		ans_p.col(i) = tcRotZ(3, in_pos_ang) * ans_p.col(i);
		ans_sys[i] = tcRotZ(3, in_pos_ang) * ans_sys[i];
	}

	base_p_djjx = ans_p;
	for (int i = 0; i < ans_sys.size(); i++)
	{
		base_sys_djjx.push_back(ans_sys[i]);
	}


	//test
	//mat test_djjx = base_p_djjx.t();
	//test_djjx.save(R"(test_djjx-11.27.txt)", raw_ascii);
}

Miller_GX_ZQ_DaoJianJianXi::Miller_GX_ZQ_DaoJianJianXi()
{
	gx_type = 6;
}

Miller_GX_ZQ_DaoJianJianXi::~Miller_GX_ZQ_DaoJianJianXi()
{
}

Miller_GX_ZQ_DaoJianJianXi::Miller_GX_ZQ_DaoJianJianXi(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_DaoJianJianXi::Miller_GX_ZQ_DaoJianJianXi(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_DaoJianJianXi::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_DaoJianJianXi::Load(int in_pos)
{	//恢复参数
	CanShu_ZQ_DaoJianJianXi  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_DaoJianJianXi::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

//A设置设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoJianFenXieCao::get_canshu(CanShu_ZQ_DaoJianFenXieCao& ans)
{
	ans = data_canshu;
}

void Miller_GX_ZQ_DaoJianFenXieCao::set_canshu(CanShu_ZQ_DaoJianFenXieCao& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_ZQ_DaoJianFenXieCao(ptr);

}

//A.1设置周刃螺旋槽参数

void Miller_GX_ZQ_DaoJianFenXieCao::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_zq_dj_fxc); //改为public
	self_xingcan = &ptr;
}

void Miller_GX_ZQ_DaoJianFenXieCao::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

//计算

void Miller_GX_ZQ_DaoJianFenXieCao::cal_base_DL()
{
}

Miller_GX_ZQ_DaoJianFenXieCao::Miller_GX_ZQ_DaoJianFenXieCao()
{
	gx_type = 7;
}

Miller_GX_ZQ_DaoJianFenXieCao::~Miller_GX_ZQ_DaoJianFenXieCao()
{
}

Miller_GX_ZQ_DaoJianFenXieCao::Miller_GX_ZQ_DaoJianFenXieCao(Miller_D_ZQ* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_ZQ_DaoJianFenXieCao::Miller_GX_ZQ_DaoJianFenXieCao(int in_name)
{
	name = in_name;
}

int Miller_GX_ZQ_DaoJianFenXieCao::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_ZQ_DaoJianFenXieCao::Load(int in_pos)
{	//恢复参数
	CanShu_ZQ_DaoJianFenXieCao  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_ZQ_DaoJianFenXieCao::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_PD_DCC::get_canshu(CanShu_PD_DCC& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_DCC::set_canshu(CanShu_PD_DCC& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_DCC(ptr);

}

void Miller_GX_PD_DCC::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_dcc); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_PD_DCC::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
}

void Miller_GX_PD_DCC::cal_base_DL()
{
	{
		vector<double> v_dengfen_ang;
		self_Dao->get_dengfen_ang(v_dengfen_ang);
		for (int i = 0; i < 6; i++)
		{
			DL DL_part;
			if (data_canshu.selected_ren[i] == 1)
			{
				int ls_ren_pos = i;

				//1、从铣刀获取基本刃线，并对刃线进行编辑
				Cal_RenXian get_renxian;
				self_Dao->get_renxian_of_hen(ls_ren_pos, get_renxian); //中心指向柱面
				//引用传递会修改原始刃线，get引用后复制出一份给后续计算10.30
				Cal_RenXian ls_renxian = get_renxian;

				//1.1刃线工件坐标系下绕Z旋转补偿角度 
				ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

				//2、生成前刀面数据--
				mat data_qdm; //12*n 
				cal_leadface(ls_renxian, data_qdm);

				int p_count = data_qdm.n_cols;

				mat p_data(3, p_count, fill::zeros);
				mat n_data(3, p_count, fill::zeros);
				mat t_data(3, p_count, fill::zeros);
				p_data = data_qdm.submat(0, 0, 2, p_count - 1);		//前刀面点
				n_data = data_qdm.submat(9, 0, 11, p_count - 1);		//法向 = z轴
				t_data = data_qdm.submat(3, 0, 5, p_count - 1);

				mat test_p2 = p_data.t();
				test_p2.save(R"(test_dcc_1.18.txt)", raw_ascii);

				//构造Gpoint前刀面数据 4.22
				std::vector<Bpoint> all_Bp;//芯厚面数据
				std::vector<Gpoint> all_Gp, ans;//前刀面数据

				Gpoint Gp;
				for (int i = 0; i < p_count; i++)
				{
					Gp.set_xyz(p_data(0), p_data(1), p_data(2));
					Gp.set_Qie(t_data(0), t_data(1), t_data(2));
					Gp.set_N(n_data(0), n_data(1), n_data(2));
					all_Gp.push_back(Gp);
				}

				//根据槽型参数构造芯厚面
				//需要转到对应刃的位置
				double cur_ren_ang_pos = v_dengfen_ang[ls_ren_pos];

				vec3 start_p = { data_canshu.dis_center, 0.0,0.0 };
				vec3 end_p = { shalun_canshu.D * 1.5, 0.0,0.0 };
				end_p = tcRotY(3, -data_canshu.ang_caoding) * end_p;
				vec3 left_move = { 0.0,10.0,0.0 };
				vec3 rigt_move = { 0.0,-10.0,0.0 };

				vec3 beg_left_p = tcRotZ(3, cur_ren_ang_pos) * (start_p + left_move);
				vec3 beg_rigt_p = tcRotZ(3, cur_ren_ang_pos) * (start_p + rigt_move);
				vec3 end_left_p = tcRotZ(3, cur_ren_ang_pos) * (end_p + left_move);
				vec3 end_rigt_p = tcRotZ(3, cur_ren_ang_pos) * (end_p + rigt_move);

				Bpoint p[4];
				//面数据
				{
					p[0].set_xyz(start_p + left_move);
					p[1].set_xyz(start_p + rigt_move);
					p[2].set_xyz(end_p + left_move);
					p[3].set_xyz(end_p + rigt_move);

					p[0].set_u(rigt_move);
					p[1].set_u(rigt_move);
					p[2].set_u(rigt_move);
					p[3].set_u(rigt_move);

					vec3 ls_v = normalise(start_p - end_p);
					p[0].set_v(ls_v);
					p[1].set_v(ls_v);
					p[2].set_v(ls_v);
					p[3].set_v(ls_v);
				}
				for (size_t i = 0; i < 4; i++)
				{
					all_Bp.push_back(p[i]);
				}

				mat in_qx_p;
				in_qx_p.insert_cols(in_qx_p.n_cols, beg_left_p);
				in_qx_p.insert_cols(in_qx_p.n_cols, beg_rigt_p);
				mat in_qx_t;
				in_qx_t.insert_cols(in_qx_t.n_cols, normalise(beg_rigt_p - beg_left_p));
				in_qx_t.insert_cols(in_qx_t.n_cols, normalise(beg_rigt_p - beg_left_p));

				mat in_ydx_p;
				in_ydx_p.insert_cols(in_ydx_p.n_cols, end_left_p);
				in_ydx_p.insert_cols(in_ydx_p.n_cols, end_rigt_p);
				mat in_ydx_t;
				in_ydx_t.insert_cols(in_ydx_t.n_cols, normalise(end_left_p - beg_left_p));
				in_ydx_t.insert_cols(in_ydx_t.n_cols, normalise(end_left_p - beg_left_p));

				Bezier_Curve3_QM ls_xhm = Get_Bezier_Curve3_QM_SL(in_qx_p, in_qx_t, in_ydx_p, in_ydx_t);

				QuMian_Grovving Grovving;
				Grovving.Set_XHM(&ls_xhm);
				Grovving.Set_QDM(all_Gp);
				Grovving.Set_SL_data(shalun_canshu.R, shalun_canshu.D / 2.0, data_canshu.angle_qiexue, !in_or_out);//函数默认外侧磨

				if (Grovving.Get_SL_WZ(ans))
				{
					throw 1;
				}

				for (size_t i = 0; i < ans.size(); i++)
				{
					mat44 ls_WZ = ans[i].get_WZ_mat44();

					vec3 ls_p = data_qdm.submat(0, i, 2, i);
					vec3 sys_ls_x = data_qdm.submat(3, i, 5, i);
					vec3 sys_ls_y = data_qdm.submat(6, i, 8, i);
					vec3 sys_ls_z = data_qdm.submat(9, i, 11, i);

					mat33 G_SYS_HDM = eye(3, 3);
					G_SYS_HDM.col(0) = sys_ls_x;
					G_SYS_HDM.col(1) = sys_ls_y;
					G_SYS_HDM.col(2) = sys_ls_z;

					mat33 G_SYS_SL = ls_WZ.submat(0, 0, 2, 2);

					DL_P ans_DL_P;
					ans_DL_P.G_P = ls_p;
					ans_DL_P.G_SYS_HDM = G_SYS_HDM;
					ans_DL_P.G_SYS_SL = G_SYS_SL;

					DL_part.Data.push_back(ans_DL_P);
				}

				//4.5、延长一定距离
				//横向退刀延长开始位姿，然后刀路反向
				{
					double ang_hen_tui = data_canshu.angle_heng_tui;

					double dis_extend = data_canshu.dis_end_extend;  //需要加密延长点12.2
					vec end_v = ls_renxian.nX(ls_renxian.n_P - 1);
					vec end_y = ls_renxian.nY(ls_renxian.n_P - 1);
					vec end_z = ls_renxian.nZ(ls_renxian.n_P - 1);

					vec3 p_dl_start = DL_part.Data[0].G_P;
					mat33 G_SYS_SL_start = DL_part.Data[0].G_SYS_SL;
					mat33 ls_sys_sl = DL_part.Data[0].G_SYS_SL * tcRotX(3, ang_hen_tui); //横向退刀
					vec start_v = ls_sys_sl * (-tcY(3));
					start_v(2) = 0.0;
					start_v = normalise(start_v);

					double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用起始
					dis_p = 0.04;
					int count_yan = dis_extend / dis_p;

					for (int i = 1; i <= count_yan; i++)
					{
						DL_P ans_start;
						ans_start.G_P = p_dl_start + (start_v)*i * dis_p;
						ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
						ans_start.G_SYS_SL = G_SYS_SL_start;
						ans_start.point_type = 2;

						DL_part.Data.insert(DL_part.Data.begin(), ans_start);

						//DL_P ans_end;
						//ans_end.G_P = p_dl_end + (end_v)*i * dis_p; //终点刃线切向 11.28
						//ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
						//ans_end.G_SYS_SL = G_SYS_SL_end;
						//ans_end.point_type = 0;

						//DL_part.Data.insert(DL_part.Data.end(), ans_end);
					}
				}

				//4.6、刀路点反向，只改点的顺序
				reverse(DL_part.Data.begin(), DL_part.Data.end());

				//5、单刃进退刀
				XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

				//6、组合完整刀路
				for (int i = 0; i < DL_part.Data.size(); i++)
				{
					DL_base.Data.push_back(DL_part.Data[i]);
				}
			}
		}
	}

	//for (int i = 0; i < 6; i++)
	//{
	//	DL DL_part;
	//	if (data_canshu.selected_ren[i] == 1)
	//	{
	//		int ls_ren_pos = i;

	//		//1、从铣刀获取基本刃线，并对刃线进行编辑
	//		Cal_RenXian get_renxian;
	//		self_Dao->get_renxian_of_hen(ls_ren_pos, get_renxian); //中心指向柱面
	//		//引用传递会修改原始刃线，get引用后复制出一份给后续计算10.30
	//		Cal_RenXian ls_renxian = get_renxian;

	//		//1.1刃线工件坐标系下绕Z旋转补偿角度 
	//		ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

	//		//2、生成前刀面数据--
	//		//平底端齿槽，端刃横线根据前角变化计算出前刀坐标系，
	//		//磨削点为槽底线上点(起点=横刃起点，且个数相同)，得到砂轮位姿
	//		mat data_qdm; //12*n 
	//		cal_leadface(ls_renxian, data_qdm);

	//int p_count = data_qdm.n_cols;

	//		mat p_data(3, p_count, fill::zeros);
	//		//mat n_data(3, p_count, fill::zeros);
	//		//mat t_data(3, p_count, fill::zeros);
	//		p_data = data_qdm.submat(0, 0, 2, p_count - 1);		//前刀面点
	//		//n_data = data_qdm.submat(9, 0, 11, p_count - 1);		//法向 = z轴
	//		//t_data = data_qdm.submat(3, 0, 5, p_count - 1);

	//		mat test_p2 = p_data.t();
	//		test_p2.save(R"(test_dcc_1.18.txt)", raw_ascii);

	//		//在投影到XOZ平面中，不用计算圆心坐标，可得到夹角
	//		vec3 p_start = data_qdm.submat(0, p_count - 1, 2, p_count - 1);

	//		////计算初始点砂轮位移角度，以初始位姿从初始磨削点向上槽顶角度平移-1.18
	//		//double D_gj = self_Dao->get_gg_canshu_D_qiu();
	//		//double ang_caoding = data_canshu.ang_caoding;
	//		//double D_sl = shalun_canshu.D;
	//		//double ang_ans = 0.0;
	//		//cal_sl_weiyi_ang(D_gj, ang_caoding, D_sl, ang_ans);


	//		//3、根据前刀面坐标系构造砂轮位姿			
	//		for (int i = 0; i < p_count; i++)
	//		{
	//			vec3 ls_p = data_qdm.submat(0, i, 2, i);
	//			vec3 sys_ls_x = data_qdm.submat(3, i, 5, i);
	//			vec3 sys_ls_y = data_qdm.submat(6, i, 8, i);
	//			vec3 sys_ls_z = data_qdm.submat(9, i, 11, i);

	//			mat33 G_SYS_HDM = eye(3, 3);
	//			G_SYS_HDM.col(0) = sys_ls_x;
	//			G_SYS_HDM.col(1) = sys_ls_y;
	//			G_SYS_HDM.col(2) = sys_ls_z;

	//			mat33 ls_G_SYS_HDM = G_SYS_HDM * tcRotZ(3, data_canshu.ang_caoding);

	//			//矩阵按照列构造，
	//			// sl_sys_z = ls_qdm_z, sl_x = ls_qdm_y, sl_y = -ls_qdm_x
	//			mat33 G_SYS_SL = ls_G_SYS_HDM;
	//			G_SYS_SL.col(0) = ls_G_SYS_HDM.col(1);
	//			G_SYS_SL.col(1) = ls_G_SYS_HDM.col(0);
	//			G_SYS_SL.col(2) = -ls_G_SYS_HDM.col(2);

	//			G_SYS_SL = G_SYS_SL * tcRotX(3, data_canshu.angle_qiexue);

	//			if (in_or_out == 1)
	//			{
	//				G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0); //默认内侧
	//			}
	//			else
	//			{
	//				G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
	//			}

	//			DL_P ans_DL_P;
	//			ans_DL_P.G_P = ls_p;
	//			ans_DL_P.G_SYS_HDM = G_SYS_HDM;
	//			ans_DL_P.G_SYS_SL = G_SYS_SL;

	//			DL_part.Data.push_back(ans_DL_P);
	//		}


	//		//4.5、延长一定距离
	//		//横向退刀延长开始位姿，然后刀路反向
	//		{
	//			double ang_hen_tui = data_canshu.angle_heng_tui;

	//			double dis_extend = data_canshu.dis_end_extend;  //需要加密延长点12.2
	//			vec end_v = ls_renxian.nX(ls_renxian.n_P - 1);
	//			vec end_y = ls_renxian.nY(ls_renxian.n_P - 1);
	//			vec end_z = ls_renxian.nZ(ls_renxian.n_P - 1);

	//			vec3 p_dl_start = DL_part.Data[0].G_P;
	//			mat33 G_SYS_SL_start = DL_part.Data[0].G_SYS_SL;
	//			mat33 ls_sys_sl = DL_part.Data[0].G_SYS_SL * tcRotX(3, ang_hen_tui); //横向退刀
	//			vec start_v = ls_sys_sl * (-tcY(3));
	//			start_v(2) = 0.0;
	//			start_v = normalise(start_v);

	//			double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用起始
	//			dis_p = 0.04;
	//			int count_yan = dis_extend / dis_p;

	//			for (int i = 1; i <= count_yan; i++)
	//			{
	//				DL_P ans_start;
	//				ans_start.G_P = p_dl_start + (start_v)*i * dis_p;
	//				ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
	//				ans_start.G_SYS_SL = G_SYS_SL_start;
	//				ans_start.point_type = 2;

	//				DL_part.Data.insert(DL_part.Data.begin(), ans_start);

	//				//DL_P ans_end;
	//				//ans_end.G_P = p_dl_end + (end_v)*i * dis_p; //终点刃线切向 11.28
	//				//ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
	//				//ans_end.G_SYS_SL = G_SYS_SL_end;
	//				//ans_end.point_type = 0;

	//				//DL_part.Data.insert(DL_part.Data.end(), ans_end);
	//			}
	//		}

	//		//4.6、刀路点反向，只改点的顺序
	//		reverse(DL_part.Data.begin(), DL_part.Data.end());

	//		//5、单刃进退刀
	//		XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

	//		//6、组合完整刀路
	//		for (int i = 0; i < DL_part.Data.size(); i++)
	//		{
	//			DL_base.Data.push_back(DL_part.Data[i]);
	//		}
	//	}
	//}
}


void Miller_GX_PD_DCC::cal_leadface(Cal_RenXian& in_rx, mat& data_qdm)
{
	//螺旋槽前刀面：刃线法坐标系绕x转 90-前角
//根据前角类型：旋转不同的刃线坐标系--11.7
	int p_num = in_rx.get_p_num();
	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat ls_sys = eye(3, 3);

		ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_n1));


		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}

void Miller_GX_PD_DCC::cal_leadface_caodi(Cal_RenXian& in_rx, mat& data_qdm)
{
	//前刀面：刃线法坐标系绕x转 90-前角
	int p_num = in_rx.get_p_num();
	double delta_ang = data_canshu.ang_n1 / p_num;

	//求得槽终点的方向向量，起点加方向长度
	mat end_sys = in_rx.nSYS(p_num - 1);
	vec3 end_hen_p = in_rx.P(p_num - 1);
	double cao_h = in_rx.Lenth_of_RenXian() * tan(tcRadians(data_canshu.ang_caoding));
	vec3 cao_t = end_sys * tcRotX(3, (90.0 - data_canshu.ang_n1)) * tcY(3);
	vec3 cao_end_p = end_hen_p + cao_t * cao_h;

	vec3 start_p = in_rx.P(0);
	vec3 ans_fangxiang = normalise(cao_end_p - start_p);

	double cao_len = in_rx.Lenth_of_RenXian() / cos(tcRadians(data_canshu.ang_caoding));
	double delta_len = cao_len / p_num;

	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = start_p + ans_fangxiang * i * delta_len;
		mat ls_test = in_rx.nSYS(i);
		mat ans_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - i * delta_ang));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ans_sys.col(0)(0) ,ans_sys.col(0)(1) ,ans_sys.col(0)(2),
		ans_sys.col(1)(0) ,ans_sys.col(1)(1) ,ans_sys.col(1)(2) ,
		ans_sys.col(2)(0) ,ans_sys.col(2)(1) ,ans_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}

void Miller_GX_PD_DCC::cal_sl_weiyi_ang(double in_D_gj, double in_ang_caoding, double in_D_sl, double& out_ang_ans)
{
	double ls = sin(in_ang_caoding);
	double theta = asin(sqrt((in_D_gj * sin(in_ang_caoding)) / in_D_sl));
	out_ang_ans = 90.0 - in_ang_caoding - 2 * theta;
}

Miller_GX_PD_DCC::Miller_GX_PD_DCC()
{
	gx_type = 8;
}

Miller_GX_PD_DCC::~Miller_GX_PD_DCC()
{
}

Miller_GX_PD_DCC::Miller_GX_PD_DCC(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_DCC::Miller_GX_PD_DCC(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_DCC::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;

}

void Miller_GX_PD_DCC::Load(int in_pos)
{
	//恢复参数
	CanShu_PD_DCC  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_DCC::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_PD_DHDM_1::get_canshu(CanShu_PD_DHDM_1& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_DHDM_1::set_canshu(CanShu_PD_DHDM_1& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_DHDM_1(ptr);

}

void Miller_GX_PD_DHDM_1::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_dhdm_1); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
	//cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}



void Miller_GX_PD_DHDM_1::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_DHDM_1::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本横刃线和点数量
			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hen_hdm_1(ls_ren_pos, data_hdm);

			double cur_qie = data_canshu.angle_qiexue;
			double cur_wy = data_canshu.angle_wy_luo;

			//2.5 获取刃线，用于修正切削角
			int p_all_count = data_hdm.n_cols;
			for (int i = 0; i < p_all_count; i++)
			{
				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
		   //用刀路点的起始两点切向延长指定距离, 
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				dis_p = 0.04;
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_HDM_start * tcX(3) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //2.18 砂轮不等后刀面坐标系，有位移切削角度
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				//double dis_end_extend = data_canshu.dis_to_center;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_end;
				   // ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				   // ans_end.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_end.G_SYS_SL = G_SYS_HDM_start;
				   // ans_end.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//4.6、刀路点反向，只改点的顺序
			reverse(DL_part.Data.begin(), DL_part.Data.end());

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}


Miller_GX_PD_DHDM_1::Miller_GX_PD_DHDM_1()
{
	gx_type = 9;
}

Miller_GX_PD_DHDM_1::~Miller_GX_PD_DHDM_1()
{
}

Miller_GX_PD_DHDM_1::Miller_GX_PD_DHDM_1(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_DHDM_1::Miller_GX_PD_DHDM_1(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_DHDM_1::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_DHDM_1::Load(int in_pos)
{	 //恢复参数
	CanShu_PD_DHDM_1  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_DHDM_1::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_PD_DHDM_2::get_canshu(CanShu_PD_DHDM_2& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_DHDM_2::set_canshu(CanShu_PD_DHDM_2& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_DHDM_2(ptr);

}

void Miller_GX_PD_DHDM_2::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_dhdm_2); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}



void Miller_GX_PD_DHDM_2::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_DHDM_2::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本横刃线和点数量
			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hen_hdm_2(ls_ren_pos, data_hdm);

			double cur_qie = data_canshu.angle_qiexue;
			double cur_wy = data_canshu.angle_wy_luo;

			//2.5 获取刃线，用于修正切削角
			int p_all_count = data_hdm.n_cols;
			for (int i = 0; i < p_all_count; i++)
			{
				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_HDM_start * tcX(3) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				//double dis_end_extend = data_canshu.dis_to_center;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_end;
				   // ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				   // ans_end.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_end.G_SYS_SL = G_SYS_HDM_start;
				   // ans_end.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//4.6、刀路点反向，只改点的顺序
			reverse(DL_part.Data.begin(), DL_part.Data.end());

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}


Miller_GX_PD_DHDM_2::Miller_GX_PD_DHDM_2()
{
	gx_type = 10;
}

Miller_GX_PD_DHDM_2::~Miller_GX_PD_DHDM_2()
{
}

Miller_GX_PD_DHDM_2::Miller_GX_PD_DHDM_2(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_DHDM_2::Miller_GX_PD_DHDM_2(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_DHDM_2::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_DHDM_2::Load(int in_pos)
{
	//恢复参数
	CanShu_PD_DHDM_2  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_DHDM_2::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_PD_DHDM_3::get_canshu(CanShu_PD_DHDM_3& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_DHDM_3::set_canshu(CanShu_PD_DHDM_3& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_DHDM_3(ptr);

}

void Miller_GX_PD_DHDM_3::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_dhdm_3); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
	//cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_PD_DHDM_3::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_DHDM_3::cal_base_DL()
{
}

Miller_GX_PD_DHDM_3::Miller_GX_PD_DHDM_3()
{
	gx_type = 11;
}

Miller_GX_PD_DHDM_3::~Miller_GX_PD_DHDM_3()
{
}

Miller_GX_PD_DHDM_3::Miller_GX_PD_DHDM_3(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_DHDM_3::Miller_GX_PD_DHDM_3(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_DHDM_3::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_DHDM_3::Load(int in_pos)
{//恢复参数
	CanShu_PD_DHDM_3  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_DHDM_3::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_PD_LXC::get_canshu(CanShu_PD_LXC& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_LXC::set_canshu(CanShu_PD_LXC& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_LXC(ptr);

}

void Miller_GX_PD_LXC::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_lxc); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
   // cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}


void Miller_GX_PD_LXC::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_LXC::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			self_Dao->get_renxian_of_luo_cao(ls_ren_pos, get_renxian);
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//2、生成前刀面数据
			mat data_qdm;
			cal_leadface(ls_renxian, data_canshu.type, data_qdm);

			int p_count = data_qdm.n_cols;

			{
				//3、准备计算砂轮位姿的数据
				//mat p_data(3, p_count, fill::zeros);
				//mat n_data(3, p_count, fill::zeros);
				//mat t_data(3, p_count, fill::zeros);
				//p_data = data_qdm.submat(0, 0, 2, p_count - 1);
				//n_data = data_qdm.submat(9, 0, 11, p_count - 1);
				//t_data = data_qdm.submat(3, 0, 5, p_count - 1);
				////3.1、芯厚面数据
				//int p_count2 = p_count + (4 * shalun_canshu.D) / 0.1;
				//mat px_data(3, p_count2, fill::zeros);
				//mat nx_data(3, p_count2, fill::zeros);
				//cal_xinhoumian(px_data, nx_data, shalun_canshu.D);

				//mat33 sys_xh = eye(3, 3);
				//vec3 p_xh = { 0.0,0.0, 0.0 };

				////test
				//mat ans_p = p_data.t();
				//ans_p.save(R"(test_luo-1.18.txt)", raw_ascii);
				//mat ans_p2 = px_data.t();
				//ans_p2.save(R"(test_luoxinhou-1.18.txt)", raw_ascii);

				//xt_XiDao_HZ ls_cal_dl;
				//ls_cal_dl.Set_QDM(p_data, n_data, t_data); //++切向
				//ls_cal_dl.Set_XHM(px_data, nx_data);
				//ls_cal_dl.Set_SYS_XH(p_xh, sys_xh);
				//ls_cal_dl.Set_SL_Cutting(shalun_canshu.D / 2.0, shalun_canshu.R, data_canshu.angle_qiexue);

				//bool is_input = ls_cal_dl.Check_Input();

				////4、砂轮结果获取 = 工件坐标系下的刀路点
				//vec3 ls_p = { 0.0,0.0,0.0 };
				//mat33 ls_sys = eye(3, 3);
				//bool has_jie = ls_cal_dl.Get_First(ls_p, ls_sys);
				//if (has_jie)
				//{
				   // for (int i = 1; i < p_count - 1; i++)
				   // {
				   //	 ls_cal_dl.Get_Next(ls_p, ls_sys);
				   //	 //计算的结果为，抽象的回转面与圆角的回转轴中心，通过砂轮安装状态才能确定出位姿
				   //	 //根据砂轮的内外磨，确定z轴是否反向

				   //	 //Z轴：砂轮轴朝向磨削面法向
				   //	 //X轴：轴心指向磨削点进行修改-不旋转z 9.13
				   //	 //右手系
				   //	 //ls_sys = ls_sys * tcRotZ(3, 180.0);

				   //	 //切换砂轮内外侧磨削 8.7 mark 默认内侧 9.9 
				   //	 if (in_or_out == 1)
				   //	 {
				   //		 ls_sys = ls_sys * tcRotX(3, 180.0);
				   //	 }
				   //	 else
				   //	 {
				   //		 ls_sys = ls_sys * tcRotX(3, 0.0);
				   //	 }

				   //	 mat33 G_SYS_SL = eye(3, 3);
				   //	 G_SYS_SL.col(0) = ls_sys.col(0);
				   //	 G_SYS_SL.col(1) = ls_sys.col(1);
				   //	 G_SYS_SL.col(2) = ls_sys.col(2);

				   //	 vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1
				   //	 //转为后刀面坐标系的定义，不完全准确，用于进退刀方向的计算-11.12
				   //	 // X_HDM = -X_QDM, Y_HDM = -Y_QDM, Z_HDM = Z_QDM,

				   //	 mat33 G_SYS_QDM = {
				   //		 {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   //		 {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   //		 {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				   //	 //不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				   //	 DL_P ans_DL_P;
				   //	 ans_DL_P.G_P = p_data.col(i);
				   //	 ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				   //	 ans_DL_P.G_SYS_SL = G_SYS_SL;

				   //	 DL_part.Data.push_back(ans_DL_P);
				   // }
				//}
				//else
				//{
				   // return;
				//}
			}

			//计算刀路点 3.25
#pragma region MyRegion
			vec3 start_qdm_p = data_qdm.submat(0, 0, 2, 0);
			vec start_sub = data_qdm.submat(3, 0, 11, 0); //取出为9*1
			mat33 G_SYS_QDM = {
				{start_sub(0),  start_sub(3), start_sub(6)},
				{start_sub(1),  start_sub(4), start_sub(7)},
				{start_sub(2),  start_sub(5), start_sub(8)}, };
			//初始砂轮位姿
			mat33 G_SYS_SL = G_SYS_QDM;
			G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度

			double xinhou_R = self_Dao->get_gg_canshu_D_qiu() * data_canshu.percent_r;
			double ans_zhuan = Cal_LXC_SL_SYS_by_XH(start_qdm_p, G_SYS_SL, shalun_canshu.D / 2.0, xinhou_R);

			G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_qdm_p = data_qdm.submat(0, i, 2, i);
				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
				   {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_QDM;
				G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

				//切换砂轮内外侧磨削 
				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				//不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_qdm_p;
				ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}
#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				double dis_start_extend = data_canshu.extend_start;

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_QDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_QDM_start * (-tcX(3)) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.extend_end;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_QDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_QDM_start * (tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}

			}

			//5、螺旋槽单刃进退刀--11.4
			XiDao_LXC_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}


void Miller_GX_PD_LXC::cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm)
{
	//螺旋槽前刀面：刃线法坐标系绕x转 90-前角
   //根据前角类型：旋转不同的刃线坐标系--11.7
	int p_num = in_rx.get_p_num();
	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat ls_sys = eye(3, 3);
		if (ang_type == 0)
		{
			ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_n1));
		}
		else
		{
			//test
			mat test_mat = in_rx.hSYS(i);
			//先Z转螺旋角，在X转修正后的前角2.20
			double ls_ang_luo = self_Dao->get_gg_canshu_luo();
			double cal_ang_qian = data_canshu.ang_d / cos(tcRadians(ls_ang_luo));
			ls_sys = in_rx.hSYS(i) * tcRotZ(3, ls_ang_luo) * tcRotX(3, (90.0 - data_canshu.ang_d));
		}

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}

}

void Miller_GX_PD_LXC::cal_xinhoumian(mat& px, mat& nx, double sl_D)
{
	//跳转错误
	int abc = 1 + 1;

	int p_count = px.n_cols;
	vec3 start_p = { self_Dao->get_gg_canshu_D_qiu() / 2.0, 0.0, 0.0 };
	// vec3 start_end = { self_Dao->get_gg_canshu_D_bing()  , 0.0, self_Dao->get_gg_canshu_len_ren() };
	double ls_hight = self_Dao->get_gg_canshu_len_ren() * tan(tcRadians(self_Dao->get_gg_canshu_Zhui()));
	vec3 start_end = { start_p(0) + ls_hight, 0.0,  self_Dao->get_gg_canshu_len_ren() };
	start_p(0) = start_p(0) * data_canshu.percent_r;
	start_end(0) = start_end(0) * data_canshu.percent_r;

	//double delta = 1.0 / (p_count * 1.0);
	double delta = 0.1;

	vec3 start_p_front = start_p;
	start_p_front(2) = start_p_front(2) - sl_D;

	vec3 start_p_back = start_end;
	start_p_back(2) = start_p_back(2) + sl_D;

	//3段线组成
	int count1 = (sl_D) / delta;
	int count2 = count1 + p_count + (sl_D) / delta;
	px.resize(3, 0);
	px.insert_cols(0, count2);
	nx.resize(3, 0);
	nx.insert_cols(0, count2);
	//前延长
	vec3 v_p_end = normalise(start_p - start_p_front);
	for (int i = 0; i < count1; i++)
	{
		vec3 ans_p = start_p_front + i * delta * v_p_end;
		px.col(i) = ans_p;
		//切向转90度
		if (i == 0)
		{
		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(0) = nx.col(1);

	//中间
	v_p_end = normalise(start_end - start_p);
	int index = 0;
	for (int i = count1; i < count1 + p_count; i++)
	{
		vec3 ans_p = start_p + index * delta * v_p_end;
		index++;
		px.col(i) = ans_p;
		//切向转90度
		if (i == count1)
		{

		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(count1) = nx.col(count1 + 1);
	//后延长
	//v_p_end = normalise(start_p_back - start_end);
	//int index2 = 0;
	//for (int i = count1 + p_count; i < count2; i++)
	//{
	   // vec3 ans_p = start_end + index2 * delta * v_p_end;
	   // index2++;
	   // px.col(i) = ans_p;
	   // //切向转90度
	   // if (i == count1 + p_count)
	   // {

	   // }
	   // else
	   // {
	   //	 vec3 ans_ls = normalise(ans_p - px.col(i - 1));
	   //	 vec3 ans_n = tcRotY(3, 90) * ans_ls;
	   //	 nx.col(i) = ans_n;
	   // }
	//}
	//nx.col(count1 + p_count) = nx.col(count1 + p_count + 1);
}

void Miller_GX_PD_LXC::gen_leadface_by_ren(Cal_RenXian& in_line)
{
}

Miller_GX_PD_LXC::Miller_GX_PD_LXC()
{
	gx_type = 12;
}

Miller_GX_PD_LXC::~Miller_GX_PD_LXC()
{
}

Miller_GX_PD_LXC::Miller_GX_PD_LXC(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_LXC::Miller_GX_PD_LXC(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_LXC::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_LXC::Load(int in_pos)
{//恢复参数
	CanShu_PD_LXC  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_LXC::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_PD_HDM_1::get_canshu(CanShu_PD_HDM_1& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_HDM_1::set_canshu(CanShu_PD_HDM_1& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_HDM_1(ptr);

}

void Miller_GX_PD_HDM_1::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_hdm_1); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
   // cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_PD_HDM_1::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_HDM_1::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本横刃线和点数量
			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_luo_hdm_1(ls_ren_pos, data_hdm);

			double cur_qie = data_canshu.angle_qiexue_luo;
			double cur_wy = data_canshu.angle_wy_luo;

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_hdm1);

			int p_all_count = data_hdm.n_cols;
			for (int i = 0; i < p_all_count; i++)
			{
				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;

				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				{
					vec3 ren_n, ren_t;
					double theta = 0.0;
					double ang_xiu = 0.0;

					ren_n = ren_hdm1.hY(i); //平面法向
					ren_t = ren_hdm1.hX(i);

					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					ang_xiu = tcDegree(acos(theta));
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				//double dis_start_extend = data_canshu.dis_start_extend;
				//vec3 p_dl_start = DL_part.Data[0].G_P;
				//mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;

				//double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				//int count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_start;
				   // ans_start.G_P = p_dl_start + G_SYS_HDM_start * tcX(3) * i * dis_p;
				   // ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_start.G_SYS_SL = G_SYS_HDM_start;
				   // ans_start.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				//}

				//double dis_end_extend = data_canshu.dis_end_extend;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_end;
				   // ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				   // ans_end.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_end.G_SYS_SL = G_SYS_HDM_start;
				   // ans_end.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

Miller_GX_PD_HDM_1::Miller_GX_PD_HDM_1()
{
	gx_type = 13;
}

Miller_GX_PD_HDM_1::~Miller_GX_PD_HDM_1()
{
}

Miller_GX_PD_HDM_1::Miller_GX_PD_HDM_1(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_HDM_1::Miller_GX_PD_HDM_1(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_HDM_1::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_HDM_1::Load(int in_pos)
{//恢复参数
	CanShu_PD_HDM_1  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_HDM_1::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_PD_HDM_2::get_canshu(CanShu_PD_HDM_2& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_HDM_2::set_canshu(CanShu_PD_HDM_2& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_HDM_2(ptr);

}

void Miller_GX_PD_HDM_2::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_hdm_2); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
   // cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}


void Miller_GX_PD_HDM_2::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_HDM_2::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本横刃线和点数量
			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_luo_hdm_2(ls_ren_pos, data_hdm);

			double cur_qie = data_canshu.angle_qiexue_luo;
			double cur_wy = data_canshu.angle_wy_luo;

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_hdm1);

			int p_all_count = data_hdm.n_cols;
			for (int i = 0; i < p_all_count; i++)
			{
				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;

				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				{
					vec3 ren_n, ren_t;
					double theta = 0.0;
					double ang_xiu = 0.0;

					ren_n = ren_hdm1.hY(i); //平面法向
					ren_t = ren_hdm1.hX(i);

					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					ang_xiu = tcDegree(acos(theta));
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
		   //用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				//double dis_start_extend = data_canshu.dis_start_extend;
				//vec3 p_dl_start = DL_part.Data[0].G_P;
				//mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;

				//double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				//int count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_start;
				   // ans_start.G_P = p_dl_start + G_SYS_HDM_start * tcX(3) * i * dis_p;
				   // ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_start.G_SYS_SL = G_SYS_HDM_start;
				   // ans_start.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				//}

				//double dis_end_extend = data_canshu.dis_end_extend;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				   // DL_P ans_end;
				   // ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				   // ans_end.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				   // ans_end.G_SYS_SL = G_SYS_HDM_start;
				   // ans_end.point_type = 0;

				   // DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}


Miller_GX_PD_HDM_2::Miller_GX_PD_HDM_2()
{
	gx_type = 14;
}

Miller_GX_PD_HDM_2::~Miller_GX_PD_HDM_2()
{
}

Miller_GX_PD_HDM_2::Miller_GX_PD_HDM_2(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_HDM_2::Miller_GX_PD_HDM_2(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_HDM_2::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_HDM_2::Load(int in_pos)
{
	//恢复参数
	CanShu_PD_HDM_2  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_HDM_2::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}


void Miller_GX_PD_HDM_3::get_canshu(CanShu_PD_HDM_3& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_HDM_3::set_canshu(CanShu_PD_HDM_3& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_HDM_3(ptr);

}

void Miller_GX_PD_HDM_3::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_hdm_3); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}


void Miller_GX_PD_HDM_3::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_HDM_3::cal_base_DL()
{
}

Miller_GX_PD_HDM_3::Miller_GX_PD_HDM_3()
{
	gx_type = 15;
}

Miller_GX_PD_HDM_3::~Miller_GX_PD_HDM_3()
{
}

Miller_GX_PD_HDM_3::Miller_GX_PD_HDM_3(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_HDM_3::Miller_GX_PD_HDM_3(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_HDM_3::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_HDM_3::Load(int in_pos)
{
	//恢复参数
	CanShu_PD_HDM_3  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_HDM_3::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_PD_DaoTiJianXi::get_canshu(CanShu_PD_DaoTiJianXi& ans)
{
	ans = data_canshu;
}

void Miller_GX_PD_DaoTiJianXi::set_canshu(CanShu_PD_DaoTiJianXi& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_PD_DaoTiJianXi(ptr);

}

void Miller_GX_PD_DaoTiJianXi::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_pd_dt_jx); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_PD_DaoTiJianXi::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_PD_DaoTiJianXi::cal_base_DL()
{

}

Miller_GX_PD_DaoTiJianXi::Miller_GX_PD_DaoTiJianXi()
{
	gx_type = 16;
}

Miller_GX_PD_DaoTiJianXi::~Miller_GX_PD_DaoTiJianXi()
{
}

Miller_GX_PD_DaoTiJianXi::Miller_GX_PD_DaoTiJianXi(Miller_D_PD* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_PD_DaoTiJianXi::Miller_GX_PD_DaoTiJianXi(int in_name)
{
	name = in_name;
}

int Miller_GX_PD_DaoTiJianXi::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_PD_DaoTiJianXi::Load(int in_pos)
{
	//恢复参数
	CanShu_PD_DaoTiJianXi  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_PD_DaoTiJianXi::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_QDM_R::get_canshu(CanShu_R_QDM_R& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_QDM_R::set_canshu(CanShu_R_QDM_R& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_QDM_R(ptr);

}

void Miller_GX_R_QDM_R::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_qdm); //改为public
	/*cal_renxian(Cal_RenXian& ans_rx);
	cal_leadface(Cal_RenXian& ans_rx);*/
	self_xingcan = &ptr;
}


void Miller_GX_R_QDM_R::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);
	//
}

void Miller_GX_R_QDM_R::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			self_Dao->get_renxian_of_rrr(ls_ren_pos, get_renxian);
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//2、生成前刀面数据
			mat data_qdm;
			cal_leadface(ls_renxian, data_canshu.type, data_qdm);
			int p_count = data_qdm.n_cols;

			mat p_data(3, p_count, fill::zeros);
			p_data = data_qdm.submat(0, 0, 2, p_count - 1);
			mat test_p2 = p_data.t();
			test_p2.save(R"(test_rrr_fxc_3.31.txt)", raw_ascii);

			//计算刀路点 3.25
#pragma region MyRegion
			vec3 start_qdm_p = data_qdm.submat(0, 0, 2, 0);
			vec start_sub = data_qdm.submat(3, 0, 11, 0); //取出为9*1
			mat33 G_SYS_QDM = {
				{start_sub(0),  start_sub(3), start_sub(6)},
				{start_sub(1),  start_sub(4), start_sub(7)},
				{start_sub(2),  start_sub(5), start_sub(8)}, };
			//初始砂轮位姿
			mat33 G_SYS_SL = G_SYS_QDM;
			G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度

			double ans_zhuan = 1.0;

			G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_qdm_p = data_qdm.submat(0, i, 2, i);
				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
				   {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_QDM; //按开槽计算位姿，将刀路点反向3.31
				G_SYS_SL = G_SYS_SL * tcRotY(3, -data_canshu.angle_qiexue);//转切削角度
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, ans_zhuan); //与开槽相反

				//切换砂轮内外侧磨削 
				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				//不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_qdm_p;
				ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}
#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				//double dis_start_extend = data_canshu.extend_start;

				//vec3 p_dl_start = DL_part.Data[0].G_P;
				//mat33 G_SYS_QDM_start = DL_part.Data[0].G_SYS_HDM;

				//double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				//int count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				//	DL_P ans_start;
				//	ans_start.G_P = p_dl_start + G_SYS_QDM_start * (-tcX(3)) * i * dis_p;
				//	ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
				//	ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
				//	ans_start.point_type = 0;

				//	DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				//}

				//double dis_end_extend = data_canshu.extend_end;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_QDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				//	DL_P ans_end;
				//	ans_end.G_P = p_dl_end + G_SYS_QDM_start * (tcX(3)) * i * dis_p;
				//	ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
				//	ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
				//	ans_end.point_type = 0;

				//	DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//4.6、刀路点反向，只改点的顺序
			reverse(DL_part.Data.begin(), DL_part.Data.end());

			//5、螺旋槽单刃进退刀--11.4
			XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_R_QDM_R::cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm)
{
	//球头前刀面：刃线法坐标系绕x转 90-前角
	int p_num = in_rx.get_p_num();

	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat test_sys = in_rx.nSYS(i);
		double cur_ang = data_canshu.ang_n1;
		mat ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - cur_ang));
		//vec3 ls_n = -ls_sys.col(1);
		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}

void Miller_GX_R_QDM_R::gen_leadface_by_ren(Cal_RenXian& in_line)
{
}

Miller_GX_R_QDM_R::Miller_GX_R_QDM_R()
{
	gx_type = 17;
}

Miller_GX_R_QDM_R::~Miller_GX_R_QDM_R()
{
}

Miller_GX_R_QDM_R::Miller_GX_R_QDM_R(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_QDM_R::Miller_GX_R_QDM_R(int in_name)
{
	name = in_name;
}

int Miller_GX_R_QDM_R::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_QDM_R::Load(int in_pos)
{
	//恢复参数
	CanShu_R_QDM_R  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_QDM_R::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_HDM_1::get_canshu(CanShu_R_HDM_1& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_HDM_1::set_canshu(CanShu_R_HDM_1& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_HDM_1(ptr);

}

void Miller_GX_R_HDM_1::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_hdm_1); //改为public
	/*cal_renxian(Cal_RenXian& ans_rx);
	cal_leadface(Cal_RenXian& ans_rx);*/
	self_xingcan = &ptr;
}

void Miller_GX_R_HDM_1::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_HDM_1::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线和螺旋线的点数量
			//int p_count_qiu = self_Dao->get_renxian_of_hen(ls_ren_pos);
			//int p_count_luo = self_Dao->get_renxian_of_rrr_count_p(ls_ren_pos);

			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_1(ls_ren_pos, data_hdm);

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hen;
			self_Dao->get_renxian_of_hen(ls_ren_pos, ren_hen);
			Cal_RenXian ren_rrr;
			self_Dao->get_renxian_of_rrr(ls_ren_pos, ren_rrr);
			Cal_RenXian ren_luo;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_luo);

			int count_p_hen = ren_hen.get_p_num();
			int count_p_rrr = ren_rrr.get_p_num();
			int count_p_hdm = data_hdm.n_cols;

			double p_delta_dis = ren_hen.Distance_of_Point;
			int count_p_cut = self_Dao->get_gg_canshu_R_qiu() / p_delta_dis;
			count_p_hen = count_p_hen - count_p_cut;

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(count_p_hen, count_p_rrr, count_p_hdm, ls_qie, ls_wy);

			int p_all_count = count_p_hdm;
			for (int i = 0; i < p_all_count; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 180);

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			//角度延长过中刀路点
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				//dis_start_extend = 0.1; //X指向回转轴且偏下-1.13,转30度
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;
				vec3 t_yan = G_SYS_HDM_start * tcRotZ(3, 0.0) * tcX(3); //转角大不能形成交线//1.16
				t_yan(2) = -t_yan(2);
				t_yan = normalise(t_yan);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + t_yan * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //横刃砂轮以0度后角延长1.16-后角5°横刃在球面上0.00098
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				//double dis_end_extend = data_canshu.dis_end_extend;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				//	DL_P ans_end;
				//	ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				//	ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
				//	ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
				//	ans_end.point_type = 0;

				//	DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_R_HDM_1::cal_cha_ang(int p_count_hen, int p_count_rrr, int p_count_hdm, vector<double>& ans_qie, vector<double>& ans_wy)
{
	//横刃切削过度到圆角起点，圆角起点过度到柱面，后续不变 3.31
	double delta_ang_qie = (data_canshu.angle_qx_hen - data_canshu.angle_qx_rrr) / p_count_hen;
	double delta_ang_wy = (data_canshu.angle_wy_hen - data_canshu.angle_wy_rrr) / p_count_hen;
	for (int i = 0; i < p_count_hen; i++)
	{
		double cur_qie = data_canshu.angle_qx_hen - i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_hen - i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	delta_ang_qie = (data_canshu.angle_qx_rrr - data_canshu.angle_qx_luo) / p_count_rrr;
	delta_ang_wy = (data_canshu.angle_wy_rrr - data_canshu.angle_wy_luo) / p_count_rrr;
	for (int i = 0; i < p_count_rrr; i++)
	{
		double cur_qie = data_canshu.angle_qx_rrr - i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_rrr - i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	delta_ang_qie = data_canshu.angle_qx_luo;
	delta_ang_wy = data_canshu.angle_wy_luo;
	for (int i = ans_qie.size(); i < p_count_hdm; i++)
	{
		double cur_qie = delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}
}

Miller_GX_R_HDM_1::Miller_GX_R_HDM_1()
{
	gx_type = 18;
}

Miller_GX_R_HDM_1::~Miller_GX_R_HDM_1()
{
}

Miller_GX_R_HDM_1::Miller_GX_R_HDM_1(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_HDM_1::Miller_GX_R_HDM_1(int in_name)
{
	name = in_name;
}

int Miller_GX_R_HDM_1::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_HDM_1::Load(int in_pos)
{
	//恢复参数
	CanShu_R_HDM_1  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_HDM_1::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_HDM_2::get_canshu(CanShu_R_HDM_2& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_HDM_2::set_canshu(CanShu_R_HDM_2& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_HDM_2(ptr);

}

void Miller_GX_R_HDM_2::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_hdm_2); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	 //cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_HDM_2::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_HDM_2::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线和螺旋线的点数量
			//int p_count_qiu = self_Dao->get_renxian_of_hen(ls_ren_pos);
			//int p_count_luo = self_Dao->get_renxian_of_rrr_count_p(ls_ren_pos);

			//2、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_2(ls_ren_pos, data_hdm);

			//2.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hen;
			self_Dao->get_renxian_of_hen(ls_ren_pos, ren_hen);
			Cal_RenXian ren_rrr;
			self_Dao->get_renxian_of_rrr(ls_ren_pos, ren_rrr);
			Cal_RenXian ren_luo;
			self_Dao->get_renxian_of_luo(ls_ren_pos, ren_luo);

			int count_p_hen = ren_hen.get_p_num();
			int count_p_rrr = ren_rrr.get_p_num();
			int count_p_hdm = data_hdm.n_cols;

			double p_delta_dis = ren_hen.Distance_of_Point;
			int count_p_cut = self_Dao->get_gg_canshu_R_qiu() / p_delta_dis;
			count_p_hen = count_p_hen - count_p_cut;

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(count_p_hen, count_p_rrr, count_p_hdm, ls_qie, ls_wy);

			int p_all_count = count_p_hdm;
			for (int i = 0; i < p_all_count; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 180);

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			//角度延长过中刀路点
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				//dis_start_extend = 0.1; //X指向回转轴且偏下-1.13,转30度
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;
				vec3 t_yan = G_SYS_HDM_start * tcRotZ(3, 0.0) * tcX(3); //转角大不能形成交线//1.16
				t_yan(2) = -t_yan(2);
				t_yan = normalise(t_yan);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + t_yan * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //横刃砂轮以0度后角延长1.16-后角5°横刃在球面上0.00098
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				//double dis_end_extend = data_canshu.dis_end_extend;
				//vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				//mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				//dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				//count_yan = dis_start_extend / dis_p;

				//for (int i = 1; i <= count_yan; i++)
				//{
				//	DL_P ans_end;
				//	ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
				//	ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
				//	ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
				//	ans_end.point_type = 0;

				//	DL_part.Data.insert(DL_part.Data.end(), ans_end);
				//}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_R_HDM_2::cal_cha_ang(int p_count_hen, int p_count_rrr, int p_count_hdm, vector<double>& ans_qie, vector<double>& ans_wy)
{//横刃切削过度到圆角起点，圆角起点过度到柱面，后续不变 3.31
	double delta_ang_qie = (data_canshu.angle_qx_hen - data_canshu.angle_qx_rrr) / p_count_hen;
	double delta_ang_wy = (data_canshu.angle_wy_hen - data_canshu.angle_wy_rrr) / p_count_hen;
	for (int i = 0; i < p_count_hen; i++)
	{
		double cur_qie = data_canshu.angle_qx_hen - i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_hen - i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	delta_ang_qie = (data_canshu.angle_qx_rrr - data_canshu.angle_qx_luo) / p_count_rrr;
	delta_ang_wy = (data_canshu.angle_wy_rrr - data_canshu.angle_wy_luo) / p_count_rrr;
	for (int i = 0; i < p_count_rrr; i++)
	{
		double cur_qie = data_canshu.angle_qx_rrr - i * delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = data_canshu.angle_wy_rrr - i * delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}

	delta_ang_qie = data_canshu.angle_qx_luo;
	delta_ang_wy = data_canshu.angle_wy_luo;
	for (int i = ans_qie.size(); i < p_count_hdm; i++)
	{
		double cur_qie = delta_ang_qie;
		ans_qie.push_back(cur_qie);

		double cur_wy = delta_ang_wy;
		ans_wy.push_back(cur_wy);
	}
}

Miller_GX_R_HDM_2::Miller_GX_R_HDM_2()
{
	gx_type = 19;
}

Miller_GX_R_HDM_2::~Miller_GX_R_HDM_2()
{
}

Miller_GX_R_HDM_2::Miller_GX_R_HDM_2(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_HDM_2::Miller_GX_R_HDM_2(int in_name)
{
	name = in_name;
}

int Miller_GX_R_HDM_2::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_HDM_2::Load(int in_pos)
{
	//恢复参数
	CanShu_R_HDM_2  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_HDM_2::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_HDM_3::get_canshu(CanShu_R_HDM_3& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_HDM_3::set_canshu(CanShu_R_HDM_3& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_HDM_3(ptr);

}

void Miller_GX_R_HDM_3::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_hdm_3); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_HDM_3::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_HDM_3::cal_base_DL()
{
}

Miller_GX_R_HDM_3::Miller_GX_R_HDM_3()
{
	gx_type = 20;
}

Miller_GX_R_HDM_3::~Miller_GX_R_HDM_3()
{
}

Miller_GX_R_HDM_3::Miller_GX_R_HDM_3(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_HDM_3::Miller_GX_R_HDM_3(int in_name)
{
	name = in_name;
}

int Miller_GX_R_HDM_3::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_HDM_3::Load(int in_pos)
{
	//恢复参数
	CanShu_R_HDM_3  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_HDM_3::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_LXC::get_canshu(CanShu_R_LXC& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_LXC::set_canshu(CanShu_R_LXC& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_LXC(ptr);

}

void Miller_GX_R_LXC::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_lxc); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
	//cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_LXC::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_LXC::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			self_Dao->get_renxian_of_luo_cao(ls_ren_pos, get_renxian);
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//2、生成前刀面数据
			mat data_qdm;
			cal_leadface(ls_renxian, data_canshu.type, data_qdm);

			int p_count = data_qdm.n_cols;

			//计算刀路点 3.25
#pragma region MyRegion
			vec3 start_qdm_p = data_qdm.submat(0, 0, 2, 0);
			vec start_sub = data_qdm.submat(3, 0, 11, 0); //取出为9*1
			mat33 G_SYS_QDM = {
				{start_sub(0),  start_sub(3), start_sub(6)},
				{start_sub(1),  start_sub(4), start_sub(7)},
				{start_sub(2),  start_sub(5), start_sub(8)}, };
			//初始砂轮位姿
			mat33 G_SYS_SL = G_SYS_QDM;
			G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度

			double xinhou_R = self_Dao->get_gg_canshu_D_qiu() * data_canshu.percent_r;
			double ans_zhuan = Cal_LXC_SL_SYS_by_XH(start_qdm_p, G_SYS_SL, shalun_canshu.D / 2.0, xinhou_R);

			G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_qdm_p = data_qdm.submat(0, i, 2, i);
				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
				   {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_QDM;
				G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

				//切换砂轮内外侧磨削 
				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				//不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_qdm_p;
				ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}
#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				double dis_start_extend = data_canshu.extend_start;

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_QDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_QDM_start * (-tcX(3)) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.extend_end;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_QDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_QDM_start * (tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}

			}

			//5、螺旋槽单刃进退刀--11.4
			XiDao_LXC_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_R_LXC::cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm)
{
	//螺旋槽前刀面：刃线法坐标系绕x转 90-前角
   //根据前角类型：旋转不同的刃线坐标系--11.7
	int p_num = in_rx.get_p_num();
	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat ls_sys = eye(3, 3);
		if (ang_type == 0)
		{
			ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_n1));
		}
		else
		{
			//test
			mat test_mat = in_rx.hSYS(i);
			//先Z转螺旋角，在X转修正后的前角2.20
			double ls_ang_luo = self_Dao->get_gg_canshu_luo();
			double cal_ang_qian = data_canshu.ang_d / cos(tcRadians(ls_ang_luo));
			ls_sys = in_rx.hSYS(i) * tcRotZ(3, ls_ang_luo) * tcRotX(3, (90.0 - data_canshu.ang_d));
		}

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}


Miller_GX_R_LXC::Miller_GX_R_LXC()
{
	gx_type = 21;
}

Miller_GX_R_LXC::~Miller_GX_R_LXC()
{
}

Miller_GX_R_LXC::Miller_GX_R_LXC(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_LXC::Miller_GX_R_LXC(int in_name)
{
	name = in_name;
}

int Miller_GX_R_LXC::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_LXC::Load(int in_pos)
{
	//恢复参数
	CanShu_R_LXC  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_LXC::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_DaoTiJianXi::get_canshu(CanShu_R_DaoTiJianXi& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_DaoTiJianXi::set_canshu(CanShu_R_DaoTiJianXi& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_DaoTiJianXi(ptr);

}

void Miller_GX_R_DaoTiJianXi::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_dt_jx); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_DaoTiJianXi::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_DaoTiJianXi::cal_base_DL()
{
}

Miller_GX_R_DaoTiJianXi::Miller_GX_R_DaoTiJianXi()
{
	gx_type = 22;
}

Miller_GX_R_DaoTiJianXi::~Miller_GX_R_DaoTiJianXi()
{
}

Miller_GX_R_DaoTiJianXi::Miller_GX_R_DaoTiJianXi(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_DaoTiJianXi::Miller_GX_R_DaoTiJianXi(int in_name)
{
	name = in_name;
}

int Miller_GX_R_DaoTiJianXi::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_DaoTiJianXi::Load(int in_pos)
{
	//恢复参数
	CanShu_R_DaoTiJianXi  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_DaoTiJianXi::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_DaoJianJianXi::get_canshu(CanShu_R_DaoJianJianXi& ans)
{
	ans = data_canshu;
}

void Miller_GX_R_DaoJianJianXi::set_canshu(CanShu_R_DaoJianJianXi& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_DaoJianJianXi(ptr);

}

void Miller_GX_R_DaoJianJianXi::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_dj_jx); //改为public
	//cal_renxian(Cal_RenXian& ans_rx);
   // cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_DaoJianJianXi::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

void Miller_GX_R_DaoJianJianXi::cal_base_DL()
{
}

Miller_GX_R_DaoJianJianXi::Miller_GX_R_DaoJianJianXi()
{
	gx_type = 23;
}

Miller_GX_R_DaoJianJianXi::~Miller_GX_R_DaoJianJianXi()
{
}

Miller_GX_R_DaoJianJianXi::Miller_GX_R_DaoJianJianXi(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_DaoJianJianXi::Miller_GX_R_DaoJianJianXi(int in_name)
{
	name = in_name;
}

int Miller_GX_R_DaoJianJianXi::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_DaoJianJianXi::Load(int in_pos)
{
	//恢复参数
	CanShu_R_DaoJianJianXi  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_DaoJianJianXi::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_R_DaoJianFenXieCao::get_canshu(CanShu_R_DaoJianFenXieCao& ans)
{
	ans = data_canshu;
}

//A设置球头容屑槽参数
void Miller_GX_R_DaoJianFenXieCao::set_canshu(CanShu_R_DaoJianFenXieCao& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_R_DaoJianFenXieCao(ptr);

}

//A.1设置球头容屑槽参数
void Miller_GX_R_DaoJianFenXieCao::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_r_dj_fxc); //改为public
	// cal_renxian(Cal_RenXian& ans_rx);
	// cal_leadface(Cal_RenXian& ans_rx);
	self_xingcan = &ptr;
}

void Miller_GX_R_DaoJianFenXieCao::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
	//
}

//计算基本刀路
void Miller_GX_R_DaoJianFenXieCao::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、从铣刀获取基本刃线，并对刃线进行编辑
			Cal_RenXian get_renxian;
			self_Dao->get_renxian_of_hen(ls_ren_pos, get_renxian); //中心指向柱面
			//引用传递会修改原始刃线，get引用后复制出一份给后续计算10.30
			Cal_RenXian ls_renxian = get_renxian;

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			ls_renxian.rotate_by_buchang(data_canshu.angle_buchang);

			//2、生成前刀面数据--
			//平底端齿槽，端刃横线根据前角变化计算出前刀坐标系，
			//磨削点为槽底线上点(起点=横刃起点，且个数相同)，得到砂轮位姿
			mat data_qdm; //12*n 
			cal_leadface(ls_renxian, data_qdm);

			int p_count = data_qdm.n_cols;

			mat p_data(3, p_count, fill::zeros);
			//mat n_data(3, p_count, fill::zeros);
			//mat t_data(3, p_count, fill::zeros);
			p_data = data_qdm.submat(0, 0, 2, p_count - 1);		//前刀面点
			//n_data = data_qdm.submat(9, 0, 11, p_count - 1);		//法向 = z轴
			//t_data = data_qdm.submat(3, 0, 5, p_count - 1);

			mat test_p2 = p_data.t();
			test_p2.save(R"(test_dcc_1.18.txt)", raw_ascii);

			//在投影到XOZ平面中，不用计算圆心坐标，可得到夹角
			vec3 p_start = data_qdm.submat(0, p_count - 1, 2, p_count - 1);

			////计算初始点砂轮位移角度，以初始位姿从初始磨削点向上槽顶角度平移-1.18
			//double D_gj = self_Dao->get_gg_canshu_D_qiu();
			//double ang_caoding = data_canshu.ang_caoding;
			//double D_sl = shalun_canshu.D;
			//double ang_ans = 0.0;
			//cal_sl_weiyi_ang(D_gj, ang_caoding, D_sl, ang_ans);


			//3、根据前刀面坐标系构造砂轮位姿			
			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_p = data_qdm.submat(0, i, 2, i);
				vec3 sys_ls_x = data_qdm.submat(3, i, 5, i);
				vec3 sys_ls_y = data_qdm.submat(6, i, 8, i);
				vec3 sys_ls_z = data_qdm.submat(9, i, 11, i);

				mat33 G_SYS_HDM = eye(3, 3);
				G_SYS_HDM.col(0) = sys_ls_x;
				G_SYS_HDM.col(1) = sys_ls_y;
				G_SYS_HDM.col(2) = sys_ls_z;

				mat33 ls_G_SYS_HDM = G_SYS_HDM * tcRotZ(3, data_canshu.ang_caoding);

				//矩阵按照列构造，
				// sl_sys_z = ls_qdm_z, sl_x = ls_qdm_y, sl_y = -ls_qdm_x
				mat33 G_SYS_SL = ls_G_SYS_HDM;
				G_SYS_SL.col(0) = ls_G_SYS_HDM.col(1);
				G_SYS_SL.col(1) = ls_G_SYS_HDM.col(0);
				G_SYS_SL.col(2) = -ls_G_SYS_HDM.col(2);

				G_SYS_SL = G_SYS_SL * tcRotX(3, data_canshu.angle_qiexue);

				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0); //默认内侧
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}

				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_p;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}


			//4.5、延长一定距离
			//横向退刀延长开始位姿，然后刀路反向
			{
				double ang_hen_tui = data_canshu.angle_heng_tui;

				double dis_extend = data_canshu.dis_end_extend;  //需要加密延长点12.2
				vec end_v = ls_renxian.nX(ls_renxian.n_P - 1);
				vec end_y = ls_renxian.nY(ls_renxian.n_P - 1);
				vec end_z = ls_renxian.nZ(ls_renxian.n_P - 1);

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_SL_start = DL_part.Data[0].G_SYS_SL;
				mat33 ls_sys_sl = DL_part.Data[0].G_SYS_SL * tcRotX(3, ang_hen_tui); //横向退刀
				vec start_v = ls_sys_sl * (-tcY(3));
				start_v(2) = 0.0;
				start_v = normalise(start_v);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用起始
				dis_p = 0.04;
				int count_yan = dis_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + (start_v)*i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = G_SYS_SL_start;
					ans_start.point_type = 2;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);

					//DL_P ans_end;
					//ans_end.G_P = p_dl_end + (end_v)*i * dis_p; //终点刃线切向 11.28
					//ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					//ans_end.G_SYS_SL = G_SYS_SL_end;
					//ans_end.point_type = 0;

					//DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//4.6、刀路点反向，只改点的顺序
			reverse(DL_part.Data.begin(), DL_part.Data.end());

			//5、单刃进退刀
			XiDao_QDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_R_DaoJianFenXieCao::cal_leadface(Cal_RenXian& in_rx, mat& data_qdm)
{//前刀面：刃线法坐标系绕x转 90-前角
	int p_num = in_rx.get_p_num();
	double delta_ang = data_canshu.ang_n1 / p_num;

	//求得槽终点的方向向量，起点加方向长度
	mat end_sys = in_rx.nSYS(p_num - 1);
	vec3 end_hen_p = in_rx.P(p_num - 1);
	double cao_h = in_rx.Lenth_of_RenXian() * tan(tcRadians(data_canshu.ang_caoding));
	vec3 cao_t = end_sys * tcRotX(3, (90.0 - data_canshu.ang_n1)) * tcY(3);
	vec3 cao_end_p = end_hen_p + cao_t * cao_h;

	vec3 start_p = in_rx.P(0);
	vec3 ans_fangxiang = normalise(cao_end_p - start_p);

	double cao_len = in_rx.Lenth_of_RenXian() / cos(tcRadians(data_canshu.ang_caoding));
	double delta_len = cao_len / p_num;

	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = start_p + ans_fangxiang * i * delta_len;
		mat ls_test = in_rx.nSYS(i);
		mat ans_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - i * delta_ang));

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ans_sys.col(0)(0) ,ans_sys.col(0)(1) ,ans_sys.col(0)(2),
		ans_sys.col(1)(0) ,ans_sys.col(1)(1) ,ans_sys.col(1)(2) ,
		ans_sys.col(2)(0) ,ans_sys.col(2)(1) ,ans_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}

Miller_GX_R_DaoJianFenXieCao::Miller_GX_R_DaoJianFenXieCao()
{
	gx_type = 24;
}

Miller_GX_R_DaoJianFenXieCao::~Miller_GX_R_DaoJianFenXieCao()
{
}

//铣刀增加一个工序时，构造对象时挂上父项指针，从而可获得公共参数
Miller_GX_R_DaoJianFenXieCao::Miller_GX_R_DaoJianFenXieCao(Miller_D_R* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_R_DaoJianFenXieCao::Miller_GX_R_DaoJianFenXieCao(int in_name)
{
	name = in_name;
}

int Miller_GX_R_DaoJianFenXieCao::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_R_DaoJianFenXieCao::Load(int in_pos)
{
	//恢复参数
	CanShu_R_DaoJianFenXieCao  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_R_DaoJianFenXieCao::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_Base::set_canshu(XingCan_Miller_GX& in_ptr)
{
}

void Miller_GX_Base::set_Mo_HDM_CanShu(xt_Mo_HDM_CanShu& in_Mo_Canshu)
{
	Mo_Canshu = in_Mo_Canshu;
}

void Miller_GX_Base::set_xingcan(int in_type)
{
	switch (in_type)
	{
	case 0:
	{
		CanShu_ZQ_QDM ls;
		self_xingcan->set_CanShu_ZQ_QDM(ls);
		break;
	}
	case 1:
	{
		Canshu_ZQ_LXC ls;
		self_xingcan->set_Canshu_ZQ_LXC(ls);
		break;
	}
	case 2:
	{
		Canshu_ZQ_HDM_1 ls;
		self_xingcan->set_Canshu_ZQ_HDM_1(ls);
		break;
	}
	case 3:
	{
		Canshu_ZQ_HDM_2 ls;
		self_xingcan->set_Canshu_ZQ_HDM_2(ls);
		break;
	}
	case 4:
	{
		Canshu_ZQ_HDM_3 ls;
		self_xingcan->set_Canshu_ZQ_HDM_3(ls);
		break;
	}
	case 5:
	{
		CanShu_ZQ_DaoTiJianXi ls;
		self_xingcan->set_CanShu_ZQ_DaoTiJianXi(ls);
		break;
	}
	case 6:
	{
		CanShu_ZQ_DaoJianJianXi ls;
		self_xingcan->set_CanShu_ZQ_DaoJianJianXi(ls);
		break;
	}
	case 7:
	{
		CanShu_ZQ_DaoJianFenXieCao ls;
		self_xingcan->set_CanShu_ZQ_DaoJianFenXieCao(ls);
		break;
	}
	case 8:
	{
		CanShu_PD_DCC ls;
		self_xingcan->set_CanShu_PD_DCC(ls);
		break;
	}
	case 9:
	{
		CanShu_PD_DHDM_1 ls;
		self_xingcan->set_CanShu_PD_DHDM_1(ls);
		break;
	}
	case 10:
	{
		CanShu_PD_DHDM_2 ls;
		self_xingcan->set_CanShu_PD_DHDM_2(ls);
		break;
	}
	case 11:
	{
		CanShu_PD_DHDM_3 ls;
		self_xingcan->set_CanShu_PD_DHDM_3(ls);
		break;
	}
	case 12:
	{
		CanShu_PD_LXC ls;
		self_xingcan->set_CanShu_PD_LXC(ls);
		break;
	}
	case 13:
	{
		CanShu_PD_HDM_1 ls;
		self_xingcan->set_CanShu_PD_HDM_1(ls);
		break;
	}
	case 14:
	{
		CanShu_PD_HDM_2 ls;
		self_xingcan->set_CanShu_PD_HDM_2(ls);
		break;
	}
	case 15:
	{
		CanShu_PD_HDM_3 ls;
		self_xingcan->set_CanShu_PD_HDM_3(ls);
		break;
	}
	case 16:
	{
		CanShu_PD_DaoTiJianXi ls;
		self_xingcan->set_CanShu_PD_DaoTiJianXi(ls);
		break;
	}
	case 17:
	{
		CanShu_R_QDM_R ls;
		self_xingcan->set_CanShu_R_QDM_R(ls);
		break;
	}
	case 18:
	{
		CanShu_R_HDM_1 ls;
		self_xingcan->set_CanShu_R_HDM_1(ls);
		break;
	}
	case 19:
	{
		CanShu_R_HDM_2 ls;
		self_xingcan->set_CanShu_R_HDM_2(ls);
		break;
	}
	case 20:
	{
		CanShu_R_HDM_3 ls;
		self_xingcan->set_CanShu_R_HDM_3(ls);
		break;
	}
	case 21:
	{
		CanShu_R_LXC ls;
		self_xingcan->set_CanShu_R_LXC(ls);
		break;
	}
	case 22:
	{
		CanShu_R_DaoTiJianXi ls;
		self_xingcan->set_CanShu_R_DaoTiJianXi(ls);
		break;
	}
	case 23:
	{
		CanShu_R_DaoJianJianXi ls;
		self_xingcan->set_CanShu_R_DaoJianJianXi(ls);
		break;
	}
	case 24:
	{
		CanShu_R_DaoJianFenXieCao ls;
		self_xingcan->set_CanShu_R_DaoJianFenXieCao(ls);
		break;
	}

	default:
		break;
	}
}

void Miller_GX_Base::set_shalun_CanShu(CanShu_shalun_cal_DL& in_cal_shalun)
{
	shalun_canshu = in_cal_shalun;
}

void Miller_GX_Base::cal_DL()
{
	//0、计算前清空基本刀路-10.21
	DL_base.Data.clear();
	DL_base.anquandian = anquandian;

	//计算基本刀路
	cal_base_DL();
	//进退刀--提到cal_base_DL()内部-11.4
	//DL_end = XiDao_JinTuiDao(DL_base, Mo_Canshu.jintuidao);
	DL_end = DL_base;
	//变换
   // DL_end = XiDao_HDM_MoXue_BianHuan(DL_end, Mo_Canshu.bianhuan);
	//循环
   // DL_end = XiDao_HDM_MoXue_XunHuan(DL_end, Mo_Canshu.xunhuan);
	//阵列
	//DL_end = XiDao_HDM_MoXue_ZhenLie(DL_end, Mo_Canshu.zhenlie);

}

void Miller_GX_Base::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//设置速度
	prog_of_gx->set_jingeilv(Mo_Canshu.sudu.MoXueJinGei, Mo_Canshu.sudu);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);
}

Miller_GX_CX_KaiCao::Miller_GX_CX_KaiCao(int in_name)
{
	name = in_name;
}

Miller_GX_CX_HDM_1::Miller_GX_CX_HDM_1(int in_name)
{
	name = in_name;
}

int Miller_GX_CX_HDM_1::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_CX_HDM_1::Load(int in_pos)
{
	//恢复参数
	CanShu_GX_CX_HDM_1  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_CX_HDM_1::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_CX_KaiCao::get_canshu(CanShu_GX_CX_KaiCao& ans)
{
	//self_Dao = in_ptr;
	ans = data_canshu;
	//data_canshu = ptr;
	//self_xingcan->set_CanShu_GX_CX_KaiCao(ptr);
}

void Miller_GX_CX_KaiCao::set_canshu(CanShu_GX_CX_KaiCao& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_GX_CX_KaiCao(ptr);
}

void Miller_GX_CX_KaiCao::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_cx_kaicao); //改为public
	self_xingcan = &ptr;
}

void Miller_GX_CX_KaiCao::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;
}

void Miller_GX_CX_KaiCao::cal_base_DL()
{
	QuMian_Grovving_namespace::Gpoint p;
	//选择用于开槽的型线，加螺旋得到刃线4.9  螺旋有型线
	Cal_XingXian cur_xx = cur_tool_sel_xx_data[data_canshu.sel_luoxuan_index];
	//根据采样参数处理型线
	int cai_type = 0;
	double cai_len = 0.0;
	double cai_ang = 0.0;
	self_Dao->get_cx_caiyang_canshu(cai_type, cai_len, cai_ang);
	if (cai_type == 0)
	{
		cai_ang = 90.0;
	}
	cur_xx.Sample(cai_len, cai_ang);

#pragma region 计算当前工序刃线
	int sel_index = data_canshu.sel_luoxuan_index;
	int type_cao = -1;
	double ang_zhuan = 0.0;
	double ang_qing = 0.0;
	double dis_pian = 0.0;
	double ang_luo = 0.0;
	double daocheng = 0.0;
	self_Dao->get_cx_luoxuancanshu_by_sel(sel_index, type_cao,
		ang_zhuan, ang_qing, dis_pian, ang_luo, daocheng);

	//根据螺旋构造刃线
	//将型线点，转不同相位角
	Cal_RenXian cur_gx_rx;
	switch (type_cao)
	{
		//倾角为零=直槽，转角及偏心
	case 0:
		cal_xiecao_by_zhuan_qing(cur_xx, ang_zhuan, ang_qing, cur_gx_rx);
		break;
	case 1:
		cal_xiecao_by_pian_qing(cur_xx, ang_zhuan, ang_qing, cur_gx_rx);
		break;
	case 2:
		cal_luoxuan_by_luo_angle(cur_xx, ang_luo, cur_gx_rx);
		break;
	case 3:
		cal_luoxuan_by_daocheng(cur_xx, daocheng, cur_gx_rx);
		break;
	default:
		break;
	}

#pragma endregion
	vector<double> v_ren_pos_ang;
	self_Dao->get_dengfen_ang(v_ren_pos_ang);
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、刃线转到选择的刃的位置后（不等分角度），构造前刀面数据4.15
			double cur_ren_pos_ang = v_ren_pos_ang[ls_ren_pos];
			Cal_RenXian cur_ren_rx = cur_gx_rx;
			mat33  sys_rotate = tcRotZ(3, cur_ren_pos_ang);
			cur_ren_rx.rotate(sys_rotate);

			//生成前刀面数据
			mat data_qdm;
			cal_leadface(cur_ren_rx, data_canshu.type, data_qdm);

			//1.1刃线工件坐标系下绕Z旋转补偿角度 
			rotate_by_buchang(data_qdm, data_canshu.angle_buchang);

			int p_count = data_qdm.n_cols;

			//计算刀路点 3.25
#pragma region MyRegion
			vec3 start_qdm_p = data_qdm.submat(0, 0, 2, 0);
			vec start_sub = data_qdm.submat(3, 0, 11, 0); //取出为9*1
			mat33 G_SYS_QDM = {
				{start_sub(0),  start_sub(3), start_sub(6)},
				{start_sub(1),  start_sub(4), start_sub(7)},
				{start_sub(2),  start_sub(5), start_sub(8)}, };
			//初始砂轮位姿
			mat33 G_SYS_SL = G_SYS_QDM;
			G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度

			double xinhou_R = self_Dao->get_gg_canshu_D_qiu() * data_canshu.percent_r;
			double ans_zhuan = Cal_LXC_SL_SYS_by_XH(start_qdm_p, G_SYS_SL, shalun_canshu.D / 2.0, xinhou_R);

			G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

			for (int i = 0; i < p_count; i++)
			{
				vec3 ls_qdm_p = data_qdm.submat(0, i, 2, i);
				vec ls_sub = data_qdm.submat(3, i, 11, i); //取出为9*1

				mat33 G_SYS_QDM = {
				   {ls_sub(0),  ls_sub(3), ls_sub(6)},
				   {ls_sub(1),  ls_sub(4), ls_sub(7)},
				   {ls_sub(2),  ls_sub(5), ls_sub(8)}, };

				mat33 G_SYS_SL = G_SYS_QDM;
				G_SYS_SL = G_SYS_SL * tcRotY(3, data_canshu.angle_qiexue);//转切削角度
				G_SYS_SL = G_SYS_SL * tcRotZ(3, 90.0) * tcRotZ(3, -ans_zhuan);

				//切换砂轮内外侧磨削 
				if (in_or_out == 1)
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 180.0);
				}
				else
				{
					G_SYS_SL = G_SYS_SL * tcRotX(3, 0.0);
				}

				//不解算出砂轮参考点，满足用戴杰后处理的条件 9.9
				DL_P ans_DL_P;
				ans_DL_P.G_P = ls_qdm_p;
				ans_DL_P.G_SYS_HDM = G_SYS_QDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}
#pragma endregion

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			{
				double dis_start_extend = data_canshu.extend_start;

				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_QDM_start = DL_part.Data[0].G_SYS_HDM;

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + G_SYS_QDM_start * (-tcX(3)) * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.extend_end;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_QDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_QDM_start * (tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}

			}

			//5、螺旋槽单刃进退刀--11.4
			XiDao_LXC_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

//根据螺旋的槽类型参数构造出型线对应的刃线 -4.15

void Miller_GX_CX_KaiCao::cal_xiecao_by_zhuan_qing(Cal_XingXian& in_xx, double in_zhuan, double in_qing, Cal_RenXian& ans_rx)
{
	//刃线需要空间线构造，空间线用mat构造
	mat data_points;
	data_points.reset();

	//将型线点遍历，旋转转角，平移倾角
	int count_p = in_xx.n_P();
	mat all_p = in_xx.BG_hP();

	all_p = tcRotZ(3, in_zhuan) * all_p;

	for (int i = 0; i < count_p - 1; i++)
	{
		vec ls_cur_p = all_p.col(i);
		vec ls_next_p = all_p.col(i + 1);

		double delta_z = ls_next_p(2) - ls_cur_p(2);
		double delta_y = delta_z * tan(tcRadians(in_qing));
		ls_next_p(1) = ls_next_p(1) + delta_y; //初始点都在XOz平面

		vec ls_cur_t = normalise(ls_next_p - ls_cur_p);
		all_p.col(i + 1) = ls_next_p; //修改下一个点，循环的下次直接使用

		vec ls_ans_data = { ls_cur_p(0),ls_cur_p(1) ,ls_cur_p(2) ,
		ls_cur_t(0),ls_cur_t(1) ,ls_cur_t(2) };

		data_points.insert_cols(data_points.n_cols, ls_ans_data);
	}
	{//最后一个点放入
		vec ls_cur_p = all_p.col(count_p - 1);

		vec ls_last_t = data_points.col(data_points.n_rows - 1);

		vec ls_ans_data = { ls_cur_p(0),ls_cur_p(1) ,ls_cur_p(2) ,
				ls_last_t(3),ls_last_t(4) ,ls_last_t(5) };
		data_points.insert_cols(data_points.n_cols, ls_ans_data);
	}

	mat ls_input = data_points.submat(0, 0, 2, count_p - 1);
	KongJianXian ls_line;
	ls_line.init_data(ls_input);

	ans_rx.ImportData_by_luoxuancao(ls_line);
}

void Miller_GX_CX_KaiCao::cal_xiecao_by_pian_qing(Cal_XingXian& in_xx, double in_pian, double in_qing, Cal_RenXian& ans_rx)
{
	//将偏心距转化为转角，调用转角函数
	vec start_p = in_xx.BG_hP(3, 0);

	double ang_zhuan = tcDegree(atan(in_pian / start_p(0)));

	cal_xiecao_by_zhuan_qing(in_xx, ang_zhuan, in_qing, ans_rx);
}

void Miller_GX_CX_KaiCao::cal_luoxuan_by_luo_angle(Cal_XingXian& in_xx, double in_luo_ang, Cal_RenXian& ans_rx)
{
	//计算每个刃线点的需要的转角
	double cur_ang_zhuan = 0.0;
	int count_p = in_xx.n_P();
	mat data_points;
	data_points.reset();

	vec last_p = in_xx.BG_hP(3, 0);
	last_p = tcRotZ(3, cur_ang_zhuan) * last_p;
	data_points.insert_cols(data_points.n_cols, last_p);

	for (int i = 1; i < count_p; i++)
	{
		vec ls_next_p = in_xx.BG_hP(3, i);

		double delta_z = ls_next_p(2) - last_p(2);
		double delta_y = delta_z * tan(tcRadians(in_luo_ang));

		double delta_ang_zhuan = tcDegree(atan(delta_y / ls_next_p(0)));

		cur_ang_zhuan = cur_ang_zhuan + delta_ang_zhuan;

		last_p = ls_next_p;
		last_p = tcRotZ(3, cur_ang_zhuan) * last_p;
		data_points.insert_cols(data_points.n_cols, last_p);
	}

	mat ls_input = data_points;
	KongJianXian ls_line;
	ls_line.init_data(ls_input);

	ans_rx.ImportData_by_luoxuancao(ls_line);
}

void Miller_GX_CX_KaiCao::cal_luoxuan_by_daocheng(Cal_XingXian& in_xx, double in_daocheng, Cal_RenXian& ans_rx)
{
	vec start_p = in_xx.BG_hP(3, 0);
	double ang_luo = tcDegree(atan(in_daocheng / (start_p(0) * datum::pi)));
	cal_luoxuan_by_luo_angle(in_xx, ang_luo, ans_rx);
}

void Miller_GX_CX_KaiCao::cal_leadface(Cal_RenXian& in_rx, int ang_type, mat& data_qdm)
{
	//螺旋槽前刀面：刃线法坐标系绕x转 90-前角
//根据前角类型：旋转不同的刃线坐标系--11.7
	int p_num = in_rx.get_p_num();
	data_qdm.resize(12, 0);
	data_qdm.insert_cols(0, p_num);
	for (int i = 0; i < p_num; i++)
	{
		vec3 ls_p = in_rx.P(i);
		mat ls_sys = eye(3, 3);
		if (ang_type == 0)
		{
			ls_sys = in_rx.nSYS(i) * tcRotX(3, (90.0 - data_canshu.ang_n1));
		}
		else
		{
			//test
			mat test_mat = in_rx.hSYS(i);
			//先Z转螺旋角，在X转修正后的前角2.20
			double ls_ang_luo = self_Dao->get_gg_canshu_luo();
			double cal_ang_qian = data_canshu.ang_d / cos(tcRadians(ls_ang_luo));
			ls_sys = in_rx.hSYS(i) * tcRotZ(3, ls_ang_luo) * tcRotX(3, (90.0 - data_canshu.ang_d));
		}

		vec ans = { ls_p(0),ls_p(1) ,ls_p(2) ,
		ls_sys.col(0)(0) ,ls_sys.col(0)(1) ,ls_sys.col(0)(2),
		ls_sys.col(1)(0) ,ls_sys.col(1)(1) ,ls_sys.col(1)(2) ,
		ls_sys.col(2)(0) ,ls_sys.col(2)(1) ,ls_sys.col(2)(2) };
		data_qdm.col(i) = ans;
	}
}

void Miller_GX_CX_KaiCao::rotate_by_buchang(mat& in_qdm, double in_ang)
{
	int length = in_qdm.n_cols;
	for (int i = 0; i < length; i++)
	{
		vec3 ls_p = in_qdm.submat(0, i, 2, i);
		vec ls_sub = in_qdm.submat(3, i, 11, i); //取出为9*1

		mat33 ls_QDM = {
				{ls_sub(0),  ls_sub(3), ls_sub(6)},
				{ls_sub(1),  ls_sub(4), ls_sub(7)},
				{ls_sub(2),  ls_sub(5), ls_sub(8)}, };

		ls_p = tcRotZ(3, in_ang) * ls_p;
		ls_QDM = tcRotZ(3, in_ang) * ls_QDM;

		vec ls_ans = { ls_p(0),ls_p(1),ls_p(2),
			ls_QDM(0),ls_QDM(1),ls_QDM(2),
			ls_QDM(3),ls_QDM(4),ls_QDM(5),
			ls_QDM(6),ls_QDM(7),ls_QDM(8), };
		in_qdm.col(i) = ls_ans;
	}

}

void Miller_GX_CX_KaiCao::cal_xinhoumian(mat& px, mat& nx, double sl_D)
{
	int p_count = px.n_cols;
	vec3 start_p = { self_Dao->get_gg_canshu_D_qiu() / 2.0, 0.0, 0.0 };
	// vec3 start_end = { self_Dao->get_gg_canshu_D_bing()  , 0.0, self_Dao->get_gg_canshu_len_ren() };
	double ls_hight = self_Dao->get_gg_canshu_len_ren() * tan(tcRadians(self_Dao->get_gg_canshu_Zhui()));
	vec3 start_end = { start_p(0) + ls_hight, 0.0,  self_Dao->get_gg_canshu_len_ren() };
	start_p(0) = start_p(0) * data_canshu.percent_r;
	start_end(0) = start_end(0) * data_canshu.percent_r;

	//double delta = 1.0 / (p_count * 1.0);
	double delta = 0.1;

	vec3 start_p_front = start_p;
	start_p_front(2) = start_p_front(2) - sl_D;

	vec3 start_p_back = start_end;
	start_p_back(2) = start_p_back(2) + sl_D;

	//3段线组成
	int count1 = (sl_D) / delta;
	int count2 = count1 + p_count + (sl_D) / delta;
	px.resize(3, 0);
	px.insert_cols(0, count2);
	nx.resize(3, 0);
	nx.insert_cols(0, count2);
	//前延长
	vec3 v_p_end = normalise(start_p - start_p_front);
	for (int i = 0; i < count1; i++)
	{
		vec3 ans_p = start_p_front + i * delta * v_p_end;
		px.col(i) = ans_p;
		//切向转90度
		if (i == 0)
		{
		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(0) = nx.col(1);

	//中间
	v_p_end = normalise(start_end - start_p);
	int index = 0;
	for (int i = count1; i < count1 + p_count; i++)
	{
		vec3 ans_p = start_p + index * delta * v_p_end;
		index++;
		px.col(i) = ans_p;
		//切向转90度
		if (i == count1)
		{

		}
		else
		{
			vec3 ans_ls = normalise(ans_p - px.col(i - 1));
			vec3 ans_n = tcRotY(3, 90) * ans_ls;
			nx.col(i) = ans_n;
		}
	}
	nx.col(count1) = nx.col(count1 + 1);
	//后延长
	//v_p_end = normalise(start_p_back - start_end);
	//int index2 = 0;
	//for (int i = count1 + p_count; i < count2; i++)
	//{
	   // vec3 ans_p = start_end + index2 * delta * v_p_end;
	   // index2++;
	   // px.col(i) = ans_p;
	   // //切向转90度
	   // if (i == count1 + p_count)
	   // {

	   // }
	   // else
	   // {
	   //	 vec3 ans_ls = normalise(ans_p - px.col(i - 1));
	   //	 vec3 ans_n = tcRotY(3, 90) * ans_ls;
	   //	 nx.col(i) = ans_n;
	   // }
	//}
	//nx.col(count1 + p_count) = nx.col(count1 + p_count + 1);


}

int Miller_GX_CX_KaiCao::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_CX_KaiCao::Load(int in_pos)
{
	//恢复参数
	CanShu_GX_CX_KaiCao  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_CX_KaiCao::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_CX_KaiCao::Miller_GX_CX_KaiCao()
{
	gx_type = 25;
}

Miller_GX_CX_KaiCao::~Miller_GX_CX_KaiCao()
{
}

Miller_GX_CX_KaiCao::Miller_GX_CX_KaiCao(Miller_D_CX* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_CX_HDM_1::get_canshu(CanShu_GX_CX_HDM_1& ans)
{
	ans = data_canshu;
}

void Miller_GX_CX_HDM_1::set_canshu(CanShu_GX_CX_HDM_1& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_GX_CX_HDM_1(ptr);
}

void Miller_GX_CX_HDM_1::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_cx_hdm_1); //改为public
	self_xingcan = &ptr;
}

void Miller_GX_CX_HDM_1::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{//需要一个主程序指针
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;

}

void Miller_GX_CX_HDM_1::cal_base_DL()
{
	//根据选择的型线、螺旋，计算出刃线，
//转对应前角得到前刀面 4.9
//刃线旋转到对应位置，因此在循环外计算好
	Cal_XingXian cur_xx = cur_tool_sel_xx_data[data_canshu.sel_luoxuan_index];
	//根据采样参数处理型线
	int cai_type = 0;
	double cai_len = 0.0;
	double cai_ang = 0.0;
	self_Dao->get_cx_caiyang_canshu(cai_type, cai_len, cai_ang);
	if (cai_type == 0)
	{
		cai_ang = 90.0;
	}
	cur_xx.Sample(cai_len, cai_ang);

#pragma region 计算当前工序刃线
	int sel_index = data_canshu.sel_luoxuan_index;
	int type_cao = -1;
	double ang_zhuan = 0.0;
	double ang_qing = 0.0;
	double dis_pian = 0.0;
	double ang_luo = 0.0;
	double daocheng = 0.0;
	self_Dao->get_cx_luoxuancanshu_by_sel(sel_index, type_cao,
		ang_zhuan, ang_qing, dis_pian, ang_luo, daocheng);

	//根据槽型构造槽面
	Cal_LouXuan cur_cm;

	vec start_p = cur_xx.BG_hP(3, 0);
	vec end_p = cur_xx.BG_hP(3, cur_xx.n_P() - 1);

	cur_cm.set_R_len(start_p(0), end_p(2));

	switch (type_cao)
	{
	case 0:
		cur_cm.init_data_by_zhuan_qing(ang_zhuan, ang_qing);
		break;
	case 1:
		cur_cm.init_data_by_pianxin_qing(dis_pian, ang_qing);
		break;
	case 2:
		cur_cm.init_data_by_luoxuan(ang_luo);
		break;
	case 3:
		cur_cm.init_data_by_daocheng(daocheng);
		break;
	default:
		break;
	}

	//槽面与型线回转的交线为后刀面刃线


#pragma endregions

	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_1(ls_ren_pos, data_hdm);

			//1.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_cx_hdm(ls_ren_pos, ren_hdm1);
			int count_p = data_hdm.n_cols;

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(count_p, ls_qie, ls_wy);

			for (int i = 0; i < count_p; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;
				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				{
					vec3 ren_n, ren_t;
					double theta = 0.0;
					double ang_xiu = 0.0;

					ren_n = ren_hdm1.hY(i); //平面法向
					ren_t = ren_hdm1.hX(i);

					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					//vec3 ls_x = normalise( dot(ren_t, G_SYS_SL.col(0)) * G_SYS_SL.col(0));
					theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					ang_xiu = tcDegree(acos(theta));
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			//角度延长过中刀路点
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				//dis_start_extend = 0.1; //X指向回转轴且偏下-1.13,转30度
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;
				vec3 t_yan = G_SYS_HDM_start * tcRotZ(3, 0.0) * tcX(3); //转角大不能形成交线//1.16
				t_yan(2) = -t_yan(2);
				t_yan = normalise(t_yan);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + t_yan * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //横刃砂轮以0度后角延长1.16-后角5°横刃在球面上0.00098
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.dis_end_extend;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_CX_HDM_1::cal_cha_ang(int count_p, vector<double>& ans_qie, vector<double>& ans_wy)
{
}

Miller_GX_CX_HDM_1::Miller_GX_CX_HDM_1()
{
	gx_type = 26;
}

Miller_GX_CX_HDM_1::~Miller_GX_CX_HDM_1()
{
}

Miller_GX_CX_HDM_1::Miller_GX_CX_HDM_1(Miller_D_CX* in_ptr)
{
	self_Dao = in_ptr;
}

void Miller_GX_CX_HDM_2::get_canshu(CanShu_GX_CX_HDM_2& ans)
{
	ans = data_canshu;
}

void Miller_GX_CX_HDM_2::set_canshu(CanShu_GX_CX_HDM_2& ptr)
{
	data_canshu = ptr;
	self_xingcan->set_CanShu_GX_CX_HDM_2(ptr);
}

void Miller_GX_CX_HDM_2::set_canshu(XingCan_Miller_GX& ptr)
{
	data_canshu = *(ptr.can_cx_hdm_2); //改为public
	self_xingcan = &ptr;
}

void Miller_GX_CX_HDM_2::gen_prog_of_gx(fangzhen_zhu* zhu_ptr)
{
	prog_of_gx = new Miller_DL_fu_prog(zhu_ptr, 0);
	//需要一个副程序刀路类，加上砂轮数据，构造G01走位
	prog_of_gx->set_gx_DL(gx_type, DL_end, slz_num, sl_pos, shalun_canshu, anquandian);;

}

void Miller_GX_CX_HDM_2::cal_base_DL()
{
	for (int i = 0; i < 6; i++)
	{
		DL DL_part;
		if (data_canshu.selected_ren[i] == 1)
		{
			int ls_ren_pos = i;

			//1、获取刀面数据
			mat data_hdm;
			self_Dao->get_hdm_2(ls_ren_pos, data_hdm);

			//1.5 获取刃线，用于修正切削角
			Cal_RenXian ren_hdm1;
			self_Dao->get_renxian_of_cx_hdm(ls_ren_pos, ren_hdm1);
			int count_p = data_hdm.n_cols;

			//插值出每个点的切削，位移角度
			vector<double> ls_qie;
			vector<double> ls_wy;
			//整个面的角度插值点
			cal_cha_ang(count_p, ls_qie, ls_wy);

			for (int i = 0; i < count_p; i++)
			{
				double cur_qie = ls_qie[i];
				double cur_wy = ls_wy[i];

				vec ls_sub = data_hdm.submat(3, i, 11, i); //取出为9*1

				//矩阵按照列构造，写的什么样存成什么样，第一列为x就存012 8.26 zy 
				mat33 G_SYS_HDM = {
					{ls_sub(0),ls_sub(3), ls_sub(6)},
					{ls_sub(1),ls_sub(4), ls_sub(7)},
					{ls_sub(2),ls_sub(5), ls_sub(8)}, };

				//饶后刀面坐标系的Y转对应切削角度(磨过面与砂轮前端面)，z轴转位移角度
				mat33 G_SYS_SL = G_SYS_HDM;
				//修正砂轮坐标系使其0切削角与刃线夹角为0 -11.18
				{
					vec3 ren_n, ren_t;
					double theta = 0.0;
					double ang_xiu = 0.0;

					ren_n = ren_hdm1.hY(i); //平面法向
					ren_t = ren_hdm1.hX(i);

					vec3 ls_x = normalise(tc_vec_prj_to_plane(G_SYS_SL.col(0), ren_n));
					//vec3 ls_x = normalise( dot(ren_t, G_SYS_SL.col(0)) * G_SYS_SL.col(0));
					theta = dot(ls_x, -ren_t) / (norm(ls_x) * norm(-ren_t));
					ang_xiu = tcDegree(acos(theta));
					G_SYS_SL = G_SYS_SL * tcRotY(3, -ang_xiu) * tcRotZ(3, 180);
				}

				G_SYS_SL = G_SYS_SL * tcRotZ(3, cur_wy) * tcRotY(3, cur_qie);  //砂轮坐标系右乘

				vec3 p_sl = data_hdm.submat(0, i, 2, i);

				DL_P ans_DL_P;
				ans_DL_P.G_P = p_sl;
				ans_DL_P.G_SYS_HDM = G_SYS_HDM;
				ans_DL_P.G_SYS_SL = G_SYS_SL;

				DL_part.Data.push_back(ans_DL_P);
			}

			//4.5、延长一定距离
			//用刀路点的起始两点切向延长指定距离, 当前刃线刀尖指向刀柄
			//角度延长过中刀路点
			{
				double dis_start_extend = data_canshu.dis_start_extend;
				//dis_start_extend = 0.1; //X指向回转轴且偏下-1.13,转30度
				vec3 p_dl_start = DL_part.Data[0].G_P;
				mat33 G_SYS_HDM_start = DL_part.Data[0].G_SYS_HDM;
				vec3 t_yan = G_SYS_HDM_start * tcRotZ(3, 0.0) * tcX(3); //转角大不能形成交线//1.16
				t_yan(2) = -t_yan(2);
				t_yan = normalise(t_yan);

				double dis_p = norm(DL_part.Data[1].G_P - p_dl_start); //间距不相等，用结束
				int count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_start;
					ans_start.G_P = p_dl_start + t_yan * i * dis_p;
					ans_start.G_SYS_HDM = DL_part.Data[0].G_SYS_HDM;
					ans_start.G_SYS_SL = DL_part.Data[0].G_SYS_SL;  //横刃砂轮以0度后角延长1.16-后角5°横刃在球面上0.00098
					ans_start.point_type = 0;

					DL_part.Data.insert(DL_part.Data.begin(), ans_start);
				}

				double dis_end_extend = data_canshu.dis_end_extend;
				vec3 p_dl_end = DL_part.Data[DL_part.Data.size() - 1].G_P;
				mat33 G_SYS_HDM_end = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;

				dis_p = norm(DL_part.Data[DL_part.Data.size() - 2].G_P - p_dl_end); //间距不相等，用结束
				count_yan = dis_start_extend / dis_p;

				for (int i = 1; i <= count_yan; i++)
				{
					DL_P ans_end;
					ans_end.G_P = p_dl_end + G_SYS_HDM_end * (-tcX(3)) * i * dis_p;
					ans_end.G_SYS_HDM = DL_part.Data[DL_part.Data.size() - 1].G_SYS_HDM;
					ans_end.G_SYS_SL = DL_part.Data[DL_part.Data.size() - 1].G_SYS_SL;
					ans_end.point_type = 0;

					DL_part.Data.insert(DL_part.Data.end(), ans_end);
				}
			}

			//5、单刃进退刀
			XiDao_HDM_JinTuiDao(DL_part, Mo_Canshu.jintuidao);

			//6、组合完整刀路
			for (int i = 0; i < DL_part.Data.size(); i++)
			{
				DL_base.Data.push_back(DL_part.Data[i]);
			}
		}
	}
}

void Miller_GX_CX_HDM_2::cal_cha_ang(int count_p, vector<double>& ans_qie, vector<double>& ans_wy)
{
}

Miller_GX_CX_HDM_2::Miller_GX_CX_HDM_2()
{
	gx_type = 27;
}

Miller_GX_CX_HDM_2::~Miller_GX_CX_HDM_2()
{
}

Miller_GX_CX_HDM_2::Miller_GX_CX_HDM_2(Miller_D_CX* in_ptr)
{
	self_Dao = in_ptr;
}

Miller_GX_CX_HDM_2::Miller_GX_CX_HDM_2(int in_name)
{
	name = in_name;
}

int Miller_GX_CX_HDM_2::Save()
{
	//2、确定参数存储的位置
	int can_pos = self_Dao->storage_tool->write_a_row_data(5, (char*)&data_canshu, sizeof(data_canshu));

	//3、构造一条gx对象数据
	time_updata cur_time;
	gx_obj_data ls_row_data(gx_type, name, slz_num);
	int gx_pos = self_Dao->storage_tool->write_a_row_data(4, (char*)&ls_row_data, sizeof(ls_row_data));

	return gx_pos;
}

void Miller_GX_CX_HDM_2::Load(int in_pos)
{
	//恢复参数
	CanShu_GX_CX_HDM_2  data_canshu;
	//int can_pos = ls_row_data.data_pos;
	self_Dao->storage_tool->read_a_row_data(5, in_pos, (char*)&data_canshu, sizeof(data_canshu));
	this->data_canshu = data_canshu;
	set_canshu(data_canshu);

	//恢复磨削参数
	xt_Mo_HDM_CanShu ls_mo;
	self_Dao->storage_tool->read_a_row_data(3, in_pos, (char*)&ls_mo, sizeof(xt_Mo_HDM_CanShu));
	Mo_Canshu = ls_mo;

	//恢复安全点
	Point_by_5axis ls_an;
	self_Dao->storage_tool->read_a_row_data(20, in_pos, (char*)&ls_mo, sizeof(ls_an));
	anquandian = ls_an;
}

void Miller_GX_CX_HDM_2::set_self_dao(Miller_D_Base* in_ptr)
{
	self_Dao = in_ptr;
}
