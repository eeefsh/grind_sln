#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include "TooL_canshu_2.h"
#include"QuMian_Grovving.h"



class Tool_Base;
class Miller_GX_Base;

//该文件包含刀具类的 几何元素的类定义
class Cal_FenDu;
class Cal_LouXuan;
class Cal_QDM;
class Cal_XinHouMian;
class Cal_HouJiao;
class Cal_hdm_RX;
class Cal_HDM;


//参考坐标系：
//X轴（刀具X轴）：	由刀尖指向刀柄
//Y轴（刀具Y轴）：	由中心指向0相位参考点
//Z轴（刀具Z轴）：	X轴×Y轴

class Prog_Manager_API Cal_XingXian
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_XingXian& in_data);

	//2 基本数据结构
public:
	CanShu_XingXian data_base;

	//3 初始化结构
public:
	void init_data(); //需要通过dxf存储位置加载，将存储管理类定义为全局 ??? 4.24
	//line 为一列一个3坐标点的多段线 必须很密
	void init_data(mat line);

	void cal_son_last_state();

	//4 主数据结构
public:
	int pos;
	Tool_Base* ptr_tool;
	//计算标志位 7.21
	bool is_lastest = 0;

	//型线：
	//直角坐标点：	参考坐标系下的坐标
	//	X坐标：	X坐标
	//	Y坐标：	Y坐标
	//	Z坐标：	Z坐标 = 0
	//柱坐标系：
	//	X轴：	相位0截形的切向，从刀尖指向刀柄
	//	Y轴：	线法向
	//	Z轴：	x* y
	//	曲线长度坐标：	型线的长度坐标--毫米5.29（可以不等距）
	//13 * n
	mat Data_Of_Points;

	//关联情况
	vector<Cal_LouXuan*> v_GL_LX;
	vector<Cal_HouJiao*> v_GL_HJ;

public:
	void add_guanxi_GL_LX(Cal_LouXuan* p);
	void add_guanxi_GL_HJ(Cal_HouJiao* p);
	void del_guanxi_GL_LX(Cal_LouXuan* p);
	void del_guanxi_GL_HJ(Cal_HouJiao* p);
	int guanxi_exist(Cal_HouJiao* p);
	int guanxi_exist(Cal_LouXuan* p);

	bool is_del_ok();

	void speak_father_del_guanxi();
	void init_guanxi();



#pragma region MyRegion
	//5 结果计算接口
public:
	//返回点的数量
	int n_P();
	//返回刃线的型线长度
	double Lenth();
	//返回第i个点的点坐标，3阶
	vec BG_P(int i);
	//返回所有的点坐标，3阶
	mat BG_P();
	////返回第i个点处的切向量，3阶
	vec BG_T(int i);
	mat BG_T();
	//返回第i个点处的法向量，3阶
	vec BG_N(int i);
	//返回第i个点处的Z向量，3阶
	vec BG_Z(int i);
	//返回第i个点处的柱坐标系，3阶
	mat33 BG_zSYS(int i);
	//返回第i个点处的长度坐标
	double Lenth_At_Point(int i);
	//返回最近的index 及X坐标值  vec2
	vec get_P_by_x(double in_x);
#pragma endregion
public:
	Cal_XingXian();
	~Cal_XingXian();
	Cal_XingXian(Tool_Base* in_ptr, CanShu_XingXian& in_data);
public:


private:
	void gen_xx_of_zhuimian();

	void gen_xx_of_qiutou();

	void gen_xx_of_pingdi();

	void gen_xx_of_yuanjiao();
//提供不同立铣刀工序对应需要的型线生成接口5.14
public:
	void Range(double in_start, double in_end);
	void Sample(double in_len, double in_ang);
public:
	int save(int pos);
	void load(int pos);


};

class Prog_Manager_API Cal_HouJiao
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_HouJiao& in_data);

	//2 基本数据结构
public:
	CanShu_HouJiao data_base;

	//3 初始化结构
public:
	void init_data();
	void init_guanxi();
	void cal_son_last_state();

	//4 主数据结构
public:
	int pos;
	Tool_Base* ptr_tool;


	bool is_lastest = 0;
	//123后角的类型 
	vec type;
	//一列一个点
	//1后角径向后角值 或法后角值
	//1后角轴向后角值
	//1后角后刀面宽度
	//2后角径向后角值 或法后角值
	//2后角轴向后角值
	//2后角后刀面宽度
	//3后角径向后角值 或法后角值
	//3后角轴向后角值
	//3后角后刀面宽度
	//曲线长度坐标：
	//10*n
	mat Data_Of_Points;

	//关联情况
	Cal_XingXian* ptr_xx;
	vector<Miller_GX_Base*> v_GL_GX;

public:
	void add_guanxi_GL_GX(Miller_GX_Base* p);
	void del_guanxi_GL_GX(Miller_GX_Base* p);
	int guanxi_exist(Miller_GX_Base* p);

	bool is_del_ok();

public:
	void speak_father_del_guanxi();
	int del_self();

#pragma region MyRegion
	//5 结果计算接口
public:
	//返回第i个点的第1-径向or法向后角值 
	double HJ1_r_or_n(int i);
	//返回第i个点的第1 -轴向后角值 
	double HJ1_a(int i);
	//返回第i个点的第1后角-宽度值 
	double HJ1_w(int i);
	//返回第i个点的第2-径向or法向后角值 
	double HJ2_r_or_n(int i);
	//返回第i个点的第2 -轴向后角值 
	double HJ2_a(int i);
	//返回第i个点的第2后角-宽度值 
	double HJ2_w(int i);
	//返回第i个点的第3-径向or法向后角值 
	double HJ3_r_or_n(int i);
	//返回第i个点的第3 -轴向后角值 
	double HJ3_a(int i);
	//返回第i个点的第3后角-宽度值 
	double HJ3_w(int i);
	//返回第i个点的长度坐标
	double Lenth_At_Point(int i);

#pragma endregion
public:
	Cal_HouJiao();
	~Cal_HouJiao();
	Cal_HouJiao(Tool_Base* in_ptr, CanShu_HouJiao& in_data);


public:
	void sel_a_xx_id(int in_id);
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API Cal_FenDu
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_FenDu& in_data);

	//2 基本数据结构
public:
	CanShu_FenDu data_base;

	//3 初始化结构
public:
	void init_data();
	void init_guanxi();
	void add_son(Cal_LouXuan* in_ptr);
	void cal_son_last_state();
	//4 主数据结构
public:
	int count;
	vector<double> v_fendu;

	int pos;
	Tool_Base* ptr_tool;

	bool is_lastest = 0;

	//关联情况
	vector<Cal_LouXuan*> v_GL_LX;

public:
	void add_guanxi_GL_LX(Cal_LouXuan* p);
	void del_guanxi_GL_LX(Cal_LouXuan* p);

	int guanxi_exist(Cal_LouXuan* p);
	int del_self();
	bool is_del_ok();


	//5 结果计算接口
public:
	//返回分度的数量
	int Count();
	//返回第i个分度的角度
	double Angle(int i);

	void speak_father_del_guanxi();

	//6 其他
public:
	Cal_FenDu();
	~Cal_FenDu();
	Cal_FenDu(Tool_Base* in_ptr, CanShu_FenDu& in_data);



public:
	int save(int pos);
	void load(int pos);

};

//螺旋还差一个相位补偿值，暂时不加
class Prog_Manager_API Cal_LouXuan
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_LuoXuan& in_data);

	//2 基本数据结构
public:
	CanShu_LuoXuan data_base;

	double get_zhi_or_xie_ang_qian();

	//3 初始化结构
public:
	void init_data();
	void init_guanxi();

	bool is_del_ok();


	void cal_son_last_state();

	//4 主数据结构
public:
	int pos;
	Tool_Base* ptr_tool;
	bool is_lastest = 0;

	Cal_XingXian* ptr_xx;
	Cal_FenDu* ptr_fd;

	//螺旋线：
	//柱坐标点
	//X坐标：	轴向长度坐标
	//R坐标：	半径坐标
	//相位坐标：	相位（第一个点相位为0，绕X正方向为正）（角度制）
	//直角坐标点：	参考坐标系下的坐标
	//X坐标：	X坐标
	//Y坐标：	Y坐标
	//Z坐标：	Z坐标
	//半径方向：	在参考坐标系下直角坐标YZ（XY）组成的单位向量，向外
	//柱0后面坐标系：	在0相位位置描述
	//X轴：	相位0截形的切向，刀柄指向刀尖
	//Y轴：	同刀具Z轴 后角线方向
	//Z轴： 后刀面法向 指向外
	//法0后面坐标系：	在直角坐标点位置描述
	//X轴：	刃线反切向，刀柄指向刀尖
	//Y轴：	后角线方向（Z轴×X轴）
	//Z轴：	单位化（X轴×(刀具X轴×半径方向)）面法向指向外
	//曲线的长度坐标：	型线的长度坐标--毫米5.29（可以不等距）
	//直纹线方向：垂直轴线	向内 25.9.15
	//31*n
	mat Data_Of_Points;

	//关联情况
	vector<Miller_GX_Base*> v_GL_GX;

	void add_guanxi_GL_GX(Miller_GX_Base* p);
	void del_guanxi_GL_GX(Miller_GX_Base* p);
	int guanxi_exist(Miller_GX_Base* p);

	int del_self();
	void speak_father_del_guanxi();

#pragma region 结果计算接口
	//5 结果计算接口
public:
	//返回点的数量
	int n_P();
	//返回第i个点的柱坐标
	vec BG_zP(int i);
	//返回第i个点的坐标，3阶
	vec BG_P(int i);
	//返回全部的柱坐标 一列一个点
	mat BG_zP();
	//返回全部的点坐标 一列一个点
	mat BG_P();

	//返回第i个点处的半径方向
	vec BG_r_arrow(int i);
	//返回第i个点处的柱坐标X方向 3阶
	vec BG_zX(int i);
	//返回第i个点处的柱坐标Y方向 3阶
	vec BG_zY(int i);
	//返回第i个点处的柱坐标Z方向 3阶
	vec BG_zZ(int i);
	//返回第i个点处的柱坐标系 3阶
	//柱0后面坐标系：	在0相位位置描述
	//X轴：	相位0截形的切向，刀柄指向刀尖
	//Y轴：	同刀具Z轴 后角线方向
	//Z轴： 后刀面法向 指向外
	mat33 BG_zSYS(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nX(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nY(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nZ(int i);
	//返回第i个点处的法坐标系 3阶
	//法0后面坐标系：	在直角坐标点位置描述
	//X轴：	刃线反切向，刀柄指向刀尖
	//Y轴：	后角线方向（Z轴×X轴）
	//Z轴：	单位化（X轴×(刀具X轴×半径方向)）面法向指向外
	mat33 BG_nSYS(int i);
	//返回第i个点处的长度坐标
	double Lenth_At_Point(int i);
	//返回总长度
	double Lenth();
	//返回第i个点处的相位
	double get_xiangwei(int i);
	//获得指定x坐标上的相位
	double get_xiangwei_by_x(double x_in);
	//通过x值就近获取下标 
	int get_index_by_x(double x_in);

	mat33 BG_nSYS_by_x(double x_in);

	//返回直纹线方向 向内
	vec BG_zhiwen(int i);
	
#pragma endregion

public:
	//计算螺旋与型线的交线 9.15
	 void cal_jiaoxian_by_xx(Cal_XingXian* ptr_xx,  Cal_hdm_RX& ans_rx);

#pragma region 其他
	//6 其他
public:
	//p：平面点，n平面法向，m圆的长度坐标，R圆半径(选择y值更大的交点)
	vec cal_cir_plane_jiaodian(vec p, vec n, double m, double R);

	void cal_zhicao_vp(vec start_p, double in_qian, double in_xie, mat& ans_vp);

	//通过螺旋线的直角坐标点计算出其他主数据内容
	void cal_main_data_by_points(mat& in_vp, double ang_qian);
	//计算斜槽的螺旋线直角坐标点
	//mat cal_xiecao_vp()
	//{
	//	double add_xishu = tan(tcRadians(data_base.ang_xie));
	//	int count_p = ptr_xx->n_P();

	//	mat ans_vp = zeros(3, count_p);

	//	vec last_p = ptr_xx->BG_P(0);
	//	for (int i = 0; i < count_p; i++)
	//	{
	//		vec ls_p = ptr_xx->BG_P(i); //直角坐标点
	//		//ls_p(1) = data_base.R_zhi_or_xie; //用螺旋参数中的半径 11.3

	//		double delta_len = ls_p(0) - last_p(0); //长度增量
	//		double delta_rad = add_xishu * delta_len; //弧度增量

	//		vec cal_p = ls_p;
	//		cal_p(0) = 0.0;
	//		double add_ang = tcDegree(atan(delta_rad / norm(cal_p))); //角度增量

	//		ls_p = tcRotX(3, add_ang) * ls_p;  //实际位置

	//		//ans_vp.insert_cols(ans_vp.n_cols, ls_p);
	//		ans_vp.col(i) = ls_p;

	//		last_p = ls_p;
	//	}
	//	return ans_vp;
	//}
	//计算螺旋槽的螺旋线直角坐标点
	mat cal_luoxuancao_vp();

	void cal_B_daocheng_canshu(vector<double>& ans_v_cal_ang);
	//将变螺旋转为变导程
	void B_luo_to_B_daocheng();

	mat cal_luoxuancao_vp_by_B_daocheng(vector<double>& in_v_cal_ang);
	//m
	mat cal_points_by_daocheng_v(vec& daocheng_v);
	//m.1
	vec cal_daocheng_v_by_dengdaocheng();
	//m.2
	vec cal_daocheng_v_by_dengluoxuanjiao();
	//m.3
	vec cal_daocheng_v_by_biandaocheng();
	//m.4
	vec cal_daocheng_v_by_luoxuanjiao_v(vec& luoxuanjiao_v);
	//m.4.1
	vec cal_luoxuanjiao_v_by_bianluoxuan();

public:
	//转角+倾角 - 构造定长度-平槽面
	void init_data_by_zhuan_qing(double in_zhuan, double in_qing);
	//偏心距+倾角 - 构造定长度-平槽面
	void init_data_by_pianxin_qing(double in_pian, double in_qing);
	//螺旋角 - 构造定长度-直纹槽面
	void init_data_by_luoxuan(double in_luo);
	//导程 - 构造定长度-直纹槽面
	void init_data_by_daocheng(double in_daocheng);
#pragma endregion

public:
	void Range(double in_start, double in_end);
	void Sample(double in_len, double in_ang);

public:
	Cal_LouXuan();
	Cal_LouXuan(Tool_Base* in_ptr, CanShu_LuoXuan& in_data);
	~Cal_LouXuan();


public:
	//中途修改指定的型线
	void sel_a_xx_id(int in_id);
	void sel_a_fd_id(int in_id);
public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API Cal_QDM
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_QianJiao& in_data);
	void set_Range(double in_start, int in_end);
	void set_Sample(double in_len, int in_ang);
	//2 基本数据结构
public:
	CanShu_QianJiao data_base;
	int luoxuan_pos;
	bool luo_or_duan = 0; // 0:螺旋、1：端 //增加标志位，使计算面数据反向 8.16

	//传参给下一级使用
	double range_start = 0.0;
	double range_end = 1.0;
	double sample_len = 0.01;
	double sample_ang = 1.01;

	//3 初始化结构
public:
	void init_data(); //螺旋槽面点上转前角构造坐标系
	void add_son(Miller_GX_Base* in_ptr);
	void cal_son_last_state();

	//4 主数据结构
public:
	Tool_Base* ptr_tool;
	Cal_LouXuan* ptr_lx;

	bool is_lastest = 0;

	//前刀面：
	//	直角坐标点：	参考坐标系下描述
	//	X坐标：	X坐标
	//	Y坐标：	Y坐标
	//	Z坐标：	Z坐标
	//	前刀面坐标系：	参考坐标系下描述
	//	X轴：	Y轴×Z轴 
	//	Y轴：	0位移角度方向，前角线方向指向前刀面区域内
	//	Z轴：	前刀面法向，背离材料侧
	//	曲线的长度坐标：	沿曲线从起点到当前点的长度 / 单位长度
	// 13*n
	mat Data_Of_Points;

	//关联情况
	vector<Miller_GX_Base* > v_GL_GX;

public:
	void del_guanxi_GL_GX(Miller_GX_Base* p);
	void add_guanxi_GL_GX(Miller_GX_Base* p);
	int guanxi_exist(Miller_GX_Base* p);

	void speak_father_del_guanxi();
	int del_self();

	//5 结果计算接口
public:
	//返回点的数量
	int n_P();
	//返回第i个点的坐标，3阶
	vec BG_P(int i);
	//返回全部的点坐标 3阶
	mat BG_P();
	//返回第i个点处前刀面坐标系的X方向 3阶
	vec BG_X(int i);
	//返回第i个点处前刀面坐标系的Y方向 3阶
	vec BG_Y(int i);
	//返回第i个点处前刀面坐标系的Z方向 3阶
	vec BG_Z(int i);
	//返回第i个点处的前刀面坐标系 3阶
	mat33 BG_SYS(int i);
	//返回第i个点处的长度坐标
	double Lenth_At_Point(int i);

#pragma region 其他
	//6 其他
public:
	//插值法向前角 //不用主数据的螺旋指针，下面函数都用副本 25.11.13
	vec cal_qianjiao_v_by_B_n(Cal_LouXuan* ls_lx);
	//插值径向前角
	vec cal_qianjiao_v_by_B_r(Cal_LouXuan* ls_lx);

	void cal_main_data_by_n_v_qianjiao(Cal_LouXuan *ls_lx, vec& in_v_qina);
	void cal_main_data_by_r_v_qianjiao(Cal_LouXuan *ls_lx, vec& in_v_qina);
	//当螺旋是直槽或斜槽，用螺旋线作为前刀面点 25.11.3
	void cal_main_data_by_zhi_or_xie(Cal_LouXuan *ls_lx);

public:
	Cal_QDM();
	~Cal_QDM();
	Cal_QDM(Tool_Base* in_ptr, CanShu_QianJiao& in_data);

public:
	void sel_a_lx_id(int in_id);
	//修改产生副本数据
public:
	//起始百分比选择范围
	void Range(double in_start, double in_end);
	//当前数据抽样结果直接修改主数据
	void Sample(double in_len, double in_ang);

public:
	Cal_QDM copy_main_data();

#pragma endregion
};

//芯厚面： 贝塞尔曲面类对象
class Prog_Manager_API Cal_XinHouMian
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_XinHouMian& in_data);

	//2 基本数据结构
public:
	CanShu_XinHouMian data_base;


	//3 初始化结构
public:
	void init_data(); //构造贝塞尔曲面

	void cal_son_last_state();

	//4 主数据结构
public:
	int pos;
	Tool_Base* ptr_tool;
	Bezier_Curve3_QM obj_qm; //曲面

	bool is_lastest = 0;

	mat ls_vp;
	mat ls_vt;
	//5 结果计算接口
public:
	void get_data(Bezier_Curve3_QM& ans_data);

	//6 其他
public:
	Cal_XinHouMian();
	~Cal_XinHouMian();

	Cal_XinHouMian(Tool_Base* in_ptr, CanShu_XinHouMian& in_data);
public:
	void cal_xh_line_of_luoxuan();
	void cal_xh_line_of_duanchi();
	void cal_xh_line_of_qiutou();
	void cal_xh_line_of_yuanjiao();
public:
	int save();
	void load();
};

class Prog_Manager_API Cal_hdm_RX
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(CanShu_hdm_rx& in_data);
	void set_range_and_sample(double in_start, double in_end, double in_len, double in_ang);


	//2 基本数据结构
public:
	CanShu_hdm_rx data_base;
	bool luo_or_duan = 0; // 0:螺旋、1：端 //增加标志位，使计算面数据反向
	bool need_jiao_hdm = 0; //后刀面是否求交得到，成型 = 1 8.22

	double range_start = 0.0;
	double range_end = 1.0;
	double sample_len = 0.01;
	double sample_ang = 1.01;

	//3 初始化结构
public:
	void init_data(); //螺旋槽面点上转前角构造坐标系
	void cal_son_last_state();

	//4 主数据结构
public:
	Tool_Base* ptr_tool;
	Cal_XingXian* ptr_xx;
	Cal_LouXuan* ptr_lx;

	bool is_lastest = 0;

	//后刀面刃线：
	//柱坐标点
	//X坐标：	轴向长度坐标
	//R坐标：	半径坐标
	//相位坐标：	相位(角度)
	//直角坐标点：	参考坐标系下的坐标
	//X坐标：	X坐标
	//Y坐标：	Y坐标
	//Z坐标：	Z坐标
	//半径方向：	在参考坐标系下直角坐标YZ组成的单位向量
	//柱0后面坐标系：	在0相位位置描述
	//X轴：	相位0截形的切向，从刀尖指向刀柄
	//Y轴：	Z轴×X轴
	//Z轴：	同刀具Z轴
	//法0后面坐标系：	在直角坐标点位置描述
	//X轴：	刃线切向，从刀尖指向刀柄
	//Y轴：	后角线方向（Z轴×X轴） 从边界朝向后刀面内
	//Z轴：	单位化（X轴×(刀具X轴×半径方向)）面法向朝内指
	//曲线的长度坐标：	沿曲线从起点到当前点的长度 / 单位长度
	//28*n
	mat Data_Of_Points;

#pragma region 结果计算接口
	//5 结果计算接口
public:
	//返回点的数量
	int n_P();
	//返回第i个点的柱坐标
	vec BG_zP(int i);
	//返回第i个点的坐标，3阶
	vec BG_P(int i);
	//返回全部的柱坐标 一列一个点
	mat BG_nzP();
	//返回全部的点坐标 一列一个点
	mat BG_nP();
	//返回第i个点处的半径方向
	vec BG_r_arrow(int i);
	//返回第i个点处的柱坐标X方向 3阶
	vec BG_zX(int i);
	//返回第i个点处的柱坐标Y方向 3阶
	vec BG_zY(int i);
	//返回第i个点处的柱坐标Z方向 3阶
	vec BG_zZ(int i);
	//返回第i个点处的柱坐标系 3阶
	//柱0后面坐标系：	在0相位位置描述
	//X轴：	相位0截形的切向，刀柄指向刀尖
	//Y轴：	同刀具Z轴 后角线方向
	//Z轴： 后刀面法向 指向外
	mat33 BG_zSYS(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nX(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nY(int i);
	//返回第i个点处的法坐标X方向 3阶
	vec BG_nZ(int i);
	//返回第i个点处的法0后面坐标系 3阶
	//法0后面坐标系：	在直角坐标点位置描述
	//X轴：	刃线反切向，刀柄指向刀尖
	//Y轴：	后角线方向（Z轴×X轴）
	//Z轴：	单位化（X轴×(刀具X轴×半径方向)）面法向指向外
	mat33 BG_nSYS(int i);
	//返回第i个点处的长度坐标
	double Lenth_At_Point(int i);
#pragma endregion

	//6 其他
public:
	//p：平面点，n平面法向，m圆的长度坐标，R圆半径(选择y值更大的交点)
	vec cal_cir_plane_jiaodian(vec p, vec n, double m, double R);

	Cal_hdm_RX();
	~Cal_hdm_RX();
public:
	Cal_hdm_RX(int id_lx, int id_hj, Tool_Base* in_ptr);

};

class Prog_Manager_API Cal_HDM
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(int id_lx,int id_hj);
	void set_Range(double in_start,int in_end);
	void set_Sample(double in_len, int in_ang);

	//2 基本数据结构
public:
	int luoxuan_order ;
	int houjiao_order ;
	bool luo_or_duan = 0; // 0:螺旋、1：端 //增加标志位，使计算面数据反向
	bool need_jiao_hdm = 0; //后刀面是否求交得到，成型 = 1 8.22

	//传参给下一级使用
	double range_start = 0.0;
	double range_end = 1.0;
	double sample_len = 0.01;
	double sample_ang = 1.01;

	//3 初始化结构
public:
	void init_data(); //螺旋槽面点上转前角构造坐标系
	void add_son(Miller_GX_Base* in_ptr);

	//4 主数据结构
public:
	Tool_Base* ptr_tool;
	Cal_LouXuan* ptr_lx;
	Cal_HouJiao* ptr_hj;

	bool is_lastest = 0;

	Cal_hdm_RX rx;

	//后刀面：	说明
	//	第1后刀面直角坐标点：	参考坐标系下描述
	//	X坐标：	X坐标
	//	Y坐标：	Y坐标
	//	Z坐标：	Z坐标
	// 第2后刀面直角坐标点：	参考坐标系下描述
	//	X坐标：	X坐标
	//	Y坐标：	Y坐标
	//	Z坐标：	Z坐标
	// 第3后刀面直角坐标点：	参考坐标系下描述
	//	X坐标：	X坐标
	//	Y坐标：	Y坐标
	//	Z坐标：	Z坐标
	// 第1后刀面坐标系：	参考坐标系下描述
	//	X轴：	Y轴×Z轴
	//	Y轴：	后角线方向，指向后刀面区域内
	//	Z轴：	后刀面法向，背离材料侧
	// 第2后刀面坐标系：	参考坐标系下描述
	//	X轴：	Y轴×Z轴
	//	Y轴：	后角线方向，指向后刀面区域内
	//	Z轴：	后刀面法向，背离材料侧
	// 第3后刀面坐标系：	参考坐标系下描述
	//	X轴：	Y轴×Z轴
	//	Y轴：	后角线方向，指向后刀面区域内
	//	Z轴：	后刀面法向，背离材料侧
	// 曲线的长度坐标：	沿曲线从起点到当前点的长度 / 单位长度
	//37*n
	mat Data_Of_Points;

	//关联关系
	vector<Miller_GX_Base*> v_GL_GX;

public:
	void del_guanxi_GL_GX(Miller_GX_Base* p);
	void add_guanxi_GL_GX(Miller_GX_Base* p);
	int guanxi_exist(Miller_GX_Base* p);
	void speak_father_del_guanxi();
	int del_self();

#pragma region MyRegion
	//5 结果计算接口
public:
	//返回点的数量
	int n_P();
	//返回第1后刀面第i个点的坐标，3阶
	vec HJ1_P(int i);
	//返回第2后刀面第i个点的坐标，3阶
	vec HJ2_P(int i);
	//返回第3后刀面第i个点的坐标，3阶
	vec HJ3_P(int i);

	//返回第1后刀面第i个点处的X 3阶
	vec HJ1_X(int i);
	//返回第1后刀面第i个点处的Y 3阶
	vec HJ1_Y(int i);
	//返回第1后刀面第i个点处的Z 3阶
	vec HJ1_Z(int i);
	//返回第1后刀面第i个点处的后面坐标系  3阶
	mat33 HJ1_SYS(int i);

	//返回第2后刀面第i个点处的X 3阶
	vec HJ2_X(int i);
	//返回第2后刀面第i个点处的Y 3阶
	vec HJ2_Y(int i);
	//返回第2后刀面第i个点处的Z 3阶
	vec HJ2_Z(int i);
	//返回第2后刀面第i个点处的后面坐标系  3阶
	mat33 HJ2_SYS(int i);

	//返回第3后刀面第i个点处的X 3阶
	vec HJ3_X(int i);
	//返回第3后刀面第i个点处的Y 3阶
	vec HJ3_Y(int i);
	//返回第3后刀面第i个点处的Z 3阶
	vec HJ3_Z(int i);
	//返回第3后刀面第i个点处的后面坐标系  3阶
	mat33 HJ3_SYS(int i);

	//返回第1后刀面第i个点处的长度坐标
	double Lenth_At_Point(int i);


public:
	//设置第1后刀面第i个点的坐标，3阶
	void set_HJ1_P(int i, vec in_p);
	//设置第2后刀面第i个点的坐标，3阶
	void set_HJ2_P(int i, vec in_p);
	//设置第3后刀面第i个点的坐标，3阶
	void set_HJ3_P(int i, vec in_p);
	//设置第1后刀面第i个点处的后面坐标系  3阶
	void set_HJ1_SYS(int i, mat in_sys);
	//设置第2后刀面第i个点处的后面坐标系  3阶
	void set_HJ2_SYS(int i, mat in_sys);
	//设置第3后刀面第i个点处的后面坐标系  3阶
	void set_HJ3_SYS(int i, mat in_sys);
	//设置第i个点的长度坐标
	void set_length(int i, double in_len);

public:
	double get_xiangwei(vec p);

#pragma endregion

	void set_main_data_by_djjx_rx(mat& ls_rx);
	//6 其他
public:
	Cal_HDM();
	~Cal_HDM();
	Cal_HDM(int id_lx, int id_hj, Tool_Base* in_ptr);

public:
	void sel_a_lx_id(int in_id);
	void sel_a_hj_id(int in_id);

	//wld20250603
		//按照型线百分比取值
	void Range(double in_start, double in_end);

	//wld20250603
	//没有结果
	void Sample(double in_len, double in_ang);

	//20250603
	void set_luoxuan_id(int id);
	//20250603
	void set_houjiao_id(int id);

	Cal_HDM copy_main_data();
};

//约等于砂轮参数类，与cal形式统一
class Prog_Manager_API Cal_SL_LRr
	: public save_lib
{
	//1 基本设置接口
public:
	void set_base_data(int in_sl_id);//法兰，半径，圆角

	//2 基本数据结构
public:
	int sl_id;

	//3 初始化结构
public:
	void init_data(); //螺旋槽面点上转前角构造坐标系


	//4 主数据结构
public:
	Tool_Base* ptr_tool;

	int SL_L;
	int SL_R;
	int SL_r;

	bool is_lastest = 0;

	//关联关系
	vector<Miller_GX_Base*> v_GL_GX;//一个砂轮可以被多个工序选择

public:
	void del_guanxi_GL_GX(Miller_GX_Base* p);
	void add_guanxi_GL_GX(Miller_GX_Base* p);
	int guanxi_exist(Miller_GX_Base* p);
	void speak_father_del_guanxi();
	int del_self();

	//6 其他
public:
	Cal_SL_LRr();
	~Cal_SL_LRr();
};


////型线存储管理类
//class Prog_Manager_API Storage_manager_xingxian
//{
//	//文件保存路径
//#pragma region 文件名称变量，保存路径=执行项目
//public:
//	string file_dir_xingxian_catalog;  //0  型线目录文件 25.4.3
//	//string file_dir_xingxian_data;   //1  型线点数据文件 25.4.3
//
//	string file_dir_xingxian_count;	//2 型线计数文件
//	//string file_dir_tool_data_CX; //2//成型刀具数据-公共参数存储文件路径4.8
//
//#pragma endregion
//public:
//	//更新型线计数--真为加，假为减
//	bool add_xingxian_count(bool add);
//	int get_xingxian_count();
//	//重命名dxf文件并拷贝到指定文件夹
//	void renameAndCopyFile(const string& sourcePath, const string& newName, const string& targetDirectory);
//
//public:
//	//将型线名称文件读成显示列表3.5-不显示-1的数据条3.6
//	void read_xx_catalog_for_display_list(vector<int>& ans_type, vector<string>& ans_name);
//	//p_manager加载一条型线,将数据写入两个文件
//	//void load_a_dxf(string in_file_name,double in_dis, string in_new_name);
//
//	void load_xx_data_by_name(string in_name, Cal_XingXian& ans_xx);
//
//	//根据目录索引对应位置的型线数据
//	void load_a_tool_xx_name_and_data(vector<int>& in_v_pos, vector<string>& ans_v_name, vector<Cal_XingXian>& ans_v_data);
//
//	//成型刀添加一条型线，将新name写入目录文件
//	int tool_add_a_xx_from_win(string in_dxf_name, string in_new_name, Cal_XingXian& xx_data);
//
//	//根据文件名修改对应行的标志位为删除（-1）3.6
//	bool renew_a_xx_name_of_type_by_delete(string in_file_name);
//
//	//获取指定位置的dxf文件名
//	string get_tag_pos_dxf_file_name(int in_pos);
//	//获取指定位置的dxf文件名及点数据
//	void get_tag_pos_dxf_name_and_data(int in_pos, string& ans_name, mat& ans_data);
//public:
//	//构造：指定所有文件的名字、将文件的数据大小在此设置
//	Storage_manager_xingxian();
//	~Storage_manager_xingxian();
//public:
//	const int NAME_BUFFER_SIZE = 100;
//private:
//	void ans_vv_to_mat(vector<vec>& points, mat& Data_Of_Points);
//};


//刃线类：输入空间线得到n*25的刃线结构--可能用不上
//class Prog_Manager_API Cal_RenXian
//{
//	//1 基本设置接口
//public:
//	//重载=
//	void operator=(const Cal_RenXian& A);
//	//输入已经构造完成的空间线（ mat（n*3：x，y，z）） 坐标系原点在螺旋线起点截面回转中心
//	//输出：以第一个点相位角为0
//	void ImportData_by_luoxuancao(KongJianXian& line_in);
//
//	void ImportData_by_qiutou(KongJianXian& line_in);
//
//	//对于平底刀横刃法坐标系与横坐标系相等
//	void ImportData_by_hengren(KongJianXian& line_in);
//
//	//2 基本数据结构
//public:
//
//
//	//3 初始化结构
//public:
//	void init_data(); //需要通过dxf存储位置加载，将存储管理类定义为全局 ??? 4.24
//	//void add_son(Cal_LouXuan* in_ptr);  //继承关系
//
//	//4 主数据结构
//public:
//	//型线点的数量 = 空间线点数 - 1
//	int n_P;
//	//点的最大编号
//	int Max_No_P;
//	//初始平均分点距
//	double Distance_of_Point;
//	//{点编号, 点坐标, (法坐标系)x向量, y向量, z向量,（横坐标系）x向量, y向量, z向量，(柱坐标)柱半径，相位角，Z坐标}
//	mat Data_Of_Points;
//	//{0,		1-3,			4-6,		7-9,	10-12 ,		13-15,	16-18,  19-21,    22,			23,     24 }
//	//n*25
//
//	//5 结果计算接口
//public:
//#pragma region 编辑空间线-删除
//public:
//	////将起点终点反向得到新的线-
//	//球头、螺旋不同--目前只有球头10.14
//	void fanxiang();
//	//将已有刃线，进行旋转
//	void rotate(mat33 SYS); //球头不能旋转
//	//将已有刃线，进行平移
//	void trans(vec3 O);
//	//截取线已有刃线的一段，输入截取起点终点（0-1]，得到新的线
//	void cutting(double start, double end);
//
//	void cutting_qiutou(double start, double end);//计算球头槽前刀面使用
//
//	//沿终点切向延伸指定距离
//	void extend(double add_dis);
//	//针对球头线设置偏心距, 在没拼接螺旋前偏置()
//	void set_pinxin_dis(double in_dis);
//
//#pragma endregion
//
//public:
//	//将已经计算完成的刃线，旋转工序对应的补偿角度 25.2.19
//	void rotate_by_buchang(double in_bu_ang);
//
//#pragma region 提取数据
//public:
//	//返回刃线的长度,在抽样的情况下可能无法得出
//	double Lenth_of_RenXian();
//	//返回刃线点的数量
//	int get_p_num();
//	//返回第i个点的坐标，点号
//	vec P(int i);
//	//返回第i个点处的，法坐标系: X向量
//	vec nX(int i);
//	//返回第i个点处的, 法坐标系：Y向量
//	vec nY(int i);
//	//返回第i个点处的，法坐标系：Z向量
//	vec nZ(int i);
//	//返回第i个点处的，横坐标系: X向量
//	vec hX(int i);
//	//返回第i个点处的，横坐标系：Y向量
//	vec hY(int i);
//	//返回第i个点处的，横坐标系：Z向量
//	vec hZ(int i);
//	//返回第i个点的柱半径
//	double rotR(int i);
//	//返回第i个点的相位角
//	double XWJ(int i);
//	//返回第i个点处的，法坐标系
//	mat nSYS(int i);
//	//返回第i个点处的，横坐标系
//	mat hSYS(int i);
//	//第i个点所在的弧长百分比，空间线长度
//	double lenth_percent(int i);
//#pragma endregion
//
//
//	//6 其他
//#pragma region 其他
//public:
//	//构造函数
//	Cal_RenXian();
//	//析构函数
//	~Cal_RenXian();
//
//	//自身处理
//public:
//	//长度条件，角度条件
//	//void Sample(double changdu, double jiaodu);  //选择横坐标的z向量在纵截面的角度变化?? 等角锥螺旋角度不变
//	////长度条件，角度条件
//	//void Sample(xt_CanShu_Sample& canshu);
//
//	////起始长度百分比选择范围 支持抽样后选范围
//	//void Range(double start, double end);
//	////起始百分比选择范围 支持抽样后选范围
//	//void Range(xt_CanShu_Range& canshu);
//
//	//反向操作可能会使结果不对，不提供刃线的编辑，数据源头在空间线 8.24 mark
//
//public:
//	//对球头线设置偏心距
//	//void set_pinxin_dis(double in_dis); //报错已经定义或声明
//	//刃线构造定义为完全由空间线组成，只计算相应坐标系
//	//因此球头线的偏心距设置应放到生成时，可以通过内部改变角度值
//
//	//球头刃线起点在回转中心，按法坐标系的法向偏置得到的线不完全重合在球面
//	//加工出的刃线理论上在球面、因此可以在刃线类里操作
//public:
//	//void save(ofstream& outFile);  //后面需要改???
//	//void load(ifstream& infile);
//
//public:
//	//提取出空间线的点集，用来进行刃线的相关编辑 返回n*3
//	mat get_kongjianxian();
//
//public:
//	double cal_cut_dis_percent_in_end(double in_dis, mat& in_ren);
//#pragma endregion
//};