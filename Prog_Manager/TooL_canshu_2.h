#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include "manager_h/xt_armadillo_settings.h"
#include <array>

#include "Storage_manager.h"
class Storage_manager;
class save_lib;

#pragma pack(push, 8)
//#pragma pack(pop) 

//变化参数类 2*n
class Prog_Manager_API CanShu_Bian
	: public save_lib
{
public:
	mat canshu;
public:
	CanShu_Bian();
	CanShu_Bian(mat in_canshu);
	//返回元素个数
	int count_element();
	//获得长度百分比处的值
	double get(double percent);
	//插入和修改元素
	void insert_element(double percent, double value);
	//删除i位置元素
	void delete_element(int i);
public:
	//CanShu_Bian& operator=(const CanShu_Bian& rhs) {
	//	// 检查自赋值
	//	if (this != &rhs) {
	//		// 执行深拷贝
	//		this->canshu = rhs.canshu;  // 假设mat类已正确实现赋值操作
	//	}
	//	return *this;
	//}
public:
	int save();
	void load(int pos);
};

//变化参数类 3*n
class Prog_Manager_API CanShu_Bian_v3
	: public save_lib
{
public:
	mat canshu;
public:
	CanShu_Bian_v3();
	CanShu_Bian_v3(mat in_canshu);
	//返回元素个数
	int count_element();
	//获得长度百分比处的值
	vec3 get(double percent);
	//插入和修改元素
	void insert_element(double percent, vec value);
	//删除i位置元素
	void delete_element(int i);
public:
	//CanShu_Bian_v3& operator=(const CanShu_Bian_v3& rhs) {
	//	// 检查自赋值
	//	if (this != &rhs) {
	//		// 执行深拷贝
	//		this->canshu = rhs.canshu;  // 假设mat类已正确实现赋值操作
	//	}
	//	return *this;
	//}
public:
	int save();
	void load(int pos);
};

//变化参数类 4*n
class Prog_Manager_API CanShu_Bian_v4
	: public save_lib
{
public:
	mat canshu;
public:
	CanShu_Bian_v4();
	CanShu_Bian_v4(mat in_canshu);
	//返回元素个数
	int count_element();
	//获得长度百分比处的值
	vec get(double percent);
	//插入和修改元素
	void insert_element(double percent, vec value);
	//删除i位置元素
	void delete_element(int i);
public:
	//CanShu_Bian_v4& operator=(const CanShu_Bian_v4& rhs) {
	//	// 检查自赋值
	//	if (this != &rhs) {
	//		// 执行深拷贝
	//		this->canshu = rhs.canshu;  // 假设mat类已正确实现赋值操作
	//	}
	//	return *this;
	//}
public:
	int save();
	void load(int pos);
};

class Prog_Manager_API  CanShu_XingXian
	: public save_lib
{
	//型线参数：
	//	类型选择：
public:
	int input_type; //0-参数获得曲线 ,1-dxf，

	//	选择0 - 通过参数获得：
public:
	//	类型选择：

public:
	//参数型线类型-：0-锥面、1-球头、2-平底、3-圆角
	int type_shape;
	//	半锥角（直径变大为正）
	double ang_zhui;
	//	选择0.0 - 锥度线：
	//	轴向长度
	//	起点半径
	double len_0;
	double start_R_0;

	//	选择0.1 - 球头：
	//	轴向长度
	//	起点半径
	double len_1;
	double start_R_1;

	//	选择0.2- 平底：
	//	轴向长度
	//	起点半径
	double len_2;
	double start_R_2;
	double ang_die_2; //蝶形角

	//	选择0.3-圆角：
	//	轴向长度
	//	起点半径
	//	圆角半径
	double len_3;
	double start_R_3;
	double ang_die_3; //蝶形角
	double yuanjiao_R_3;

	//	选择1 - 通过dxf获得：
public:
	//	dxf文件路径
	int sel_dxf_pos;
public:
	CanShu_XingXian();
	~CanShu_XingXian();
	
public:
	int save(int pos);
	void load(int pos);
};

//螺旋相位canshu类：根据该类将型线转相位得到螺旋 2*n 长度+转角
class Prog_Manager_API CanShu_LuoXuan
	: public save_lib
{
	//int 转 streampos 超出int范围有风险
private:
	int save_obj_hjbc;
	int save_B_daocheng;
	int save_B_luoxuan;

public:
	//索引关系由id改为pos 10.13
	int guanlian_xx_id=-1;
	int guanlian_fd_id=-1;
	//后角补偿值
	CanShu_Bian obj_hjbc;

	//槽类型选择：
public:
	int type_cao; //0-直槽、1-斜槽、2-螺旋槽
	double R_zhi_or_xie; 
	//	选择0 - 直槽：
public:
	//	类型选择：
	int type_zhi; //0-前角、1-偏心距

	//	选择1.1 - 前角：
	//	前角
	double zhi_ang_qian;

	//	选择1.2 - 偏心距：
	//	偏心距
	double zhi_pianxin;

	//	选择1 - 斜槽
public:
	//	斜角
	double ang_xie; //斜角=倾角

	//	类型选择：
	int type_xie; //0-前角、1-偏心距

	//	选择2.1 - 前角：
	//	前角
	double xie_ang_qian;
	//	选择2.2 - 偏心距
	//	偏心距
	double xie_pianxin;

	//	选择2 - 螺旋槽
public:
	double ang_r;
	//	类型选择：
	int type_luo; //0-等导程、1-等螺旋角、2-变导程、3-变螺旋角

	//	选择3.1 - 等导程：
	//	导程：
	double D_daocheng;	//导程

	//	选择3.2 - 等螺旋角：
	//	螺旋角
	double D_ang_luo;	//螺旋角

	//	选择3.3 - 变导程：
	//	曲线长度坐标：
	//	导程：
	CanShu_Bian  B_daocheng;

	//	选择3.4 - 变螺旋角：
	//	曲线长度坐标：
	//	螺旋角
	CanShu_Bian  B_luoxuan;

public:

private:
public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_XinHouMian
	: public save_lib
{
public:
	//0.0-拉伸面，0.1-回转面 --可根据其他参数被修改
	int type_mian;
	
public:
	//0-型线，1-参数得到
	int type_line;

	//	选择0 - 通过dxf获得：
public:
	int xingxian_pos;

	//	选择1 - 参数得到
	//0-螺旋槽(柱面：直槽，斜槽)，1-平底端齿槽、2-球头槽、3-圆角前刀面、4-成型端齿槽
public:
	int type_cao;
	double dis_acc = 1.0;

	//0-螺旋槽
	double len;
	double start_R;
	double ang_zhui;
	double ang_luo; //25.9.17

	//1-平底端齿槽
	double high_up;
	double ang_cao; //x轴向下夹角

	//2-球头槽
	double r_qiu; //球头半径
	double r_xin;  //芯厚半径
	double high_o;  //芯厚圆上移高度
	double ang_up;	//轴向夹角
	double ang_down;//轴向夹角

	//3-圆角前刀面--
	//方案二：过点直线
	double r_xin_p; //轴心距离
	double ang_p;

	//4 - 成型端齿槽
	double start_len_cx;
	double start_R_cx;
	double end_len_cx;
	double end_R_cx;

	//其他工序设置成可用的默认值，不开放到前端输入 25.10.10
	double len_lashen; //Z方向双向拉伸
	double len_huizhuan_pianyi; //回转轴偏移
	double ang_huizhuan; //回转角度双向

};


class Prog_Manager_API CanShu_BangLiao
	: public save_lib
{
public:
	int type; //0-参数，1-型线

	double cx_D;
	double cx_len;
	double cx_zhui;

	int cx_sel_xx_id;
	int cx_is_max_ring; //型线最大环：0-原始、1-圆柱

public:
	CanShu_BangLiao();
	~CanShu_BangLiao();

private:
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		type,
	//		bangliao_D,
	//		bangliao_len,
	//		bangliao_zhui,
	//		bangliao_sel_xx_index,
	//		bangliao_is_max_ring
	//	);
	//}
	//CanShu_BangLiao() = default;
	//CanShu_BangLiao(
	//	int _type,
	//	double _bangliao_D,
	//	double _bangliao_len,
	//	double _bangliao_zhui,
	//	int _bangliao_sel_xx_index,
	//	int _bangliao_is_max_ring)
	//	: type(_type),
	//	bangliao_D(_bangliao_D),
	//	bangliao_len(_bangliao_len),
	//	bangliao_zhui(_bangliao_zhui),
	//	bangliao_sel_xx_index(_bangliao_sel_xx_index),
	//	bangliao_is_max_ring(_bangliao_is_max_ring) {}
public:
	//int save();
	//void load();
};

class Prog_Manager_API CanShu_FenDu
	: public save_lib
{
public:
	int count;
	double v_ang_pos[20];
public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_QianJiao
	: public save_lib
{
private:
	int save_b_qianjiao_n;
	int save_b_qianjiao_r;

public:
	//1.螺旋id
	int luoxuan_order;

public:
	//2.前角参数：
	//类型选择：
	int type; //0-法向，1-径向

	//1.1 选择0 - 法向前角
	//	曲线长度坐标：
	//	法向前角值：
	// 1列1个点
	CanShu_Bian b_qianjiao_n;

	//1.2 选择1 - 径向前角
	//	曲线长度坐标：
	//	径向前角：
	// 1列1个点
	CanShu_Bian b_qianjiao_r;

public:
	CanShu_QianJiao();
	~CanShu_QianJiao();

private:
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(save_b_qianjiao_n,
	//		save_b_qianjiao_r,
	//		luoxuan_id,
	//		type
	//	);
	//}
	//CanShu_QianJiao() = default;
	//CanShu_QianJiao(int _save_b_qianjiao_n,
	//	int _save_b_qianjiao_r,
	//	int _luoxuan_id,
	//	int _type)
	//	: save_b_qianjiao_n(_type),
	//	save_b_qianjiao_r(_save_b_qianjiao_r),
	//	luoxuan_id(_luoxuan_id),
	//	type(_type)
	//{}
public:
	 int save(int pos);
	 void load(int pos);
};

class Prog_Manager_API CanShu_hdm_rx
	
{
public:
	//型线id
	int xingxian_pos;
	//螺旋id
	int luoxuan_pos;
public:

};

class Prog_Manager_API CanShu_HouJiao
	: public save_lib
{
private:
	int save_B_ang_n_1;
	int	save_B_ang_n_2;
	int	save_B_ang_n_3;
	int	save_B_ang_a_r_1;
	int	save_B_ang_a_r_2;
	int	save_B_ang_a_r_3;
public:
	int guanlian_xx_id = -1;

public:
	//0-法向，1-径向轴向
	int type;

	//选择0-法后角：
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
	//1后角曲线长度坐标：
	//1后角法后角值：
	//占位
	//1后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_n_1;

	//2后角曲线长度坐标：
	//2后角法后角值：
	// 
	//2后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_n_2;

	//3后角曲线长度坐标：
	//3后角法后角值：
	// 
	//3后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_n_3;

	//选择1-径向和轴向后角：
public:
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
	//1后角曲线长度坐标：
	//1后角径向后角值：
	//1后角轴向后角值：
	//1后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_a_r_1;

	//2后角曲线长度坐标：
	//2后角径向后角值：
	//2后角轴向后角值：
	//2后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_a_r_2;

	//3后角曲线长度坐标：
	//3后角径向后角值：
	//3后角轴向后角值：
	//3后角后刀面宽度：
	//一列一个点
	CanShu_Bian_v4 B_ang_a_r_3;

public:
	int save(int pos);
	void load(int pos);
};

class Prog_Manager_API CanShu_HDM
	: public save_lib
{
public:
	//型线id
	int xingxian_pos;
	//螺旋id
	int luoxuan_pos;
	//后角id
	int houjiao_id;
public:

public:
	//int save();
	//void load();

};


//磨削方法：旋转位移参数
class Prog_Manager_API xt_CanShu_HDM_MoXue_XZ_WY
	: public save_lib
{
private:
	int pos_XZ_bian;
	int pos_WY_bian;
public:
	double XZ;
	double WY;
	bool XZ_isbian;
	bool WY_isbian;
	CanShu_Bian XZ_bian;
	CanShu_Bian WY_bian;

	// 使用共享指针代替值类型
	//std::shared_ptr<CanShu_Bian> XZ_bian;
	//std::shared_ptr<CanShu_Bian> WY_bian;
public:
	xt_CanShu_HDM_MoXue_XZ_WY();
	~xt_CanShu_HDM_MoXue_XZ_WY();

public:
	int save(int pos);
	void load(int pos);
};



//磨削方法：切削位移参数
class Prog_Manager_API xt_CanShu_HDM_MoXue_QX_WY
	: public save_lib
{
private:
	int pos_QX_bian;
	int pos_WY_bian;
public:
	double QX;
	double WY;
	bool QX_isbian;
	bool WY_isbian;
	CanShu_Bian QX_bian;
	CanShu_Bian WY_bian;

	//std::shared_ptr<CanShu_Bian> QX_bian;
	//std::shared_ptr<CanShu_Bian> WY_bian;
	xt_CanShu_HDM_MoXue_QX_WY();
public:
	int save(int pos);
	void load(int pos);

};


//磨削方法：摆动位移参数
class Prog_Manager_API _BD_WY_xt_CanShu_HDM_1_MoXue
	: public save_lib
{
private:
	int pos_BD_bian;
	int pos_WY_bian;
public:
	double BD;
	double WY;
	bool BD_isbian;
	bool WY_isbian;
	CanShu_Bian BD_bian;
	CanShu_Bian WY_bian;

	_BD_WY_xt_CanShu_HDM_1_MoXue();

	//std::shared_ptr<CanShu_Bian> BD_bian;
	//std::shared_ptr<CanShu_Bian> WY_bian;
public:
	//	//xt_CanShu_HDM_MoXue_BD_WY();
	//	void save(std::ofstream& outfile);
	//	void load(std::ifstream& infile);
	//public:
	//	template <class Archive>
	//	void serialize(Archive& ar) {
	//		ar(save_BD_bian,
	//			save_WY_bian,
	//			BD,
	//			WY,
	//			BD_isbian,
	//			WY_isbian,
	//			BD_bian(nullptr),
	//			WY_bian(nullptr)
	//		);
	//	}
	//	xt_CanShu_HDM_MoXue_BD_WY() = default;
	//	xt_CanShu_HDM_MoXue_BD_WY(
	//		int _save_BD_bian,
	//		int _save_WY_bian,
	//		double _BD,
	//		double _WY,
	//		bool _BD_isbian,
	//		bool _WY_isbian,
	//		std::shared_ptr<CanShu_Bian> _BD_bian = nullptr,
	//		std::shared_ptr<CanShu_Bian> _WY_bian = nullptr
	//	)
	//		:
	//		save_BD_bian(_save_BD_bian),
	//		save_WY_bian(_save_WY_bian),
	//		BD(_BD),
	//		WY(_WY),
	//		BD_isbian(_BD_isbian),
	//		WY_isbian(_WY_isbian),
	//		BD_bian(_BD_bian),
	//		WY_bian(_WY_bian)
	//	{}
public:
	int pos;
	int save();
	void load();

};
//后刀面磨削参数
class Prog_Manager_API CanShu_HDM_MoXue_FangFa
	: public save_lib
{
private:
	//int pos_xz_wy;
	//int pos_bd_wy;
	int pos_qx_wy;

public:
	int in_or_out;
public:
	int type;//0：旋转+位移；1：摆动+位移, 2: 切削+位移, 3：旋转+摆动

	//后刀面磨削方法只存一种，通过type区分，保持与前刀面方法形式一致 7.8
	//xt_CanShu_HDM_MoXue_XZ_WY xz_wy;

	//xt_CanShu_HDM_MoXue_BD_WY bd_wy;

	xt_CanShu_HDM_MoXue_QX_WY qx_wy;

public:
	CanShu_HDM_MoXue_FangFa();
	//void save(std::ofstream& outfile);
	//void load(std::ifstream& infile);
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(in_or_out,
	//		type,
	//		xz_wy,
	//		bd_wy,
	//		qx_wy
	//	);
	//}
	//CanShu_HDM_MoXue_FangFa() = default;
	//CanShu_HDM_MoXue_FangFa(
	//	int _in_or_out,
	//	int _type,
	//	const xt_CanShu_HDM_MoXue_XZ_WY& _xz_wy,
	//	const xt_CanShu_HDM_MoXue_BD_WY& _bd_wy,
	//	const xt_CanShu_HDM_MoXue_QX_WY& _qx_wy
	//)
	//	:
	//	in_or_out(_in_or_out),
	//	type(_type),
	//	xz_wy(_xz_wy),
	//	bd_wy(_bd_wy),
	//	qx_wy(_qx_wy)
	//{}
public:
	int save(int pos);
	void load(int pos);

};

//前刀面磨削方法参数
class Prog_Manager_API CanShu_QDM_MoXue_FangFa
	: public save_lib
{
public:
	int in_or_out;
public:
	//切削角度
	double ang_qiexue;
	//芯厚的参数
public:
	//0-螺旋槽，1-平底端齿槽、2-球头槽、3-圆角前刀面
	int type_cao;

public:
	CanShu_QDM_MoXue_FangFa();
	~CanShu_QDM_MoXue_FangFa();

private:
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		in_or_out,
	//		ang_qiexue,
	//		type_cao,
	//		//B_mat
	//		);  // 直接序列化 Armadillo 矩阵
	//}
	//CanShu_QDM_FangFa() = default;
	//CanShu_QDM_FangFa(
	//	int    _in_or_out,
	//	double    _ang_qiexue,
	//	int    _type_cao)
	//	:
	//	in_or_out(_in_or_out),
	//	ang_qiexue(_ang_qiexue),
	//	type_cao(_type_cao)
	//{}
public:
	int save(int pos);
	void load(int pos);

};

//进退刀参数
class Prog_Manager_API xt_CanShu_JinTuiDao
	: public save_lib
{
public:
	int JinDaoXiangQie;
	int TuiDaoXiangQie;
	double JingXiangAnQuanJuLi;
	double ZhouXiangAnQuanJuLi;
	double JinDaoJiaoDu;
	double TuiDaoJiaoDu;
	double JinDaoJuLi;
	double TuiDaoJuLi;
	double JieJinJiaoDu;
	double YuanLiJiaoDu;
public:
	xt_CanShu_JinTuiDao();
public:
	int save(int pos);
	void load(int pos);

};

//后刀面磨削变换参数
class Prog_Manager_API xt_CanShu_MoXue_BianHuan
	: public save_lib

{
public:
	double FaXiangPianZhi;
	double ChangDuPianZhi;
	double JingXiangPianZhi;
	double XuanZhuanPianZhi;
public:
	xt_CanShu_MoXue_BianHuan();
	xt_CanShu_MoXue_BianHuan(double inFaXiangPianZhi, double inChangDuPianZhi, double inJingXiangPianZhi, double inXuanZhuanPianZhi);
public:
	void save(std::ofstream& outfile);
	void load(std::ifstream& infile);

public:
	int save(int pos);
	void load(int pos);


};

//后刀面磨削循环单次参数
class Prog_Manager_API xt_CanShu_HDM_MoXue_d_XunHuan
	: public save_lib

{
public:
	int LeiXing;
	int CiShu;
	double YuLiang;
public:
	xt_CanShu_HDM_MoXue_d_XunHuan();
	xt_CanShu_HDM_MoXue_d_XunHuan operator=(const xt_CanShu_HDM_MoXue_d_XunHuan& A);

public:
	int save(int pos);
	void load(int pos);
};

//后刀面磨削循环参数
//由多个磨削循环参数组成，排在前面的参数更接近于型线
class Prog_Manager_API xt_CanShu_MoXue_XunHuan
	: public save_lib
{
public:
	//参数对象序列
	vector<xt_CanShu_HDM_MoXue_d_XunHuan> CanShu;
public:
	//构造函数
	xt_CanShu_MoXue_XunHuan();
	//插入一组循环参数
	void AddCanShu(xt_CanShu_HDM_MoXue_d_XunHuan dCanShu);
	//编辑一组循环参数
	void EditCanShu(int id, xt_CanShu_HDM_MoXue_d_XunHuan dCanShu);
	//删除一组循环参数
	void DeleteCanShu(int);
	//上移动
	void up(int i);
	//下移动
	void down(int i);


	void save(std::ofstream& outfile);
	void load(std::ifstream& infile);

public:
	int save(int pos);
	void load(int pos);

};

//磨削速度参数
class Prog_Manager_API CanShu_SuDu
	: public save_lib
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
public:
	int save(int pos);
	void load(int pos);


};

//阵列参数
class Prog_Manager_API xt_CanShu_MoXue_ZhenLie
	: public save_lib
{
public:
	int DengFen;//0为等分，1为不等分
	int RenShu;
	int BDF_RenShu;
	vec WeiZhi;
public:
	void SetDengfen(int i);//0为等分，其他为不等分
	void SetRenShu(int i);//
	void BDF_add();
	void BDF_delete(int i);
	int BDF_edit(int i, double jiaodu);
	void BDF_Dengfen();
	xt_CanShu_MoXue_ZhenLie();
	void save(std::ofstream& outfile);
	void load(std::ifstream& infile);
public:
	int save(int pos);
	void load(int pos);
};


//范围选择参数
class Prog_Manager_API xt_CanShu_Range
	:  public save_lib
{
public:
	double start;
	double end;
public:
	xt_CanShu_Range();
	xt_CanShu_Range(double in_start, double in_end);
	
public:
	int save(int pos);
	void load(int pos);
};

//抽样参数
class Prog_Manager_API xt_CanShu_Sample
	: public save_lib
{
public:
	double Sample_lenth;
	double Sample_angle;

public:
	//增加两组仿真采样 25.9.17
	double Sample_lenth_2D;
	double Sample_angle_2D;
	double Sample_lenth_3D;
	double Sample_angle_3D;
public:
	xt_CanShu_Sample();

public:
	int save(int pos);
	void load(int pos);
};


//磨后刀面参数
class Prog_Manager_API xt_Mo_HDM_CanShu
	:  public save_lib
{
//存储位置
public:
	double A_before = 0.0;
public:
	xt_CanShu_Range range;
	xt_CanShu_Sample sample;

	xt_CanShu_JinTuiDao jintuidao;
	xt_CanShu_MoXue_BianHuan bianhuan;
	xt_CanShu_MoXue_XunHuan xunhuan;
	xt_CanShu_MoXue_ZhenLie zhenlie;

	CanShu_HDM_MoXue_FangFa fangfa;
	CanShu_SuDu sudu;
public:
	xt_Mo_HDM_CanShu();
public:	
	int save(int pos);
	void load(int pos);

	//访问接口
public:
	double get_range_start();
	double get_range_end();
	double get_sample_len(int cal_flag);
	double get_sample_ang(int cal_flag);
};

class Prog_Manager_API xt_Mo_QDM_CanShu
	:  public save_lib
{
public:
	double A_before = 0.0;
public:
	xt_CanShu_Range range;
	xt_CanShu_Sample sample;

	xt_CanShu_JinTuiDao jintuidao;
	xt_CanShu_MoXue_BianHuan bianhuan;
	xt_CanShu_MoXue_XunHuan xunhuan;
	xt_CanShu_MoXue_ZhenLie zhenlie;

	CanShu_QDM_MoXue_FangFa fangfa;
	CanShu_SuDu sudu;
public:
	int save(int pos);
	void load(int pos);

	//访问接口
public:
	double get_range_start();
	double get_range_end();
	double get_sample_len(int cal_flag);
	double get_sample_ang(int cal_flag);
};

class Prog_Manager_API xt_gx_shalun
{
public:
	double Ry;  //圆角圆心直径
	double r;	//圆角
	double L;	//
public:
	//template <class Archive>
	//void serialize(Archive& ar) {
	//	ar(
	//		D,
	//		R,
	//		FL);  // 基本类型直接序列化
	//}
	//xt_gx_shalun() = default;
	//xt_gx_shalun(
	//	double _D,
	//	double _R,
	//	double _FL)
	//	:
	//	D(_D),
	//	R(_R),
	//	FL(_FL)
	//{}
public:
	//根据id从砂轮库中获取，不存储 6.13
	//int save();
	//void load();
	
	//1、圆角半径(r)；
	//	2、圆角圆心在砂轮杆上到参考点的轴向距离(L)；
	//	3、圆角圆心到砂轮回转中心的径向距离(Ry)。
};


//#pragma pack(push, 8)
#pragma pack(pop) 




