#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"Obj_Prog.h"

class nc_block;
class Point_by_5axis;

#pragma pack(push, 8)
//#pragma pack(pop) 

class Prog_Manager_API Canshu_Tool_GongYong
{
public:
	double delta_dis_ren = 0.001; //刃线密度，两点间距离
	xt_CanShu_Sample sample_tool; //让工序可以拿到5.19zy

	//基础数据结构
public:
	//安全点
	Point_by_5axis gx_safe_p;
	Point_by_5axis sl_safe_p;
	Point_by_5axis cx_safe_p;

};


class Prog_Manager_API CanShu_Geo_ZQ
	
{
public:
	CanShu_Geo_ZQ();

	//总体尺寸
public:
	double D;   //球直径
	double len_ren;	//刃的轴线长度
	double len_all;	//工件长度
	double ang_zhui;	//半锥角

	//球头部分--可根据螺旋角将球头刃线设置默认值5.22 todo：
public:
	//double ang_start_zhuan;	//球头起始转角 （刀尖）    可调
	double ang_end_luo;		//球头结束螺旋角  等于螺旋角

	double xishu_aotu; //曲线凹凸系数，默认1.0

	//锥面部分
public:
	double ang_luoxuan;	//等螺旋角

	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离

	//std::array<double, 6> v_no_dengfen_angle;
	//std::array<double, 6> v_pianxin_dis;
	//std::array<double, 6> v_center_dis;

#pragma region 三组后角
	//三个后角-三组（顶点，螺旋起点，螺旋结束）
public:
	double hdm_1_width;	//后刀面1宽度
	double hdm_1_d_qiu; //径向-刀尖
	double hdm_1_a_qiu;	//轴向
	double hdm_1_d_mid;
	double hdm_1_a_mid;
	double hdm_1_d_luo;
	double hdm_1_a_luo;
public:
	double hdm_2_width;	//后刀面2宽度
	double hdm_2_d_qiu; //径向
	double hdm_2_a_qiu;	//轴向
	double hdm_2_d_mid;
	double hdm_2_a_mid;
	double hdm_2_d_luo;
	double hdm_2_a_luo;
public:
	double hdm_3_width;	//后刀面3宽度
	double hdm_3_d_qiu; //径向
	double hdm_3_a_qiu;	//轴向
	double hdm_3_d_mid;
	double hdm_3_a_mid;
	double hdm_3_d_luo;
	double hdm_3_a_luo;
#pragma endregion
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(D,
	//		renlen,
	//		ang_zhui,
	//		ang_end_luo,
	//		xishu_aotu,
	//		ang_luoxuan,
	//		ren_count,
	//		is_dengfen,
	//		v_no_dengfen_angle,
	//		v_pianxin_dis,
	//		v_center_dis,
	//		hdm_1_width,
	//		hdm_1_d_qiu,
	//		hdm_1_a_qiu,
	//		hdm_1_d_mid,
	//		hdm_1_a_mid,
	//		hdm_1_d_luo,
	//		hdm_1_a_luo,
	//		hdm_2_width,
	//		hdm_2_d_qiu,
	//		hdm_2_a_qiu,
	//		hdm_2_d_mid,
	//		hdm_2_a_mid,
	//		hdm_2_d_luo,
	//		hdm_2_a_luo,
	//		hdm_3_width,
	//		hdm_3_d_qiu,
	//		hdm_3_a_qiu,
	//		hdm_3_d_mid,
	//		hdm_3_a_mid,
	//		hdm_3_d_luo,
	//		hdm_3_a_luo
	//	);
	//}
	//CanShu_Geo_ZQ() = default;
	//CanShu_Geo_ZQ(
	//	double _D,
	//	double _renlen,
	//	double _ang_zhui,
	//	double _ang_end_luo,
	//	double _xishu_aotu,
	//	double _ang_luoxuan,
	//	int _ren_count,
	//	bool _is_dengfen,
	//	const double _v_no_dengfen_angle[6],
	//	const double _v_pianxin_dis[6],
	//	const double _v_center_dis[6],
	//	double _hdm_1_width,
	//	double _hdm_1_d_qiu,
	//	double _hdm_1_a_qiu,
	//	double _hdm_1_d_mid,
	//	double _hdm_1_a_mid,
	//	double _hdm_1_d_luo,
	//	double _hdm_1_a_luo,
	//	double _hdm_2_width,
	//	double _hdm_2_d_qiu,
	//	double _hdm_2_a_qiu,
	//	double _hdm_2_d_mid,
	//	double _hdm_2_a_mid,
	//	double _hdm_2_d_luo,
	//	double _hdm_2_a_luo,
	//	double _hdm_3_width,
	//	double _hdm_3_d_qiu,
	//	double _hdm_3_a_qiu,
	//	double _hdm_3_d_mid,
	//	double _hdm_3_a_mid,
	//	double _hdm_3_d_luo,
	//	double _hdm_3_a_luo
	//)
	//	:
	//	D(_D),
	//	len_ren(_renlen),
	//	ang_zhui(_ang_zhui),
	//	ang_end_luo(_ang_end_luo),
	//	xishu_aotu(_xishu_aotu),
	//	ang_luoxuan(_ang_luoxuan),
	//	ren_count(_ren_count),
	//	is_dengfen(_is_dengfen),
	//	//   v_no_dengfen_angle(_v_no_dengfen_angle),
	//	   //v_pianxin_dis(),
	//	   //v_center_dis(),
	//	hdm_1_width(_hdm_1_width),
	//	hdm_1_d_qiu(_hdm_1_d_qiu),
	//	hdm_1_a_qiu(_hdm_1_a_qiu),
	//	hdm_1_d_mid(_hdm_1_d_mid),
	//	hdm_1_a_mid(_hdm_1_a_mid),
	//	hdm_1_d_luo(_hdm_1_d_luo),
	//	hdm_1_a_luo(_hdm_1_a_luo),
	//	hdm_2_width(_hdm_2_width),
	//	hdm_2_d_qiu(_hdm_2_d_qiu),
	//	hdm_2_a_qiu(_hdm_2_a_qiu),
	//	hdm_2_d_mid(_hdm_2_d_mid),
	//	hdm_2_a_mid(_hdm_2_a_mid),
	//	hdm_2_d_luo(_hdm_2_d_luo),
	//	hdm_2_a_luo(_hdm_2_a_luo),
	//	hdm_3_width(_hdm_3_width),
	//	hdm_3_d_qiu(_hdm_3_d_qiu),
	//	hdm_3_a_qiu(_hdm_3_a_qiu),
	//	hdm_3_d_mid(_hdm_3_d_mid),
	//	hdm_3_a_mid(_hdm_3_a_mid),
	//	hdm_3_d_luo(_hdm_3_d_luo),
	//	hdm_3_a_luo(_hdm_3_a_luo)
	//{
	//	std::copy(_v_no_dengfen_angle, _v_no_dengfen_angle + 6, v_no_dengfen_angle.begin());
	//	std::copy(_v_pianxin_dis, _v_pianxin_dis + 6, v_pianxin_dis.begin());
	//	std::copy(_v_center_dis, _v_center_dis + 6, v_center_dis.begin());
	//}
};

class Prog_Manager_API CanShu_Geo_PD
	
{
public:
	CanShu_Geo_PD();

	//平底部分
public:
	double D;	// 柱直径
	double len_ren;	//刃的轴线长度
	double len_all;	//工件长度
	double ang_die;	//蝶形角
	double ang_luo;	//螺旋角

	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离
	//std::array<double, 6> v_no_dengfen_angle;
	//std::array<double, 6> v_pianxin_dis;
	//std::array<double, 6> v_center_dis;
#pragma region 三组后角
	//三个后角-三组（横刃，螺旋部分）
public:
	double hdm_1_width;	//后刀面1宽度
	double hdm_1_a_hen;	//轴向--横刃只有
	double hdm_1_d_luo;
public:
	double hdm_2_width;	//后刀面2宽度
	double hdm_2_a_hen;	//轴向--横刃只有
	double hdm_2_d_luo;
public:
	double hdm_3_width;	//后刀面3宽度
	double hdm_3_a_hen;	//轴向--横刃只有
	double hdm_3_d_luo;
#pragma endregion
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		D_qiu,
	//		ang_die,
	//		ang_luo,
	//		ren_count,
	//		is_dengfen,
	//		v_no_dengfen_angle,
	//		v_pianxin_dis,
	//		v_center_dis,
	//		hdm_1_width,
	//		hdm_1_a_hen,
	//		hdm_1_d_luo,
	//		hdm_2_width,
	//		hdm_2_a_hen,
	//		hdm_2_d_luo,
	//		hdm_3_width,
	//		hdm_3_a_hen,
	//		hdm_3_d_luo
	//	);
	//}
	//CanShu_Geo_PD() = default;
	//CanShu_Geo_PD(
	//	double _D_qiu,
	//	double _ang_die,
	//	double _ang_luo,
	//	int    _ren_count,
	//	bool   _is_dengfen,
	//	const double _v_no_dengfen_angle[6],
	//	const double _v_pianxin_dis[6],
	//	const double _v_center_dis[6],
	//	double _hdm_1_width,
	//	double _hdm_1_a_hen,
	//	double _hdm_1_d_luo,
	//	double _hdm_2_width,
	//	double _hdm_2_a_hen,
	//	double _hdm_2_d_luo,
	//	double _hdm_3_width,
	//	double _hdm_3_a_hen,
	//	double _hdm_3_d_luo
	//)
	//	:
	//	D(_D_qiu),
	//	ang_die(_ang_die),
	//	ang_luo(_ang_luo),
	//	ren_count(_ren_count),
	//	is_dengfen(_is_dengfen),
	//	//   v_no_dengfen_angle(_v_no_dengfen_angle),
	//	   //v_pianxin_dis(),
	//	   //v_center_dis(),
	//	hdm_1_width(_hdm_1_width),
	//	hdm_1_a_hen(_hdm_1_a_hen),
	//	hdm_1_d_luo(_hdm_1_d_luo),
	//	hdm_2_width(_hdm_2_width),
	//	hdm_2_a_hen(_hdm_2_a_hen),
	//	hdm_2_d_luo(_hdm_2_d_luo),
	//	hdm_3_width(_hdm_3_width),
	//	hdm_3_a_hen(_hdm_3_a_hen),
	//	hdm_3_d_luo(_hdm_3_d_luo)
	//{
	//	std::copy(_v_no_dengfen_angle, _v_no_dengfen_angle + 6, v_no_dengfen_angle.begin());
	//	std::copy(_v_pianxin_dis, _v_pianxin_dis + 6, v_pianxin_dis.begin());
	//	std::copy(_v_center_dis, _v_center_dis + 6, v_center_dis.begin());
	//}
};

class Prog_Manager_API CanShu_Geo_R
	
{
public:
	CanShu_Geo_R();

public:
	double D;	//柱直径
	double ang_die;	//蝶形角
	double ang_luo;	//螺旋角
	double len_ren;	//刃的轴线长度
	double len_all;	//工件长度

	double R_qiu;	//圆角半径
	//double ang_in; //圆角截面从90度往回转中心的角度
	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离
	//std::array<double, 6> v_no_dengfen_angle;
	//std::array<double, 6> v_pianxin_dis;
	//std::array<double, 6> v_center_dis;
#pragma region 三组后角
	//三个后角-三组（顶点，螺旋起点，螺旋部分）
public:
	double hdm_1_width;	//后刀面1宽度
	double hdm_1_a_hen;	//横刃轴向
	double hdm_1_d_rrr; //圆角径向
	double hdm_1_d_luo;
public:
	double hdm_2_width;	//后刀面2宽度
	double hdm_2_a_hen;	//横刃轴向
	double hdm_2_d_rrr; //圆角径向
	double hdm_2_d_luo;
public:
	double hdm_3_width;	//后刀面3宽度
	double hdm_3_a_hen;	//横刃轴向
	double hdm_3_d_rrr; //圆角径向
	double hdm_3_d_luo;
#pragma endregion
public:
	/*template <class Archive>
	void serialize(Archive& ar) {
		ar(
			D_qiu,
			ang_die,
			ang_luo,
			R_qiu,
			ren_count,
			is_dengfen,
			v_no_dengfen_angle,
			v_pianxin_dis,
			v_center_dis,
			hdm_1_width,
			hdm_1_a_hen,
			hdm_1_d_rrr,
			hdm_1_d_luo,
			hdm_2_width,
			hdm_2_a_hen,
			hdm_2_d_rrr,
			hdm_2_d_luo,
			hdm_3_width,
			hdm_3_a_hen,
			hdm_3_d_rrr,
			hdm_3_d_luo
		);
	}
	CanShu_Geo_R() = default;
	CanShu_Geo_R(
		double _D_qiu,
		double _ang_die,
		double _ang_luo,
		double _R_qiu,
		int    _ren_count,
		bool   _is_dengfen,
		const double _v_no_dengfen_angle[6],
		const double _v_pianxin_dis[6],
		const double _v_center_dis[6],
		double _hdm_1_width,
		double _hdm_1_a_hen,
		double _hdm_1_d_rrr,
		double _hdm_1_d_luo,
		double _hdm_2_width,
		double _hdm_2_a_hen,
		double _hdm_2_d_rrr,
		double _hdm_2_d_luo,
		double _hdm_3_width,
		double _hdm_3_a_hen,
		double _hdm_3_d_rrr,
		double _hdm_3_d_luo
	)
		:
		D(_D_qiu),
		ang_die(_ang_die),
		ang_luo(_ang_luo),
		R_qiu(_R_qiu),
		ren_count(_ren_count),
		is_dengfen(_is_dengfen),
		hdm_1_width(_hdm_1_width),
		hdm_1_a_hen(_hdm_1_a_hen),
		hdm_1_d_rrr(_hdm_1_d_rrr),
		hdm_1_d_luo(_hdm_1_d_luo),
		hdm_2_width(_hdm_2_width),
		hdm_2_a_hen(_hdm_2_a_hen),
		hdm_2_d_rrr(_hdm_2_d_rrr),
		hdm_2_d_luo(_hdm_2_d_luo),
		hdm_3_width(_hdm_3_width),
		hdm_3_a_hen(_hdm_3_a_hen),
		hdm_3_d_rrr(_hdm_3_d_rrr),
		hdm_3_d_luo(_hdm_3_d_luo)
	{
		std::copy(_v_no_dengfen_angle, _v_no_dengfen_angle + 6, v_no_dengfen_angle.begin());
		std::copy(_v_pianxin_dis, _v_pianxin_dis + 6, v_pianxin_dis.begin());
		std::copy(_v_center_dis, _v_center_dis + 6, v_center_dis.begin());
	}*/
};

//成型铣刀几何参数
//设置：形状、后角、螺旋、端齿、棒料
class Prog_Manager_API CanShu_Geo_CX
{
public:
	//整体尺寸
	//CanShu_BangLiao canshu_bl; //棒料
	int type; //0-参数，1-型线

	double cx_D;
	double cx_len;
	double cx_zhui;

	int cx_sel_xx_id;
	int cx_is_max_ring; //型线最大环：0-原始、1-圆柱

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离

public:
	CanShu_Geo_CX();
};

#pragma pack(pop) 