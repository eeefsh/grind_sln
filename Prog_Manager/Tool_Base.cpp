#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Tool_Base.h"
#include"Miller_GX_Obj.h"
#include"Storage_manager.h"


JC_sl_lib::JC_sl_lib()
{
	//ptr_storage = nullptr;
}

void JC_sl_lib::load_slz(int n_order, int in_slz_num)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_sl_lib, n_order, (char*)&in_slz_num, sizeof(in_slz_num));
}

void JC_sl_lib::unload_slz(int n_order)
{
	int ls_num = -1;
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_sl_lib, n_order, (char*)&ls_num, sizeof(ls_num));
}

int JC_sl_lib::count()
{
	return 6;
}

int JC_sl_lib::get_slz_id(int n_order)
{
	int ls_num = -1;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_sl_lib, n_order, (char*)&ls_num, sizeof(ls_num));
	return ls_num;
}

bool JC_sl_lib::is_slz_on(int n_order)
{
	int ls_num = -1;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_sl_lib, n_order, (char*)&ls_num, sizeof(ls_num));
	if (ls_num == -1)
	{
		return 0;
	}
	return 1;
}


Tool_lib::Tool_lib()
{
	//外存中恢复 count
	//外存中恢复 v_tool_pos
	display_tool_list();
}


//刷新显示列表
inline void Tool_lib::display_tool_list()
{
	//0、进入这个函数将显示数据的容器清空
	v_tool_name.clear();
	v_tool_time.clear();
	v_tool_pos.clear();
	v_tool_type.clear();

	//1 按时间顺序查找所有 刀具pos
	multimap<time_updata, int> time_pos;
	int ls_tool_count = storage_lib.get_tool_count(); 
	int ls_tool_count2 = ls_tool_count;

	set<int> del_pos;
	storage_lib.get_empty_pos(del_pos);
	int cur_read_pos = 0;
	while (ls_tool_count > 0)
	{
		if (del_pos.find(cur_read_pos) == del_pos.end()) //没找到，说明没删除
		{
			time_updata ls_time;
			storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_time,
				cur_read_pos, (char*)&ls_time, sizeof(ls_time));
			time_pos.insert({ ls_time ,cur_read_pos });
			ls_tool_count--;
		}
		cur_read_pos++;
	}

	//2、时间升序遍历
	multimap<time_updata, int>::iterator it = time_pos.begin();
	while (it != time_pos.end())
	{
		string s_time;// s_time.resize(200);
		time_to_string(it->first, s_time);
		v_tool_time.push_back(s_time);

		int name_pos = it->second;
		v_tool_pos.push_back(name_pos);

		string cur_name;
		storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_name, name_pos, (char*)&cur_name, sizeof(cur_name));
		v_tool_name.push_back(cur_name);


		int int_type = -1;
		string cur_type;
		storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_type, name_pos, (char*)&int_type, sizeof(int_type));
		cur_type = to_string(int_type);
		v_tool_type.push_back(cur_type);

		it++;
	}
	
}

inline void Tool_lib::display_tool_list_by_type(int in_type)
{	//0、进入这个函数将显示数据的容器清空
	v_tool_name.clear();
	v_tool_time.clear();
	v_tool_pos.clear();
	v_tool_type.clear();

	//从刀具类型文件中筛选出指定类型
	int ls_tool_count = storage_lib.get_tool_count(); //可以用管理读写文件中的最大行号实现 7.4 ???

	set<int> del_pos;
	storage_lib.get_empty_pos(del_pos);
	vector<int> v_type;
	storage_lib.read_type(v_type); //读到文件末尾
	//筛选类型，剔除空行 --- 可以合并到读类型函数中 7.15 mark
	vector<int> ans_v_type;
	set<int>::iterator it_del = del_pos.begin();

	for (int i = 0; i < v_type.size(); i++) //对列的0 等于数量1
	{
		if (v_type[i] == in_type) //类型正确
		{
			if (it_del == del_pos.end()) //
			{
				ans_v_type.push_back(i + 1);
			}
			else
			{
				if (i != *it_del)
				{
					ans_v_type.push_back(i + 1);
				}
			}
		}
	}


	map<time_updata, int> time_pos;
	map<time_updata, int> time_type; //增加类型，同理时间顺序
	for (int i = 0; i < ans_v_type.size(); i++)
	{
		int name_pos = ans_v_type[i];

		time_updata ls_time;
		get_tool_time(name_pos, ls_time);
		string s_time;
		time_to_string(ls_time, s_time);
		v_tool_time.push_back(s_time);

		v_tool_pos.push_back(name_pos);

		string cur_name;
		get_tool_name(name_pos, cur_name);//读100长度字符串，写入时长度设置100 7.10
		v_tool_name.push_back(cur_name);

		string cur_type;
		tool_type_to_string(in_type, cur_type);
		v_tool_type.push_back(cur_type);
	}
}

int Tool_lib::count()
{
	return v_tool_pos.size();
}

int Tool_lib::get_tool_pos(int n_order)
{
	return v_tool_pos[n_order];
}

string Tool_lib::get_name(int n_order)
{
	return v_tool_name[n_order];
}

string Tool_lib::get_time(int n_order)
{
	return v_tool_time[n_order];
}

string Tool_lib::get_type(int n_order)
{
	return v_tool_type[n_order];
}

Tool_Base::Tool_Base()
{
	ptr_list_xx = new List_of_XingXian;
	ptr_list_hj = new List_of_HouJiao;
	ptr_list_lx = new List_of_LuoXuan;
	ptr_list_fd = new List_of_FenDu;
	ptr_list_gx = new List_of_GongXu;
	ptr_list_sl = new List_of_ShaLun;

	ptr_list_xx->ptr_tool = this;
	ptr_list_hj->ptr_tool = this;
	ptr_list_lx->ptr_tool = this;
	ptr_list_fd->ptr_tool = this;
	ptr_list_gx->ptr_tool = this;
	ptr_list_sl->ptr_tool = this;

	prog_zhu = new fangzhen_zhu;
}

void Tool_Base::cal_selected_gx_DL(int flag)
{
	//更新计算标识状态
	updata_all_obj_cal_state();

	//更新工序的计算标识 25.11.11
	updata_all_gx_cal_flag(flag);

	//刀具基类的init函数就是计算list成员，不用再次计算，其中成型刀为空实现 8.7
	init();

	
	//设置程序安全位置
	prog_zhu->set_cx_safe_p(get_cx_safe_p(), 5000.0);

	//生成程序树
	prog_zhu->generation();

	//清空当前选择计算刀路的工序
	v_select_cal_gx_index.clear();

	clear_zhu_prog_then_gen();//副程序生成结束后更新主 25.9.11
}

void Tool_Base::updata_all_obj_cal_state()
{
	for (size_t i = 0; i < ptr_list_xx->get_count(); i++)
	{
		if (ptr_list_xx->get_obj(i)->is_lastest == 0)
		{
			for (size_t j = 0; j < ptr_list_xx->get_obj(i)->v_GL_HJ.size(); j++)
			{
				ptr_list_xx->get_obj(i)->v_GL_HJ[j]->is_lastest = 0;
			}

			for (size_t j = 0; j < ptr_list_xx->get_obj(i)->v_GL_LX.size(); j++)
			{
				ptr_list_xx->get_obj(i)->v_GL_LX[j]->is_lastest = 0;
			}
		}
	}

	for (size_t i = 0; i < ptr_list_fd->get_count(); i++)
	{
		if (ptr_list_fd->get_obj(i)->is_lastest == 0)
		{
			for (size_t j = 0; j < ptr_list_fd->get_obj(i)->v_GL_LX.size(); j++)
			{
				ptr_list_fd->get_obj(i)->v_GL_LX[j]->is_lastest = 0;
			}
		}
	}

	for (size_t i = 0; i < ptr_list_hj->get_count(); i++)
	{
		if (ptr_list_hj->get_obj(i)->is_lastest == 0)
		{
			for (size_t j = 0; j < ptr_list_hj->get_obj(i)->v_GL_GX.size(); j++)
			{
				ptr_list_hj->get_obj(i)->v_GL_GX[j]->is_lastest = 0;
			}
		}
	}

	for (size_t i = 0; i < ptr_list_lx->get_count(); i++)
	{
		if (ptr_list_lx->get_obj(i)->is_lastest == 0)
		{
			for (size_t j = 0; j < ptr_list_lx->get_obj(i)->v_GL_GX.size(); j++)
			{
				ptr_list_lx->get_obj(i)->v_GL_GX[j]->is_lastest = 0;
			}
		}
	}

	//
	for (size_t i = 0; i < ptr_list_sl->get_count(); i++)
	{
		if (ptr_list_sl->get_obj(i)->is_lastest == 0)
		{
			//获取不到砂轮修改的状态 25.10.31 ???
			
			//for (size_t j = 0; j < ptr_list_lx->get_obj(i)->v_GL_GX.size(); j++)
			//{
			//	ptr_list_lx->get_obj(i)->v_GL_GX[j]->is_lastest = 0;
			//}
		}
	}

}

void Tool_Base::updata_all_gx_cal_flag(int flag)
{
	for (int i = 0; i < ptr_list_gx->get_count(); i++)
	{
		ptr_list_gx->get_obj(i)->flag_cal_prog = flag;
	}
}

void Tool_Base::clear_zhu_prog_then_gen()
{
	if (prog_zhu != nullptr)
	{
		delete prog_zhu;
		prog_zhu = nullptr;
		prog_zhu = new fangzhen_zhu();
	}
	nc_program_fu::name_fu_i = 0; //25.11.17
}

void Tool_Base::cal_all_list()
{
	ptr_list_xx->cal_self();
	ptr_list_hj->cal_self();
	ptr_list_lx->cal_self();
	//ptr_list_fd->cal_self();
	//ptr_list_gx.cal_self();
}

void Tool_Base::set_sl_manager(wheel_output* in_ptr)
{
	ptr_sl_manager = in_ptr;
}

void Tool_Base::set_type(int in_type)
{
	type_tool = in_type;
}

double Tool_Base::get_delta_dis()
{
	return canshu_gg.delta_dis_ren;
}

int Tool_Base::get_xx_count()
{
	return ptr_list_xx->v_obj_ptr.size();
}

bool Tool_Base::check_sel_xx_can_del(int pos)
{
	int count_hj = ptr_list_hj->v_obj_ptr.size();
	for (int i = 0; i < count_hj; i++)
	{
		Cal_HouJiao* ls_hj = ptr_list_hj->v_obj_ptr[i];
		if (ls_hj != nullptr)
		{
			if (ls_hj->data_base.guanlian_xx_id == pos)
			{
				return false;
			}
		}
	}

	int count_lx = ptr_list_lx->v_obj_ptr.size();
	for (int i = 0; i < count_lx; i++)
	{
		Cal_LouXuan* ls_lx = ptr_list_lx->v_obj_ptr[i];
		if (ls_lx != nullptr)
		{
			if (ls_lx->data_base.guanlian_xx_id == pos)
			{
				return false;
			}
		}
	}

	return true;
}

bool Tool_Base::del_a_xx(int pos)
{
	return ptr_list_xx->del_obj(pos);
}

bool Tool_Base::check_sel_hj_can_del(int pos)
{
	int count_gx = ptr_list_gx->v_obj_ptr.size();
	for (int i = 0; i < count_gx; i++)
	{
		Miller_GX_Base* ls_gx = ptr_list_gx->v_obj_ptr[i];
		if (ls_gx != nullptr)
		{
			if (ls_gx->get_hj_id() == pos)
			{
				return false;
			}
		}
	}

	return true;
}

bool Tool_Base::del_a_hj(int pos_ral)
{
	return ptr_list_hj->del_obj(pos_ral);
}

bool Tool_Base::check_sel_fd_can_del(int pos)
{
	int count_hj = ptr_list_lx->v_obj_ptr.size();
	for (int i = 0; i < count_hj; i++)
	{
		Cal_LouXuan* ls_hj = ptr_list_lx->v_obj_ptr[i];
		if (ls_hj != nullptr)
		{
			if (ls_hj->data_base.guanlian_fd_id == pos)
			{
				return false;
			}
		}
	}

	return true;
}

bool Tool_Base::del_a_fd(int index)
{

	return ptr_list_fd->del_obj(index);
}

bool Tool_Base::check_sel_lx_can_del(int index)
{
	int count_gx = ptr_list_gx->v_obj_ptr.size();
	for (int i = 0; i < count_gx; i++)
	{
		Miller_GX_Base* ls_gx = ptr_list_gx->v_obj_ptr[i];
		if (ls_gx != nullptr)
		{

			if (ls_gx->get_lx_id() == index)
			{
				return false;
			}
		}
	}
	return true;
}

bool Tool_Base::del_a_lx(int index)
{
	return ptr_list_lx->del_obj(index);
}


Miller_GX_Base* Tool_Base::get_gx(int n_order)
{
	return 	ptr_list_gx->get_obj(n_order);
}

bool Tool_Base::set_n_gx_canshu(int n_order, XingCan_GX* xc_canshu)
{
	//从工序队列里拿到工序对象
	Miller_GX_Base* cur_gx = ptr_list_gx->v_obj_ptr[n_order];

	//更新工序状态 25.9.29
	cur_gx->is_lastest = 0;

	//cur_gx->set_canshu(xc_canshu);

	return true;
}

bool Tool_Base::get_n_gx_canshu(int n_order, XingCan_GX*& xc_canshu)
{
	Miller_GX_Base* cur_gx = ptr_list_gx->v_obj_ptr[n_order];

	//xc_canshu = cur_gx->self_xingcan;
	return true;
}

bool Tool_Base::set_n_gx_mo_canshu(int n_order, xt_Mo_HDM_CanShu& mo_canshu)
{
	ptr_list_gx->v_obj_ptr[n_order]->set_mo_canshu(mo_canshu);
	ptr_list_gx->v_obj_ptr[n_order]->is_lastest = 0;
	return 1;
}

bool Tool_Base::set_n_gx_mo_canshu(int n_order, xt_Mo_QDM_CanShu& mo_canshu)
{
	ptr_list_gx->v_obj_ptr[n_order]->set_mo_canshu(mo_canshu);
	ptr_list_gx->v_obj_ptr[n_order]->is_lastest = 0;
	return 1;
}

void Tool_Base::renew_a_gx_of_xc(int in_pos, XingCan_GX* xc_canshu)
{
	//根据工序类型构造出参数类，写到对应位置
	int cur_type = xc_canshu->gx_type;

	//switch (cur_type)
	//{
	//case 0:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_kc), sizeof((*xc_canshu->can_kc)));
	//	break;
	//case 1:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_lxc), sizeof((*xc_canshu->can_lxc)));
	//	break;
	//case 2:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_dcc_qiu), sizeof((*xc_canshu->can_dcc_qiu)));
	//	break;
	//case 3:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_dcc_ping), sizeof((*xc_canshu->can_dcc_ping)));
	//	break;
	//case 4:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_dcc_yuan), sizeof((*xc_canshu->can_dcc_yuan)));
	//	break;
	//case 5:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_cx_hdm), sizeof((*xc_canshu->can_cx_hdm)));
	//	break;
	//case 6:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_zq_hdm), sizeof((*xc_canshu->can_zq_hdm)));
	//	break;
	//case 7:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_pd_duan_hdm), sizeof((*xc_canshu->can_pd_duan_hdm)));
	//	break;
	//case 8:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_pd_zhu_hdm), sizeof((*xc_canshu->can_pd_zhu_hdm)));
	//	break;
	//case 9:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_r_hdm), sizeof((*xc_canshu->can_r_hdm)));
	//	break;
	//case 10:
	//	storage_lib.Storage_base::renew_a_row_data(5, in_pos, (char*)&(*xc_canshu->can_r_hdm), sizeof((*xc_canshu->can_r_hdm)));
	//	break;

	//default:
	//	break;
	//}
}


string Tool_Base::get_gx_name(int n_order)
{
	Miller_GX_Base* ls_gx = get_gx(n_order);
	string ans_name = ls_gx->get_name();

	return ans_name;
}

string Tool_Base::get_gx_type(int n_order)
{
	Miller_GX_Base* ls_gx = get_gx(n_order);
	string ans_name = ls_gx->get_type_of_string();

	return ans_name;
}


int Tool_Base::get_gx_sl_id(int n_order)
{
	Miller_GX_Base* ls_gx = get_gx(n_order);
	int sl_id = ls_gx->get_sl_id();
	return sl_id;
}

string Tool_Base::get_gx_jingeilv(int n_order)
{
	Miller_GX_Base* ls_gx = get_gx(n_order);
	double ls_jg = ls_gx->get_jingeilv();
	string ans_name = to_string(ls_jg);

	return ans_name;
}

void Tool_Base::new_a_gx_and_add_to_list( int gx_pos)
{
	gx_base_canshu ls_data;
	storage_lib.get_gx_obj_canshu(gx_pos, (char*)&ls_data, sizeof(ls_data));

	int gx_type = ls_data.type_gx;
	//new 并放到工序列表中
	//1、根据类型新建一个gx对象
	Miller_GX_Base* cur_gx = nullptr;
	//共享指针模式的情况，switch不能实现，改用if 6.10 zy
#pragma region new
	if (gx_type == 0)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_KaiCao(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 1)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_LXC(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 2)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_qiu(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 3)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_ping(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 4)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DCC_yuanjiao(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 5)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_CX_HDM(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 6)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_ZQ_HDM(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 7)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_PD_duan_HDM(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 8)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_PD_zhu_HDM(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 9)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_R_HDM(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 10)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_DJJX(gx_type, this));
		cur_gx = ls_gx;
	}
	else if (gx_type == 11)
	{
		Miller_GX_Base* ls_gx(new Miller_GX_KaiCao_2(gx_type, this));
		cur_gx = ls_gx;
	}
	else
	{

	}
#pragma endregion

	//cur_gx->set_xingcan(gx_type);

	ptr_list_gx->add_obj(cur_gx);
	ptr_list_gx->v_pos.push_back(gx_pos);
}

void Tool_Base::set_gx_sl_id(int n_order, int in_sl_id)
{
	Miller_GX_Base* ls_gx = get_gx(n_order);

	//增加判断，没修改就不修改标志。砂轮窗口打开时就进触发，不在此处判断 25.10.31 
	if (ls_gx->base_data.shalun_id == in_sl_id)
	{
		return;
	}

	ls_gx->base_data.shalun_id = in_sl_id;
	ls_gx->is_lastest = 0;
	
	ptr_list_sl->add_obj(in_sl_id, ls_gx);

}

void Tool_Base::set_new_gx_name(int n_order, string in_name)
{
	//直接操作存储文件，复写数据
	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };

	//string转为数组 size < 100
	for (int i = 0; i < in_name.size(); i++)
	{
		name_buffer[i] = in_name[i];
	}

	//工序对象文件位置 = name位置
	Miller_GX_Base* ls_gx = get_gx(n_order);
	int storage_pos = ls_gx->pos;
	//storage_lib.Storage_base::renew_a_row_data(9, storage_pos, name_buffer, NAME_BUFFER_SIZE);
	//更新工序显示列表
}

void Tool_Base::save_a_gx_obj_data(int n_order)
{
	//修改工序其他文件
	Miller_GX_Base* ls_gx = get_gx(n_order);
	int storage_pos = ls_gx->pos;

	//保存到文件
	//gx_obj_data ls_gx;
	//storage_tool.Storage_base::read_a_row_data(4, storage_pos, (char*)&ls_gx, sizeof(ls_gx));
	//for (int i = 0; i < 6; i++)
	//{
	//	ls_gx.A_before_ren[i] = cur_tool->v_data[cur_gx_index]->A_before_ren[i];
	//	ls_gx.sel_A_before_ren[i] = cur_tool->v_data[cur_gx_index]->sel_A_before_ren[i];
	//}

	//storage_lib.Storage_base::renew_a_row_data(4, storage_pos, (char*)&ls_gx, sizeof(ls_gx));
}


bool Tool_Base::del_a_gx(int order_pos)
{
	if (order_pos < 0 || order_pos > ptr_list_gx->get_count() - 1)
	{
		return false;
	}
	ptr_list_gx->del_obj(order_pos);
	return true;
}

bool Tool_Base::move_up_a_gx(int order_pos)
{
	int up_pos = order_pos - 1;
	//交换刀具执行列表的顺序-位置列表
	if (order_pos == 0)
	{
		return false;
	}
	else
	{
		ptr_list_gx->swap_gx(up_pos, order_pos);
	}
	return true;
}

bool Tool_Base::move_down_a_gx(int order_pos)
{
	int down_pos = order_pos + 1;
	//交换刀具执行列表的顺序-位置列表
	if (order_pos == ptr_list_gx->get_count() - 1)
	{
		return false;
	}
	else
	{
		ptr_list_gx->swap_gx( order_pos, down_pos);
	}
	return true;
}


int Tool_Base::set_cur_gx_name(string in_name)
{
	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };

	//string转为数组 size < 100
	for (int i = 0; i < in_name.size(); i++)
	{
		name_buffer[i] = in_name[i];
	}
	//2、从gx名称文件中返回一个下标
	//int name_pos = storage_lib.write_a_row_data(9, name_buffer, NAME_BUFFER_SIZE);
	return 0;
}


void Tool_Base::set_anquandian(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p)
{
	canshu_gg.gx_safe_p = gx_p;
	canshu_gg.sl_safe_p = sl_p;
	canshu_gg.cx_safe_p = cx_p;
}

Point_by_5axis Tool_Base::get_gx_safe_p()
{
	return canshu_gg.gx_safe_p;
}

Point_by_5axis Tool_Base::get_sl_safe_p()
{
	return canshu_gg.sl_safe_p;
}

Point_by_5axis Tool_Base::get_cx_safe_p()
{
	return canshu_gg.cx_safe_p;
}

void Tool_Base::set_sample_tool(xt_CanShu_Sample& in_sample)
{
	canshu_gg.sample_tool = in_sample;
}

void Tool_Base::set_sel_cal_gx(vector<int> in_v_sel)
{
	v_select_cal_gx_index = in_v_sel;
}

void Tool_Base::get_gonggong_canshu(Canshu_Tool_GongYong& ans_can)
{
	ans_can = canshu_gg;
}

void Tool_Base::set_gonggong_canshu(Canshu_Tool_GongYong& ans_can)
{
	canshu_gg = ans_can;
}

void Tool_Base::set_sample_canshu(double len, double ang)
{
	canshu_gg.sample_tool.Sample_lenth = len;
	canshu_gg.sample_tool.Sample_angle = ang;
}

void Tool_Base::get_cur_tool_canshu(CanShu_Geo_CX& ans_can)
{

}
void Tool_Base::get_cur_tool_canshu(CanShu_Geo_ZQ& ans_can)
{

}
void Tool_Base::get_cur_tool_canshu(CanShu_Geo_PD& ans_can)
{

}
void Tool_Base::get_cur_tool_canshu(CanShu_Geo_R& ans_can)
{

}

void Tool_Base::set_cur_tool_canshu(CanShu_Geo_CX& ans_can)
{

}
void Tool_Base::set_cur_tool_canshu(CanShu_Geo_ZQ& ans_can)
{

}
void Tool_Base::set_cur_tool_canshu(CanShu_Geo_PD& ans_can)
{

}
void Tool_Base::set_cur_tool_canshu(CanShu_Geo_R& ans_can)
{

}

double Tool_Base::get_D()
{
	return 0.0;
}

double Tool_Base::get_renlen()
{
	return 0.0;
}

double Tool_Base::get_alllen()
{
	return 0.0;
}

double Tool_Base::get_rrr()
{
	return 0.0;
}

void Tool_Base::set_gx_sl_pos_in_JC(int n_order, int in_pos)
{
	ptr_list_gx->v_obj_ptr[n_order]->base_data.sl_pos_in_JC = in_pos;
}

bool Tool_Base::updata_gx_lastest_by_sl_edit(vector<int>& in_v_sl_id)
{
	for (int i = 0; i < in_v_sl_id.size(); i++)
	{
		int ls_sl_id = in_v_sl_id[i];

		int count_gx = ptr_list_gx->get_count();
		for (int j = 0; j < count_gx; j++)
		{
			Miller_GX_Base* ls_gx = ptr_list_gx->get_obj(j);

			if (ls_gx->get_sl_id() == ls_sl_id)
			{
				ls_gx->is_lastest = 0;
			}
		}
	}

	return true;
}



inline int Tool_lib::add_a_row_data(int dao_type, string in_name)
{
	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };
	//string转为数组 size < 100
	for (int i = 0; i < in_name.size(); i++)
	{
		name_buffer[i] = in_name[i];
	}

	//int ans_pos = storage_lib.write_a_row_data(8, name_buffer, NAME_BUFFER_SIZE);

	time_updata cur_time;
	//storage_lib.Storage_base::renew_a_row_data(16,ans_pos,(char*)&cur_time, sizeof(cur_time)); 
	//storage_lib.Storage_base::renew_a_row_data(17,ans_pos,(char*)&dao_type, sizeof(dao_type));

	storage_lib.add_tool_count(1);

	display_tool_list();

	return  0;
}

void Tool_lib::edit_name(int n_order, string in_name)
{
	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };

	//string转为数组 size < 100
	for (int i = 0; i < in_name.size(); i++)
	{
		name_buffer[i] = in_name[i];
	}

	//刀具对象文件位置 = name位置
	int storage_pos = v_tool_pos[n_order];
	//storage_lib.Storage_base::renew_a_row_data(8, storage_pos, name_buffer, NAME_BUFFER_SIZE);
	//更新工序显示列表
	v_tool_name[n_order] = in_name;
}

void Tool_lib::del_a_tool(int n_order)
{
	//刀具对象文件位置 = name位置
	int storage_pos = v_tool_pos[n_order];

	//修改管理刀具读写的文件
	storage_lib.del_a_tool(storage_pos); //内部已经修改计数文件

	//将所属的工序全部删除 7.11 
	List_of_GongXu ls_gx_list; 
	ls_gx_list.pos = storage_pos; 
	ls_gx_list.load_gx_v_pos(); //位置与刀同步 25.6.15 需要一个恢复工序位置，不恢复其他数据的接口

	for (int i = 0; i < ls_gx_list.v_pos.size(); i++)
	{
		//storage_lib.del_a_gx(ls_gx_list.v_pos[i]);
	}

	display_tool_list();
}

inline void Tool_lib::get_tool_name(int in_pos, string& ans_name)
{
	ans_name = storage_lib.get_tool_name(in_pos);
}

inline void Tool_lib::get_tool_time(int in_pos, time_updata& cur_tm)
{
	//storage_lib.Storage_base::read_a_row_data(16, in_pos, (char*)&cur_tm, sizeof(cur_tm));
}

inline void Tool_lib::time_to_string(time_updata cur_tm, string& s_time)
{
	tm ls_ym = cur_tm.get_tm();
	// 构造时间部分
	/*s_time += std::to_string(ls_ym.tm_year + 1900) + "年";
	s_time += std::to_string(ls_ym.tm_mon + 1) + "月";
	s_time += std::to_string(ls_ym.tm_mday) + "日 ";
	s_time += std::to_string(ls_ym.tm_hour) + "时";
	s_time += std::to_string(ls_ym.tm_min) + "分";*/
	strftime((char*)&s_time, 80, "%Y/%m/%d  %H:%M", &ls_ym);
}

inline void Tool_lib::tool_type_to_string(int in_type, string& s_type)
{
	switch (in_type)
	{
	case 0:
		s_type = "锥度球头";
		break;
	case 1:
		s_type = "平底";
		break;
	case 2:
		s_type = "圆角R";
		break;
	case 3:
		s_type = "成型铣刀";
		break;

	default:
		break;
	}
}

int Tool_Base::save()
{	
	{
		//1、构造一条刀具对象数据
		tool_obj_data ls_row_data;
		ls_row_data.delta_dis_ren = canshu_gg.delta_dis_ren;
		ls_row_data.Sample_lenth = canshu_gg.sample_tool.Sample_lenth;
		ls_row_data.Sample_angle = canshu_gg.sample_tool.Sample_angle;
		ls_row_data.set_safe_p(canshu_gg.gx_safe_p, canshu_gg.sl_safe_p, canshu_gg.cx_safe_p);

		for (int i = 0; i < v_sel_gx.size(); i++)
		{
			ls_row_data.sel_gx[v_sel_gx[i]] = 1;
		}

		//2、保存列表返回对应的位置


		//3 更新
		storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_tool_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));
		
		
		return pos;
	}

	{
		////1、保存列表返回对应的位置
	//pos_xx_list = ptr_list_xx->save();
	//pos_hj_list = ptr_list_hj->save();
	//pos_lx_list = ptr_list_lx->save();
	//pos_fd_list = ptr_list_fd->save();
	//pos_gx_list = ptr_list_gx->save();

	////2、指定文件(对象)、获取存储位置
	//std::ofstream ofs(storage_lib.file_dir_tool_obj, std::ios::binary | std::ios::app);
	//cereal::BinaryOutputArchive archive(ofs);

	////3、序列化
	//archive(pos_xx_list);
	//archive(pos_hj_list);
	//archive(pos_lx_list);
	//archive(pos_fd_list);
	//archive(pos_gx_list);

	//archive(canshu_gg.delta_dis_ren);
	//archive(canshu_gg.sample_tool.Sample_lenth);
	//archive(canshu_gg.sample_tool.Sample_angle);
	//archive(canshu_gg.anquandian.X);
	//archive(canshu_gg.anquandian.Y);
	//archive(canshu_gg.anquandian.Z);
	//archive(canshu_gg.anquandian.A);
	//archive(canshu_gg.anquandian.C);

	////4 更新
	//storage_lib.Storage_base::renew_a_row_data(25, 0, (char*)&w_c2g, sizeof(w_c2g));

	////4.1 写时间和类型文件--先于对象前写入
	//time_updata cur_time;
	//storage_lib.Storage_base::renew_a_row_data(16, pos, (char*)&cur_time, sizeof(cur_time));
	//storage_lib.Storage_base::renew_a_row_data(17, pos, (char*)&type_tool, sizeof(type_tool));

	////4.2、往刀具计数文件写入一条
	//storage_lib.add_tool_count(1);

	////5
	//return pos;
	}
	
}

void Tool_Base::load()
{
	{
		//0 恢复偏心距
		w_c2g = storage_lib.get_tool_w_c2g(pos);

		//1 基本数据结构
		tool_obj_data ls_row_data;
		storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_obj, pos, (char*)&ls_row_data, sizeof(ls_row_data));

		//
		canshu_gg.delta_dis_ren = ls_row_data.delta_dis_ren;
		canshu_gg.sample_tool.Sample_lenth = ls_row_data.Sample_lenth;
		canshu_gg.sample_tool.Sample_angle = ls_row_data.Sample_angle;
		ls_row_data.get_safe_p(canshu_gg.gx_safe_p, canshu_gg.sl_safe_p, canshu_gg.cx_safe_p);

		for (int i = 0; i < 100; i++)
		{
			if (ls_row_data.sel_gx[i] == 1)
			{
				v_sel_gx.push_back(i);
			}
		}

		//
		ptr_list_xx->pos = pos;
		ptr_list_hj->pos = pos;
		ptr_list_lx->pos = pos;
		ptr_list_fd->pos = pos;
		ptr_list_gx->pos = pos;
		//ptr_list_sl->pos = pos;
		
		//
		ptr_list_xx->ptr_tool = this;
		ptr_list_hj->ptr_tool = this;
		ptr_list_lx->ptr_tool = this;
		ptr_list_fd->ptr_tool = this;
		ptr_list_gx->ptr_tool = this;
		ptr_list_sl->ptr_tool = this;

		//
		ptr_list_xx->load();
		ptr_list_hj->load();
		ptr_list_lx->load();
		ptr_list_fd->load();
		ptr_list_gx->load();

		ptr_list_sl->load();

		//
		ptr_list_xx->init_guanxi();
		ptr_list_hj->init_guanxi();
		ptr_list_lx->init_guanxi();
		ptr_list_fd->init_guanxi();
		ptr_list_gx->init_guanxi();
	}
}

int Tool_Base::save_all()
{
	{
		////1、构造一条刀具对象数据
		//tool_obj_data ls_row_data;
		//ls_row_data.delta_dis_ren = canshu_gg.delta_dis_ren;
		//ls_row_data.Sample_lenth = canshu_gg.sample_tool.Sample_lenth;
		//ls_row_data.Sample_angle = canshu_gg.sample_tool.Sample_angle;
		//ls_row_data.X = canshu_gg.gx_safe_p.X;
		//ls_row_data.Y = canshu_gg.gx_safe_p.Y;
		//ls_row_data.Z = canshu_gg.gx_safe_p.Z;
		//ls_row_data.A = canshu_gg.gx_safe_p.A;
		//ls_row_data.C = canshu_gg.gx_safe_p.C;

		////2、保存列表返回对应的位置
		//set_pos(pos);
		//ls_row_data.xx_list_pos = ptr_list_xx->save();
		//ls_row_data.hj_list_pos = ptr_list_hj->save();
		//ls_row_data.lx_list_pos = ptr_list_lx->save();
		//ls_row_data.fd_list_pos = ptr_list_fd->save();
		//ls_row_data.gx_list_pos = ptr_list_gx->save();

		////3 更新
		////storage_lib.Storage_base::renew_a_row_data(0, pos, (char*)&ls_row_data, sizeof(ls_row_data));
		//////
		////storage_lib.Storage_base::renew_a_row_data(25, 0, (char*)&w_c2g, sizeof(w_c2g));

		//////4 写时间和类型文件--先于对象前写入
		////time_updata cur_time;
		////storage_lib.Storage_base::renew_a_row_data(16, pos, (char*)&cur_time, sizeof(cur_time));
		////storage_lib.Storage_base::renew_a_row_data(17, pos, (char*)&type_tool, sizeof(type_tool));

		//return pos;
	}
	return 0;
}

void Tool_Base::set_pos(int in_pos)
{
	pos = in_pos;
	ptr_list_xx->pos = in_pos;
	ptr_list_hj->pos = in_pos;
	ptr_list_lx->pos = in_pos;
	ptr_list_fd->pos = in_pos;
	ptr_list_gx->pos = in_pos;
}
