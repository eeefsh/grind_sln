#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include"Miller_GX_CanShu.h"
#include"Storage_manager.h"


CanShu_GX_KaiCao::CanShu_GX_KaiCao()
{
	pos_ang_qian = -1;
	guanlian_lx_id = -1; 
	//type_xinhou =0;	//0等比芯厚、1变比芯厚
	percent_start=0.5;//起始芯厚比（半径） 
	percent_end=0.5;

	//angle_qiexue=5.0;	//切削角度

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个 
}

CanShu_GX_KaiCao::~CanShu_GX_KaiCao()
{
}

void CanShu_GX_KaiCao::load(int pos)
{
	gx_cx_kaicao_can_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	pos_ang_qian = ls_row_data.pos_ang_qian;
	guanlian_lx_id = ls_row_data.lx_pos;
	percent_start = ls_row_data.percent_start;
	percent_end = ls_row_data.percent_end;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = ls_row_data.selected_ren[i];
	}

	CanShu_QianJiao ls_ang_qian;
	ls_ang_qian.load(pos);

	ang_qian = ls_ang_qian;
}

int CanShu_GX_KaiCao::save(int pos)
{
	ang_qian.luoxuan_order = guanlian_lx_id;
	pos_ang_qian = ang_qian.save(pos);

	gx_cx_kaicao_can_data ls_row_data;
	ls_row_data.pos_ang_qian = pos_ang_qian;
	ls_row_data.lx_pos = guanlian_lx_id;
	ls_row_data.percent_start = percent_start;
	ls_row_data.percent_end = percent_end;

	for (int i = 0; i < 6; i++)
	{
		ls_row_data.selected_ren[i] = selected_ren[i];
	}

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	return pos;
}


CanShu_GX_LXC::CanShu_GX_LXC()
{
	ang_d =0.0; //径向前角

	//type_xinhou=0;	//0等比芯厚、1变比芯厚
	percent_start=0.5;//起始芯厚比（半径） 
	percent_end=0.5;

	//angle_qiexue=5.0;	//切削角度

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_LXC::~CanShu_GX_LXC()
{
}

void CanShu_GX_LXC::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_LXC));
}

int CanShu_GX_LXC::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_LXC));
	return pos;
}


CanShu_GX_DCC_qiu::CanShu_GX_DCC_qiu()
{
	pos_b_qianjiao_n = -1;

	//dis_to_center =0.0;	//到中心距离 
	//dis_end_extend=0.0;	//结束延长距离

	high_up_o=0.0;	  //芯厚圆心上偏高度
	ang_up=60.0;	      //顶部角度--与x轴夹角
	percent_r=0.6;		//起始处半径比值
	ang_down=20.0;	  //柱面出线角度 与x轴夹角

	//angle_qiexue=5.0;	//切削角度
	//ang_n = 8.0;

	ang_hen_tui = 45.0;	//横向退刀
	dis_hen_tui = 0.5;	//横向退刀

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_DCC_qiu::~CanShu_GX_DCC_qiu()
{
}

int CanShu_GX_DCC_qiu::save(int pos)
{
	pos_b_qianjiao_n = b_qianjiao_n.save();

	gx_dcc_qiu_can_data ls_row_data;
	ls_row_data.pos_b_qianjiao_n = pos_b_qianjiao_n;
	//ls_row_data.dis_to_center = dis_to_center;
	//ls_row_data.dis_end_extend = dis_end_extend;
	ls_row_data.high_up_o = high_up_o;
	ls_row_data.ang_up = ang_up;
	ls_row_data.percent_r = percent_r;
	ls_row_data.ang_down = ang_down;
	//ls_row_data.angle_qiexue = angle_qiexue;
	ls_row_data.ang_hen_tui = ang_hen_tui;
	ls_row_data.dis_hen_tui = dis_hen_tui;
	for (int i = 0; i < 6; i++)
	{
		ls_row_data.selected_ren[i] = selected_ren[i];
	}

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void CanShu_GX_DCC_qiu::load(int pos)
{
	gx_dcc_qiu_can_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	pos_b_qianjiao_n = ls_row_data.pos_b_qianjiao_n;
	//dis_to_center = ls_row_data.dis_to_center;
	//dis_end_extend = ls_row_data.dis_end_extend;
	high_up_o = ls_row_data.high_up_o;
	ang_up = ls_row_data.ang_up;
	percent_r = ls_row_data.percent_r;
	ang_down = ls_row_data.ang_down;
	//angle_qiexue = ls_row_data.angle_qiexue;
	ang_hen_tui = ls_row_data.ang_hen_tui;
	dis_hen_tui = ls_row_data.dis_hen_tui;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = ls_row_data.selected_ren[i];
	}

	CanShu_Bian ls_mat;
	ls_mat.load(pos_b_qianjiao_n);
	b_qianjiao_n = ls_mat;

	//storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(*this));

}

CanShu_GX_DCC_ping::CanShu_GX_DCC_ping()
{
	//dis_to_center=0.0;	//到中心距离 

	ang_n=5.0;

	high_down=0.0;	//芯厚线起点，端面沿轴向下降高度
	ang_cao=30.0;	//与端平面夹角

	//angle_qiexue=5.0;	//切削角度

	ang_hen_tui=45.0;	//横向退刀
	dis_hen_tui=0.5;	//横向退刀

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}
CanShu_GX_DCC_ping::~CanShu_GX_DCC_ping()
{
}

int CanShu_GX_DCC_ping::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DCC_ping));
	return pos;
}

void CanShu_GX_DCC_ping::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DCC_ping));

}

CanShu_GX_DCC_yuanjiao::CanShu_GX_DCC_yuanjiao()
{
	ang_n=5.0;

	dis_to_center=0.0;	//交点到中心距离 
	ang_cao=45.0;	//与端平面夹角

	//angle_qiexue=5.0;	//切削角度

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_DCC_yuanjiao::~CanShu_GX_DCC_yuanjiao()
{
}

int CanShu_GX_DCC_yuanjiao::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DCC_yuanjiao));
	return pos;
}

void CanShu_GX_DCC_yuanjiao::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DCC_yuanjiao));

}

CanShu_GX_CX_HDM::CanShu_GX_CX_HDM()
{
	guanlian_lx_id=-1;
	guanlian_hj_id=-1;
	sel_hdm_id=0;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}
CanShu_GX_CX_HDM::~CanShu_GX_CX_HDM()
{
}

int CanShu_GX_CX_HDM::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_CX_HDM));
	return pos;
}

void CanShu_GX_CX_HDM::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_CX_HDM));
}

CanShu_GX_ZQ_HDM::CanShu_GX_ZQ_HDM()
{
	sel_hdm_id=0; // 0、1、2

	dis_to_center=0.0;	//到中心距离 

	angle_qiexue_qiu=35.0;	//切削角度
	angle_wy_qiu=30.0;	//位移角度- 后刀面法向正转为正

	pos_percent=0.5; //插值点的位置
	angle_qiexue_qiu2=20.0;	//切削角度
	angle_wy_qiu2=15.0;	//位移角度

	angle_qiexue_luo=5.0;	//切削角度
	angle_wy_luo=0.0;	//位移角度

	dis_end_extend=0.0;	//结束延长距离

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_ZQ_HDM::~CanShu_GX_ZQ_HDM()
{
}


int CanShu_GX_ZQ_HDM::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_ZQ_HDM));
	return pos;
}

void CanShu_GX_ZQ_HDM::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_ZQ_HDM));

}

CanShu_GX_PD_duan_HDM::CanShu_GX_PD_duan_HDM()
{
	sel_hdm_id=0; 

	angle_qiexue=5.0;	
	angle_wy_luo=0.0;	
	dis_to_center=0.0;	

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_PD_duan_HDM::~CanShu_GX_PD_duan_HDM()
{
}

int CanShu_GX_PD_duan_HDM::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_PD_duan_HDM));
	return pos;
}


void CanShu_GX_PD_duan_HDM::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_PD_duan_HDM));

}

CanShu_GX_PD_zhu_HDM::CanShu_GX_PD_zhu_HDM()
{
	sel_hdm_id = 0;

	angle_qiexue_luo = 5.0;
	angle_wy_luo = 0.0;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_PD_zhu_HDM::~CanShu_GX_PD_zhu_HDM()
{
}

int CanShu_GX_PD_zhu_HDM::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_PD_zhu_HDM));
	return pos;
}

void CanShu_GX_PD_zhu_HDM::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_PD_zhu_HDM));

}

CanShu_GX_R_HDM::CanShu_GX_R_HDM()
{
	sel_hdm_id=0; // 0、1、2、

	dis_to_center=0.0;	//到中心距离 

	angle_qx_hen=5.0;	//切削角度
	angle_wy_hen=0.0;	//位移角度

	angle_qx_rrr=5.0;	//切削角度
	angle_wy_rrr=0.0;	//位移角度

	angle_qx_luo=5.0;	//切削角度
	angle_wy_luo=0.0;	//位移角度

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_R_HDM::~CanShu_GX_R_HDM()
{
}

int CanShu_GX_R_HDM::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_R_HDM));
	return pos;
}

void CanShu_GX_R_HDM::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_R_HDM));
}


CanShu_GX_DJJX::CanShu_GX_DJJX()
{
	djjx_R =3.5; //圆弧半径
	djjx_ang_up=30.0; //圆弧起点与x轴夹角
	djjx_ang_down=30.0; //圆弧终点与z轴夹角

	djjx_ang_x =0.0; //圆弧中间点平移到原点绕基本轴旋转
	djjx_ang_y = 0.0;
	djjx_ang_z = 0.0;

	djjx_pianzhi_x= 0.0;//刀尖间隙圆弧球心偏置距离
	djjx_pianzhi_y= 0.0;
	djjx_pianzhi_z= 0.0;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_DJJX::~CanShu_GX_DJJX()
{
}
int CanShu_GX_DJJX::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DJJX));
	return pos;
}

void CanShu_GX_DJJX::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_DJJX));

}

bool XingCan_GX::set_CanShu_GX_LXC(CanShu_GX_LXC& in_ptr)
{
	if (can_lxc != nullptr)
	{
		delete can_lxc;
		can_lxc = nullptr;
	}
	can_lxc = new CanShu_GX_LXC(in_ptr);
	gx_type = 1;
	return true;
}

bool XingCan_GX::set_CanShu_GX_KaiCao(CanShu_GX_KaiCao& in_ptr)
{
	if (can_kc != nullptr)
	{
		delete can_kc;
	}
	can_kc = new CanShu_GX_KaiCao(in_ptr);
	gx_type = 0;
	return true;
}

bool XingCan_GX::set_CanShu_GX_DCC_qiu(CanShu_GX_DCC_qiu& in_ptr)
{
	if (can_dcc_qiu != nullptr)
	{
		delete can_dcc_qiu;
	}
	can_dcc_qiu = new CanShu_GX_DCC_qiu(in_ptr);
	gx_type = 2;
	return true;
}

bool XingCan_GX::set_CanShu_GX_DCC_ping(CanShu_GX_DCC_ping& in_ptr)
{
	if (can_dcc_ping != nullptr)
	{
		delete can_dcc_ping;
	}
	can_dcc_ping = new CanShu_GX_DCC_ping(in_ptr);
	gx_type = 3;
	return true;
}

bool XingCan_GX::set_CanShu_GX_DCC_yuanjiao(CanShu_GX_DCC_yuanjiao& in_ptr)
{
	if (can_dcc_yuan != nullptr)
	{
		delete can_dcc_yuan;
	}
	can_dcc_yuan = new CanShu_GX_DCC_yuanjiao(in_ptr);
	gx_type = 4;
	return true;
}

bool XingCan_GX::set_CanShu_GX_CX_HDM(CanShu_GX_CX_HDM& in_ptr)
{
	if (can_cx_hdm != nullptr)
	{
		delete can_cx_hdm;
	}
	can_cx_hdm = new CanShu_GX_CX_HDM(in_ptr);
	gx_type = 5;
	return true;
}

bool XingCan_GX::set_CanShu_GX_ZQ_HDM(CanShu_GX_ZQ_HDM& in_ptr)
{
	if (can_zq_hdm != nullptr)
	{
		delete can_zq_hdm;
	}
	can_zq_hdm = new CanShu_GX_ZQ_HDM(in_ptr);
	gx_type = 6;
	return true;
}

bool XingCan_GX::set_CanShu_GX_PD_duan_HDM(CanShu_GX_PD_duan_HDM& in_ptr)
{
	if (can_pd_duan_hdm != nullptr)
	{
		delete can_pd_duan_hdm;
	}
	can_pd_duan_hdm = new CanShu_GX_PD_duan_HDM(in_ptr);
	gx_type = 7;
	return true;
}

bool XingCan_GX::set_CanShu_GX_PD_zhu_HDM(CanShu_GX_PD_zhu_HDM& in_ptr)
{
	if (can_pd_zhu_hdm != nullptr)
	{
		delete can_pd_zhu_hdm;
	}
	can_pd_zhu_hdm = new CanShu_GX_PD_zhu_HDM(in_ptr);
	gx_type = 8;
	return true;
}

bool XingCan_GX::set_CanShu_GX_R_HDM(CanShu_GX_R_HDM& in_ptr)
{
	if (can_r_hdm != nullptr)
	{
		delete can_r_hdm;
	}
	can_r_hdm = new CanShu_GX_R_HDM(in_ptr);
	gx_type = 9;
	return true;
}


bool XingCan_GX::set_CanShu_GX_DJJX(CanShu_GX_DJJX& in_ptr)
{
	if (can_djjx != nullptr)
	{
		delete can_djjx;
	}
	can_djjx = new CanShu_GX_DJJX(in_ptr);
	gx_type = 10;
	return true;
}

bool XingCan_GX::set_CanShu_GX_KaiCao_2(CanShu_GX_KaiCao_2& in_ptr)
{
	if (can_kc_2 != nullptr)
	{
		delete can_kc_2;
	}
	can_kc_2 = new CanShu_GX_KaiCao_2(in_ptr);
	gx_type = 11;
	return true;
}

XingCan_GX::XingCan_GX()
{
	gx_type = -1;

	can_kc=nullptr;
	can_lxc=nullptr;
	can_dcc_qiu=nullptr;
	can_dcc_ping=nullptr;
	can_dcc_yuan=nullptr;
	can_cx_hdm=nullptr;
	can_zq_hdm=nullptr;
	can_pd_duan_hdm=nullptr;
	can_pd_zhu_hdm=nullptr;
	can_r_hdm=nullptr;
	can_djjx=nullptr;
	can_kc_2=nullptr;
}

XingCan_GX::~XingCan_GX()
{
	//
	if (can_kc != nullptr)
	{
		delete can_kc;
	}
	if (can_lxc != nullptr)
	{
		delete can_lxc;
		can_lxc = nullptr;
	}
	if (can_dcc_qiu != nullptr)
	{
		delete can_dcc_qiu;
	}
	if (can_dcc_ping != nullptr)
	{
		delete can_dcc_ping;
	}
	if (can_dcc_yuan != nullptr)
	{
		delete can_dcc_yuan;
	}
	if (can_cx_hdm != nullptr)
	{
		delete can_cx_hdm;
	}
	if (can_zq_hdm != nullptr)
	{
		delete can_zq_hdm;
	}
	if (can_pd_duan_hdm != nullptr)
	{
		delete can_pd_duan_hdm;
	}
	if (can_pd_zhu_hdm != nullptr)
	{
		delete can_pd_zhu_hdm;
	}
	if (can_r_hdm != nullptr)
	{
		delete can_r_hdm;
	}
	if (can_djjx != nullptr)
	{
		delete can_djjx;
	}
}

XingCan_GX::XingCan_GX(int in_type)
{
}

CanShu_GX_KaiCao_2::CanShu_GX_KaiCao_2()
{
	pos_ang_qian = -1;
	guanlian_lx_id = -1;

	start_len = 0.0;
	start_R = 1.0;
	end_len = 10.0;
	end_R = 5.0;

	type_xinhou = 0;	//0拉伸面、1回转面
	len_lashen = 5.0; //Z方向双向拉伸
	len_huizhuan_pianyi = 0.0; //回转轴偏移，y方向可以为负
	ang_huizhuan = 30.0; //回转角度双向
	
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1;
	}
	selected_ren[0] = 1; //默认选择第一个
}

CanShu_GX_KaiCao_2::~CanShu_GX_KaiCao_2()
{
}

int CanShu_GX_KaiCao_2::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(
		storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_KaiCao_2)
	);
	return pos;
}

void CanShu_GX_KaiCao_2::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_gx_data, pos, (char*)&*this, sizeof(CanShu_GX_KaiCao_2));
}
