#define Prog_Manager_EXPORTS
#include"Miller_CanShu.h"
using namespace std;
#include<vector>

CanShu_ZQ_QDM::CanShu_ZQ_QDM()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}

	angle_buchang = 0.0;

	ang_to_end = 5.0;
	dis_end_extend = 1.0;
	dis_to_center = 0.0;
	dis_start_extend = 0.0;

	type = 0;
	ang_n1 = 5.0;
	ang_n2 = 3.0;
	ang_n3 = 0.1;

	deep_qie = 0.1;
	angle_up = 30.0;
	jin_percent_r = 0.9;
	angle_jin = 10.0;

	angle_qiexue = 2.0;
}

CanShu_ZQ_QDM::~CanShu_ZQ_QDM()
{
}

void CanShu_ZQ_QDM::set_CanShu(double in_pian, double in_end_bi, double in_end_dis, double in_start_bi, double in_start_dis, int in_type, double in_ang1, double in_ang2, double in_ang3, double in_deep, double in_ang_up, double in_r_bi, double ang_end, double in_ang_qie)
{
	ang_to_end = in_end_bi;
	dis_end_extend = in_end_dis;
	dis_to_center = in_start_bi;
	dis_start_extend = in_start_dis;

	type = in_type;
	ang_n1 = in_ang1;
	ang_n2 = in_ang2;
	ang_n3 = in_ang3;

	deep_qie = in_deep;
	angle_up = in_ang_up;
	jin_percent_r = in_r_bi;
	angle_jin = ang_end;

	angle_qiexue = in_ang_qie;
}

void CanShu_ZQ_QDM::set_canshu(vector<double>& v_canshu)
{
	double ls = v_canshu[0];
	ang_to_end = v_canshu[1];
	dis_end_extend = v_canshu[2];
	dis_to_center = v_canshu[3];
	dis_start_extend = v_canshu[4];

	type = v_canshu[5];
	ang_n1 = v_canshu[6];
	ang_n2 = v_canshu[7];
	ang_n3 = v_canshu[8];

	deep_qie = v_canshu[9];
	angle_up = v_canshu[10];
	jin_percent_r = v_canshu[11];
	angle_jin = v_canshu[12];

	angle_qiexue = v_canshu[13];
}

void CanShu_ZQ_QDM::get_canshu(vector<double>& v_canshu)
{
	v_canshu.clear();
	//v_canshu.push_back(pianxin);
	v_canshu.push_back(ang_to_end);
	v_canshu.push_back(dis_end_extend);
	v_canshu.push_back(dis_to_center);
	v_canshu.push_back(dis_start_extend);

	v_canshu.push_back(type);
	v_canshu.push_back(ang_n1);
	v_canshu.push_back(ang_n2);
	v_canshu.push_back(ang_n3);

	v_canshu.push_back(deep_qie);
	v_canshu.push_back(angle_up);
	v_canshu.push_back(jin_percent_r);
	v_canshu.push_back(angle_jin);
	v_canshu.push_back(angle_qiexue);
}

int CanShu_ZQ_QDM::get_canshu_count()
{
	return 14;
}

void CanShu_ZQ_GongGong::set_CanShu(double in_len_all, double in_len_ren, double in_D_bing, double in_D_qiu, double in_ang_start_zhuan, double in_ang_start_qing, double in_ang_start_luo, double in_ang_end_zhuan, double in_ang_end_qing, double in_ang_end_luo, double in_ang_zhui, double in_ang_luoxuan, double in_ang_bing)
{
	len_all = in_len_all;
	len_ren = in_len_ren;
	D_bing = in_D_bing;

	D_qiu = in_D_qiu;
	ang_start_zhuan = in_ang_start_zhuan;
	ang_start_qing = in_ang_start_qing;
	ang_start_luo = in_ang_start_luo;

	ang_end_zhuan = in_ang_end_zhuan;
	ang_end_qing = in_ang_end_qing;
	ang_end_luo = in_ang_end_luo;

	ang_zhui = in_ang_zhui;
	ang_luoxuan = in_ang_luoxuan;
	//ang_start_zhuan_luo = 0.0;
	ang_bing = in_ang_bing;
}

CanShu_ZQ_GongGong::~CanShu_ZQ_GongGong()
{
}

int CanShu_ZQ_GongGong::get_canshu_count()
{
	return 13;
}

CanShu_ZQ_GongGong::CanShu_ZQ_GongGong()
{

	len_all = 100.123451;
	len_ren = 50.0;
	D_bing = 10.0;

	D_qiu = 20.0;
	ang_start_zhuan = 0.0;
	ang_start_qing = 0.0;
	ang_start_luo = 30.0;

	ang_end_zhuan = 90.;
	ang_end_qing = 90.0;
	ang_end_luo = 0.0;

	ang_zhui = 0.0;
	ang_luoxuan = 30.0;
	ang_bing = 0.1;

	ren_count = 0;
	is_dengfen = true;
	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}


	hdm_1_width = 1.0;
	hdm_1_d_qiu = 0.0;
	hdm_1_a_qiu = 3.0;
	hdm_1_d_mid = 10.0;
	hdm_1_a_mid = 0.0;
	hdm_1_d_luo = 15.0;
	hdm_1_a_luo = 0.0;

	hdm_2_width = 1.0;
	hdm_2_d_qiu = 0.0;
	hdm_2_a_qiu = 3.0;
	hdm_2_d_mid = 10.0;
	hdm_2_a_mid = 0.0;
	hdm_2_d_luo = 15.0;
	hdm_2_a_luo = 0.0;

}
Canshu_ZQ_HDM_1::Canshu_ZQ_HDM_1()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	dis_to_center = 0.0;
	dis_start_extend = 0.0;

	angle_qiexue_qiu = 3.0;
	angle_wy_qiu = 0.0;

	pos_percent = 0.5; //插值点的位置
	angle_qiexue_qiu2 = 3.0;	//切削角度
	angle_wy_qiu2 = 0.0;	//位移角度

	dis_end_extend = 2.0;

	angle_qiexue_luo = 5.0;	//切削角度
	angle_wy_luo = 0.0;	//位移角度
}

Canshu_ZQ_HDM_1::~Canshu_ZQ_HDM_1()
{
}

int Canshu_ZQ_HDM_1::get_canshu_count()
{
	return 21;
}

Canshu_ZQ_LXC::Canshu_ZQ_LXC()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	dis_start_extend = 0.0;
	dis_end_extend = 0.0;

	type = 1;
	ang_n1 = 1.0;
	ang_d = 10.0;

	type_xinhou = 0;
	angle_wy_deng = 5.0;
	percent_r = 0.5;
	angle_wy_start = 5.0;
	angle_wy_end = 5.0;

	angle_qiexue = 2.1;
}

Canshu_ZQ_LXC::~Canshu_ZQ_LXC()
{
}

void Canshu_ZQ_LXC::set_canshu(vector<double>& v_canshu)
{
	dis_start_extend = v_canshu[0];
	dis_end_extend = v_canshu[1];

	type = v_canshu[2];
	ang_n1 = v_canshu[3];

	type_xinhou = v_canshu[4];
	angle_wy_deng = v_canshu[5];
	percent_r = v_canshu[6];
	angle_wy_start = v_canshu[7];
	angle_wy_end = v_canshu[8];

	angle_qiexue = v_canshu[9];
}

void Canshu_ZQ_LXC::get_canshu(vector<double>& v_canshu)
{
	v_canshu.clear();
	v_canshu.push_back(dis_start_extend);
	v_canshu.push_back(dis_end_extend);

	v_canshu.push_back(type);
	v_canshu.push_back(ang_n1);

	v_canshu.push_back(type_xinhou);
	v_canshu.push_back(angle_wy_deng);
	v_canshu.push_back(percent_r);
	v_canshu.push_back(angle_wy_start);
	v_canshu.push_back(angle_wy_end);

	v_canshu.push_back(angle_qiexue);
}

int Canshu_ZQ_LXC::get_canshu_count()
{
	return 10;
}

Canshu_ZQ_HDM_2::Canshu_ZQ_HDM_2()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	dis_to_center = 0.0;
	dis_start_extend = 0.0;

	angle_qiexue_qiu = 5.0;
	angle_wy_qiu = 35.0;

	pos_percent = 0.5; //插值点的位置
	angle_qiexue_qiu2 = 2.0;	//切削角度
	angle_wy_qiu2 = 10;	//位移角度

	dis_end_extend = 0.0;
	angle_qiexue_luo = 2.0;	//切削角度
	angle_wy_luo = 0.0;	//位移角度
}

Canshu_ZQ_HDM_2::~Canshu_ZQ_HDM_2()
{
}

int Canshu_ZQ_HDM_2::get_canshu_count()
{
	return 16;
}

CanShu_shalun_cal_DL::CanShu_shalun_cal_DL()
{
	D = 0.1;
	R = 0.05;
	L = 0.1;
}

CanShu_shalun_cal_DL::~CanShu_shalun_cal_DL()
{
}

void CanShu_shalun_cal_DL::set_CanShu(double in_d, double in_r, double in_l)
{
	D = in_d;
	R = in_r;
	L = in_l;
}

void CanShu_SuDu::set_CanShu()
{
}

CanShu_ZQ_DaoTiJianXi::CanShu_ZQ_DaoTiJianXi()
{
}

CanShu_ZQ_DaoTiJianXi::~CanShu_ZQ_DaoTiJianXi()
{
}


CanShu_ZQ_DaoJianFenXieCao::CanShu_ZQ_DaoJianFenXieCao()
{
}

CanShu_ZQ_DaoJianFenXieCao::~CanShu_ZQ_DaoJianFenXieCao()
{
}


CanShu_ZQ_DaoJianJianXi::CanShu_ZQ_DaoJianJianXi()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	djjx_R = 3.5; //圆弧半径
	djjx_ang_up = 30.0; //圆弧起点与x轴夹角
	djjx_ang_down = 30.0; //圆弧终点与z轴夹角
	djjx_ang_x = 0.0; //圆弧中间点平移到原点绕基本轴旋转
	djjx_ang_y = 0.0;
	djjx_ang_z = 0.0;
	djjx_pianzhi_x = 0.0; //刀尖间隙圆弧球心偏置距离
	djjx_pianzhi_y = 0.0;
	djjx_pianzhi_z = 0.0;
}

CanShu_ZQ_DaoJianJianXi::~CanShu_ZQ_DaoJianJianXi()
{
}


Canshu_ZQ_HDM_3::Canshu_ZQ_HDM_3()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	angle_qiexue_qiu = 5.0;
	angle_wy_qiu = 35.0;

	pos_percent = 0.5; //插值点的位置
	angle_qiexue_qiu2 = 2.0;	//切削角度
	angle_wy_qiu2 = 10;	//位移角度

	extend_end = 0.0;
	angle_qiexue_luo = 2.0;	//切削角度
	angle_wy_luo = 0.0;	//位移角度
}

Canshu_ZQ_HDM_3::~Canshu_ZQ_HDM_3()
{
}

int Canshu_ZQ_HDM_3::get_canshu_count()
{
	return 16;
}

int CanShu_PD_GongGong::get_canshu_count()
{
	return 6;
}

CanShu_PD_GongGong::CanShu_PD_GongGong()
{
	len_all = 100.0;
	len_ren = 50.0;
	D_bing = 10.0;
	D_qiu = 20.0;
	ang_die = 5.0;
	ang_luo = 30.0;

	ren_count = 0;
	is_dengfen = true;
	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}

	hdm_1_width = 1.0;
	hdm_1_a_hen = 10.0;
	hdm_1_d_luo = 5.0;

	hdm_2_width = 1.0;
	hdm_2_a_hen = 10.0;
	hdm_2_d_luo = 5.0;

	hdm_3_width = 1.0;
	hdm_3_a_hen = 10.0;
	hdm_3_d_luo = 5.0;
}

CanShu_PD_GongGong::~CanShu_PD_GongGong()
{
}


int CanShu_R_GongGong::get_canshu_count()
{
	return 8;
}

CanShu_R_GongGong::CanShu_R_GongGong()
{
	len_all = 100.0;
	len_ren = 50.0;
	D_bing = 10.0;
	D_qiu = 10.0;
	ang_die = 5.0;
	ang_luo = 30.0;

	R_qiu = 0.5;

	ren_count = 0;
	is_dengfen = true;
	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}

	hdm_1_width = 1.0;
	hdm_1_a_hen = 5.0;
	hdm_1_d_luo = 15.0;

	hdm_2_width = 1.0;
	hdm_2_a_hen = 5.0;
	hdm_2_d_luo = 15.0;
}

CanShu_R_GongGong::~CanShu_R_GongGong()
{
}

CanShu_PD_DCC::CanShu_PD_DCC()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	dis_center = 1.0;
	ang_caoding = 30.0;

	type = 1;
	ang_n1 = 5.0;

	angle_heng_tui = 45.0;
	dis_end_extend = 0.8;

	angle_qiexue = 5.0;
}

CanShu_PD_DCC::~CanShu_PD_DCC()
{
}

int CanShu_PD_DCC::get_canshu_count()
{
	return 7;
}

CanShu_R_DaoJianJianXi::CanShu_R_DaoJianJianXi()
{
}

CanShu_R_DaoJianJianXi::~CanShu_R_DaoJianJianXi()
{
}

int CanShu_R_DaoJianJianXi::get_canshu_count()
{
	return 0;
}

CanShu_R_DaoJianFenXieCao::CanShu_R_DaoJianFenXieCao()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	dis_center =0.0;	
	ang_caoding=30.0;	

	type=1;
	ang_n1=10.0;

	angle_heng_tui=45.0;
	dis_end_extend=0.0;

	angle_qiexue = 5.0;
}

CanShu_R_DaoJianFenXieCao::~CanShu_R_DaoJianFenXieCao()
{
}

int CanShu_R_DaoJianFenXieCao::get_canshu_count()
{
	return 0;
}

CanShu_PD_DHDM_1::CanShu_PD_DHDM_1()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	//ang_a1 = 5.0;
	//ang_a2 = 3.0;
	//ang_a3 = 3.0;
	angle_qiexue = 5.0;
	angle_wy_luo = 0.0;	//位移角度
	dis_to_center = 0.0;	//到中心距离 
	dis_start_extend = 0.0;	//开始延长距离
}

CanShu_PD_DHDM_1::~CanShu_PD_DHDM_1()
{
}

int CanShu_PD_DHDM_1::get_canshu_count()
{
	return 6;
}

CanShu_PD_DHDM_2::CanShu_PD_DHDM_2()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;
	//ang_a1 = 5.0;
	//ang_a2 = 3.0;
	//ang_a3 = 0.1;
	angle_qiexue = 5.0;
	angle_wy_luo = 0.0;	//位移角度
	dis_to_center = 0.0;	//到中心距离 
	dis_start_extend = 0.0;	//开始延长距离
}

CanShu_PD_DHDM_2::~CanShu_PD_DHDM_2()
{
}

int CanShu_PD_DHDM_2::get_canshu_count()
{
	return 6;
}

CanShu_PD_DHDM_3::CanShu_PD_DHDM_3()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	ang_a1 = 5.0;
	//ang_a2 = 3.0;
	//ang_a3 = 0.1;
	angle_qiexue = 5.0;
}

CanShu_PD_DHDM_3::~CanShu_PD_DHDM_3()
{
}

int CanShu_PD_DHDM_3::get_canshu_count()
{
	return 6;
}

CanShu_PD_LXC::CanShu_PD_LXC()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	extend_start = 0.0;
	extend_end = 0.0;

	type = 0;
	ang_n1 = 5.0;

	type_xinhou = 1;
	angle_wy_deng = 5.0;
	percent_r = 0.7;
	angle_wy_start = 5.0;
	angle_wy_end = 5.0;

	angle_qiexue = 5.0;
}

CanShu_PD_LXC::~CanShu_PD_LXC()
{
}

int CanShu_PD_LXC::get_canshu_count()
{
	return 0;
}

CanShu_PD_HDM_1::CanShu_PD_HDM_1()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	//type_luo = 0;
	//ang_n_luo = 10.0;
	//ang_d_luo = 0.7;

	angle_qiexue_luo = 5.0;
	angle_wy_luo = 5.0;
}

CanShu_PD_HDM_1::~CanShu_PD_HDM_1()
{
}

int CanShu_PD_HDM_1::get_canshu_count()
{
	return 10;
}

CanShu_PD_HDM_2::CanShu_PD_HDM_2()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	//type_luo = 0;
	//ang_n_luo = 10.0;
	//ang_d_luo = 0.7;

	angle_qiexue_luo = 5.0;
	angle_wy_luo = 5.0;
}

CanShu_PD_HDM_2::~CanShu_PD_HDM_2()
{
}

int CanShu_PD_HDM_2::get_canshu_count()
{
	return 10;
}

CanShu_PD_HDM_3::CanShu_PD_HDM_3()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	//type_luo = 0;
	//ang_n_luo = 10.0;
	//ang_d_luo = 0.7;

	angle_qiexue_luo = 5.0;
	angle_wy_luo = 5.0;
}

CanShu_PD_HDM_3::~CanShu_PD_HDM_3()
{
}

int CanShu_PD_HDM_3::get_canshu_count()
{
	return 10;
}

CanShu_PD_DaoTiJianXi::CanShu_PD_DaoTiJianXi()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;
}

CanShu_PD_DaoTiJianXi::~CanShu_PD_DaoTiJianXi()
{
}

int CanShu_PD_DaoTiJianXi::get_canshu_count()
{
	return 7;
}

CanShu_R_QDM_R::CanShu_R_QDM_R()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	type = 1.0;
	ang_n1 = 5.0;
	angle_qiexue = 5.0;
}

CanShu_R_QDM_R::~CanShu_R_QDM_R()
{
}

int CanShu_R_QDM_R::get_canshu_count()
{
	return 7;
}

CanShu_R_HDM_1::CanShu_R_HDM_1()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	angle_qx_hen = 30.0;
	angle_wy_hen = 30.0;
	dis_to_center=0.0;
	dis_start_extend=0.0;

	angle_qx_rrr = 10.0;
	angle_wy_rrr = 5.0;

	angle_qx_luo = 5.0;
	angle_wy_luo = 0.0;
}

CanShu_R_HDM_1::~CanShu_R_HDM_1()
{
}

int CanShu_R_HDM_1::get_canshu_count()
{
	return 10;
}

CanShu_R_HDM_2::CanShu_R_HDM_2()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	angle_qx_hen = 30.0;
	angle_wy_hen = 30.0;
	dis_to_center = 0.0;
	dis_start_extend = 0.0;

	angle_qx_rrr = 10.0;
	angle_wy_rrr = 5.0;

	angle_qx_luo = 5.0;
	angle_wy_luo = 0.0;
}

CanShu_R_HDM_2::~CanShu_R_HDM_2()
{
}

int CanShu_R_HDM_2::get_canshu_count()
{
	return 10;
}

CanShu_R_HDM_3::CanShu_R_HDM_3()
{
	extend_start = 5.0;
	extend_end = 5.0;

	type_luo = 0;
	is_ding_luo = 5.0;

	ang_n1_luo = 0;
	ang_n2_luo = 5.0;
	ang_d_luo = 0.7;
	ang_a_luo = 5.0;
	angle_qiexue_luo = 5.0;

	angle_wy_luo = 5.0;
}

CanShu_R_HDM_3::~CanShu_R_HDM_3()
{
}

int CanShu_R_HDM_3::get_canshu_count()
{
	return 10;
}

CanShu_R_LXC::CanShu_R_LXC()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	extend_start = 0.0;
	extend_end = 0.0;

	type = 1;
	ang_n1 = 5.0;

	type_xinhou = 1;
	angle_wy_deng = 5.0;
	percent_r = 0.7;
	angle_wy_start = 5.0;
	angle_wy_end = 5.0;

	angle_qiexue = 5.0;
}

CanShu_R_LXC::~CanShu_R_LXC()
{
}

int CanShu_R_LXC::get_canshu_count()
{
	return 10;
}

CanShu_R_DaoTiJianXi::CanShu_R_DaoTiJianXi()
{
}

CanShu_R_DaoTiJianXi::~CanShu_R_DaoTiJianXi()
{
}

int CanShu_R_DaoTiJianXi::get_canshu_count()
{
	return 0;
}

int CanShu_CX_GongGong::get_canshu_count()
{
	return 3;
}

CanShu_CX_GongGong::CanShu_CX_GongGong()
{
	len_all = 100.123451;
	len_ren = 50.0;
	D_bing = 10.0;

	//ren_count = 0;
	//is_dengfen = true;
	//for (int i = 0; i < 6; i++)
	//{
	//	v_no_dengfen_angle[i] = 0.0;
	//}

	for (int i = 0; i < 30; i++)
	{
		v_sel_dxf_pos[i] = -1;
		//v_cur_ang_pos_to_dxf_index[i] = -1;

		v_type_cao[i]= -1;
		v_ang_zhuan[i]=0.0;
		v_ang_qing[i]=0.0;
		v_dis_pian[i]=0.0;
		v_ang_luo[i]=0.0;
		v_daocheng[i] =0.0;

		v_canshu_or_xingxian[i] = 0; 
		v_canshu_D[i] = 0.0;
		v_canshu_len[i] = 0.0;
		v_canshu_zhui[i] = 0.0;
		v_luoxuan_sel_xx_index[i] = -1;

		v_hdm_1_width[i] = 0.0;
		v_hdm_1_a_luo[i] = 0.0;
		v_hdm_1_d_luo[i] = 0.0;
		v_hdm_2_width[i] = 0.0;
		v_hdm_2_a_luo[i] = 0.0;
		v_hdm_2_d_luo[i] = 0.0;
		v_hdm_3_width[i] = 0.0;
		v_hdm_3_a_luo[i] = 0.0;
		v_hdm_3_d_luo[i] = 0.0;

		v_houjiao_sel_xx_index[i] = -1;
	}

	cai_type = 0;
	cai_len = 0.001;
	cai_ang = 0.001;
}

CanShu_CX_GongGong::~CanShu_CX_GongGong()
{
}

CanShu_GX_CX_KaiCao::CanShu_GX_CX_KaiCao()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	extend_start = 0.0;
	extend_end = 0.0;

	type = 0;
	ang_n1 = 5.0;
	ang_d = 10.0;

	type_xinhou = 1;
	angle_wy_deng = 5.0;
	percent_r = 0.7;
	angle_wy_start = 5.0;
	angle_wy_end = 5.0;

	angle_qiexue = 5.0;

}

CanShu_GX_CX_KaiCao::~CanShu_GX_CX_KaiCao()
{
}

CanShu_GX_CX_HDM_1::CanShu_GX_CX_HDM_1()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	fangfa = 0;

	angle_qiexue = 5.0;
	angle_wy = 5.0;
	angle_zhuan = 5.0;
	angle_baidong = 5.0;

	dis_start_extend = 0.0;//到中心距离
	dis_end_extend = 0.0;//开始延长距离 
}

CanShu_GX_CX_HDM_1::~CanShu_GX_CX_HDM_1()
{
}

CanShu_GX_CX_HDM_2::CanShu_GX_CX_HDM_2()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = 0;
	}
	angle_buchang = 0.0;

	fangfa = 0;

	angle_qiexue = 5.0;
	angle_wy = 5.0;
	angle_zhuan = 5.0;
	angle_baidong = 5.0;

	dis_start_extend = 0.0;//到中心距离
	dis_end_extend = 0.0;//开始延长距离 
}

CanShu_GX_CX_HDM_2::~CanShu_GX_CX_HDM_2()
{
}
