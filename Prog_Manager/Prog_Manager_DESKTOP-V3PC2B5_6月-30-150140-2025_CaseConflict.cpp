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
	if (storage_lib.read_a_row_data(8, pos, name_buffer, NAME_BUFFER_SIZE))
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

inline void Prog_manager::add_a_tool(int dao_type, string in_name)
{
	new_a_tool(dao_type);
	int ans_pos = obj_tool_lib.add_a_row_data(dao_type, in_name);
	
	cur_tool_ptr->set_pos(ans_pos);//6.24增加设置刀具存储位置的函数，将其关联的所有存储都赋值
	cur_tool_ptr->save();
}

bool Prog_manager::open_a_tool(int n_order)
{
	//0、打开前将之前打开的刀save 6.25
	if (cur_tool_ptr != nullptr)
	{
		cur_tool_ptr->save_all();
	}

	//1、根据选择刀具的位置(不显示存储位置)，索引到存储的位置
	int ls_pos = obj_tool_lib.get_tool_pos(n_order);

	//2、在刀具类型文件中读出数据
	//tool_obj_data ls_row_data;
	int ls_type = -1;
	storage_lib.read_a_row_data(17, ls_pos, (char*)&ls_type, sizeof(ls_type));
	
	//2.1 当前刀的两个容器恢复

	//名称位置与刀具对象位置相同
	if (cur_tool_ptr != nullptr)
	{
		//清空之前打开的数据所new出的到
		delete cur_tool_ptr;
	}

	//3、恢复出刀具及参数,挂到刀具指针上
	new_a_tool(ls_type);
	cur_tool_ptr->set_pos(ls_pos);

	//铣刀基类里没有对应的公共参数
	//使用刀具的load加载完数据，不传位置，提前赋值5.28
	cur_tool_ptr->load();

	return true;
}

bool Prog_manager::new_a_tool(int dao_type)
{
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

	cur_tool_ptr->type_tool = dao_type;

	return true;
}

inline vector<int> Prog_manager::check_sl_is_on_lib()
{
	//获取已经安装的砂轮组id
	vector<int> slz_id_laod;
	for (int j = 0; j < 6; j++)
	{
		slz_id_laod.push_back(obj_JC_sl_lib.get_slz_id(0));
	}

	vector<int> v_gx_sl_zu_by_no;
	for (int i = 0; i < cur_tool_ptr->v_select_cal_gx_index.size(); i++)
	{
		int sel_row = cur_tool_ptr->v_select_cal_gx_index[i];
		int cur_sl_num = cur_tool_ptr->ptr_list_gx->get_a_cal_data(sel_row)->get_sl_id();
		int slz_id = sl_manager.get_group_key_by_wheel_key(cur_sl_num);


		//砂轮库上每个位置检查
		bool is_has = 0;
		for (int j = 0; j < 6; j++)
		{

			if (slz_id == slz_id_laod[i])
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
	cur_tool_ptr->cal_selected_gx_DL();

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
		int cur_gx_type = cur_gx_ptr->type_gx;

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

	int cur_gx_type = in_gx_ptr->type_gx;
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
}

string Prog_manager::get_new_gx_name( int order)
{
	int ls_type = cur_tool_ptr->v_new_gx_type[order];
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
	
	new_tool->f_manager->Recover_nc_code(NC_prog_dir);
}


mat44 view_mat;		//视角位置  
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
	debug_tool_ptr->machine->clear_cache();
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
	debug_tool* ls_debug_ptr = new debug_tool;
	virtual_machine* ls_machine_ptr = new virtual_machine;
	ls_debug_ptr->f_manager->data_clear();

	
	ls_machine_ptr->set_move_speed(1);
	ls_debug_ptr->set_machine(ls_machine_ptr);
	ls_debug_ptr->f_manager->Recover_main(in_prog_ptr->cur_tool_ptr->prog_zhu->name);

	//内部实现还是用的stl
	   //wheel_group* sl_zu_ptr = P_manager->sl_manager.get_a_group_ptr_by_wheel(0);
	   //FZ_3D->set_shaluncanshu(sl_zu_ptr);

	init_sl_lib_3D(in_prog_ptr);
	set_gj_by_col_and_trans_pos(in_prog_ptr->cur_tool_ptr->get_D(), in_prog_ptr->cur_tool_ptr->get_renlen(), 0.1);

	set_fangzhen_zhu(in_prog_ptr->cur_tool_ptr->prog_zhu);
	set_debug_tool(ls_debug_ptr);
}

void fangzhen_3D::set_show(vec& in_trans)
{
	vis_manager_ptr->pos_gj_trans = in_trans;
}


bool fangzhen_3D::fangzhen_process()
{
	
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_CULL_FACE); //双面显示
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	base_mat = eye(4, 4);


	if (debug_tool_ptr->machine->is_M30)
	{
		debug_tool_ptr->machine->play_or_pause = 0;
	}


	if (debug_tool_ptr->machine->play_or_pause)
	{
		if (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
		{
			if (debug_tool_ptr->no_next_block())
			{
				debug_tool_ptr->reset_nc_prog_now();
				nc_block new_process_block(debug_tool_ptr->f_manager->Recover_block());
				debug_tool_ptr->set_nc_prog(new_process_block);
			}
			debug_tool_ptr->run_one();
		}
		else//不空为真
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

	vis_manager_ptr->set_view_mat(view_mat);
	vis_manager_ptr->show_now_state(
		debug_tool_ptr->machine->get_mac_sys(),
		debug_tool_ptr->machine->get_abs_sys(),
		0, base_mat, view_mat);

	return true;

}

void fangzhen_3D::set_button_play()
{
	debug_tool_ptr->machine->play_or_pause = 1;
}

void fangzhen_3D::set_button_pause()
{
	debug_tool_ptr->machine->play_or_pause = 0;
}

void fangzhen_3D::hide_parts(vector<bool>& v_hide)
{
	vis_manager_ptr->set_hide_parts(v_hide);
}

void fangzhen_3D::set_button_reset_move_prog()
{
	//重新初始化工件及程序内容
	//if (cur_gj_init_type = 0)
	//{
	//	set_gj_by_stl_and_trans_pos(gj_stl, acc_d, trans_init);
	//}
	//else if (cur_gj_init_type = 1)
	//{
	//	set_gj_by_col_and_trans_pos(col_D,col_len,acc_d);
	//}
	//else
	//{
	//	set_gj_by_rot_and_trans_pos(rot_D, rot_zhui, rot_len_ren, rot_len_all, rot_D_bing, acc_d);
	//}
	debug_tool_ptr->machine->reset_button = 1;
	debug_tool_ptr->machine->is_M30 = 0;
	//调试器复位
	//debug_tool_ptr->reset_nc_prog();
	debug_tool_ptr->f_manager->Recover_main(zhu_fu_zi_prog_ptr->name);

	debug_tool_ptr->machine->clear_cache();
}



fangzhen_2D::fangzhen_2D()
{
	show_ptr = new jiemian_show;

	zhu_fu_zi_prog_ptr = nullptr;

	//调试器
	debug_tool_ptr = nullptr;

	using_slz_num_2D = 0;

	//初始化需要的成员
	trans_look_gj = { 0.0, 0.0, -1.0,
					  0.0, 0.0, 0.0, 0.0, 0.0 };
}

fangzhen_2D::~fangzhen_2D()
{
	debug_tool_ptr->machine->clear_cache();
}

bool fangzhen_2D::set_debug_tool(debug_tool* in_debug)
{
	debug_tool_ptr = in_debug;
	//debug_tool_ptr->set_nc_prog(zhu_fu_zi_prog_ptr);
	//debug_tool_ptr->set_machine(machine_ptr);
	return true;
}

bool fangzhen_2D::set_sl_outline(mat& sl_outline)
{
	vis_2D_manager.set_wheel_outline(sl_outline);
	return true;
}

void fangzhen_2D::set_gj_D_and_lenth(double gj_D, double gj_len)
{
	vis_2D_manager.set_gj_YuanZhu(gj_D, gj_len);
}

void fangzhen_2D::set_gj_jiemian(vec trans)
{
	//设置截面的参考点及法向，输入vec = {n, p，旋转（Z+），偏移}
	vec v_z = { trans(0),trans(1),trans(2), 0 };
	vec v_y = { trans(3),trans(4),  0,      0 };  //要求与法向vz垂直，且不能为0--
	vec v_x = tc_cross(v_y, v_z);
	bool is_zong = 0;
	if (trans(2) < 0.0001 && trans(2) > -0.0001)
	{
		v_x = tcZ(4);
		is_zong = 1;
	}
	else
	{
		v_x = normalise(tcX(4) - dot(v_z, tcX(4)) * v_z);
	}

	v_y = tc_cross(v_z, v_x);
	vec v_p = { trans(3),trans(4),trans(5), 1 };

	mat jiemian_mat = zeros(4, 4);
	jiemian_mat.col(0) = v_x;
	jiemian_mat.col(1) = v_y;
	jiemian_mat.col(2) = v_z;
	jiemian_mat.col(3) = v_p;

	double ang_rotate = trans(6);
	jiemian_mat = jiemian_mat * tcRotZ(4, ang_rotate);

	//磨削坐标系，起点x偏置等于2d的Z偏置
	vis_2D_manager.set_face(jiemian_mat);  //

	double pianyi = trans(7);
	mat weizhi_mat = eye(4, 4);
	weizhi_mat(2, 3) = pianyi;
	vis_2D_manager.set_gj_WeiZhi(weizhi_mat);

	mat show_mat2 = vis_2D_manager.get_show_data_gj();
	show_ptr->draw_gj_2D(show_mat2);

	//计算水平中心点在截平面上的投影点
	{
		vec v_o = { 0.0,0.0,v_p(2),0.0 };  //水平中心点
		vec A = (v_o - v_p);  //参考点指向回转中心
		vec v_A = normalise(tc_cross(A, tcZ(4)));//速度方向
		vec ans_p = normalise(v_A - dot(v_A, v_z) * v_z); //投影点
		ans_p = normalise(tc_cross(ans_p, v_z));

		double ang = tcDegree(acos(dot(tcZ(4), v_z)));
		vec v_len = { v_p(0),v_p(1),0.0 };
		double ls = norm(v_len);
		double ls2 = abs(cos(tcRadians(ang)));
		ans_p = ans_p * ls * ls2; //投影长度

		mat ls_mat = jiemian_mat;
		ls_mat.col(3) = { 0.0,0.0,0.0,1 };
		ans_p = inv(ls_mat) * ans_p;

		//增加垂线两点
		vec ans_p1 = normalise(tcRotZ(4, 90) * ans_p);
		vec ans_p2 = normalise(tcRotZ(4, -90) * ans_p);

		//画直线
		glNewList(show_ptr->list_line, GL_COMPILE);
		glBegin(GL_LINES);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2d(0.0, 0.0);
			glVertex2d(ans_p(0), ans_p(1));
			glVertex2d(0.0, 0.0);
			glVertex2d(ans_p1(0), ans_p1(1));
			glColor3f(0.0f, 1.0f, 0.0f);

			//两轴线11.26
			glColor4f(0.0f, 1.0f, 0.0f, 0.1f);
			//glVertex2d(-35.0, 0.0);
			//glVertex2d(35.0, 0.0);
			//glVertex2d(0.0, -32.0);
			//glVertex2d(0.0, 32.0);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		glEnd();
		glEndList();
	}
}

void fangzhen_2D::trans_vec5_to_mat44(vec5 cur_coor, mat44& temp)
{
	mat44 gj_sys;
	mat44 sl_sys;
	mat44 base = eye(4, 4);

	cal_gongjian_abs_mat(cur_coor, base, gj_sys);
	cal_shalun_abs_mat(cur_coor, base, sl_sys);

	cal_SL_to_GJ(gj_sys, sl_sys, temp);
}

void fangzhen_2D::cal_gongjian_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& gj_abs_sys)
{
	gj_abs_sys = tcTranslate(-in_abs_sys(0), 0.0, 0.0) * tcRotZ(4, in_abs_sys(4)) * tcRotY(4, in_abs_sys(3))
		* tcRotX(4, 90) * tcRotZ(4, 90);

	//第一条螺旋刃在下方，test 不转Z

}

void fangzhen_2D::cal_shalun_abs_mat(vec5& in_abs_sys, mat44& base_in, mat44& sl_abs_sys)
{
	base_in = tcTranslate(0.0, 0.0, 0.0) * tcRotX(4, 90);
	sl_abs_sys = tcTranslate(0.0, in_abs_sys(1), 0.0) * tcTranslate(0.0, 0.0, in_abs_sys(2)) * base_in;

}

void fangzhen_2D::cal_SL_to_GJ(mat44& gj_abs_sys, mat44& sl_abs_sys, mat44& gj_sys_sl)
{
	vec3 ABS_O_SL = sl_abs_sys.submat(0, 3, 2, 3);
	mat33 ABS_SYS_SL = sl_abs_sys.submat(0, 0, 2, 2);

	vec3 ABS_O_GJ = gj_abs_sys.submat(0, 3, 2, 3);
	mat33 ABS_SYS_GJ = gj_abs_sys.submat(0, 0, 2, 2);

	vec3  GJ_O_SL = ABS_SYS_GJ.i() * (ABS_O_SL - ABS_O_GJ);
	mat33 GJ_SYS_SL = ABS_SYS_GJ.i() * ABS_SYS_SL;




	//当前计算的砂轮相对工件的位置，是砂轮参考点(法向朝外)，加上法兰长度到端面才能计算二维-9.12
	//GJ_O_SL = GJ_O_SL + GJ_SYS_SL.col(2) * (lenth_ckd_to_outface);

	//将砂轮坐标系的回转轴，转为X轴
	gj_sys_sl.col(0) = { GJ_SYS_SL.col(2)(0), GJ_SYS_SL.col(2)(1), GJ_SYS_SL.col(2)(2),  0 };
	gj_sys_sl.col(1) = { GJ_SYS_SL.col(0)(0), GJ_SYS_SL.col(0)(1), GJ_SYS_SL.col(0)(2),  0 };
	gj_sys_sl.col(2) = { GJ_SYS_SL.col(1)(0), GJ_SYS_SL.col(1)(1), GJ_SYS_SL.col(1)(2),  0 };
	gj_sys_sl.col(3) = { GJ_O_SL(0),          GJ_O_SL(1),		    GJ_O_SL(2),	 1 };

	//加上参考点到内端面长度才能计算二维-10.14
	gj_sys_sl = gj_sys_sl * tcTranslate(lenth_ckd_to_inface, 0, 0);
}

void fangzhen_2D::set_button_reset()
{
	debug_tool_ptr->machine->reset_button = 1;
	debug_tool_ptr->machine->is_M30 = 0;
	//debug_tool_ptr->f_manager->Recover_main(theApp.pMainWnd->P_manager->fangzhen_zhu_prog_ptr->name);
	debug_tool_ptr->f_manager->Recover_main(zhu_fu_zi_prog_ptr->name);
	//debug_tool_ptr->reset_nc_prog();
	debug_tool_ptr->machine->clear_cache();
	index_ckd_out_face = 0;
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

void fangzhen_2D::set_button_run_one()
{
	debug_tool_ptr->machine->reset_button = 0;
	debug_tool_ptr->machine->play_or_pause = 1;
	debug_tool_ptr->machine->run_one = 1;
	debug_tool_ptr->machine->count_run_one++;
}

void fangzhen_2D::set_button_clear_screen()
{
	debug_tool_ptr->machine->count_clear_screen = 2;
}

void fangzhen_2D::init_sl_lib_2D(Prog_manager* in_prog_ptr)
{
	//2D仿真进入时，清空
	sl_lib_2D.clear();
	sl_lib_on_sl_num.clear();

	//for (int i = 0; i < 6; i++)
	//{
	//	int cur_sl_zu_num = in_prog_ptr->sl_zu_num[i];
	//	//一个砂轮组上挂的砂轮数量不等
	//	vector<int> sl_count_num = in_prog_ptr->sl_manager.get_a_group_all_wheel_key(cur_sl_zu_num);
	//	sl_lib_on_sl_num.push_back(sl_count_num);

	//	vector<mat> v_sl_outline;
	//	for (int j = 0; j < sl_count_num.size(); j++)
	//	{
	//		int cur_num = sl_count_num[j];
	//		mat cur_outline = in_prog_ptr->sl_manager.get_2D_wheel_outline(cur_num);

	//		v_sl_outline.push_back(cur_outline);
	//	}
	//	sl_lib_2D.push_back(v_sl_outline);
	//}

	////构造外端面长度容器
	//v_gx_lenth_ckd_to_inface = in_prog_ptr->v_2D_need_lenth;
}

bool fangzhen_2D::change_sl(int slz_num, int in_sl_pos)
{
	if (slz_num < 0 || slz_num > 5)
	{
		return false;
	}
	set_sl_outline(sl_lib_2D[slz_num][in_sl_pos]);

	//换参考点长度
	lenth_ckd_to_inface = v_gx_lenth_ckd_to_inface[index_ckd_out_face];
	index_ckd_out_face++;

	return true;
}

void fangzhen_2D::set_sl_duan_len(double fl, double hou, double r, int in_out_mo)
{
	if (in_out_mo == 0) //外侧磨
	{
		lenth_ckd_to_inface = fl + r;
	}
	else
	{
		lenth_ckd_to_inface = fl - r + hou;
	}
}


void fangzhen_2D::init(tcGLMatrixCtrl* mat_ptr, Prog_manager* in_prog_ptr)
{
	set_mat_ctrl(mat_ctrl);
	set_fangzhen_zhu(in_prog_ptr->get_zhu_prog());

	debug_tool* ls_debug_ptr = new debug_tool;
	virtual_machine* ls_machine_ptr = new virtual_machine;
	ls_debug_ptr->f_manager->data_clear();

	ls_machine_ptr->set_move_speed(1);
	ls_debug_ptr->set_machine(ls_machine_ptr);
	ls_debug_ptr->f_manager->Recover_main(in_prog_ptr->get_zhu_prog()->name);

	set_debug_tool(ls_debug_ptr);
	show_ptr->set_2D_OpenGl_show();

	init_sl_lib_2D(in_prog_ptr);
	set_renxian_of_ckd(in_prog_ptr);
	set_gj_D_and_lenth(in_prog_ptr->cur_tool_ptr->get_D(), in_prog_ptr->cur_tool_ptr->get_renlen());
}

void fangzhen_2D::set_show(double dlg_len, double dil_high, double in_xishu)
{
	double xishu_start = 0.03125;
	show_ptr->set_L_H(dlg_len, dil_high, xishu_start); //0.03125
	xishu_ce_dis = xishu_start;
}

void fangzhen_2D::set_mat_ctrl(tcGLMatrixCtrl* ptr)
{
	mat_ctrl = ptr;
	//vec3 ls_scale;
	//vec3 p;

	//cal_scale(ls_scale, p);

	//mat_ctrl->reset_view_scale(2.0 / ls_scale(0));
	//mat_ctrl->reset_view_point(p);
}

bool fangzhen_2D::set_fangzhen_zhu(fangzhen_zhu* in_ptr)
{
	zhu_fu_zi_prog_ptr = in_ptr;
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

	double pre_pianyi = trans_look_gj(7);
	//调整选择刃线点的旋转角度(取负)，使其在正右边 11.22
	trans_look_gj = { ans_n(0),ans_n(1),ans_n(2),
					ans_p(0),ans_p(1),ans_p(2), -ans_ang, pre_pianyi };
}

bool fangzhen_2D::fangzhen_process()
{
	//使用GLAD来加载OpenGL

//在此添加在消息循环前显示的内容
 //防止缩放时颜色变化

	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_CULL_FACE);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat show_mat;

	if (debug_tool_ptr->machine->is_M30)
	{
		debug_tool_ptr->machine->play_or_pause = 0;
	}


	if (debug_tool_ptr->machine->count_clear_screen > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		debug_tool_ptr->machine->count_clear_screen--; //两次才能翻面清屏成功
		return 1; //清屏时，不执行其他显示相关操作
	}

	if (debug_tool_ptr->machine->reset_button)
	{
		for (int i = 0; i < 20; i++) //12.3
		{
			show_ptr->redraw();
		}
	}
	else
	{
		if (debug_tool_ptr->machine->play_or_pause)
		{
			if (debug_tool_ptr->machine->run_one == 0)
			{
#pragma region 准备显示数据
				base_mat = eye(4, 4);
				if (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
				{
					if (debug_tool_ptr->no_next_block())
					{
						debug_tool_ptr->reset_nc_prog_now();
						nc_block new_process_block(debug_tool_ptr->f_manager->Recover_block());

						debug_tool_ptr->set_nc_prog(new_process_block);
					}
					debug_tool_ptr->run_one();

					//检查是否换砂轮，更换
					//仿真砂轮是数据，虚拟机的砂轮是砂轮的索引，
					//程序值改变虚拟机的砂轮索引
				}
				else//不空为真
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
					mat44 temp = zeros(4, 4);
					//将一个机床绝对vec5转为2d仿真的矩阵
					trans_vec5_to_mat44(cur_coor, temp);

					show_mat = vis_2D_manager.get_show_data(temp);
				}
#pragma endregion
			}
			else
			{
#pragma region 准备显示数据
				base_mat = eye(4, 4);
				if (debug_tool_ptr->machine->is_cache_empty()) //machine_ptr->is_cache_empty()
				{
					if (debug_tool_ptr->no_next_block())
					{
						debug_tool_ptr->reset_nc_prog_now();
						nc_block new_process_block(debug_tool_ptr->f_manager->Recover_block());
						debug_tool_ptr->set_nc_prog(new_process_block);
					}

					debug_tool_ptr->run_one();

					//检查是否换砂轮，更换
					//仿真砂轮是数据，虚拟机的砂轮是砂轮的索引，
					//程序值改变虚拟机的砂轮索引
				}
				else//不空为真
				{
					if (debug_tool_ptr->machine->count_run_one_pre < debug_tool_ptr->machine->count_run_one)
					{
						debug_tool_ptr->machine->count_run_one_pre = debug_tool_ptr->machine->count_run_one;

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
						mat44 temp = zeros(4, 4);
						//将一个机床绝对vec5转为2d仿真的矩阵
						trans_vec5_to_mat44(cur_coor, temp);

						show_mat = vis_2D_manager.get_show_data(temp);


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
	xs = xs * sf;
	glLoadMatrixd(ls.memptr());
	show_ptr->Calls();

#pragma endregion

	return true;
}
