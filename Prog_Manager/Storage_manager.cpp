#pragma once
#define Prog_Manager_EXPORTS
#include"pch.h"
#include"Miller_GX_CanShu.h"
#include "Tool_Canshu.h"


#include "Storage_manager.h"
#include "TooL_canshu_2.h"
#include<fstream>
#include <filesystem>
#include "Tool_Geo_Obj.h"


Storage_manager save_lib::storage_lib;

int save_lib::error_message_global = 0; //0无错误

class CanShu_GX_KaiCao;
class CanShu_GX_LXC;
class CanShu_GX_DCC_qiu;
class CanShu_GX_DCC_ping;
class CanShu_GX_DCC_yuanjiao;
class CanShu_GX_CX_HDM;
class CanShu_GX_ZQ_HDM;
class CanShu_GX_PD_duan_HDM;
class CanShu_GX_PD_zhu_HDM;
class CanShu_GX_R_HDM;
class CanShu_GX_DJJX;
class CanShu_XingXian;
class CanShu_LuoXuan;
class CanShu_XinHouMian;
class CanShu_BangLiao;
class CanShu_FenDu;
class CanShu_QianJiao;
class CanShu_HouJiao;
class xt_CanShu_HDM_MoXue_XZ_WY;
class _BD_WY_xt_CanShu_HDM_1_MoXue;
class xt_CanShu_HDM_MoXue_QX_WY;
class CanShu_HDM_MoXue_FangFa;
class CanShu_QDM_MoXue_FangFa;
class xt_CanShu_JinTuiDao;
class xt_CanShu_MoXue_BianHuan;
class xt_CanShu_HDM_MoXue_d_XunHuan;
class xt_CanShu_MoXue_XunHuan;
class CanShu_SuDu;
class xt_CanShu_MoXue_ZhenLie;
class xt_CanShu_Range;
class xt_CanShu_Sample;
class xt_Mo_HDM_CanShu;
class xt_Mo_QDM_CanShu;
class xt_gx_shalun;




void tool_obj_data::set_safe_p(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p)
{
	gx_p_X = gx_p.X;
	gx_p_Y = gx_p.Y;
	gx_p_Z = gx_p.Z;
	gx_p_A = gx_p.A;
	gx_p_C = gx_p.C;

	sl_p_X = sl_p.X;
	sl_p_Y = sl_p.Y;
	sl_p_Z = sl_p.Z;
	sl_p_A = sl_p.A;
	sl_p_C = sl_p.C;

	cx_p_X = cx_p.X;
	cx_p_Y = cx_p.Y;
	cx_p_Z = cx_p.Z;
	cx_p_A = cx_p.A;
	cx_p_C = cx_p.C;
}

void tool_obj_data::get_safe_p(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p)
{
	 gx_p.X = gx_p_X;
	 gx_p.Y = gx_p_Y;
	 gx_p.Z = gx_p_Z;
	 gx_p.A = gx_p_A;
	 gx_p.C = gx_p_C;

	 sl_p.X = sl_p_X;
	 sl_p.Y = sl_p_Y;
	 sl_p.Z = sl_p_Z;
	 sl_p.A = sl_p_A;
	 sl_p.C = sl_p_C;

	 cx_p.X = cx_p_X;
	 cx_p.Y = cx_p_Y;
	 cx_p.Z = cx_p_Z;
	 cx_p.A = cx_p_A;
	 cx_p.C = cx_p_C;
}

tool_obj_data::tool_obj_data()
{
	type = -1;
	name = -1;

	delta_dis_ren = 0.01;
	Sample_lenth = 0.01;
	Sample_angle =0.1;

	 gx_p_X = 150.0;
	 gx_p_Y = 200.0;
	 gx_p_Z = 200.0;
	 gx_p_A = 0.0;
	 gx_p_C = -90.0;

	 sl_p_X = 150.0;
	 sl_p_Y = 200.0;
	 sl_p_Z = 200.0;
	 sl_p_A = 0.0;
	 sl_p_C = -90.0;

	 cx_p_X = 150.0;
	 cx_p_Y = 200.0;
	 cx_p_Z = 200.0;
	 cx_p_A = 0.0;
	 cx_p_C = -90.0;

	 for (int i = 0; i < 100; i++)
	 {
		 sel_gx[i] = 0;
	 }
}

tool_obj_data::~tool_obj_data()
{
}


//构造：指定所有文件的名字、将文件的数据大小在此设置

int Storage_manager::add_xingxian(string name, string file_dir, CanShu_XingXian canshu_obj, int tool)
{
	int obj_pos = add_a_xx_(name, file_dir,canshu_obj);
	add_a_xx_to_tool(tool, obj_pos);
	return obj_pos;
}

int Storage_manager::add_houjiao(CanShu_HouJiao canshu_obj, int tool)
{
	int obj_pos = add_a_hj(canshu_obj);
	add_a_hj_to_tool(tool, obj_pos);
	return obj_pos;
}

int Storage_manager::add_fendu(CanShu_FenDu canshu_obj, int tool)
{
	int obj_pos = add_a_fd(canshu_obj);
	add_a_fd_to_tool(tool, obj_pos);
	return obj_pos;
}

int Storage_manager::add_luoxuan(CanShu_LuoXuan canshu_obj, int tool)
{
	int obj_pos = add_a_lx(canshu_obj);
	add_a_lx_to_tool(tool, obj_pos);
	return obj_pos;
}

bool Storage_manager::del_xingxian(int obj_pos_in_tool, int cur_tool)
{
	del_a_xx_from_tool(cur_tool, obj_pos_in_tool);
	obj_list_data ls_data;
	get_tool_xx_list(cur_tool, ls_data);
	//ls_data.
	return true;
}

inline Storage_manager::Storage_manager()
{
	//设置文件名
	{
		//
		file_dir_sl = Storage_base::folder + "sl_obj.txt";
		file_dir_slz = Storage_base::folder + "slz_obj.txt";
		file_dir_dxf = Storage_base::folder + "sl_dxf.txt";
		file_dir_sl_sy = Storage_base::folder + "sl_sy.txt";
		file_dir_slz_sy = Storage_base::folder + "slz_sy.txt";

		//
		file_dir_gx_miller_morenzhi = Storage_base::folder + "gx_miller_morenzhi.txt";
		file_dir_w_c2g = Storage_base::folder + "w_c2g.txt";
		file_dir_mo_gj_trans = Storage_base::folder + "mo_gj_trans.txt";
		file_dir_sl_lib = Storage_base::folder + "jichuang_sl_lib.txt";

		//
		file_dir_mat_2n = Storage_base::folder + "mat_2n.txt";
		file_dir_mat_3n = Storage_base::folder + "mat_3n.txt";
		file_dir_mat_4n = Storage_base::folder + "mat_4n.txt";
	}

#pragma region 创建文件
	//砂轮只创建文件 -- 文件索引号11-15
	fstream file1;
	if (!std::filesystem::exists(file_dir_sl))
	{
		file1.open(file_dir_sl, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_slz))
	{
		file1.open(file_dir_slz, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_dxf))
	{
		file1.open(file_dir_dxf, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_sl_sy))
	{
		file1.open(file_dir_sl_sy, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_slz_sy))
	{
		file1.open(file_dir_slz_sy, std::ios::out | std::ios::binary);
		file1.close();
	}

	if (!std::filesystem::exists(file_dir_gx_miller_morenzhi))
	{
		//fstream file1;
		//file1.open(file_dir_gx_miller_morenzhi, std::ios::out | std::ios::binary);
		//int len_data = sizeof(xt_Mo_HDM_CanShu);	//磨削参数一条数据长度-10.22
		//file1.write((char*)&len_data, len_data);
		//file1.close();
	}
	if (!std::filesystem::exists(file_dir_w_c2g))
	{
		fstream file1;
		file1.open(file_dir_w_c2g, std::ios::out | std::ios::binary);
		int len_data = sizeof(double);
		file1.write((char*)&len_data, sizeof(len_data));
		double w_c2g = 0.0001;
		file1.write((char*)&w_c2g, sizeof(w_c2g));
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_mo_gj_trans))
	{
		fstream file1;
		file1.open(file_dir_mo_gj_trans, std::ios::out | std::ios::binary);
		int len_data =  sizeof(double);
		file1.write((char*)&len_data, sizeof(len_data));
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_sl_lib))
	{
		fstream file1;
		file1.open(file_dir_sl_lib, std::ios::out | std::ios::binary);
		int len_data = sizeof(int);
		file1.write((char*)&len_data, sizeof(len_data));
		int ls_slz_id = -1;
		for (size_t i = 0; i < 6; i++)
		{
			file1.write((char*)&ls_slz_id, sizeof(ls_slz_id));
		}
		file1.close();
	}

	//
	if (!std::filesystem::exists(file_dir_mat_2n))
	{
		fstream file1;
		file1.open(file_dir_mat_2n, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_mat_3n))
	{
		fstream file1;
		file1.open(file_dir_mat_3n, std::ios::out | std::ios::binary);
		file1.close();
	}
	if (!std::filesystem::exists(file_dir_mat_4n))
	{
		fstream file1;
		file1.open(file_dir_mat_4n, std::ios::out | std::ios::binary);
		file1.close();
	}

#pragma endregion
}

Storage_manager::~Storage_manager()
{
}


gx_base_canshu::gx_base_canshu()
{
	type_gx = -1;
	shalun_id = -1;
	sl_pos_in_JC = -1; 
	sl_pos_in_slz = 0;
	sel_fd_id = 0; //默认选第一个，让暂时不报错 25.11.14

	for (int i = 0; i < 6; i++)
	{
		sel_A_before_ren[i] = 0; //选择的刃
	}
}

gx_base_canshu::~gx_base_canshu()
{
}

FZ3D_gj_trans_data::FZ3D_gj_trans_data(vec gj_trans)
{
	x_move = gj_trans(0);
	y_move = gj_trans(1);
	z_move = gj_trans(2);
}

FZ3D_gj_trans_data::FZ3D_gj_trans_data()
{
	x_move = 0.0;
	y_move = 0.0;
	z_move = 0.0;
}

FZ3D_gj_trans_data::~FZ3D_gj_trans_data()
{

}

sl_zu_num_data::sl_zu_num_data(vector<int>& in_sl_zu)
{
	sl_zu_1_num = in_sl_zu[0];
	sl_zu_2_num = in_sl_zu[1];
	sl_zu_3_num = in_sl_zu[2];
	sl_zu_4_num = in_sl_zu[3];
	sl_zu_5_num = in_sl_zu[4];
	sl_zu_6_num = in_sl_zu[5];
}

sl_zu_num_data::sl_zu_num_data()
{
	sl_zu_1_num = -1;
	sl_zu_2_num = -1;
	sl_zu_3_num = -1;
	sl_zu_4_num = -1;
	sl_zu_5_num = -1;
	sl_zu_6_num = -1;
}

sl_zu_num_data::~sl_zu_num_data()
{
}

xingxian_name_data::xingxian_name_data()
{
	type = 0;
}

xingxian_name_data::~xingxian_name_data()
{
}

xingxian_catalog::xingxian_catalog()
{
	type = 0;
}

xingxian_catalog::~xingxian_catalog()
{

}

string save_lib::get_error_message_txt()
{
	switch (error_message_global)
	{
	case 0:
		return "无错误";

	case -1:
		return "刀路计算错误";
	case -2:
		return "开槽计算错误";
	case -3:
		return "后刀面求交计算错误";
	default:
		break;
	}
	return "无错误";
}

save_lib::save_lib()
{
}

save_lib::~save_lib()
{
}

int save_lib::save(int pos)
{
	return 0;
}

void save_lib::load(int pos)
{
}

gx_cx_kaicao_can_data::gx_cx_kaicao_can_data()
{
	 pos_ang_qian=-1;
	lx_pos = -1; 
	 percent_start= -1.0;
	percent_end = -1.0;
	//angle_qiexue = -1.0;

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1; //选择的刃
	}
}

gx_cx_kaicao_can_data::~gx_cx_kaicao_can_data()
{
}

gx_dcc_qiu_can_data::gx_dcc_qiu_can_data()
{
	pos_b_qianjiao_n = -1;
	dis_to_center = 0.0;
	dis_end_extend = 0.0;

	high_up_o = 0.0;	  //
	ang_up = 0.0;	      //
	percent_r =0.0;
	ang_down = 0.0;	  //

	//angle_qiexue = 5.0;
	ang_hen_tui = 45.0; 
	dis_hen_tui = 45.0; 

	for (int i = 0; i < 6; i++)
	{
		selected_ren[i] = -1; //选择的刃
	}

}

gx_dcc_qiu_can_data::~gx_dcc_qiu_can_data()
{
}

obj_list_data::obj_list_data()
{
	xx_count = 0;
	empty_count = 0;
	empty_id_count = 100;
	for (int i = 0; i < 100; i++)
	{
		obj_pos[i] = -1; 
		empty_pos[i] = -1;
		obj_index_show_queue[i] = -1;
		id_to_show_index[i] = 0;
		show_index_to_id[i] = 0;
		empty_id[i] = 100 - 1 - i;
	}
}

obj_list_data::~obj_list_data()
{
}

int obj_list_data::get_show_index_by_id(int id)
{
	return id + id_to_show_index[id];
}

int obj_list_data::get_id_by_show_index(int show_index)
{
	return show_index + show_index_to_id[show_index];
}

int obj_list_data::get_obj_pos_by_id(int id)
{
	int show = get_show_index_by_id(id);
	return get_obj_pos_by_show_index(show);
}

int obj_list_data::get_obj_pos_by_show_index(int show_index)
{
	return obj_pos[obj_index_show_queue[show_index]];
}

bool obj_list_data::add_an_obj(int abs_pos)
{
	if (xx_count == 100)
	{
		return false;
	}
	if (empty_count == 0)
	{
		obj_pos[xx_count] = abs_pos;
		obj_index_show_queue[xx_count] = xx_count;
	}
	else
	{
		obj_pos[empty_pos[empty_count - 1]] = abs_pos;
		obj_index_show_queue[xx_count] = empty_pos[empty_count - 1];
		empty_pos[empty_count - 1] = -1;
		empty_count--;
	}


	//
	int ls_id = empty_id[empty_id_count - 1];
	empty_id_count--;

	//
	show_index_to_id[xx_count] = ls_id - xx_count;

	//
	id_to_show_index[ls_id] = xx_count - ls_id;

	//
	xx_count++;

	return true;
}

bool obj_list_data::del_an_obj(int sel_order)
{
	int sto_i = get_obj_pos_by_show_index(sel_order);

	if (xx_count > 0)
	{
		//
		obj_pos[sto_i] = -1;
		empty_pos[empty_count] = sto_i;
		empty_count++;

		//
		int id_now = get_id_by_show_index(sel_order);
		empty_id[empty_id_count] = id_now;
		empty_id_count++;
		
		//删除位设置0
		id_to_show_index[get_id_by_show_index(sel_order)] = 0;

		for (size_t i = sel_order; i < xx_count-1; i++)
		{
			obj_index_show_queue[i] = obj_index_show_queue[i + 1];
			show_index_to_id[i] = show_index_to_id[i + 1];
			show_index_to_id[i]++;
			id_to_show_index[get_id_by_show_index(i+1)]--;
		}
		obj_index_show_queue[xx_count - 1] = -1;
		show_index_to_id[xx_count - 1] = 0;
		//id_to_show_index[get_id_by_show_index(xx_count -1)]--;
		//
		xx_count--;

		return true;
	}
	else
	{
		return false;
	}

}

bool obj_list_data::swap_order(int queue_index1, int queue_index2)
{
	if (queue_index1 < xx_count)
	{
		if (queue_index2 < xx_count)
		{

			int id1 = get_id_by_show_index(queue_index1);
			int id2 = get_id_by_show_index(queue_index2);

			//
			int mid = 0;
			mid = obj_index_show_queue[queue_index1];
			obj_index_show_queue[queue_index1] = obj_index_show_queue[queue_index2];
			obj_index_show_queue[queue_index2] = mid;

			int cha = queue_index2 - queue_index1;
			//
			int before_1 = show_index_to_id[queue_index2];
			int before_2 = show_index_to_id[queue_index1];
			show_index_to_id[queue_index1] = before_1 - cha;
			show_index_to_id[queue_index2] = before_2 + cha;

			//
			id_to_show_index[id1] = +cha;
			id_to_show_index[id2] = -cha;

			return true;
		}
	}
	return false;
}

int obj_list_data::get_sto_index(int show_index)
{
	return obj_index_show_queue[show_index];
}

int obj_list_data::where_in_show_queue(int abs_pos)
{
	return 0;
}

int Storage_base::add_a_row_data(string file, const char* dir, int lenth)
{
	//1 打开文件
	fstream file1;

	file1.open(file, std::ios::in | std::ios::out | std::ios::binary);

	if (!file1.is_open())
	{
		throw - 1;
	}

	//2 读取文件头信息
	file1.seekg(0);
	int len_data = -1;
	file1.read((char*)&len_data, sizeof(len_data));
	int count_data = -1;//空行也算
	file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
	int empty_count = -1;
	file1.read((char*)&empty_count, sizeof(empty_count));
	file1.clear();

	//3 
	int ans_pos = -1;
	if (empty_count > 0)
	{
		//读取空白位最后一个index
		file1.seekg(head_size + count_data * len_data + (empty_count - 1) * sizeof(int));
		file1.read((char*)&ans_pos, sizeof(ans_pos));
		file1.clear();

		//在空白位写入数据
		file1.seekp(head_size + ans_pos * len_data);
		file1.write(dir, lenth);

		empty_count--;
		file1.seekp(2 * sizeof(int)); //write定位
		file1.write((char*)&empty_count, sizeof(empty_count));
	}
	else
	{
		file1.clear();
		file1.seekp(head_size + count_data * len_data);
		file1.write(dir, lenth);
		count_data++;
		//如果没有空行，则后续没有空行编号
		ans_pos = count_data-1; //后用最大位置
		file1.seekp(1*sizeof(int)); //write定位
		file1.write((char*)&count_data, sizeof(count_data));

	}


	file1.close();

	return ans_pos;
}

//往指定file文件，读取行数index的内容到dir
inline bool Storage_base::read_a_row_data(string file, int index, char* dir, int lenth)
{
	//根据文件标志在对应数据文件中读数据
	fstream file2;
	file2.open(file, std::ios::in | std::ios::binary);
	if (!file2.is_open())
	{
		throw - 1;
	}

	file2.seekg(0, ios::beg);
	int data_lenth = -1;
	file2.read((char*)(&data_lenth), sizeof(data_lenth));
	file2.seekg(head_size + index * data_lenth, ios::beg);
	file2.read(dir, lenth);
	file2.clear();

	file2.close();

	return 1;
}

//往指定file文件，更新一行数据
inline void Storage_base::edit_a_row_data(string file, int index, char* dir, int lenth)
{
	//打开文件
	fstream file2;
	file2.open(file, std::ios::in | std::ios::out | std::ios::binary);
	if (!file2.is_open())
	{
		throw - 1;
	}

	//读取一个int，第一个int是数据条目的长度，int之后每个条目等长
	file2.seekg(0);
	int len_data2 = -1;
	file2.read((char*)&len_data2, sizeof(len_data2));


	file2.clear();
	//根据读取的长度，转跳到对条目的位置
	file2.clear();
	file2.seekp(head_size +index * len_data2);//第一行不是数据条；将数据条存放最大位置从1开始 24.6.28？？？？
	//写入数据内容
	file2.write(dir, lenth);

	//关闭
	file2.close();
}

void Storage_base::delete_a_row_data(string file, int index)
{
	//1 打开文件
	fstream file1;
	file1.open(file, std::ios::in | std::ios::out | std::ios::binary);
	if (!file1.is_open())
	{
		throw - 1;
	}

	//2 读取文件头信息
	file1.seekg(0);
	int len_data = -1;
	file1.read((char*)&len_data, sizeof(len_data));
	int count_data = -1;//空行也算
	file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
	int empty_count = -1;
	file1.read((char*)&empty_count, sizeof(empty_count));

	//3 校验是否超出总数
	if (index > count_data - 1)
	{
		return;
	}

	//4 校验是否已经被删
	for (size_t i = 0; i < empty_count; i++)
	{
		//读取空白位最后一个index
		int empty_pos = -1;
		file1.seekg(head_size + count_data * len_data);
		file1.read((char*)&empty_pos, sizeof(empty_pos));
		if (index == empty_pos)
		{
			return;
		}
	}

	//5 删除
	//5.1
	file1.clear();
	file1.seekp(head_size + count_data * len_data + empty_count * sizeof(int));
	file1.write((char*)&index, sizeof(index));
	//5.2
	file1.seekp(2 * sizeof(int));
	empty_count++;
	file1.write((char*)&empty_count, sizeof(empty_count));
}


Storage_base::Storage_base()
{
}

Storage_base::~Storage_base()
{
}

inline void Storage_base::str_to_buffer(string& name)
{
	//int len = name.size();
	//if (len >= NAME_BUFFER_SIZE)
	//{
	//	throw - 1;
	//}
	//for (int i = 0; i < len; i++)
	//{
	//	name_buffer[i] = name[i];
	//}


	if (name.size() >= NAME_BUFFER_SIZE) {
		throw std::length_error("Input string is too long for name_buffer");
	}

	// 清空缓冲区（可选）
	std::memset(name_buffer, 0, NAME_BUFFER_SIZE);

	// 拷贝字符串内容
	name.copy(name_buffer, name.size());

	// 确保以 '\0' 结尾
	name_buffer[name.size()] = '\0';
}

inline void Storage_base::buffer_to_str(string& name)
{
	name.assign(name_buffer, strnlen(name_buffer, NAME_BUFFER_SIZE));
	//name.clear();
	//name.resize(NAME_BUFFER_SIZE);

	//for (int i = 0; i < NAME_BUFFER_SIZE; i++)
	//{
	//	//C 风格字符串，找到第一个 \0 终止符的位置，仅拼接有效内容 -4.14
	//	if (name_buffer[i] != '\0')
	//	{
	//		name = name + name_buffer[i];
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
}

//往指定file文件，更新一行数据
inline int Storage_tool_list::add_a_tool(int type, string name)
{
	//写name文件
	str_to_buffer(name);//字符串转数组
	int ans_pos = add_a_row_data(file_dir_tool_name, name_buffer, NAME_BUFFER_SIZE);

	//初始其他刀具文件
	tool_obj_data ls_obj;
	ls_obj.type = type;
	ls_obj.name = ans_pos;
	//2
	edit_a_row_data(file_dir_tool_obj, ans_pos, (char*)&ls_obj, sizeof(tool_obj_data));

	//3
	{
		if (type == 0)
		{
			CanShu_Geo_ZQ ls_geo;
			edit_a_row_data(file_dir_tool_data, ans_pos, (char*)&ls_geo, sizeof(ls_geo));
		}
		if (type == 1)
		{
			CanShu_Geo_PD ls_geo;
			edit_a_row_data(file_dir_tool_data, ans_pos, (char*)&ls_geo, sizeof(ls_geo));
		}
		if (type == 2)
		{
			CanShu_Geo_R ls_geo;
			edit_a_row_data(file_dir_tool_data, ans_pos, (char*)&ls_geo, sizeof(ls_geo));
		}
		if (type == 3)
		{
			CanShu_Geo_CX ls_geo;
			edit_a_row_data(file_dir_tool_data, ans_pos, (char*)&ls_geo, sizeof(ls_geo));
		}
	}

	//4
	time_updata ls_time;
	edit_a_row_data(file_dir_tool_time, ans_pos, (char*)&ls_time, sizeof(time_updata));
	//5
	edit_a_row_data(file_dir_tool_type, ans_pos, (char*)&type, sizeof(type));

	//Point_by_5axis ls_p;
	//renew_a_row_data(file_dir_tool_type, ans_pos, (char*)&type, sizeof(type));
	
	//6
	obj_list_data ls_list;
	edit_a_row_data(file_dir_tool_list_xx, ans_pos, (char*)&ls_list, sizeof(obj_list_data));
	edit_a_row_data(file_dir_tool_list_hj, ans_pos, (char*)&ls_list, sizeof(obj_list_data));
	edit_a_row_data(file_dir_tool_list_lx, ans_pos, (char*)&ls_list, sizeof(obj_list_data));
	edit_a_row_data(file_dir_tool_list_fd, ans_pos, (char*)&ls_list, sizeof(obj_list_data));
	edit_a_row_data(file_dir_tool_list_gx, ans_pos, (char*)&ls_list, sizeof(obj_list_data));

	//7
	add_tool_count(1);

	return ans_pos;
}

inline bool Storage_tool_list::del_a_tool(int pos)
{
	//步骤1
	delete_a_row_data(file_dir_tool_name, pos);

	//步骤2
	add_tool_count(0);
	return true;
}

inline void Storage_tool_list::get_tool_obj_canshu(int pos, tool_obj_data& ans_data)
{
	read_a_row_data(file_dir_tool_obj, pos, (char*)&ans_data, sizeof(ans_data));
}

inline void Storage_tool_list::set_tool_obj_canshu(int pos, tool_obj_data& ans_data)
{
	edit_a_row_data(file_dir_tool_obj, pos, (char*)&ans_data, sizeof(ans_data));
}

//调用读一行数据实现，打开文件指定，输入已经指定，函数没存在必要，
//接口就是read，只需要增加相关的增删 25.7.1

inline void Storage_tool_list::get_tool_canshu(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_tool_data, pos, dir, lenth);
}

inline void Storage_tool_list::set_tool_canshu(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_tool_data, pos, dir, lenth);
}

inline string Storage_tool_list::get_tool_name(int pos)
{
	read_a_row_data(file_dir_tool_name, pos, name_buffer, NAME_BUFFER_SIZE);
	string ans_name;
	buffer_to_str(ans_name);
	return ans_name;
}

inline void Storage_tool_list::set_tool_name(int pos, string name)
{
	str_to_buffer(name);
	edit_a_row_data(file_dir_tool_name, pos, name_buffer, NAME_BUFFER_SIZE);
}

inline void Storage_tool_list::get_tool_time(int pos, time_updata& ans_time)
{
	read_a_row_data(file_dir_tool_time, pos, (char*)&ans_time, sizeof(ans_time));
}

inline void Storage_tool_list::set_tool_time(int pos, time_updata& ans_time)
{
	edit_a_row_data(file_dir_tool_time, pos, (char*)&ans_time, sizeof(ans_time));
}

inline int Storage_tool_list::get_tool_type(int pos)
{
	int ans_type = -1;
	read_a_row_data(file_dir_tool_type, pos,(char*)&ans_type, sizeof(ans_type));
	return ans_type;
}

//inline void Storage_tool_fun::set_tool_type(int pos, char* dir, int lenth)
//{
//	renew_a_row_data(file_dir_tool_type, pos, dir, lenth);
//}

//传数组的地址

inline void Storage_tool_list::get_tool_xx_list(int pos, obj_list_data& ans_list)
{
	read_a_row_data(file_dir_tool_list_xx, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::set_tool_xx_list(int pos, obj_list_data& ans_list)
{
	edit_a_row_data(file_dir_tool_list_xx, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::get_tool_hj_list(int pos, obj_list_data& ans_list)
{
	read_a_row_data(file_dir_tool_list_hj, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::set_tool_hj_list(int pos, obj_list_data& ans_list)
{
	edit_a_row_data(file_dir_tool_list_hj, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::get_tool_lx_list(int pos, obj_list_data& ans_list)
{
	read_a_row_data(file_dir_tool_list_lx, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::set_tool_lx_list(int pos, obj_list_data& ans_list)
{
	edit_a_row_data(file_dir_tool_list_lx, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::get_tool_fd_list(int pos, obj_list_data& ans_list)
{
	read_a_row_data(file_dir_tool_list_fd, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::set_tool_fd_list(int pos, obj_list_data& ans_list)
{
	edit_a_row_data(file_dir_tool_list_fd, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::get_tool_gx_list(int pos, obj_list_data& ans_list)
{
	read_a_row_data(file_dir_tool_list_gx, pos, (char*)&ans_list, sizeof(ans_list));
}

inline void Storage_tool_list::set_tool_gx_list(int pos, obj_list_data& ans_list)
{
	edit_a_row_data(file_dir_tool_list_gx, pos, (char*)&ans_list, sizeof(ans_list));
}

//只移动刀里工序列表的数据

inline bool Storage_tool_list::move_up_a_gx(int tool_pos, int cur_order, int up_order)
{
	obj_list_data ls_data;
	get_tool_gx_list(tool_pos, ls_data);

	int temp_pos = ls_data.obj_pos[cur_order];
	ls_data.obj_pos[cur_order] = ls_data.obj_pos[up_order];
	ls_data.obj_pos[up_order] = temp_pos;

	set_tool_gx_list(tool_pos, ls_data);

	return 1;
}

inline bool Storage_tool_list::move_down_a_gx(int tool_pos, int cur_order, int down_order)
{
	obj_list_data ls_data;
	get_tool_gx_list(tool_pos, ls_data);

	int temp_pos = ls_data.obj_pos[cur_order];
	ls_data.obj_pos[cur_order] = ls_data.obj_pos[down_order];
	ls_data.obj_pos[down_order] = temp_pos;

	set_tool_gx_list(tool_pos, ls_data);

	return 1;
}

//更新刀具计数--真为加，假为减


//check
inline bool Storage_tool_list::add_tool_count(bool add)
{
	int ls_count = get_tool_count();
	if (add)
	{
		ls_count++;
	}
	else
	{
		ls_count-- ;
	}	
	edit_a_row_data(file_dir_tool_count, 0, (char*)&ls_count, sizeof(ls_count));
	return true;
}
//check
inline int Storage_tool_list::get_tool_count()
{
	int count = -1;
	read_a_row_data(file_dir_tool_count, 0, (char*)&count, sizeof(count));
	return count;
}

void Storage_tool_list::add_a_xx_to_tool(int tool_pos, int obj_pos_abs)
{
	add_a_obj_to_tool(file_dir_tool_list_xx, tool_pos, obj_pos_abs);
}

void Storage_tool_list::add_a_hj_to_tool(int tool_pos, int obj_pos_abs)
{
	add_a_obj_to_tool(file_dir_tool_list_hj, tool_pos, obj_pos_abs);
}

void Storage_tool_list::add_a_lx_to_tool(int tool_pos, int obj_pos_abs)
{
	add_a_obj_to_tool(file_dir_tool_list_lx, tool_pos, obj_pos_abs);
}

void Storage_tool_list::add_a_fd_to_tool(int tool_pos, int obj_pos_abs)
{
	add_a_obj_to_tool(file_dir_tool_list_fd, tool_pos, obj_pos_abs);
}

void Storage_tool_list::add_a_gx_to_tool(int tool_pos, int obj_pos_abs)
{
	add_a_obj_to_tool(file_dir_tool_list_gx, tool_pos, obj_pos_abs);
}

void Storage_tool_list::del_a_xx_from_tool(int tool_pos, int sel_order)
{
	obj_list_data ls_list;
	read_a_row_data(file_dir_tool_list_xx, tool_pos, (char*)&ls_list, sizeof(ls_list));

	ls_list.del_an_obj(sel_order);

	edit_a_row_data(file_dir_tool_list_xx, tool_pos, (char*)&ls_list, sizeof(ls_list));

	obj_list_data ls_list1;

	read_a_row_data(file_dir_tool_list_hj, tool_pos, (char*)&ls_list1, sizeof(ls_list1));

	//for (int i = 0; i <ls_list1.xx_count; i++)
	//{
	//	CanShu_HouJiao ls_canshu;
	//	read_a_row_data(file_dir_hj_canshu, tool_pos, (char*)&ls_list, sizeof(ls_list));
	//	ls_list1.obj_abs_pos(i)
	//}


}

void Storage_tool_list::del_a_hj_from_tool(int tool_pos, int sel_order)
{
	obj_list_data ls_list;
	read_a_row_data(file_dir_tool_list_hj, tool_pos, (char*)&ls_list, sizeof(ls_list));

	ls_list.del_an_obj(sel_order);

	edit_a_row_data(file_dir_tool_list_hj, tool_pos, (char*)&ls_list, sizeof(ls_list));
}

void Storage_tool_list::del_a_lx_from_tool(int tool_pos, int sel_order)
{
	obj_list_data ls_list;
	read_a_row_data(file_dir_tool_list_lx, tool_pos, (char*)&ls_list, sizeof(ls_list));

	ls_list.del_an_obj(sel_order);

	edit_a_row_data(file_dir_tool_list_lx, tool_pos, (char*)&ls_list, sizeof(ls_list));
}

void Storage_tool_list::del_a_fd_from_tool(int tool_pos, int sel_order)
{
	obj_list_data ls_list;
	read_a_row_data(file_dir_tool_list_fd, tool_pos, (char*)&ls_list, sizeof(ls_list));

	ls_list.del_an_obj(sel_order);

	edit_a_row_data(file_dir_tool_list_fd, tool_pos, (char*)&ls_list, sizeof(ls_list));
}

void Storage_tool_list::del_a_gx_from_tool(int tool_pos, int sel_order)
{
	obj_list_data ls_list;
	read_a_row_data(file_dir_tool_list_gx, tool_pos, (char*)&ls_list, sizeof(ls_list));

	//for (int i = sel_order; i < ls_list.xx_count - 1; i++)
	//{
	//	ls_list.xx_pos[sel_order] = ls_list.xx_pos[sel_order + 1];
	//}
	//ls_list.xx_pos[ls_list.xx_count - 1] = -1;
	//ls_list.xx_count--;

	ls_list.del_an_obj(sel_order);

	edit_a_row_data(file_dir_tool_list_gx, tool_pos, (char*)&ls_list, sizeof(ls_list));
}

//获取当前被删除后刀具对象空位
//将value加入到file文件中的第tool_pos位置的表中
void Storage_tool_list::add_a_obj_to_tool(string file, int tool_pos, int obj_pos_in)
{
	//刀的工序列表增加一个xx
	obj_list_data ls_list;
	read_a_row_data(file, tool_pos, (char*)&ls_list, sizeof(ls_list));

	ls_list.add_an_obj(obj_pos_in);

	edit_a_row_data(file, tool_pos, (char*)&ls_list, sizeof(ls_list));
}

//check
inline bool Storage_tool_list::get_empty_pos(set<int>& del_pos)
{
	fstream file1;
	{
		file1.open(file_dir_tool_name, std::ios::in | std::ios::out | std::ios::binary);
		if (!file1.is_open())
		{
			throw -1;
		}
		//读出当前数量
		file1.seekg(0);
		int len_data = -1;
		file1.read((char*)&len_data, sizeof(len_data));
		int count_data = -1;//空行也算
		file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
		int empty_count = -1;
		file1.read((char*)&empty_count, sizeof(empty_count));

		//遍历出空行号
		for (int i = 0; i < empty_count; i++)
		{
			int cur_pos = -1;
			file1.seekg(head_size + len_data * count_data);
			file1.read((char*)(&cur_pos), sizeof(cur_pos));
			del_pos.insert(cur_pos);
		}
		file1.close();
		return true;
	}
}
//check
inline void Storage_tool_list::read_type(vector<int>& ans_v_type)
{
	fstream file2;
	{
		file2.open(file_dir_tool_type, std::ios::in | std::ios::binary);
		if (!file2.is_open())
		{
			throw - 1;
		}
		//数据长度
		file2.seekg(head_size, ios::beg);//偏置head_size，直接读数据 25.11.14
		//int len_data2 = -1;
		//file2.read((char*)(&len_data2), sizeof(len_data2));
		//读到文件末尾
		while (1)
		{
			if (file2.eof())
			{
				break;
			}
			int ls_type = -1;
			file2.read((char*)(&ls_type), sizeof(ls_type));
			if (ls_type != -1)
			{
				ans_v_type.push_back(ls_type);
			}
		}

		file2.close();
		return;
	}
}

inline Storage_tool_list::Storage_tool_list()
{
	//设置文件名
	{
		file_dir_tool_obj = folder + "tool_obj.txt";
		file_dir_tool_data = folder + "tool_data.txt";
		file_dir_tool_name = folder + "tool_name.txt";
		file_dir_tool_time = folder + "tool_time.txt";
		file_dir_tool_type = folder + "tool_type.txt";
		file_dir_tool_list_xx = folder + "tool_list_xx.txt";
		file_dir_tool_list_hj = folder + "tool_list_hj.txt";
		file_dir_tool_list_lx = folder + "tool_list_lx.txt";
		file_dir_tool_list_fd = folder + "tool_list_fd.txt";
		file_dir_tool_list_gx = folder + "tool_list_gx.txt";
		file_dir_tool_write = folder + "tool_save_pos.txt";

		file_dir_tool_count = folder + "tool_count.txt";
	}

#pragma region 创建文件
	//创建文件-并写入数据，存在就不打开直接过
	//工序文件初始化
	if (!std::filesystem::exists(file_dir_tool_obj))
	{
		fstream file1;			//in|out 模式不会创建文件
		file1.open(file_dir_tool_obj, std::ios::out | std::ios::binary);
		int len_data = 100 * sizeof(double);	//刀具对象一条数据长度
		file1.write((char*)&len_data, sizeof(len_data)); //直接写一条数据长度

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_data))
	{
		fstream file1;
		file1.open(file_dir_tool_data, std::ios::out | std::ios::binary);
		int len_data = 100 * sizeof(double);	//刀具数据一条数据长度//成型刀需要更大空间 4.8
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_name))
	{
		fstream file1;
		file1.open(file_dir_tool_name, std::ios::out | std::ios::binary);
		int len_data = NAME_BUFFER_SIZE;	//刀具name一条数据长度
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_time))
	{
		fstream file1;
		file1.open(file_dir_tool_time, std::ios::out | std::ios::binary);
		int len_data = sizeof(time_updata);	//刀具time一条数据长度
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();

	}
	if (!std::filesystem::exists(file_dir_tool_type))
	{
		fstream file1;
		file1.open(file_dir_tool_type, std::ios::out | std::ios::binary);
		int len_data = sizeof(int);	//刀具type一条数据长度
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_list_xx))
	{
		fstream file1;
		file1.open(file_dir_tool_list_xx, std::ios::out | std::ios::binary);
		int len_data = sizeof(obj_list_data);
		file1.write((char*)&len_data, sizeof(len_data));
		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_list_hj))
	{
		fstream file1;
		file1.open(file_dir_tool_list_hj, std::ios::out | std::ios::binary);
		int len_data = sizeof(obj_list_data);
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_list_lx))
	{
		fstream file1;
		file1.open(file_dir_tool_list_lx, std::ios::out | std::ios::binary);
		int len_data = sizeof(obj_list_data);
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_list_fd))
	{
		fstream file1;
		file1.open(file_dir_tool_list_fd, std::ios::out | std::ios::binary);
		int len_data = sizeof(obj_list_data);
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_list_gx))
	{
		fstream file1;
		file1.open(file_dir_tool_list_gx, std::ios::out | std::ios::binary);
		int len_data = sizeof(obj_list_data);
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_write))
	{
		fstream file1;
		file1.open(file_dir_tool_write, std::ios::out | std::ios::binary);
		int len_data = sizeof(int);
		file1.write((char*)&len_data, sizeof(len_data));

		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.close();
	}
	if (!std::filesystem::exists(file_dir_tool_count))
	{
		fstream file1;
		file1.open(file_dir_tool_count, std::ios::out | std::ios::binary);
		int len_data = sizeof(int);	//刀具count一条数据长度
		file1.write((char*)&len_data, sizeof(len_data));
		int data_count = 0;
		int empty_count = 0;
		file1.write((char*)&data_count, sizeof(data_count));
		file1.write((char*)&empty_count, sizeof(empty_count));

		file1.seekp(head_size + 0); 
		file1.write((char*)&data_count, sizeof(data_count));

		file1.close();
	}
#pragma endregion
}

inline Storage_tool_list::~Storage_tool_list()
{

}

//
//inline int Storage_gx_fun::add_a_row_data(string file, const char* dir, int lenth)
//{
//	//1、先读管理写的文件2-4，找到可以存放对象的位置
//	fstream file1;
//	if (file_dir_gx_name == file)
//	{
//		file1.open(file_dir_gx_write, std::ios::in | std::ios::out | std::ios::binary);
//	}
//
//	if (!file1.is_open())
//	{
//		throw -1;
//	}
//	file1.seekg(0);
//	int len_data = -1;
//	file1.read((char*)&len_data, sizeof(len_data));
//	int count_data = -1;
//	file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
//	int empty_count = -1;
//	file1.read((char*)&empty_count, sizeof(empty_count));
//
//	int tool_save_pos = -1;
//	if (empty_count > 0)
//	{
//		file1.seekg((2 + empty_count) * len_data); //起始定位
//		file1.read((char*)&tool_save_pos, sizeof(tool_save_pos));
//		//不删除内容下次写入覆盖，依据空行数量判断位置有效性
//		empty_count--;
//	}
//	else
//	{
//		tool_save_pos = count_data; //后用最大位置
//		count_data++;
//	}
//
//	//2、加对象时更新最大存放位置
//	//25.6.25 当前新建tool + gx，是通过name文件开始，加判断 file=8 
//	//if (in_file == 4 || in_file == 0 || in_file == 21 
//	//	|| in_file == 8 || in_file == 9)
//	{
//		file1.seekp(1 * len_data); //write定位
//		file1.write((char*)&count_data, sizeof(count_data));
//		file1.seekp(2 * len_data); //write定位
//		file1.write((char*)&empty_count, sizeof(empty_count));
//	}
//
//	file1.close();
//
//	//3、根据文件标志在对应数据文件中写入数据
//	fstream file2;
//	file2.open(file, std::ios::in | std::ios::out | std::ios::binary);
//
//	file2.seekg(0);
//	int len_data2 = -1;
//	file2.read((char*)&len_data2, sizeof(len_data2));
//	file2.seekp(tool_save_pos * len_data2);
//	file2.write(dir, lenth);
//
//	file2.close();
//
//	return tool_save_pos;
//}

inline int Storage_gx_fun::add_a_gx(int type, string name)
{
	//写name文件
	str_to_buffer(name);//字符串转数组
	int pos = add_a_row_data(file_dir_gx_name, name_buffer, NAME_BUFFER_SIZE);

	//初始其他刀具文件
	gx_base_canshu ls_obj;
	ls_obj.type_gx = type;
	edit_a_row_data(file_dir_gx_base_canshu, pos, (char*)&ls_obj, sizeof(ls_obj));

	//工序参数
	bool is_hdm_fangfa = 1;
	{
		if (type == 0)
		{
			CanShu_GX_KaiCao ls_geo;
			ls_geo.save(pos);

			is_hdm_fangfa = 0;
		}
		if (type == 1)
		{
			CanShu_GX_LXC ls_geo;
			ls_geo.save(pos);

			is_hdm_fangfa = 0;
		}
		if (type == 2)
		{
			CanShu_GX_DCC_qiu ls_geo;
			ls_geo.save(pos);

			is_hdm_fangfa = 0;
		}
		if (type == 3)
		{
			CanShu_GX_DCC_ping ls_geo;
			ls_geo.save(pos);

			is_hdm_fangfa = 0;
		}
		if (type == 4)
		{
			CanShu_GX_DCC_yuanjiao ls_geo;
			ls_geo.save(pos);

			is_hdm_fangfa = 0;
		}
		if (type == 5)
		{
			CanShu_GX_CX_HDM ls_geo;
			ls_geo.save(pos);
		}
		if (type == 6)
		{
			CanShu_GX_ZQ_HDM ls_geo;
			ls_geo.save(pos);
		}
		if (type == 7)
		{
			CanShu_GX_PD_duan_HDM ls_geo;
			ls_geo.save(pos);
		}
		if (type == 8)
		{
			CanShu_GX_PD_zhu_HDM ls_geo;
			ls_geo.save(pos);
		}
		if (type == 9)
		{
			CanShu_GX_R_HDM ls_geo;
			ls_geo.save(pos);
		}
		if (type == 10)
		{
			CanShu_GX_DJJX ls_geo;
			ls_geo.save(pos);
		}
	}

	


	{
		//xt_CanShu_Range ls_range;
		//ls_range.pos = ans_pos;
		//ls_range.save();
		////renew_a_row_data(file_dir_gx_range, ans_pos, (char*)&ls_obj, sizeof(tool_obj_data));


		//xt_CanShu_Sample ls_sample;
		//ls_sample.pos = ans_pos;
		//ls_sample.save();

		//xt_CanShu_JinTuiDao ls_jtd;
		//ls_jtd.pos = ans_pos;
		//ls_jtd.save();


		////循环不写
		//xt_CanShu_MoXue_BianHuan ls_bh;
		//ls_bh.pos = ans_pos;
		////ls_bh.save();

		//xt_CanShu_MoXue_ZhenLie ls_zl;
		//ls_zl.pos = ans_pos;
		////ls_zl.save();

		//CanShu_SuDu ls_sd;
		//ls_sd.pos = ans_pos;
		//ls_sd.save();

		//double ls_A_before = 0.0;
		//renew_a_row_data(file_dir_gx_A_before, ans_pos, (char*)&ls_A_before, sizeof(ls_A_before));

	}
	
	//磨面参数 7.8
	if (is_hdm_fangfa)
	{
		xt_Mo_HDM_CanShu ls_mo;
		ls_mo.save(pos);
	}
	else
	{
		xt_Mo_QDM_CanShu ls_mo;
		ls_mo.save(pos);
	}


	//刀的工序列表增加一个工序
	//xx_list_data ls_list;
	//read_a_row_data(file_dir_tool_list_gx, ans_pos, (char*)&ls_list, sizeof(ls_list));
	//int ls_pos = -1;
	//if (ls_list.empty_count)
	//{
	//	ls_pos = ls_list.empty_pos[0];
	//}
	//ls_list.xx_pos[ls_list.xx_count] = ls_pos;
	//for (int i = 0; i < ls_list.empty_count; i++)
	//{
	//	if (i < ls_list.empty_count - 1)
	//	{
	//		ls_list.empty_pos[i] = ls_list.empty_pos[i + 1];
	//	}
	//	else
	//	{
	//		ls_list.empty_pos[i] = -1;
	//	}

	//}
	//ls_list.xx_count++;
	//ls_list.empty_count--;
	//renew_a_row_data(file_dir_tool_list_gx, ans_pos, (char*)&ls_list, sizeof(ls_list));


	return pos;
}

inline bool Storage_gx_fun::del_a_gx(int in_pos)
{
	delete_a_row_data(file_dir_gx_name, in_pos);

	return true;
}


inline void Storage_gx_fun::get_gx_obj_canshu(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_base_canshu, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_obj_canshu(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_base_canshu, pos, dir, lenth);
}

//调用读一行数据实现

inline void Storage_gx_fun::get_gx_canshu(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_data, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_canshu(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_data, pos, dir, lenth);
}

string Storage_gx_fun::get_gx_name(int pos)
{
	read_a_row_data(file_dir_gx_name, pos, name_buffer, NAME_BUFFER_SIZE);
	string ans_name;
	buffer_to_str(ans_name);
	return ans_name;
}

inline void Storage_gx_fun::set_gx_name(int pos, string name)
{
	str_to_buffer(name);
	edit_a_row_data(file_dir_gx_name, pos, name_buffer, NAME_BUFFER_SIZE);
}

string Storage_gx_fun::get_gx_type(int pos)
{
	gx_base_canshu ls_data;
	get_gx_obj_canshu(pos,(char*)&ls_data, sizeof(ls_data));
	{
		if (ls_data.type_gx == 0)
		{
			return "成型 - 开槽";
		}
		if (ls_data.type_gx == 1)
		{
			return "螺旋槽";
		}	
		if (ls_data.type_gx == 2)
		{
			return "端齿槽 - 球头";
		}	
		if (ls_data.type_gx == 3)
		{
			return "端齿槽 - 平底";
		}	
		if (ls_data.type_gx == 4)
		{
			return  "圆角前刀面";
		}	
		if (ls_data.type_gx == 5)
		{
			return "成型 - 后刀面";
		}	
		if (ls_data.type_gx == 6)
		{
			return "锥球 - 后刀面";
		}	
		if (ls_data.type_gx == 7)
		{
			return "平底 - 端后刀面";
		}	
		if (ls_data.type_gx == 8)
		{
			return "平底 - 柱后刀面";
		}	
		if (ls_data.type_gx == 9)
		{
			return "圆角R - 后刀面";
		}	
		if (ls_data.type_gx == 10)
		{
			return "刀尖间隙";
		}
		if (ls_data.type_gx == 11)
		{
			return "成型 - 开槽 2";
		}

		return "错误类型";
	}
}


int Storage_gx_fun::get_gx_sl_id(int pos)
{
	gx_base_canshu ls_data;
	get_gx_obj_canshu(pos, (char*)&ls_data, sizeof(ls_data));

	return ls_data.shalun_id;
}

void Storage_gx_fun::set_gx_sl_id(int pos, int sl_id)
{
	gx_base_canshu ls_data;
	get_gx_obj_canshu(pos, (char*)&ls_data, sizeof(ls_data));
	ls_data.shalun_id = sl_id;

	set_gx_obj_canshu(pos, (char*)&ls_data, sizeof(ls_data));
}

void Storage_gx_fun::set_gx_sl_pos_in_JC(int pos, int sl_pos_in_JC)
{
	gx_base_canshu ls_data;
	get_gx_obj_canshu(pos, (char*)&ls_data, sizeof(ls_data));
	ls_data.sl_pos_in_JC = sl_pos_in_JC;

	set_gx_obj_canshu(pos, (char*)&ls_data, sizeof(ls_data));

}

string Storage_gx_fun::get_gx_jingeilv(int pos)
{
	CanShu_SuDu ls_sudu;
	get_gx_sudu(pos, (char*)&ls_sudu, sizeof(ls_sudu));

	string str = to_string(ls_sudu.MoXueJinGei);
	int precision = 2;
	size_t dot_pos = str.find('.');
	if (dot_pos != std::string::npos && precision >= 0) {
		str = str.substr(0, dot_pos + precision + 1);
	}

	return str;
}


inline void Storage_gx_fun::get_gx_range(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_range, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_range(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_range, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_sample(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_sample, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_sample(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_sample, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_jintuidao(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_jintuidao, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_jintuidao(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_jintuidao, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_bianhuan(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_bianhuan, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_bianhuan(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_bianhuan, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_xunhuan(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_xunhuan, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_xunhuan(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_xunhuan, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_zhenlie(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_zhenlie, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_zhenlie(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_zhenlie, pos, dir, lenth);
}

void Storage_gx_fun::get_gx_hdm_fangfa(int pos, CanShu_HDM_MoXue_FangFa& in_ff)
{
	in_ff.load(pos);
}

void Storage_gx_fun::set_gx_hdm_fangfa(int pos, CanShu_HDM_MoXue_FangFa& in_ff)
{
	in_ff.save(pos);
}

void Storage_gx_fun::get_gx_qdm_fangfa(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_fangfa, pos, dir, lenth);
	//in_ff.load(pos);
}
void Storage_gx_fun::set_gx_qdm_fangfa(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_fangfa, pos, dir, lenth);
	//in_ff.save(pos);
}

//inline void Storage_gx_fun::get_gx_fangfa(int pos, char* dir, int lenth)
//{
//	read_a_row_data(file_dir_gx_fangfa, pos, dir, lenth);
//}
//
//inline void Storage_gx_fun::set_gx_fangfa(int pos, char* dir, int lenth)
//{
//	renew_a_row_data(file_dir_gx_fangfa, pos, dir, lenth);
//}

inline void Storage_gx_fun::get_gx_sudu(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_sudu, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_sudu(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_sudu, pos, dir, lenth);
}

inline void Storage_gx_fun::get_gx_A_before(int pos, char* dir, int lenth)
{
	read_a_row_data(file_dir_gx_A_before, pos, dir, lenth);
}

inline void Storage_gx_fun::set_gx_A_before(int pos, char* dir, int lenth)
{
	edit_a_row_data(file_dir_gx_A_before, pos, dir, lenth);
}

int Storage_gx_fun::get_gx_sl_in_or_out(int pos)
{
	gx_base_canshu ls_gx_canshu;
	get_gx_obj_canshu(pos, (char*)&ls_gx_canshu, sizeof(ls_gx_canshu));

	int cur_gx_type = ls_gx_canshu.type_gx;
	if (-1 < cur_gx_type && cur_gx_type < 5)
	{
		CanShu_QDM_MoXue_FangFa fangfa_qdm;
		fangfa_qdm.load(pos);
		return fangfa_qdm.in_or_out;
	}
	if (4 < cur_gx_type && cur_gx_type < 10)
	{
		CanShu_HDM_MoXue_FangFa fangfa_hdm;
		fangfa_hdm.load(pos);
		return fangfa_hdm.in_or_out;
	}
	if (11 == cur_gx_type)
	{
		CanShu_QDM_MoXue_FangFa fangfa_qdm;
		fangfa_qdm.load(pos);
		return fangfa_qdm.in_or_out;
	}

	return -1;
}

Storage_gx_fun::Storage_gx_fun()
{
	//设置文件名
	{
			file_dir_gx_base_canshu = folder + "gx_obj.txt";
			//file_dir_gx_miller_canshu = folder + "gx_miller_canshu.txt";
			file_dir_gx_data = folder + "gx_data.txt";
			file_dir_gx_name = folder + "gx_name.txt";
			//file_dir_gx_mo_mian_canshu = folder + "gx_mo_mian.txt";
			file_dir_gx_range = folder + "gx_range.txt";
			file_dir_gx_sample = folder + "gx_sample.txt";
			file_dir_gx_jintuidao = folder + "gx_jintuidao.txt";
			file_dir_gx_bianhuan = folder + "gx_bianhuan.txt";
			file_dir_gx_xunhuan = folder + "gx_xunhuan.txt";
			file_dir_gx_zhenlie = folder + "gx_zhenlie.txt";
			file_dir_gx_fangfa = folder + "gx_fangfa.txt";
			file_dir_gx_sudu = folder + "gx_sudu.txt";
			file_dir_gx_A_before = folder + "gx_A_before.txt";
			//file_dir_gx_write = folder + "gx_save_pos.txt";

			file_dir_gx_juti_ff = folder + "gx_juti_ff.txt";

	}

#pragma region 创建文件
		//工序文件初始化

		if (!std::filesystem::exists(file_dir_gx_name))
		{
			fstream file1;
			file1.open(file_dir_gx_name, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_base_canshu))
		{
			fstream file1;
			file1.open(file_dir_gx_base_canshu, std::ios::out | std::ios::binary); //所以文件都要有数据长度，用来校验读取6.27
			int len_data = sizeof(gx_base_canshu); //+ sizeof(time_t)
			file1.write((char*)&len_data, sizeof(len_data));

			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		//if (!std::filesystem::exists(file_dir_gx_miller_canshu))
		//{
		//	//fstream file1;
		//	//file1.open(file_dir_gx_miller_canshu, std::ios::out | std::ios::binary);
		//	//int len_data = sizeof(xt_Mo_HDM_CanShu);	//磨削参数一条数据长度
		//	//file1.write((char*)&len_data, len_data);
		//	//file1.close();
		//}
		if (!std::filesystem::exists(file_dir_gx_data))
		{
			fstream file1;
			file1.open(file_dir_gx_data, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}

		//if (!std::filesystem::exists(file_dir_gx_mo_mian_canshu))
		//{
		//	fstream file1;
		//	file1.open(file_dir_gx_mo_mian_canshu, std::ios::out | std::ios::binary);
		//	int len_data = 100 * sizeof(double);
		//	file1.write((char*)&len_data, sizeof(len_data));
		//	int data_count = 0;
		//	int empty_count = 0;
		//	file1.write((char*)&data_count, sizeof(data_count));
		//	file1.write((char*)&empty_count, sizeof(empty_count));
		//	file1.close();
		//}
		if (!std::filesystem::exists(file_dir_gx_range))
		{
			fstream file1;
			file1.open(file_dir_gx_range, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_sample))
		{
			fstream file1;
			file1.open(file_dir_gx_sample, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_jintuidao))
		{
			fstream file1;
			file1.open(file_dir_gx_jintuidao, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_bianhuan))
		{
			fstream file1;
			file1.open(file_dir_gx_bianhuan, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_xunhuan))
		{
			fstream file1;
			file1.open(file_dir_gx_xunhuan, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_zhenlie))
		{
			fstream file1;
			file1.open(file_dir_gx_zhenlie, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_fangfa))
		{
			fstream file1;
			file1.open(file_dir_gx_fangfa, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_sudu))
		{
			fstream file1;
			file1.open(file_dir_gx_sudu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_gx_A_before))
		{
			fstream file1;
			file1.open(file_dir_gx_A_before, std::ios::out | std::ios::binary);
			int len_data = 1 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}

		//if (!std::filesystem::exists(file_dir_gx_write))
		//{
		//	fstream file1;
		//	file1.open(file_dir_gx_write, std::ios::out | std::ios::binary);
		//	int len_data = sizeof(int);
		//	file1.write((char*)&len_data, sizeof(len_data));
		//	int index_max = 0;
		//	file1.write((char*)&index_max, sizeof(index_max));
		//	int empty_num = 0;
		//	file1.write((char*)&empty_num, sizeof(empty_num));
		//	file1.close();
		//}

		if (!std::filesystem::exists(file_dir_gx_juti_ff))
		{
			fstream file1;
			file1.open(file_dir_gx_juti_ff, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
#pragma endregion

}

Storage_gx_fun::~Storage_gx_fun()
{
}

Storage_obj_list::Storage_obj_list()
{
	//设置文件名
	{
			//
		file_dir_xx_name = folder + "xx_name.txt";
		file_dir_xx_newdir = folder + "xx_newdir.txt";
		file_dir_xx_canshu = folder + "xx_canshu.txt";

		file_dir_xx_count = folder + "xx_count.txt";

		file_dir_hj_canshu = folder + "hj_canshu.txt";
		file_dir_hj_name = folder +  "hj_save_pos.txt";
		file_dir_lx_canshu = folder + "lx_canshu.txt";
		file_dir_lx_name  = folder + "lx_save_pos.txt";
		file_dir_fd_canshu = folder + "fd_canshu.txt";
		file_dir_fd_name  = folder + "fd_save_pos.txt";
		file_dir_qj_canshu = folder + "qj_canshu.txt";
		file_dir_qj_name  = folder + "qj_save_pos.txt";
	}

#pragma region 创建文件
		if (!std::filesystem::exists(file_dir_xx_name))
		{
			fstream file1;
			file1.open(file_dir_xx_name, std::ios::out | std::ios::binary);
			file1.seekp(0);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int max_index = 0;
			int empty_count = 0;
			file1.write((char*)&max_index, sizeof(max_index));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		else
		{
			fstream file1;
			file1.open(file_dir_xx_name, std::ios::in | std::ios::binary);
			int len = -1;
			int max_index = -1;
			int empty_count = -1;
			file1.seekg(0);
			file1.read((char*)&len, sizeof(len));
			file1.seekg(1 * sizeof(int));
			file1.read((char*)&max_index, sizeof(max_index));
			file1.read((char*)&empty_count, sizeof(empty_count));

			file1.close();
		}
		if (!std::filesystem::exists(file_dir_xx_newdir))
		{
			fstream file1;
			file1.open(file_dir_xx_newdir, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_xx_canshu))
		{
			fstream file1;
			file1.open(file_dir_xx_canshu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}

		if (!std::filesystem::exists(file_dir_xx_count))
		{
			fstream file1;
			file1.open(file_dir_xx_count, std::ios::out | std::ios::binary);
			int len_data = sizeof(int);
			file1.write((char*)&len_data, sizeof(len_data));
			file1.close();
		}

		if (!std::filesystem::exists(file_dir_hj_canshu))
		{
			fstream file1;
			file1.open(file_dir_hj_canshu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			int empty_count = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_hj_name))
		{
			fstream file1;
			file1.open(file_dir_hj_name, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_lx_canshu))
		{
			fstream file1;
			file1.open(file_dir_lx_canshu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int data_count = 0;
			int empty_count = 0;
			file1.write((char*)&data_count, sizeof(data_count));
			file1.write((char*)&empty_count, sizeof(empty_count));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_lx_name))
		{
			fstream file1;
			file1.open(file_dir_lx_name, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_fd_canshu))
		{
			fstream file1;
			file1.open(file_dir_fd_canshu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_fd_name))
		{
			fstream file1;
			file1.open(file_dir_fd_name, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_qj_canshu))
		{
			fstream file1;
			file1.open(file_dir_qj_canshu, std::ios::out | std::ios::binary);
			int len_data = 100 * sizeof(double);
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
		if (!std::filesystem::exists(file_dir_qj_name))
		{
			fstream file1;
			file1.open(file_dir_qj_name, std::ios::out | std::ios::binary);
			int len_data = NAME_BUFFER_SIZE;
			file1.write((char*)&len_data, sizeof(len_data));
			int index_max = 0;
			file1.write((char*)&index_max, sizeof(index_max));
			int empty_num = 0;
			file1.write((char*)&empty_num, sizeof(empty_num));
			file1.close();
		}
#pragma endregion

}

Storage_obj_list::~Storage_obj_list()
{
}

////往指定file文件，写入指定长度地址的内容
//
//inline int Storage_obj_list_fun::add_a_row_data(string file, const char* dir, int lenth)
//{
//	//1、先读管理写的文件2-4，找到可以存放对象的位置
//	fstream file1;
//
//	if (file_dir_xx_name == file)
//	{
//		file1.open(file_dir_xx_write, std::ios::in | std::ios::out | std::ios::binary);
//	}
//
//	if (!file1.is_open())
//	{
//		throw -1;
//	}
//	file1.seekg(0);
//	int len_data = -1;
//	file1.read((char*)&len_data, sizeof(len_data));
//	int count_data = -1;
//	file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
//	int empty_count = -1;
//	file1.read((char*)&empty_count, sizeof(empty_count));
//
//	int tool_save_pos = -1;
//	if (empty_count > 0)
//	{
//		file1.seekg((2 + empty_count) * len_data); //起始定位
//		file1.read((char*)&tool_save_pos, sizeof(tool_save_pos));
//		//不删除内容下次写入覆盖，依据空行数量判断位置有效性
//		empty_count--;
//	}
//	else
//	{
//		tool_save_pos = count_data; //后用最大位置
//		count_data++;
//	}
//
//	//2、加对象时更新最大存放位置
//	//25.6.25 当前新建tool + gx，是通过name文件开始，加判断 file=8 
//	//if (in_file == 4 || in_file == 0 || in_file == 21 
//	//	|| in_file == 8 || in_file == 9)
//	{
//		file1.seekp(1 * len_data); //write定位
//		file1.write((char*)&count_data, sizeof(count_data));
//		file1.seekp(2 * len_data); //write定位
//		file1.write((char*)&empty_count, sizeof(empty_count));
//	}
//
//	file1.close();
//
//	//3、根据文件标志在对应数据文件中写入数据
//	fstream file2;
//	file2.open(file, std::ios::in | std::ios::out | std::ios::binary);
//
//	file2.seekg(0);
//	int len_data2 = -1;
//	file2.read((char*)&len_data2, sizeof(len_data2));
//	file2.seekp(tool_save_pos * len_data2);
//	file2.write(dir, lenth);
//
//	file2.close();
//
//	return tool_save_pos;
//}
//
//inline int Storage_obj_list_fun::add_a_xx_by_dxf(const string& sourcePath, string& xx_name)
//{
//	//写name文件
//	str_to_buffer(xx_name);//字符串转数组
//	int ans_pos = add_a_row_data(file_dir_xx_name, name_buffer, NAME_BUFFER_SIZE);
//
//	//拷贝DXF文件到统一的目录，并统一编号，按照tool_1_xx-num_.dxf，规则命名7.2
//	string file_name = "xx_num_";
//	int xx_count = get_xingxian_count();
//	file_name = file_name + to_string(xx_count);
//	renameAndCopyFile(sourcePath, file_name, folder_dxf);
//
//	//记录DXF文件路径
//	string newdir = folder_dxf + file_name + ".dxf";
//	str_to_buffer(newdir);
//	edit_a_row_data(file_dir_xx_newdir, ans_pos, name_buffer, NAME_BUFFER_SIZE);
//
//	//增加型线计数
//	add_xingxian_count(1);
//
//	return ans_pos;
//}

int Storage_obj_list::add_a_xx_(string name, string file_dir, CanShu_XingXian& canshu_xx)
{
	//步骤1 增加一条型线
	str_to_buffer(name);//字符串转数组 
	int ans_pos = add_a_row_data(file_dir_xx_name, name_buffer, NAME_BUFFER_SIZE);
	//步骤2 存储对应 dxf路径
	if (file_dir == "")
	{
		string newdir = "";
		str_to_buffer(newdir);
		edit_a_row_data(file_dir_xx_newdir, ans_pos, name_buffer, NAME_BUFFER_SIZE);
	}
	else
	{
		string newdir = "";
		string file_name = "";
		string folder_dxf = "dxf_copy\\";
		{
			//拷贝DXF文件到统一的目录，并统一编号，按照tool_1_xx-num_.dxf，规则命名7.2
			file_name = "xx_num_";
			int xx_count = get_xingxian_count();
			file_name = file_name + to_string(xx_count);
			renameAndCopyFile(file_dir, file_name, folder_dxf);

			//记录DXF文件路径
			newdir = folder_dxf + file_name + ".dxf";
		}
		//记录DXF文件路径
		newdir = folder_dxf + file_name + ".dxf";
		str_to_buffer(newdir);
		edit_a_row_data(file_dir_xx_newdir, ans_pos, name_buffer, NAME_BUFFER_SIZE);
	}
	//步骤3 存储对应 基本参数
	canshu_xx.sel_dxf_pos = ans_pos;

	edit_a_row_data(file_dir_xx_canshu, ans_pos, (char*)&canshu_xx, sizeof(canshu_xx));

	//步骤4 更新型线总数量
	add_xingxian_count(1);
	return ans_pos;
}

//有问题，添加或者改变路径需要注意文件是否更新
int Storage_obj_list::edit_a_xx_(int xx_pos, string name ,string file_dir, CanShu_XingXian in_can)
{
	//步骤1 改参数
	in_can.save(xx_pos);

	//步骤2 改名字
	edit_a_row_data(file_dir_xx_name, xx_pos, (char*)&name, sizeof(name));

	//步骤3 改路径
	string newdir = file_dir;
	str_to_buffer(newdir);
	edit_a_row_data(file_dir_xx_newdir, xx_pos, name_buffer, NAME_BUFFER_SIZE);
	return 1;
}

int Storage_obj_list::edit_a_hj_(int xx_pos, CanShu_HouJiao in_can)
{
	//步骤1 改参数
	edit_a_row_data(file_dir_hj_canshu, xx_pos, (char*)&in_can, sizeof(in_can));
	return 1;
}

int Storage_obj_list::edit_a_lx_(int xx_pos,CanShu_LuoXuan in_can)
{
	//步骤1 改参数
	edit_a_row_data(file_dir_lx_canshu, xx_pos, (char*)&in_can, sizeof(in_can));

	return 1;
}

int Storage_obj_list::edit_a_fd_(int xx_pos, CanShu_FenDu in_can)
{
	//步骤1 改参数
	edit_a_row_data(file_dir_fd_canshu, xx_pos, (char*)&in_can, sizeof(in_can));

	return 1;
}

//void Storage_obj_list_fun::add_a_xx_canshu_to_file(int pos, char* dir, int lenth)
//{
//	edit_a_row_data(file_dir_xx_canshu, pos, dir, lenth);
//}

//以name文件为主键，删除只需要删除主键
inline bool Storage_obj_list::del_a_xx_(int in_pos)
{
	//步骤1
	delete_a_row_data(file_dir_xx_name, in_pos);
	return true;
}

bool Storage_obj_list::del_a_hj_(int pos)
{
	//步骤1
	delete_a_row_data(file_dir_hj_name, pos);
	return true;
}

bool Storage_obj_list::del_a_fd_(int pos)
{
	//步骤1
	delete_a_row_data(file_dir_fd_name, pos);
	return true;
}

bool Storage_obj_list::del_a_lx_(int pos)
{
	//步骤1
	delete_a_row_data(file_dir_lx_name, pos);
	return true;
}

inline string Storage_obj_list::get_xx_name(int pos)
{
	read_a_row_data(file_dir_xx_name, pos, name_buffer, NAME_BUFFER_SIZE);
	string ans_name;
	buffer_to_str(ans_name);
	return ans_name;
}

inline void Storage_obj_list::set_xx_name(int pos, string name)
{
	str_to_buffer(name);
	edit_a_row_data(file_dir_xx_name, pos, name_buffer, NAME_BUFFER_SIZE);
}

inline string Storage_obj_list::get_xx_newdir(int pos)
{
	read_a_row_data(file_dir_xx_newdir, pos, name_buffer, NAME_BUFFER_SIZE);
	string ans_name;
	buffer_to_str(ans_name);
	return ans_name;
}

//int Storage_obj_list_fun::add_a_hj( char* dir, int lenth)
//{
//	int ans_pos = find_write_pos(file_dir_hj_write);
//	renew_a_row_data(file_dir_hj_canshu, ans_pos, dir, lenth);
//	return ans_pos;
//}

void Storage_obj_list::get_dxf_xx_data(int pos, double in_acc, mat& ans_data)
{
	string tag_dir = get_xx_newdir(pos);
	line_manager ls_tool(tag_dir);

	vector<vec> dxf_points;
	ls_tool.get_discrete_point(in_acc, dxf_points); 

	
	ans_vv_to_mat(dxf_points, ans_data);
}

inline void Storage_obj_list::ans_vv_to_mat(vector<vec>& points, mat& Data_Of_Points)
{
	Data_Of_Points.clear();
	int count_p = points.size();
	Data_Of_Points.reset();
	Data_Of_Points = zeros(6, count_p);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_data = points[i];
		vec ls_t = { ls_data(0), ls_data(1), ls_data(2) };
		vec ls_p = { ls_data(3),ls_data(4),ls_data(5) };
		//dxf的x 转为Z为长度方向
		//ls_t = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_t;
		//ls_p = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_p;

		double lenth = 0.0001; //???? 6.14
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ls_t(0), ls_t(1), ls_t(2)};

		Data_Of_Points.col(i) = ans_p;
	}
}

int Storage_obj_list::add_a_hj(CanShu_HouJiao& in_can)
{
	//1 生成一个名字
	int name_id = get_index_count(file_dir_hj_name);
	string name = to_string(name_id);

	//2 增加一条
	int pos = add_a_row_data(file_dir_hj_name, (char*)&name, sizeof(name));

	//3 记录参数
	in_can.save(pos);

	//4 返回
	return pos;
}

int Storage_obj_list::add_a_lx(CanShu_LuoXuan& in_can)
{
	//1 生成一个名字
	int name_id = get_index_count(file_dir_lx_name);
	string name = to_string(name_id);

	//2 增加一条
	int pos = add_a_row_data(file_dir_lx_name, (char*)&name, sizeof(name));

	//3 记录参数
	in_can.save(pos);

	//4 返回
	return pos;
}

int Storage_obj_list::add_a_fd(CanShu_FenDu& in_can)
{
	//1 生成一个名字
	int name_id = get_index_count(file_dir_fd_name);
	string name = to_string(name_id);

	//2 增加一条后角
	int pos = add_a_row_data(file_dir_fd_name, (char*)&name, sizeof(name));

	//3 记录后角参数
	in_can.save(pos);

	//4 返回
	return pos;
}

void Storage_obj_list::get_a_xx_canshu(int pos, CanShu_XingXian& ans_can)
{
	read_a_row_data(file_dir_xx_canshu, pos, (char*)&ans_can, sizeof(ans_can));
}

void Storage_obj_list::get_a_hj_canshu(int pos, CanShu_HouJiao& ans_can)
{
	ans_can.load(pos);
}

void Storage_obj_list::get_a_lx_canshu(int pos, CanShu_LuoXuan& ans_can)
{
	ans_can.load(pos);
}

void Storage_obj_list::get_a_fd_canshu(int pos, CanShu_FenDu& ans_can)
{
	ans_can.load(pos);
}

void Storage_obj_list::get_a_qj_canshu(int pos, CanShu_QianJiao& ans_can)
{
	ans_can.load(pos);
}

Cal_XingXian* Storage_obj_list::new_a_xingxian_from_storage(int pos)
{
	CanShu_XingXian ls_read_data;
	get_a_xx_canshu(pos, ls_read_data);
	Cal_XingXian* ls_cal = new Cal_XingXian;
	ls_cal->set_base_data(ls_read_data);
	return ls_cal;
}

Cal_HouJiao* Storage_obj_list::new_a_houjiao_from_storage(int pos)
{
	CanShu_HouJiao ls_read_data;
	get_a_hj_canshu(pos, ls_read_data);

	Cal_HouJiao* cal_hj = new Cal_HouJiao;
	cal_hj->set_base_data(ls_read_data);

	return cal_hj;
}

Cal_LouXuan* Storage_obj_list::new_a_luoxuan_from_storage(int pos)
{
	CanShu_LuoXuan ls_read_data;
	get_a_lx_canshu(pos, ls_read_data);

	Cal_LouXuan* cal_lx = new  Cal_LouXuan;
	cal_lx->set_base_data(ls_read_data);
	return cal_lx;
}

Cal_FenDu* Storage_obj_list::new_a_fendu_from_storage(int pos)
{
	CanShu_FenDu ls_read_data;
	get_a_fd_canshu(pos, ls_read_data);

	Cal_FenDu* cal_fd = new  Cal_FenDu;
	cal_fd->set_base_data(ls_read_data);

	return cal_fd;
}

//没用
//int Storage_obj_list::find_write_pos(string file)
//{
//	//1、先读管理写的文件2-4，找到可以存放对象的位置
//	fstream file1;
//
//	file1.open(file, std::ios::in | std::ios::out | std::ios::binary);
//
//	if (!file1.is_open())
//	{
//		throw - 1;
//	}
//	file1.seekg(0);
//	int len_data = -1;
//	file1.read((char*)&len_data, sizeof(len_data));
//	int count_data = -1;
//	file1.read((char*)&count_data, sizeof(count_data));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
//	int empty_count = -1;
//	file1.read((char*)&empty_count, sizeof(empty_count));
//
//	int tool_save_pos = -1;
//	if (empty_count > 0)
//	{
//		file1.seekg((2 + empty_count) * len_data); //起始定位
//		file1.read((char*)&tool_save_pos, sizeof(tool_save_pos));
//		//不删除内容下次写入覆盖，依据空行数量判断位置有效性
//		empty_count--;
//	}
//	else
//	{
//		tool_save_pos = count_data; //后用最大位置
//		count_data++;
//	}
//
//	//2、加对象时更新最大存放位置
//	//25.6.25 当前新建tool + gx，是通过name文件开始，加判断 file=8 
//	//if (in_file == 4 || in_file == 0 || in_file == 21 
//	//	|| in_file == 8 || in_file == 9)
//	{
//		file1.seekp(1 * len_data); //write定位
//		file1.write((char*)&count_data, sizeof(count_data));
//		file1.seekp(2 * len_data); //write定位
//		file1.write((char*)&empty_count, sizeof(empty_count));
//	}
//
//	file1.close();
//
//	return tool_save_pos;
//}

//更新型线计数--真为加，假为减
//check 与刀同理
inline bool Storage_obj_list::add_xingxian_count(bool add)
{
	fstream file2;
	file2.open(file_dir_xx_count, std::ios::in | std::ios::out | std::ios::binary);
	if (!file2.is_open())
	{
		throw -1;
	}
	//读取当前存储数据
	file2.seekg(0, ios::beg);
	int len_data2 = -1;
	file2.read((char*)(&len_data2), sizeof(len_data2));
	int ls_count = -1;
	file2.read((char*)(&ls_count), sizeof(ls_count));
	if (add)
	{
		ls_count++;
	}
	else
	{
		ls_count--;
	}


	file2.clear();
	file2.seekp(0, ios::beg);
	file2.write((char*)(&len_data2), sizeof(len_data2));
	file2.write((char*)(&ls_count), sizeof(ls_count));

	file2.close();
	return true;
}

inline int Storage_obj_list::get_xingxian_count()
{
	fstream file2;
	file2.open(file_dir_xx_count, std::ios::in | std::ios::out | std::ios::binary);
	if (!file2.is_open())
	{
		throw - 1;
	}

	//读出当前数量，根据输入修改值后写入
	file2.seekg(0, ios::beg);
	int len_data2 = -1;
	file2.read((char*)(&len_data2), sizeof(len_data2));
	int ls_count = 0;
	file2.read((char*)(&ls_count), sizeof(ls_count));

	file2.close();

	return ls_count;
}

//重命名dxf文件并拷贝到指定文件夹
//check
inline void Storage_obj_list::renameAndCopyFile(const string& sourcePath, const string& file_name, const string& targetDirectory)
{
	namespace fs = std::filesystem;
	try
	{
		// 检查源文件是否存在
		if (!fs::exists(sourcePath)) {
			std::cerr << "源文件不存在: " << sourcePath << std::endl;
			return;
		}

		// 检查目标目录是否存在，不存在则创建
		if (!fs::exists(targetDirectory)) {
			fs::create_directories(targetDirectory);
		}

		// 获取源文件扩展名
		std::string extension = fs::path(sourcePath).extension().string();

		// 构建目标路径
		fs::path targetPath = fs::path(targetDirectory) / (file_name + extension);

		// 拷贝文件到目标目录并重命名
		fs::copy_file(sourcePath, targetPath, fs::copy_options::overwrite_existing);

		std::cout << "文件已成功重命名并拷贝到: " << targetPath << std::endl;
	}
	catch (const fs::filesystem_error& e)
	{
		std::cerr << "文件操作错误: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "发生错误: " << e.what() << std::endl;
	}
}

//	//将型线名称文件读成显示列表3.5-不显示-1的数据条3.6
//	void read_xx_catalog_for_display_list(vector<int>& ans_type, vector<string>& ans_name)
//	{
//		fstream file2;
//		{
//			file2.open(file_dir_xx_name, std::ios::in | std::ios::binary);
//			if (!file2.is_open())
//			{
//				return;
//			}
//			//数据长度
//			file2.seekg(0, ios::beg);
//			int len_data2 = -1;
//			file2.read((char*)(&len_data2), sizeof(len_data2));
//			//读到文件末尾
//			while (1)
//			{
//				if (file2.eof())
//				{
//					break;
//				}
//
//				xingxian_catalog ls_data;
//
//				file2.read((char*)(&ls_data), sizeof(xingxian_catalog));
//
//				if (ls_data.type > -1)
//				{
//					ans_type.push_back(ls_data.type);
//					string file_name;
//					file_name.resize(NAME_BUFFER_SIZE);
//					for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//					{
//						file_name[i] = ls_data.name_buffer[i];
//					}
//
//					ans_name.push_back(file_name);
//				}
//			}
//
//			file2.close();
//			return;
//		}
//	}
//	//p_manager加载一条型线,将数据写入两个文件
//	//void load_a_dxf(string in_file_name,double in_dis, string in_new_name);
//
//	void load_xx_data_by_name(string in_name)
//	{
//
//	}
//
//	//根据目录索引对应位置的型线数据
//	void load_a_tool_xx_name_and_data(vector<int>& in_v_pos, vector<string>& ans_v_name)
//	{
//		ans_v_name.clear();
//		//ans_v_data.clear();
//		for (int i = 0; i < in_v_pos.size(); i++)
//		{
//			string ls_name;
//			mat ls_data;
//			get_tag_pos_dxf_name_and_data(in_v_pos[i], ls_name, ls_data);
//			ans_v_name.push_back(ls_name);
//			//ans_v_data.push_back(ls_data);
//		}
//	}
//
//	//成型刀添加一条型线，将新name写入目录文件, 返回存储的编号
//	int tool_add_a_xx_from_win(string in_dxf_name, string in_new_name)
//	{
//
//
//		//读出点数据
//		//line_manager read_dxf_tool(in_dxf_name);
//		//vector<vec> p_of_dxf;
//		//read_dxf_tool.get_integral_point(in_dis, in_ang, p_of_dxf);
//		double in_dis = 0.001; //默认两点间距离 4.3
//		//read_dxf_tool.get_discrete_point(in_dis, p_of_dxf);
//
//		//xx_data.init_data_by_dxf_file(in_new_name, in_dis);4.14
//		//int count_p = p_of_dxf.size();
//
//		//写型线文件，先写点数据，后写目录
//		//fstream file1;
//		//file1.open(file_dir_xingxian_data, std::ios::out | std::ios::binary);
//
//		//file1.seekp(0, ios::end); //write定位
//		//int cur_data_start_index = file1.tellp();
//		//for (size_t i = 0; i < count_p; i++)
//		//{
//		//	vec ls_data = p_of_dxf[i];
//		//	double p_buffer[6] = { ls_data(0), ls_data(1), ls_data(2),
//		//		ls_data(3), ls_data(4), ls_data(5) };
//		//	//file1.write((char*)&p_buffer, sizeof(p_buffer));
//		//	//型线点数据
//		//	p_data.insert_cols(p_data.n_cols, ls_data);
//		//}
//		//file1.close();
//
//
//		xingxian_catalog ls_catalog;
//		ls_catalog.type = 0;
//		for (int i = 0; i < in_new_name.size(); i++)
//		{
//			ls_catalog.name_buffer[i] = in_new_name[i];
//		}
//
//		int count_xx_num = get_xingxian_count();
//
//		int len = sizeof(ls_catalog);
//		fstream file2;
//		file2.open(file_dir_xx_name, std::ios::in | std::ios::out | std::ios::binary);
//		file2.seekp(count_xx_num * sizeof(ls_catalog), ios::beg); //write定位
//
//		file2.write((char*)&ls_catalog, sizeof(ls_catalog));
//
//		file2.close();
//		return 0;
//	}
//
//
//	//根据文件名修改对应行的标志位为删除（-1）3.6
//	bool renew_a_xx_name_of_type_by_delete(string in_file_name)
//	{
//		fstream file2;
//		{
//			file2.open(file_dir_xx_name, std::ios::in | std::ios::binary);
//			if (!file2.is_open())
//			{
//				throw - 1;
//			}
//			//数据长度
//			file2.seekg(0, ios::beg);
//			int len_data2 = -1;
//			file2.read((char*)(&len_data2), sizeof(len_data2));
//			int row_index = 1; //改变标志位写入的索引
//
//			//读到文件末尾
//			while (1)
//			{
//				if (file2.eof())
//				{
//					break;
//				}
//
//				xingxian_name_data ls_data;
//				file2.read((char*)(&ls_data), sizeof(xingxian_name_data));
//
//				string file_name;
//				file_name.resize(NAME_BUFFER_SIZE);
//				for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//				{
//					file_name[i] = ls_data.name_buffer[i];
//				}
//
//				if (file_name == in_file_name)
//				{
//					if (ls_data.type == 0)
//					{
//						file2.seekp(row_index * len_data2);
//						ls_data.type = -1;
//						file2.write((char*)&ls_data, sizeof(ls_data));
//						break;
//					}
//					else
//					{
//						return false;
//					}
//				}
//				row_index++;
//			}
//
//			file2.close();
//		}
//		return true;
//	}
//
//	//获取指定位置的dxf文件名
//	string get_tag_pos_dxf_file_name(int in_pos)
//	{
//		//xingxian_name_data ans_data;
//		//fstream file2;
//		//{
//		//	file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::binary);
//		//	if (!file2.is_open())
//		//	{
//		//		return "null";
//		//	}
//		//	//数据长度
//		//	file2.seekg(0, ios::beg);
//		//	int len_data2 = -1;
//		//	file2.read((char*)(&len_data2), sizeof(len_data2));
//
//		//	file2.seekg(in_pos * len_data2, ios::beg);
//		//	file2.read((char*)&ans_data, sizeof(xingxian_name_data));
//
//		//	file2.close();
//		//}
//		//string file_name;
//		//file_name.resize(NAME_BUFFER_SIZE);
//		//for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//		//{
//		//	file_name[i] = ans_data.name_buffer[i];
//		//}
//		//return file_name;
//		return "";
//	}
//	//获取指定位置的dxf文件名及点数据
//	void get_tag_pos_dxf_name_and_data(int in_pos, string& ans_name, mat& ans_data)
//	{
//		double in_dis = 0.001; //默认两点间距离 4.3
//		//read_dxf_tool.get_discrete_point(in_dis, p_of_dxf);
//
//		xingxian_catalog ls_catalog;
//		ls_catalog.type = 0;
//		int len = sizeof(ls_catalog);
//
//		fstream file2;
//		file2.open(file_dir_xx_name, std::ios::in | std::ios::out | std::ios::binary);
//		file2.seekg(in_pos * sizeof(ls_catalog), ios::beg);
//
//		file2.read((char*)&ls_catalog, sizeof(ls_catalog));
//
//		file2.close();
//
//		string file_name;
//		//file_name.resize(NAME_BUFFER_SIZE);
//		for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//		{
//			//C 风格字符串，找到第一个 \0 终止符的位置，仅拼接有效内容 -4.14
//			if (ls_catalog.name_buffer[i] != '\0')
//			{
//				file_name = file_name + ls_catalog.name_buffer[i];
//			}
//			//else
//			//{
//			//	break;
//			//}
//		}
//
//
//		line_manager ls_read_tool(file_name);
//		vector<vec> ans_ponts;
//
//		ls_read_tool.get_discrete_point(in_dis, ans_ponts);
//
//		ans_vv_to_mat(ans_ponts, ans_data);
//
//		ans_name = file_name;
//	}
//private:
//	void ans_vv_to_mat(vector<vec>& points, mat& Data_Of_Points)
//	{
//		Data_Of_Points.clear();
//		int count_p = points.size();
//		for (int i = 0; i < count_p; i++)
//		{
//			vec ls_data = points[i];
//			vec ls_t = { ls_data(0), ls_data(1), ls_data(2) };
//			vec ls_p = { ls_data(3),ls_data(4),ls_data(5) };
//			//dxf的x 转为Z为长度方向
//			ls_t = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_t;
//			ls_p = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_p;
//
//			double lenth = 0.0001; //???? 6.14
//			vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ls_t(0), ls_t(1), ls_t(2), i * lenth };
//
//			Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//		}
//	}

//往指定file文件，写入指定长度地址的内容  增加操作调用，只能是名称文件

double Storage_manager::get_tool_w_c2g(int pos)
{
	double ans = 0.0;
	Storage_base::read_a_row_data(file_dir_w_c2g, pos, (char*)&ans, sizeof(ans));
	return ans;
}

void Storage_manager::set_tool_w_c2g(int pos, double w_c2g)
{
	Storage_base::edit_a_row_data(file_dir_w_c2g, pos, (char*)&w_c2g, sizeof(w_c2g));
}

void Storage_manager::get_mo_gj_trans(int pos, char* dir, int lenth)
{
	Storage_base::read_a_row_data(file_dir_mo_gj_trans, pos, dir, lenth);
}

void Storage_manager::set_mo_gj_trans(int pos, char* dir, int lenth)
{
	Storage_base::edit_a_row_data(file_dir_mo_gj_trans, pos, dir, lenth);
}

//有head_size下标索引从0开始 ,机床砂轮组的全修改 25.11.14
void Storage_manager::get_jc_sl_lib(vector<int>& v_jc_sl)
{
	v_jc_sl.clear();
	for (int i = 0; i < 6; i++)
	{
		int sl_id = -1;
		//Storage_base::read_a_row_data(file_dir_sl_lib, i + 1, (char*)&sl_id, sizeof(sl_id));
		Storage_base::read_a_row_data(file_dir_sl_lib, i, (char*)&sl_id, sizeof(sl_id));
		v_jc_sl.push_back(sl_id);
	}
	
}

//void Storage_manager::set_jc_sl_lib(int pos, char* dir, int lenth)
//{
//	Storage_base::renew_a_row_data(file_dir_sl_lib, pos, dir, lenth);
//}

int Storage_manager::get_sl_pos_in_JC(int sl_id)
{
	vector<int> v_jc_sl;
	get_jc_sl_lib(v_jc_sl);

	int ans_pos = -1;
	for (int i = 0; i < 6; i++)
	{
		if (v_jc_sl[i] == sl_id)
		{
			ans_pos = i;
		}
	}

	return ans_pos;
}

void Storage_manager::get_2n_mat(int pos, mat& mat)
{
	std::ifstream ifs(save_lib::storage_lib.file_dir_mat_2n, std::ios::binary);
	ifs.seekg(pos);
	cereal::BinaryInputArchive archive(ifs);

	archive(mat);
}

int Storage_manager::set_2n_mat(mat& in_mat)
{
	//每个 BinaryOutputArchive 实例会写入自己的头部信息 > 不用考虑数据长度 25.6.16
//追加方式、
	std::ofstream ofs(save_lib::storage_lib.file_dir_mat_2n, std::ios::binary | std::ios::app);
	cereal::BinaryOutputArchive archive(ofs);
	ofs.seekp(0, ios::end);
	int ans_pos = ofs.tellp();

	archive(in_mat);

	ofs.close();

	return ans_pos;
}

void Storage_manager::get_3n_mat(int pos, mat& in_mat)
{
	std::ifstream ifs(save_lib::storage_lib.file_dir_mat_3n, std::ios::binary);
	ifs.seekg(pos);
	cereal::BinaryInputArchive archive(ifs);

	archive(in_mat);
}

int Storage_manager::set_3n_mat(mat& in_mat)
{
	std::ofstream ofs(save_lib::storage_lib.file_dir_mat_3n, std::ios::binary | std::ios::app);
	cereal::BinaryOutputArchive archive(ofs);
	ofs.seekp(0, ios::end);
	int ans_pos = ofs.tellp();

	archive(in_mat);

	ofs.close();

	return ans_pos;
}

void Storage_manager::get_4n_mat(int pos, mat& in_mat)
{
	std::ifstream ifs(save_lib::storage_lib.file_dir_mat_4n, std::ios::binary);
	ifs.seekg(pos);
	cereal::BinaryInputArchive archive(ifs);

	archive(in_mat);
}

int Storage_manager::set_4n_mat(mat& in_mat)
{
	std::ofstream ofs(save_lib::storage_lib.file_dir_mat_4n, std::ios::binary | std::ios::app);
	cereal::BinaryOutputArchive archive(ofs);
	ofs.seekp(0, ios::end);
	int ans_pos = ofs.tellp();

	archive(in_mat);

	ofs.close();

	return ans_pos;
}

mo_hdm_ff_canshu_data::mo_hdm_ff_canshu_data()
{
	pos_qx_wy = -1;
	
	in_or_out = -1;
	
	type = -1;
}

mo_hdm_ff_canshu_data::~mo_hdm_ff_canshu_data()
{
}

lx_canshu_data::lx_canshu_data()
{
	 save_obj_hjbc = -1;
	 save_B_daocheng=-1;
	 save_B_luoxuan=-1;
	
	 xingxian_pos=-1;
	 fendu_pos=-1;
	
	 type_cao = -1; //0-直槽、1-斜槽、2-螺旋槽
	
	type_zhi =-1; //0-前角、1-偏心距
	zhi_ang_qian = 0.0;
	zhi_pianxin =0.0;
	ang_xie = 0.0; //斜角=倾角
	R_zhi_or_xie = 0.0;

	type_xie =-1; //0-前角、1-偏心距

	xie_ang_qian =0.0;

	xie_pianxin=0.0;

	type_luo=-1; //0-等导程、1-等螺旋角、2-变导程、3-变螺旋角

	D_daocheng=0.0;	//导程
	D_ang_luo=0.0;	//螺旋角

	ang_r = 0.0;
}

lx_canshu_data::~lx_canshu_data()
{
}

qj_canshu_data::qj_canshu_data()
{
	
	save_b_qianjiao_n =-1;
	save_b_qianjiao_r=-1;
	
	luoxuan_pos=-1;
	
	type=-1; //0-法向，1-径向
}

qj_canshu_data::~qj_canshu_data()
{
}

hj_canshu_data::hj_canshu_data()
{
	save_B_ang_n_1	 = -1;
	save_B_ang_n_2	 = -1;
	save_B_ang_n_3	 = -1;
	save_B_ang_a_r_1 = -1;
	save_B_ang_a_r_2 = -1;
	save_B_ang_a_r_3 = -1;

	xingxian_pos = -1;

	type = -1; //0-法向，1-径向

	D_ang_n_1 =0.0;
	D_wid_n_1=0.0;
	is_bian_n_1=0;
	D_ang_n_2=0.0;
	D_wid_n_2=0.0;
	is_bian_n_2=0;
	D_ang_n_3=0.0;
	D_wid_n_3=0.0;
	is_bian_n_3=0;

	D_ang_a_1 = 0.0;
	D_ang_r_1 = 0.0;
	D_wid_a_1 = 0.0;
	is_bian_a_1 = 0;
	D_ang_a_2 = 0.0;
	D_ang_r_2 = 0.0;
	D_wid_a_2 = 0.0;
	is_bian_a_2 = 0;
	D_ang_a_3 = 0.0;
	D_ang_r_3 = 0.0;
	D_wid_a_3 = 0.0;
	is_bian_a_3 = 0;
}

hj_canshu_data::~hj_canshu_data()
{
	save_B_ang_n_1=-1;
	save_B_ang_n_2=-1;
	save_B_ang_n_3=-1;
	save_B_ang_a_r_1=-1;
	save_B_ang_a_r_2=-1;
	save_B_ang_a_r_3=-1;

	xingxian_pos=-1;

	type=-1; //0-法向，1-径向

}


fangfa_xx_wy_data::fangfa_xx_wy_data()
{
	pos_xx_bian=-1;
	pos_wy_bian=-1;

	xx=-1;
	wy=-1;
	xx_isbian=-1;
	wy_isbian=-1;
}

fangfa_xx_wy_data::~fangfa_xx_wy_data()
{
}
