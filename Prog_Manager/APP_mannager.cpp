#include "APP_mannager.h"

APP_manager::APP_manager()
{
	//ptr_storage = new Storage_manager;

	sl_manager.Init_Dir(
		storage_lib.file_dir_sl_sy,
		storage_lib.file_dir_sl,
		storage_lib.file_dir_slz_sy,
		storage_lib.file_dir_slz
	);

	//obj_tool_lib.ptr_storage = ptr_storage;

	//obj_JC_sl_lib.ptr_storage = ptr_storage;

	cur_tool_ptr = nullptr;
}

APP_manager::~APP_manager()
{
	//delete ptr_storage;

	if (cur_tool_ptr != nullptr)
	{
		delete cur_tool_ptr;
	}
}

string APP_manager::get_cur_tool_name()
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

inline void APP_manager::add_a_tool(int dao_type, string in_name)
{
	new_a_tool(dao_type);
	int ans_pos = obj_tool_lib.add_a_row_data(dao_type, in_name);
	cur_tool_ptr->pos = ans_pos;
}

bool APP_manager::open_a_tool(int n_order)
{
	//1、根据选择刀具的位置(不显示存储位置)，索引到存储的位置
	int ls_pos = obj_tool_lib.get_tool_pos(n_order);

	//2、在刀具对象文件中读出数据
	tool_obj_data ls_row_data;
	
	storage_lib.read_a_row_data(0, ls_pos, (char*)&ls_row_data, sizeof(ls_row_data));
	
	//2.1 当前刀的两个容器恢复

	//名称位置与刀具对象位置相同
	if (cur_tool_ptr != nullptr)
	{
		//清空之前打开的数据所new出的到
		delete cur_tool_ptr;
	}

	//3、恢复出刀具及参数,挂到刀具指针上
	new_a_tool(ls_row_data.type); 
	cur_tool_ptr->pos = ls_pos;

	//铣刀基类里没有对应的公共参数
	//使用刀具的load加载完数据，不传位置，提前赋值5.28
	cur_tool_ptr->load();

	return true;
}

bool APP_manager::new_a_tool(int dao_type)
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

void APP_manager::set_Prog_NC_move(vec3 in_move)
{
	Prog_NC_move = in_move;
}

void APP_manager::gen_tance_prog_of_first(double dis_safe_in, double dis_start_in, double dis_more_in)
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

void APP_manager::gen_tance_prog_of_sel_gx(double dis_safe_in, double dis_start_in, double dis_more_in)
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

void APP_manager::get_a_gx_tance_input(Miller_GX_Base* in_gx_ptr, DL& in_ans_DL, vector<vec3>& ans_v_points, vector<vec3>& ans_v_nors, vector<double>& ans_v_A, vector<double>& ans_v_C)
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

void APP_manager::cal_G_p_tance_AC(vec3 ans_point, mat33 ans_sys, int in_type, double& ans_A, double& ans_C)
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


void APP_manager::gen_NC_prog()
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
