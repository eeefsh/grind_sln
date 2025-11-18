#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Tool_Base_Members.h"
#include"Miller_GX_Obj.h"

//10-22ok
bool List_of_XingXian::add_obj(	string name, string file_dir, CanShu_XingXian canshu_obj)
{
	//增加一个型线存储
	int pos = storage_lib.add_a_xx_(name, file_dir, canshu_obj);
	
	//增加如这把刀
	if (!base_data.add_an_obj(pos))
	{
		storage_lib.del_a_xx_(pos);
		return false;
	}

	//存
	save();

	//
	Cal_XingXian* p = new Cal_XingXian();
	p->ptr_tool = ptr_tool;
	p->set_base_data(canshu_obj);
	v_obj_ptr.push_back(p);

	p->init_guanxi();

	return true;
}
//10-22ok
bool List_of_XingXian::edit_obj(int show_order, string name, string file_dir, CanShu_XingXian canshu_obj)
{
	//
	int pos= base_data.get_obj_pos_by_show_index(show_order);
	storage_lib.edit_a_xx_(pos, name, file_dir, canshu_obj);

	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	//
	v_obj_ptr[show_order]->set_base_data(canshu_obj);
	//
	v_obj_ptr[show_order]->init_guanxi();


	return true;
}
//10-22ok
bool List_of_XingXian::del_obj(int show_order)
{
	//
	if (!v_obj_ptr[show_order]->is_del_ok())
	{
		return false;
	}

	//
	int del_pos = base_data.get_obj_pos_by_show_index(show_order);
	if (!base_data.del_an_obj(show_order))
	{
		return false;
	}
	
	//
	if (!storage_lib.del_a_xx_(del_pos))
	{
		return false;
	}

	//存
	save();

	//
	delete v_obj_ptr[show_order];
	v_obj_ptr[show_order] = nullptr;
	v_obj_ptr.erase(v_obj_ptr.begin() + show_order);

	return true;
}

bool List_of_XingXian::get_obj(int show_order, string& name, string& file_dir, CanShu_XingXian& canshu_obj)
{
	//storage_lib.read_a_row_data(
	//	storage_lib.file_dir_xx_name,
	//	base_data.get_id_by_show_index(show_order),
	//	(char*)&name,
	//	sizeof(name));
	//storage_lib.read_a_row_data(
	//	storage_lib.file_dir_xx_newdir,
	//	base_data.get_id_by_show_index(show_order),
	//	(char*)&file_dir,
	//	sizeof(file_dir));

	//storage_lib.read_a_row_data(
	//	storage_lib.file_dir_xx_canshu,
	//	base_data.get_id_by_show_index(show_order),
	//	(char*)&canshu_obj,
	//	sizeof(canshu_obj));

	//应该从pos取数据，不是id，其他都是pos 25.11.5 zy
	storage_lib.read_a_row_data(
		storage_lib.file_dir_xx_name,
		base_data.get_obj_pos_by_show_index(show_order),
		(char*)&name,
		sizeof(name));
	storage_lib.read_a_row_data(
		storage_lib.file_dir_xx_newdir,
		base_data.get_obj_pos_by_show_index(show_order),
		(char*)&file_dir,
		sizeof(file_dir));

	storage_lib.read_a_row_data(
		storage_lib.file_dir_xx_canshu,
		base_data.get_obj_pos_by_show_index(show_order),
		(char*)&canshu_obj,
		sizeof(canshu_obj));

	
	return true;
}
//10-22ok
bool List_of_XingXian::swap_order(int order_1, int order_2)
{
	//
	if (!base_data.swap_order(order_1, order_2))
	{
		return false;
	}

	//存
	save();

	return true;
}
//10-22ok
 Cal_XingXian* List_of_XingXian::get_obj(int in_id)
{
	return v_obj_ptr[in_id];
}
//10-22ok
 int List_of_XingXian::get_count()
{
	return v_obj_ptr.size();
}
//10-22cuo
void List_of_XingXian::cal_self()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		if (v_obj_ptr[i]->is_lastest == 0)
		{
			v_obj_ptr[i]->init_data();
		}
	}
}
//10-22ok
List_of_XingXian::List_of_XingXian()
{
	pos = -1;
	ptr_tool = nullptr;
}
//10-22ok
List_of_XingXian::~List_of_XingXian()
{
	for (size_t i = 0; i < v_obj_ptr.size(); i++)
	{
		if (v_obj_ptr[i] != nullptr)
		{
			delete v_obj_ptr[i];
			v_obj_ptr[i] = nullptr;
		}
	}
}
//10-22ok
int List_of_XingXian::save()
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_tool_list_xx,
		ptr_tool->pos,
		(char*)&base_data,
		sizeof(base_data)
	);
	return 0;
}
//10-22ok
void List_of_XingXian::load()
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_list_xx, pos, 
		(char*)&base_data, sizeof(base_data)
	);
	
	v_obj_ptr.clear();
	for (size_t i = 0; i < base_data.xx_count; i++)
	{
		Cal_XingXian* obj_ptr = new Cal_XingXian();
		obj_ptr->load(base_data.get_obj_pos_by_show_index(i));
		obj_ptr->ptr_tool = ptr_tool;
		v_obj_ptr.push_back(obj_ptr);
	}

}
//10-22cuo
void List_of_XingXian::init_guanxi()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		v_obj_ptr[i]->init_guanxi();
	}
}
//10-22ok
bool List_of_FenDu::add_obj(CanShu_FenDu in_data)
{
	//增加一个型线存储
	int pos = storage_lib.add_a_fd(in_data); 

	//增加如这把刀
	if (!base_data.add_an_obj(pos))
	{
		storage_lib.del_a_fd_(pos);
		return false;
	}

	//存
	save();

	//
	Cal_FenDu* p = new Cal_FenDu();
	p->ptr_tool = ptr_tool;
	p->set_base_data(in_data);
	v_obj_ptr.push_back(p);

	p->init_guanxi();

	return true;
}
//10-22ok
bool List_of_FenDu::edit_obj(int show_order, CanShu_FenDu in_data)
{
	//
	int obj_pos = base_data.get_obj_pos_by_show_index(show_order);
	in_data.save(obj_pos);

	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	//
	v_obj_ptr[show_order]->set_base_data(in_data);
	//
	v_obj_ptr[show_order]->init_guanxi();

	return true;
}
//10-22ok
bool List_of_FenDu::del_obj(int show_order)
{
	//
	if (!v_obj_ptr[show_order]->is_del_ok())
	{
		return false;
	}

	//
	int del_pos = base_data.get_obj_pos_by_show_index(show_order);
	if (!base_data.del_an_obj(show_order))
	{
		return false;
	}

	//
	if (!storage_lib.del_a_fd_(del_pos))
	{
		return false;
	}

	//存
	save();

	//
	delete v_obj_ptr[show_order];
	v_obj_ptr[show_order] = nullptr;
	v_obj_ptr.erase(v_obj_ptr.begin() + show_order);
	return true;
}
//10-22ok
bool List_of_FenDu::swap_order(int order_1, int order_2)
{
	//
	if (!base_data.swap_order(order_1, order_2))
	{
		return false;
	}

	//存
	save();

	return true;
}

bool List_of_FenDu::get_obj(int show_order, CanShu_FenDu& in_data)
{
	in_data.load(base_data.get_obj_pos_by_show_index(show_order));
	return true;
}
//10-22ok
Cal_FenDu* List_of_FenDu::get_obj(int in_id)
{
	return v_obj_ptr[in_id];
}
//10-22ok
int List_of_FenDu::get_count()
{
	return v_obj_ptr.size();
}
//10-22cuo
void List_of_FenDu::cal_self()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		if (v_obj_ptr[i]->is_lastest == 0)
		{
			v_obj_ptr[i]->init_data();
		}
	}
}
//10-22ok
List_of_FenDu::List_of_FenDu()
{
	pos = -1;
	ptr_tool = nullptr;
}
//10-22cuo
List_of_FenDu::~List_of_FenDu()
{
}
//10-22ok
int List_of_FenDu::save()
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_tool_list_fd,
		ptr_tool->pos,
		(char*)&base_data,
		sizeof(base_data)
	);
	return 0;
}
//10-22ok
void List_of_FenDu::load()
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_list_fd, pos, (char*)&base_data, sizeof(base_data));

	v_obj_ptr.clear();
	for (size_t i = 0; i < base_data.xx_count; i++)
	{
		Cal_FenDu* obj_ptr = new Cal_FenDu();
		obj_ptr->load(base_data.get_obj_pos_by_show_index(i));
		obj_ptr->ptr_tool = ptr_tool;
		v_obj_ptr.push_back(obj_ptr);
	}
}
//10-22cuo
void List_of_FenDu::init_guanxi()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		v_obj_ptr[i]->init_guanxi();
	}
}
//10-22ok
bool List_of_LuoXuan::add_obj(CanShu_LuoXuan in_data)
{
	//增加一个型线存储
	int pos = storage_lib.add_a_lx(in_data);

	//增加如这把刀
	if (!base_data.add_an_obj(pos))
	{
		storage_lib.del_a_lx_(pos);
		return false;
	}

	//存
	save();

	//
	Cal_LouXuan* p = new Cal_LouXuan();
	p->ptr_tool = ptr_tool;
	p->set_base_data(in_data);
	v_obj_ptr.push_back(p);

	p->init_guanxi();

	return true;
}
//10-22ok
bool List_of_LuoXuan::edit_obj(int show_order, CanShu_LuoXuan in_data)
{
	//
	int obj_pos = base_data.get_obj_pos_by_show_index(show_order);
	in_data.save(obj_pos);
	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	//
	v_obj_ptr[show_order]->set_base_data(in_data);
	//
	v_obj_ptr[show_order]->init_guanxi();
	//
	return true;
}
//10-22ok
bool List_of_LuoXuan::del_obj(int show_order)
{
	//
	if (!v_obj_ptr[show_order]->is_del_ok())
	{
		return false;
	}

	//
	int del_pos = base_data.get_obj_pos_by_show_index(show_order);
	if (!base_data.del_an_obj(show_order))
	{
		return false;
	}

	//
	if (!storage_lib.del_a_lx_(del_pos))
	{
		return false;
	}

	//存
	save();

	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	delete v_obj_ptr[show_order];
	v_obj_ptr[show_order] = nullptr;
	v_obj_ptr.erase(v_obj_ptr.begin() + show_order);
	return true;
}
//10-22ok
bool List_of_LuoXuan::swap_order(int order_1, int order_2)
{
	//
	if (!base_data.swap_order(order_1, order_2))
	{
		return false;
	}

	//存
	save();

	return true;
}
bool List_of_LuoXuan::get_obj(int show_order, CanShu_LuoXuan& in_data)
{
	in_data.load(base_data.get_obj_pos_by_show_index(show_order));
	return true;
}
//10-22ok
Cal_LouXuan* List_of_LuoXuan::get_obj(int in_id)
{
	if (v_obj_ptr.size() > 0)
	{
		return v_obj_ptr[in_id];
	}
	else
	{
		return nullptr;
	}
}
//10-22ok
int List_of_LuoXuan::get_count()
{
	return v_obj_ptr.size();
}
//10-22cuo
void List_of_LuoXuan::cal_self()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		if (v_obj_ptr[i]->is_lastest == 0)
		{
			v_obj_ptr[i]->init_data();
		}
	}
}
//10-22ok
List_of_LuoXuan::List_of_LuoXuan()
{
	pos = -1;
	ptr_tool = nullptr;
}
//10-22cuo
List_of_LuoXuan::~List_of_LuoXuan()
{
}
int List_of_LuoXuan::get_n_lx_type(int index)
{
	Cal_LouXuan* ls_ptr = v_obj_ptr[index];
	if (ls_ptr == nullptr)
	{
		return -1;
	}
	return ls_ptr->data_base.type_cao;
}
//10-22ok
int List_of_LuoXuan::save()
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_tool_list_lx,
		ptr_tool->pos,
		(char*)&base_data,
		sizeof(base_data)
	);
	return 0;
}
//10-22ok
void List_of_LuoXuan::load()
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_list_lx, pos, (char*)&base_data, sizeof(base_data));

	v_obj_ptr.clear();
	for (size_t i = 0; i < base_data.xx_count; i++)
	{
		Cal_LouXuan* obj_ptr = new Cal_LouXuan();
		obj_ptr->load(base_data.get_obj_pos_by_show_index(i));
		obj_ptr->ptr_tool = ptr_tool;
		v_obj_ptr.push_back(obj_ptr);
	}
}
//10-22cuo
void List_of_LuoXuan::init_guanxi()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		v_obj_ptr[i]->init_guanxi();
	}
}
//10-22ok
bool List_of_HouJiao::add_obj(CanShu_HouJiao in_data)
{
	//增加一个型线存储
	int pos = storage_lib.add_a_hj(in_data);

	//增加如这把刀
	if (!base_data.add_an_obj(pos))
	{
		storage_lib.del_a_hj_(pos);
		return false;
	}

	//存
	save();

	//
	Cal_HouJiao* p = new Cal_HouJiao();
	p->ptr_tool = ptr_tool;
	p->set_base_data(in_data);
	v_obj_ptr.push_back(p);

	//
	p->init_guanxi();

	return true;
}
//10-22ok
bool List_of_HouJiao::edit_obj(int show_order, CanShu_HouJiao in_data)
{
	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	//
	int obj_pos = base_data.get_obj_pos_by_show_index(show_order);
	//
	in_data.save(obj_pos);
	//
	v_obj_ptr[show_order]->set_base_data(in_data);
	//
	v_obj_ptr[show_order]->init_guanxi();


	return true;
}
//10-22ok
bool List_of_HouJiao::del_obj(int show_order)
{
	//
	if (!v_obj_ptr[show_order]->is_del_ok())
	{
		return false;
	}

	//
	int del_pos = base_data.get_obj_pos_by_show_index(show_order);
	if (!base_data.del_an_obj(show_order))
	{
		return false;
	}

	//
	if (!storage_lib.del_a_hj_(del_pos))
	{
		return false;
	}

	//存
	save();

	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	delete v_obj_ptr[show_order];
	v_obj_ptr[show_order] = nullptr;
	v_obj_ptr.erase(v_obj_ptr.begin() + show_order);
	return true;
}
//10-22ok
bool List_of_HouJiao::swap_order(int order_1, int order_2)
{
	//
	if (!base_data.swap_order(order_1, order_2))
	{
		return false;
	}

	//存
	save();

	return true;
}
bool List_of_HouJiao::get_obj(int show_order, CanShu_HouJiao data)
{
	data.load(base_data.get_obj_pos_by_show_index(show_order));
	return true;
}
//10-22ok
Cal_HouJiao* List_of_HouJiao::get_obj(int in_id)
{
	if (v_obj_ptr.size() > 0)
	{
		return v_obj_ptr[in_id];
	}
	else
	{
		return nullptr;
	}
}
//10-22ok
int List_of_HouJiao::get_count()
{
	return v_obj_ptr.size();
}
//10-22cuo
void List_of_HouJiao::cal_self()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		if (v_obj_ptr[i]->is_lastest == 0)
		{
			v_obj_ptr[i]->init_data();
		}
	}
}
//10-22ok
List_of_HouJiao::List_of_HouJiao()
{
	pos = -1;
	ptr_tool = nullptr;
}
//10-22cuo
List_of_HouJiao::~List_of_HouJiao()
{
}
//10-22ok
int List_of_HouJiao::save()
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_tool_list_hj,
		ptr_tool->pos,
		(char*)&base_data,
		sizeof(base_data)
	);
	return 0;
}
//10-22ok
void List_of_HouJiao::load()
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_list_hj, pos, (char*)&base_data, sizeof(base_data));

	v_obj_ptr.clear();
	for (size_t i = 0; i < base_data.xx_count; i++)
	{
		Cal_HouJiao* obj_ptr = new Cal_HouJiao();
		obj_ptr->load(base_data.get_obj_pos_by_show_index(i));
		obj_ptr->ptr_tool = ptr_tool;
		v_obj_ptr.push_back(obj_ptr);
	}
}
//10-22cuo
void List_of_HouJiao::init_guanxi()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		v_obj_ptr[i]->init_guanxi();
	}
}

void List_of_GongXu::add_obj(Miller_GX_Base* in_data)
{
	v_pos.push_back(in_data->pos);
	in_data->is_lastest = 0;
	in_data->ptr_tool = ptr_tool;
	v_obj_ptr.push_back(in_data);
	in_data->init_guanxi();
}

void List_of_GongXu::cal_self()
{
	for (int i = 0; i < ptr_tool->v_select_cal_gx_index.size(); i++)
	{
		Miller_GX_Base* ls_gx = v_obj_ptr[ptr_tool->v_select_cal_gx_index[i]];

		if (v_obj_ptr[i]->is_lastest == 0)
		{
			//计算前需要砂轮参数，获取需要砂轮库指针 7.21
			int in_or_out = storage_lib.get_gx_sl_in_or_out(ls_gx->pos);//0000
			int sl_id = ls_gx->get_sl_id();

			ptr_tool->ptr_sl_manager->get_wheel_L(sl_id, in_or_out, ls_gx->sl.L);
			ptr_tool->ptr_sl_manager->get_wheel_Ry(sl_id, in_or_out, ls_gx->sl.Ry);
			ptr_tool->ptr_sl_manager->get_wheel_r(sl_id, in_or_out, ls_gx->sl.r);

			//计算刀路生成副程序
			ls_gx->init_data();

			if (error_message_global != 0)
			{
				ptr_tool->clear_zhu_prog_then_gen();//中途计算失败要清除加入的副 25.10.31
				return;
			}
		}
		else
		{
			//不重新计算刀路点，但要重构一个副程序 25.11.7 
			ls_gx->init_prog_of_gx();
		}
		//将工序的副程序挂到主程序上
		ptr_tool->prog_zhu->push_my_fu(ls_gx->prog_of_gx);
	}
}

bool List_of_GongXu::add_obj(int type, string name)
{
	//
	#pragma region 新建工序对象
	//
	Miller_GX_Base* cur_gx = nullptr;
	if (type == 0)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_KaiCao(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 1)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_LXC(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 2)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_qiu(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 3)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_ping(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 4)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_yuanjiao(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 5)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_CX_HDM(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 6)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_ZQ_HDM(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 7)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_PD_duan_HDM(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 8)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_PD_zhu_HDM(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 9)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_R_HDM(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 10)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DJJX(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else if (type == 11)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_KaiCao_2(type, ptr_tool));
		cur_gx = ls_gx;
	}
	else
	{
		return false;
	}
#pragma endregion

	//
	int pos = storage_lib.add_a_row_data(
		storage_lib.file_dir_gx_name,(char*)&name,sizeof(name)
	);

	//
	if (!base_data.add_an_obj(pos))
	{
		storage_lib.del_a_gx(pos);
		return false;
	}

	//存
	save();

	//
	cur_gx->save(pos);

	//
	cur_gx->is_lastest = 0;
	v_obj_ptr.push_back(cur_gx);

	return true;
}

bool List_of_GongXu::del_obj(int show_order)
{
	//
	int del_pos = base_data.get_obj_pos_by_show_index(show_order);
	if (!base_data.del_an_obj(show_order))
	{
		return false;
	}
	
	//
	if (!storage_lib.del_a_gx(del_pos))
	{
		return false;
	}

	//存
	save();

	//
	v_obj_ptr[show_order]->speak_father_del_guanxi();
	delete v_obj_ptr[show_order];
	v_obj_ptr[show_order] = nullptr;
	v_obj_ptr.erase(v_obj_ptr.begin() + show_order);

	return true;
}

bool List_of_GongXu::swap_order(int order_1, int order_2)
{
	//
	if (!base_data.swap_order(order_1, order_2))
	{
		return false;
	}

	//存
	save();

	swap(v_obj_ptr[order_1], v_obj_ptr[order_2]);

	return true;
}

bool List_of_GongXu::get_obj_gongxu_name(int show_index, string& name)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_name,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&name,
		sizeof(name));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_name(int show_index, string& name)
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_gx_name,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&name,
		sizeof(name));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_data(int show_index, save_lib* p)
{
	p->load(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_data(int show_index, save_lib* p)
{
	//
	v_obj_ptr[show_index]->speak_father_del_guanxi();
	//
	p->save(base_data.get_obj_pos_by_show_index(show_index));
	//
	v_obj_ptr[show_index]->load(base_data.get_obj_pos_by_show_index(show_index));
	//
	v_obj_ptr[show_index]->init_guanxi();

	//点开dlg并确定更新计算标志位，
	v_obj_ptr[show_index]->is_lastest = 0;

	return true;
}

bool List_of_GongXu::get_obj_gongxu_basedata(int show_index, gx_base_canshu& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_base_canshu,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_basedata(int show_index, gx_base_canshu& data)
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_gx_base_canshu,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_range(int show_index, xt_CanShu_Range& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_range,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_range(int show_index, xt_CanShu_Range& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_sample(int show_index, xt_CanShu_Sample& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_sample,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_sample(int show_index, xt_CanShu_Sample& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_jintuidao(int show_index, xt_CanShu_JinTuiDao& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_jintuidao,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_jintuidao(int show_index, xt_CanShu_JinTuiDao& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_bianhuan(int show_index, xt_CanShu_MoXue_BianHuan& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_bianhuan,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_bianhuan(int show_index, xt_CanShu_MoXue_BianHuan& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_xunhuan(int show_index, xt_CanShu_MoXue_XunHuan& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_xunhuan,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_xunhuan(int show_index, xt_CanShu_MoXue_XunHuan& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_zhenlie(int show_index, xt_CanShu_MoXue_ZhenLie& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_zhenlie,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));

	return true;
}

bool List_of_GongXu::set_obj_gongxu_zhenlie(int show_index, xt_CanShu_MoXue_ZhenLie& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_fangfa(int show_index, CanShu_HDM_MoXue_FangFa& data)
{
	data.load(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_fangfa(int show_index, CanShu_HDM_MoXue_FangFa& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_fangfa(int show_index, CanShu_QDM_MoXue_FangFa& data)
{
	data.load(show_index);
	/*storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_fangfa,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));*/
	return true;
}

bool List_of_GongXu::set_obj_gongxu_fangfa(int show_index, CanShu_QDM_MoXue_FangFa& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_sudu(int show_index, CanShu_SuDu& data)
{
	data.load(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_sudu(int show_index, CanShu_SuDu& data)
{
	data.save(base_data.get_obj_pos_by_show_index(show_index));
	return true;
}

bool List_of_GongXu::get_obj_gongxu_A_before(int show_index, double& data)
{
	storage_lib.read_a_row_data(
		storage_lib.file_dir_gx_A_before,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

bool List_of_GongXu::set_obj_gongxu_A_before(int show_index, double& data)
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_gx_A_before,
		base_data.get_obj_pos_by_show_index(show_index),
		(char*)&data,
		sizeof(data));
	return true;
}

 Miller_GX_Base* List_of_GongXu::get_obj(int in_id)
{
	
	return v_obj_ptr[in_id];
}

 int List_of_GongXu::get_count()
{
	return v_obj_ptr.size();
}

 void List_of_GongXu::del_a_gx(int in_order)
{
	 base_data.del_an_obj(in_order);

	v_obj_ptr.erase(v_obj_ptr.begin() + in_order);
}

 void List_of_GongXu::swap_gx(int up, int down)
{
	//swap(v_list.begin() + up, v_list.begin() + down);
	swap(v_obj_ptr[up], v_obj_ptr[down]);
}

Miller_GX_Base* List_of_GongXu::gen_gx(int type)
{
	switch (type)
	{
	case 0:
		return new Miller_GX_KaiCao;
	case 1:
		return new Miller_GX_LXC;
	case 2:
		return new Miller_GX_DCC_qiu;
	case 3:
		return new Miller_GX_DCC_ping;
	case 4:
		return new Miller_GX_DCC_yuanjiao;
	case 5:
		return new Miller_GX_CX_HDM;
	case 6:
		return new Miller_GX_ZQ_HDM;
	case 7:
		return new Miller_GX_PD_duan_HDM;
	case 8:
		return new Miller_GX_PD_zhu_HDM;
	case 9:
		return new Miller_GX_R_HDM;
	case 10:
		return new Miller_GX_DJJX;
	case 11:
		return new Miller_GX_KaiCao_2;


	default:
		return nullptr;
		break;
	}
}

List_of_GongXu::List_of_GongXu()
{
	pos = -1;
	ptr_tool = nullptr;
}

List_of_GongXu::~List_of_GongXu()
{
}

int List_of_GongXu::save()
{
	storage_lib.edit_a_row_data(
		storage_lib.file_dir_tool_list_gx,
		ptr_tool->pos,
		(char*)&base_data,
		sizeof(base_data)
	);
	return 0;
}

void List_of_GongXu::load()
{
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_list_gx, pos, (char*)&base_data, sizeof(base_data));

	v_obj_ptr.clear();
	for (int i = 0; i < base_data.xx_count; i++)
	{
		int pos = base_data.get_obj_pos_by_show_index(i);

		gx_base_canshu base_canshu;
		storage_lib.Storage_base::read_a_row_data(
			storage_lib.file_dir_gx_base_canshu, pos, (char*)&base_canshu, sizeof(base_canshu));

		Miller_GX_Base* ls_ptr = gen_gx(base_canshu.type_gx);
		ls_ptr->ptr_tool = ptr_tool;
		ls_ptr->load(pos);
		v_obj_ptr.push_back(ls_ptr);
	}
}

void List_of_GongXu::load_gx_v_pos()
{
}

void List_of_GongXu::init_guanxi()
{
	for (int i = 0; i < v_obj_ptr.size(); i++)
	{
		v_obj_ptr[i]->init_guanxi();
	}
}

//int List_of_GongXu::save()
//{
//	xx_list_data ls_row_data;
//	int obj_count = v_list.size();
//	ls_row_data.xx_count = obj_count;
//	for (int i = 0; i < obj_count; i++)
//	{
//		int ls_pos = v_list[i]->save();
//		ls_row_data.xx_pos[i] = ls_pos;
//	}
//
//	int empty_count = empty_index.size();
//	ls_row_data.empty_count = empty_count;
//	for (int i = 0; i < empty_count; i++)
//	{
//		ls_row_data.empty_pos[i] = empty_index.front();
//		empty_index.pop();
//	}
//
//	//storage_lib.Storage_base::renew_a_row_data(44, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	time_updata cur_time;
//	//storage_lib.Storage_base::renew_a_row_data(16, pos, (char*)&cur_time, sizeof(cur_time));
//
//
//	return pos;
//}
//
//void List_of_GongXu::load()
//{
//	xx_list_data ls_row_data;
//	//storage_lib.Storage_base::read_a_row_data(44, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	v_pos.clear();
//	for (int i = 0; i < ls_row_data.xx_count; i++)
//	{
//		//恢复型线对象放到容器
//		int ls_pos = ls_row_data.xx_pos[i];
//		v_pos.push_back(ls_pos);
//
//		//读出一条gx对象数据
//		gx_obj_data ls_row_data_gx;
//		//storage_lib.Storage_base::read_a_row_data(4, ls_pos, (char*)&ls_row_data_gx, sizeof(ls_row_data_gx));
//
//
//		Miller_GX_Base* ls_ptr = gen_gx(ls_row_data_gx.type);
//		ls_ptr->pos = ls_pos;
//		ls_ptr->ptr_tool = ptr_tool;
//		ls_ptr->load();
//
//		v_list.push_back(ls_ptr);
//	}
//
//	for (int i = 0; i < ls_row_data.empty_count; i++)
//	{
//		int ls_pos = ls_row_data.empty_pos[i];
//		empty_index.push(ls_pos);
//	}
//}
//
//void List_of_GongXu::load_gx_v_pos()
//{
//	xx_list_data ls_row_data;
//	//storage_lib.Storage_base::read_a_row_data(44, pos, (char*)&ls_row_data, sizeof(ls_row_data));
//
//	v_pos.clear();
//	for (int i = 0; i < ls_row_data.xx_count; i++)
//	{
//		//恢复型线对象放到容器
//		int ls_pos = ls_row_data.xx_pos[i];
//		v_pos.push_back(ls_pos);
//	}
//}

void List_of_ShaLun::add_obj(int sl_id, Miller_GX_Base* in_p)
{
	v_sl_id.push_back(sl_id);
	v_obj_ptr.push_back(in_p);
}

void List_of_ShaLun::cal_self()
{
}

void List_of_ShaLun::load()
{
	int count_gx = ptr_tool->ptr_list_gx->v_obj_ptr.size();
	for (int i = 0; i < count_gx; i++)
	{
		Miller_GX_Base* ls_gx = ptr_tool->ptr_list_gx->v_obj_ptr[i];

		add_obj(ls_gx->get_sl_id(), ls_gx);
	}
}

int List_of_ShaLun::get_count()
{
	return v_sl_id.size();
}

Miller_GX_Base* List_of_ShaLun::get_obj(int i)
{
	if (v_obj_ptr.size() > 0)
	{
		return v_obj_ptr[i];
	}
	else
	{
		return nullptr;
	}
}

List_of_ShaLun::List_of_ShaLun()
{
	ptr_tool = nullptr;
}

List_of_ShaLun::~List_of_ShaLun()
{
}
