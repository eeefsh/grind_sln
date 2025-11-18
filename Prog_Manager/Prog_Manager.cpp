#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Prog_Manager.h"
#include"Tool_Obj.h"


Prog_manager::Prog_manager()
{
	::gladLoadGL();
	//::gladLoadGL();
	sl_manager.Init_Dir(
		storage_lib.file_dir_sl_sy,
		storage_lib.file_dir_sl,
		storage_lib.file_dir_slz_sy,
		storage_lib.file_dir_slz
	);

	
	cur_tool_ptr = nullptr;
	FZ_3D = nullptr;
	FZ_2D = nullptr;

	init_gx_type_name();
}

Prog_manager::~Prog_manager()
{
	//delete ptr_storage;

	if (cur_tool_ptr != nullptr)
	{
		delete cur_tool_ptr;
	}
}

string Prog_manager::get_cur_tool_name()
{
	int pos = cur_tool_ptr->pos;
	string ans_name;

	const int NAME_BUFFER_SIZE = 100; // 与文件存储的定长一致
	char name_buffer[NAME_BUFFER_SIZE] = { 0 };
	if (storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_tool_name, pos,
		name_buffer, NAME_BUFFER_SIZE))
	{
		ans_name.assign(name_buffer);
		// 如果存储时有填充空字符，会自动截断
	}
	else
	{
		ans_name = "Unknown";
	}
	return ans_name;
}

string Prog_manager::get_cur_tool_type()
{
	if (cur_tool_ptr->type_tool == 0)
	{
		return "锥球：";
	}
	if (cur_tool_ptr->type_tool == 1)
	{
		return "平底：";
	}
	if (cur_tool_ptr->type_tool == 2)
	{
		return "圆角：";
	}
	if (cur_tool_ptr->type_tool == 3)
	{
		return "成型：";
	}

	return "null：";
}
inline void Prog_manager::add_a_tool(int pos, int dao_type, string in_name)
{
	new_a_tool(dao_type);
	//int ans_pos = obj_tool_lib.add_a_row_data(dao_type, in_name);
	
	cur_tool_ptr->set_pos(pos);//6.24增加设置刀具存储位置的函数，将其关联的所有存储都赋值
	//cur_tool_ptr->save();
}

bool Prog_manager::open_a_tool(int n_order)
{
	//1、根据选择刀具的位置(不显示存储位置)，索引到存储的位置
	int ls_pos = obj_tool_lib.get_tool_pos(n_order);

	//2、读刀具类型
	int ls_type = -1;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_tool_type, ls_pos, (char*)&ls_type, sizeof(ls_type));
	
	//3、建一个对应类型刀具，并关联存储位
	if (cur_tool_ptr != nullptr)
	{
		//清空之前打开的数据所new出的到
		delete cur_tool_ptr;
	}
	new_a_tool(ls_type);
	cur_tool_ptr->set_pos(ls_pos);

	//4、从外存恢复数据
	cur_tool_ptr->load();

	return true;
}

bool Prog_manager::new_a_tool(int dao_type)
{
	//没有析构？？？
	//1、根据铣刀类型新建一个刀具对象
	switch (dao_type)
	{
	case 0:
		cur_tool_ptr = new Tool_ZQ();
		break;
	case 1:
		cur_tool_ptr = new Tool_PD();
		break;
	case 2:
		cur_tool_ptr = new Tool_R();
		break;
	case 3:
		cur_tool_ptr = new Tool_CX();
		break;
	default:
		break;
	}

	return true;
}

inline vector<int> Prog_manager::find_sl_is_not_on_lib()
{
	//获取已经安装的砂轮组id
	vector<int> slz_id_laod;
	for (int j = 0; j < 6; j++)
	{
		slz_id_laod.push_back(obj_JC_sl_lib.get_slz_id(j));
	}

	vector<int> v_gx_sl_zu_by_no;
	for (int i = 0; i < cur_tool_ptr->v_select_cal_gx_index.size(); i++)
	{
		int sel_row = cur_tool_ptr->v_select_cal_gx_index[i];
		int cur_sl_num = cur_tool_ptr->ptr_list_gx->get_obj(sel_row)->get_sl_id();
		int slz_id = sl_manager.get_group_key_by_wheel_key(cur_sl_num);


		//砂轮库上每个位置检查
		bool is_has = 0;
		for (int j = 0; j < 6; j++)
		{

			if (slz_id == slz_id_laod[j])
			{
				is_has = 1;
				break;
			}
		}
		if (is_has == 0)
		{
			v_gx_sl_zu_by_no.push_back(sel_row);
		}
	}
	return v_gx_sl_zu_by_no;
}

void Prog_manager::set_Prog_NC_move(vec3 in_move)
{
	Prog_NC_move = in_move;
}

fangzhen_zhu* Prog_manager::get_zhu_prog()
{
	return cur_tool_ptr->prog_zhu;
}

int Prog_manager::get_FZ_2D_xx_id()
{
	if (FZ_2D == nullptr)
	{
		return 0;
	}
	return FZ_2D->gongjian_xx_num;
}

void Prog_manager::set_FZ_2D_xx_id(int in_id)
{
	return FZ_2D->set_gongjianXX_num(in_id);
}

void Prog_manager::gen_tance_prog_of_first(double dis_safe_in, double dis_start_in, double dis_more_in)
{
	length_tance_fu* fu_ptr = new length_tance_fu(cur_tool_ptr->prog_zhu, 0);

	fu_ptr->set_tance_dis(dis_safe_in, dis_start_in, dis_more_in);

	//探测点为{0,0,0}，法向{0,0,-1}，绝对坐标系{1,0,0}
	//vec3 t_p = { 0.0,0.0,0.0 }; //
	vec3 t_n = { 1.0,0.0,0.0 };

	fu_ptr->v_points_in = tance_start_p;
	fu_ptr->v_nors_in = t_n;
	fu_ptr->v_dis_jiagong_in = dis_jiagong_to_tance;
	fu_ptr->v_A_in = 0.0;
	fu_ptr->v_C_in = -90.0;

	//将tance副程序挂到主程序上
	cur_tool_ptr->prog_zhu->push_my_fu(fu_ptr);
}

void Prog_manager::gen_tance_prog_of_sel_gx(double dis_safe_in, double dis_start_in, double dis_more_in)
{
	//清空主程序上的所有副程序
	if (cur_tool_ptr->prog_zhu != nullptr)
	{
		delete cur_tool_ptr->prog_zhu;
		cur_tool_ptr->prog_zhu = nullptr;
	}
	cur_tool_ptr->prog_zhu = new fangzhen_zhu();

	//ready_cal_DL_pre_data();

	//刀的基本结构计算
	cur_tool_ptr->cal_selected_gx_DL(0);

	//选择的工序对应一个探测副程序
	for (int i = 0; i < cur_tool_ptr->v_select_cal_gx_index.size(); i++)
	{
		//int sel_row = v_gx_select_cal_DL[i];
		//int cur_gx_index = cur_tool->v_gx_order[sel_row];
		int sel_order = cur_tool_ptr->v_select_cal_gx_index[i];
		Miller_GX_Base* cur_gx_ptr = cur_tool_ptr->get_gx(sel_order);

		//计算完刀路后才有面的法向,
		cur_gx_ptr->init_prog_of_gx();

		//daijie_houchuli_a_gx_DL(cur_gx_ptr->DL_end, cur_gx_ptr->shalun_canshu, cur_gx_ptr->A_before,
		//	cur_gx_ptr->A_before_ren, cur_gx_ptr->sel_A_before_ren);

		//根据工序类型拿对应的探测输入
		int cur_gx_type = cur_gx_ptr->base_data.
			type_gx;

		//在父项刀指针里拿
		vector<vec3> ls_v_points;
		vector<vec3> ls_v_nors;
		vector<double> ls_v_A;
		vector<double> ls_v_C;
		//当前刀路数据包含了进退刀，多个刃的数据 ???，后刀面需要刃线区分球头
		//在刀路中找到第一个刃磨削点的开始，结束下标
		get_a_gx_tance_input(cur_gx_ptr, cur_gx_ptr->DL_end, ls_v_points, ls_v_nors, ls_v_A, ls_v_C);

		//准备副程序
		buchang_tance_fu* fu_ptr = new buchang_tance_fu(cur_tool_ptr->prog_zhu, 0);

		fu_ptr->set_tance_dis(dis_safe_in, dis_start_in, dis_more_in);
		fu_ptr->gx_type_in = cur_gx_type;
		fu_ptr->v_points_in = ls_v_points;
		fu_ptr->v_nors_in = ls_v_nors;
		fu_ptr->v_A_in = ls_v_A;
		fu_ptr->v_C_in = ls_v_C;

		//将工序的副程序挂到主程序上
		cur_tool_ptr->prog_zhu->push_my_fu(fu_ptr);
	}

	//v_gx_select_cal_DL.clear();

	//生成程序树
	cur_tool_ptr->prog_zhu->generation();

	//2025.3.7
	gen_NC_prog();
}

void Prog_manager::get_a_gx_tance_input(Miller_GX_Base* in_gx_ptr, DL& in_ans_DL, vector<vec3>& ans_v_points, vector<vec3>& ans_v_nors, vector<double>& ans_v_A, vector<double>& ans_v_C)
{
	int start_index = -1;
	int end_index = -1;
	int count_p = in_ans_DL.Data.size();
	for (int i = 0; i < count_p; i++)
	{
		int p_type = in_ans_DL.Data[i].point_type;
		if (p_type == 0 && start_index == -1) //只进一次
		{
			start_index = i;
		}
		if (p_type != 0 && start_index > 0)
		{
			end_index = i - 1;
			break;
		}
	}

	int cur_gx_type = in_gx_ptr->base_data.type_gx;
	switch (cur_gx_type)
	{
	case 0: //锥球前刀面
	{//默认G54等于0
		int p_pos = (start_index + end_index) / 2;
		vec3 ans_p = in_ans_DL.Data[p_pos].G_P;
		vec3 ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);

		vec3 ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0); //前刀面选刀路切向：后指向前
		vec3 ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
		mat33 ans_sys = eye(3, 3);
		ans_sys.col(0) = ls_x;
		ans_sys.col(1) = ls_y;
		ans_sys.col(2) = ans_n;
		double ans_A = 0.0;
		double ans_C = 0.0;

		ans_p = ans_p + normalise(ls_y) * 0.3; //目标点往后角线方向平移小长度

		cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);

		ans_v_points.push_back(ans_p);
		ans_v_nors.push_back(ans_sys.col(2));
		ans_v_A.push_back(ans_A);
		ans_v_C.push_back(ans_C);
	}
	break;
	case 1:
	{
		int p_pos = (start_index + end_index) / 2;
		vec3 ans_p = in_ans_DL.Data[p_pos].G_P;
		vec3 ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);

		vec3 ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0);
		vec3 ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
		mat33 ans_sys = eye(3, 3);
		ans_sys.col(0) = ls_x;
		ans_sys.col(1) = ls_y;
		ans_sys.col(2) = ans_n;
		double ans_A = 0.0;
		double ans_C = 0.0;

		cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);

		ans_v_points.push_back(ans_p);
		ans_v_nors.push_back(ans_sys.col(2));
		ans_v_A.push_back(ans_A);
		ans_v_C.push_back(ans_C);
	}
	break;
	case 2: //锥球后刀面
	{
		//1、从铣刀获取基本球头刃线和螺旋线的点数量
		//int p_count_qiu = in_gx_ptr->self_Dao->get_renxian_of_qiu_count_p(0);
		//int p_count_luo = in_gx_ptr->self_Dao->get_renxian_of_luo_count_p(0);

		////2、获取刀面数据
		//mat data_hdm;
		//in_gx_ptr->self_Dao->get_hdm_1(0, data_hdm); //12*n

		//四个点 ， 对应不到球头相应位置,传入刃线数据
		{
			int p_pos = start_index + 20;
			vec3 ans_p = in_ans_DL.Data[p_pos].G_P;
			vec3 ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);
			vec3 ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0);
			vec3 ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
			ans_p = ans_p + ls_y * 0.0;  //探测点刃线点偏置
			mat33 ans_sys = eye(3, 3);
			ans_sys.col(0) = ls_x;
			ans_sys.col(1) = ls_y;
			ans_sys.col(2) = ans_n;
			double ans_A = 0.0;
			double ans_C = 0.0;
			cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);
			ans_v_points.push_back(ans_p);
			ans_v_nors.push_back(ans_sys.col(2));
			ans_v_A.push_back(ans_A);
			ans_v_C.push_back(ans_C);

			//找球中点
			int qiu_end_index = 0;
			for (int i = start_index; i < end_index; i++)
			{
				vec3 ls_p = in_ans_DL.Data[i].G_P;
				if (ls_p(2) > 0)
				{
					qiu_end_index = i;
					break;
				}
			}

			p_pos = (start_index + qiu_end_index) / 2;
			ans_p = in_ans_DL.Data[p_pos].G_P;
			ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);
			ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0);
			ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
			ans_p = ans_p + ls_y * 0.1;
			ans_sys = eye(3, 3);
			ans_sys.col(0) = ls_x;
			ans_sys.col(1) = ls_y;
			ans_sys.col(2) = ans_n;
			ans_A = 0.0;
			ans_C = 0.0;
			cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);
			ans_v_points.push_back(ans_p);
			ans_v_nors.push_back(ans_sys.col(2));
			ans_v_A.push_back(ans_A);
			ans_v_C.push_back(ans_C);

			p_pos = qiu_end_index;
			ans_p = in_ans_DL.Data[p_pos].G_P;
			ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);
			ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0);
			ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
			ans_p = ans_p + ls_y * 0.1;
			ans_sys = eye(3, 3);
			ans_sys.col(0) = ls_x;
			ans_sys.col(1) = ls_y;
			ans_sys.col(2) = ans_n;
			ans_A = 0.0;
			ans_C = 0.0;
			cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);
			ans_v_points.push_back(ans_p);
			ans_v_nors.push_back(ans_sys.col(2));
			ans_v_A.push_back(ans_A);
			ans_v_C.push_back(ans_C);

			p_pos = (qiu_end_index + end_index) / 2;
			ans_p = in_ans_DL.Data[p_pos].G_P;
			ans_n = in_ans_DL.Data[p_pos].G_SYS_HDM.col(2);
			ls_x = in_ans_DL.Data[p_pos].G_SYS_HDM.col(0);
			ls_y = in_ans_DL.Data[p_pos].G_SYS_HDM.col(1);
			ans_p = ans_p + ls_y * 0.1;
			ans_sys = eye(3, 3);
			ans_sys.col(0) = ls_x;
			ans_sys.col(1) = ls_y;
			ans_sys.col(2) = ans_n;
			ans_A = 0.0;
			ans_C = 0.0;
			cal_G_p_tance_AC(ans_p, ans_sys, cur_gx_type, ans_A, ans_C);
			ans_v_points.push_back(ans_p);
			ans_v_nors.push_back(ans_sys.col(2));
			ans_v_A.push_back(ans_A);
			ans_v_C.push_back(ans_C);
		}

	}
	break;

	default:
		break;
	}
}

void Prog_manager::cal_G_p_tance_AC(vec3 ans_point, mat33 ans_sys, int in_type, double& ans_A, double& ans_C)
{
	//工件放到到绝对坐标系 
	ans_point = tcRotX(3, 90) * ans_point;
	ans_sys = tcRotX(3, 90) * ans_sys;

	mat33 trans_sys = eye(3, 3);

	double cal_A = 0.0;
	double cal_C = 0.0;

	if (in_type == 2 || in_type == 9 || in_type == 13 || in_type == 18) //其他后刀面工序 
	{
		//将刃线切向转到在XOY平面的投影平行绝对坐标系的Y
		vec3 ls_tou = normalise(tc_vec_prj_to_plane(ans_sys.col(0), tcY(3)));
		cal_A = deltaRotAngle(ls_tou, tcX(3), tcY(3)); //转到竖直面,

		trans_sys = tcRotY(3, cal_A) * trans_sys; //在C=0的位置转y
		mat33 ls_sys = trans_sys * ans_sys;

		//探测柱面AC值会造成干涉 1.2-加判断,不改变探测点及法向，改变工件摆放的位置
		//判断后刀面y轴，的朝向，将工件头朝右
		cal_C = deltaRotAngle(ls_sys.col(1), -tcX(3), tcZ(3)); //转到平行-X
		double jia_ang = dot(ls_sys.col(1), tcY(3));
		if (jia_ang > 0.0)
		{
			cal_C = cal_C - 180.0;
		}

		trans_sys = tcRotZ(3, cal_C) * trans_sys;
	}
	else
	{
		//将刃线法向转到在XOY平面的投影平行绝对坐标系的Y
		vec3 ls_tou = normalise(tc_vec_prj_to_plane(ans_sys.col(1), tcY(3)));
		cal_A = deltaRotAngle(ls_tou, -tcX(3), tcY(3)); //转到水平面

		trans_sys = tcRotY(3, cal_A) * trans_sys;
		mat33 ls_sys = trans_sys * ans_sys;

		cal_C = deltaRotAngle(ls_sys.col(1), tcY(3), tcZ(3)); //转到平行Y

		trans_sys = tcRotZ(3, cal_C) * trans_sys;
	}

	//转到Z方向探测1.3 》A + 90， 绕x转90

	ans_point = tcRotX(3, 90.0) * trans_sys * ans_point;
	ans_sys = tcRotX(3, 90.0) * trans_sys * ans_sys;
	ans_A = cal_A;
	ans_C = cal_C;
}


int Prog_manager::get_new_gx_type(int order)
{
	return  cur_tool_ptr->v_new_gx_type[order];
}



void Prog_manager::init_gx_type_name()
{
	v_gx_name_show.push_back("成型-开槽");
	v_gx_name_show.push_back("螺旋槽");
	v_gx_name_show.push_back("端齿槽-球头");
	v_gx_name_show.push_back("端齿槽-平底");
	v_gx_name_show.push_back("圆角前刀面");

	v_gx_name_show.push_back("成型-后刀面");
	v_gx_name_show.push_back("锥球-后刀面");
	v_gx_name_show.push_back("平底-端后刀面");
	v_gx_name_show.push_back("平底-柱后刀面");
	v_gx_name_show.push_back("圆角R-后刀面");
	v_gx_name_show.push_back("刀尖间隙");

	v_gx_name_show.push_back("成型-开槽2");
}

string Prog_manager::get_new_gx_name( int order)
{
	int ls_type = cur_tool_ptr->v_new_gx_type[order];
	return v_gx_name_show[ls_type];
}

string Prog_manager::get_n_gx_type_name(int order)
{
	int ls_type = cur_tool_ptr->ptr_list_gx->v_obj_ptr[order]->base_data.type_gx;
	return v_gx_name_show[ls_type];
}

void Prog_manager::gen_NC_prog()
{
	debug_tool* new_tool = new debug_tool;
	string NC_prog_dir = "C:\\ml_240221";

	//需要可自动创建文件夹 6.9
	namespace fs = std::filesystem;
	if (!fs::exists(NC_prog_dir)) 
	{
		if (fs::create_directory(NC_prog_dir)) 
		{
			std::cout << "文件夹创建成功: "  << std::endl;
		}
		else {
			std::cerr << "文件夹创建失败: "  << std::endl;
		}
	}
	else 
	{
		std::cout << "文件夹已存在: " << std::endl;
	}

	this->get_zhu_prog()->prog_file.init(get_zhu_prog()->name); //25.9.11
	this->get_zhu_prog()->prog_file.Recover_nc_code(NC_prog_dir);
}

void Prog_manager::set_cal_prog_flag(int flag)
{
	flag_nc_or_2d_or_3d = flag;
}


mat44 scale_and_trans_mat;		//视角位置  
mat44 base_mat;	//机床所在位置 基本不变
//vec5 ls_mac_sys = { -100,-260,-120,0,0 }; //机床内部轴坐标位置   -200 碰

bool is_move = false;

fangzhen_3D::fangzhen_3D()
{
	zhu_fu_zi_prog_ptr = nullptr;

	//定义可视化机床
	vis_manager_ptr = new visualize_manager;


	//调试器
	debug_tool_ptr = nullptr;
}

fangzhen_3D::~fangzhen_3D()
{
	if (debug_tool_ptr != nullptr)
	{
		delete debug_tool_ptr;
	}
}

void fangzhen_3D::init_sl_lib_3D(Prog_manager* in_prog_ptr)
{
	sl_lib_3D.clear();
	sl_lib_on_sl_num.clear();
	
	for (int i = 0; i < 6; i++)
	{
		int ls_slz_id = in_prog_ptr->obj_JC_sl_lib.get_slz_id(i);
		vector<int> temp;
		if (ls_slz_id == -1)
		{
		}
		else
		{
			in_prog_ptr->sl_manager.get_a_group_all_wheel_key(ls_slz_id, temp);
		}
		sl_lib_3D.push_back(ls_slz_id);
		sl_lib_on_sl_num.push_back(temp);
	}
}

//bool fangzhen_3D::change_sl(int sl_num)
//{
//	set_shaluncanshu(sl_lib_3D[sl_num]);
//	return 1;
//}

bool fangzhen_3D::change_sl(int slz_pos, int in_sl_pos)
{
	if (slz_pos < 0 || slz_pos > 5)
	{
		return false;
	}
	set_shaluncanshu(sl_lib_3D[slz_pos], sl_lib_on_sl_num[slz_pos][in_sl_pos]);

	return 1;
}

bool fangzhen_3D::set_gj_by_stl_and_trans_pos(string in_dir, double in_acc_d, vec& in_trans)
{
	cur_gj_init_type = 0;
	in_dir = "STL\\r20_l100.stl";

	gj_stl = in_dir;
	acc_d = in_acc_d;
	trans_init = in_trans;

	vis_manager_ptr->init_gj_by_stl(gj_stl, trans_init, acc_d);
	return true;
}

bool fangzhen_3D::set_gj_by_col_and_trans_pos(double D, double len, double in_acc_d)
{
	cur_gj_init_type = 1;
	col_D = D;
	col_len = len;
	acc_d = in_acc_d;

	//设置工件安装位姿
	vis_manager_ptr->init_gj_by_col(col_D, col_len, acc_d);
	return true;
}

bool fangzhen_3D::set_gj_by_rot_and_trans_pos(double D, double zhui, double len_ren, double len_all, double D_bing, double in_acc_d)
{
	cur_gj_init_type = 2;
	rot_D = D;
	rot_zhui = zhui;
	rot_len_ren = len_ren;
	rot_len_all = len_all;
	rot_D_bing = D_bing;
	acc_d = in_acc_d;

	//构建一个3*n 的矩阵，类似DXF线， z =0， 8.21
	mat outline;
	int p_count = len_all / in_acc_d;
	outline.resize(3, 0);
	outline.insert_cols(0, p_count);

	//球头线，锥度线，柄线
	int p_inset = D / in_acc_d;
	for (int i = 0; i < p_inset; i++)
	{
		double x = -D + i * in_acc_d;
		double y = sqrt((D * D) - (x * x));  //都是正值
		double z = 0;
		vec3 ans_p = { x,y,z };
		outline.col(i) = ans_p;
	}
	//求锥接点
	vec3 ans_p = { D, D, 0.0 };
	outline.col(p_inset) = ans_p;
	p_inset++;
	//锥结束点
	double ls_h = (len_ren - D) * tan(tcRadians(zhui));
	ans_p = { len_ren, D + ls_h, 0.0 };
	outline.col(p_inset) = ans_p;
	p_inset++;
	//柄起点
	ans_p = { len_ren, D_bing, 0.0 };
	outline.col(p_inset) = ans_p;
	p_inset++;
	//柄终点
	ans_p = { len_all, D_bing, 0.0 };
	outline.col(p_inset) = ans_p;

	vis_manager_ptr->init_gj_by_rot(outline, 0.1);
	return false;
}

bool fangzhen_3D::set_shaluncanshu(int in_slz_id,int in_sl_id)
{
	vis_manager_ptr->load_shalun(in_slz_id, in_sl_id);

	vec3 sl_ckp = { 219.832, 350.927, 179.5 };
	vis_manager_ptr->sl_data_ptr->set_JC_O_SL(sl_ckp);

	//vector<mat> temp_mat;
	//vis_manager_ptr->sl_manager->get_group_show_outline(in_sl_zu,temp_mat);
	//vis_manager_ptr->jichuang_gl_ptr->init_tool(temp_mat);

	return true;
}

bool fangzhen_3D::set_fangzhen_zhu(fangzhen_zhu* in_ptr)
{
	zhu_fu_zi_prog_ptr = in_ptr;
	debug_tool_ptr->set_nc_prog(in_ptr);
	return true;
}

bool fangzhen_3D::set_debug_tool(debug_tool* in_debug)
{
	debug_tool_ptr = in_debug;
	//debug_tool_ptr->set_nc_prog(zhu_fu_zi_prog_ptr->entrance);
	//debug_tool_ptr->set_nc_prog(in_debug->f_manager->Recover_block());
	return true;
}

void fangzhen_3D::init(tcGLMatrixCtrl* mat_ptr, Prog_manager* in_prog_ptr)
{
	vis_manager_ptr->init_mat_ctrl(mat_ptr);
	vis_manager_ptr->sl_manager = &in_prog_ptr->sl_manager;

	//debug_tool* ls_debug_ptr = new debug_tool;
	//virtual_machine* ls_machine_ptr = new virtual_machine;
	//ls_debug_ptr->f_manager->data_clear();

	//
	//ls_machine_ptr->set_move_speed(1);
	//ls_debug_ptr->set_machine(ls_machine_ptr);
	//debug_tool_ptr->zhu_program_now->prog_file.init(in_prog_ptr->cur_tool_ptr->prog_zhu->name);

	//内部实现还是用的stl
	   //wheel_group* sl_zu_ptr = P_manager->sl_manager.get_a_group_ptr_by_wheel(0);
	   //FZ_3D->set_shaluncanshu(sl_zu_ptr);

	init_sl_lib_3D(in_prog_ptr);
	set_gj_by_col_and_trans_pos(in_prog_ptr->cur_tool_ptr->get_D(), in_prog_ptr->cur_tool_ptr->get_alllen(), 0.1);

	set_fangzhen_zhu(in_prog_ptr->cur_tool_ptr->prog_zhu);
	set_debug_tool(debug_tool_ptr);
}

void fangzhen_3D::set_show(vec& in_trans)
{
	vis_manager_ptr->pos_gj_trans = in_trans;
}


int fangzhen_3D::fangzhen_process()
{
	::gladLoadGL();
	
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_CULL_FACE); //双面显示
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	base_mat = eye(4, 4);


	if (debug_tool_ptr->machine->is_M30)
	{
		debug_tool_ptr->machine->play_or_pause = 0;

		debug_tool_ptr->zhu_program_now->prog_file.ifile_data.seekg(0, std::ios::beg); //   
		nb_NC_block::position = debug_tool_ptr->zhu_program_now->prog_file.ifile_data.tellg();
	}


	if (debug_tool_ptr->machine->play_or_pause)
	{

		if (debug_tool_ptr->machine->run_one == 0)
		{

			while (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
			{
				if (debug_tool_ptr->no_next_block())
				{
					debug_tool_ptr->clean_temp_block();
					nc_block new_process_block(debug_tool_ptr->zhu_program_now->prog_file.Recover_block());
					debug_tool_ptr->set_nc_prog(new_process_block);
				}

				debug_tool_ptr->run_one();
				if (debug_tool_ptr->machine->is_M30)
				{
					break;
				}
			}
			if (!debug_tool_ptr->machine->is_cache_empty())//不空为真
			{
				debug_tool_ptr->machine->move_cache();

				//判断是否换砂轮
				int prog_using_tool = debug_tool_ptr->machine->get_using_tool();
				int prog_using_sl_pos = debug_tool_ptr->machine->get_using_sl_num_on_slz();
				if (using_sl_num_3D != prog_using_tool) //砂轮组不同
				{
					using_sl_num_3D = prog_using_tool;
					using_sl_pos = prog_using_sl_pos;
					change_sl(using_sl_num_3D, prog_using_sl_pos);
				}
			}

		}
		else
		{
#pragma region 准备显示数据
			base_mat = eye(4, 4);
			while (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
			{
				if (debug_tool_ptr->no_next_block())
				{
					debug_tool_ptr->clean_temp_block();
					nc_block new_process_block(debug_tool_ptr->zhu_program_now->prog_file.Recover_block());
					debug_tool_ptr->set_nc_prog(new_process_block);
				}

				debug_tool_ptr->run_one();
				if (debug_tool_ptr->machine->is_M30)
				{
					break;
				}
			}

			if (!debug_tool_ptr->machine->is_cache_empty())//不空为真
			{
				if ( 0 < debug_tool_ptr->machine->count_run_one)
				{
					debug_tool_ptr->machine->count_run_one--;

					debug_tool_ptr->machine->move_cache();

					//判断是否换砂轮
					int prog_using_tool = debug_tool_ptr->machine->get_using_tool();
					int prog_using_sl_pos = debug_tool_ptr->machine->get_using_sl_num_on_slz();
					if (using_sl_num_3D != prog_using_tool) //砂轮组不同
					{
						using_sl_num_3D = prog_using_tool;
						using_sl_pos = prog_using_sl_pos;
						change_sl(using_sl_num_3D, prog_using_sl_pos);
					}

				}
			}
#pragma endregion
		}

		
	}
	//暂停也要显示状态

	vis_manager_ptr->set_view_mat(scale_and_trans_mat);
	vis_manager_ptr->show_now_state(
		debug_tool_ptr->machine->get_mac_sys(),
		debug_tool_ptr->machine->get_abs_sys(),
		0, base_mat, scale_and_trans_mat);

	return 0;
}

void fangzhen_3D::set_button_play()
{
	debug_tool_ptr->machine->play_or_pause = 1;
	debug_tool_ptr->machine->run_one = 0;
}

void fangzhen_3D::set_button_pause()
{
	debug_tool_ptr->machine->play_or_pause = 0;
}

void fangzhen_3D::hide_parts(vector<bool>& v_hide)
{
	vis_manager_ptr->set_hide_parts(v_hide);
}

void fangzhen_3D::set_button_run_one(int step_size)
{
	debug_tool_ptr->machine->reset_button = 0;
	debug_tool_ptr->machine->play_or_pause = 1;
	debug_tool_ptr->machine->run_one = 1;
	debug_tool_ptr->machine->count_run_one = step_size;
}

void fangzhen_3D::set_button_reset_move_prog()
{
	debug_tool_ptr->machine->reset_button = 1;
	debug_tool_ptr->machine->is_M30 = 0;
	debug_tool_ptr->reset_nc_prog();
	debug_tool_ptr->machine->clear_cache();
}



fangzhen_2D::fangzhen_2D()
{
	prog_manager_ptr = nullptr;
	pGLFWwindow = nullptr;

	show_ptr = new jiemian_show;

	debug_tool_ptr = nullptr;
	zhu_fu_zi_prog_ptr = nullptr;
}

fangzhen_2D::~fangzhen_2D()
{
	if (debug_tool_ptr != nullptr)
	{
		delete debug_tool_ptr;
	}
}

void fangzhen_2D::init_glfw_show_set()
{
	::gladLoadGL();
	glfwMakeContextCurrent(pGLFWwindow); // 确保当前窗口是激活的

	for (int i = 0; i < 20; i++) //12.3
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(pGLFWwindow); // 交换前后缓冲区  

	// 禁用光源和光照  
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// 禁用剔除面  
	glDisable(GL_CULL_FACE);

	// 重置材质、显示模式等（如果使用）  
	glShadeModel(GL_FLAT); // 可根据需要调整  

	// 重置深度测试设置  
	glDisable(GL_DEPTH_TEST);

	// 恢复矩阵到单位矩阵  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 重新设置投影（如需要）  
	glOrtho(-1, 1, -1, 1, 100, -100);



	// 禁用重新缩放法线  
	glDisable(GL_RESCALE_NORMAL);

	// 重置着色模型  
	glShadeModel(GL_FLAT); // 设为平坦着色，或可以保持为GL_SMOOTH根据需求  

	// 切换到投影矩阵模式并重置为单位阵  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 恢复默认正交投影，如果需要可以设定回原来的值  
	glOrtho(-1, 1, -1, 1, 100, -100); // 根据需求设置  

	// 切换到模型视图矩阵模式，并重置为单位阵  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 如果需要，可以重置其他状态  
	glEnable(GL_DEPTH_TEST); // 启用深度测试，根据需要决定  
	glCullFace(GL_BACK); // 继续背面剔除  
	glFrontFace(GL_CCW); // 继续设置前面朝向  




	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_RESCALE_NORMAL);
	// 设置平滑着色模式，保证颜色插值平滑
	glShadeModel(GL_SMOOTH);
	// 设置投影矩阵为正交投影
	glMatrixMode(GL_PROJECTION);  // 切换到投影矩阵模式
	glLoadIdentity();             // 将投影矩阵重置为单位矩阵
	//glOrtho(-0.5, 0.5, -0.5, 0.5, 1, -1);
	glOrtho(-1, 1, -1, 1, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glfwSwapInterval(1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void fangzhen_2D::init_view_set()
{
	P_look=zeros(3);
	N_look = { 1.0,0.0,0.0 };
	P_screen=zeros(3);
	fangda_xishu = 1.0;
	xuanzhuan_jiaodu = 0.0;
}

mat fangzhen_2D::cal_G_SYS_Look()
{
	//计算上方向
	vec plane_p = P_look;
	plane_p(0) = 0.0;
	if (norm(plane_p) < 0.0001)
	{
		plane_p = tcY(3);
	}
	plane_p = normalise(plane_p);
	vec shang = tcRotX(3, 90.0) * plane_p;

	N_look = normalise(N_look);
	if (N_look(2) > 0.999999)
	{
		shang = tcX(3);
	}
	else if (N_look(2) < -0.999999)
	{
		shang = -tcX(3);
	}
	else
	{
		shang = normalise(tc_vec_prj_to_plane(shang, N_look));
	}

	mat mG_SYS_Look = zeros(3, 4);

	//指向眼睛
	mG_SYS_Look.col(2) = N_look;

	//指向上
	mG_SYS_Look.col(1) = shang;

	mG_SYS_Look.col(0) = normalise(tc_cross(mG_SYS_Look.col(1), mG_SYS_Look.col(2)));

	mG_SYS_Look.col(3) = P_look;

	mG_SYS_Look.insert_rows(3, 1, true);

	mG_SYS_Look(3, 3) = 1.0;

	return mG_SYS_Look;
}

void fangzhen_2D::set_P_look(vec3 p)
{
	P_look = p;
}

void fangzhen_2D::set_N_look(vec3 n)
{
	N_look = n;
}

void fangzhen_2D::set_P_screen(vec3 p)
{
	P_screen = p;
}

void fangzhen_2D::set_fangda(vec point1, vec point2)
{
	//平移向量 
	vec2 zhongdian = (point1 + point2) / 2;
	vec move_v = { zhongdian(0),zhongdian(1), 0.0,0.0 };
	//move_v = screen_scale_mat * move_v * (lenth_of_a_pixel / 0.03125);
	move_v = -move_v * (lenth_of_a_pixel / 0.03125) / fangda_xishu;
	P_screen = P_screen + move_v.subvec(0, 2);

	double delta_fangda = 0.0;
	show_ptr->get_Ctrl_view(point1, point2, delta_fangda);

	fangda_xishu = fangda_xishu * delta_fangda;

}

void fangzhen_2D::set_fangda_xishu(double m)
{
	fangda_xishu = m;
}

void fangzhen_2D::set_xuanzhuan_jiaodu(double j)
{
	xuanzhuan_jiaodu = j;
}

bool fangzhen_2D::set_debug_tool(debug_tool* in_debug)
{
	debug_tool_ptr = in_debug;
	//debug_tool_ptr->set_nc_prog(zhu_fu_zi_prog_ptr);
	//debug_tool_ptr->set_machine(machine_ptr);
	return true;
}

bool fangzhen_2D::set_sl_outline_by_sl_id(int sl_id)
{
	mat ls_sl_out_line;
	prog_manager_ptr->sl_manager.get_2D_wheel_outline(sl_id, ls_sl_out_line);
	vis_2D_manager.set_wheel_outline(ls_sl_out_line);
	return true;
}

void fangzhen_2D::set_gj_D_and_lenth(double gj_D, double gj_len)
{
	vis_2D_manager.set_gj_YuanZhu(gj_D, gj_len);
}

void fangzhen_2D::set_gongjianXX_num(int gongjianXX_num_in)
{
	gongjian_xx_num = gongjianXX_num_in;
}

void fangzhen_2D::set_gongjianXX()
{
	Cal_XingXian xx = *(prog_manager_ptr->cur_tool_ptr->ptr_list_xx->get_obj(gongjian_xx_num));
	xx.Sample(0.04, 1.0);
	vis_2D_manager.set_line(xx.BG_P());
}



void fangzhen_2D::cal_look_mat()
{
	mat44 G_SYS_Look = cal_G_SYS_Look();
	mat44 screen_trans_mat = eye(4, 4);
	screen_trans_mat.submat(0, 3, 2, 3) = P_screen;

	mat44 screen_scale_mat = eye(4, 4);
	screen_scale_mat(0, 0) = fangda_xishu;
	screen_scale_mat(1, 1) = fangda_xishu;
	screen_scale_mat = screen_scale_mat * show_ptr->reset_view();

	mat44 screen_rot_mat = tcRotZ(4, xuanzhuan_jiaodu);

	//总公式
	mat ans = inv(G_SYS_Look);

	 ans = inv(screen_rot_mat * screen_scale_mat * screen_trans_mat * inv(G_SYS_Look));


	//磨削坐标系，起点x偏置等于2d的Z偏置/
	vis_2D_manager.set_face(ans);

	mat weizhi_mat = eye(4, 4);
	vis_2D_manager.set_gj_WeiZhi(weizhi_mat);

	mat look_points = vis_2D_manager.get_look_points();
	show_ptr->draw_gj_2D(look_points);
}

void fangzhen_2D::trans_vec5_to_mat44(vec5 cur_coor, mat44& G_SYS_SL)
{
	mat44 ABS_SYS_G;
	mat44 ABS_SYS_SL;
	mat44 base = eye(4, 4);

	cal_gongjian_abs_mat(cur_coor, base, ABS_SYS_G);
	cal_shalun_abs_mat(cur_coor, base, ABS_SYS_SL);

	cal_SL_to_GJ(ABS_SYS_G, ABS_SYS_SL, G_SYS_SL);
}

void fangzhen_2D::cal_gongjian_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& ABS_SYS_G)
{
	ABS_SYS_G =
		tcTranslate(-in_abs_sys(0), 0.0, 0.0) * tcRotZ(4, in_abs_sys(4)) * tcRotY(4, in_abs_sys(3)) //计算机床运动
		* tcRotZ(4, 90)																				//转换工件坐标系
		* base_in ;
}

void fangzhen_2D::cal_shalun_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& ABS_SYS_SL)
{
	ABS_SYS_SL = tcTranslate(0.0, in_abs_sys(1), 0.0) * tcTranslate(0.0, 0.0, in_abs_sys(2))		//计算机床运动
		* tcRotZ(4, -90.0)																			//转换砂轮坐标系
		* base_in;
}

void fangzhen_2D::cal_SL_to_GJ(mat44& ABS_SYS_G, mat44& ABS_SYS_SL, mat44& G_SYS_SL)
{
	//vec3 ABS_O_SL = ABS_SYS_SL.submat(0, 3, 2, 3);
	//mat33 ABS_SYS_SL = ABS_SYS_SL.submat(0, 0, 2, 2);

	//vec3 ABS_O_GJ = ABS_SYS_G.submat(0, 3, 2, 3);
	//mat33 ABS_SYS_GJ = ABS_SYS_G.submat(0, 0, 2, 2);

	//vec3  GJ_O_SL = ABS_SYS_G.i() * (ABS_O_SL - ABS_O_GJ);
	//mat33 GJ_SYS_SL = ABS_SYS_G.i() * ABS_SYS_SL;

	////当前计算的砂轮相对工件的位置，是砂轮参考点(法向朝外)，加上法兰长度到端面才能计算二维-9.12
	////GJ_O_SL = GJ_O_SL + GJ_SYS_SL.col(2) * (lenth_ckd_to_outface);

	////将砂轮坐标系的回转轴，转为X轴
	//G_SYS_SL.col(0) = { GJ_SYS_SL.col(2)(0), GJ_SYS_SL.col(2)(1), GJ_SYS_SL.col(2)(2),  0 };
	//G_SYS_SL.col(1) = { GJ_SYS_SL.col(0)(0), GJ_SYS_SL.col(0)(1), GJ_SYS_SL.col(0)(2),  0 };
	//G_SYS_SL.col(2) = { GJ_SYS_SL.col(1)(0), GJ_SYS_SL.col(1)(1), GJ_SYS_SL.col(1)(2),  0 };
	//G_SYS_SL.col(3) = { GJ_O_SL(0),          GJ_O_SL(1),		    GJ_O_SL(2),	 1 };

	////加上参考点到内端面长度才能计算二维-10.14
	////gj_sys_sl = gj_sys_sl * tcTranslate(lenth_ckd_to_inface, 0, 0);

	G_SYS_SL = ABS_SYS_G.i() * ABS_SYS_SL;
}

void fangzhen_2D::set_button_reset()
{
	debug_tool_ptr->machine->reset_button = 1;
	debug_tool_ptr->machine->is_M30 = 0;
	debug_tool_ptr->reset_nc_prog();
	debug_tool_ptr->machine->clear_cache();
}

void fangzhen_2D::set_button_play()
{
	debug_tool_ptr->machine->reset_button = 0;
	debug_tool_ptr->machine->play_or_pause = true;
	debug_tool_ptr->machine->run_one = 0;
}

void fangzhen_2D::set_button_pause()
{
	debug_tool_ptr->machine->reset_button = 0;
	debug_tool_ptr->machine->play_or_pause = false;
}

void fangzhen_2D::set_button_run_one(int step_size)
{
	debug_tool_ptr->machine->reset_button = 0;
	debug_tool_ptr->machine->play_or_pause = 1;
	debug_tool_ptr->machine->run_one = 1;
	debug_tool_ptr->machine->count_run_one = step_size;
}

void fangzhen_2D::set_button_clear_screen()
{
	debug_tool_ptr->machine->count_clear_screen = 2;
}

void fangzhen_2D::init_sl_lib_2D(Prog_manager* in_prog_ptr)
{
	prog_manager_ptr = in_prog_ptr;

	//2D仿真进入时，清空
	sl_lib_on_sl_num.clear();
	
	for (int i = 0; i < 6; i++)
	{
		int cur_sl_zu_num = prog_manager_ptr->obj_JC_sl_lib.get_slz_id(i);
		vector<int> sl_count_num;
		if (cur_sl_zu_num == -1)
		{
			//没安装砂轮组
			sl_count_num.push_back(-1);
			sl_count_num.push_back(-1);
			sl_count_num.push_back(-1);
		}
		else
		{
			//一个砂轮组上挂的砂轮数量不等
			bool is_get = prog_manager_ptr->sl_manager.get_a_group_all_wheel_key(cur_sl_zu_num, sl_count_num);
			if (is_get == 1)
			{
				throw - 1;
			}
		}
		sl_lib_on_sl_num.push_back(sl_count_num);
	}

	//构造外端面长度容器
	//v_gx_lenth_ckd_to_inface = in_prog_ptr->v_2D_need_lenth;
}

bool fangzhen_2D::change_sl(int slz_num, int in_sl_pos)
{
	if (slz_num < 0 || slz_num > 5)
	{
		return false;
	}
	set_sl_outline_by_sl_id(sl_lib_on_sl_num[slz_num][in_sl_pos]);

	////换参考点长度
	//lenth_ckd_to_inface = v_gx_lenth_ckd_to_inface[index_ckd_out_face];
	//index_ckd_out_face++;

	return true;
}

void fangzhen_2D::init(tcGLMatrixCtrl* mat_ptr, Prog_manager* in_prog_ptr, GLFWwindow* pwnd)
{
	pGLFWwindow = pwnd;

	//设置仿真用主程序
	set_fangzhen_zhu(in_prog_ptr->get_zhu_prog());

	//关联调试器虚拟机
	show_ptr->set_2D_OpenGl_show();

	//初始化砂轮库
	init_sl_lib_2D(in_prog_ptr);

	//初始化视口参数
	init_view_set();

	//set_gongjianXX_num(sel_xx_id);
	set_gongjianXX();
}

void fangzhen_2D::set_show(double dlg_len, double dil_high, double in_xishu)
{
	double xishu_start = in_xishu;
	show_ptr->set_L_H(dlg_len, dil_high, xishu_start); //0.03125
}

bool fangzhen_2D::set_fangzhen_zhu(fangzhen_zhu* in_ptr)
{
	zhu_fu_zi_prog_ptr = in_ptr;
	debug_tool_ptr->set_nc_prog(in_ptr);
	return true;
}

//mat44 ls(fill::zeros);
//double xs = 0.075;
//xs = xs * sf;
//mat pingyi = tcTranslate(tx, ty, 0);
///*{ 1,0,0,tx,
//		   0,1,0,ty,
//		   0,0,1,0,
//		   0,0,0,1};*/
//ls = tcScale(xs * (730.0 / 800.0), xs, 0.01) * mat_ctrl->to_mirror_Z() * mat_ctrl->get_mat_now();
//ls = pingyi * ls;
//glLoadMatrixd(ls.memptr());

void fangzhen_2D::set_renxian_of_ckd(Prog_manager* in_prog_ptr)
{
	//取完整的后刀面刃线
	//in_prog_ptr->cur_tool->get_renxian_of_hdm1(0, renxian_of_ckd);
}

void fangzhen_2D::set_gj_look_jiemian(double in_len, int in_n_or_d)
{
	vec3 ans_n = { 0.0,0.0,1.0 };
	vec3 ans_p = { 0.0,0.0,0.0 };
	double ans_ang = 0.0;

	//for (int i = 0; i < renxian_of_ckd.n_P; i++)
	//{
	//	vec ls_p = renxian_of_ckd.P(i);
	//	if (ls_p(2) > in_len)
	//	{
	//		ans_p = ls_p;
	//		if (in_n_or_d == 0)
	//		{
	//			//垂直法平面，从刀尖看。取-x
	//			ans_n = -renxian_of_ckd.nX(i);
	//		}
	//		else
	//		{
	//			//垂直径向平面，从刀尖看。取-x
	//			ans_n = -renxian_of_ckd.hX(i);
	//		}

	//		//在刃线坐标系下，相对X轴绕Z轴转的角度
	//		vec3 cal_p = { ls_p(0),ls_p(1),0.0 };
	//		ans_ang = deltaRotAngle(tcX(3), normalise(cal_p), tcZ(3));

	//		break;
	//	}
	//}

}

bool fangzhen_2D::fangzhen_process()
{
	//使用GLAD来加载OpenGL
	::gladLoadGL();

	show_ptr->Calls();

	int using_sl_pos = -1;
	//2D显示类
	int using_slz_num_2D = 0;

	mat show_mat;

	if (debug_tool_ptr->machine->is_M30)
	{
		debug_tool_ptr->machine->play_or_pause = 0;

		debug_tool_ptr->zhu_program_now->prog_file.ifile_data.seekg(0, std::ios::beg); //   
		nb_NC_block::position = debug_tool_ptr->zhu_program_now->prog_file.ifile_data.tellg();
	}

	if (debug_tool_ptr->machine->count_clear_screen > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pGLFWwindow); // 交换前后缓冲区  
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pGLFWwindow); // 交换前后缓冲区 

		debug_tool_ptr->machine->count_clear_screen--; //两次才能翻面清屏成功
		return 1; //清屏时，不执行其他显示相关操作
	}

	if (debug_tool_ptr->machine->reset_button)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pGLFWwindow); // 交换前后缓冲区  
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pGLFWwindow); // 交换前后缓冲区  
	}
	else
	{
		if (debug_tool_ptr->machine->play_or_pause)
		{
			if (debug_tool_ptr->machine->run_one == 0)
			{
#pragma region 准备显示数据
				base_mat = eye(4, 4);
				while(debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
				{
					if (debug_tool_ptr->no_next_block())
					{
						debug_tool_ptr->clean_temp_block();
						nc_block new_process_block(debug_tool_ptr->zhu_program_now->prog_file.Recover_block());
						debug_tool_ptr->set_nc_prog(new_process_block);
					}
					debug_tool_ptr->run_one();
					if (debug_tool_ptr->machine->is_M30)
					{
						break;
					}
					
					//检查是否换砂轮，更换
					//仿真砂轮是数据，虚拟机的砂轮是砂轮的索引，
					//程序值改变虚拟机的砂轮索引
				}
				
				if(!debug_tool_ptr->machine->is_cache_empty())
				{
					debug_tool_ptr->machine->move_cache();

					//判断是否换砂轮
					int prog_using_tool = debug_tool_ptr->machine->get_using_tool();
					int prog_using_sl_pos = debug_tool_ptr->machine->get_using_sl_num_on_slz();
					if (using_slz_num_2D != prog_using_tool) //砂轮组不同
					{
						using_slz_num_2D = prog_using_tool;
						using_sl_pos = prog_using_sl_pos;
						change_sl(using_slz_num_2D, prog_using_sl_pos);
					}
					else
					{
						if (using_sl_pos != prog_using_sl_pos) //砂轮不同
						{
							using_sl_pos = prog_using_sl_pos;
							change_sl(using_slz_num_2D, prog_using_sl_pos);
						}
					}

					//计算位置
					vec5 cur_coor = debug_tool_ptr->machine->get_abs_sys();
					mat44 G_SYS_SL = zeros(4, 4);
					//将一个机床绝对vec5转为2d仿真的矩阵
					trans_vec5_to_mat44(cur_coor, G_SYS_SL);

					{
						std::ofstream outfile("vec5_point.txt", std::ios_base::app);

						// 写入坐标点，格式为 "x, y, z"
						outfile << G_SYS_SL(0,3)<< "  " << G_SYS_SL(1, 3) << "  " << G_SYS_SL(2, 3) << std::endl;
					}

					show_mat = vis_2D_manager.get_show_data(G_SYS_SL);
				}
#pragma endregion
			}
			else
			{
#pragma region 准备显示数据
				base_mat = eye(4, 4);
				while (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
				{
					if (debug_tool_ptr->no_next_block())
					{
						debug_tool_ptr->clean_temp_block();
						nc_block new_process_block(debug_tool_ptr->zhu_program_now->prog_file.Recover_block());
						debug_tool_ptr->set_nc_prog(new_process_block);
					}

					debug_tool_ptr->run_one();
					if (debug_tool_ptr->machine->is_M30)
					{
						break;
					}

					//检查是否换砂轮，更换
					//仿真砂轮是数据，虚拟机的砂轮是砂轮的索引，
					//程序值改变虚拟机的砂轮索引
				}

				if (!debug_tool_ptr->machine->is_cache_empty())//不空为真
				{
					if (0 < debug_tool_ptr->machine->count_run_one)
					{
						debug_tool_ptr->machine->count_run_one--;
						debug_tool_ptr->machine->move_cache();

						//判断是否换砂轮
						int prog_using_tool = debug_tool_ptr->machine->get_using_tool();
						int prog_using_sl_pos = debug_tool_ptr->machine->get_using_sl_num_on_slz();
						if (using_slz_num_2D != prog_using_tool) //砂轮组不同
						{
							using_slz_num_2D = prog_using_tool;
							using_sl_pos = prog_using_sl_pos;
							change_sl(using_slz_num_2D, prog_using_sl_pos);
						}
						else
						{
							if (using_sl_pos != prog_using_sl_pos) //砂轮不同
							{
								using_sl_pos = prog_using_sl_pos;
								change_sl(using_slz_num_2D, prog_using_sl_pos);
							}
						}

						//计算位置
						vec5 cur_coor = debug_tool_ptr->machine->get_abs_sys();
						mat44 G_SYS_SL = zeros(4, 4);
						//将一个机床绝对vec5转为2d仿真的矩阵
						trans_vec5_to_mat44(cur_coor, G_SYS_SL);
						
						show_mat = vis_2D_manager.get_show_data(G_SYS_SL);

					}
				}
#pragma endregion
			}
		}
	}

#pragma region 显示2D

	if (!(show_ptr->show_flag %= 1))
	{
		show_ptr->draw_line(show_mat);
	}
	show_ptr->show_flag++;
	double xs = 0.015;
	//glLoadMatrixd(look_SYS_screen.memptr());
	show_ptr->Calls();

#pragma endregion

	return true;
}
