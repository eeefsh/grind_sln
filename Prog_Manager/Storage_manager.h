#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include<string>
#include <set>
#include <vector>
#include"manager_h/xt_armadillo_settings.h"
#include"manager_h/MA_010101_gy_dll_time_updata.h"
#include"manager_h/MA_010101_Read_dxf_manager.h"

#include"TooL_canshu_2.h"
#include"pch.h"
using namespace std;
#include <filesystem>


class CanShu_Bian;
class CanShu_Bian_v3;
class CanShu_Bian_v4;
class obj_list_data;
class tool_obj_data;
class CanShu_HouJiao;
class CanShu_LuoXuan;
class CanShu_FenDu;
class CanShu_QianJiao;
class CanShu_HDM_MoXue_FangFa;
class CanShu_QDM_MoXue_FangFa;
class save_lib;
class CanShu_XingXian;

class Cal_XingXian;
class Cal_HouJiao;
class Cal_LouXuan;
class Cal_FenDu;
class Point_by_5axis;





class Prog_Manager_API Storage_base
{
public:
	int head_size = 2000;
	const int NAME_BUFFER_SIZE = 100;
	char name_buffer[100] = { 0 }; //用于转换字符串 7.1


public:
	//往指定file文件，写入指定长度地址的内容  增加操作调用，只能是名称文件
	virtual int add_a_row_data(string file, const char* dir, int lenth);
	//往指定file文件，读取行数index的内容到dir
	bool read_a_row_data(string file, int index, char* dir, int lenth);
	//往指定file文件，更新一行数据
	void edit_a_row_data(string file, int index, char* dir, int lenth);
	//删除一条数据
	void delete_a_row_data(string file, int index);

public:
	string folder = "gongyi_data\\";
	string folder_dxf = "dxf_copy\\";
	Storage_base();
	~Storage_base();

	void str_to_buffer(string& str);
	void buffer_to_str(string& str);
};

//刀具表：用于存储刀具及其刀具整体参数对象
class Prog_Manager_API Storage_tool_list
	:virtual public Storage_base
{

#pragma region 文件名称变量，保存路径=执行项目
public:
	string file_dir_tool_name;	//8	//刀具名称存储文件
	string file_dir_tool_obj;  //0	//刀具对象存储文件路径			 每把刀有一个key pos
	string file_dir_tool_data; //1	//刀具数据-公共参数存储文件路径	 一把刀的所有公共参数存成一行
	string file_dir_tool_time;	//16 刀具修改时间
	string file_dir_tool_type;	//17 刀具类型
	string file_dir_tool_list_xx; //40//刀具的五个表
	string file_dir_tool_list_hj; //41
	string file_dir_tool_list_lx; //42
	string file_dir_tool_list_fd; //43
	string file_dir_tool_list_gx; //44
	string file_dir_tool_write;//2	//管理刀具存储位置的文件		 空位号

	string file_dir_tool_count;	//10  //刀具计数文件
#pragma endregion

public:
	Storage_tool_list();
	~Storage_tool_list();

#pragma region 刀具操作
public:
	//增加一把刀，返回存储位置，刀相关存储文件都填值
	int add_a_tool(int type, string name);

public:
	bool del_a_tool(int pos);

public:
	void set_tool_canshu(int pos, char* dir, int lenth);
	void set_tool_obj_canshu(int pos, tool_obj_data& ans_data);
	void set_tool_name(int pos, string name);
	void set_tool_time(int pos, time_updata& ans_time);
	//更新刀具计数--真为加，假为减
	bool add_tool_count(bool add);
private: //用刀的list_gx调整顺序 11.17
	bool move_up_a_gx(int tool_pos, int cur_order, int up_order);
	bool move_down_a_gx(int tool_pos, int cur_order, int down_order);

public:
	void get_tool_canshu(int pos, char* dir, int lenth);
	void get_tool_obj_canshu(int pos, tool_obj_data& ans_data);
	string get_tool_name(int pos);
	void get_tool_time(int pos, time_updata& ans_time);
	int get_tool_type(int pos);
	int get_tool_count();

public:
	//获取当前被删除后刀具对象空位
	bool get_empty_pos(set<int>& del_pos);  //set便于查找是否存在
	void read_type(vector<int>& ans_v_type);
#pragma endregion

#pragma region list 增删改查
//增
public:
	void add_a_xx_to_tool(int tool_pos, int obj_pos_abs);
	void add_a_hj_to_tool(int tool_pos, int obj_pos_abs);
	void add_a_lx_to_tool(int tool_pos, int obj_pos_abs);
	void add_a_fd_to_tool(int tool_pos, int obj_pos_abs);
	void add_a_gx_to_tool(int tool_pos, int obj_pos_abs);
	
//删
public:
	void del_a_xx_from_tool(int tool_pos, int sel_order);
	void del_a_hj_from_tool(int tool_pos, int sel_order);
	void del_a_lx_from_tool(int tool_pos, int sel_order);
	void del_a_fd_from_tool(int tool_pos, int sel_order);
	void del_a_gx_from_tool(int tool_pos, int sel_order);

//改
public:
	void set_tool_xx_list(int pos, obj_list_data& ans_list);
	void set_tool_hj_list(int pos, obj_list_data& ans_list);
	void set_tool_lx_list(int pos, obj_list_data& ans_list);
	void set_tool_fd_list(int pos, obj_list_data& ans_list);
	void set_tool_gx_list(int pos, obj_list_data& ans_list);

//查
public:
	void get_tool_xx_list(int pos, obj_list_data& ans_list);
	void get_tool_hj_list(int pos, obj_list_data& ans_list);
	void get_tool_lx_list(int pos, obj_list_data& ans_list);
	void get_tool_fd_list(int pos, obj_list_data& ans_list);
	void get_tool_gx_list(int pos, obj_list_data& ans_list);

private:
	//将 dir起始，长lenth的内存段数据 加入到pos对应刀下面的 file 对应表中作为一个成员
	void add_a_obj_to_tool(string file, int tool_pos, int obj_pos);
#pragma endregion

};

class Prog_Manager_API Storage_gx_fun
	:virtual public Storage_base
{
#pragma region 文件名
public:
	string file_dir_gx_name;	//9	//工序名称存储文件
	string file_dir_gx_base_canshu;	   //4	//工序对象存储文件路径			 
	string file_dir_gx_data;   //5	//工序参数存储文件路径	
	
	string file_dir_gx_range; //30	范围
	string file_dir_gx_sample; //31	 采样
	string file_dir_gx_jintuidao; //32	进退刀
	string file_dir_gx_bianhuan; //33	变换
	string file_dir_gx_xunhuan; //34	循环
	string file_dir_gx_zhenlie; //35	阵列
	string file_dir_gx_fangfa; //36		方法 前后可以合 指定最大长度 6.13
	string file_dir_gx_sudu; //37		速度
	string file_dir_gx_A_before; //29

	string file_dir_gx_juti_ff;  //38 具体方法
#pragma endregion
public:
	Storage_gx_fun();
	~Storage_gx_fun();

//public:
//	//往指定file文件，写入指定长度地址的内容  增加操作调用，只能是名称文件
//	virtual int add_a_row_data(string file, const char* dir, int lenth);

#pragma region 工序操作
public:
	int add_a_gx(int type, string name);
	//删除刀对应工序列表文件的order数据
	bool del_a_gx(int in_pos);


	string get_gx_name(int pos);
	string get_gx_type(int pos);
	void get_gx_obj_canshu(int pos, char* dir, int lenth);
	void get_gx_canshu(int pos, char* dir, int lenth);
	int get_gx_sl_id(int pos);

	void get_gx_range(int pos, char* dir, int lenth);
	void get_gx_sample(int pos, char* dir, int lenth);
	void get_gx_jintuidao(int pos, char* dir, int lenth);
	void get_gx_bianhuan(int pos, char* dir, int lenth);
	void get_gx_xunhuan(int pos, char* dir, int lenth);
	void get_gx_zhenlie(int pos, char* dir, int lenth);
	void get_gx_hdm_fangfa(int pos, CanShu_HDM_MoXue_FangFa& in_ff);
	//void get_gx_qdm_fangfa(int pos, CanShu_QDM_MoXue_FangFa& in_ff);
	void get_gx_qdm_fangfa(int pos, char* dir, int lenth);
	void get_gx_sudu(int pos, char* dir, int lenth);
	void get_gx_A_before(int pos, char* dir, int lenth);

	string get_gx_jingeilv(int pos);

public:
	void set_gx_name(int pos, string name);
	void set_gx_obj_canshu(int pos, char* dir, int lenth);
	void set_gx_canshu(int pos, char* dir, int lenth);
	//void set_gx_type(int pos, char* dir, int lenth);
	void set_gx_sl_id(int pos, int sl_id);

	void set_gx_range(int pos, char* dir, int lenth);
	void set_gx_sample(int pos, char* dir, int lenth);
	void set_gx_jintuidao(int pos, char* dir, int lenth);
	void set_gx_bianhuan(int pos, char* dir, int lenth);
	void set_gx_xunhuan(int pos, char* dir, int lenth);
	void set_gx_zhenlie(int pos, char* dir, int lenth);
	void set_gx_hdm_fangfa(int pos, CanShu_HDM_MoXue_FangFa& in_ff);
	//void set_gx_qdm_fangfa(int pos, CanShu_QDM_MoXue_FangFa& in_ff);
	void set_gx_qdm_fangfa(int pos, char* dir, int lenth);
	void set_gx_sudu(int pos, char* dir, int lenth);
	void set_gx_A_before(int pos, char* dir, int lenth);

	void set_gx_sl_pos_in_JC(int pos, int sl_pos_in_JC);

	int get_gx_sl_in_or_out(int pos); //0-内，1-外

	//void get_gx_fangfa(int pos, char* dir, int lenth);
	//void set_gx_fangfa(int pos, char* dir, int lenth);
	//存取参数不对，有变参的应转换数据 7.25


#pragma endregion
};

//用于存储：型线、后角、分度、螺旋等组合参数对象
class Prog_Manager_API Storage_obj_list
	:virtual public Storage_base
{
#pragma region 文件名
public:
	string file_dir_xx_name;  //21 型线名称文件 >> 型线目录文件 25.4.3
	string file_dir_xx_newdir;  //21 型线新路径文件 
	string file_dir_xx_canshu; //26	型线参数

	string file_dir_xx_count;	//型线计数文件
public:
	string file_dir_hj_name;
	string file_dir_hj_canshu;

	string file_dir_lx_name;
	string file_dir_lx_canshu;

	string file_dir_fd_name;
	string file_dir_fd_canshu;

	string file_dir_qj_name;
	string file_dir_qj_canshu;

#pragma endregion

public:
	Storage_obj_list();
	~Storage_obj_list();

//public:
//	//往指定file文件，写入指定长度地址的内容  增加操作调用，只能是名称文件
//	int add_a_row_data(string file, const char* dir, int lenth);

	
#pragma region 列表操作
public:
	int add_a_xx_(string name, string file_dir, CanShu_XingXian& canshu_xx); //改为引用传递 25.11.5 zy
	int add_a_hj(CanShu_HouJiao& in_can);
	int add_a_lx(CanShu_LuoXuan& in_can);
	int add_a_fd(CanShu_FenDu& in_can);

	int edit_a_xx_(int xx_pos, string name,string dxf_file_dir, CanShu_XingXian in_can);
	int edit_a_hj_(int xx_pos, CanShu_HouJiao in_can);
	int edit_a_lx_(int xx_pos, CanShu_LuoXuan in_can);
	int edit_a_fd_(int xx_pos, CanShu_FenDu in_can);

	bool del_a_xx_(int pos);
	bool del_a_hj_(int pos);
	bool del_a_fd_(int pos);
	bool del_a_lx_(int pos);

public:
	//需要输入一个主键（name)文件  获得已经用过的index数量，最大index是数量-1；
	int get_index_count(string dir)
	{
		//1 打开文件
		fstream file1;

		file1.open(dir, std::ios::in | std::ios::out | std::ios::binary);

		if (!file1.is_open())
		{
			throw - 1;
		}

		//2 读取文件头信息
		file1.seekg(0);
		int len_data = -1;
		file1.read((char*)&len_data, sizeof(len_data));
		int index_count = -1;
		file1.read((char*)&index_count, sizeof(index_count));  //程序再次运行，打开已有文件，数据被复原 7.15 ???
		int empty_count = -1;
		file1.read((char*)&empty_count, sizeof(empty_count));
		file1.clear();
		file1.close();

		return index_count;
	}

public:
	string get_xx_name(int pos);
	void set_xx_name(int pos,string name);

	string get_xx_newdir(int pos);
	//void set_xx_newdir(int pos, char* dir, int lenth);
	
	void get_dxf_xx_data(int pos,double in_acc, mat& ans_data);
private:
	//转为点 + 切向 7.25
	void ans_vv_to_mat(vector<vec>& points, mat& Data_Of_Points);

public:
	void get_a_xx_canshu(int pos, CanShu_XingXian& ans_can);
	void get_a_hj_canshu(int pos, CanShu_HouJiao& ans_can);
	void get_a_lx_canshu(int pos, CanShu_LuoXuan& ans_can);
	void get_a_fd_canshu(int pos, CanShu_FenDu& ans_can);
	void get_a_qj_canshu(int pos, CanShu_QianJiao& ans_can);

public:
	Cal_XingXian* new_a_xingxian_from_storage(int pos);
	Cal_HouJiao* new_a_houjiao_from_storage(int pos);
	Cal_LouXuan* new_a_luoxuan_from_storage(int pos);
	Cal_FenDu* new_a_fendu_from_storage(int pos);



private:
	//int find_write_pos(string file);

public:
	//更新型线计数--真为加，假为减
	bool add_xingxian_count(bool add);
	int get_xingxian_count();

	//重命名dxf文件并拷贝到指定文件夹
	void renameAndCopyFile(const string& sourcePath, const string& file_name, const string& targetDirectory);
public:
#pragma endregion


};

//存储管理类，作为刀具工序的工具，将数据读写到对应文件中
class Prog_Manager_API Storage_manager
	:virtual public Storage_tool_list,
	virtual public Storage_gx_fun,
	virtual public Storage_obj_list
{
	//文件保存路径
#pragma region 文件名称变量，保存路径=执行项目
public:
	string file_dir_sl;			//11  //砂轮
	string file_dir_slz;		//12  //砂轮组
	string file_dir_dxf;		//13  //砂轮dxf 
	string file_dir_sl_sy;		//14  //砂轮索引
	string file_dir_slz_sy;		//15  //砂轮组索引

public:
	string file_dir_gx_miller_morenzhi;   //7	//工序默认磨削参数值存储文件，修改后更新    
	string file_dir_w_c2g; //25	AC偏心距
	string file_dir_mo_gj_trans;	//18 磨削加工位姿    不用
	string file_dir_sl_lib;	//19 机床砂轮库num      //初始化需要指定个数 25.6.10

public:
	string file_dir_mat_2n; //50
	string file_dir_mat_3n; //51
	string file_dir_mat_4n; //52

#pragma endregion

	//如何判别数据往哪个文件写 -输入 标志 int
	//每个文件有指定 每行最大长度
	//删除时，产生空行
	//增加时优先进入空行
public:
	
#pragma region 其他文件操作
		double get_tool_w_c2g(int pos);
		void set_tool_w_c2g(int pos, double w_c2g);

		void get_mo_gj_trans(int pos, char* dir, int lenth);
		void set_mo_gj_trans(int pos, char* dir, int lenth);
		//数组
		void get_jc_sl_lib(vector<int>& v_jc_sl);
		//void set_jc_sl_lib(int pos, char* dir, int lenth);

		//根据砂轮id 获取在机床库中的位置 8.8
		int get_sl_pos_in_JC(int sl_id);


		void get_2n_mat(int pos, mat& in_mat);
		int set_2n_mat(mat& in_mat);
		void get_3n_mat(int pos, mat& in_mat);
		int set_3n_mat(mat& in_mat);
		void get_4n_mat(int pos, mat& in_mat);
		int set_4n_mat(mat& in_mat);

		//

#pragma endregion

public:
	//刀具程序库，保留，从文件读取前端显示所需数据 7.4
	//void display_tool_list(vector<string>);

public:
	int add_xingxian(string name, string file_dir, CanShu_XingXian canshu_obj, int tool);
	int add_houjiao(CanShu_HouJiao canshu_obj, int tool);
	int add_fendu(CanShu_FenDu canshu_obj, int tool);
	int add_luoxuan(CanShu_LuoXuan canshu_obj, int tool);

	bool del_xingxian(int obj_pos_in_tool,int cur_tool);


public:
	//构造：指定所有文件的名字、将文件的数据大小在此设置
	Storage_manager(); //追加app方式打开文件，默认定位到末尾seekg不起作用，在增加刀具时读数清空重写 7.12 mark
	~Storage_manager();

};

class Prog_Manager_API save_lib
{
public:
	static Storage_manager storage_lib;

	static int error_message_global;
	string get_error_message_txt();
public:
	save_lib();
	~save_lib();


public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(a);  // 直接序列化 Armadillo 矩阵
	//}

public:
	virtual int save(int pos);
	virtual void load(int pos);
};


#pragma pack(push, 8)

class Prog_Manager_API tool_obj_data
{
public:
	int type;
	int name;
	//time_updata time; 7.15
public:
	double delta_dis_ren;
	double Sample_lenth;
	double Sample_angle;

public:
	double gx_p_X;
	double gx_p_Y;
	double gx_p_Z;
	double gx_p_A;
	double gx_p_C;
public:
	double sl_p_X;
	double sl_p_Y;
	double sl_p_Z;
	double sl_p_A;
	double sl_p_C;
public:
	double cx_p_X;
	double cx_p_Y;
	double cx_p_Z;
	double cx_p_A;
	double cx_p_C;
public:
	void set_safe_p(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p);
	void get_safe_p(Point_by_5axis& gx_p, Point_by_5axis& sl_p, Point_by_5axis& cx_p);

public:
	int sel_gx[100]; //选择的工序记录 25.10.13

public:
	//刀的位置已经对应相关列表位置，不需要，目前没用上（可以删除）7.18
	//int xx_list_pos;
	//int hj_list_pos;
	//int lx_list_pos;
	//int fd_list_pos;
	//int gx_list_pos;
public:
	tool_obj_data();
	~tool_obj_data();
};

class Prog_Manager_API gx_base_canshu
{
public:
	int type_gx;

	int shalun_id;
	int sl_pos_in_JC; //选择砂轮是赋值 6.20
	int sl_pos_in_slz;
	int sel_fd_id;

	int sel_A_before_ren[6]; //选择的刃 //可以删除 25.11.14

public:
	gx_base_canshu();
	~gx_base_canshu();

public:


private:

};

//也属于工序参数类 
class Prog_Manager_API gx_cx_kaicao_can_data
{
public:
	int pos_ang_qian;

	int lx_pos;	//0等比芯厚、1变比芯厚
	double percent_start;//起始芯厚比（半径） 
	double percent_end;
	//double angle_qiexue;

	int selected_ren[6];
public:
	gx_cx_kaicao_can_data();
	~gx_cx_kaicao_can_data();



};

class Prog_Manager_API gx_dcc_qiu_can_data
{
public:
	int pos_b_qianjiao_n;

	double dis_to_center;	//到中心距离 
	double dis_end_extend;	//结束延长距离

	//芯厚线
	double high_up_o;	  //芯厚圆心上偏高度
	double ang_up;	      //顶部角度--与刀轴线在xy平面的夹角
	double percent_r;		//起始处半径比值
	double ang_down;	  //柱面出线角度与x轴夹角

	//double angle_qiexue;	//切削角度
	double ang_hen_tui;	//横向退刀
	double dis_hen_tui;	//横向退刀

	int selected_ren[6];

public:
	gx_dcc_qiu_can_data();
	~gx_dcc_qiu_can_data();
};

//五种表存储数据
//id 是针对某一对象 在第一次产生时，外部存储的show位置。后续不变。
//由于该对象的show位置后续会发生变化，因此，id2show和show2id都会发生变化。
class Prog_Manager_API obj_list_data
{
public:
	int xx_count;//有效的元素个数
	int obj_pos[100];//在外存中的主键：存储位置
	int empty_count;//obj_pos中空置位置的数量
	int empty_pos[100];//obj_pos中空置的位置

	int obj_index_show_queue[100];//按显示顺序排列的obj_pos;
	int id_to_show_index[100];//show_queue_index 补偿值 100位置输入id 
	int show_index_to_id[100];//100位置输入show_index
	int empty_id[100];
	int empty_id_count;

public:
	obj_list_data();
	~obj_list_data();

	//id 需要保持何obj_pos对应关系不变  
public:
	int get_show_index_by_id(int id);
	int get_id_by_show_index(int show_index);
	int get_obj_pos_by_id(int id);
	int get_obj_pos_by_show_index(int show_index);

	bool add_an_obj(int obj_pos_in);
	bool del_an_obj(int sel_order);//相对坐标
	bool swap_order(int queue_index1, int queue_index2);


	int get_sto_index(int show_index);
	int where_in_show_queue(int abs_pos);
	
};

//型线就是型线
//分度就是分度
//芯厚就是芯厚

class Prog_Manager_API lx_canshu_data
{
public:
	int save_obj_hjbc;
	int save_B_daocheng;
	int save_B_luoxuan;

public:
	int xingxian_pos;
	int fendu_pos;

	int type_cao; //0-直槽、1-斜槽、2-螺旋槽
public:
	//	类型选择：
	int type_zhi; //0-前角、1-偏心距
	double zhi_ang_qian;
	double zhi_pianxin;
	double ang_xie; //斜角=倾角
	double R_zhi_or_xie;

	int type_xie; //0-前角、1-偏心距

	double xie_ang_qian;
	double xie_pianxin;

	int type_luo; //0-等导程、1-等螺旋角、2-变导程、3-变螺旋角

	double D_daocheng;	//导程
	double D_ang_luo;	//螺旋角
	double ang_r;

public:
	lx_canshu_data();
	~lx_canshu_data();
};

class Prog_Manager_API qj_canshu_data
{
public:
	int save_b_qianjiao_n;
	int save_b_qianjiao_r;

	int luoxuan_pos;

	int type; //0-法向，1-径向
public:
	qj_canshu_data();
	~qj_canshu_data();
};

class Prog_Manager_API hj_canshu_data
{
public:
	int save_B_ang_n_1;
	int	save_B_ang_n_2;
	int	save_B_ang_n_3;
	int	save_B_ang_a_r_1;
	int	save_B_ang_a_r_2;
	int	save_B_ang_a_r_3;

	int xingxian_pos;

	int type; //0-法向，1-径向
public:
	double D_ang_n_1;
	double D_wid_n_1;
	bool is_bian_n_1;
	double D_ang_n_2;
	double D_wid_n_2;
	bool is_bian_n_2;
	double D_ang_n_3;
	double D_wid_n_3;
	bool is_bian_n_3;

	double D_ang_a_1;
	double D_ang_r_1;
	double D_wid_a_1;
	bool is_bian_a_1;
	double D_ang_a_2;
	double D_ang_r_2;
	double D_wid_a_2;
	bool is_bian_a_2;
	double D_ang_a_3;
	double D_ang_r_3;
	double D_wid_a_3;
	bool is_bian_a_3;

public:
	hj_canshu_data();
	~hj_canshu_data();

};

class Prog_Manager_API mo_hdm_ff_canshu_data
{
public:
	int pos_qx_wy;
public:
	int in_or_out;
public:
	int type;
	mo_hdm_ff_canshu_data();
	~mo_hdm_ff_canshu_data();
};

//磨削方法的具体方法，三种
class Prog_Manager_API fangfa_xx_wy_data
{
public:
	int pos_xx_bian;
	int pos_wy_bian;
public:
	double xx;
	double wy;
	bool xx_isbian;
	bool wy_isbian;

	fangfa_xx_wy_data();
	~fangfa_xx_wy_data();
};

class Prog_Manager_API FZ3D_gj_trans_data
{
public:
	double x_move;
	double y_move;
	double z_move;

public:
	FZ3D_gj_trans_data(vec gj_trans);

public:
	FZ3D_gj_trans_data();
	~FZ3D_gj_trans_data();

private:

};

class Prog_Manager_API sl_zu_num_data
{
public:
	int sl_zu_1_num;
	int sl_zu_2_num;
	int sl_zu_3_num;
	int sl_zu_4_num;
	int sl_zu_5_num;
	int sl_zu_6_num;

public:
	sl_zu_num_data(vector<int>& in_sl_zu);

public:
	sl_zu_num_data();
	~sl_zu_num_data();

private:

};

class Prog_Manager_API xingxian_name_data
{
public:
	int type; //当前文件状态，-1被删除，0未使用，1有刀使用
	//string file_name; //文件名
	char name_buffer[100] = { 0 };
public:
	xingxian_name_data();
	~xingxian_name_data();

private:

};

class Prog_Manager_API xingxian_catalog
{
public:
	int type;//当前文件状态，-1被删除，0未使用，1有刀使用
	char name_buffer[100] = { 0 };
	char dir_buffer[100] = { 0 };
public:
	xingxian_catalog();
	~xingxian_catalog();
};

#pragma pack(pop) 