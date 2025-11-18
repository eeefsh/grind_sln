#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"KongJianXian.h"
//#include"manager_h/MA_010301_Cal_JiHe_ChaZhi.h"

//空间线生成器
//1、构造一个线生成器对象
//2、设置生成线的精度
//3、根据所需参数生成不同形状的空间线，ans_line
//4、编辑已有空间线，操作后得到新的线保存在ans_line
class Prog_Manager_API generator_line
{
//整体数据
private:
	//点之间间隔距离,默认= 0.04;
	double delta_dis ; 
//空间线
public:
	KongJianXian ans_line;	//生成和编辑线都会改变data，成为新的线

	//1、初始化构造
public:
	generator_line();
	~generator_line();

public:
	//2、设置点的间距
	void set_delta_dis(double in_dis); 
	double get_delta_dis();

//3、生成不同形状的空间线 
public:
	//生成平底端面刃直线 - 终点在z-方向（圆周指向轴心）
	//形状参数：铣刀半径、偏心距（回转中心到直线的距离）、蝶形角（端直线绕z轴回转形成的面 与 过回转轴及起点的交线，交线上以起点指向回转轴的短线 与 XY平面的夹角）
	//变换参数：空间线的位置变换
	void gen_duan_ren_line(double R, double pianxin, double die_ang,
		mat33 SYS, vec3 O);

	//生成圆角端面刃直线 - 终点在z-方向
	//形状参数：铣刀半径、偏心距（回转中心到直线的距离）、蝶形角、圆角半径
	//变换参数：空间线的位置变换
	void gen_duan_ren_line_R(double R, double ren_R, double pianxin, 
		double die_ang,
		mat33 SYS, vec3 O);

	//生成锥度螺旋等角线 --终点在回转轴上的距离，z+方向）-//螺旋角（右旋与回转轴夹角）
	//形状参数：小端半径、半锥度角、螺旋角、螺旋线z方向长度（
	//变换参数：空间线的位置变换
	void gen_luoxuan_ren_line(double R, double zhui_ang, double luo_ang, double z_lenth,
		double start_ang,
		mat33 SYS, vec3 O);

	//比正常螺旋线轴向短：ren_R
	void gen_luoxuan_ren_line_R(double R, double ren_R, double zhui_ang, double luo_ang, double z_lenth,
		double start_ang,
		mat33 SYS, vec3 O);

	//生成球面三次基本线 -（起点在刀尖，终点在柱面(锥度=0时)，锥度决定终点倾角及螺旋角（））
	//形状参数：球头半径、曲线凹凸性系数，起始螺旋角（刀尖=）、终点位置（倾角、螺旋角）
	//变换参数：空间线的位置变换
	//起点长度=0，结束点相位=0
	void gen_qiutou_ren_line(double R,  
		double xishu_aotu,double ang_zhui,double end_luo,
		mat33 SYS, vec3 O);

	//生成三次圆角轴心回转面基本线-（端面到柱面）
	//形状参数：铣刀半径、圆角半径
	//变换参数：空间线的位置变换
	//内部调用gen_rrr_by_hermite 
	void gen_R_ren_line(double R, double ren_R,
		double pianxin,double die_ang, double end_luo,
		mat33 SYS, vec3 O);
private:
	void gen_rrr_by_hermite(vec3 start_p,vec3 star_t,vec3 end_p,vec3 end_t,
		int num_p,
		mat33 SYS, vec3 O);

private:
	void correct_qiutouren(mat& ans_ren);

#pragma region MyRegion
	//编辑空间线接口
public:
	////将起点终点反向得到新的线
	//void fanxiang()
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	ls_data = ls_data.t(); //3*n

	//	ls_data = fliplr(ls_data);

	//	//mat ls_data2;
	//	//ls_data2.reset();
	//	//ls_data2.resize(3, 0);
	//	//ls_data2.insert_cols(0, ls_data.n_cols);
	//	//int index = 0;
	//	//for (int i = ls_data.n_cols - 1; i >= 0; i--)
	//	//{
	//	//	vec3 ls_p2 = ls_data.col(index);
	//	//	ls_data2.col(i) = ls_p2;
	//	//	index++;
	//	//}
	//	//vec3 ls_p2 = ls_data2.col(0);
	//	//vec3 ls_p3 = ls_data2.col(1);
	//	//vec3 ls_p4 = ls_data2.col(ls_data2.n_cols - 1);

	//	ans_line.init_data(ls_data);
	//}
	////将已有空间线，进行旋转
	//void rotate(mat33 SYS)
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	ls_data = ls_data.t();
	//	ls_data = SYS * ls_data;

	//	ans_line.init_data(ls_data);

	//}
	////将已有空间线，进行平移
	//void trans(vec3 O)
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	ls_data = ls_data.t();
	//	ls_data.each_col() += O;

	//	ans_line.init_data(ls_data);
	//}
	////截取线已有线的一段，输入截取起点终点（0-1]，得到新的线
	//void cutting(double start, double end)
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	int p_num = ls_data.n_rows;
	//	int start_index = p_num * start;
	//	int end_index = p_num * end;
	//	//切掉两头
	//	//ls_data.shed_rows(0,start_index);
	//	//ls_data.shed_rows(end_index - start_index, ls_data.n_rows - 1);
	//	ls_data.shed_rows(end_index - 1, ls_data.n_rows - 1);
	//	ls_data.shed_rows(0, start_index);

	//	//test
	//	//mat ans_p = ls_data;
	//	//ans_p.save(R"(test_qdm_8.13_cut.txt)", raw_ascii);

	//	ls_data = ls_data.t();
	//	ans_line.init_data(ls_data);
	//}
	////沿终点切向延伸指定距离
	//void extend_end(double add_dis)
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	int p_num = ls_data.n_rows;
	//	ls_data = ls_data.t();
	//	vec3 pend1 = ls_data.col(p_num - 1);
	//	vec3 pend2 = ls_data.col(p_num - 2);
	//	vec3 delta_qie = normalise(pend1 - pend2);

	//	int add_num = add_dis / delta_dis;
	//	ls_data.insert_rows(p_num - 1, add_num);
	//	for (int i = 0; i < add_num; i++)
	//	{
	//		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
	//		ls_data.row(p_num + i) = ls_p;
	//	}

	//	ls_data = ls_data.t();
	//	ans_line.init_data(ls_data);
	//}
	////沿起点切向延伸指定距离
	//void extend_start(double add_dis)
	//{
	//	mat ls_data = ans_line.get_all_p(); //n*3
	//	int p_num = ls_data.n_rows;
	//	ls_data = ls_data.t();
	//	vec3 pend1 = ls_data.col(0);
	//	vec3 pend2 = ls_data.col(1);
	//	vec3 delta_qie = normalise(pend1 - pend2);

	//	int add_num = add_dis / delta_dis;
	//	ls_data.insert_rows(p_num - 1, add_num);
	//	for (int i = 0; i < add_num; i++)
	//	{
	//		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
	//		ls_data.row(p_num + i) = ls_p;
	//	}

	//	ls_data = ls_data.t();
	//	ans_line.init_data(ls_data);
	//}
	////在当前线的末尾拼接上输入的线--
	////将线1的结束点去除，因为两线拼接有重点-24-9.24
	//void join_a_line(KongJianXian& in_line2)
	//{
	//	mat line1_data = ans_line.get_all_p(); //n*3
	//	mat line2_data = in_line2.get_all_p();

	//	line1_data.shed_row(line1_data.n_rows - 1);
	//	//join_cols() and join_vert(): vertical concatenation
	//	mat ls_data = join_cols(line1_data, line2_data);

	//	//test
	//	//mat ans_p = ls_data;
	//	//ans_p.save(R"(test_qdm_10.21.1_join.txt)", raw_ascii);

	//	ls_data = ls_data.t();
	//	ans_line.init_data(ls_data);
	//}
#pragma endregion

};

//class Prog_Manager_API CanShu_XingXian
//{
//public:
//	int input_type; //0-dxf，1-参数获得曲线
//
//	int sel_dxf_pos;
//
//	double start_R; //起始半径Z=0; 
//	double len;
//	double end_R; //若前端输入锥度，则转换为此表达形式
//public:
//	CanShu_XingXian();
//	~CanShu_XingXian();
//
//private:
//
//};
//
////螺旋相位canshu类：根据该类将型线转相位得到螺旋 2*n 长度+转角
//class Prog_Manager_API CanShu_LX_XiangWei
//{
//public:
//	int type_cao; //0：转角+倾角、1：偏心+倾角、2：螺旋角、3：导程
//	double ang_zhuan;	//转角 型线点相位为0，绕回转轴转
//	double ang_qing;	//倾角
//	double dis_pian;	//偏心距
//	double ang_luo;		//螺旋角
//	double daocheng;	//导程
//
//public:
//	//{长度，转角} 2*n 
//	mat Data_Of_XW;   //可以不要输出，螺旋根据参数计算对应相位
//
//public:
//	CanShu_LX_XiangWei();
//	~CanShu_LX_XiangWei();
//
//private:
//
//};
//
////前角类：前角类型，三组前角 
//class Prog_Manager_API CanShu_Qian_Angle
//{
//public:
//	int type_ang; //0-法向，1-径向
//	double ang_1;	//根据类型判断，径向法向都存
//	double ang_2;
//	double ang_3;
//
//public:
//	CanShu_Qian_Angle();
//	~CanShu_Qian_Angle();
//
//private:
//
//};
//
//class Prog_Manager_API CanShu_XinHouMian
//{
//public:
//	int type_mian; //0-平面，1-回转面
//	int input_type; //0-型线，1-参数控制
//	int sel_dxf_pos;
//
//	double beg_R; //起始半径Z=0; 
//	double len;
//	double end_R; //若前端输入锥度，则转换为此表达形式 
//public:
//	CanShu_XinHouMian();
//	~CanShu_XinHouMian();
//
//private:
//
//};
//
////工艺参数：
//class Prog_Manager_API CanShu_QDM_GongYi
//{
//public:
//	int type; //0-切削角度，1-槽宽
//	double ang_qiexue; //0-型线，1-参数控制
//	double cao_width;
//
//public:
//	CanShu_QDM_GongYi();
//	~CanShu_QDM_GongYi();
//
//private:
//
//};
//
//class Prog_Manager_API CanShu_HouJiao
//{
//public:
//	double hdm_1_width;	//后刀面1宽度
//	double hdm_1_a_luo;
//	double hdm_1_d_luo;
//	double hdm_2_width;	//后刀面2宽度
//	double hdm_2_a_luo;
//	double hdm_2_d_luo;
//	double hdm_3_width;	//后刀面2宽度
//	double hdm_3_a_luo;
//	double hdm_3_d_luo;
//public:
//	CanShu_HouJiao();
//	~CanShu_HouJiao();
//
//private:
//
//};
//
////后角补偿参数：百分比+补偿角度 2*n
//class Prog_Manager_API CanShu_HJ_BuChang
//{
//public:
//	mat canshu;
//public:
//	CanShu_HJ_BuChang();
//	~CanShu_HJ_BuChang();
//
//private:
//
//};
//
////后刀面磨削方法参数
//class Prog_Manager_API CanShu_HDM_FangFa
//{
//public:
//	//0-切削+位移,1-旋转+位移,2-摆动+位移,3-旋转+摆动
//	int type; 
//	double ang_QX;
//	double ang_WY;
//	double ang_XH;
//	double ang_BD;
//
//public:
//	CanShu_HDM_FangFa();
//	~CanShu_HDM_FangFa();
//
//private:
//
//};
//
//class Prog_Manager_API CanShu_BangLiao
//{
//public:
//	int type; //0-参数，1-型线
//
//	double bangliao_D;
//	double bangliao_len;
//	double bangliao_zhui;
//
//	int bangliao_sel_xx_index;
//	int bangliao_is_max_ring; //型线最大环：0-原始、1-圆柱
//
//public:
//	 CanShu_BangLiao();
//	~ CanShu_BangLiao();
//
//private:
//
//};
//
//class Prog_Manager_API CanShu_CaiYang
//{
//public:
//	int cai_type;	//采样类型.0:长度，1：长度+角度
//	
//	double cai_len;	//采样长度
//	double cai_ang;	//采样角度
//public:
//	CanShu_CaiYang();
//	~CanShu_CaiYang();
//
//private:
//
//};
//
//class Prog_Manager_API CanShu_FenDu
//{
//public:
//	double v_ang_pos[6];
//
//public:
//	 CanShu_FenDu();
//	~ CanShu_FenDu();
//
//private:
//
//};


