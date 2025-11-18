#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Miller_GX_Obj.h"


inline Miller_GX_LXC::Miller_GX_LXC(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_LXC::Miller_GX_LXC()
{
}

void Miller_GX_LXC::set_gx_canshu(CanShu_GX_LXC& in_canshu)
{
	base_data = in_canshu;
}

inline void Miller_GX_LXC::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数: 设置完整

inline void Miller_GX_LXC::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
	Miller_Mo_QDM::base_data = in_mo;
}

void Miller_GX_LXC::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
}

void Miller_GX_LXC::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->get_luoxuancao_lx_id();
	ls_input.type = 1;
	ls_input.b_qianjiao_r.insert_element(0.0, base_data.ang_d);
	ls_input.b_qianjiao_r.insert_element(1.0, base_data.ang_d);

	ls_obj_mian.set_base_data(ls_input);

	//工序刀指针给临时计算对象访问数据 7.18
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

void Miller_GX_LXC::init_xinhou()
{
	//取刀具参数中的螺旋角 9.17
	CanShu_Geo_ZQ ls_tool_can;
	ptr_tool->get_cur_tool_canshu(ls_tool_can);

	Cal_XinHouMian ls_obj;

	//构造面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = 1;
	ls_input.type_line = 1;
	ls_input.type_cao = 0; //螺旋槽
	

	{
		vec p_end = obj_mian.BG_P(obj_mian.n_P() - 1);
		ls_input.len = p_end(0); //轴向长度 取x

		vec p_start = obj_mian.BG_P(0);
		//p_start(2) = 0.0;
		double tool_R = ptr_tool->get_D() / 2.0;
		ls_input.start_R = tool_R * base_data.percent_start;

		double delta_R = norm(p_start) * (base_data.percent_end - base_data.percent_start);
		double ls_zhui = 0.0;
		if (delta_R > 0.0)
		{
			ls_zhui = tcDegree(atan(delta_R / ls_input.len));
		}
		ls_input.ang_zhui = ls_zhui;

		ls_input.ang_luo = ls_tool_can.ang_luoxuan;
	}

	ls_input.len_lashen = 0.0;
	ls_input.len_huizhuan_pianyi = 0.0;
	ls_input.ang_huizhuan = 170.0;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

int Miller_GX_LXC::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_LXC::load(int pos)
{
	Miller_Mo_QDM::load(pos);

	CanShu_GX_LXC ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}



void Miller_GX_LXC::get_canshu(CanShu_GX_LXC& ans)
{
	ans = base_data;
}

void Miller_GX_LXC::set_canshu(CanShu_GX_LXC& ptr)
{
	
	//self_xingcan->set_CanShu_GX_LXC(ptr);
}

void Miller_GX_LXC::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_lxc);
	//if (self_xingcan != nullptr)
	//{
	//	delete self_xingcan;
	//	self_xingcan = nullptr;
	//}
	////self_xingcan = ptr;
}


void Miller_GX_LXC::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_QDM_data();
	if (error_message_global != 0)
	{
		return;
	}
	init_xinhou();
}

//5.0-构造

int Miller_GX_KaiCao::get_lx_id()
{
	return base_data.guanlian_lx_id;
}

inline void Miller_GX_KaiCao::init_guanxi()
{
	if (base_data.guanlian_lx_id != -1)
	{
		int lx_show_order = ptr_tool->ptr_list_lx->base_data.get_show_index_by_id(base_data.guanlian_lx_id);

		ptr_lx = ptr_tool->ptr_list_lx->get_obj(lx_show_order);
		if (ptr_lx != nullptr)
		{
			ptr_lx->add_guanxi_GL_GX(this);
		}
	}
}

inline Miller_GX_KaiCao::Miller_GX_KaiCao(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_KaiCao::Miller_GX_KaiCao()
{
}

//5.1-设置工序参数：

inline void Miller_GX_KaiCao::set_gx_canshu(CanShu_GX_KaiCao& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_KaiCao::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

//inline void Miller_GX_KaiCao::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
//{
//	mo_canshu = in_mo;
//}
//
//void Miller_GX_KaiCao::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
//{
//}

void Miller_GX_KaiCao::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}

	gen_QDM_data();

	if (error_message_global != 0)
	{
		return;
	}

	init_xinhou();
}

inline void Miller_GX_KaiCao::speak_father_del_guanxi()
{
	if (ptr_lx != nullptr)
	{
		ptr_lx->del_guanxi_GL_GX(this);
	}
}

void Miller_GX_KaiCao::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->ptr_list_lx->base_data.
		get_show_index_by_id(base_data.guanlian_lx_id);
	ls_input.type = 0;
	ls_input.b_qianjiao_r = base_data.ang_qian.b_qianjiao_r;
	ls_input.b_qianjiao_n = base_data.ang_qian.b_qianjiao_n;
	ls_obj_mian.set_base_data(ls_input);
	//工序刀指针给临时计算对象访问数据 7.18
	ls_obj_mian.ptr_tool = ptr_tool;

	//设置范围和采样参数 25.11.12
	double start = Miller_Mo_QDM::base_data.get_range_start();
	double end = Miller_Mo_QDM::base_data.get_range_end();
	ls_obj_mian.set_Range(start, end);
	double len = Miller_Mo_QDM::base_data.get_sample_len(flag_cal_prog);
	double ang = Miller_Mo_QDM::base_data.get_sample_ang(flag_cal_prog);
	ls_obj_mian.set_Sample(len, ang);


	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

void Miller_GX_KaiCao::init_xinhou()
{
	Cal_XinHouMian ls_obj;

	//构造面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = 1;
	ls_input.type_line = 1;
	ls_input.type_cao = 0; //螺旋槽
	
	{
		vec p_end = obj_mian.BG_P(obj_mian.n_P() - 1);
		ls_input.len = p_end(0); //轴向长度 取x

		vec p_start = obj_mian.BG_P(0);
		p_start(2) = 0.0;
		ls_input.start_R = norm(p_start) * base_data.percent_start;

		double delta_R = norm(p_start) * (base_data.percent_end - base_data.percent_start);
		double ls_zhui = tcDegree(atan(delta_R / ls_input.len));
		ls_input.ang_zhui = ls_zhui;
		ls_input.ang_luo = 0.0;
	}

	ls_input.len_lashen = 0.0;
	ls_input.len_huizhuan_pianyi = 0.0;
	ls_input.ang_huizhuan = 170.0;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

//int Miller_GX_KaiCao::save(int pos)
//{
//	//工序对象
//	gx_obj_data ls_row_data;
//	ls_row_data.type = type_gx;
//	ls_row_data.name = pos;
//	ls_row_data.shalun_id = shalun_id;
//	storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_gx_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//	
//	//工序参数
//	base_data.pos = pos;
//	base_data.save(int pos);
//
//	//磨削参数
//	
//	mo_canshu.save(int pos);;
//
//	return pos;
//}

void Miller_GX_KaiCao::load(int pos)
{
	//
	Miller_Mo_QDM::load(pos);


	CanShu_GX_KaiCao ls_base;
	ls_base.load(pos);
	base_data = ls_base;
	
}

int Miller_GX_KaiCao::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}



void Miller_GX_KaiCao::get_canshu(CanShu_GX_KaiCao& ans)
{
	ans = base_data;
}

void Miller_GX_KaiCao::set_canshu(CanShu_GX_KaiCao& canshu)
{
	
	//self_xingcan->set_CanShu_GX_KaiCao(canshu);
}

void Miller_GX_KaiCao::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_kc); 
	////self_xingcan = ptr;
}


//5.0-构造

inline Miller_GX_DCC_qiu::Miller_GX_DCC_qiu(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_DCC_qiu::Miller_GX_DCC_qiu()
{
}

//5.1-设置工序参数：
//不提成统一形参接口???

inline void Miller_GX_DCC_qiu::set_gx_canshu(CanShu_GX_DCC_qiu& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_DCC_qiu::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

inline void Miller_GX_DCC_qiu::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
	Miller_Mo_QDM::base_data = in_mo;
}

void Miller_GX_DCC_qiu::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
}

void Miller_GX_DCC_qiu::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_QDM_data();

	if (error_message_global != 0)
	{
		return;
	}
	init_xinhou();
}

void Miller_GX_DCC_qiu::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->get_duanchicao_lx_id();
	ls_input.type = 0;
	ls_input.b_qianjiao_n = base_data.b_qianjiao_n;

	ls_obj_mian.set_base_data(ls_input);
	ls_obj_mian.ptr_tool = ptr_tool;
	//ls_obj_mian.luo_or_duan = 1; //不用改变前刀面计算，砂轮优化里有逆路径
	ls_obj_mian.init_data();

	//
	Reverse_flag = 1;
	obj_mian = ls_obj_mian;
}

void Miller_GX_DCC_qiu::init_xinhou()
{
	Cal_XinHouMian ls_obj;

	//构造面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = 1;
	ls_input.type_line = 1;
	ls_input.type_cao = 2; //球头槽

	//vec p_end = obj_mian.BG_P(obj_mian.n_P() - 1);
	double qiu_R = ptr_tool->get_D() / 2.0;

	ls_input.r_qiu = qiu_R;
	ls_input.r_xin = qiu_R * base_data.percent_r;

	ls_input.high_o = base_data.high_up_o;
	ls_input.ang_up = base_data.ang_up;
	ls_input.ang_down = base_data.ang_down;

	ls_input.len_lashen = 0.0;
	ls_input.len_huizhuan_pianyi = 0.0;
	ls_input.ang_huizhuan = 170.0;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

int Miller_GX_DCC_qiu::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_DCC_qiu::load(int pos)
{
	//
	Miller_Mo_QDM::load(pos);
	//
	CanShu_GX_DCC_qiu ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}



void Miller_GX_DCC_qiu::get_canshu(CanShu_GX_DCC_qiu& ans)
{
	ans = base_data;
}

void Miller_GX_DCC_qiu::set_canshu(CanShu_GX_DCC_qiu& ptr)
{
	
	//self_xingcan->set_CanShu_GX_DCC_qiu(ptr);
}

void Miller_GX_DCC_qiu::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_dcc_qiu);
	////self_xingcan = ptr;
}

//5.0-构造

inline Miller_GX_DCC_ping::Miller_GX_DCC_ping(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_DCC_ping::Miller_GX_DCC_ping()
{
}

//5.1-设置工序参数：
//不提成统一形参接口???

inline void Miller_GX_DCC_ping::set_gx_canshu(CanShu_GX_DCC_ping& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_DCC_ping::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

inline void Miller_GX_DCC_ping::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
	Miller_Mo_QDM::base_data = in_mo;
}

void Miller_GX_DCC_ping::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
}

void Miller_GX_DCC_ping::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_QDM_data();

	if (error_message_global != 0)
	{
		return;
	}
	init_xinhou();
}

void Miller_GX_DCC_ping::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->get_duanchicao_lx_id();
	ls_input.type = 0;
	ls_input.b_qianjiao_r.insert_element(0.0, base_data.ang_n);
	ls_input.b_qianjiao_r.insert_element(1.0, base_data.ang_n);


	ls_obj_mian.set_base_data(ls_input);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	Reverse_flag = 1;
	obj_mian = ls_obj_mian;
}

void Miller_GX_DCC_ping::init_xinhou()
{
	Cal_XinHouMian ls_obj;

	//构造面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = 0;
	ls_input.type_line = 1;
	ls_input.type_cao = 1; //平底端齿槽

	ls_input.high_up = base_data.high_down;
	ls_input.ang_cao = base_data.ang_cao;

	ls_input.len_lashen = 10.0;
	ls_input.len_huizhuan_pianyi = 0.0;
	ls_input.ang_huizhuan = 0.0;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

//int Miller_GX_DCC_ping::save(int pos);
//{
//	gx_obj_data ls_row_data;
//	ls_row_data.type = type_gx;
//	ls_row_data.name = pos;
//	ls_row_data.shalun_id = shalun_id;
//	storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_gx_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	//工序参数
//	base_data.pos = pos;
//	base_data.save(int pos);;
//
//	//磨削参数
//	
//	mo_canshu.save(int pos);;
//
//	return pos;
//}

void Miller_GX_DCC_ping::load(int pos)
{
	//
	Miller_Mo_QDM::load(pos);
	//
	CanShu_GX_DCC_ping ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

int Miller_GX_DCC_ping::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}


void Miller_GX_DCC_ping::get_canshu(CanShu_GX_DCC_ping& ans)
{
	ans = base_data;
}

void Miller_GX_DCC_ping::set_canshu(CanShu_GX_DCC_ping& ptr)
{
	
	//self_xingcan->set_CanShu_GX_DCC_ping(ptr);
}

void Miller_GX_DCC_ping::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_dcc_ping);
	//self_xingcan = ptr;
}

//5.0-构造

inline Miller_GX_DCC_yuanjiao::Miller_GX_DCC_yuanjiao(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_DCC_yuanjiao::Miller_GX_DCC_yuanjiao()
{
}

//5.1-设置工序参数：

inline void Miller_GX_DCC_yuanjiao::set_gx_canshu(CanShu_GX_DCC_yuanjiao& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_DCC_yuanjiao::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

inline void Miller_GX_DCC_yuanjiao::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
	Miller_Mo_QDM::base_data = in_mo;
}

void Miller_GX_DCC_yuanjiao::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
}

void Miller_GX_DCC_yuanjiao::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_QDM_data();

	if (error_message_global != 0)
	{
		return;
	}
	init_xinhou();
}

void Miller_GX_DCC_yuanjiao::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->get_yuanjiaocao_lx_id();
	ls_input.type = 0;
	ls_input.b_qianjiao_r.insert_element(0.0, base_data.ang_n);
	ls_input.b_qianjiao_r.insert_element(1.0, base_data.ang_n);


	ls_obj_mian.set_base_data(ls_input);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

void Miller_GX_DCC_yuanjiao::init_xinhou()
{
	Cal_XinHouMian ls_obj;

	//构造面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = 1;
	ls_input.type_line = 1;
	ls_input.type_cao = 3; 

	ls_input.r_xin_p = base_data.dis_to_center;
	ls_input.ang_p = base_data.ang_cao;

	ls_input.len_lashen = 0.0;
	ls_input.len_huizhuan_pianyi = 0.0;
	ls_input.ang_huizhuan = 170.0;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

void Miller_GX_DCC_yuanjiao::load(int pos)
{
	//
	Miller_Mo_QDM::load(pos);
	//
	CanShu_GX_DCC_yuanjiao ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

int Miller_GX_DCC_yuanjiao::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}


void Miller_GX_DCC_yuanjiao::get_canshu(CanShu_GX_DCC_yuanjiao& ans)
{
	ans = base_data;
}

void Miller_GX_DCC_yuanjiao::set_canshu(CanShu_GX_DCC_yuanjiao& ptr)
{
	
	//self_xingcan->set_CanShu_GX_DCC_yuanjiao(ptr);
}

void Miller_GX_DCC_yuanjiao::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_dcc_yuan);
	//self_xingcan = ptr;
}

//5.0-构造

int Miller_GX_CX_HDM::get_hj_id()
{
	return base_data.guanlian_hj_id;
}

int Miller_GX_CX_HDM::get_lx_id()
{
	return base_data.guanlian_lx_id;
}

void Miller_GX_CX_HDM::init_guanxi()
{
	if (base_data.guanlian_hj_id != -1)
	{
		int hj_show_order = ptr_tool->ptr_list_hj->base_data.get_show_index_by_id(base_data.guanlian_hj_id);

		ptr_hj = ptr_tool->ptr_list_hj->get_obj(hj_show_order);

		if (ptr_hj != nullptr)
		{
			ptr_hj->add_guanxi_GL_GX(this);
		}
	}

	if (base_data.guanlian_lx_id != -1)
	{
		int lx_show_order = ptr_tool->ptr_list_lx->base_data.get_show_index_by_id(base_data.guanlian_lx_id);
		ptr_lx = ptr_tool->ptr_list_lx->get_obj(lx_show_order);
		if (ptr_lx != nullptr)
		{
			ptr_lx->add_guanxi_GL_GX(this);
		}
	}
}

void Miller_GX_CX_HDM::speak_father_del_guanxi()
{
	if (ptr_lx != nullptr)
	{
		ptr_lx->del_guanxi_GL_GX(this);
	}
	if (ptr_hj != nullptr)
	{
		ptr_hj->del_guanxi_GL_GX(this);
	}


}

inline Miller_GX_CX_HDM::Miller_GX_CX_HDM(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_CX_HDM::Miller_GX_CX_HDM()
{
}

//5.1-设置工序参数：

inline void Miller_GX_CX_HDM::set_gx_canshu(CanShu_GX_CX_HDM& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_CX_HDM::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

void Miller_GX_CX_HDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

inline void Miller_GX_CX_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_CX_HDM::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();

}

void Miller_GX_CX_HDM::gen_HDM_data()
{
	Cal_HDM ls_obj_mian;
	//构造面需要的参数
	int ls_lx_order = ptr_tool->ptr_list_lx->base_data.get_show_index_by_id(base_data.guanlian_lx_id) ;
	int ls_hj_order = ptr_tool->ptr_list_hj->base_data.get_show_index_by_id(base_data.guanlian_hj_id);
	ls_obj_mian.set_base_data(ls_lx_order, ls_hj_order);

	//设置范围和采样参数 25.11.12
	double start = Miller_Mo_HDM::base_data.get_range_start();
	double end = Miller_Mo_HDM::base_data.get_range_end();
	ls_obj_mian.set_Range(start, end);
	double len = Miller_Mo_HDM::base_data.get_sample_len(flag_cal_prog);
	double ang = Miller_Mo_HDM::base_data.get_sample_ang(flag_cal_prog);
	ls_obj_mian.set_Sample(len, ang);

	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.need_jiao_hdm = 1;
	ls_obj_mian.init_data();

	if (error_message_global != 0)
	{
		return;
	}

	obj_mian = ls_obj_mian;

	sel_hdm_id = base_data.sel_hdm_id;
}

void Miller_GX_CX_HDM::load(int pos)
{
	Miller_Mo_HDM::load(pos);

	CanShu_GX_CX_HDM ls_base;
	ls_base.load(pos);
	base_data = ls_base;	
}

int Miller_GX_CX_HDM::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}


void Miller_GX_CX_HDM::get_canshu(CanShu_GX_CX_HDM& ans)
{
	ans = base_data;
}

void Miller_GX_CX_HDM::set_canshu(CanShu_GX_CX_HDM& ptr)
{
	
	//self_xingcan->set_CanShu_GX_CX_HDM(ptr);
}

void Miller_GX_CX_HDM::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_cx_hdm);
	//self_xingcan = ptr;
}

//5.0-构造

inline Miller_GX_ZQ_HDM::Miller_GX_ZQ_HDM(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_ZQ_HDM::Miller_GX_ZQ_HDM()
{
}

//5.1-设置工序参数：

inline void Miller_GX_ZQ_HDM::set_gx_canshu(CanShu_GX_ZQ_HDM& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_ZQ_HDM::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

void Miller_GX_ZQ_HDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

inline void Miller_GX_ZQ_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_ZQ_HDM::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();

	//在计算后刀面后处理前，根据工序参数构造出，插值数组 8.16
	//拿不到工序参数，工序派生类构造数据
	{
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_isbian = 1;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_isbian = 1;

		//根据计算好的面，计算对应长度的对应值
		double pos_0 = 0.0;
		double qx_0 = base_data.angle_qiexue_qiu;
		double wy_0 = base_data.angle_wy_qiu;

		double pos_1 = 0.0;
		double qx_1 = base_data.angle_qiexue_qiu2;
		double wy_1 = base_data.angle_wy_qiu2;

		double pos_2 = 0.0;
		double qx_2 = base_data.angle_qiexue_luo;
		double wy_2 = base_data.angle_wy_luo;

		double pos_3 = 1.0;
		double qx_3 = base_data.angle_qiexue_luo;
		double wy_3 = base_data.angle_wy_luo;

		double tool_R = ptr_tool->get_D() / 2.0;
		int count_p = obj_mian.n_P();
		for (int i = 0; i < count_p; i++)
		{
			vec ls_p = { -1.0,-1.0,-1.0 };
			if (base_data.sel_hdm_id == 0)
			{
				ls_p = obj_mian.HJ1_P(i);
			}
			else
			{
				ls_p = obj_mian.HJ2_P(i);
			}

			if (ls_p(0) > tool_R)
			{
				pos_2 = obj_mian.Lenth_At_Point(i) / obj_mian.Lenth_At_Point(count_p - 1); //长度百分比 8.16
				break;
			}
		}
		pos_1 = pos_2 * base_data.pos_percent;

		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.reset();
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.reset();

		vec qx_b_0 = { pos_0 ,qx_0 };
		vec qx_b_1 = { pos_1 ,qx_1 };
		vec qx_b_2 = { pos_2 ,qx_2 };
		vec qx_b_3 = { pos_3 ,qx_3 };
		vec wy_b_0 = { pos_0 ,wy_0 };
		vec wy_b_1 = { pos_1 ,wy_1 };
		vec wy_b_2 = { pos_2 ,wy_2 };
		vec wy_b_3 = { pos_3 ,wy_3 };
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_0);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_1);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_2);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_3);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_0);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_1);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_2);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_3);

	}
	
}

void Miller_GX_ZQ_HDM::gen_HDM_data()
{
	//确定磨面的方法 8.20 
	Miller_Mo_HDM::base_data.fangfa.type = 2;

	Cal_HDM ls_obj_mian;

	//构造面需要的参数
	int ls_lx_id = ptr_tool->get_hdm_lx_id();
	int ls_hj_id = ptr_tool->get_hdm_hj_id();
	sel_hdm_id = base_data.sel_hdm_id;

	ls_obj_mian.set_base_data(ls_lx_id, ls_hj_id);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

void Miller_GX_ZQ_HDM::load(int pos)
{
	//
	Miller_Mo_HDM::load(pos);
	//
	CanShu_GX_ZQ_HDM ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

int Miller_GX_ZQ_HDM::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_ZQ_HDM::get_canshu(CanShu_GX_ZQ_HDM& ans)
{
	ans = base_data;
}

void Miller_GX_ZQ_HDM::set_canshu(CanShu_GX_ZQ_HDM& ptr)
{
	
	//self_xingcan->set_CanShu_GX_ZQ_HDM(ptr);
}

void Miller_GX_ZQ_HDM::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_zq_hdm);
	//self_xingcan = ptr;
}


//5.1-设置工序参数：


//5.0-构造

inline Miller_GX_PD_duan_HDM::Miller_GX_PD_duan_HDM(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_PD_duan_HDM::Miller_GX_PD_duan_HDM()
{
}

inline void Miller_GX_PD_duan_HDM::set_gx_canshu(CanShu_GX_PD_duan_HDM& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_PD_duan_HDM::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

void Miller_GX_PD_duan_HDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

inline void Miller_GX_PD_duan_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_PD_duan_HDM::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();

	//在计算后刀面后处理前，根据工序参数构造出，插值数组
	//拿不到工序参数，工序派生类构造数据
	{
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_isbian = 0;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_isbian = 0;

		//根据计算好的面，计算对应长度的对应值
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX = base_data.angle_qiexue;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY = base_data.angle_wy_luo;
	}
}

void Miller_GX_PD_duan_HDM::gen_HDM_data()
{
	//确定磨面的方法 8.20 
	Miller_Mo_HDM::base_data.fangfa.type = 2;

	Cal_HDM ls_obj_mian;

	//构造面需要的参数
	int ls_lx_id = ptr_tool->get_hdm_pd_duan_lx_id();
	int ls_hj_id = ptr_tool->get_hdm_pd_duan_hj_id();
	sel_hdm_id = base_data.sel_hdm_id;

	ls_obj_mian.set_base_data(ls_lx_id, ls_hj_id);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.luo_or_duan = 1;
	ls_obj_mian.init_data();

	Reverse_flag = 1;
	obj_mian = ls_obj_mian;
}

void Miller_GX_PD_duan_HDM::load(int pos)
{
	Miller_Mo_HDM::load(pos);

	CanShu_GX_PD_duan_HDM ls_base;
	ls_base.load(pos);
	base_data = ls_base;
	
}

int Miller_GX_PD_duan_HDM::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_PD_duan_HDM::get_canshu(CanShu_GX_PD_duan_HDM& ans)
{
	ans = base_data;
}

void Miller_GX_PD_duan_HDM::set_canshu(CanShu_GX_PD_duan_HDM& ptr)
{
	
	//self_xingcan->set_CanShu_GX_PD_duan_HDM(ptr);
}

void Miller_GX_PD_duan_HDM::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_pd_duan_hdm);
	//self_xingcan = ptr;
}

//5.0-构造

inline Miller_GX_PD_zhu_HDM::Miller_GX_PD_zhu_HDM(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_PD_zhu_HDM::Miller_GX_PD_zhu_HDM()
{
}

//5.1-设置工序参数：

inline void Miller_GX_PD_zhu_HDM::set_gx_canshu(CanShu_GX_PD_zhu_HDM& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_PD_zhu_HDM::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

void Miller_GX_PD_zhu_HDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

inline void Miller_GX_PD_zhu_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_PD_zhu_HDM::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();

	//在计算后刀面后处理前，根据工序参数构造出，插值数组
	//拿不到工序参数，工序派生类构造数据
	{
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_isbian = 0;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_isbian = 0;

		//根据计算好的面，计算对应长度的对应值
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX = base_data.angle_qiexue_luo;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY = base_data.angle_wy_luo;
	}
}

void Miller_GX_PD_zhu_HDM::gen_HDM_data()
{
	//确定磨面的方法 8.20 
	Miller_Mo_HDM::base_data.fangfa.type = 2;

	Cal_HDM ls_obj_mian;

	//构造面需要的参数
	int ls_lx_id = ptr_tool->get_hdm_pd_zhu_lx_id();
	int ls_hj_id = ptr_tool->get_hdm_pd_zhu_hj_id();
	sel_hdm_id = base_data.sel_hdm_id;

	ls_obj_mian.set_base_data(ls_lx_id, ls_hj_id);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

//int Miller_GX_PD_zhu_HDM::save(int pos);
//{
//	//工序对象
//	gx_obj_data ls_row_data;
//	ls_row_data.type = type_gx;
//	ls_row_data.name = pos;
//	ls_row_data.shalun_id = shalun_id;
//	storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_gx_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	//工序参数
//	base_data.pos = pos;
//	base_data.save(int pos);;
//
//	//磨削参数
//	
//	mo_canshu.save(int pos);;
//
//	return pos;
//}
//
void Miller_GX_PD_zhu_HDM::load(int pos)
{
	Miller_Mo_HDM::load(pos);

	CanShu_GX_PD_zhu_HDM ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

int Miller_GX_PD_zhu_HDM::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}


void Miller_GX_PD_zhu_HDM::get_canshu(CanShu_GX_PD_zhu_HDM& ans)
{
	ans = base_data;
}

void Miller_GX_PD_zhu_HDM::set_canshu(CanShu_GX_PD_zhu_HDM& ptr)
{
	
	//self_xingcan->set_CanShu_GX_PD_zhu_HDM(ptr);
}

void Miller_GX_PD_zhu_HDM::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_pd_zhu_hdm);
	//self_xingcan = ptr;
}


//5.0-构造

inline Miller_GX_R_HDM::Miller_GX_R_HDM(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_R_HDM::Miller_GX_R_HDM()
{
}

//5.1-设置工序参数：

inline void Miller_GX_R_HDM::set_gx_canshu(CanShu_GX_R_HDM& in_canshu)
{
	base_data = in_canshu;
}

//5.1-选砂轮: 基类写纯虚函数，保证派生类设置流程的完整

inline void Miller_GX_R_HDM::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

//5.2-设置磨削参数

void Miller_GX_R_HDM::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

inline void Miller_GX_R_HDM::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_R_HDM::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();

	//在计算后刀面后处理前，根据工序参数构造出，插值数组 8.21
	//拿不到工序参数，工序派生类构造数据
	{
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_isbian = 1;
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_isbian = 1;

		//根据计算好的面，计算对应长度的对应值
		double pos_0 = 0.0;
		double qx_0 = base_data.angle_qx_hen;
		double wy_0 = base_data.angle_wy_hen;

		double pos_1 = 0.0;
		double qx_1 = base_data.angle_qx_rrr;
		double wy_1 = base_data.angle_wy_rrr;

		double pos_2 = 0.0;
		double qx_2 = base_data.angle_qx_luo;
		double wy_2 = base_data.angle_wy_luo;

		double pos_3 = 1.0;
		double qx_3 = base_data.angle_qx_luo;
		double wy_3 = base_data.angle_wy_luo;

		double tool_R = ptr_tool->get_D() / 2.0;
		double rrr_R = ptr_tool->get_rrr();
		int count_p = obj_mian.n_P();
		for (int i = 0; i < count_p; i++)
		{
			vec ls_p = { -1.0,-1.0,-1.0 };
			if (base_data.sel_hdm_id == 0)
			{
				ls_p = obj_mian.HJ1_P(i);
			}
			else
			{
				ls_p = obj_mian.HJ2_P(i);
			}

			if (ls_p(1) > tool_R - rrr_R)
			{
				pos_1 = obj_mian.Lenth_At_Point(i) / obj_mian.Lenth_At_Point(count_p - 1); //长度百分比 
				//break;
			}
			if (ls_p(0) > rrr_R && ls_p(1) > tool_R - rrr_R)
			{
				pos_2 = obj_mian.Lenth_At_Point(i) / obj_mian.Lenth_At_Point(count_p - 1); //长度百分比 
				break;
			}
		}

		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.reset();
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.reset();

		vec qx_b_0 = { pos_0 ,qx_0 };
		vec qx_b_1 = { pos_1 ,qx_1 };
		vec qx_b_2 = { pos_2 ,qx_2 };
		vec qx_b_3 = { pos_3 ,qx_3 };
		vec wy_b_0 = { pos_0 ,wy_0 };
		vec wy_b_1 = { pos_1 ,wy_1 };
		vec wy_b_2 = { pos_2 ,wy_2 };
		vec wy_b_3 = { pos_3 ,wy_3 };
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_0);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_1);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_2);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.QX_bian.canshu.n_cols, qx_b_3);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_0);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_1);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_2);
		Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.insert_cols(Miller_Mo_HDM::base_data.fangfa.qx_wy.WY_bian.canshu.n_cols, wy_b_3);

	}
}

void Miller_GX_R_HDM::gen_HDM_data()
{
	//确定磨面的方法 8.20 
	Miller_Mo_HDM::base_data.fangfa.type = 2;

	Cal_HDM ls_obj_mian;

	//构造面需要的参数
	int ls_lx_id = ptr_tool->get_hdm_lx_id();
	int ls_hj_id = ptr_tool->get_hdm_hj_id();
	sel_hdm_id = base_data.sel_hdm_id;

	ls_obj_mian.set_base_data(ls_lx_id, ls_hj_id);
	ls_obj_mian.ptr_tool = ptr_tool;
	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

//int Miller_GX_R_HDM::save(int pos);
//{
//	//工序对象
//	gx_obj_data ls_row_data;
//	ls_row_data.type = type_gx;
//	ls_row_data.name = pos;
//	ls_row_data.shalun_id = shalun_id;
//	storage_lib.Storage_base::renew_a_row_data(storage_lib.file_dir_gx_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	//工序参数
//	base_data.pos = pos;
//	base_data.save(int pos);;
//
//	//磨削参数
//	
//	mo_canshu.save(int pos);;
//
//	return pos;
//}
//
void Miller_GX_R_HDM::load(int pos)
{
	Miller_Mo_HDM::load(pos);

	CanShu_GX_R_HDM ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

int Miller_GX_R_HDM::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_R_HDM::get_canshu(CanShu_GX_R_HDM& ans)
{
	ans = base_data;
}

void Miller_GX_R_HDM::set_canshu(CanShu_GX_R_HDM& ptr)
{
	
	//self_xingcan->set_CanShu_GX_R_HDM(ptr);
}

void Miller_GX_R_HDM::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_r_hdm);
	//self_xingcan = ptr;
}


int Miller_GX_DJJX::save(int pos)
{
	Miller_Mo_HDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_DJJX::load(int pos)
{
	Miller_Mo_HDM::load(pos);

	CanShu_GX_DJJX ls_base;
	ls_base.load(pos);
	base_data = ls_base;
}

void Miller_GX_DJJX::get_canshu(CanShu_GX_DJJX& ans)
{
	ans = base_data;
}


void Miller_GX_DJJX::set_canshu(CanShu_GX_DJJX& ptr)
{
	
	//self_xingcan->set_CanShu_GX_DJJX(ptr);
}

void Miller_GX_DJJX::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_djjx);
	//self_xingcan = ptr;
}

Miller_GX_DJJX::Miller_GX_DJJX(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

void Miller_GX_DJJX::set_gx_canshu(CanShu_GX_DJJX& in_canshu)
{
}

void Miller_GX_DJJX::set_shalun_id(int in_id)
{
}

void Miller_GX_DJJX::set_mo_canshu(xt_Mo_QDM_CanShu& in_mo)
{
}

void Miller_GX_DJJX::set_mo_canshu(xt_Mo_HDM_CanShu& in_mo)
{
	Miller_Mo_HDM::base_data = in_mo;
}

void Miller_GX_DJJX::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}
	gen_HDM_data();
}

Miller_GX_DJJX::Miller_GX_DJJX()
{
}

Miller_GX_DJJX::~Miller_GX_DJJX()
{
}

void Miller_GX_DJJX::gen_HDM_data()
{
	Cal_HDM ls_obj_mian;
	//刀尖间隙直接计算出后刀面数据，cal_hdm提供一个接djjx的接口（只有后刀面1）

	mat ls_rx = gen_hdm_rx_by_canshu();
	ls_obj_mian.set_main_data_by_djjx_rx(ls_rx);

	obj_mian = ls_obj_mian;
}

mat Miller_GX_DJJX::gen_hdm_rx_by_canshu()
{
	mat ans_data = zeros(12, 0);


	//计算刀尖间隙-刀具坐标系中计算
	double ls_R = base_data.djjx_R;
	//两个角度决定圆弧转角
	double ang_start = base_data.djjx_ang_down;
	double ang_end = 90.0 - base_data.djjx_ang_up;

	vec3 o_p = { 0.0, ls_R, 0.0 };
	vec3 cal_p = o_p;
	double rotate_ang = ang_start;

	mat ans_p; //指向刀尖
	deque<mat33> ans_sys;

	//圆弧部分
	while (rotate_ang < ang_end) //限制高度点
	{
		cal_p = tcRotZ(3, rotate_ang) * o_p;
		ans_p.insert_cols(ans_p.n_cols, cal_p);

		vec y_sys = tcZ(3);
		vec z_sys = normalise(cal_p);
		vec x_sys = normalise(cross(y_sys, z_sys));

		mat33 cal_sys = eye(3, 3);
		cal_sys.col(0) = x_sys;
		cal_sys.col(1) = y_sys;
		cal_sys.col(2) = z_sys;

		ans_sys.push_back(cal_sys);

		rotate_ang = rotate_ang + 0.01;
	}

	////下端直线
	vec3 v_down = normalise(ans_p.col(1) - ans_p.col(0));
	mat33 sys_down = ans_sys.at(0);
	double delta_dis = norm(ans_p.col(1) - ans_p.col(0));
	double dis_all = ls_R / cos(tcRadians(base_data.djjx_ang_down));
	int count_p = dis_all / delta_dis;

	for (int i = 0; i < count_p; i++)
	{
		cal_p = ans_p.col(0) + v_down * i * delta_dis;
		ans_p.insert_cols(0, cal_p);

		ans_sys.push_front(sys_down);
	}

	////上端直线
	vec3 v_up = normalise(ans_p.col(ans_p.n_cols - 2) - ans_p.col(ans_p.n_cols - 1));
	mat33 sys_up = ans_sys.at(ans_sys.size() - 1);
	dis_all = ls_R / cos(tcRadians(base_data.djjx_ang_up));
	count_p = dis_all / delta_dis;

	for (int i = 0; i < count_p; i++)
	{
		cal_p = ans_p.col(ans_p.n_cols - 1) + v_up * i * delta_dis;
		ans_p.insert_cols(ans_p.n_cols, cal_p);

		ans_sys.push_back(sys_up);
	}

	////线旋转-绕圆弧中间点旋转，提供三个转轴,
	vec3 p_mid = ans_p.col(ans_p.n_cols / 2); //可以提供选择参考点的接口在前端，todo：
	mat33 sys_mid = ans_sys[ans_sys.size() / 2];//直接取中间位置的坐标系, 参考后刀面坐标系
	mat33 sys_rotate_line = tcRotX(3, base_data.djjx_ang_x)
		* tcRotY(3, base_data.djjx_ang_y) * tcRotZ(3, base_data.djjx_ang_z);
	for (int i = 0; i < ans_p.n_cols; i++)
	{
		//平移到原点，旋转后，复位
		ans_p.col(i) = sys_rotate_line * (ans_p.col(i) - p_mid) + p_mid;
		ans_sys[i] = sys_rotate_line * ans_sys[i];
	}

	////test
	////mat test_djjx2 = ans_p.t();
	////test_djjx2.save(R"(test_djjx_2-12.3.txt)", raw_ascii);

	//偏移坐标系,参考刀具坐标系
	vec pianzhi = { base_data.djjx_pianzhi_x, base_data.djjx_pianzhi_y, base_data.djjx_pianzhi_z };
	for (int i = 0; i < ans_p.n_cols; i++)
	{
		ans_p.col(i) = ans_p.col(i) + pianzhi;
	}

	//拼接结果
	for (int i = 0; i < ans_p.n_cols; i++)
	{
		vec ls_p = ans_p.col(i);
		mat ls_sys = ans_sys[i];
		vec ls_ans = { ls_p(0),  ls_p(1) , ls_p(2) ,
		 ls_sys(0,0),ls_sys(1,0),ls_sys(2,0),
		 ls_sys(0,1),ls_sys(1,1),ls_sys(2,1),
		 ls_sys(0,2),ls_sys(1,2),ls_sys(2,2),
		};
		ans_data.insert_cols(ans_data.n_cols, ls_ans);
	}

	return ans_data;
}

Miller_GX_KaiCao_2::Miller_GX_KaiCao_2(int in_type, Tool_Base* in_ptr)
{
	Miller_GX_Base::base_data.type_gx = in_type;
	ptr_tool = in_ptr;
}

Miller_GX_KaiCao_2::Miller_GX_KaiCao_2()
{
}

void Miller_GX_KaiCao_2::set_gx_canshu(CanShu_GX_KaiCao_2& in_canshu)
{
	base_data = in_canshu;
}

void Miller_GX_KaiCao_2::set_shalun_id(int in_id)
{
	Miller_GX_Base::base_data.shalun_id = in_id;
}

void Miller_GX_KaiCao_2::init_mo_data()
{
	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = base_data.selected_ren[i];
	}

	gen_QDM_data();
	if (error_message_global != 0)
	{
		return;
	}
	init_xinhou();
}

void Miller_GX_KaiCao_2::gen_QDM_data()
{
	Cal_QDM ls_obj_mian;

	//构造面需要的参数

	//构造面需要的参数
	CanShu_QianJiao ls_input;
	ls_input.luoxuan_order = ptr_tool->ptr_list_lx->base_data.
		get_show_index_by_id(base_data.guanlian_lx_id);
	ls_input.type = 0;
	ls_input.b_qianjiao_r = base_data.ang_qian.b_qianjiao_r;
	ls_input.b_qianjiao_n = base_data.ang_qian.b_qianjiao_n;

	ls_obj_mian.set_base_data(ls_input);

	//工序刀指针给临时计算对象访问数据 7.18
	ls_obj_mian.ptr_tool = ptr_tool;

	ls_obj_mian.init_data();

	obj_mian = ls_obj_mian;
}

void Miller_GX_KaiCao_2::init_xinhou()
{
	Cal_XinHouMian ls_obj;

	//构造芯厚面需要的参数
	CanShu_XinHouMian ls_input;
	ls_input.type_mian = base_data.type_xinhou;
	ls_input.type_line = 1;
	ls_input.type_cao = 4; //成型端齿槽

	ls_input.start_len_cx = base_data.start_len;
	ls_input.start_R_cx = base_data.start_R;
	ls_input.end_len_cx = base_data.end_len;
	ls_input.end_R_cx = base_data.end_R;

	ls_input.len_lashen = base_data.len_lashen;
	ls_input.len_huizhuan_pianyi = base_data.len_huizhuan_pianyi;
	ls_input.ang_huizhuan = base_data.ang_huizhuan;

	ls_obj.set_base_data(ls_input);
	ls_obj.init_data();

	obj_xinhou = ls_obj;
}

int Miller_GX_KaiCao_2::save(int pos)
{
	Miller_Mo_QDM::save(pos);
	base_data.save(pos);
	return pos;
}

void Miller_GX_KaiCao_2::load(int pos)
{
	Miller_Mo_QDM::load(pos);

	CanShu_GX_KaiCao_2 ls_base;
	ls_base.load(pos);
	base_data = ls_base;

}

void Miller_GX_KaiCao_2::get_canshu(CanShu_GX_KaiCao_2& ans)
{
	ans = base_data;
}

void Miller_GX_KaiCao_2::set_canshu(CanShu_GX_KaiCao_2& ptr)
{
	//self_xingcan->set_CanShu_GX_KaiCao_2(ptr);
}

void Miller_GX_KaiCao_2::set_canshu(XingCan_GX* ptr)
{
	base_data = *(ptr->can_kc_2);
	//self_xingcan = ptr;
}
