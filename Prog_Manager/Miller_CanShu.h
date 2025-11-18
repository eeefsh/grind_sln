#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
//#include"manager_h/xt_armadillo_settings.h"
#include"manager_h/MA_010601_Cal_JiHe_PointSort.h"
#include<vector>
using namespace std;

class CanShu_shalun_cal_DL;
class CanShu_SuDu;
class CanShu_Angle_Qian;
class CanShu_Angle_Hou;

class CanShu_Angle_Hou
{
public:
	double a;
	int count_dxf__xx;
	int count_houjiao;
	int count_luoxuan;
};

#pragma pack(push, 8)
//锥度球头铣刀公共参数
class Prog_Manager_API CanShu_ZQ_GongGong
{
	//整体尺寸
public:
	double len_all;	//总长
	double len_ren;	//刃长
	double D_bing;	//柄径
	double D_qiu;	//球头直径 or 柱直径

	//球头部分
public:
	double ang_start_zhuan;	//球头起始转角
	double ang_start_qing;	//球头起始倾角
	double ang_start_luo;	//球头起始螺旋角

	double ang_end_zhuan;	//球头结束转角
	double ang_end_qing;	//球头结束倾角
	double ang_end_luo;		//球头结束螺旋角

	//锥面部分
public:
	double ang_zhui;	//半锥角
	double ang_luoxuan;	//等螺旋角
	double ang_bing;	//柄径过度角

	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;
	//vector<double> v_no_dengfen_angle; //不等分对应刃的角度值
	//vector<double> v_pianxin_dis;
	//vector<double> v_center_dis; //到中心距离

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离


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



	//*****************数据存储分界线**********************//

public:
	void set_CanShu(double in_len_all, double in_len_ren, double in_D_bing,
		double in_D_qiu, double in_ang_start_zhuan, double in_ang_start_qing, double in_ang_start_luo,
		double in_ang_end_zhuan, double in_ang_end_qing, double in_ang_end_luo,
		double in_ang_zhui, double in_ang_luoxuan, double in_ang_bing);

	//空间位置
public:
	mat33 SYS;
	vec3 O;

public:

	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();

public:
	CanShu_ZQ_GongGong();
	~CanShu_ZQ_GongGong();

};
#pragma pack(pop)

//平底铣刀公共参数
class Prog_Manager_API CanShu_PD_GongGong
{
	//整体尺寸
public:
	double len_all;	//总长
	double len_ren;	//刃长
	double D_bing;	//柄径

	//平底部分
public:
	double D_qiu;	// 柱直径
	double ang_die;	//蝶形角
	double ang_luo;	//螺旋角

	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离

	//double v_dis_center_dcc[6]; //起点到中心距离
	//double v_ang_up_dcc[6]; //槽顶角度


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
	//*****************数据存储分界线**********************//

	//空间位置
public:
	mat33 SYS;
	vec3 O;

public:

	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();

public:
	CanShu_PD_GongGong();
	~CanShu_PD_GongGong();

};

//圆角R铣刀公共参数
class Prog_Manager_API CanShu_R_GongGong
{
	//整体尺寸
public:
	double len_all;	//总长
	double len_ren;	//刃长
	double D_bing;	//柄径

public:
	double D_qiu;	//柱直径
	double ang_die;	//蝶形角
	double ang_luo;	//螺旋角

	double R_qiu;	//圆角半径
	//double ang_in; //圆角截面从90度往回转中心的角度
	//刃相关
public:
	int ren_count; //刃的个数，通常为2,3,4,6
	bool is_dengfen;

	double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	double v_pianxin_dis[6];
	double v_center_dis[6]; //到中心距离

#pragma region 三组后角
	//三个后角-三组（顶点，螺旋起点，螺旋部分）
public:
	double hdm_1_width;	//后刀面1宽度
	double hdm_1_a_hen;	//横刃轴向
	double hdm_1_d_luo;
public:
	double hdm_2_width;	//后刀面2宽度
	double hdm_2_a_hen;	//横刃轴向
	double hdm_2_d_luo;
	//public:
	//	double hdm_3_width;	//后刀面3宽度
	//	double hdm_3_a_hen;	//横刃轴向
	//	double hdm_3_d_rrr; //圆角上端
	//	double hdm_3_a_rrr;
	//	double hdm_3_d_luo;
#pragma endregion

	//*****************数据存储分界线**********************//

	//空间位置
public:
	mat33 SYS;
	vec3 O;

public:

	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();

public:
	CanShu_R_GongGong();
	~CanShu_R_GongGong();

};

//成型铣刀公共参数
class Prog_Manager_API CanShu_CX_GongGong
{
#pragma region 棒料
	//整体尺寸
public:
	double len_all;	//总长
	double len_ren;	//刃长
	double D_bing;	//柄径

	double bangliao_D;
	double bangliao_len;
	double bangliao_zhui;

	int bangliao_sel_xx_index;
	int bangliao_is_max_ring; //型线最大环：0-原始、1-圆柱
#pragma endregion
	//刃相关
public:
	int v_sel_dxf_pos[30]; //一个刃对应文件存放的位置-对应目录4.8
	//int ren_count; //刃的个数，通常为2,3,4,6
	//bool is_dengfen;

	//double v_no_dengfen_angle[6]; //不等分对应刃的角度值
	//double v_pianxin_dis[6];
	//double v_center_dis[6]; //到中心距离
	//int v_cur_ang_pos_to_dxf_index[30];  //当前角度位置关联的型线索引25.4.2

	//型线参数
public:
	int cai_type;	//采样类型.0:长度，1：长度+角度
	double cai_len;	//采样长度
	double cai_ang;	//采样角度

#pragma region 螺旋参数
	//螺旋参数
public:
	//int type_cao;  //0：转角+倾角、1：偏心+倾角、2：螺旋角、3：导程
	//double ang_zhuan;	//转角 型线点相位为0，绕回转轴转
	//double ang_qing;	//倾角
	//double dis_pian;	//偏心距
	//double ang_luo;		//螺旋角
	//double daocheng;	//导程

	int v_type_cao[30];
	double v_ang_zhuan[30];
	double v_ang_qing[30];
	double v_dis_pian[30];
	double v_ang_luo[30];
	double v_daocheng[30];
	int v_canshu_or_xingxian[30]; //螺旋的性状是：0-参数、1-型线
	double v_canshu_D[30];
	double v_canshu_len[30];
	double v_canshu_zhui[30];
	int v_luoxuan_sel_xx_index[30];

	//CanShu_Angle_Hou v_gx_arr[30];

	int v_budengfen_count[30];
#pragma endregion

	double vv_ren_pos_ang[30][6]; //每个螺旋分度对应点的刃位置角度4.21

public:
	//记录dxf型线，后角，螺旋添加数量的-4.11-	//添加+1，删除-1
	int count_dxf__xx;
	int count_houjiao;
	int count_luoxuan;

#pragma region 三组后角
	//三个后角-三组（顶点，螺旋起点，螺旋结束）
public:
	double v_hdm_1_width[30];	//后刀面1宽度
	double v_hdm_1_a_luo[30];
	double v_hdm_1_d_luo[30];
	double v_hdm_2_width[30];	//后刀面2宽度
	double v_hdm_2_a_luo[30];
	double v_hdm_2_d_luo[30];
	double v_hdm_3_width[30];	//后刀面2宽度
	double v_hdm_3_a_luo[30];
	double v_hdm_3_d_luo[30];
	int v_houjiao_sel_xx_index[30];

#pragma endregion


	//*****************数据存储分界线**********************//

	//空间位置
public:
	mat33 SYS;
	vec3 O;
public:

	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();

public:
	CanShu_CX_GongGong();
	~CanShu_CX_GongGong();

};

//锥度球头-球头部分前刀面参数
class Prog_Manager_API CanShu_ZQ_QDM
{
public:
	int selected_ren[6];
	double angle_buchang;
	//球头刃
public:  //刀尖到螺旋起点
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 
	double ang_to_end;	//到螺旋起点角度
	double dis_end_extend;	//结束延长距离


	//前角控制-三个点位控制前角的变化
	int type;//前角类型
	double ang_n1;//法1
	double ang_n2;//法2
	double ang_n3;//法3

	//芯厚线
	double deep_qie;	//顶端切入深度
	double angle_up;	//顶部角度--与xy平面的夹角 --刃线
	double jin_percent_r;		//起始处半径比值
	double angle_jin;	//起始进线角度 ---刃线 与x轴夹角

	double angle_qiexue;	//切削角度

	double angle_hen_tui;	//横向退刀
public:
	CanShu_ZQ_QDM();
	~CanShu_ZQ_QDM();

	void set_CanShu(double in_pian, double in_end_bi, double in_end_dis, double in_start_bi, double in_start_dis,
		int in_type, double in_ang1, double in_ang2, double in_ang3,
		double in_deep, double in_ang_up, double in_r_bi, double ang_end,
		double in_ang_qie);
public:
	//通过vector设置参数 7.18 
	void set_canshu(vector<double>& v_canshu);
	void get_canshu(vector<double>& v_canshu);
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//锥度球头-螺旋槽参数
class Prog_Manager_API Canshu_ZQ_LXC
{
public:
	//选择加工的刃、最多6个
	int selected_ren[6];	//在对应位置赋值为1
	double angle_buchang;
	//螺旋刃
public:
	double dis_start_extend;//起始延长距离
	double dis_end_extend;	//结束延长距离

	//前角控制-固定值
	int type;//前角类型-0法向、1径向
	double ang_n1;//法1
	double ang_d; //径向前角

	//芯厚- ???6.13 芯厚设置作为一个对话框
	int type_xinhou;	//0等芯厚、1等比芯厚、2变芯厚
	double angle_wy_deng;	//等芯厚位移角度
	double percent_r;	//等比芯厚
	double angle_wy_start;	//变芯厚位起始移角度
	double angle_wy_end;	//变芯厚位结束移角度--线性

	double angle_qiexue;	//切削角度

public:
	Canshu_ZQ_LXC();
	~Canshu_ZQ_LXC();
public:
	//通过vector设置参数 7.18 
	void set_canshu(vector<double>& v_canshu);
	void get_canshu(vector<double>& v_canshu);
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//锥度球头铣刀-第一后刀面参数
class Prog_Manager_API Canshu_ZQ_HDM_1
{
public:
	int selected_ren[6];
	double angle_buchang;
	//球头刃
public:
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 

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
	Canshu_ZQ_HDM_1();
	~Canshu_ZQ_HDM_1();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//锥度球头铣刀-第二后刀面参数
class Prog_Manager_API Canshu_ZQ_HDM_2
{
public:
	int selected_ren[6];
	double angle_buchang;
	//球头刃
public:
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 

	double angle_qiexue_qiu;	//切削角度
	double angle_wy_qiu;	//位移角度- 后刀面法向正转为正

	//球头刃磨后刀面所需插值的切削，位移
public:
	double pos_percent; //插值点的位置
	double angle_qiexue_qiu2;	//切削角度
	double angle_wy_qiu2;	//位移角度
	//螺旋刃
public:
	double dis_end_extend;	//结束延长距离

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度

public:
	Canshu_ZQ_HDM_2();
	~Canshu_ZQ_HDM_2();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//锥度球头铣刀-第三后刀面参数
class Prog_Manager_API Canshu_ZQ_HDM_3
{
public:
	int selected_ren[6];
	double angle_buchang;
	//球头刃
public:
	//从球头前刀面参数继承过来，其他控制的默认设计，不给用户输入
	double angle_qiexue_qiu;	//切削角度
	double angle_wy_qiu;	//位移角度
	//球头刃磨后刀面所需插值的切削，位移
public:
	double pos_percent; //插值点的位置
	double angle_qiexue_qiu2;	//切削角度
	double angle_wy_qiu2;	//位移角度
	//螺旋刃
public:
	double extend_end;	//结束延长距离

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度

public:
	Canshu_ZQ_HDM_3();
	~Canshu_ZQ_HDM_3();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//锥度球头铣刀-刀体间隙参数--待定
class Prog_Manager_API CanShu_ZQ_DaoTiJianXi
{
public:
	int selected_ren[6];
	double angle_buchang;


public:
	CanShu_ZQ_DaoTiJianXi();
	~CanShu_ZQ_DaoTiJianXi();
public:
};

//锥度球头铣刀-刀尖体间隙参数--待定
class Prog_Manager_API CanShu_ZQ_DaoJianJianXi
{
public:
	int selected_ren[6];
	double angle_buchang;

	//刀尖间隙所需参数 12.23放到工序中
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
	CanShu_ZQ_DaoJianJianXi();
	~CanShu_ZQ_DaoJianJianXi();
public:

};

//锥度球头铣刀-刀尖分屑槽参数--待定
class Prog_Manager_API CanShu_ZQ_DaoJianFenXieCao
{

public:
	CanShu_ZQ_DaoJianFenXieCao();
	~CanShu_ZQ_DaoJianFenXieCao();
};

//平底铣刀端齿容屑槽参数
class Prog_Manager_API CanShu_PD_DCC
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	double dis_center;		//槽顶到中心距离
	double ang_caoding;	//槽顶角度

	//前角控制-三个点位控制前角的变化
	double type;//前角类型
	double ang_n1;//法1
	//double ang_n2;//法2
	//double ang_n3;//法3

	double angle_heng_tui;	//横向退刀
	double dis_end_extend;

	double angle_qiexue;	//切削角度

public:
	CanShu_PD_DCC();
	~CanShu_PD_DCC();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀端第一端后刀面参数
class Prog_Manager_API CanShu_PD_DHDM_1
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//double type;//后角类型--只有轴向角
	//double ang_a1;//轴1
	//double ang_a2;//轴2
	//double ang_a3;//轴3

	double angle_qiexue;	//切削角度
	double angle_wy_luo;	//位移角度
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 

public:
	CanShu_PD_DHDM_1();
	~CanShu_PD_DHDM_1();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀端第二端后刀面参数
class Prog_Manager_API CanShu_PD_DHDM_2
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//double type;//后角类型--只有轴向角
	//double ang_a1;//轴1
	//double ang_a2;//轴2
	//double ang_a3;//轴3

	double angle_qiexue;	//切削角度
	double angle_wy_luo;	//位移角度
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离

public:
	CanShu_PD_DHDM_2();
	~CanShu_PD_DHDM_2();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀端第三端后刀面参数
class Prog_Manager_API CanShu_PD_DHDM_3
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//double type;//后角类型--只有轴向角
	double ang_a1;//轴1
	//double ang_a2;//轴2
	//double ang_a3;//轴3

	double angle_qiexue;	//切削角度

public:
	CanShu_PD_DHDM_3();
	~CanShu_PD_DHDM_3();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀螺旋槽参数
class Prog_Manager_API CanShu_PD_LXC
{
public:
	//选择加工的刃、最多6个
	int selected_ren[6];	//在对应位置赋值为1
	double angle_buchang;
	//螺旋刃
public:
	double extend_start;//起始延长距离
	double extend_end;	//结束延长距离

	//前角控制-固定值
	int type;//前角类型
	double ang_n1;//法1
	double ang_d;//径向

	int type_xinhou;	//0等芯厚、1等比芯厚、2变芯厚
	double angle_wy_deng;	//等芯厚位移角度
	double percent_r;	//等比芯厚
	double angle_wy_start;	//变芯厚位起始移角度
	double angle_wy_end;	//变芯厚位结束移角度--线性

	double angle_qiexue;	//切削角度

public:
	CanShu_PD_LXC();
	~CanShu_PD_LXC();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀第一后刀面参数-柱面
class Prog_Manager_API CanShu_PD_HDM_1
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//后角控制
	//int type_luo;//后角类型
	//double ang_n_luo;//法1
	//double ang_d_luo;//径向后角

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度
public:
	CanShu_PD_HDM_1();
	~CanShu_PD_HDM_1();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀第二后刀面参数
class Prog_Manager_API CanShu_PD_HDM_2
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//后角控制
	//int type_luo;//后角类型
	//double ang_n_luo;//法1
	//double ang_d_luo;//径向后角+轴向后角-定

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度

public:
	CanShu_PD_HDM_2();
	~CanShu_PD_HDM_2();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀第三后刀面参数
class Prog_Manager_API CanShu_PD_HDM_3
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//后角控制
	//int type_luo;//后角类型
	//double ang_n_luo;//法1
	//double ang_d_luo;//径向后角+轴向后角-定

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度

public:
	CanShu_PD_HDM_3();
	~CanShu_PD_HDM_3();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//平底铣刀刀体间隙参数--12.23 同理锥球刀尖间隙
class Prog_Manager_API CanShu_PD_DaoTiJianXi
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	double dtjx_dis_center; //起点到中心距离
	double dtjx_ang_up; //起点与x轴夹角，在下为正
	double dtjx_ang_x; //中间点平移到原点绕基本轴旋转
	double dtjx_ang_y;
	double dtjx_ang_z;
	double dtjx_pianzhi_x; //刀尖间隙圆弧球心偏置距离
	double dtjx_pianzhi_y;
	double dtjx_pianzhi_z;
public:
	CanShu_PD_DaoTiJianXi();
	~CanShu_PD_DaoTiJianXi();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀圆角前刀面参数
class Prog_Manager_API CanShu_R_QDM_R
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	//double R;		//槽顶到中心距离
	//前角控制-三个点位控制前角的变化
	double type;//前角类型
	double ang_n1;//法1

	double angle_qiexue;	//切削角度

public:
	CanShu_R_QDM_R();
	~CanShu_R_QDM_R();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀第一后刀面参数
class Prog_Manager_API CanShu_R_HDM_1
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	double angle_qx_hen;	//切削角度
	double angle_wy_hen;	//位移角度
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 

	double angle_qx_rrr;	//切削角度
	double angle_wy_rrr;	//位移角度

	double angle_qx_luo;	//切削角度
	double angle_wy_luo;	//位移角度


public:
	CanShu_R_HDM_1();
	~CanShu_R_HDM_1();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀第二后刀面参数
class Prog_Manager_API CanShu_R_HDM_2
{
public:
	int selected_ren[6];
	double angle_buchang;

public:
	double angle_qx_hen;	//切削角度
	double angle_wy_hen;	//位移角度
	double dis_to_center;	//到中心距离 
	double dis_start_extend;	//开始延长距离 

	double angle_qx_rrr;	//切削角度
	double angle_wy_rrr;	//位移角度

	double angle_qx_luo;	//切削角度
	double angle_wy_luo;	//位移角度


public:
	CanShu_R_HDM_2();
	~CanShu_R_HDM_2();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀第三后刀面参数
class Prog_Manager_API CanShu_R_HDM_3
{
public:
	double extend_start;//起始延长距离
	double extend_end;	//结束延长距离

	//后角控制
	int type_luo;//后角类型
	bool is_ding_luo;//固定值
	double ang_n1_luo;//法1
	double ang_n2_luo;//法2
	double ang_d_luo;//径向后角+轴向后角-定
	double ang_a_luo;

	double angle_qiexue_luo;	//切削角度
	double angle_wy_luo;	//位移角度


public:
	CanShu_R_HDM_3();
	~CanShu_R_HDM_3();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀螺旋槽参数
class Prog_Manager_API CanShu_R_LXC
{
public:
	//选择加工的刃、最多6个
	int selected_ren[6];	//在对应位置赋值为1
	double angle_buchang;
	//螺旋刃
public:
	double extend_start;//起始延长距离
	double extend_end;	//结束延长距离

	//前角控制-固定值
	int type;//前角类型
	double ang_n1;//法1
	double ang_d;//径向

	int type_xinhou;	//0等芯厚、1等比芯厚、2变芯厚
	double angle_wy_deng;	//等芯厚位移角度
	double percent_r;	//等比芯厚
	double angle_wy_start;	//变芯厚位起始移角度
	double angle_wy_end;	//变芯厚位结束移角度--线性

	double angle_qiexue;	//切削角度

public:
	CanShu_R_LXC();
	~CanShu_R_LXC();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀刀体间隙参数--待定
class Prog_Manager_API CanShu_R_DaoTiJianXi
{
public:
	double pianxin;		//偏心距
	double ang_caodi;	//槽底角度

	//前角控制-三个点位控制前角的变化
	double type;//前角类型
	double ang_n1;//法1
	double ang_n2;//法2
	double ang_n3;//法3

	double angle_qiexue;	//切削角度

public:
	CanShu_R_DaoTiJianXi();
	~CanShu_R_DaoTiJianXi();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀刀尖间隙参数--待定
class Prog_Manager_API CanShu_R_DaoJianJianXi
{
public:
	double pianxin;		//偏心距
	double ang_caodi;	//槽底角度

	//前角控制-三个点位控制前角的变化
	double type;//前角类型
	double ang_n1;//法1
	double ang_n2;//法2
	double ang_n3;//法3

	double angle_qiexue;	//切削角度

public:
	CanShu_R_DaoJianJianXi();
	~CanShu_R_DaoJianJianXi();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//圆角R铣刀刀尖分屑槽参数
class Prog_Manager_API CanShu_R_DaoJianFenXieCao
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	double dis_center;		//槽顶到中心距离
	double ang_caoding;	//槽顶角度

	//前角控制-三个点位控制前角的变化
	int type;//前角类型
	double ang_n1;//法1
	//double ang_n2;//法2
	//double ang_n3;//法3

	double angle_heng_tui;	//横向退刀
	double dis_end_extend;

	double angle_qiexue;	//切削角度

public:
	CanShu_R_DaoJianFenXieCao();
	~CanShu_R_DaoJianFenXieCao();
public:
	//返回当前工序参数类参数个数，修改参数后要修改返回值 7.18 mark
	int get_canshu_count();
};

//成型刀开槽参数
class Prog_Manager_API CanShu_GX_CX_KaiCao
{
public:
	//选择加工的刃、最多6个
	int selected_ren[6];	//在对应位置赋值为1
	double angle_buchang;

public:
	double extend_start;//起始延长距离
	double extend_end;	//结束延长距离

	//前角控制-固定值
	int type;//前角类型 0法、1径
	double ang_n1;//法
	double ang_d;//径向

	int type_xinhou;	//0等芯厚、1等比芯厚、2变芯厚
	double angle_wy_deng;	//等芯厚位移角度
	double percent_r;	//等比芯厚
	double angle_wy_start;	//变芯厚位起始移角度
	double angle_wy_end;	//变芯厚位结束移角度--线性

	double angle_qiexue;	//切削角度
public:
	int sel_luoxuan_index;  //选择的螺旋
	//int sel_xingxian_index; // 选择的型线 4.8 4.18l螺旋已经选择型线

public:
	CanShu_GX_CX_KaiCao();
	~CanShu_GX_CX_KaiCao();

};

//成型刀后刀面1参数
class Prog_Manager_API CanShu_GX_CX_HDM_1
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	int fangfa; //方法0：切削+位移。1：转动+位移，2：转动+摆动
	double angle_qiexue;	//切削角度
	double angle_wy;	//位移角度
	double angle_zhuan;
	double angle_baidong;

	double dis_start_extend;//到中心距离
	double dis_end_extend;//开始延长距离 

public:
	int sel_luoxuan_index;  //选择的螺旋
	//int sel_xingxian_index;
	int sel_houjiao_index; // 选择的后角

public:
	CanShu_GX_CX_HDM_1();
	~CanShu_GX_CX_HDM_1();
};

//成型刀后刀面2参数
class Prog_Manager_API CanShu_GX_CX_HDM_2
{
public:
	int selected_ren[6];
	double angle_buchang;
public:
	int fangfa; //方法0：切削+位移。1：转动+位移，2：转动+摆动
	double angle_qiexue;	//切削角度
	double angle_wy;	//位移角度
	double angle_zhuan;
	double angle_baidong;

	double dis_start_extend;//到中心距离
	double dis_end_extend;//开始延长距离 

public:
	int sel_luoxuan_index;  //选择的螺旋
	//int sel_xingxian_index;
	int sel_houjiao_index; // 选择的后角

public:
	CanShu_GX_CX_HDM_2();
	~CanShu_GX_CX_HDM_2();
};

//计算刀路所需砂轮数据
class Prog_Manager_API CanShu_shalun_cal_DL
{
public:
	double D;  //直径，外轮廓刀回转中心
	double R;	//圆角
	double L;	//法兰长度，圆角处圆心与回转轴的交点为起点

public:
	CanShu_shalun_cal_DL();
	~CanShu_shalun_cal_DL();
	void set_CanShu(double in_d, double in_r, double in_l);
};

//磨削速度参数
class Prog_Manager_API CanShu_SuDu
{
public:
	double SL_XianSuDu;	//砂轮线速度
	double MoXueJinGei;	//磨削进给
	double JinDao;	//进刀
	double TuiDao;	//退刀
	double JieJin;	//接近
	double YuanLi;	//远离
	double KuaiSu;	//快速
public:
	CanShu_SuDu();
	~CanShu_SuDu();
	void set_CanShu();
private:

};













