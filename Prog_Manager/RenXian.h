#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"generator_line.h"
#include "Obj_Prog.h"
#include"manager_h/MA_060195_XiDao_Grovving.h"
#include"QuMian_Grovving.h"

using namespace std;
enum MoXueLeiXing { XZ_WY, BD_WY };

class Miller_GX_Base;
class xt_CanShu_Sample;
class xt_CanShu_Range;
class Cal_LouXuan;
class Cal_QDM;
class Cal_HDM;


////型线类：输入得到13*n的型线结构，X半径方向，Z长度方向
//class Prog_Manager_API Cal_XingXian
//{
//	//1 基本设置接口
//public:
//	void set_base_data(CanShu_XingXian& in_data);
//
//	//2 基本数据结构
//public:
//	CanShu_XingXian data_base;
//
//	//3 初始化结构
//public:
//	void init_data(); //需要通过dxf存储位置加载，将存储管理类定义为全局 ??? 4.24
//	void add_son(Cal_LouXuan* in_ptr);  //继承关系
//
//	//4 主数据结构
//public:
//	//{点坐标, 切向量X, 法向量Y，向量X，长度坐标} 13*n 默认间距0.001
//	mat Data_Of_Points;
//
//	//5 结果计算接口
//public:
//	//数据访问
//	//返回点的数量
//	int n_P();
//	//返回刃线的型线长度
//	double Lenth();
//	//返回第i个点的坐标，3或4阶，点号
//	vec BG_P(int a, int i);
//	//返回全部的点坐标
//	mat BG_P();
//	//返回第i个点处的切向量，3或4阶，点号
//	vec BG_T(int a, int i);
//	//返回全部的点坐标
//	mat BG_T();
//	//返回第i个点处的长度坐标
//	double Lenth_At_Point(int i);
//
//	//6 其他
//public:
//	//初始化按照精度读取dxf文件为点集数据
//	void init_data_by_dxf_file(string in_file, double in_dis, double in_ang);
//	void init_data_by_dxf_file(string in_file, double in_dis);
//public:
//	void rotate(mat33 SYS); //4.7
//	//对线进行处理
//public:
//	//抽样(只能操作一次) 长度条件，角度条件
//	void Sample(double changdu, double jiaodu);
//	//起始百分比选择范围 抽样后不能选范围 [0,1]
//	void Range(double in_strat, double in_end);
//	//径向偏置-增大回转半径
//	void PianZhi_R(double in_R);
//
//	//在某个长度位置插入一个点,返回这个点的位置
//	virtual int insert_point_at_lenth(double pos);
//	//起点延长
//	virtual void extend_at_start(double lenth);
//	//终点延长
//	virtual void extend_at_end(double lenth);
//
//	//设置数据
//public:
//	//设置第i个点的坐标
//	void set_P(int i, vec P_in);
//	//设置第i个点的切向
//	void set_T(int i, vec T_in);
//	//设置第i个点的长度坐标
//	void set_Lenth_At_Point(int i, double lenth_pos);
//
//public:
//	Cal_XingXian();
//	~Cal_XingXian();
//
//private:
//	//将读取的dxf点转为mat
//	void ans_vv_to_mat(vector<vec>& points);
//
//};
//
////刃线类：输入空间线得到n*25的刃线结构
//class Prog_Manager_API Cal_RenXian
//{
//	//数据
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
//	//初始化
//public:
//	//构造函数
//	Cal_RenXian();
//	//析构函数
//	~Cal_RenXian();
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
//	//自身处理
//public:
//	//长度条件，角度条件
//	void Sample(double changdu, double jiaodu);  //选择横坐标的z向量在纵截面的角度变化?? 等角锥螺旋角度不变
//	//长度条件，角度条件
//	void Sample(xt_CanShu_Sample& canshu);
//
//	//起始长度百分比选择范围 支持抽样后选范围
//	void Range(double start, double end);
//	//起始百分比选择范围 支持抽样后选范围
//	void Range(xt_CanShu_Range& canshu);
//
//	//反向操作可能会使结果不对，不提供刃线的编辑，数据源头在空间线 8.24 mark
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
//public:
//	//对球头线设置偏心距
//	//void set_pinxin_dis(double in_dis); //报错已经定义或声明
//	//刃线构造定义为完全由空间线组成，只计算相应坐标系
//	//因此球头线的偏心距设置应放到生成时，可以通过内部改变角度值
//
//	//球头刃线起点在回转中心，按法坐标系的法向偏置得到的线不完全重合在球面
//	//加工出的刃线理论上在球面、因此可以在刃线类里操作
//public:
//	void save(ofstream& outFile);  //后面需要改???
//	void load(ifstream& infile);
//
//public:
//	//提取出空间线的点集，用来进行刃线的相关编辑 返回n*3
//	mat get_kongjianxian();
//
//public:
//	double cal_cut_dis_percent_in_end(double in_dis, mat& in_ren);
//};
//
////螺旋槽面类：成型刀螺旋的表达{点坐标,方向,切向,法向} 12*n
////不产生离散点及方向，存槽型的参数，根据参数输入，高度值，计算出对应点及方向4.16
////保留点集数据，增加可生成对应点的接口4.18
//class Prog_Manager_API Cal_LouXuan
//{
//	//1 基本设置接口
//public:
//	void set_base_data(Cal_XingXian* in_ptr, CanShu_LX_XiangWei& in_data);
//
//	//2 基本数据结构
//public:
//	int xingxian_id;
//	int fendu_id;
//	CanShu_LX_XiangWei data_base;	//相位
//
//	//3 初始化结构
//public:
//	void init_data(); 
//	void add_son(Cal_QDM* in_ptr);  //前后刀面都选用螺旋 ??? 4.25
//	void add_son(Cal_HDM* in_ptr);
//
//public:
//	//转角+倾角 - 构造定长度-平槽面
//	void init_data_by_zhuan_qing(double in_zhuan, double in_qing);
//	//偏心距+倾角 - 构造定长度-平槽面
//	void init_data_by_pianxin_qing(double in_pian, double in_qing);
//	//螺旋角 - 构造定长度-直纹槽面
//	void init_data_by_luoxuan(double in_luo);
//	//导程 - 构造定长度-直纹槽面
//	void init_data_by_daocheng(double in_daocheng);
//
//	//4 主数据结构
//public:
//	Cal_XingXian* ptr_xx;		//型线
//	//{点坐标,方向,切向,法向} 12*n
//	mat Data_Of_Points; //起点固定在X轴上
//
//	//5 结果计算接口
//public:
//	//返回点的数量
//	int n_P();
//	//返回第i个点的坐标，3或4阶，点号
//	vec BG_P(int a, int i);
//	//返回全部的点坐标
//	mat BG_P();
//	//返回第i个点处的方向量，3或4阶，点号
//	vec BG_T(int a, int i);
//	//返回全部的方向量
//	mat BG_T();
//
//	//6 其他
//public:
//	Cal_LouXuan();
//	~Cal_LouXuan();
//
//public:
//	void set_R_len(double in_R, double in_z_len);
//public:
//	void rotate(mat33 SYS); //4.7
//
//private:
//	void gen_luoxuanxian(double in_luo, double in_R, mat& points);
//};
//
////前刀面： 螺旋+前角得到前刀面数据： 12*n，点+sys
//class Prog_Manager_API Cal_QDM
//{
////1 基本设置接口
//public:
//	void set_base_data(Cal_LouXuan* in_ptr, CanShu_Qian_Angle& in_data);
//
////2 基本数据结构
//public:
//	int luoxuan_id;
//	CanShu_Qian_Angle ptr_q_ang;
//
////3 初始化结构
//public:
//	void init_data(); //螺旋槽面点上转前角构造坐标系
//	void add_son(Miller_GX_Base* in_ptr);
//
////4 主数据结构
//public:
//	Cal_LouXuan* ptr_lx;
//	//{点坐标,坐标系} 12*n
//	mat Data_Of_QDM;
//
////5 结果计算接口
//public:
//
////6 其他
//public:
//	Cal_QDM();
//	~Cal_QDM();
//
//};
//
////芯厚面： 贝塞尔曲面类对象
//class Prog_Manager_API Cal_XinHouMian
//{
//	//1 基本设置接口
//public:
//	void set_base_data(CanShu_XinHouMian& in_data);
//
//	//2 基本数据结构
//public:
//	CanShu_XinHouMian ptr_xh;
//
//	//3 初始化结构
//public:
//	void init_data(); //构造贝塞尔曲面
//	void add_son(Miller_GX_Base* in_ptr);
//
//	//4 主数据结构
//public:
//	Bezier_Curve3_QM ptr_qm; //曲面
//
//	//5 结果计算接口
//public:
//	void get_data(Bezier_Curve3_QM& ans_data);
//
//	//6 其他
//public:
//	Cal_XinHouMian();
//	~Cal_XinHouMian();
//
//private:
//
//};
//
////后角类：成型刀后角类，点+后角 4*n
//class Prog_Manager_API Cal_Houjiao
//{
//	//1 基本设置接口
//public:
//	void set_base_data(CanShu_HouJiao& in_data);
//	//2 基本数据结构
//public:
//	int xingxian_id;
//	CanShu_HouJiao ptr_hj;
//
//	//3 初始化结构
//public:
//	void init_data();
//	void add_son(Miller_GX_Base* in_ptr);
//
//	//4 主数据结构
//public:
//	Cal_XingXian* ptr_xx;		//型线
//	//{点坐标,后角} 4*n
//	mat Data_Of_Points;
//
//	//5 结果计算接口
//public:
//	void get_data(mat& ans_data);
//	//6 其他
//public:
//	Cal_Houjiao();
//	~Cal_Houjiao();
//
//private:
//
//};
//
////后刀面刃线：与刃线表达相同，输入不同
//class Prog_Manager_API Cal_hdm_RX
//{
//	//1 基本设置接口
//public:
//	void set_base_data(Cal_LouXuan* in_ptr, CanShu_HJ_BuChang& in_data);
//
//	//2 基本数据结构
//public:
//	int xingxian_id;
//	int luoxuan_id;
//	CanShu_HJ_BuChang ptr_bc; //后角补偿值
//
//	//3 初始化结构
//public:
//	void init_data(); //螺旋槽面点上转前角构造坐标系
//	void add_son(Cal_HDM* in_ptr);
//
//
//	//4 主数据结构
//public:
//	Cal_XingXian* ptr_xx;
//	Cal_LouXuan* ptr_lx;
//
//	Cal_RenXian hdm_rx;
//
//	//{点坐标,方向,切向,法向} 12*n
//	mat Data_Of_Points; //起点固定在X轴上
//
//	//5 结果计算接口
//public:
//
//	//6 其他
//public:
//	Cal_hdm_RX();
//	~Cal_hdm_RX();
//
//};
//
////后刀面： 刃线+后角得到后刀面数据： 12*n，点+sys
//class Prog_Manager_API Cal_HDM
//{
//	//1 基本设置接口
//public:
//	void set_base_data(Cal_Houjiao* in_ptr, Cal_hdm_RX& in_data);
//
//	//2 基本数据结构
//public:
//	int xingxian_id;
//	int luoxuan_id;
//	int houjiao_id;
//
//	//3 初始化结构
//public:
//	void init_data(); //螺旋槽面点上转前角构造坐标系
//	void add_son(Miller_GX_Base*);
//
//
//	//4 主数据结构
//public:
//	Cal_XingXian* ptr_xx;
//	Cal_LouXuan* ptr_lx;
//	Cal_hdm_RX ptr_rx;
//	Cal_Houjiao* ptr_hj;
//
//	//{点坐标,后刀面坐标系} 12*n
//	mat Data_Of_HDM;
//
//	//5 结果计算接口
//public:
//	void get_data(Cal_RenXian& ans_data);
//
//	//6 其他
//public:
//	Cal_HDM();
//	~Cal_HDM();
//};








