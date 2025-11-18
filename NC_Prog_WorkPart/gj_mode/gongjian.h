#pragma once
#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif
#include<set>
#include "manager_h/xt_glfw_setting.h"
#include"../data_class/sy_cengji_weizhi.h"
#include"shalun.h"
#include"gongjian_stl.h"

class shalun;

//圆柱形工件，存直径 + 长度 24.3.19
class NC_Prog_WorkPart_API gongjian_col
{
public:
	double col_D;
	double col_len;

public:
	gongjian_col();
	~gongjian_col();

	void set_col_var(double D, double len);
	void get_col_tri_nor(vector<double3v>& ans_points,
		vector<double3v>& ans_normals, double acc_in);
private:
	void gen_down_point(vector<vec3>& dwon_point, vector<vec3>& dwon_nor, 
		vector<vec3>& up_point, double acc_in);

};

//回转形工件，存母线（z轴向长度 + 半径） 24.3.19
class NC_Prog_WorkPart_API gongjian_rot
{
public:
	vector<double> rot_len;
	vector<double> rot_r;
	map<double, double> outline_len_r;

public:
	gongjian_rot();	
	~gongjian_rot();
	//外形轮廓母线输入矩阵 3*n 一列一个点 （类似于砂轮外形）
	//DXF文件导出一般，x为长度，y为半径
	void set_rot_var(mat& gj_outline);
	void get_rot_tri_nor(vector<double3v>& ans_points,
		vector<double3v>& ans_normals, double acc_in);

};

class NC_Prog_WorkPart_API gongjian_init :
	virtual public gongjian_stl,
	virtual public gongjian_col,
	virtual public gongjian_rot
{
public:
	//输入的离散 显示精度
	double acc_d;

public:
	//表面点索引
	index_cells manager_cells;
	//显示开关
	bool is_show = true;

public:
	//待更新的组
	set<octree*>  groups_changed;
	set<int> groups_clear;

//public:
//	//显示列表起始号
//	int list_start_num;
//	//显示列表号---大小
//	int list_num;
	//分组大小 树到数第几层 在初始化树完成后设置
	int group_last_n;

public:
	//在表面点处画多边形的 边数 默认值12
	int draw_point_seg = 12;
	//在表面点处画多边形的 半径 默认值0.5
	double draw_point_r = 0.5;
	vec3 minxyz;
	vec3 maxxyz;

public:

	//获取工件精度
	double get_acc();

	//1.5.1计算当前组 所对应显示列表号
	int cal_list_num(octree& root, octree& group);
	//1.5.2 更新一个显示列表的内容
	//void display_fresh_a_list(octree* cur_zu, int list_index);

public:
	//1：初始化 stl工件 输入文件 离散精度
	//对工件离散模型的参数进行赋值
	void init_gj_by_stl(string file_dir, vec trans, double acc_in);
	//初始化圆柱形工件  输入 直径，长度，离散精度
	void init_gj_by_col(double D_in, double len_in, double acc_in);
	//初始化回转形工件  输入 外形轮廓，离散精度
	void init_gj_by_rot(mat& gj_outline, double acc_in);

	//12.8 增加数据的发送
	void send_init_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num);
	//显示磨削过程中离散模型的变化
	//void show_cutting();	//更新列表并显示,工件

private:
	//1.1 包含表面索引初始化
	void lisan_by_stl(const tri_meshB& mesh, vec trans, vector<double3v>& ans_points,vector<double3v>& ans_normals,int3v& P_MAX, int3v& P_MIN);
	void lisan_by_col_and_rot(vector<double3v>& in_points, vector<double3v>& in_normals, vector<double3v>& ans_points, vector<double3v>& ans_normals, int3v& P_MAX, int3v& P_MIN);

	//1.1.1 从三角网格中读取到所有顶点及法向
	void get_points_and_normals(const tri_meshB& mesh_gj, vec trans, vector<double3v>& ans_point_vec,vector<double3v>& ans_normal_vec);
	//1.1.2	离散所有 tri_mesh 的刀的三角形
	void tri_lisan_vec_triangles(const vector<double3v>& points_in,const vector<double3v>& normals_in,vector<double3v>& ans_points,vector<double3v>& ans_normals,int3v& P_MAX, int3v& P_MIN);
	//1.1.2.1 三角形按照精度加密得到一堆点 生成cell放入map
	void tri_lisan_a_triangle(double3v p1, double3v p2, double3v p3, const double3v& normal,vector<double3v>& san_p_all, vector<double3v>& res_nor);
	//1.1.2.1.1 找公共点 最长边 次长边
	void find_bp(double3v& p1, double3v& p2, double3v& p3, double3v& b_point, double3v& long_p, double3v& short_p);
	//1.1.2.1.2 边采样
	void cai_point_1(double3v bp, double3v p2, int n, vector<double3v>& vp1);
	//1.1.2.1.3 点组合成的边采样 
	void cai_point_2(double3v bp, double3v p2, double d, const double3v& normal, vector<double3v>& vp1, vector<double3v>& res_nor);
	//1.1.2.1.4	计算两点之间的采样个数
	int c_p_mun(double3v bp, double3v p2);

private:
	//1.1 包含表面索引初始化
	//void lisan_by_col(vector<double3v>& ans_points, vector<double3v>& ans_normals, int3v& P_MAX, int3v& P_MIN);


private:
	//1.2 创建阵列点盒，建立坐标位置索引 + 记录空间大小最值
	void create_cells_and_boxes(const vector<double3v>& points, const vector<double3v>& normals,int3v& P_MAX, int3v& P_MIN);
	//1.2.1	记录工件表面点的 最值点
	void find_max_min_p(int3v& P_MAX, int3v& P_MIN, int3v p);
	//1.3	初始化树
	void init_tree(const int3v& P_MAX, const int3v& P_MIN, const double d);
	//1.3.1 树的层级确定后 确定分组
	void set_group_last_n();
	//1.4 根据倒数第几层(树的底层为1) 计算分组个数 并genlist
	//void gen_list();

public:
	//1.5 初始化每个列表的内容
	//void init_list();
	//构建一个临时用于显示变换的矩阵
	mat44 construct_sys(mat33 SYS, vec3 O);
	//设置点画圆的分割边数 与 半径
	void set_show(int seg, double rad);
};

class NC_Prog_WorkPart_API gongjian_cutoff:
	virtual public gongjian_init
{
	//gongjian_init* gj_init_ptr;
public:
	gongjian_cutoff();
	//gongjian_cutoff(gongjian_init* gj_ptr);
	//2：切除
	void cut_off(shalun* sl, unsigned char color, unsigned char count_cut);
	
	void send_cut_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num);

	//将砂轮坐标系转到工件坐标系
	//void cal_SL_to_GJ(shalun* sl, vec3& GJ_O_SL, mat33& GJ_SYS_SL);

private:
	//2.1  根据工件砂轮位置检测碰撞 得到碰撞的cells
	void check_allcells_peng(shalun* sl, queue<obj_cell*>& ans_cells_peng);
	//2.1.1 搜索盒 与 砂轮包围盒 碰撞计算
	bool is_peng_box_and_sl(shalun* sl, octree* cur_box);
	//2.1.2	cell 与 砂轮包围盒 碰撞计算
	bool is_peng_cell_and_sl(shalun* sl, obj_cell* cur_cell);
	//点 + 半径 与 砂轮包围盒 碰撞计算
	bool is_peng(shalun* sl, double3v& temp_p, double R);
	//2.1.3 //轮廓碰撞计算
	bool is_peng_cell_and_ls_outline(shalun* sl, obj_cell* cur_he);
	//2.2 根据碰撞的cells 计算变形结果
	void change_point(queue<obj_cell*>& cells_peng, shalun* sl, unsigned char color, unsigned char count_cut);
	//2.2.2 计算一个面的向对面的号
	int cal_duimian_num(int face_now);
	//2.3 更新变化组所对应显示事列表的内容
	//void renew_list();
};


class NC_Prog_WorkPart_API gongjian_cutted :
	virtual public gongjian_cutoff
{
	//gongjian_init* gj_init_ptr;
//public:
//	//网格工件的显示列表号
//	GLint list_num_cutted;
	//工件离散精度
	double gj_acc;
	//平滑的阶数 范围
	int smooth_w;

public:
	//三角形网格容器  存放边界修补三角 + 没变形三角细化时放入
	vector<mesh_tri> mesh_finish_tri;
private:
	//边去重删除
	map<int3v, pair<int3v, int3v>> mesh_line;  //剩下未封闭的边
	//边去重 边的引用次数最多为2 11.15
	map<int3v, int> all_line;

	//测试 缺口边产生顺序 ???
	vector<pair<int3v, int3v>> test_line;
	//四边形去重  》》11.22 
	//set<int3v, mesh_tri> mesh_three;
	map<int3v, mesh_tri> mesh_three;

public:
	//颜色显示列表起始号
	GLint color_list_start;
	//颜色显示列表大小
	GLint color_list_size;

public:
	gongjian_cutted();
	~gongjian_cutted();
	//*************************************
	// 	   对外接口

		//初始化切除完成后的网格工件
	//gongjian_cutted(gongjian_init* gj_ptr);
	void create_face_mesh();
	//显示网格工件
	//void show_cutted_mesh();
	void send_mesh_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num);

	//3.29 根据点的颜色状态将点分组，一组对应一个list
	void send_cutted_data(vector<vector<mesh_cutted>>& show_data, vector<int>& zu_color);
	//*************************************

private:
	//1、获取所有变形的cell
	void get_all_change_cells(map<int3v, int>& all_cells, vector<double3v>& all_cells_dou3v);

	//2、平滑所有点 同一刀序一起平滑
	void smooth_all_cells(map<int3v, int>& change_cells, vector<double3v>& change_cells_new);

	//3、构建切除平滑完成后的网格  四边形网格
	void create_mesh_finish(map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new);

	//4、将四边形网格拆分成两个三角显示
	//void show_all_cells();

private:
	//2.1
	void smooth_a_cell(int3v cell_p, int change_index, map<int3v, int>& change_cells, vector<double3v>& change_cells_new);
	//2.1.1		获取当前cell 的 n 阶邻域cell
	void get_n_side_cells(int3v& cell_p, int count_cut, int smooth_size, set<int3v>& side_cell);
	//2.1.1.1	找一个cell的v方向的前  -x  （cell 上为外 顺序即：前上 前平 前下）
	bool find_cell_v_front(int3v& cur_cell, int3v& aim_cell);
	//2.1.1.2	找一个cell的v方向的后  +x 
	bool find_cell_v_back(int3v& cur_cell, int3v& aim_cell);
	//2.1.1.3	找一个cell的u  左  -y
	bool find_cell_u_left(int3v& cur_cell, int3v& aim_cell);
	//2.1.1.4	找一个cell的u  右  +y
	bool find_cell_u_right(int3v& cur_cell, int3v& aim_cell);
	//2.1.1.5	判断指定位置面是否为外
	bool is_pos_out(int pos, vector<int>& cur_out);
	//根据一个点（）的周围点，平滑出新的坐标值 
	void cal_smooth_new_cell(set<int3v>& side_cells, int3v& cell_p, int change_index, map<int3v, int>& change_cells, vector<double3v>& change_cells_new);
	//计算平滑移动的方向 
	void acl_move_nor(set<int3v>& side_cells, int3v& cell_p, vec3& move_nor);

private:
	//3.1	找cell的四边形其他cell（弃用）
	void find_cell_polygon_4(int3v& cur_p, vector<int3v>& polygons);
	//3.1.1	找一个cell的 相对当前外面的 前 （上下左右 -x 前+z 后-z）
	bool find_polygon_front(int3v& cur_p, int out_pos, int3v& front_p);
	//3.1.2	找一个cell的 相对当前外面的 左 （上下前后 -y 左-z 右+z） 
	bool find_polygon_left(int3v& cur_p, int out_pos, int3v& left_p);
	//3.1.3	找一个cell的 左前
	bool find_polygon_left_and_front(int3v& cur_p, int out_pos, int3v& left_front_p);
	//3.1	找cell的四边形 或三角形 其他cell
	void find_cell_polygon_4or3(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons);
	//处理一个cell多个外的最终转向
	void deal_cell_finish_out(vector<int>& cur_out);
	//创建一个三角面片
	void create_tri_mesh(int3v& cur_p, int3v& p1, int3v& p2, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new);
	//设置颜色列表 更新显示列表调用不同的列表号
	void set_color_list();
	//创建一个四边形网格
	void create_a_mesh(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons);

private:
	//将三边放入边容器
	void insert_line(mesh_tri& tri_temp);
	//处理不封闭的边
	void deal_mesh_line(map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new);
	//判断一个三角是否存在
	bool is_tri_mesh_eixst(mesh_tri& mesh_temp);
	//判断两个三角面片的法向是否相等
	bool is_nor_equal(mesh_tri& mesh_temp, int3v& tri_center);
	//判断一个三角 的 三边是否存在
	bool is_line_eixst(mesh_tri& temp_tri);
	//将一个四边形按照优先级分解为两个三角形
	void discolse_4_to_3(mesh_cutted& mesh_temp, char cur_color);
	//将一个三角面片放入容器
	void push_tri_to_container(double3v& p1, double3v& p2, double3v& p3, char cur_color);
	//将一个三角面片放入  检查 容器
	void push_tri_to_check(mesh_tri& tri_temp);
	//找一个cell的 前左
	void find_polygon_front_and_left(int3v& front_cell, set<int3v>& set_cells);

	void create_few_tri_mesh(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, vector<int3v>& polygons);
	//获得一个cell的真实坐标值
	void get_a_cell_real_value(int3v& cur_p, map<int3v, int>& all_change_cells, vector<double3v>& change_cells_new, double3v& cur_cell, char cur_color);

private:
	//网格细分 同刀序切
	//void mesh_sub_loop_of_cut();
	//计算cell旁边的 cell的int3v 坐标 （xyz：123，add：true）
	void cal_cell_int3v_side(int3v& aim_cell, int XYZ, bool ADD);
};


class NC_Prog_WorkPart_API gongjian:
	virtual public gongjian_cutted
{
public:
	//参考位置：相对机床的坐标系 //坐标原点 //位姿矩阵
	vec3 JC_O_GJ;
	mat33 JC_SYS_GJ;

public:
	gongjian();
	gongjian(string& file, vec trans, double acc);
	gongjian(double D, double len, double acc_d);
	gongjian(mat& gj_outline, double acc_d);

	~gongjian();

public:
	void set_position(vec3& p, mat& mat3);
	//void cutting(shalun* sl, unsigned char color, unsigned char count_cut);
	//void create_mesh();


public:
	//获取工件位置
	vec3 get_O();
	//获取工件姿态
	mat33 get_SYS();
};

