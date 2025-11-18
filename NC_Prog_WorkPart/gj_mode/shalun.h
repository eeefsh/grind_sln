#pragma once

#ifdef NC_Prog_WorkPart_EXPORTS
#define NC_Prog_WorkPart_API __declspec(dllexport)
#else
#define NC_Prog_WorkPart_API __declspec(dllimport)
#endif

#include<map>
#include"manager_h/xt_armadillo_settings.h"
#include"../send_data_API/get_send_data.h"
#include "gongjian.h"
using namespace std;

//2024.9.2 修改： 限制设置砂轮坐标系的输入统一
//将参数改为私有

class NC_Prog_WorkPart_API shalun
{
private:
	//相对机床的参考系 
	//坐标参考点	
	vec3 JC_O_SL;	
	mat33 JC_SYS_SL;	//矩阵: Z轴砂轮轴，方向朝主轴外侧
public:
	void set_JC_O_SL(vec3& in_JC_O_SL);
	//输入相对机床的参考系:  Z轴为砂轮外侧指向内侧
	void set_JC_SYS_SL(mat33& in_JC_SYS_SL); //绕自身X转180

public:
	vec3 GJ_O_SL;
	mat33 GJ_SYS_SL;
	
public:
	//砂轮的显示开关
	bool is_show;

public:
	//外形参数
	double in_length;	//砂轮内端面 参考点沿Z方向到内侧的距离
	double out_length;	//砂轮外端面 参考点沿Z方向到外侧的距离
	double cover_d;		//包围盒直径
	//砂轮外形轮廓，一个长度对应一个半径，len大于in_length、r小于over_d
	map<double, double> outline_len_r;

public:
	shalun();
	shalun(vec3 &p, mat33 &mat3);
	~shalun();

public:
	//1.初始化外形参数
	//2.申请显示列表 并放入显示内容
	//参数定义：in-内端面长度 out-外端面长度 c_d-包围盒直径
	//设置外形轮廓: 要求长度个数与半径个数相等
	void init_shape(double in, double out, double c_d, vector<double>& v_lens, vector<double>& v_rs);
	//卸载砂轮时 重置碰撞砂轮的数据
	void reset_data();

	void send_shalun_data(vector<vector<mesh_cutted>>& show_data, vector<int>& renew_list_num, vector<int>& del_list_num);

	//将砂轮坐标系转到工件坐标系
	void cal_SL_to_GJ(vec3& JC_O_GJ, mat33& JC_SYS_GJ);

	//void show(mat33& A);
private:
	//设置外形轮廓 要求长度个数与半径个数相等
	void set_outline(vector<double>& v_lens, vector<double>& v_rs);
};

class NC_Prog_WorkPart_API tanzhen_Z
{
public:
	//相对机床的参考系 
	//坐标参考点	
	vec3 JC_O_TZ;  //探Z头端上点：距离Z轴端面回转中心
	mat33 JC_SYS_TZ;
public:
	vec3 GJ_O_TZ;
	mat33 GJ_SYS_TZ;

//外形参数基础 
// X = -79.471，Y= 10.578，Z = -85.01
// H = 9.628,  len = 4.814， LEN = 22.0
public:
	//看作长方体薄片进行碰撞检测 
	double width = 0.1;		//往x正 偏置
	double length = 22.0;	//往y正 偏置
	double height = 9.628;	//往Z负 偏置
	//vec3 up_lien;	//相对上点 Y轴正 偏置
	//vec3 mid_face;	//相对上点 Y轴正 + Z轴负 偏置
	//vec3 dwon_point;//相对上点 Z轴负 偏置
	//vec3 dwon_lien; //相对上点 Y轴正 + Z轴负 偏置

	//将用于探测碰撞的点，集合起来便于计算
	//vector<vec3> cal_peng_points;

public:
	tanzhen_Z();
	~tanzhen_Z();

public:
	//根据砂轮的绝对位置(mat44) 计算探针的位置数据
	void cal_self_pos(mat44& mat_z);
	//检查是否与工件发生碰撞，结果不精确，计算到倒数第二层
	//bool check_peng_gj(gongjian* gj_ptr);  //碰撞实现归属于哪个类 ???

private:

};






