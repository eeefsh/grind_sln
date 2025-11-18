#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include<vector>
#include"TooL_canshu_2.h"

using namespace std;


//工序可以访问到刀
//其他参数从刀具几何参数获得


#pragma pack(push, 8)
//#pragma pack(pop) 

class Prog_Manager_API CanShu_GX_KaiCao
	:public save_lib

{
public:
	CanShu_GX_KaiCao();
	~CanShu_GX_KaiCao();
private:
	int pos_ang_qian;
public:
	int guanlian_lx_id;
	CanShu_QianJiao ang_qian;

public:
	int selected_ren[6];	//在对应位置赋值为1
	//芯厚- 
	//int type_xinhou;	//0等比芯厚、1变比芯厚
	double percent_start;//起始芯厚比（半径） 
	double percent_end;

public:
	//double angle_qiexue;	//切削角度 放在磨削方法里，删除 7.15 
public:
	int save(int pos);
	void load(int pos);

};

class Prog_Manager_API CanShu_GX_LXC
	:public save_lib
{
public:
	CanShu_GX_LXC();
	~CanShu_GX_LXC();
public:
	int selected_ren[6];	//在对应位置赋值为1
	//前角控制-固定值
	double ang_d; //径向前角

	//芯厚- 
	//int type_xinhou;	//0等比芯厚、1变比芯厚
	double percent_start;//起始芯厚比（半径） 
	double percent_end;

	//double angle_qiexue;	//切削角度
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(ang_d,
	//		type_xinhou,
	//		percent_start,
	//		percent_end,
	//		angle_qiexue,
	//		);
	//}
	//CanShu_GX_LXC() = default;
	//CanShu_GX_LXC(
	//	double _ang_d,
	//	int    _type_xinhou,
	//	double _percent_start,
	//	double _percent_end,
	//	double _angle_qiexue
	//)
	//	:
	//	ang_d(_ang_d),
	//	type_xinhou(_type_xinhou),
	//	percent_start(_percent_start),
	//	percent_end(_percent_end),
	//	angle_qiexue(_angle_qiexue)
	//{}
public:
	int save(int pos);
	void load(int pos);


};

class Prog_Manager_API CanShu_GX_DCC_qiu
	:public save_lib
{
public:
	CanShu_GX_DCC_qiu();
	~CanShu_GX_DCC_qiu();
private:
	int pos_b_qianjiao_n;
	//球头刃
public:
	int selected_ren[6];	//在对应位置赋值为1
	//double dis_to_center;	//到中心距离 
	//double dis_end_extend;	//结束延长距离

	//前角控制-多个点位控制前角的变化
	 //刀尖到螺旋起点
public:
	//int type;//前角类型 -默认法向
	CanShu_Bian b_qianjiao_n;
	//double ang_n;

	//芯厚线
	double high_up_o;	  //芯厚圆心上偏高度
	double ang_up;	      //顶部角度--与x轴夹角
	double percent_r;		//起始处半径比值
	double ang_down;	  //柱面出线角度 与x轴夹角


	//double angle_qiexue;	//切削角度

	double ang_hen_tui;	//横向退刀
	double dis_hen_tui;	//横向退刀

public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_GX_DCC_ping
	:public save_lib
{
public:
	CanShu_GX_DCC_ping();
	~CanShu_GX_DCC_ping();
public:
	int selected_ren[6];	//在对应位置赋值为1
	//double dis_to_center;	//到中心距离 

public:
	//int type;//前角类型 -默认法向
	double ang_n;

	//芯厚线
	double high_down;	//芯厚线起点，端面沿轴向下降高度
	double ang_cao;	//与端平面夹角
public:
	//double angle_qiexue;	//切削角度

	double ang_hen_tui;	//横向退刀
	double dis_hen_tui;	//横向退刀距离
public:
	int save(int  pos);
	void load(int  pos);
};

//圆角前刀面
class Prog_Manager_API CanShu_GX_DCC_yuanjiao
	:public save_lib
{
public:
	CanShu_GX_DCC_yuanjiao();
	~CanShu_GX_DCC_yuanjiao();
public:
	int selected_ren[6];	//在对应位置赋值为1
	//int type;//前角类型 -默认法向
	double ang_n;
	//芯厚类似平底端齿槽，带角度的直线
public:
	double dis_to_center;	//交点到中心距离 
	double ang_cao;	//与端平面夹角
public:
	//double angle_qiexue;	//切削角度

public:
	int save(int pos);
	void load(int pos);
};


class Prog_Manager_API CanShu_GX_CX_HDM
	:public save_lib
{
public:
	CanShu_GX_CX_HDM();
	~CanShu_GX_CX_HDM();
public:
	int selected_ren[6];	//在对应位置赋值为1
	int guanlian_lx_id;
	int guanlian_hj_id;
	int sel_hdm_id; // 0、1、2

//public:
//	template <class Archive>
//	void serialize(Archive& ar) {
//		ar(
//			lx_id,
//			hj_id
//		);
//	}
//	CanShu_GX_CX_HDM() = default;
//	CanShu_GX_CX_HDM(
//		int _lx_id,
//		int _hj_id
//	)
//		:
//		lx_id(_lx_id),
//		hj_id(_hj_id)
//	{}
public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_GX_ZQ_HDM
	:public save_lib
{
public:
	CanShu_GX_ZQ_HDM();
	~CanShu_GX_ZQ_HDM();

public:
	int selected_ren[6];	//在对应位置赋值为1
	//选择磨削的第几后刀面
public:
	int sel_hdm_id; // 0、1、2

	//球头刃
public:
	double dis_to_center;	//到中心距离 

	double angle_qiexue_qiu;	//切削角度
	double angle_wy_qiu;	//位移角度- 后刀面法向正转为正

	//球头刃磨后刀面所需插值的切削，位移
public:
	double pos_percent; //插值点的位置
	double angle_qiexue_qiu2;	//切削角度
	double angle_wy_qiu2;	//位移角度

	//螺旋刃
public:
	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度

	double dis_end_extend;	//结束延长距离
public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_GX_PD_duan_HDM
	:public save_lib
{
public:
	CanShu_GX_PD_duan_HDM();
	~CanShu_GX_PD_duan_HDM();

public:
	int selected_ren[6];	//在对应位置赋值为1
	//选择磨削的第几后刀面
public:
	int sel_hdm_id; // 0. 1、2

public:
	double angle_qiexue;	//切削角度--在磨削方法中有设置？？
	double angle_wy_luo;	//位移角度
	double dis_to_center;	//到中心距离  
public:
	 int save(int pos);
	 void load(int pos);
};

class Prog_Manager_API CanShu_GX_PD_zhu_HDM
	:public save_lib
{
public:
	CanShu_GX_PD_zhu_HDM();
	~CanShu_GX_PD_zhu_HDM();
public:
	int selected_ren[6];	//在对应位置赋值为1
	//选择磨削的第几后刀面
public:
	int sel_hdm_id; //0、 1、2

public:
	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度
public:
	
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_GX_R_HDM
	:public save_lib
{
public:
	CanShu_GX_R_HDM();
	~CanShu_GX_R_HDM();
public:
	int selected_ren[6];	//在对应位置赋值为1
	//选择磨削的第几后刀面
public:
	int    sel_hdm_id; // 0、1、2、

	double dis_to_center;	//到中心距离 
public:
	double angle_qx_hen;	//切削角度
	double angle_wy_hen;	//位移角度

	double angle_qx_rrr;	//切削角度
	double angle_wy_rrr;	//位移角度

	double angle_qx_luo;	//切削角度
	double angle_wy_luo;	//位移角度

public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_GX_DJJX
	:public save_lib
{
public:
	CanShu_GX_DJJX();
	~CanShu_GX_DJJX();
public:
	int selected_ren[6];

public:
	double djjx_R; //圆弧半径
	double djjx_ang_up; //圆弧起点与x轴夹角
	double djjx_ang_down; //圆弧终点与z轴夹角

	double djjx_ang_x; //圆弧中间点平移到原点绕基本轴旋转
	double djjx_ang_y;
	double djjx_ang_z;

	double djjx_pianzhi_x; //刀尖间隙圆弧球心偏置距离
	double djjx_pianzhi_y;
	double djjx_pianzhi_z;

public:
	int save(int pos);
	void load(int pos);

};

class Prog_Manager_API CanShu_GX_KaiCao_2
	:public save_lib
{
public:
	CanShu_GX_KaiCao_2();
	~CanShu_GX_KaiCao_2();
private:
	int pos_ang_qian;
public:
	int guanlian_lx_id;
	CanShu_QianJiao ang_qian;

public:
	int selected_ren[6];	//在对应位置赋值为1

public:
	//芯厚参数，
	double start_len;
	double start_R;
	double end_len;
	double end_R;

	//芯厚- 回转芯厚不能过轴线
	int type_xinhou;	//0拉伸面、1回转面
	double len_lashen; //Z方向双向拉伸
	double len_huizhuan_pianyi; //回转轴偏移
	double ang_huizhuan; //回转角度双向

public:
	int save(int pos);
	void load(int pos);

};

class Prog_Manager_API XingCan_GX
{
public:
	//工序类型
	int gx_type;
public:
	CanShu_GX_KaiCao* can_kc;
	CanShu_GX_LXC* can_lxc;
	CanShu_GX_DCC_qiu* can_dcc_qiu;
	CanShu_GX_DCC_ping* can_dcc_ping;
	CanShu_GX_DCC_yuanjiao* can_dcc_yuan;
	CanShu_GX_CX_HDM* can_cx_hdm;
	CanShu_GX_ZQ_HDM* can_zq_hdm;
	CanShu_GX_PD_duan_HDM* can_pd_duan_hdm;
	CanShu_GX_PD_zhu_HDM* can_pd_zhu_hdm;
	CanShu_GX_R_HDM* can_r_hdm;
	CanShu_GX_DJJX* can_djjx;
	CanShu_GX_KaiCao_2* can_kc_2;

public:
	bool set_CanShu_GX_KaiCao(CanShu_GX_KaiCao& in_ptr);
	bool set_CanShu_GX_LXC(CanShu_GX_LXC& in_ptr);
	bool set_CanShu_GX_DCC_qiu(CanShu_GX_DCC_qiu& in_ptr);
	bool set_CanShu_GX_DCC_ping(CanShu_GX_DCC_ping& in_ptr);
	bool set_CanShu_GX_DCC_yuanjiao(CanShu_GX_DCC_yuanjiao& in_ptr);
	bool set_CanShu_GX_CX_HDM(CanShu_GX_CX_HDM& in_ptr);
	bool set_CanShu_GX_ZQ_HDM(CanShu_GX_ZQ_HDM& in_ptr);
	bool set_CanShu_GX_PD_duan_HDM(CanShu_GX_PD_duan_HDM& in_ptr);
	bool set_CanShu_GX_PD_zhu_HDM(CanShu_GX_PD_zhu_HDM& in_ptr);
	bool set_CanShu_GX_R_HDM(CanShu_GX_R_HDM& in_ptr);
	bool set_CanShu_GX_DJJX(CanShu_GX_DJJX& in_ptr);
	bool set_CanShu_GX_KaiCao_2(CanShu_GX_KaiCao_2& in_ptr);
public:
	XingCan_GX(); //后续加成员，要在内部初始化指针 mark
	~XingCan_GX();
	XingCan_GX(int in_type);

};

//#pragma pack(push, 8)
#pragma pack(pop) 